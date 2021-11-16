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
		template<size_t PLAYER>
		using nodeType = typename gametreeType::template nodeType<PLAYER>;
	private:
		frontType m_Front;
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
		signal m_Stop;
		signal m_IsRunning;
		template<size_t PLAYER>
		bool principalVariationSearch(nodeType<PLAYER>& node, const depthType& depthRemaining, durationType& finalDuration, std::uintmax_t& finalNodes, depthType& finalDepth, variationType& finalVariation, scoreType finalScore) noexcept
		{
			variationType principalVariation{ variationType() };
			this->heuristics().beginSearch();
			scoreType score;
			score = node.template searchRoot<false>(depthRemaining, principalVariation, m_ScoreFromPreviousDepth, m_CurrentMove, m_CountMoves);
			this->heuristics().endSearch();
			bool bReturn{ false };
			m_Stop.doIfLow(
				[depthRemaining, score, &principalVariation, &bReturn, &finalVariation, &finalScore, &finalDepth, &finalNodes, &finalDuration, this]()
				{
					finalVariation = principalVariation;
					finalScore = score;
					finalDepth = depthRemaining;
					finalNodes = this->heuristics().nodeCount();
					finalDuration = std::chrono::duration_cast<durationType>(this->heuristics().duration());
					std::stringstream outStream;
					outStream << "info ";
					outStream << "depth " << static_cast<int>(depthRemaining) << " ";
					const std::chrono::milliseconds milliseconds{ std::chrono::duration_cast<std::chrono::milliseconds>(this->heuristics().duration()) };
					outStream << "time " << static_cast<std::uintmax_t>(milliseconds.count()) << " ";
					outStream << "nodes " << this->heuristics().nodeCount() << " ";
					outStream << "score ";
					if (score.isOpen())
					{
						outStream << "cp " << static_cast<std::intmax_t>(static_cast<double>(score) * 100.0) << " ";
					}
					else
					{
						outStream << "mate ";
						if (score.isWinning())
						{
							outStream << static_cast<std::intmax_t>((score.winDistance() + 1) / 2) << " ";
						}
						else
						{
							outStream << -static_cast<std::intmax_t>((score.lossDistance() + 1) / 2) << " ";
						}
					}
					if (finalVariation.length() > 0)
					{
						outStream << "pv";
						for (depthType i = 0; i < finalVariation.length(); i++)
						{
							outStream << " ";
							std::string str{ motorType::moveToString(this->position(), finalVariation[i]) };
							this->makeMove(finalVariation[i]);
							outStream << str;
						}
						for (depthType i = 0; i < finalVariation.length(); i++)
						{
							this->unmakeMove();
						}
					}
					outStream << std::endl;
					this->writeOutput(outStream.str());
					bReturn = true;
				}
			);
			return bReturn;
		}
		timeType m_SearchTimerStart;
		durationType m_SearchTimerInterval;
		std::atomic_bool m_PonderEnabled;
		signal m_TimerStarted;
		threadqueue m_SearchQueue;
		threadqueue m_TimerQueue;
		std::mutex m_SearchMutex;
		void timeThreadFunction() noexcept
		{
			this->writeDebugString("Timer ticking...");
			bool isElapsed{ false };
			while (!isElapsed)
			{
				isElapsed = true;
				m_Stop.doIfLow(
					[this, &isElapsed]()
					{
						const durationType elapsedTime{ std::chrono::duration_cast<durationType>(chronographType::now() - m_SearchTimerStart) };
						if ((elapsedTime + std::chrono::milliseconds(10)) > m_SearchTimerInterval)
						{
							this->writeDebugString("Timer elapsed...");
							isElapsed = true;
						}
						else
							isElapsed = false;
					}
				);
				if (isElapsed)
				{
					this->writeDebugString("Timer firing...");
					m_Stop.raise();
					break;
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
			this->writeDebugString("Timer finished...");
			m_TimerStarted.lower();
		}
		template<size_t PLAYER>
		void searchThreadFunc() noexcept
		{
			m_IsRunning.raise();
			this->writeDebugString("Search started...");
			typename descriptorFrontend::template stackType<PLAYER> stack{ typename descriptorFrontend::template stackType<PLAYER>(this->position(), this->history(), this->rootContext()) };
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType nextPlayer{ movingPlayer.next() };
			m_CurrentDepth = 0;
			variationType finalVariation{ variationType() };
			durationType searchTime{ durationType(0) };
			std::array<double, countPlayers> factor{ arrayhelper::make<countPlayers,double>(0.0) };
			m_ScoreFromPreviousDepth = evaluatorType::evaluate(scoreType::minimum(), scoreType::maximum(), stack);
			timeType start{ chronographType::now() };
			scoreType finalScore;
			depthType finalDepth{ depthType(-1) };
			std::uintmax_t finalNodes{ UINTMAX_C(0) };
			durationType finalDuration{ durationType(0) };
			nodeType<PLAYER> node(stack, m_Stop, this->heuristics(), this->history().length());
			while (principalVariationSearch(node, m_CurrentDepth, finalDuration, finalNodes, finalDepth, finalVariation, finalScore))
			{
				++m_CurrentDepth;
				const durationType plyTime{ std::chrono::duration_cast<durationType>(chronographType::now() - start) };
				searchTime += plyTime;
				if (this->front().exceedsDepthLimit(m_CurrentDepth))
				{
					this->writeDebugString("Depth limit exceeded...");
					break;
				}
				if (this->front().exceedsTimeLimit(searchTime))
				{
					this->writeDebugString("Time limit exceeded...");
					break;
				}
				if (m_CurrentDepth >= countSearchPlies)
				{
					this->writeDebugString("Reached maximum ply depth...");
					break;
				}
				if (m_CurrentDepth > countPlayers)
				{
					bool bBreak{ false };
					factor[m_CurrentDepth % countPlayers] = static_cast<double>(searchTime.count()) / static_cast<double>((searchTime - plyTime).count());
					m_TimerStarted.doIfHigh([this, &factor, searchTime, &bBreak]()
						{
							if (m_CurrentDepth > (2 * countPlayers))
							{
								const durationType projectedTime{ durationType(static_cast<long>(searchTime.count() * factor[(m_CurrentDepth + countPlayers - 1) % countPlayers])) };
								const durationType neededTime{ projectedTime - searchTime };
								const durationType remainingTime{ m_SearchTimerInterval - std::chrono::duration_cast<durationType>(chronographType::now() - m_SearchTimerStart) };
								if (neededTime > remainingTime)
								{
									this->writeDebugString("Not enough time for another ply...");
									bBreak = true;
								}
							}
						});
					if (bBreak)
						break;
				}
			}
			std::stringstream outStream;
			outStream << "bestmove";
			if (finalVariation.length() > 0)
			{
				const std::string hintMoveString{ motorType::moveToString(this->currentGame().position(), finalVariation[0]) };
				outStream << " " << hintMoveString;
				if (m_PonderEnabled)
				{
					if (finalVariation.length() > 1)
					{
						this->makeMove(finalVariation[0]);
						const std::string ponderMoveString{ motorType::moveToString(this->currentGame().position(), finalVariation[1]) };
						this->unmakeMove();
						outStream << " ponder " << ponderMoveString;
					}
				}
				outStream << std::endl;
			}
			else
			{
				outStream << " 0000";
				outStream << std::endl;
			}
			m_TimerStarted.doIfHigh(
				[this]()
				{
					m_Stop.raise();
				}
			);
			m_TimerStarted.wait(false);
			this->writeOutput(outStream.str());
			this->writeDebugString("Search finished...");
			m_IsRunning.lower();
		}
		void limitSearchInternal(const durationType& timeLeft) noexcept
		{
			m_TimerStarted.doIfElse(
				[this, timeLeft]()
				{
					const timeType startTime{ chronographType::now() };
					m_SearchTimerStart = startTime;
					m_SearchTimerInterval = timeLeft;
					this->writeDebugString("Timer modified (" + parser::durationToString(m_SearchTimerInterval) + " )...");
					return true;
				},
				[this, timeLeft]()
				{
					const timeType startTime{ chronographType::now() };
					m_SearchTimerStart = startTime;
					m_SearchTimerInterval = timeLeft;
					m_TimerQueue.start(
						[this]()
						{
							timeThreadFunction();
						}
					);
					this->writeDebugString("Timer started (" + parser::durationToString(m_SearchTimerInterval) + " )...");
					return true;
				}
				);
		}
	public:
		bool ponderEnabled() const noexcept
		{
			return m_PonderEnabled;
		}
		virtual void resizeHashTables(const size_t sizeInBytes) noexcept
		{

		}
		virtual void onPositionChanged() noexcept override
		{
			this->front().clearHintMove();
		}
		virtual void onMakeMove(const movebitsType movebits) noexcept override
		{
			pygmalion::search::engine<typename FRONT::gametreeType>::onMakeMove(movebits);
			this->front().clearHintMove();
		}
		virtual void onUnMakeMove() noexcept override
		{
			pygmalion::search::engine<typename FRONT::gametreeType>::onUnMakeMove();
			this->front().clearHintMove();
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
			m_IsRunning{ signal(false) },
			m_Stop{ signal(false) },
			m_PonderEnabled{ false },
			m_TimerStarted{ signal(false) },
			m_Front{ frontType() }
		{
			this->template addCommand<command_ucinewgame<descriptorFrontend, frontType>>();
			this->template addCommand<command_uci<descriptorFrontend, frontType>>();
			this->template addCommand<command_isready<descriptorFrontend, frontType>>();
			this->template addCommand<command_position<descriptorFrontend, frontType>>();
			this->template addCommand<command_stop<descriptorFrontend, frontType>>();
			this->template addCommand<command_ponderhit<descriptorFrontend, frontType>>();
			this->template addCommand<command_setoption<descriptorFrontend, frontType>>();
			this->template addCommand<command_debug<descriptorFrontend, frontType>>();
			this->template addCommand<command_go<descriptorFrontend, frontType>>();
			this->template addCommand<command_debugFrontend<descriptorFrontend, frontType>>();
			this->template addCommand<command_debugClocks<descriptorFrontend, frontType>>();
		}
		virtual ~engine() noexcept
		{
			forceMove();
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
				const durationType timeRemaining{ this->currentGame().playerClock(pl).timeRemaining() / (movesLeft) };
				const double factor{ std::max(0.0,static_cast<double>(movesLeft - (expectedGameLength() - minimumExpectedGameLength() + 1))) / static_cast<double>(expectedGameLength() - minimumExpectedGameLength()) };
				const double skew{ factor * timeSkew() + (1.0 - factor) * 1.0 };
				const durationType allocated{ std::min(durationType(static_cast<long long>(skew * static_cast<double>(timeRemaining.count()))) + this->currentGame().incrementTime(this->position().movingPlayer()),durationType(static_cast<long long>(0.95 * static_cast<double>(this->currentGame().playerClock(pl).timeRemaining().count())))) };
				return allocated;
			}
			else
			{
				const int movesPlayed{ static_cast<int>(this->currentGame().lastTimeControl(pl)) };
				const int movesLeft{ movesPerTimeControl - (movesPlayed % movesPerTimeControl) };
				const durationType timeRemaining{ this->currentGame().playerClock(pl).timeRemaining() / (movesLeft) };
				const double factor{ std::max(0.0,static_cast<double>(movesLeft - (expectedGameLength() - minimumExpectedGameLength() + 1))) / static_cast<double>(expectedGameLength() - minimumExpectedGameLength()) };
				const double skew{ factor * timeSkew() + (1.0 - factor) * 1.0 };
				const durationType allocated{ std::min(durationType(static_cast<long long>(skew * static_cast<double>(timeRemaining.count()))) + this->currentGame().incrementTime(this->position().movingPlayer()),durationType(static_cast<long long>(0.95 * static_cast<double>(this->currentGame().playerClock(pl).timeRemaining().count())))) };
				return allocated;
			}
		}
		template<size_t PLAYER>
		void searchMoveLimited() noexcept
		{
			std::unique_lock<std::mutex> lock(m_SearchMutex);
			this->writeDebugString("Waiting for search to finish...");
			m_IsRunning.wait(false,
				[this]()
				{
					this->writeDebugString("Search finished...");
				}
			);
			m_Stop.lower();
			m_SearchQueue.start([this]()
				{
					this->template searchThreadFunc<PLAYER>();
				});
			m_IsRunning.wait(
				[this]()
				{
					this->writeDebugString("Search (limited) launched...");
					const durationType timeLeft{ this->allocateTime(this->currentGame().position().movingPlayer()) };
					m_TimerStarted.doIfElse(
						[this, timeLeft]()
						{
							const timeType startTime{ chronographType::now() };
							m_SearchTimerStart = startTime;
							m_SearchTimerInterval = timeLeft;
							this->writeDebugString("Timer modified (" + parser::durationToString(m_SearchTimerInterval) + " )...");
							return true;
						},
						[this, timeLeft]()
						{
							const timeType startTime{ chronographType::now() };
							m_SearchTimerStart = startTime;
							m_SearchTimerInterval = timeLeft;
							m_TimerQueue.start(
								[this]()
								{
									timeThreadFunction();
								}
							);
							this->writeDebugString("Timer started (" + parser::durationToString(m_SearchTimerInterval) + " )...");
							return true;
						}
						);
				}
			);
		}
		template<size_t PLAYER>
		void searchMoveUnlimited() noexcept
		{
			std::unique_lock<std::mutex> lock(m_SearchMutex);
			this->writeDebugString("Waiting for search to finish...");
			m_IsRunning.wait(false,
				[this]()
				{
					this->writeDebugString("Search finished...");
				}
			);
			m_Stop.lower();
			m_SearchQueue.start(
				[this]()
				{
					this->template searchThreadFunc<PLAYER>();
				});
			m_IsRunning.wait(
				[this]()
				{
					this->writeDebugString("Search (unlimited) launched...");
				}
			);
		}
		void limitSearch() noexcept
		{
			std::unique_lock<std::mutex> lock(m_SearchMutex);
			m_IsRunning.doIfHigh(
				[this]()
				{
					const durationType timeLeft{ this->allocateTime(this->currentGame().position().movingPlayer()) };
					m_TimerStarted.doIfElse(
						[this, timeLeft]()
						{
							const timeType startTime{ chronographType::now() };
							m_SearchTimerStart = startTime;
							m_SearchTimerInterval = timeLeft;
							this->writeDebugString("Timer modified (" + parser::durationToString(m_SearchTimerInterval) + " )...");
							return true;
						},
						[this, timeLeft]()
						{
							const timeType startTime{ chronographType::now() };
							m_SearchTimerStart = startTime;
							m_SearchTimerInterval = timeLeft;
							m_TimerQueue.start(
								[this]()
								{
									timeThreadFunction();
								}
							);
							this->writeDebugString("Timer started (" + parser::durationToString(m_SearchTimerInterval) + " )...");
							return true;
						}
						);
					this->writeDebugString("Search limited...");
				}
			);
		}
		void forceMove() noexcept
		{
			std::unique_lock<std::mutex> lock(m_SearchMutex);
			m_IsRunning.doIfHigh(
				[this]()
				{
					m_Stop.raise();
					this->writeDebugString("Search signaled...");
				}
			);
		}
		void waitForSearchToFinish() noexcept
		{
			this->writeDebugString("Waiting for search to finish...");
			m_IsRunning.wait(false,
				[this]()
				{
					this->writeDebugString("Search finished...");
				}
			);
		}
		virtual void writeDebugString(const std::string& text) noexcept override
		{
			if (this->front().isUCI())
			{
				std::stringstream str;
				str << "info string ";
				str << text;
				str << std::endl;
				this->writeOutput(str.str());
			}
			else
				this->writeOutput(text);
		}
		void doMove(const movebitsType& movebits) noexcept
		{
			this->currentGame().playerClock(this->position().movingPlayer()).set(this->currentGame().playerClock(this->position().movingPlayer()).timeRemaining() + std::chrono::duration_cast<durationType>(this->currentGame().incrementTime(this->position().movingPlayer())));
			this->makeMove(movebits);
		}
		void undoMove() noexcept
		{
			this->unmakeMove();
		}
		virtual bool handleOptions(const std::string& token, const std::string& remainder) noexcept
		{
			std::string remainder2;
			std::string remainder3;
			std::string token2;
			parser::parseToken(remainder, token2, remainder2);
			if (token2 == "name")
			{
				remainder3 = remainder2;
				parser::parseToken(remainder3, token2, remainder2);
				if (token2 == "ponder")
				{
					remainder3 = remainder2;
					parser::parseToken(remainder3, token2, remainder2);
					if (token2 == "value")
					{
						remainder3 = remainder2;
						parser::parseToken(remainder3, token2, remainder2);
						if (token2 == "true" || token2 == "1")
							m_PonderEnabled = true;
						else
							m_PonderEnabled = false;
						return true;
					}
				}
				else if (token2 == "hash")
				{
					remainder3 = remainder2;
					parser::parseToken(remainder3, token2, remainder2);
					if (token2 == "value")
					{
						remainder3 = remainder2;
						parser::parseToken(remainder3, token2, remainder2);
						const size_t sizeInMB{ static_cast<size_t>(parser::parseInt(token2)) };
						const size_t sizeInBytes{ sizeInMB * 1024 * 1024 };
						this->resizeHashTables(sizeInBytes);
						return true;
					}
				}
				else
				{
#if defined(PYGMALION_TUNE)&&(PYGMALION_TUNE==1)
					for (size_t idx = 0; idx < evaluatorType::getParameterCount(); idx++)
					{
						parameter par{ evaluatorType::getParameter(idx) };
						if (parser::toLower(par.name()) == token2)
						{
							remainder3 = remainder2;
							parser::parseToken(remainder3, token2, remainder2);
							if (token2 == "value")
							{
								remainder3 = remainder2;
								parser::parseToken(remainder3, token2, remainder2);
								const int value{ static_cast<int>(parser::parseInt(token2)) };
								const double dValue{ static_cast<double>(value) * par.delta() };
								evaluatorType::setParameter(idx, dValue);
								this->heuristics().transpositionTable().clear();
								return true;
							}
							break;
						}
					}
#endif

				}
			}
			return false;
		}
	};
}