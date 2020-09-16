namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugAddPiece :
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
			if (token == "debug-addpiece")
			{
				this->output() << std::endl;
				size_t len;
				std::string remainder2;
				playerType p;
				parser::parseToken(remainder, token, remainder2);
				if (boardType::parsePlayer(token, p, len))
				{
					std::string remainder3;
					pieceType pc;
					parser::parseToken(remainder2, token, remainder3);
					if (boardType::parsePiece(token, pc, len))
					{
						std::string remainder4;
						squareType sq;
						parser::parseToken(remainder3, token, remainder4);
						if (boardType::parseSquare(token, sq, len))
						{
							if (this->position().totalOccupancy()[sq])
								this->output() << "there already is a piece on " << boardType::squareToString(sq) << "." << std::endl;
							else
							{
								this->output() << "adding " << boardType::pieceToString(pc, p) << " on " << boardType::squareToString(sq) << "." << std::endl;
								this->position().addPiece(pc, sq, p);
							}
						}
						else
							this->output() << "invalid square: " << token;
					}
					else
						this->output() << "invalid piece: " << token;
				}
				else
					this->output() << "invalid player: " << token;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
	};

}