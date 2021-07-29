namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugNextPlayer :
		public pygmalion::state::command<DESCRIPTION_STATE, BOARD>
	{
	public:
		using boardType = BOARD;
		using descriptorState = DESCRIPTION_STATE;
#include "../include_state.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-nextplayer")
			{
				playerType next{ this->position().movingPlayer() };
				++next;
				this->output() << std::endl;
				this->output() << "advance moving player to " << boardType::playerToString(next) << "." << std::endl;
				this->position().setMovingPlayer(next);
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-NEXTPLAYER";
		}
	};
}