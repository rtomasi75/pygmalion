namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugSetPlayer :
		public pygmalion::state::command<DESCRIPTION_STATE, BOARD>
	{
	public:
		using boardType = BOARD;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-setplayer")
			{
				std::string remainder2;
				parser::parseToken(remainder, token, remainder2);
				playerType player;
				size_t len;
				if (boardType::parsePlayer(token, player, len))
				{
					this->output() << std::endl;
					this->output() << "set moving player to " << boardType::playerToString(player) << "." << std::endl;
					this->position().setMovingPlayer(player);
					this->output() << std::endl;
				}
				else
				{
					this->output() << std::endl;
					this->output() << "invalid player: " << token << std::endl;
					this->output() << std::endl;
				}
				return true;
			}
			else
				return false;
		}
	};

}