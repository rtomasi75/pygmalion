namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_go :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	private:
		template<size_t PLAYER>
		void process() noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
					this->frontendEngine().template searchMoveLimited<PLAYER>();
				else
					this->template process<PLAYER + 1>();
			}
			else
				PYGMALION_ASSERT(false);
		}
		template<size_t PLAYER>
		void processAnalyze() noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
					this->frontendEngine().template searchMoveUnlimited<PLAYER>();
				else
					this->template processAnalyze<PLAYER + 1>();
			}
			else
				PYGMALION_ASSERT(false);
		}
		template<size_t PLAYER>
		void ponder() noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					this->frontendEngine().template searchMoveUnlimited<PLAYER>();
				}
				else
					this->template ponder<PLAYER + 1>();
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (this->front().isUCI())
			{
				std::string commandToken;
				std::string remainder;
				parser::parseToken(cmd, commandToken, remainder);
				std::array<durationType, countPlayers> increment{ arrayhelper::make<countPlayers>(durationType(0)) };
				std::array<durationType, countPlayers> time{ arrayhelper::make<countPlayers>(durationType(0)) };
				size_t movestogo{ 0 };
				depthType mate{ depthType(-1) };
				depthType depthLimit{ depthType(-1) };
				std::uintmax_t nodes{ 0 };
				movelistType moves{ movelistType() };
				bool bInfinite{ true };
				bool bPonder{ false };
				bool bMoveTime{ false };
				durationType movetime{ durationType(0) };
				if (commandToken == "go")
				{
					while (remainder != "")
					{
						std::string token;
						std::string remainder2;
						parser::parseToken(remainder, token, remainder2);
						if (token == "infinite")
						{
							bInfinite = true;
							remainder = remainder2;
						}
						else if (token == "ponder")
						{
							bPonder = true;
							remainder = remainder2;
						}
						else if (token == "movetime")
						{
							std::string timeToken;
							parser::parseToken(remainder2, timeToken, remainder);
							std::int64_t parsedMilliseconds{ parser::parseInt(timeToken) };
							movetime = std::chrono::duration_cast<durationType>(std::chrono::milliseconds(parsedMilliseconds));
							bMoveTime = true;
						}
						else if (token == "wtime")
						{
							std::string timeToken;
							parser::parseToken(remainder2, timeToken, remainder);
							std::int64_t parsedMilliseconds{ parser::parseInt(timeToken) };
							time[0] = std::chrono::duration_cast<durationType>(std::chrono::milliseconds(parsedMilliseconds));
							bInfinite = false;
						}
						else if (token == "btime")
						{
							std::string timeToken;
							parser::parseToken(remainder2, timeToken, remainder);
							std::int64_t parsedMilliseconds{ parser::parseInt(timeToken) };
							time[1] = std::chrono::duration_cast<durationType>(std::chrono::milliseconds(parsedMilliseconds));
							bInfinite = false;
						}
						else if (token == "winc")
						{
							std::string timeToken;
							parser::parseToken(remainder2, timeToken, remainder);
							std::int64_t parsedMilliseconds{ parser::parseInt(timeToken) };
							increment[0] = std::chrono::duration_cast<durationType>(std::chrono::milliseconds(parsedMilliseconds));
						}
						else if (token == "binc")
						{
							std::string timeToken;
							parser::parseToken(remainder2, timeToken, remainder);
							std::int64_t parsedMilliseconds{ parser::parseInt(timeToken) };
							increment[1] = std::chrono::duration_cast<durationType>(std::chrono::milliseconds(parsedMilliseconds));
						}
						else if (token == "movestogo")
						{
							std::string movesToken;
							parser::parseToken(remainder2, movesToken, remainder);
							std::int64_t parsedMovesToGo{ parser::parseInt(movesToken) };
							movestogo = static_cast<size_t>(parsedMovesToGo);
						}
						else if (token == "depth")
						{
							std::string movesToken;
							parser::parseToken(remainder2, movesToken, remainder);
							std::int64_t parsedDepth{ parser::parseInt(movesToken) };
							depthLimit = static_cast<depthType>(parsedDepth);
						}
						else if (token == "mate")
						{
							std::string movesToken;
							parser::parseToken(remainder2, movesToken, remainder);
							std::int64_t parsedMovesToMate{ parser::parseInt(movesToken) };
							mate = static_cast<depthType>(parsedMovesToMate);
						}
						else if (token == "nodes")
						{
							std::string movesToken;
							parser::parseToken(remainder2, movesToken, remainder);
							std::int64_t parsedNodes{ parser::parseInt(movesToken) };
							nodes = static_cast<std::uintmax_t>(parsedNodes);
						}
						else if (token == "searchmoves")
						{
							remainder = remainder2;
							while (remainder != "")
							{
								std::string movesToken;
								parser::parseTokenCaseSensitive(remainder, movesToken, remainder2);
								movebitsType movebits;
								size_t count{ 0 };
								if (motorType::parseMove(this->position(), movesToken, movebits, count))
									moves.add(movebits);
								else
									break;
								remainder = remainder2;
							}
						}
						else
						{
							this->output() << "info string Invalid token: \"" << token << "\"" << std::endl;
							return false;
						}
					}
					if (bMoveTime)
					{
						this->front().setTimeLimit(movetime);
					}
					if (depthLimit > -1)
					{
						this->front().setDepthLimit(depthLimit - 1);
					}
					if (bInfinite)
					{
						if (bPonder)
						{
							this->template ponder<0>();
						}
						else
							this->template processAnalyze<0>();
					}
					else
					{
						this->frontendEngine().currentGame().setTimeControl(movestogo, time, increment);
						for (const auto pl : playerType::range)
						{
							this->searchEngine().currentGame().playerClock(pl).set(time[pl]);
						}
						if (bPonder)
							this->template ponder<0>();
						else
							this->template process<0>();
					}
					return true;
				}
				else
					return false;
			}
			return false;
		}
		virtual std::string help() noexcept override
		{
			return "GO";
		}
	};

}