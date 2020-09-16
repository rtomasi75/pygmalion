namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugFiles :
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
			if (token == "debug-files")
			{
				this->output() << std::endl;
				this->output() << countFiles << " file" << (countFiles != 1 ? "s" : "") << ":";
				for (const auto file : fileType::range)
					this->output() << " "<< boardType::fileToString(file);
				this->output() << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
	};

}