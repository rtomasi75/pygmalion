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
			if constexpr (cpu::supports(cpu::MMX))
				output() << "  MMX" << std::endl;
			if constexpr (cpu::supports(cpu::BMI))
				output() << "  BMI" << std::endl;
			if constexpr (cpu::supports(cpu::BMI2))
				output() << "  BMI2" << std::endl;
			if constexpr (cpu::supports(cpu::SSE))
				output() << "  SSE" << std::endl;
			if constexpr (cpu::supports(cpu::SSE2))
				output() << "  SSE2" << std::endl;
			if constexpr (cpu::supports(cpu::SSE3))
				output() << "  SSE3" << std::endl;
			if constexpr (cpu::supports(cpu::SSSE3))
				output() << "  SSSE3" << std::endl;
			if constexpr (cpu::supports(cpu::SSE41))
				output() << "  SSE41" << std::endl;
			if constexpr (cpu::supports(cpu::SSE42))
				output() << "  SSE42" << std::endl;
			if constexpr (cpu::supports(cpu::AVX))
				output() << "  AVX" << std::endl;
			if constexpr (cpu::supports(cpu::AVX2))
				output() << "  AVX2" << std::endl;
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