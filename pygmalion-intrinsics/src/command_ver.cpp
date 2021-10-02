#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{
	bool command_ver::onProcess(const std::string& cmd) noexcept
	{
		if (cmd == "ver")
		{
			output() << std::endl;
			output() << intrinsicsEngine().version() << std::endl;
			output() << std::endl;
			return true;
		}
		else
			return false;
	}

	std::string command_ver::help() noexcept
	{
		return "VER";
	}
}