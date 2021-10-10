#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{
	bool command_debugCpu::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-cpu")
		{
			output() << std::endl;
			output() << cpu::flags() << std::endl;
			output() << std::endl;
			return true;
		}
		else
			return false;
	}

	std::string command_debugCpu::help() noexcept
	{
		return "DEBUG-CPU";
	}
}