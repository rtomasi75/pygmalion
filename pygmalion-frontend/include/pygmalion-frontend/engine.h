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
		std::string scoreToString(const subjectiveType score)
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
			multiscoreType alphabeta{ multiscoreType() };
			heuristicsType heuristics{ heuristicsType() };
			heuristics.beginSearch();
			const objectiveType score{ node.template search<false>(alphabeta, depthRemaining, 0, principalVariation, heuristics, this->outputStream()) };
			heuristics.endSearch();
			if (isRunning)
			{
				finalVariation = principalVariation;
				if (this->front().postMode())
				{
					this->outputStream() << static_cast<int>(depthRemaining) << " ";
					this->outputStream() << scoreToString(evaluatorType::makeSubjective(score, this->position().movingPlayer())) << " ";
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
		void moveThreadFunc()
		{
			typename descriptorFrontend::stackType stack{ typename descriptorFrontend::stackType(this->position(), this->history(),  this->position().movingPlayer()) };
			depthType depthRemaining{ 0 };
			variationType finalVariation{ variationType() };
			while (principalVariationSearch(stack, depthRemaining, finalVariation, m_MoveThreadIsRunning))
			{
				depthRemaining++;
				if (this->front().exceedsDepthLimit(depthRemaining))
					break;
			}
			this->currentGame().playerClock(this->currentGame().position().movingPlayer()).stop();
			if (!m_MoveThreadAborted)
			{
				if (finalVariation.length() > 0)
				{
					const std::string moveString{ motorType::moveToString(this->position(), finalVariation[0]) };
					this->doMove(finalVariation[0]);
					this->currentGame().playerClock(this->currentGame().position().movingPlayer()).start();
					this->outputStream() << "move " << moveString << std::endl;
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
		void thinkMove() noexcept
		{
			std::unique_lock<std::mutex> lock;
			if (!m_MoveThreadIsRunning)
			{
				const std::chrono::milliseconds timeLeft{ this->allocateTime(std::chrono::duration_cast<std::chrono::milliseconds>(this->currentGame().playerClock(this->currentGame().position().movingPlayer()).timeRemaining()),20) };
				const std::chrono::milliseconds timeLimit{ std::chrono::duration_cast<std::chrono::milliseconds>(this->front().timeLimit()) };
				const std::chrono::milliseconds timeAvailable{ this->front().isTimeLimited() ? std::min(timeLeft,timeLimit) : timeLeft };
				this->currentGame().playerClock(this->currentGame().position().movingPlayer()).start();
				m_MoveThreadIsRunning = true;
				m_MoveThreadAborted = false;
				m_pMoveThread = new std::thread([this]() {moveThreadFunc(); });
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
			this->currentGame().playerClock(this->position().movingPlayer()).set(this->currentGame().playerClock(this->position().movingPlayer()).timeRemaining() + std::chrono::duration_cast<std::chrono::microseconds>(this->front().incrementTime()));
			this->makeMove(movebits);
		}
		constexpr void undoMove() noexcept
		{
			this->unmakeMove();
		}
	};
}