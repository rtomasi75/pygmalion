#include <pygmalion-chess-evaluation.h>
namespace pygmalion::chess::evaluation
{
	bool command_debugSEE::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-see")
		{
			std::string remainder2;
			parser::parseTokenCaseSensitive(remainder, token, remainder2);
			this->output() << std::endl;
			movebitsType movebits;
			if (motorType::parseMove(this->position(), token, movebits))
			{
				typename generatorType::contextType context;
				stackType stack(this->position(), this->history(), this->position().movingPlayer(), &context);
				if (generatorType::isMoveLegal(stack, movebits))
				{
					materialScore score{ evaluatorType::staticExchange(movebits, this->position()) };
					this->output() << "static exchange evaluation for " << motorType::moveToString(this->position(), movebits) << ":" << std::endl;
					this->output() << score;
				}
				else
					this->output() << token << " is not a legal move." << std::endl;
			}
			else
				this->output() << token << " is not a possible move." << std::endl;
			this->output() << std::endl;
			return true;
		}
		else
			return false;
	}
}