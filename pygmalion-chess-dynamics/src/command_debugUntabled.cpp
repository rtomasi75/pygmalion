#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_debugUntabled::onProcess(const std::string& cmd) noexcept
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
			size_t count{ 0 };
			if (boardType::parsePiece(token, pc, p, count))
			{
				squareType sq;
				std::string remainder3;
				parser::parseTokenCaseSensitive(remainder2, token, remainder3);
				count = 0;
				if (boardType::parseSquare(token, sq, count))
				{
					switch (pc)
					{
					default:
						PYGMALION_UNREACHABLE;
						break;
					case king:
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "king untabled quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenKing.untabled_targets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "king untabled capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenKing.untabled_attacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
						this->output() << std::endl;
						this->output() << "king untabled inverse quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenKing.untabled_inverseTargets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "king untabled inverse capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenKing.untabled_inverseAttacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
						break;
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
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "knight untabled inverse quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenKnight.untabled_inverseTargets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "knight untabled inverse capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenKnight.untabled_inverseAttacks(sq, ~position().totalOccupancy()) & position().playerOccupancy(p.next()));
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
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "rook inverse relevant squares from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(propagator_sliders_hv::inverseRelevant(sq));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "rook inverse quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersHV.untabled_inverseTargets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "rook inverse capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares((generatorType::movegenSlidersHV.untabled_inverseAttacks(sq, ~position().totalOccupancy())) & position().playerOccupancy(p.next()));
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
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "bishop inverse relevant squares from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(propagator_sliders_diag::inverseRelevant(sq));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "bishop inverse quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersDiag.untabled_inverseTargets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "bishop inverse capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares((generatorType::movegenSlidersDiag.untabled_inverseAttacks(sq, ~position().totalOccupancy())) & position().playerOccupancy(p.next()));
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
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "queen inverse relevant squares from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(propagator_sliders_hv::inverseRelevant(sq) | propagator_sliders_diag::relevant(sq));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "queen inverse quiet moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares(generatorType::movegenSlidersHV.untabled_inverseTargets(sq, ~position().totalOccupancy()) | generatorType::movegenSlidersDiag.untabled_targets(sq, ~position().totalOccupancy()));
						this->output() << std::endl;
						if (p == whitePlayer)
							this->output() << "white ";
						else
							this->output() << "black ";
						this->output() << "queen inverse capture moves from " << boardType::squareToString(sq) << ":" << std::endl;
						dumpSquares((generatorType::movegenSlidersHV.untabled_inverseAttacks(sq, ~position().totalOccupancy()) | generatorType::movegenSlidersDiag.untabled_attacks(sq, ~position().totalOccupancy())) & position().playerOccupancy(p.next()));
						break;
					case pawn:
						if (p == whitePlayer)
						{
							this->output() << "white pawn untabled push from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnPushWhite.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "white pawn untabled double push from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnDoublePushWhite.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "white pawn untabled capture from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnCaptureWhite.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "white pawn untabled promotion from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnPromotionWhite.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "white pawn untabled promocapture from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnPromoCaptureWhite.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "white pawn untabled inverse push from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnPushWhite.untabled_inverseTargets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "white pawn untabled inverse double push from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnDoublePushWhite.untabled_inverseTargets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "white pawn untabled inverse capture from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnCaptureWhite.untabled_inverseTargets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "white pawn untabled inverse promotion from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnPromotionWhite.untabled_inverseTargets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "white pawn untabled inverse promocapture from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnPromoCaptureWhite.untabled_inverseTargets(sq, ~position().totalOccupancy()));
						}
						else
						{
							this->output() << "black pawn untabled push from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnPushBlack.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "black pawn untabled double push from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnDoublePushBlack.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "black pawn untabled capture from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnCaptureBlack.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "black pawn untabled promotion from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnPromotionBlack.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "black pawn untabled promocapture from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnPromoCaptureBlack.untabled_targets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "black pawn untabled inverse push from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnPushBlack.untabled_inverseTargets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "black pawn untabled inverse double push from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnDoublePushBlack.untabled_inverseTargets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "black pawn untabled inverse capture from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnCaptureBlack.untabled_inverseTargets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "black pawn untabled inverse promotion from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnPromotionBlack.untabled_inverseTargets(sq, ~position().totalOccupancy()));
							this->output() << std::endl;
							this->output() << "black pawn untabled inverse promocapture from " << boardType::squareToString(sq) << ":" << std::endl;
							dumpSquares(generatorType::movegenPawnPromoCaptureBlack.untabled_inverseTargets(sq, ~position().totalOccupancy()));
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
}