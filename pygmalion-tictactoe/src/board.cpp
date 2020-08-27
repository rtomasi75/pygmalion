#include <pygmalion-tictactoe.h>

namespace pygmalion::tictactoe
{

	board::boardStack::boardStack(const boardStack& parent, const move mv) noexcept :
		stack<movedata, move, boardStack>(parent, mv)
	{
	}

	board::boardStack::boardStack(instanceType& position, const player oldPlayer) noexcept :
		stack<movedata, move, boardStack>(position, oldPlayer)
	{
	}

	bool board::boardStack::isMoveLegal_Implementation(const moveType& move) const noexcept
	{
		return movegen::isMoveLegal(*this, move);
	}

	bool board::boardStack::generateMoves_Implementation(movelistType& moves, int& currentPass) const noexcept
	{
		return movegen::generateMoves(*this, moves, currentPass);
	}

	bool board::boardStack::generateTacticalMoves_Implementation(movelistType& moves, int& currentPass) const noexcept
	{
		return movegen::generateTacticalMoves(*this, moves, currentPass);
	}

}