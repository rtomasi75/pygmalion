#include <pygmalion-chess.h>

namespace pygmalion::chess
{
	evaluationTables::evaluationTables() noexcept :
		m_Material
	{
		score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),
		score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),
		score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),
		score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),
		score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),
		score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),
		score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),
		score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),
		score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),
		score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),
		score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),
		score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),score::zero(),
	}
	{
		for (int8_t i = 0; i <= maxSquareValue; i++)
		{
			m_SquareImportance[i] = bitsType(0);
			for (const auto square : board::squareType::range)
			{
				if (m_SquareValue[square] == i)
					m_SquareImportance[i].setBit(square);
			}
		}
		for (const auto rank : board::rankType::range)
		{
			for (const auto file : board::fileType::range)
			{
				const typename board::squareType square{ board::squareType::fromRankFile(rank,file) };
				for (const auto s : board::playerType::range)
				{
					bitsType moveMap;
					bitsType capMap;
					int8_t imp{ 0 };
					if ((rank != movegen::rank1) && (rank != movegen::rank8))
					{
						moveMap = movegen::pawnMoveMap_untabled(s, square, false);
						capMap = movegen::pawnMoveMap_untabled(s, square, true);
						if ((rank == movegen::rank2) && (s == movegen::whitePlayer))
						{
							moveMap |= board::up(moveMap);
						}
						if ((rank == movegen::rank7) && (s == movegen::blackPlayer))
						{
							moveMap |= board::down(moveMap);
						}

						for (int8_t importance = 1; importance <= maxSquareValue; importance++)
						{
							bitsType relevant = m_SquareImportance[importance];
							imp += importance * (relevant & moveMap).populationCount();
							imp += importance * (relevant & capMap).populationCount();
						}
						m_Material[s][movegen::pawn][square] = ((s == movegen::whitePlayer) ? score::one() : -score::one()) * (m_LazyMaterial[movegen::pawn] * score::one() + score::atom() * imp);
					}
					moveMap = movegen::knightMoveMap_untabled(square);
					capMap = movegen::knightMoveMap_untabled(square);
					imp = 0;
					for (int8_t importance = 1; importance <= maxSquareValue; importance++)
					{
						bitsType relevant = m_SquareImportance[importance];
						imp += importance * (relevant & moveMap).populationCount();
						imp += importance * (relevant & capMap).populationCount();
					}
					m_Material[s][movegen::knight][square] = ((s == movegen::whitePlayer) ? score::one() : -score::one()) * (m_LazyMaterial[movegen::knight] * score::one() + score::atom() * imp);
					moveMap = bitsType::empty();
					capMap = bitsType::empty();
					movegen::sliderMoveMaps_untabled(true, square, bitsType::empty(), bitsType::universe(), moveMap, capMap);
					imp = 0;
					for (int8_t importance = 1; importance <= maxSquareValue; importance++)
					{
						bitsType relevant = m_SquareImportance[importance];
						imp += importance * (relevant & moveMap).populationCount();
						imp += importance * (relevant & capMap).populationCount();
					}
					m_Material[s][movegen::bishop][square] = ((s == movegen::whitePlayer) ? score::one() : -score::one()) * (m_LazyMaterial[movegen::bishop] * score::one() + score::atom() * imp);
					moveMap = bitsType::empty();
					capMap = bitsType::empty();
					movegen::sliderMoveMaps_untabled(false, square, bitsType::empty(), bitsType::universe(), moveMap, capMap);
					imp = 0;
					for (int8_t importance = 1; importance <= maxSquareValue; importance++)
					{
						bitsType relevant = m_SquareImportance[importance];
						imp += importance * (relevant & moveMap).populationCount();
						imp += importance * (relevant & capMap).populationCount();
					}
					m_Material[s][movegen::rook][square] = ((s == movegen::whitePlayer) ? score::one() : -score::one()) * (m_LazyMaterial[movegen::rook] * score::one() + score::atom() * imp);
					moveMap = bitsType::empty();
					capMap = bitsType::empty();
					movegen::sliderMoveMaps_untabled(false, square, bitsType::empty(), bitsType::universe(), moveMap, capMap);
					movegen::sliderMoveMaps_untabled(true, square, bitsType::empty(), bitsType::universe(), moveMap, capMap);
					imp = 0;
					for (int8_t importance = 1; importance <= maxSquareValue; importance++)
					{
						bitsType relevant = m_SquareImportance[importance];
						imp += importance * (relevant & moveMap).populationCount();
						imp += importance * (relevant & capMap).populationCount();
					}
					m_Material[s][movegen::queen][square] = ((s == movegen::whitePlayer) ? score::one() : -score::one()) * (m_LazyMaterial[movegen::queen] * score::one() + score::atom() * imp);
					moveMap = movegen::kingMoveMap_untabled(square);
					capMap = movegen::kingMoveMap_untabled(square);
					imp = 0;
					for (int8_t importance = 1; importance <= maxSquareValue; importance++)
					{
						bitsType relevant = m_SquareImportance[importance];
						imp += importance * (relevant & moveMap).populationCount();
						imp += importance * (relevant & capMap).populationCount();
					}
					m_Material[s][movegen::king][square] = ((s == movegen::whitePlayer) ? score::one() : -score::one()) * (m_LazyMaterial[movegen::king] * score::one() + score::atom() * imp);
				}
			}
		}
		for (int rank = 1; rank < 7; rank++)
		{
			for (const auto side : board::playerType::range)
			{
				const typename board::rankType promotionrank{ side == movegen::whitePlayer ? movegen::rank8 : movegen::rank1 };
				const int dist{ (side == movegen::whitePlayer) ? promotionrank - rank : rank - promotionrank };
				for (const auto file : board::fileType::range)
				{
					score promotedscore = m_Material[side][movegen::queen][board::squareType::fromRankFile(promotionrank, file)] + m_Material[side][movegen::knight][board::squareType::fromRankFile(promotionrank, file)];
					for (int d = 0; d <= dist; d++)
					{
						promotedscore *= static_cast<score>(0.5);
					}
					m_Material[side][movegen::pawn][board::squareType::fromRankFile(rank, file)] += m_PromotionStep * promotedscore;
				}
			}
		}
		for (const auto sq : board::squareType::range)
		{
			m_Material[movegen::blackPlayer][movegen::pawn][sq] = -m_Material[movegen::whitePlayer][movegen::pawn][board::squareType::fromRankFile(7 - sq.rank(), sq.file())];
		}
	}
}