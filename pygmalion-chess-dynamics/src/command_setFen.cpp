#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_setFen::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "set-fen")
		{
			this->output() << std::endl;
			std::string error;
			if (this->position().setFen(remainder,error))
			{
				this->output() << "New position: " << this->position().getFen() << std::endl;
			}
			else
			{
				this->output() << error << std::endl;
			}
			this->output() << std::endl;
			return true;
		}
		else
			return false;
	}
}