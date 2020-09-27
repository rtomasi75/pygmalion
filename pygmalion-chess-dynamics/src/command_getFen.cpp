#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_getFen::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "get-fen")
		{
			this->output() << std::endl;
			std::string error;
			this->output() << this->position().getFen() << std::endl;
			this->output() << std::endl;
			return true;
		}
		else
			return false;
	}
}