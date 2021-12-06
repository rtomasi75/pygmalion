namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugMaterial :
		public pygmalion::state::command<DESCRIPTION_STATE, BOARD>
	{
	public:
		using boardType = BOARD;
		using descriptorState = DESCRIPTION_STATE;
#include "../include_state.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-material")
			{
				for (const auto pl : playerType::range)
				{
					for (const auto pc : pieceType::range)
					{
						this->output() << boardType::pieceToString(pc, pl) << ":" << std::endl;
						for (size_t r = countRanks; r > 0; r--)
						{
							const rankType rank{ static_cast<rankType>(r - 1) };
							for (const auto file : fileType::range)
							{
								const squareType sq{ rank & file };
								this->output() << "\t";
								this->output() << this->stateEngine().materialTable().materialAbsolute(pl, pc, sq);
							}
							this->output() << std::endl;
						}
						this->output() << std::endl;
					}
				}
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-MATERIAL";
		}
	};
}