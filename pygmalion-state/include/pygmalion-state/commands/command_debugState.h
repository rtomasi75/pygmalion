namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugState :
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
			if (token == "debug-state")
			{
				this->output() << std::endl;
				this->output() << boardType::name() << std::endl;
				this->output() << std::endl;
				this->output() << "player:     " << std::setw(4) << sizeof(playerType) << " = " << sizeof(playerType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "piece:      " << std::setw(4) << sizeof(pieceType) << " = " << sizeof(pieceType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "rank:       " << std::setw(4) << sizeof(rankType) << " = " << sizeof(rankType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "file:       " << std::setw(4) << sizeof(fileType) << " = " << sizeof(fileType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "square:     " << std::setw(4) << sizeof(squareType) << " = " << sizeof(squareType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "squares:    " << std::setw(4) << sizeof(squaresType) << " = " << sizeof(squaresType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "flag:       " << std::setw(4) << sizeof(flagType) <<" = " << sizeof(flagType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "flags:      " << std::setw(4) << sizeof(flagsType) << " = " << sizeof(flagsType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "gamestate:  " << std::setw(4) << sizeof(gamestateType) << " = " << sizeof(gamestateType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "cumulation: " << std::setw(4) << sizeof(cumulationType) << " = " << sizeof(cumulationType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "board:      " << std::setw(4) << sizeof(boardType) << " = " << sizeof(boardType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "signature:  " << std::setw(4) << sizeof(typename boardType::signatureType) << " = " << sizeof(typename boardType::signatureType) * CHAR_BIT << "bit" << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-STATE";
		}
	};

}