namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugFile :
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
			if (token == "debug-file")
			{
				this->output() << std::endl;
				std::string remainder2;
				fileType file;
				parser::parseTokenCaseSensitive(remainder, token, remainder2);
				if (boardType::parseFile(token, file))
				{
					this->output() << "file " << boardType::fileToString(file) << std::endl;
					this->dumpSquares(static_cast<squaresType>(file));
				}
				else
					this->output() << "invalid file: " << token;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
	};

}