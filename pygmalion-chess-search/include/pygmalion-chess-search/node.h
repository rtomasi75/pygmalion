namespace pygmalion::chess
{
	class node :
		public pygmalion::node<descriptor_search, node>
	{
	public:
		constexpr node(const stackType& stack, std::atomic_bool& isRunning, heuristicsType& heuristics) noexcept :
			pygmalion::node<descriptor_search, node>(stack, isRunning, heuristics)
		{

		}
		constexpr static bool futilityPruningEnabled_Implementation(const size_t depthRemaining) noexcept
		{
			return depthRemaining <= 1;
		}
		constexpr node(const node& parent, const movebitsType moveBits) noexcept :
			pygmalion::node<descriptor_search, node>(parent, moveBits)
		{
		}
		constexpr static depthType nullMoveReduction_Implementation(const size_t depthRemaining) noexcept
		{
			return depthType(2) + depthRemaining / depthType(4);
		}
		bool nullMoveAllowed_Implementation(const scoreType alpha, const scoreType beta) const noexcept
		{
			if (!(alpha.isOpen() && beta.isOpen()))
				return false;
			const squaresType pieces{ this->stack().position().pieceOccupancy(knight) | this->stack().position().pieceOccupancy(bishop) | this->stack().position().pieceOccupancy(rook) | this->stack().position().pieceOccupancy(queen) };
			const squaresType playerPieces{ pieces & this->stack().position().playerOccupancy(this->stack().position().movingPlayer()) };
			return (playerPieces != squaresType::none()) && !this->stack().isCheck();
		}
		constexpr static scoreType futilityMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
		{
			assert(depthRemaining <= 1);
			return evaluatorType::MaxPositionChange;
		}
		constexpr static scoreType futilityGlobalMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
		{
			assert(depthRemaining <= 1);
			if (stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()))
				return static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) + evaluatorType::MaxPositionChange;
			if (stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()))
				return static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) + evaluatorType::MaxPositionChange;
			if (stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()))
				return static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) + evaluatorType::MaxPositionChange;
			if (stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()))
				return static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) + evaluatorType::MaxPositionChange;
			if (stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()))
				return static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange;
			return evaluatorType::MaxPositionChange;
		}
		bool pruningAllowed_Implementation(const scoreType alpha, const scoreType beta) const noexcept
		{
			return alpha.isOpen() && beta.isOpen() && !this->stack().isCheck();
		}
		scoreType tacticalMoveValue_Implementation(const movebitsType& move) const noexcept
		{
			assert(motorType::move().isCapture(move));
			const squareType captureSquare{ motorType::move().captureSquare(this->stack().position(),move) };
			const pieceType capturedPiece{ this->stack().position().getPiece(captureSquare) };
			const scoreType victimValue{ static_cast<scoreType>(boardType::materialValue(capturedPiece, whitePlayer)) };
			return victimValue;
		}
	};
}