#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_debugMovegen::onProcess(const std::string& cmd) noexcept
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
						dumpSquares(generatorType::movegenKnight.targets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "knight capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenKnight.attacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
						break;
					case king:
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "king quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenKing.targets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "king capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenKing.attacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
						break;
					case rook:
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "rook quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersHV.targets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "rook capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersHV.attacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
						break;
					case bishop:
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "bishop quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersDiag.targets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "bishop capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersDiag.attacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
						break;
					case queen:
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "queen quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersHV.targets(sq, ~position().totalOccupancy()) | generatorType::movegenSlidersDiag.targets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "queen capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares((generatorType::movegenSlidersHV.attacks(sq, ~position().totalOccupancy()) | generatorType::movegenSlidersDiag.attacks(sq, ~position().totalOccupancy())) & position().playerOccupancy(p.next()));
						break;
					case pawn:
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "pawn pushes from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::pawnPushTargets(sq, p, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "pawn double pushes from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::pawnDoublePushTargets(sq, p, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "pawn captures from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::pawnCaptureTargets(sq, p, ~position().totalOccupancy()));
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
}