namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugAddPiece :
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
			if (token == "debug-addpiece")
			{
				this->output() << std::endl;
				std::string remainder2;
				playerType p;
				pieceType pc;
				parser::parseTokenCaseSensitive(remainder, token, remainder2);
				size_t count{ 0 };
				if (boardType::parsePiece(token, pc, p, count))
				{
					std::string remainder3;
					squareType sq;
					parser::parseTokenCaseSensitive(remainder2, token, remainder3);
					count = 0;
					if (boardType::parseSquare(token, sq, count))
					{
						if (this->position().totalOccupancy()[sq])
							this->output() << "there already is a piece on " << boardType::squareToString(sq) << "." << std::endl;
						else
						{
							this->output() << "adding " << boardType::pieceToString(pc, p) << " on " << boardType::squareToString(sq) << "." << std::endl;
							this->position().addPiece(pc, sq, p, this->stateEngine().materialTable());
						}
					}
					else
						this->output() << "invalid square: " << token;
				}
				else
					this->output() << "invalid piece: " << token;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-ADDPIECE";
		}
	};
}