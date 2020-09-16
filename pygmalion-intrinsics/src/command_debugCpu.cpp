#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{
	bool command_debugCpu::onProcess(engine& eng, const std::string& cmd) const noexcept 
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-cpu")
		{
			eng.outputStream() << std::endl;
			eng.outputStream() << "CPU features:" << std::endl;
			if constexpr (cpu::supports(cpu::X86))
				eng.outputStream() << "  X86" << std::endl;
			if constexpr (cpu::supports(cpu::X64))
				eng.outputStream() << "  X64" << std::endl;
			if constexpr (cpu::supports(cpu::BMI2))
				eng.outputStream() << "  BMI2" << std::endl;
			eng.outputStream() << std::endl;
			return true;
		}
		else
			return false;
	}
}