#include <pygmalion-intrinsics.h>

namespace pygmalion
{
	std::ostream& operator<<(std::ostream& str, const compiler::flags f) noexcept
	{
		str << "Compiler intrinsics:" << std::endl;
		if constexpr (compiler::supports(compiler::MSC))
			str << "  MSC" << std::endl;
		if constexpr (compiler::supports(compiler::GNU))
			str << "  GNU" << std::endl;
		return str;
	}
}