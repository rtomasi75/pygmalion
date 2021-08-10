#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_debugTargeted::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-targeted")
		{
			std::string remainder2;
			parser::parseTokenCaseSensitive(remainder, token, remainder2);
			playerType p;
			this->output() << std::endl;
			if (boardType::parsePlayer(token, p))
			{
				stackType stack(this->position(), this->position().movingPlayer().next());
				if (p == whitePlayer)
				{
					const squaresType attacked{ stack.squaresTargetedByPlayer(whitePlayer) };
					dumpSquares(attacked);
				}
				else
				{
					const squaresType attacked{ stack.squaresTargetedByPlayer(blackPlayer) };
					dumpSquares(attacked);
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