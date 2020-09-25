namespace pygmalion::chess::dynamics
{
	class command_debugUntabled :
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
			if (token == "debug-untabled")
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
							this->output() << "knight untabled quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenKnight.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "knight untabled capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenKnight.untabled_attacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
							break;
						case rook:
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "rook relevant squares from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(propagator_sliders_hv::relevant(sq));
							this->output() << std::endl;
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "rook quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenSlidersHV.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "rook capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares((generatorType::movegenSlidersHV.untabled_attacks(sq, ~position().totalOccupancy())) & position().playerOccupancy(p.next()));
							break;
						case bishop:
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "bishop relevant squares from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(propagator_sliders_diag::relevant(sq));
							this->output() << std::endl;
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "bishop quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenSlidersDiag.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "bishop capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares((generatorType::movegenSlidersDiag.untabled_attacks(sq, ~position().totalOccupancy())) & position().playerOccupancy(p.next()));
							break;
						case queen:
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "queen relevant squares from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(propagator_sliders_hv::relevant(sq) | propagator_sliders_diag::relevant(sq));
							this->output() << std::endl;
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "queen quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenSlidersHV.untabled_targets(sq, ~position().totalOccupancy()) | generatorType::movegenSlidersDiag.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							if (p == whitePlayer)
								this->output() << "white ";
							else
								this->output() << "black ";
							this->output() << "queen capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares((generatorType::movegenSlidersHV.untabled_attacks(sq, ~position().totalOccupancy()) | generatorType::movegenSlidersDiag.untabled_attacks(sq, ~position().totalOccupancy())) & position().playerOccupancy(p.next()));
							break;
						case pawn:
							if (p == whitePlayer)
							{
								this->output() << "white pawn untabled push from " << boardType::squareToString(sq) << ":" << std::endl;
								dumpSquares(generatorType::movegenPawnPushWhite.untabled_targets(sq, ~position().totalOccupancy()));
								this->output() << std::endl;
								this->output() << "white pawn untabled double push from " << boardType::squareToString(sq) << ":" << std::endl;
								dumpSquares(generatorType::movegenPawnDoublePushWhite.untabled_targets(sq, ~position().totalOccupancy()));
							}
							else
							{
								this->output() << "black pawn untabled push from " << boardType::squareToString(sq) << ":" << std::endl;
								dumpSquares(generatorType::movegenPawnPushBlack.untabled_targets(sq, ~position().totalOccupancy()));
								this->output() << std::endl;
								this->output() << "black pawn untabled double push from " << boardType::squareToString(sq) << ":" << std::endl;
								dumpSquares(generatorType::movegenPawnDoublePushBlack.untabled_targets(sq, ~position().totalOccupancy()));
							}
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