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
			size_t count{ 0 };
			if (squareType::parse(token, count, sq))
			{
				this->output() << "king area for " << sq.toShortString() << ": " << token << std::endl;
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