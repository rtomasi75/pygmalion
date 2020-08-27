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
			for (const auto square : board::square::range)
			{
				if (m_SquareValue[square] == i)
					m_SquareImportance[i].setBit(square);
			}
		}
		for (const auto rank : board::rank::range)
		{
			for (const auto file : board::file::range)
			{
				const typename board::square square{ board::fromRankFile(rank,file) };
				for (const auto s : board::player::range)
				{
					bitsType moveMap;
					bitsType capMap;
					int8_t imp{ 0 };
					if ((rank != board::rank1) && (rank != board::rank8))
					{
						moveMap = movegen::pawnMoveMap_untabled(s, square, false);
						capMap = movegen::pawnMoveMap_untabled(s, square, true);
						if ((rank == board::rank2) && (s == board::whitePlayer))
						{
							moveMap |= board::up(moveMap);
						}
						if ((rank == board::rank7) && (s == board::blackPlayer))
						{
							moveMap |= board::down(moveMap);
						}

						for (int8_t importance = 1; importance <= maxSquareValue; importance++)
						{
							bitsType relevant = m_SquareImportance[importance];
							imp += importance * (relevant & moveMap).populationCount();
							imp += importance * (relevant & capMap).populationCount();
						}
						m_Material[s][board::pawn][square] = ((s == board::whitePlayer) ? score::one() : -score::one()) * (m_LazyMaterial[board::pawn] * score::one() + score::atom() * imp);
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
					m_Material[s][board::knight][square] = ((s == board::whitePlayer) ? score::one() : -score::one()) * (m_LazyMaterial[board::knight] * score::one() + score::atom() * imp);
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
					m_Material[s][board::bishop][square] = ((s == board::whitePlayer) ? score::one() : -score::one()) * (m_LazyMaterial[board::bishop] * score::one() + score::atom() * imp);
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
					m_Material[s][board::rook][square] = ((s == board::whitePlayer) ? score::one() : -score::one()) * (m_LazyMaterial[board::rook] * score::one() + score::atom() * imp);
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
					m_Material[s][board::queen][square] = ((s == board::whitePlayer) ? score::one() : -score::one()) * (m_LazyMaterial[board::queen] * score::one() + score::atom() * imp);
					moveMap = movegen::kingMoveMap_untabled(square);
					capMap = movegen::kingMoveMap_untabled(square);
					imp = 0;
					for (int8_t importance = 1; importance <= maxSquareValue; importance++)
					{
						bitsType relevant = m_SquareImportance[importance];
						imp += importance * (relevant & moveMap).populationCount();
						imp += importance * (relevant & capMap).populationCount();
					}
					m_Material[s][board::king][square] = ((s == board::whitePlayer) ? score::one() : -score::one()) * (m_LazyMaterial[board::king] * score::one() + score::atom() * imp);
				}
			}
		}
		for (int rank = 1; rank < 7; rank++)
		{
			for (const auto side : board::player::range)
			{
				const typename board::rank promotionrank{ side == board::whitePlayer ? board::rank8 : board::rank1 };
				const int dist{ (side == board::whitePlayer) ? promotionrank - rank : rank - promotionrank };
				for (const auto file : board::file::range)
				{
					score promotedscore = m_Material[side][board::queen][board::fromRankFile(promotionrank, file)] + m_Material[side][board::knight][board::fromRankFile(promotionrank, file)];
					for (int d = 0; d <= dist; d++)
					{
						promotedscore *= static_cast<score>(0.5);
					}
					m_Material[side][board::pawn][board::fromRankFile(rank, file)] += m_PromotionStep * promotedscore;
				}
			}
		}
		for (const auto sq : board::square::range)
		{
			m_Material[board::blackPlayer][board::pawn][sq] = -m_Material[board::whitePlayer][board::pawn][board::fromRankFile(7 - board::rankOfSquare(sq), board::fileOfSquare(sq))];

		}
	}
}