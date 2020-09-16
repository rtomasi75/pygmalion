namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugFlags :
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
			if (token == "debug-flags")
			{
				this->output() << std::endl;
				this->output() << countFlags << " flag" << (countFlags != 1 ? "s" : "") << ":";
				for (const auto flag : flagType::range)
					this->output() << " "<< boardType::flagToString(flag);
				this->output() << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
	};

}