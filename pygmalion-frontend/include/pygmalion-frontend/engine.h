namespace pygmalion::frontend
{
	template<typename FRONT>
	class engine :
		public pygmalion::search::engine<typename FRONT::gametreeType>,
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
		std::string scoreToString(const scoreType& score)
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
		indexType m_CurrentMove;
		indexType m_CountMoves;
		depthType m_CurrentDepth;
		scoreType m_ScoreFromPreviousDepth;
		template<size_t PLAYER>
		bool principalVariationSearch(const typename descriptorFrontend::template stackType<PLAYER>& stack, const depthType& depthRemaining, variationType& finalVariation, std::atomic_bool& isRunning) noexcept
		{
			using nodeType = typename gametreeType::template nodeType<PLAYER>;
			nodeType node(stack, isRunning, this->heuristics(), this->history().length());
			variationType principalVariation{ variationType() };
			this->feedback().sortIndices(this->history().length());
			this->heuristics().beginSearch();
			scoreType score;
			if (this->front().analyzeMode())
				score = node.template searchRoot<false, true>(depthRemaining, principalVariation, m_ScoreFromPreviousDepth, this->outputStream(), m_CurrentMove, m_CountMoves);
			else
				score = node.template searchRoot<false, false>(depthRemaining, principalVariation, m_ScoreFromPreviousDepth, this->outputStream(), m_CurrentMove, m_CountMoves);
			this->heuristics().endSearch();
			if (isRunning)
			{
				finalVariation = principalVariation;
				if (this->front().postMode() && this->front().isXBoard())
				{
					this->outputStream() << static_cast<int>(depthRemaining) << " ";
					this->outputStream() << scoreToString(score) << " ";
					const std::chrono::milliseconds milliseconds{ std::chrono::duration_cast<std::chrono::milliseconds>(this->heuristics().duration()) };
					const int centiseconds{ static_cast<int>(milliseconds.count() / 10) };
					this->outputStream() << centiseconds << " ";
					this->outputStream() << this->heuristics().nodeCount() << " ";
					this->outputStream() << this->template variationToString<PLAYER>(finalVariation) << std::endl;
				}
				return true;
			}
			return false;
		}
		template<size_t PLAYER>
		void moveThreadFunc(const durationType allocatedTime)
		{
			typename descriptorFrontend::template stackType<PLAYER> stack{ typename descriptorFrontend::template stackType<PLAYER>(this->position(), this->history(), this->rootContext()) };
			m_CurrentDepth = 0;
			variationType finalVariation{ variationType() };
			durationType timeRemaining{ this->currentGame().playerClock(this->position().movingPlayer()).timeRemaining() };
			durationType searchTime{ durationType(0) };
			double factor[]{ 0.0,0.0 };
			m_ScoreFromPreviousDepth = evaluatorType::evaluate(scoreType::minimum(), scoreType::maximum(), stack);
			while (principalVariationSearch(stack, m_CurrentDepth, finalVariation, m_MoveThreadIsRunning))
			{
				if ((finalVariation.length() > 0) && this->front().analyzeMode())
				{
					this->front().hintMove() = finalVariation[0];
					this->front().hasHint() = true;
				}
				++m_CurrentDepth;
				if (!(this->front().analyzeMode()))
				{
					if (this->front().exceedsDepthLimit(m_CurrentDepth))
						break;
				}
				const durationType plyTime{ timeRemaining - this->currentGame().playerClock(this->position().movingPlayer()).timeRemaining() };
				timeRemaining = std::chrono::duration_cast<std::chrono::milliseconds>(this->currentGame().playerClock(this->position().movingPlayer()).timeRemaining());
				searchTime += plyTime;
				if (m_CurrentDepth > countPlayers)
				{
					factor[m_CurrentDepth % countPlayers] = static_cast<double>(searchTime.count()) / static_cast<double>((searchTime - plyTime).count());
					if (m_CurrentDepth > (2 * countPlayers))
					{
						const durationType projectedTime{ durationType(static_cast<long>(searchTime.count() * factor[(m_CurrentDepth + countPlayers - 1) % countPlayers])) };
						const durationType neededTime{ projectedTime - searchTime };
						if (!(this->front().analyzeMode()))
						{
							if (neededTime > (allocatedTime - searchTime))
								break;
						}
					}
				}
			}
			if (!(this->front().analyzeMode()))
				this->currentGame().playerClock(this->currentGame().position().movingPlayer()).stop();
			if (!m_MoveThreadAborted)
			{
				if ((finalVariation.length() > 0) && !(this->front().analyzeMode()))
				{
					const std::string moveString{ motorType::moveToString(this->currentGame().position(), finalVariation[0]) };
					this->doMove(finalVariation[0]);
					if (finalVariation.length() > 1)
					{
						this->front().hintMove() = finalVariation[1];
						this->front().hasHint() = true;
					}
					else
					{
						this->front().hasHint() = false;
					}
					this->currentGame().playerClock(this->currentGame().position().movingPlayer()).start();
					this->outputStream() << "move " << moveString << std::endl;
					bool allowStoreTT;
					const gamestateType result{ evaluatorType::template earlyResult<PLAYER,false>(stack, allowStoreTT) };
					if (!gamestateType::isOpen(result))
					{
						this->outputStream() << "result " << frontType::gamestateToString(this->currentGame().position(), result) << std::endl;
					}
					this->outputStream().flush();
				}
			}
			this->front().analyzeMode() = false;
			this->front().ponderMode() = false;
			std::unique_lock<std::mutex> lock;
			m_MoveThreadIsRunning = false;
		}
	public:
		virtual void onPositionChanged() noexcept override
		{
			this->front().hasHint() = false;
		}
		virtual void onMakeMove(const movebitsType movebits) noexcept override
		{
			pygmalion::search::engine<typename FRONT::gametreeType>::onMakeMove(movebits);
			this->front().hasHint() = false;
		}
		virtual void onUnMakeMove() noexcept override
		{
			pygmalion::search::engine<typename FRONT::gametreeType>::onUnMakeMove();
			this->front().hasHint() = false;
		}
		depthType currentDepth() const noexcept
		{
			return m_CurrentDepth;
		}
		indexType countMoves() const noexcept
		{
			return m_CountMoves;
		}
		indexType currentMove() const noexcept
		{
			return m_CurrentMove;
		}
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
			pygmalion::search::engine<typename FRONT::gametreeType>(input, output),
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
			this->template addCommand<command_uci<descriptorFrontend, frontType>>();
			this->template addCommand<command_debug<descriptorFrontend, frontType>>();
			this->template addCommand<command_isready<descriptorFrontend, frontType>>();
			this->template addCommand<command_draw<descriptorFrontend, frontType>>();
			this->template addCommand<command_bk<descriptorFrontend, frontType>>();
			this->template addCommand<command_hint<descriptorFrontend, frontType>>();
			this->template addCommand<command_analyze<descriptorFrontend, frontType>>();
			this->template addCommand<command_ping<descriptorFrontend, frontType>>();
		}
		virtual ~engine() noexcept
		{
			cancelMove();
		}
		virtual double timeSkew() const noexcept
		{
			return 2.0;
		}
		virtual int expectedGameLength() const noexcept
		{
			return 40;
		}
		virtual int minimumExpectedGameLength() const noexcept
		{
			return 10;
		}
		constexpr durationType allocateTime(const playerType& pl) const noexcept
		{
			const int movesPerTimeControl{ this->currentGame().movesPerTimeControl() };
			if (movesPerTimeControl == 0)
			{
				const int movesPlayed{ static_cast<int>(this->history().length() / countPlayers) };
				const int movesLeft{ std::max(minimumExpectedGameLength(),expectedGameLength() - movesPlayed) };
				const durationType timeRemaining{ this->currentGame().playerClock(pl).timeRemaining() / movesLeft };
				const double factor{ std::max(0.0,static_cast<double>(movesLeft - (expectedGameLength() - minimumExpectedGameLength()))) / static_cast<double>(expectedGameLength() - minimumExpectedGameLength()) };
				const double skew{ factor * timeSkew() + (1.0 - factor) * 1.0 };
				const durationType allocated{ durationType(static_cast<long long>(skew * static_cast<double>(timeRemaining.count()))) + this->currentGame().incrementTime() };
				return allocated;
			}
			else
			{
				const int movesPlayed{ static_cast<int>(this->currentGame().lastTimeControl(pl)) };
				const int movesLeft{ movesPerTimeControl - movesPlayed };
				const durationType timeRemaining{ this->currentGame().playerClock(pl).timeRemaining() / movesLeft };
				const double factor{ std::max(0.0,static_cast<double>(movesLeft - (expectedGameLength() - minimumExpectedGameLength()))) / static_cast<double>(expectedGameLength() - minimumExpectedGameLength()) };
				const double skew{ factor * timeSkew() + (1.0 - factor) * 1.0 };
				const durationType allocated{ durationType(static_cast<long long>(skew * static_cast<double>(timeRemaining.count()))) + this->currentGame().incrementTime() };
				return allocated;
			}
		}
		template<size_t PLAYER>
		void thinkMove() noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			if (!m_MoveThreadIsRunning)
			{
				const durationType timeLeft{ this->allocateTime(this->currentGame().position().movingPlayer()) };
				const durationType timeLimit{ this->front().timeLimit() };
				const durationType timeAvailable{ this->front().isTimeLimited() ? std::min(timeLeft,timeLimit) : timeLeft };
				const timeType startTime{ chronographType::now() };
				if (!(this->front().analyzeMode()))
					this->currentGame().playerClock(this->currentGame().position().movingPlayer()).start();
				m_MoveThreadIsRunning = true;
				m_MoveThreadAborted = false;
				m_pMoveThread = new std::thread([this, timeAvailable]() {moveThreadFunc<PLAYER>(timeAvailable); });
				this->front().hasHint() = false;
				if (!this->front().analyzeMode())
				{
					std::thread timerThread
					{
						std::thread(
							[this,timeAvailable]()
							{
								const timeType start{ chronographType::now() };
								bool isElapsed{ false };
								while (m_MoveThreadIsRunning && !isElapsed)
								{
									const timeType end{ chronographType::now() + std::chrono::duration_cast<durationType>(std::chrono::milliseconds(10)) };
									std::this_thread::sleep_until(end);
									std::this_thread::sleep_for(std::chrono::milliseconds(10));
									const durationType elapsedTime{ std::chrono::duration_cast<durationType>(chronographType::now() - start) };
									if ((elapsedTime + std::chrono::milliseconds(10)) > timeAvailable)
									{
										isElapsed = true;
									}
								}
								std::unique_lock<std::mutex> lock(m_Mutex);
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
		}
		template<size_t PLAYER>
		void startAnalysis()
		{
			if (!this->front().analyzeMode())
			{
				this->front().analyzeMode() = true;
				this->template thinkMove<PLAYER>();
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
		void stopAnalysis() noexcept
		{
			std::unique_lock<std::mutex> lock;
			if (this->front().analyzeMode())
			{
				if (m_MoveThreadIsRunning)
				{
					m_MoveThreadAborted = true;
					m_MoveThreadIsRunning = false;
					m_pMoveThread->join();
					delete m_pMoveThread;
					m_pMoveThread = nullptr;
				}
				this->front().analyzeMode() = false;
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
		void doMove(const movebitsType& movebits) noexcept
		{
			this->currentGame().playerClock(this->position().movingPlayer()).set(this->currentGame().playerClock(this->position().movingPlayer()).timeRemaining() + std::chrono::duration_cast<durationType>(this->currentGame().incrementTime()));
			this->makeMove(movebits);
		}
		void undoMove() noexcept
		{
			this->unmakeMove();
		}
	};
}