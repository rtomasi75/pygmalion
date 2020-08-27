#include <pygmalion-chess.h>

namespace pygmalion::chess
{
	movegenTables::movegenTables() noexcept
	{
		for (const auto sq : board::square::range)
		{
			m_KnightMoveMap[sq] = movegen::knightMoveMap_untabled(sq);
			m_KingMoveMap[sq] = movegen::kingMoveMap_untabled(sq);
			for (const auto p : board::player::range)
			{
				m_PawnMoveMap[p][sq] = movegen::pawnMoveMap_untabled(p, sq, false);
#if defined(_DEBUG)&& defined(PYGMALION_CHESS_DEBUG_PAWNMOVEMAP)
				std::cerr << "pmm_init" << " " << frontend::playerToString(p) << " " << frontend::squareToString(sq) << std::endl;
				frontend::dumpBitboard(m_PawnMoveMap[p][sq], std::cerr);
#endif
				m_PawnCaptureMap[p][sq] = movegen::pawnMoveMap_untabled(p, sq, true);
			}
		//	m_SliderMagics[false][sq] = slidermagic(slidermagicinfo(sq, false));
		//	m_SliderMagics[true][sq] = slidermagic(slidermagicinfo(sq, true));
		}
	}

	void movegenTables::pawnMoveMap_Debug(const squareType sq, const playerType p) const noexcept
	{
		std::cerr << "pmm_get" << " " << pygmalion::chess::frontend::playerToString(p) << " " << frontend::squareToString(sq) << std::endl;
		frontend::dumpBitboard(m_PawnMoveMap[p][sq], std::cerr);
	}
}