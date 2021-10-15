#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_debugTropism::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-tropism")
		{
			std::string remainder2;
			parser::parseTokenCaseSensitive(remainder, token, remainder2);
			playerType pl;
			this->output() << std::endl;
			size_t count{ 0 };
			if (boardType::parsePlayer(token, pl, count))
			{
				parser::parseTokenCaseSensitive(remainder2, token, remainder);
				squareType sq;
				count = 0;
				if (boardType::parseSquare(token, sq, count))
				{
					parser::parseTokenCaseSensitive(remainder, token, remainder2);
					pieceType pc;
					playerType dummy;
					count = 0;
					if (boardType::parsePiece(token, pc, dummy, count))
						this->template process<0>(pl, sq, pc);
					else
						this->output() << "invalid piece: " << token << std::endl;
				}
				else
					this->output() << "invalid square: " << token << std::endl;
			}
			else
				this->output() << "invalid player: " << token << std::endl;
			this->output() << std::endl;
			return true;
		}
		else
			return false;
	}
}