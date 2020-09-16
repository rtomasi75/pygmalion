#include <pygmalion-intrinsics.h>

namespace pygmalion::intrinsics
{
	bool command_debugCompiler::onProcess(engine& eng, const std::string& cmd) const noexcept 
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-compiler")
		{
			eng.outputStream() << std::endl;
			eng.outputStream() << "Compiler intrinsics:" << std::endl;
			if constexpr (compiler::supports(compiler::MSC))
				eng.outputStream() << "  MSC" << std::endl;
			if constexpr (compiler::supports(compiler::GNU))
				eng.outputStream() << "  GNU" << std::endl;
			eng.outputStream() << std::endl;
			return true;
		}
		else
			return false;
	}
}