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
			output() << "CPU features:" << std::endl;
			if constexpr (cpu::supports(cpu::X86))
				output() << "  X86" << std::endl;
			if constexpr (cpu::supports(cpu::X64))
				output() << "  X64" << std::endl;
			if constexpr (cpu::supports(cpu::BMI2))
				output() << "  BMI2" << std::endl;
			output() << std::endl;
			return true;
		}
		else
			return false;
	}
}