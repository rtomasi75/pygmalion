#include <pygmalion-tictactoe.h>

namespace pygmalion::tictactoe
{
#if !defined(PYGMALION_CPU_BMI2)
	movemagic movegen::m_Magic{ movemagic(movemagicinfo(), 0x000b) };
#else
	movemagic movegen::m_Magic{ movemagic(movemagicinfo()) };
#endif

	bool movegen::generateMoves_Implementation(const stackType& stack, movelistType& moves, int& currentPass) noexcept
	{
		if (currentPass == 0)
		{
			moves = m_Magic[stack.position().totalOccupancy()];
			currentPass++;
			return true;
		}
		else
			return false;
	}

}