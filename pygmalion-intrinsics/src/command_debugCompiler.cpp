#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{
	bool command_debugCompiler::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-compiler")
		{
			output() << std::endl;
			output() << compiler::flags() << std::endl;
			output() << std::endl;
			return true;
		}
		else
			return false;
	}

	std::string command_debugCompiler::help() noexcept
	{
		return "DEBUG-COMPILER";
	}
}