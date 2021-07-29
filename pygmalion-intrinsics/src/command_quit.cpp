#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{
	bool command_quit::onProcess(const std::string& cmd) noexcept
	{
		if (cmd == "quit")
		{
			intrinsicsEngine().stop();
			return true;
		}
		else
			return false;
	}

	std::string command_quit::help() noexcept
	{
		return "QUIT";
	}
}