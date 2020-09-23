namespace pygmalion::chess::dynamics
{
	class command_debugMovegen :
		public pygmalion::dynamics::command<descriptor_dynamics, generator>
	{
	public:
		using generatorType = generator;
		using stackType = typename generatorType::stackType;
		using descriptorDynamics = descriptor_dynamics;
#include <pygmalion-dynamics/include_dynamics.h>
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-movegen")
			{
				std::string remainder2;
				parser::parseTokenCaseSensitive(remainder, token, remainder2);
				pieceType pc;
				playerType p;
				this->output() << std::endl;
				if (boardType::parsePiece(token, pc, p))
				{
					squareType sq;
					std::string remainder3;
					parser::parseTokenCaseSensitive(remainder2, token, remainder3);
					if (boardType::parseSquare(token, sq))
					{
						switch (pc)
						{
						case knight:
							dumpSquares(generatorType::knightTargets(sq));
							break;
						}
					}
					else
						this->output() << "invalid square: " << token << std::endl;
				}
				else
					this->output() << "invalid piece: " << token << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
	};

}