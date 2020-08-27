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
		if (side == boardType::whitePlayer)
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
		const typename board::rank rank = board::rankOfSquare(square);
		const typename board::file file = board::fileOfSquare(square);
		board::rank r;
		board::file f;
		if (bDiag)
		{
			for (r = rank + 1, f = file + 1; (r < 8) && (f < 8); r++, f++)
			{
				const squareType sq{ board::fromRankFile(r, f) };
				result.setBit(sq);
				if (blockers.checkBit(sq))
					break;
			}
			for (r = rank + 1, f = file - 1; (r < 8) && (f >= 0); r++, f--)
			{
				const squareType sq{ board::fromRankFile(r, f) };
				result.setBit(sq);
				if (blockers.checkBit(sq))
					break;
			}
			for (r = rank - 1, f = file + 1; (r >= 0) && (f < 8); r--, f++)
			{
				const squareType sq{ board::fromRankFile(r, f) };
				result.setBit(sq);
				if (blockers.checkBit(sq))
					break;
			}
			for (r = rank - 1, f = file - 1; (r >= 0) && (f >= 0); r--, f--)
			{
				const squareType sq{ board::fromRankFile(r, f) };
				result.setBit(sq);
				if (blockers.checkBit(sq))
					break;
			}
		}
		else
		{
			for (r = rank + 1; r < 8; r++)
			{
				const squareType sq{ board::fromRankFile(r, file) };
				result.setBit(sq);
				if (blockers.checkBit(sq))
					break;
			}
			for (r = rank - 1; r >= 0; r--)
			{
				const squareType sq{ board::fromRankFile(r, file) };
				result.setBit(sq);
				if (blockers.checkBit(sq))
					break;
			}
			for (f = file + 1; f < 8; f++)
			{
				const squareType sq{ board::fromRankFile(rank, f) };
				result.setBit(sq);
				if (blockers.checkBit(sq))
					break;
			}
			for (f = file - 1; f >= 0; f--)
			{
				const squareType sq{ board::fromRankFile(rank, f) };
				result.setBit(sq);
				if (blockers.checkBit(sq))
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
}
