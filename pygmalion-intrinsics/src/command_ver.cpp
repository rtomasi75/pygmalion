#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{
	bool command_ver::onProcess(engine& eng, const std::string& cmd) const noexcept
	{
		if (cmd == "ver")
		{
			eng.outputStream() << "Pygmalion ver. 3.0" << std::endl;
			eng.outputStream() << "playing " << eng.version() << std::endl;
			return true;
		}
		else
			return false;
	}
}