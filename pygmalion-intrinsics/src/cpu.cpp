#include <pygmalion-intrinsics.h>

namespace pygmalion
{
	std::ostream& operator<<(std::ostream& str, const cpu::flags f) noexcept
	{
		if (f & cpu::X86)
			str << "X86" << std::endl;
		if (f & cpu::X64)
			str << "X64" << std::endl;
		if (f & cpu::BMI2)
			str << "BMI2" << std::endl;
		return str;
	}
}