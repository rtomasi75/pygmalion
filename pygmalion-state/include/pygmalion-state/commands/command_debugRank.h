namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugRank :
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
			if (token == "debug-rank")
			{
				this->output() << std::endl;
				std::string remainder2;
				rankType rank;
				parser::parseTokenCaseSensitive(remainder, token, remainder2);
				size_t count{ 0 };
				if (boardType::parseRank(token, rank, count))
				{
					this->output() << "rank " << boardType::rankToString(rank) << std::endl;
					this->dumpSquares(static_cast<squaresType>(rank));
				}
				else
					this->output() << "invalid file: " << token;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-RANK";
		}
	};

}