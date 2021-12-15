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
			playerpieceType ppc;
			this->output() << std::endl;
			size_t count{ 0 };
			if (playerpieceType::parse(token, count, ppc))
			{
				const playerType pl{ ppc.player() };
				const pieceType pc{ ppc.piece() };
				parser::parseTokenCaseSensitive(remainder2, token, remainder);
				squareType sq;
				count = 0;
				if (squareType::parse(token, count, sq))
				{
					parser::parseTokenCaseSensitive(remainder, token, remainder2);
					playerType dummy;
					count = 0;
					this->template process<0>(pl, sq, pc);
				}
				else
					this->output() << "invalid square: " << token << std::endl;
			}
			else
				this->output() << "invalid player/piece: " << token << std::endl;
			this->output() << std::endl;
			return true;
		}
		else
			return false;
	}
}