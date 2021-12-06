namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugCaptureTargets :
		public pygmalion::dynamics::command<DESCRIPTION_DYNAMICS, GENERATOR>
	{
	public:
		using generatorType = GENERATOR;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
#include "../include_dynamics.h"	
	private:
		template<size_t PLAYER>
		void process(const playerType pl, const pieceType pc, const squareType sq) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == pl)
				{
					this->dumpSquares(generatorType::captureTargets(player, pc, sq));
				}
				else
					this->template process<PLAYER + 1>(pl, pc, sq);
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-capturetargets")
			{
				this->output() << std::endl;
				for (const auto pc : pieceType::range)
				{
					for (const auto pl : playerType::range)
					{
						for (const auto sq : squareType::range)
						{
							this->output() << boardType::pieceToString(pc, pl) << boardType::squareToString(sq) << std::endl;
							this->template process<0>(pl, pc, sq);
						}
					}
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-CAPTURETARGETS";
		}
	};

}