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
		static std::uintmax_t perft(const stackType& stack, const size_t depth, const size_t maxDepth, movegenFeedback& feedback, std::uintmax_t& nodes) noexcept
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
					counter += perft(substack, depth + 1, maxDepth, feedback, nodes);
				}
			}
			nodes++;
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
				typename generatorType::contextType* pContext = new typename generatorType::contextType[depth + 1];
				for (size_t i = 0; i < depth; i++)
				{
					p.start();
					stackType stack{ stackType(this->position(),this->history(), this->position().movingPlayer(), pContext) };
					std::uintmax_t nodes{ 0 };
					const std::uintmax_t leafs{ perft(stack,0, i, this->feedback(), nodes) };
					p.stop();
					this->output() << "depth: " << std::setw(2) << static_cast<int>(i + 1) << " leafs: " << parser::valueToString(static_cast<double>(leafs), "") << " nodes: " << parser::valueToString(static_cast<double>(nodes), "") << " time: " << parser::durationToString(p.duration()) << " speed: " << p.computeSpeed(nodes, "N") << ", " << p.computeSpeed(leafs+nodes, "mv") << std::endl;
				}
				delete[] pContext;
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