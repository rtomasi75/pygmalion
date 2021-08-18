namespace pygmalion::frontend
{
	template<typename FRONT>
	class engine :
		public pygmalion::search::engine<typename FRONT::nodeType>,
		public FRONT::descriptorFrontend
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = typename FRONT::descriptorFrontend;
#include "include_frontend.h"
	private:
		frontType m_Front;
		std::atomic_bool m_MoveThreadIsRunning;
		bool m_MoveThreadAborted;
		std::mutex m_Mutex;
		std::thread* m_pMoveThread;
		std::string scoreToString(const scoreType score)
		{
			std::stringstream str{ std::stringstream() };
			if (score.isWinning())
			{
				const int value{ 100000 + static_cast<int>(score.winDistance() / 2) };
				str << value;
			}
			else if (score.isLosing())
			{
				const int value{ -100000 - static_cast<int>(score.lossDistance() / 2) };
				str << value;
			}
			else
				str << static_cast<int>(100 * score);
			return str.str();
		}
		static std::string variationToStringFromDepth(const typename descriptorFrontend::stackType& stack, const variationType& variation, const depthType depth) noexcept
		{
			if (variation.length() > depth)
			{
				std::stringstream sstr;
				sstr << stack.moveToString(variation[depth]) << " ";
				typename descriptorFrontend::stackType subStack(stack, variation[depth]);
				sstr << variationToStringFromDepth(subStack, variation, depth + 1);
				return sstr.str();
			}
			return "";
		}
		static std::string variationToString(const typename descriptorFrontend::stackType& stack, const variationType& variation) noexcept
		{
			return variationToStringFromDepth(stack, variation, 0);
		}
		bool principalVariationSearch(const typename descriptorFrontend::stackType& stack, const depthType depthRemaining, variationType& finalVariation, std::atomic_bool& isRunning)
		{
			nodeType node(stack, isRunning);
			variationType principalVariation{ variationType() };
			heuristicsType heuristics{ heuristicsType() };
			heuristics.beginSearch();
			const scoreType score{ node.template search<false>(scoreType::minimum(), scoreType::maximum(), depthRemaining, 0, principalVariation, heuristics, this->outputStream()) };
			heuristics.endSearch();
			if (isRunning)
			{
				finalVariation = principalVariation;
				if (this->front().postMode())
				{
					this->outputStream() << static_cast<int>(depthRemaining) << " ";
					this->outputStream() << scoreToString(score) << " ";
					const std::chrono::milliseconds milliseconds{ std::chrono::duration_cast<std::chrono::milliseconds>(heuristics.duration()) };
					const int centiseconds{ static_cast<int>(milliseconds.count() / 10) };
					this->outputStream() << centiseconds << " ";
					this->outputStream() << heuristics.nodeCount() << " ";
					this->outputStream() << variationToString(stack, finalVariation) << std::endl;
				}
				return true;
			}
			return false;
		}
		void moveThreadFunc(const std::chrono::milliseconds allocatedTime)
		{
			typename descriptorFrontend::stackType stack{ typename descriptorFrontend::stackType(this->position(), this->history(),  this->position().movingPlayer()) };
			depthType depthRemaining{ 0 };
			variationType finalVariation{ variationType() };
			std::chrono::milliseconds timeRemaining{ std::chrono::duration_cast<std::chrono::milliseconds>(this->currentGame().playerClock(this->position().movingPlayer()).timeRemaining()) };
			std::chrono::milliseconds searchTime{ std::chrono::milliseconds(0) };
			double factor[]{ 0.0,0.0 };
			while (principalVariationSearch(stack, depthRemaining, finalVariation, m_MoveThreadIsRunning))
			{
				depthRemaining++;
				if (this->front().exceedsDepthLimit(depthRemaining))
					break;
				const std::chrono::milliseconds plyTime{ timeRemaining - std::chrono::duration_cast<std::chrono::milliseconds>(this->currentGame().playerClock(this->position().movingPlayer()).timeRemaining()) };
				timeRemaining = std::chrono::duration_cast<std::chrono::milliseconds>(this->currentGame().playerClock(this->position().movingPlayer()).timeRemaining());
				searchTime += plyTime;
				if (depthRemaining > 2)
				{
					factor[depthRemaining % 2] = static_cast<double>(searchTime.count()) / static_cast<double>((searchTime - plyTime).count());
					if (depthRemaining > 4)
					{
						const std::chrono::milliseconds projectedTime{ std::chrono::milliseconds(static_cast<long>(searchTime.count() * factor[(depthRemaining + 1) % 2])) };
						const std::chrono::milliseconds neededTime{ projectedTime - searchTime };
						if (neededTime > (allocatedTime - searchTime))
							break;
					}
				}
			}
			this->currentGame().playerClock(this->currentGame().position().movingPlayer()).stop();
			if (!m_MoveThreadAborted)
			{
				if (finalVariation.length() > 0)
				{
					const std::string moveString{ motorType::moveToString(this->currentGame().position(), finalVariation[0]) };
					this->doMove(finalVariation[0]);
					this->currentGame().playerClock(this->currentGame().position().movingPlayer()).start();
					this->outputStream() << "move " << moveString << std::endl;
					const gamestateType result{ evaluatorType::earlyResult(stack) };
					if (!gamestateType::isOpen(result))
					{
						this->outputStream() << "result " << frontType::gamestateToString(this->currentGame().position(), result) << std::endl;
					}
				}
			}
			std::unique_lock<std::mutex> lock;
			m_MoveThreadIsRunning = false;
		}
	public:
		constexpr frontType& front() noexcept
		{
			return m_Front;
		}
		constexpr const frontType& front() const noexcept
		{
			return m_Front;
		}
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::search::engine<typename FRONT::nodeType>(input, output),
			m_Front{ frontType() },
			m_MoveThreadIsRunning{ false },
			m_Mutex{ std::mutex() },
			m_pMoveThread{ nullptr },
			m_MoveThreadAborted{ false }
		{
			this->template addCommand<command_debugFrontend<descriptorFrontend, frontType>>();
			this->template addCommand<command_xboard<descriptorFrontend, frontType>>();
			this->template addCommand<command_protover<descriptorFrontend, frontType>>();
			this->template addCommand<command_accepted<descriptorFrontend, frontType>>();
			this->template addCommand<command_rejected<descriptorFrontend, frontType>>();
			this->template addCommand<command_random<descriptorFrontend, frontType>>();
			this->template addCommand<command_computer<descriptorFrontend, frontType>>();
			this->template addCommand<command_sd<descriptorFrontend, frontType>>();
			this->template addCommand<command_st<descriptorFrontend, frontType>>();
			this->template addCommand<command_force<descriptorFrontend, frontType>>();
			this->template addCommand<command_name<descriptorFrontend, frontType>>();
			this->template addCommand<command_post<descriptorFrontend, frontType>>();
			this->template addCommand<command_nopost<descriptorFrontend, frontType>>();
			this->template addCommand<command_level<descriptorFrontend, frontType>>();
			this->template addCommand<command_debugClocks<descriptorFrontend, frontType>>();
			this->template addCommand<command_go<descriptorFrontend, frontType>>();
			this->template addCommand<command_hard<descriptorFrontend, frontType>>();
			this->template addCommand<command_easy<descriptorFrontend, frontType>>();
			this->template addCommand<command_undo<descriptorFrontend, frontType>>();
			this->template addCommand<command_usermove<descriptorFrontend, frontType>>();
		}
		virtual ~engine() noexcept
		{
			cancelMove();
		}
		virtual std::string version() const noexcept override
		{
			return "no game (frontend only)";
		}
		virtual double timeSkew() const noexcept
		{
			return 1.0;
		}
		virtual int expectedGameLength() const noexcept
		{
			return 60;
		}
		virtual int minimumExpectedGameLength() const noexcept
		{
			return 20;
		}
		constexpr std::chrono::milliseconds allocateTime(const playerType pl) const noexcept
		{
			const int historyLength{ static_cast<int>(this->history().length() / 2) };
			const int movesPerTimeControl{ this->currentGame().movesPerTimeControl() ? static_cast<int>(this->currentGame().movesPerTimeControl()) : expectedGameLength() };
			const int movesPlayed{ this->currentGame().movesPerTimeControl() ? static_cast<int>(this->currentGame().lastTimeControl(pl)) : historyLength };
			const int movesLeft{ std::max(this->currentGame().movesPerTimeControl() ? 1 : minimumExpectedGameLength(),movesPerTimeControl - movesPlayed) };
			const std::chrono::milliseconds allocated{ std::chrono::duration_cast<std::chrono::milliseconds>(this->currentGame().playerClock(pl).timeRemaining() / movesLeft) + this->currentGame().incrementTime() };
			const double factor{ std::max(static_cast<double>(expectedGameLength() - historyLength), 0.0) / static_cast<double>(expectedGameLength()) };
			const double skew{ (factor * timeSkew()) + (1.0 - factor) };
			const std::chrono::milliseconds result{ std::chrono::milliseconds(std::min(static_cast<long>(skew * allocated.count()), static_cast<long>(0.95 * this->currentGame().playerClock(pl).timeRemaining().count()))) };
			return result;
		}
		void thinkMove() noexcept
		{
			std::unique_lock<std::mutex> lock;
			if (!m_MoveThreadIsRunning)
			{
				const std::chrono::milliseconds timeLeft{ this->allocateTime(this->currentGame().position().movingPlayer()) };
				const std::chrono::milliseconds timeLimit{ std::chrono::duration_cast<std::chrono::milliseconds>(this->front().timeLimit()) };
				const std::chrono::milliseconds timeAvailable{ this->front().isTimeLimited() ? std::min(timeLeft,timeLimit) : timeLeft };
				this->currentGame().playerClock(this->currentGame().position().movingPlayer()).start();
				m_MoveThreadIsRunning = true;
				m_MoveThreadAborted = false;
				m_pMoveThread = new std::thread([this, timeLeft]() {moveThreadFunc(timeLeft); });
				std::thread timerThread
				{
					std::thread(
						[this, timeAvailable]()
						{
							std::this_thread::sleep_for(timeAvailable);
							std::unique_lock<std::mutex> lock;
							if (m_MoveThreadIsRunning)
								forceMove();
							else
							{
								if (m_pMoveThread)
								{
									m_pMoveThread->join();
									delete m_pMoveThread;
									m_pMoveThread = nullptr;
								}
							}
						}
					)
				};
				timerThread.detach();
			}
		}
		void cancelMove() noexcept
		{
			std::unique_lock<std::mutex> lock;
			if (m_MoveThreadIsRunning)
			{
				m_MoveThreadAborted = true;
				m_MoveThreadIsRunning = false;
				m_pMoveThread->join();
				delete m_pMoveThread;
				m_pMoveThread = nullptr;
			}
		}
		void forceMove() noexcept
		{
			std::unique_lock<std::mutex> lock;
			if (m_MoveThreadIsRunning)
			{
				m_MoveThreadAborted = false;
				m_MoveThreadIsRunning = false;
				m_pMoveThread->join();
				delete m_pMoveThread;
				m_pMoveThread = nullptr;
			}
		}
		constexpr void doMove(const movebitsType& movebits) noexcept
		{
			this->currentGame().playerClock(this->position().movingPlayer()).set(this->currentGame().playerClock(this->position().movingPlayer()).timeRemaining() + std::chrono::duration_cast<std::chrono::microseconds>(this->currentGame().incrementTime()));
			this->makeMove(movebits);
		}
		constexpr void undoMove() noexcept
		{
			this->unmakeMove();
		}
	};
}