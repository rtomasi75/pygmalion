namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugCriticals :
		public pygmalion::dynamics::command<DESCRIPTION_DYNAMICS, GENERATOR>
	{
	public:
		using generatorType = GENERATOR;
		using stackType = typename generatorType::stackType;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
		using movegenFeedback = typename generatorType::movegenFeedback;
#include "../include_dynamics.h"
	private:
		bool verify(const stackType& stack, const size_t depth, const size_t maxDepth, movegenFeedback& feedback) noexcept
		{
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
					if (generatorType::isMoveCritical(stack, moveBits))
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
			}
			else
			{
				while (stack.nextMove(moveBits, depth, feedback))
				{
					if (generatorType::isMoveCritical(stack, moveBits))
					{
						counterMoves++;
						moves.add(moveBits);
					}
					{
						const stackType substack{ stackType(stack,moveBits) };
						bOk &= verify(substack, depth + 1, maxDepth, feedback);
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
				}
			}
			return bOk;
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
				profiler p;
				this->output() << std::endl;
				for (size_t i = 0; i < depth; i++)
				{
					p.start();
					stackType stack{ stackType(this->position(),this->history(), this->position().movingPlayer()) };
					const bool bOk{ verify(stack,0, i, this->feedback()) };
					p.stop();
					this->output() << std::endl << "depth: " << std::setw(2) << static_cast<int>(i + 1) << " verification: " << (bOk ? "OK" : "ERROR") << " time: " << parser::durationToString(p.duration()) << std::endl;
				}
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