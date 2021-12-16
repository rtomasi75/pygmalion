#include <pygmalion-chess-state.h>
namespace pygmalion::chess
{
	void board::onInitialize_Implementation(const materialTableType& materialTable) noexcept
	{
		setMovingPlayer(whitePlayer);
		// pawns
		for (const auto f : fileType::range)
		{
			addPiece(pawn, rank2 & f, whitePlayer, materialTable);
			addPiece(pawn, rank7 & f, blackPlayer, materialTable);
		}
		clearEnPassant();
		addPiece(king, squareE1, whitePlayer, materialTable);
		addPiece(king, squareE8, blackPlayer, materialTable);
		// rooks
		addPiece(rook, squareA1, whitePlayer, materialTable);
		addPiece(rook, squareH1, whitePlayer, materialTable);
		addPiece(rook, squareA8, blackPlayer, materialTable);
		addPiece(rook, squareH8, blackPlayer, materialTable);
		setCastleRightQueensideBlack();
		setCastleRightQueensideWhite();
		setCastleRightKingsideBlack();
		setCastleRightKingsideWhite();
		// knights
		addPiece(knight, squareB1, whitePlayer, materialTable);
		addPiece(knight, squareG1, whitePlayer, materialTable);
		addPiece(knight, squareB8, blackPlayer, materialTable);
		addPiece(knight, squareG8, blackPlayer, materialTable);
		// bishops
		addPiece(bishop, squareC1, whitePlayer, materialTable);
		addPiece(bishop, squareF1, whitePlayer, materialTable);
		addPiece(bishop, squareC8, blackPlayer, materialTable);
		addPiece(bishop, squareF8, blackPlayer, materialTable);
		// queens
		addPiece(queen, squareD1, whitePlayer, materialTable);
		addPiece(queen, squareD8, blackPlayer, materialTable);
	}

}