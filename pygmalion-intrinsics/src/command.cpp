#include <pygmalion-intrinsics.h>

namespace pygmalion
{
	bool command::onProcess(pygmalion::intrinsics::engine& eng, const std::string& cmd) const noexcept
	{
		return false;
	}

	bool command::process(pygmalion::intrinsics::engine& eng, const std::string& cmd) const noexcept
	{
		return onProcess(eng, cmd);
	}

}