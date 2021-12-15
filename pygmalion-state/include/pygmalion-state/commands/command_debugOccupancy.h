namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugOccupancy :
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
			if (token == "debug-occupancy")
			{
				this->output() << std::endl;
				std::string remainder2;
				parser::parseToken(remainder, token, remainder2);
				if (token == "p" || token == "player")
				{
					std::string remainder3;
					parser::parseTokenCaseSensitive(remainder2, token, remainder3);
					playerType p;
					size_t count{ 0 };
					if (playerType::parse(token, count, p))
					{

						this->output() << "occupancy bitboard for " << p.toLongString() << ":" << std::endl;
						this->dumpSquares(this->position().playerOccupancy(p));
					}
					else
						this->output() << "invalid player: " << token << std::endl;
				}
				else if (token == "ppc" || token == "playerpiece")
				{
					std::string remainder3;
					parser::parseTokenCaseSensitive(remainder2, token, remainder3);
					playerpieceType ppc;
					size_t count{ 0 };
					if (playerpieceType::parse(token, count, ppc))
					{

						this->output() << "occupancy bitboard for " << ppc.toLongString() << ":" << std::endl;
						this->dumpSquares(this->position().pieceOccupancy(ppc.piece()) & this->position().playerOccupancy(ppc.player()));
					}
					else
						this->output() << "invalid player/piece: " << token << std::endl;
				}
				else if (token == "pc" || token == "piece")
				{
					std::string remainder3;
					parser::parseTokenCaseSensitive(remainder2, token, remainder3);
					pieceType pc;
					size_t count{ 0 };
					if (pieceType::parse(token, count, pc))
					{

						this->output() << "occupancy bitboard for " << pc.toLongString() << ":" << std::endl;
						this->dumpSquares(this->position().pieceOccupancy(pc));
					}
					else
						this->output() << "invalid player: " << token << std::endl;
				}
				else if (token == "t" || token == "total")
				{
					this->output() << "total occupancy bitboard:" << std::endl;
					this->dumpSquares(this->position().totalOccupancy());
				}
				else
				{
					this->output() << "need to specify one of the follwoing:" << std::endl;
					this->output() << "  p (player)" << std::endl;
					this->output() << "  pc (piece)" << std::endl;
					this->output() << "  ppc (playerpiece)" << std::endl;
					this->output() << "  t (total)" << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-OCCUPANCY";
		}
	};
}