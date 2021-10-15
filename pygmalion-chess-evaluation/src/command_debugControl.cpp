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
			size_t count{ 0 };
			if (boardType::parsePlayer(token, p, count))
			{
				this->template process<0>(p);
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