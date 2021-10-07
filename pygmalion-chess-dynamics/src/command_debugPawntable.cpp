#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_debugPawntable::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-pawntable")
		{
			this->output() << std::endl;
			this->output() << "PT entry:   " << std::setw(4) << sizeof(typename generatorType::pawntable::pawnentry) << " = " << sizeof(typename generatorType::pawntable::pawnentry) * CHAR_BIT << "bit" << std::endl;
			this->output() << "PT memory:  " << std::setw(4) << parser::memoryToString(generatorType::pawnTable().memoryUsed(), "B") << std::endl;
			this->output() << "PT entries: " << std::setw(4) << generatorType::pawnTable().countEntries() << std::endl;
			this->output() << "PT used:    " << std::setw(4) << generatorType::pawnTable().countUsedEntries() << std::endl;
			this->output() << std::endl;
			//this->output() << "sizeof(tropism): " << sizeof(typename generatorType::tropismType) << std::endl;
			//this->output() << std::endl;
			return true;
		}
		else
			return false;
	}
}