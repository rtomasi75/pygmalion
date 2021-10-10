#include <pygmalion-intrinsics.h>

namespace pygmalion
{
	std::ostream& operator<<(std::ostream& str, const cpu::flags f) noexcept
	{
		str << "CPU features:" << std::endl;
		if constexpr (cpu::supports(cpu::X86))
			str << "  X86" << std::endl;
		if constexpr (cpu::supports(cpu::X64))
			str << "  X64" << std::endl;
		if constexpr (cpu::supports(cpu::MMX))
			str << "  MMX" << std::endl;
		if constexpr (cpu::supports(cpu::POPCNT))
			str << "  POPCNT" << std::endl;
		if constexpr (cpu::supports(cpu::BMI))
			str << "  BMI" << std::endl;
		if constexpr (cpu::supports(cpu::BMI2))
			str << "  BMI2" << std::endl;
		if constexpr (cpu::supports(cpu::SSE))
			str << "  SSE" << std::endl;
		if constexpr (cpu::supports(cpu::SSE2))
			str << "  SSE2" << std::endl;
		if constexpr (cpu::supports(cpu::SSE3))
			str << "  SSE3" << std::endl;
		if constexpr (cpu::supports(cpu::SSSE3))
			str << "  SSSE3" << std::endl;
		if constexpr (cpu::supports(cpu::SSE41))
			str << "  SSE41" << std::endl;
		if constexpr (cpu::supports(cpu::SSE42))
			str << "  SSE42" << std::endl;
		if constexpr (cpu::supports(cpu::AVX))
			str << "  AVX" << std::endl;
		if constexpr (cpu::supports(cpu::AVX2))
			str << "  AVX2" << std::endl;
		return str;
	}
}