namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugPerft :
		public pygmalion::dynamics::command<DESCRIPTION_DYNAMICS, GENERATOR>
	{
	public:
		using generatorType = GENERATOR;
		using stackType = typename generatorType::stackType;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
		using movegenFeedback = typename generatorType::movegenFeedback;
#include "../include_dynamics.h"
	private:
		static std::uintmax_t perft(const stackType& stack, const size_t depth, const size_t maxDepth, movegenFeedback& feedback) noexcept
		{
			movebitsType moveBits;
			std::uintmax_t counter{ 0 };
			if (depth == maxDepth)
			{
				while (stack.nextMove(moveBits, depth, feedback))
				{
					counter++;
				}
			}
			else
			{
				while (stack.nextMove(moveBits, depth, feedback))
				{
					const stackType substack{ stackType(stack,moveBits) };
					counter += perft(substack, depth + 1, maxDepth, feedback);
				}
			}
			return counter;
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-perft")
			{
				size_t depth{ static_cast<size_t>(parser::parseInt(remainder)) };
				profiler p;
				this->output() << std::endl;
				for (size_t i = 0; i < depth; i++)
				{
					p.start();
					stackType stack{ stackType(this->position(),this->history(), this->position().movingPlayer()) };
					const std::uintmax_t nodes{ perft(stack,this->history().length(), i, this->feedback()) };
					p.stop();
					this->output() << "depth: " << std::setw(2) << static_cast<int>(i + 1) << " nodes: " << parser::valueToString(static_cast<double>(nodes), "N") << " time: " << parser::durationToString(p.duration()) << " speed: " << p.computeSpeed(nodes, "N") << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-PERFT";
		}
	};

}