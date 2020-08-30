#include <pygmalion-chess.h>

namespace pygmalion::chess
{
	movegenTables movegen::m_Tables;

	typename movegen::bitsType movegen::pawnMoveMap_untabled(const playerType side, const squareType square, const bool bCapture) noexcept
	{
		assert(side.isValid());
		assert(square.isValid());
		const bitsType piecemask{ bitsType::setMask(square) };
		bitsType movemap{ bitsType::empty() };
		if (side == whitePlayer)
		{
			if (bCapture)
			{
				movemap |= boardType::upLeft(piecemask & boardType::notRank1);
				movemap |= boardType::upRight(piecemask & boardType::notRank1);
			}
			else
				movemap |= boardType::up(piecemask & boardType::notRank1);
		}
		else
		{
			if (bCapture)
			{
				movemap |= boardType::downLeft(piecemask & boardType::notRank8);
				movemap |= boardType::downRight(piecemask & boardType::notRank8);
			}
			else
				movemap |= boardType::down(piecemask & boardType::notRank8);
		}
		return movemap;
	}

	typename movegen::bitsType movegen::knightMoveMap_untabled(const squareType square) noexcept
	{
		assert(square.isValid());
		const bitsType piecemask{ bitsType::setMask(square) };
		bitsType map{ bitsType::empty() };
		map |= boardType::upLeftLeft(piecemask);
		map |= boardType::upRightRight(piecemask);
		map |= boardType::downLeftLeft(piecemask);
		map |= boardType::downRightRight(piecemask);
		map |= boardType::upUpLeft(piecemask);
		map |= boardType::upUpRight(piecemask);
		map |= boardType::downDownLeft(piecemask);
		map |= boardType::downDownRight(piecemask);
		return map;
	}

	typename movegen::bitsType movegen::kingMoveMap_untabled(const squareType square) noexcept
	{
		assert(square.isValid());
		const bitsType piecemask{ bitsType::setMask(square) };
		bitsType map{ bitsType::empty() };
		map |= boardType::up(piecemask);
		map |= boardType::down(piecemask);
		map |= boardType::left(piecemask);
		map |= boardType::right(piecemask);
		map |= boardType::upLeft(piecemask);
		map |= boardType::upRight(piecemask);
		map |= boardType::downLeft(piecemask);
		map |= boardType::downRight(piecemask);
		return map;
	}

	typename movegen::bitsType movegen::sliderAttacks_untabled(const squareType square, const bitsType blockers, const bool bDiag) noexcept
	{
		assert(square.isValid());
		bitsType result;
		const typename board::rankType rank{ square.rank() };
		const typename board::fileType file{ square.file() };
		board::rankType r;
		board::fileType f;
		if (bDiag)
		{
			for (r = rank + 1, f = file + 1; (r < 8) && (f < 8); r++, f++)
			{
				const squareType sq{ squareType::fromRankFile(r, f) };
				result.setBit(sq);
				if (blockers[sq])
					break;
			}
			for (r = rank + 1, f = file - 1; (r < 8) && (f >= 0); r++, f--)
			{
				const squareType sq{ squareType::fromRankFile(r, f) };
				result.setBit(sq);
				if (blockers[sq])
					break;
			}
			for (r = rank - 1, f = file + 1; (r >= 0) && (f < 8); r--, f++)
			{
				const squareType sq{ squareType::fromRankFile(r, f) };
				result.setBit(sq);
				if (blockers[sq])
					break;
			}
			for (r = rank - 1, f = file - 1; (r >= 0) && (f >= 0); r--, f--)
			{
				const squareType sq{ squareType::fromRankFile(r, f) };
				result.setBit(sq);
				if (blockers[sq])
					break;
			}
		}
		else
		{
			for (r = rank + 1; r < 8; r++)
			{
				const squareType sq{ squareType::fromRankFile(r, file) };
				result.setBit(sq);
				if (blockers[sq])
					break;
			}
			for (r = rank - 1; r >= 0; r--)
			{
				const squareType sq{ squareType::fromRankFile(r, file) };
				result.setBit(sq);
				if (blockers[sq])
					break;
			}
			for (f = file + 1; f < 8; f++)
			{
				const squareType sq{ squareType::fromRankFile(rank, f) };
				result.setBit(sq);
				if (blockers[sq])
					break;
			}
			for (f = file - 1; f >= 0; f--)
			{
				const squareType sq{ squareType::fromRankFile(rank, f) };
				result.setBit(sq);
				if (blockers[sq])
					break;
			}
		}
		return result;
	}

