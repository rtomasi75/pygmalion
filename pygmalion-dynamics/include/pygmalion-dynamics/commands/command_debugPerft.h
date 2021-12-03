namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugPerft :
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
		static std::uintmax_t perft(const stackType<PLAYER>& stack, const size_t depth, const size_t maxDepth, std::uintmax_t& nodes) noexcept
		{
			constexpr const playerType nextPlayer{ static_cast<playerType>(PLAYER).next() };
			movebitsType moveBits;
			std::uintmax_t counter{ 0 };
			if (depth == maxDepth)
			{
				while (stack.nextMove(moveBits))
				{
					counter++;
				}
			}
			else
			{
				while (stack.nextMove(moveBits))
				{
					const stackType<static_cast<size_t>(nextPlayer)> substack{ stackType<static_cast<size_t>(nextPlayer)>(stack,moveBits) };
					counter += perft(substack, depth + 1, maxDepth, nodes);
				}
			}
			nodes++;
			return counter;
		}
		template<size_t PLAYER>
		void process(const size_t depth) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					typename generatorType::contextType* pContext = new typename generatorType::contextType[depth + 1];
					profiler p;
					for (size_t i = 0; i < depth; i++)
					{
						p.start();
						stackType<PLAYER> stack{ stackType<PLAYER>(this->position(),this->history(), pContext) };
						std::uintmax_t nodes{ 0 };
						const std::uintmax_t leafs{ this->template perft<PLAYER>(stack,0, i, nodes) };
						p.stop();
						this->output() << "depth: " << std::setw(2) << static_cast<int>(i + 1) << " leafs: " << parser::valueToString(static_cast<double>(leafs), "") << " nodes: " << parser::valueToString(static_cast<double>(nodes), "") << " time: " << parser::durationToString(p.duration()) << " speed: " << p.computeSpeed(nodes, "N") << ", " << p.computeSpeed(leafs + nodes, "mv") << std::endl;
						this->flushOutput();
					}
					delete[] pContext;
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
			if (token == "debug-perft")
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
			return "DEBUG-PERFT";
		}
	};

}