#include <pygmalion-chess-evaluation.h>
namespace pygmalion::chess::evaluation
{
	bool command_debugControl::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-control")
		{
			std::string remainder2;
			parser::parseTokenCaseSensitive(remainder, token, remainder2);
			playerType p;
			this->output() << std::endl;
			if (boardType::parsePlayer(token, p))
			{
				typename generatorType::contextType context;
				stackType stack(this->position(), this->history(), this->position().movingPlayer().next(), &context);
				squaresType controlWhite{ squaresType::none() };
				squaresType controlBlack{ squaresType::none() };
				stack.control(controlWhite, controlBlack);
				if (p == whitePlayer)
				{
					dumpSquares(controlWhite);
				}
				else
				{
					dumpSquares(controlBlack);
				}
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