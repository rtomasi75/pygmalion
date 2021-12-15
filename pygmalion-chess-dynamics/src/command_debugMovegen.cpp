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
			this->output() << std::endl;
			size_t count{ 0 };
			playerpieceType ppc;
			if (playerpieceType::parse(token, count, ppc))
			{
				const pieceType pc{ ppc.piece() };
				const playerType p{ ppc.player() };
				squareType sq;
				std::string remainder3;
				parser::parseTokenCaseSensitive(remainder2, token, remainder3);
				count = 0;
				if (squareType::parse(token, count, sq))
				{
					switch (pc)
					{
					default:
						PYGMALION_UNREACHABLE;
						break;
					case knight:
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "knight quiet moves from " << sq.toShortString() << ":" << std::endl;
						dumpSquares(generatorType::movegenKnight.targets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "knight capture moves from " << sq.toShortString() << ":" << std::endl;
						dumpSquares(generatorType::movegenKnight.attacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
						break;
					case king:
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "king quiet moves from " << sq.toShortString() << ":" << std::endl;
						dumpSquares(generatorType::movegenKing.targets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "king capture moves from " << sq.toShortString() << ":" << std::endl;
						dumpSquares(generatorType::movegenKing.attacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
						break;
					case rook:
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "rook quiet moves from " << sq.toShortString() << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersHV.targets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "rook capture moves from " << sq.toShortString() << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersHV.attacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
						break;
					case bishop:
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "bishop quiet moves from " << sq.toShortString() << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersDiag.targets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "bishop capture moves from " << sq.toShortString() << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersDiag.attacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
						break;
					case queen:
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "queen quiet moves from " << sq.toShortString() << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersHV.targets(sq, ~position().totalOccupancy()) | generatorType::movegenSlidersDiag.targets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "queen capture moves from " << sq.toShortString() << ":" << std::endl;
						dumpSquares((generatorType::movegenSlidersHV.attacks(sq, ~position().totalOccupancy()) | generatorType::movegenSlidersDiag.attacks(sq, ~position().totalOccupancy())) & position().playerOccupancy(p.next()));
						break;
					case pawn:
						if (p == whitePlayer)
						{
							this->output() << "white ";
							this->output() << "pawn pushes from " << sq.toShortString() << ":" << std::endl;
							dumpSquares(generatorType::template pawnPushTargets<static_cast<size_t>(whitePlayer)>(sq, ~position().totalOccupancy()));
						}
						else
						{
							this->output() << "black ";
							this->output() << "pawn pushes from " << sq.toShortString() << ":" << std::endl;
							dumpSquares(generatorType::template pawnPushTargets<static_cast<size_t>(blackPlayer)>(sq, ~position().totalOccupancy()));
						}
						this->output() << std::endl;
						if (p == whitePlayer)
						{
							this->output() << "white ";
							this->output() << "pawn double pushes from " << sq.toShortString() << ":" << std::endl;
							dumpSquares(generatorType::template pawnDoublePushTargets<static_cast<size_t>(whitePlayer)>(sq, ~position().totalOccupancy()));
						}
						else
						{
							this->output() << "black ";
							this->output() << "pawn double pushes from " << sq.toShortString() << ":" << std::endl;
							dumpSquares(generatorType::template pawnDoublePushTargets<static_cast<size_t>(blackPlayer)>(sq, ~position().totalOccupancy()));
						}
						this->output() << std::endl;
						if (p == whitePlayer)
						{
							this->output() << "white ";
							this->output() << "pawn captures from " << sq.toShortString() << ":" << std::endl;
							dumpSquares(generatorType::template pawnCaptureTargets<static_cast<size_t>(whitePlayer)>(sq, ~position().totalOccupancy()));
						}
						else
						{
							this->output() << "black ";
							this->output() << "pawn captures from " << sq.toShortString() << ":" << std::endl;
							dumpSquares(generatorType::template pawnCaptureTargets<static_cast<size_t>(blackPlayer)>(sq, ~position().totalOccupancy()));
						}
						break;
					}
				}
				else
					this->output() << "invalid square: " << token << std::endl;
			}
			else
				this->output() << "invalid player/piece: " << token << std::endl;
			this->output() << std::endl;
			return true;
		}
		else
			return false;
	}
}