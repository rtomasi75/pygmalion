#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_debugCheck::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-check")
		{
			std::string remainder2;
			parser::parseTokenCaseSensitive(remainder, token, remainder2);
			this->output() << std::endl;
			stackType stack(this->position(), this->history(), this->position().movingPlayer().next());
			if (stack.isCheck())
			{
				movebitsType moveBits;
				if (stack.nextMove(moveBits, 0, this->feedback()))
					this->output() << "Check." << std::endl;
				else
					this->output() << "Checkmate." << std::endl;
			}
			else
				this->output() << "Not in check." << std::endl;
			this->output() << std::endl;
			return true;
		}
		else
			return false;
	}
}