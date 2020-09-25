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
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "knight quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::knightTargets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "knight capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::knightAttacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
							break;
						case rook:
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "rook quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::sliderTargetsHV(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "rook capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::sliderAttacksHV(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
							break;
						case bishop:
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "bishop quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::sliderTargetsDiag(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "bishop capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::sliderAttacksDiag(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
							break;
						case queen:
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "queen quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::sliderTargetsHV(sq, ~position().totalOccupancy()) | generatorType::sliderTargetsDiag(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "queen capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares((generatorType::sliderAttacksHV(sq, ~position().totalOccupancy()) | generatorType::sliderAttacksDiag(sq, ~position().totalOccupancy())) & position().playerOccupancy(p.next()));
							break;
						case pawn:
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "pawn push from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::pawnPushTargets(sq, p, ~position().totalOccupancy()));
							this->output() << std::endl;
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "pawn double push from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::pawnDoublePushTargets(sq, p, ~position().totalOccupancy()));
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