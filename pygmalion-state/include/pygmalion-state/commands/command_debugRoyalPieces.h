namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugRoyalPieces :
		public pygmalion::state::command<DESCRIPTION_STATE, BOARD>
	{
	public:
		using boardType = BOARD;
		using descriptorState = DESCRIPTION_STATE;
#include "../include_state.h"	
		using materialTableType = state::materialTables<descriptorState, boardType>;
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-royalpieces")
			{
				this->output() << std::endl;
				this->output() << "Royal pieces:";
				if (countRoyalPieces > 0)
				{
					for (const auto rp : royalpieceType::range)
					{
						this->output() << " " << rp.toShortString();
					}
				}
				else
					this->output() << " (no royal pieces)";
				this->output() << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-ROYALPIECES";
		}
	};

}