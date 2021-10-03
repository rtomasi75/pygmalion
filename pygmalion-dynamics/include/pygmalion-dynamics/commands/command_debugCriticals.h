namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugCriticals :
		public pygmalion::dynamics::command<DESCRIPTION_DYNAMICS, GENERATOR>
	{
	public:
		using generatorType = GENERATOR;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
#include "../include_dynamics.h"
		using movegenFeedback = typename generatorType::movegenFeedback;
	private:
		template<size_t PLAYER>
		bool verify(const stackType<PLAYER>& stack, const size_t depth, const size_t maxDepth, movegenFeedback& feedback) noexcept
		{
			constexpr const playerType nextPlayer{ static_cast<playerType>(PLAYER).next() };
			movebitsType moveBits;
			std::uintmax_t counterMoves{ 0 };
			std::uintmax_t counterCriticalMoves{ 0 };
			bool bOk{ true };
			movelistType criticalMoves;
			movelistType moves;
			if (depth == maxDepth)
			{
				while (stack.nextMove(moveBits, depth, feedback))
				{
					if (generatorType::template isMoveCritical<PLAYER, stackType<PLAYER>>(stack, moveBits))
					{
						counterMoves++;
						moves.add(moveBits);
					}
				}
				while (stack.nextCriticalMove(moveBits, depth, feedback))
				{
					counterCriticalMoves++;
					criticalMoves.add(moveBits);
				}
				bOk &= counterMoves == counterCriticalMoves;
				if (criticalMoves.length() > moves.length())
				{
					for (indexType i = 0; i < criticalMoves.length(); i++)
					{
						if (!moves.contains(criticalMoves[i]))
						{
							this->output() << generatorType::moveToString(stack, criticalMoves[i], this->history().length() + depth) << " missing in moves" << std::endl;
						}
					}
				}
				if (criticalMoves.length() < moves.length())
				{
					for (indexType i = 0; i < moves.length(); i++)
					{
						if (!criticalMoves.contains(moves[i]))
						{
							this->output() << generatorType::moveToString(stack, moves[i], this->history().length() + depth) << " missing in criticals" << std::endl;
						}
					}
				}
				for (indexType i = 0; i < criticalMoves.length(); i++)
				{
					bool bBreak{ false };
					for (indexType j = 0; j < criticalMoves.length(); j++)
					{
						if (i != j)
						{
							if (criticalMoves[i] == criticalMoves[j])
							{
								bOk = false;
								this->output() << generatorType::moveToString(stack, criticalMoves[i], this->history().length() + depth) << " twice in criticals" << std::endl;
								bBreak = true;
								break;
							}
						}
					}
					if (bBreak)
						break;
				}
				for (indexType i = 0; i < moves.length(); i++)
				{
					bool bBreak{ false };
					for (indexType j = 0; j < moves.length(); j++)
					{
						if (i != j)
						{
							if (moves[i] == moves[j])
							{
								bOk = false;
								this->output() << generatorType::moveToString(stack, moves[i], this->history().length() + depth) << " twice in moves" << std::endl;
								bBreak = true;
								break;
							}
						}
					}
					if (bBreak)
						break;
				}
			}
			else
			{
				while (stack.nextMove(moveBits, depth, feedback))
				{
					if (generatorType::template isMoveCritical<PLAYER, stackType<PLAYER>>(stack, moveBits))
					{
						counterMoves++;
						moves.add(moveBits);
					}
					{
						const stackType<static_cast<size_t>(nextPlayer)> substack{ stackType<static_cast<size_t>(nextPlayer)>(stack,moveBits) };
						bOk &= this->template verify<static_cast<size_t>(nextPlayer)>(substack, depth + 1, maxDepth, feedback);
					}
					if (!bOk)
					{
						this->output() << " " << generatorType::moveToString(stack, moveBits, this->history().length() + depth);
						break;
					}
				}
				while (stack.nextCriticalMove(moveBits, depth, feedback))
				{
					counterCriticalMoves++;
					criticalMoves.add(moveBits);
				}
				if (bOk)
				{
					bOk &= counterMoves == counterCriticalMoves;
					if (criticalMoves.length() > moves.length())
					{
						for (indexType i = 0; i < criticalMoves.length(); i++)
						{
							if (!moves.contains(criticalMoves[i]))
							{
								this->output() << generatorType::moveToString(stack, criticalMoves[i], this->history().length() + depth) << " missing in moves" << std::endl;
							}
						}
					}
					if (criticalMoves.length() < moves.length())
					{
						for (indexType i = 0; i < moves.length(); i++)
						{
							if (!criticalMoves.contains(moves[i]))
							{
								this->output() << generatorType::moveToString(stack, moves[i], this->history().length() + depth) << " missing in criticals" << std::endl;
							}
						}
					}
					for (indexType i = 0; i < criticalMoves.length(); i++)
					{
						bool bBreak{ false };
						for (indexType j = 0; j < criticalMoves.length(); j++)
						{
							if (i != j)
							{
								if (criticalMoves[i] == criticalMoves[j])
								{
									bOk = false;
									this->output() << generatorType::moveToString(stack, criticalMoves[i], this->history().length() + depth) << " twice in criticals" << std::endl;
									bBreak = true;
									break;
								}
							}
						}
						if (bBreak)
							break;
					}
					for (indexType i = 0; i < moves.length(); i++)
					{
						bool bBreak{ false };
						for (indexType j = 0; j < moves.length(); j++)
						{
							if (i != j)
							{
								if (moves[i] == moves[j])
								{
									bOk = false;
									this->output() << generatorType::moveToString(stack, moves[i], this->history().length() + depth) << " twice in moves" << std::endl;
									bBreak = true;
									break;
								}
							}
						}
						if (bBreak)
							break;
					}
				}
			}
			return bOk;
		}
		template<size_t PLAYER>
		void process(const size_t depth) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					profiler p;
					for (size_t i = 0; i < depth; i++)
					{
						p.start();
						typename generatorType::contextType context;
						stackType<PLAYER> stack{ stackType<PLAYER>(this->position(),this->history(),&context) };
						const bool bOk{ this->template verify<PLAYER>(stack,0, i, this->feedback()) };
						p.stop();
						this->output() << std::endl << "depth: " << std::setw(2) << static_cast<int>(i + 1) << " verification: " << (bOk ? "OK" : "ERROR") << " time: " << parser::durationToString(p.duration()) << std::endl;
					}
				}
				else
					this->template process<PLAYER + 1>(depth);
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-criticals")
			{
				size_t depth{ static_cast<size_t>(parser::parseInt(remainder)) };
				this->output() << std::endl;
				this->template process<0>(depth);
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-CRITICALS";
		}
	};

}