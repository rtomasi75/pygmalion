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
#include "../include_dynamics.h"
	private:
		static void perft(const stackType& stack, std::uintmax_t& counter, const size_t depth, const size_t maxDepth) noexcept
		{
			if (depth == maxDepth)
				return;
			movebitsType moveBits;
			while (stack.nextMove(moveBits))
			{
				counter++;
				const stackType substack{ stackType(stack,moveBits) };
				perft(substack, counter, depth + 1, maxDepth);
			}
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
				std::uintmax_t nodes;
				this->output() << std::endl;
				for (size_t i = 0; i < depth; i++)
				{
					nodes = 0;
					p.start();
					stackType stack{ stackType(this->position(), this->position().movingPlayer()) };
					perft(stack, nodes, 0, i + 1);
					p.stop();
					this->output() << "depth: " << std::setw(2) << static_cast<int>(i + 1) << " nodes: " << parser::valueToString(static_cast<double>(nodes), "n") << " time: " << parser::durationToString(p.duration()) << " speed: " << p.computeSpeed(nodes, "n") << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
	};

}