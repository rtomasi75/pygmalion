#include <pygmalion-intrinsics.h>

namespace pygmalion
{
	std::ostream& operator<<(std::ostream& str, const compiler::flags f) noexcept
	{
		if (f & compiler::flags::MSC)
			str << "MSC" << std::endl;
		if (f & compiler::flags::GNU)
			str << "GNU" << std::endl;
		return str;
	}
}