namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugRemovePiece :
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
			if (token == "debug-removepiece")
			{
				this->output() << std::endl;
				std::string remainder2;
				squareType sq;
				parser::parseTokenCaseSensitive(remainder, token, remainder2);
				size_t count{ 0 };
				if (squareType::parse(token, count, sq))
				{
					if (!this->position().totalOccupancy()[sq])
						this->output() << "there is no piece on " << sq.toShortString() << "." << std::endl;
					else
					{
						const pieceType pc{ this->position().getPiece(sq) };
						const playerType p{ this->position().getPlayer(sq) };
						this->output() << "removing " << (pc & p).toLongString() << " from " << sq.toShortString() << "." << std::endl;
						this->position().removePiece(pc, sq, p, this->stateEngine().materialTable());
					}
				}
				else
					this->output() << "invalid square: " << token;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-REMOVEPIECE";
		}
	};

}