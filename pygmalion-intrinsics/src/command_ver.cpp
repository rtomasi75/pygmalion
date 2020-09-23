#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{
	bool command_ver::onProcess(const std::string& cmd) noexcept
	{
		if (cmd == "ver")
		{
			output() << std::endl;
			output() << "Pygmalion ver. 3.0" << std::endl;
			output() << "playing " << intrinsicsEngine().version() << std::endl;
			output() << std::endl;
			return true;
		}
		else
			return false;
	}
}