#include <pygmalion-chess-evaluation.h>
namespace pygmalion::chess::evaluation
{
	bool command_debugPawntable::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-pawntable")
		{
			std::string remainder2;
			parser::parseTokenCaseSensitive(remainder, token, remainder2);
			playerType p;
			this->output() << std::endl;

			this->output() << "The pawntable has " << pawntable::countPawnTableEntries << " entries." << std::endl;
			this->output() << "  sizeof(pawnentry): " << sizeof(pawntable::pawnentry) << std::endl;
			this->output() << "  memory usage: " << parser::valueToString(sizeof(pawntable::pawnentry) * pawntable::countPawnTableEntries, "B") << std::endl;
			this->output() << std::endl;
			this->output() << "  sizeof(tropism): " << sizeof(typename generatorType::tropismType) << std::endl;
			this->output() << std::endl;
			return true;
		}
		else
			return false;
	}
}