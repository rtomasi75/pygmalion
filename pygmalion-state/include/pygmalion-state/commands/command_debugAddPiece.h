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
				playerpieceType ppc;
				parser::parseTokenCaseSensitive(remainder, token, remainder2);
				size_t count{ 0 };
				if (playerpieceType::parse(token, count, ppc))
				{
					std::string remainder3;
					squareType sq;
					parser::parseTokenCaseSensitive(remainder2, token, remainder3);
					count = 0;
					if (squareType::parse(token, count, sq))
					{
						if (this->position().totalOccupancy()[sq])
							this->output() << "there already is a piece on " << sq.toShortString() << "." << std::endl;
						else
						{
							this->output() << "adding " << ppc.toLongString() << " on " << sq.toShortString() << "." << std::endl;
							this->position().addPiece(ppc.piece(), sq, ppc.player(), this->stateEngine().materialTable());
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