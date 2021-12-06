namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugPromoCaptureOrigins :
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
		void process(const playerType pl, const pieceType pc) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == pl)
				{
					this->dumpSquares(generatorType::promoCaptureOrigins(player, pc));
				}
				else
					this->template process<PLAYER + 1>(pl, pc);
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-promocaptureorigins")
			{
				this->output() << std::endl;
				for (const auto pc : pieceType::range)
				{
					for (const auto pl : playerType::range)
					{
						this->output() << boardType::pieceToString(pc, pl) << std::endl;
						this->template process<0>(pl, pc);
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
			return "DEBUG-PROMOCAPTUREORIGINS";
		}
	};

}