#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_debugKingArea::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-kingarea")
		{
			std::string remainder2;
			parser::parseToken(remainder, token, remainder2);
			squareType sq;
			this->output() << std::endl;
			if (boardType::parseSquare(token, sq))
			{
				this->output() << "king area for " << boardType::squareToString(sq) << ": " << token << std::endl;
				this->dumpSquares(generatorType::kingArea(sq));
			}
			else
				this->output() << "invalid square: " << token << std::endl;
			this->output() << std::endl;
			return true;
		}
		else
			return false;
	}
}