namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugRanks :
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
			if (token == "debug-ranks")
			{
				this->output() << std::endl;
				this->output() << countRanks << " rank" << (countRanks != 1 ? "s" : "") << ":";
				for (const auto rank : rankType::range)
					this->output() << " " << boardType::rankToString(rank);
				this->output() << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-RANKS";
		}
	};

}