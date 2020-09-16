#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{
	bool command_quit::onProcess(engine& eng, const std::string& cmd) const noexcept
	{
		if (cmd == "quit")
		{
			eng.stop();
			return true;
		}
		else
			return false;
	}
}