	void movegen::sliderMoveMaps_untabled(const bool bDiag, const squareType square, const bitsType occupy, const bitsType capturetargets, bitsType& moves, bitsType& caps) noexcept
	{
		assert(square.isValid());
		bitsType attmask = sliderAttacks_untabled(square, occupy, bDiag);
		moves |= attmask & ~occupy;
		caps |= attmask & capturetargets;
	}

	void movegen::initializePosition_Implementation(boardType& position) noexcept
	{
		position.clear();
		position.setMovingPlayer(whitePlayer);
		// pawns
		for (const auto f : fileType::range)
		{
			position.addPiece(pawn, squareType::fromRankFile(rank2, f), whitePlayer);
			position.material() += evaluator::material(whitePlayer, pawn, squareType::fromRankFile(rank2, f));
			position.addPiece(pawn, squareType::fromRankFile(rank7, f), blackPlayer);
			position.material() += evaluator::material(blackPlayer, pawn, squareType::fromRankFile(rank7, f));
		}
		position_clearEnPassantFlags(position);
		// kings
		position.addPiece(king, squareE1, whitePlayer);
		position.material() += evaluator::material(whitePlayer, king, squareE1);
		position.addPiece(king, squareE8, blackPlayer);
		position.material() += evaluator::material(blackPlayer, king, squareE8);
		// rooks
		position.addPiece(rook, squareA1, whitePlayer);
		position.material() += evaluator::material(whitePlayer, rook, squareA1);
		position.addPiece(rook, squareH1, whitePlayer);
		position.material() += evaluator::material(whitePlayer, rook, squareH1);
		position.addPiece(rook, squareA8, blackPlayer);
		position.material() += evaluator::material(blackPlayer, rook, squareA8);
		position.addPiece(rook, squareH8, blackPlayer);
		position.material() += evaluator::material(blackPlayer, rook, squareH8);
		position_setCastlerightQueensideBlack(position);
		position_setCastlerightQueensideWhite(position);
		position_setCastlerightKingsideBlack(position);
		position_setCastlerightKingsideWhite(position);
		// knights
/*		position.addPiece(knight, squareB1, whitePlayer);
		position.material() += evaluator::material(whitePlayer, knight, squareB1);
		position.addPiece(knight, squareG1, whitePlayer);
		position.material() += evaluator::material(whitePlayer, knight, squareG1);
		position.addPiece(knight, squareB8, blackPlayer);
		position.material() += evaluator::material(blackPlayer, knight, squareB8);
		position.addPiece(knight, squareG8, blackPlayer);
		position.material() += evaluator::material(blackPlayer, knight, squareG8);
		// bishops
		position.addPiece(bishop, squareC1, whitePlayer);
		position.material() += evaluator::material(whitePlayer, bishop, squareC1);
		position.addPiece(bishop, squareF1, whitePlayer);
		position.material() += evaluator::material(whitePlayer, bishop, squareF1);
		position.addPiece(bishop, squareC8, blackPlayer);
		position.material() += evaluator::material(blackPlayer, bishop, squareC8);
		position.addPiece(bishop, squareF8, blackPlayer);
		position.material() += evaluator::material(blackPlayer, bishop, squareF8);
		// queens
		position.addPiece(queen, squareD1, whitePlayer);
		position.material() += evaluator::material(whitePlayer, queen, squareD1);
		position.addPiece(queen, squareD8, blackPlayer);
		position.material() += evaluator::material(blackPlayer, queen, squareD8);*/
	}
	
