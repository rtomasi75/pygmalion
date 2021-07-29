#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{
	bool command_help::onProcess(const std::string& cmd) noexcept
	{
		if (cmd == "help")
		{
			intrinsicsEngine().outputStream() << "Available commands:" << std::endl;
			for (auto& C : intrinsicsEngine().m_Commands)
			{
				intrinsicsEngine().outputStream() << "  " << C->help() << std::endl;
			}
			return true;
		}
		else
			return false;
	}

	std::string command_help::help() noexcept
	{
		return "HELP";
	}
}