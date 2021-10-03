#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_debugAttacked::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-attacked")
		{
			std::string remainder2;
			parser::parseTokenCaseSensitive(remainder, token, remainder2);
			playerType p;
			if (boardType::parsePlayer(token, p))
			{
				this->output() << std::endl;
				this->template process<0>(p);
				this->output() << std::endl;
			}
			else
				this->output() << "invalid player: " << token << std::endl;
			return true;
		}
		else
			return false;
	}
}

