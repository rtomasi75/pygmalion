namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugSetFlag :
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
			if (token == "debug-setflag")
			{
				std::string remainder2;
				parser::parseToken(remainder, token, remainder2);
				flagType flag;
				size_t len;
				if (boardType::parseFlag(token, flag, len))
				{
					this->output() << std::endl;
					this->output() << "setting " << boardType::flagToString(flag) << " flag." << std::endl;
					this->position().setFlag(flag);
					this->output() << std::endl;
				}
				else
				{
					this->output() << std::endl;
					this->output() << "invalid flag: " << token << std::endl;
					this->output() << std::endl;
				}
				return true;
			}
			else
				return false;
		}
	};

}