	void movegen::makeMove_Implementation(boardType& position, const movedataType& md) noexcept
	{
		score newMaterial{ md.oldMaterial() };
		if (md.isCapture())
		{
			position.removePiece(md.capturedPiece(), md.captureSquare(), md.otherPlayer());
			position.setDistanceToDraw(DrawingDistance);
			newMaterial -= evaluator::material(md.otherPlayer(), md.capturedPiece(), md.captureSquare());
			switch (md.capturedPiece())
			{
			case movegen::rook:
				if (md.otherPlayer() == movegen::blackPlayer)
				{
					if (md.captureSquare() == movegen::squareA8)
						movegen::position_clearCastlerightQueensideBlack(position);
					else if (md.captureSquare() == movegen::squareH8)
						movegen::position_clearCastlerightKingsideBlack(position);
				}
				else
				{
					if (md.captureSquare() == movegen::squareA1)
						movegen::position_clearCastlerightQueensideWhite(position);
					else if (md.captureSquare() == movegen::squareH1)
						movegen::position_clearCastlerightKingsideWhite(position);
				}
				break;
			}
		}
		else
			position.setDistanceToDraw(position.getDistanceToDraw() - 1);
		switch (md.movingPiece())
		{
		case movegen::king:
			if (md.movingPlayer() == movegen::blackPlayer)
			{
				movegen::position_clearCastlerightKingsideBlack(position);
				movegen::position_clearCastlerightQueensideBlack(position);
			}
			else
			{
				movegen::position_clearCastlerightKingsideWhite(position);
				movegen::position_clearCastlerightQueensideWhite(position);
			}
		case movegen::rook:
			if (md.movingPlayer() == movegen::blackPlayer)
			{
				if (md.fromSquare() == movegen::squareA8)
					movegen::position_clearCastlerightQueensideBlack(position);
				else if (md.fromSquare() == movegen::squareH8)
					movegen::position_clearCastlerightKingsideBlack(position);
			}
			else
			{
				if (md.fromSquare() == movegen::squareA1)
					movegen::position_clearCastlerightQueensideWhite(position);
				else if (md.fromSquare() == movegen::squareH1)
					movegen::position_clearCastlerightKingsideWhite(position);
			}
			break;
		}
		position.removePiece(md.movingPiece(), md.fromSquare(), md.movingPlayer());
		newMaterial -= evaluator::material(md.movingPlayer(), md.movingPiece(), md.fromSquare());
		position.addPiece(md.targetPiece(), md.toSquare(), md.movingPlayer());
		newMaterial += evaluator::material(md.movingPlayer(), md.targetPiece(), md.toSquare());
		movegen::position_clearEnPassantFlags(position);
		if (md.isDoublePush())
			movegen::position_setEnPassantFlag(position, md.toSquare().file());
		else if (md.isCastling())
		{
			position.removePiece(movegen::rook, md.rookFrom(), md.movingPlayer());
			newMaterial -= evaluator::material(md.movingPlayer(), movegen::rook, md.rookFrom());
			position.addPiece(movegen::rook, md.rookTo(), md.movingPlayer());
			newMaterial += evaluator::material(md.movingPlayer(), movegen::rook, md.rookTo());
		}
		position.setMovingPlayer(md.otherPlayer());
		position.setMaterial(newMaterial);
	}
	
	void movegen::unmakeMove_Implementation(boardType& position, const movedataType& md) noexcept
	{
		if (md.isCastling())
		{
			position.removePiece(movegen::rook, md.rookTo(), md.movingPlayer());
			position.addPiece(movegen::rook, md.rookFrom(), md.movingPlayer());
		}
		position.removePiece(md.targetPiece(), md.toSquare(), md.movingPlayer());
		position.addPiece(md.movingPiece(), md.fromSquare(), md.movingPlayer());
		if (md.isCapture())
			position.addPiece(md.capturedPiece(), md.captureSquare(), md.otherPlayer());
		position.setMaterial(md.oldMaterial());
		position.setDistanceToDraw(md.oldDistanceToDraw());
		position.setMovingPlayer(md.movingPlayer());
		position.flags() = md.oldFlags();
	}

}
