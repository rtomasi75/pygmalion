namespace pygmalion::chess
{
	class node :
		public pygmalion::node<descriptor_search, node>
	{
	public:
		node(const stackType& stack, std::atomic_bool& isRunning, heuristicsType& heuristics) noexcept :
			pygmalion::node<descriptor_search, node>(stack, isRunning, heuristics)
		{

		}
		constexpr static bool futilityPruningEnabled_Implementation(const size_t depthRemaining) noexcept
		{
			return depthRemaining <= 1;
		}
		node(const node& parent, const movebitsType moveBits) noexcept :
			pygmalion::node<descriptor_search, node>(parent, moveBits)
		{
		}
		constexpr static depthType nullMoveReduction_Implementation(const size_t depthRemaining) noexcept
		{
			return depthType(2) + depthRemaining / depthType(4);
		}
		bool nullMoveAllowed_Implementation() const noexcept
		{
			const squaresType pieces{ this->stack().position().pieceOccupancy(knight) | this->stack().position().pieceOccupancy(bishop) | this->stack().position().pieceOccupancy(rook) | this->stack().position().pieceOccupancy(queen) };
			const squaresType playerPieces{ pieces & this->stack().position().playerOccupancy(this->stack().position().movingPlayer()) };
			return playerPieces != squaresType::none();
		}
		constexpr static scoreType futilityMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
		{
			switch (depthRemaining)
			{
			case 0:
				if ((stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer())) & (stack.movingPlayer() == whitePlayer ? rank7 : rank2))
					return static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange;
				else
					return evaluatorType::MaxPositionChange;
			case 1:
				if ((stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer())) & (stack.movingPlayer() == whitePlayer ? rank7 : rank2))
					return static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
				else
					return evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
			default:
				assert(false);
				return scoreType::zero();
			}
		}
		constexpr static scoreType futilityGlobalMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
		{
			switch (depthRemaining)
			{
			case 0:
				if ((stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer())) & (stack.movingPlayer() == whitePlayer ? rank7 : rank2))
				{
					if (stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) + static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange;
					if (stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) + static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange;
					if (stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) + static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange;
					if (stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) + static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange;
					if (stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange;
					return static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange;
				}
				else
				{
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
			case 1:
				if ((stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer())) & (stack.movingPlayer() == whitePlayer ? rank7 : rank2))
				{
					if (stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) + static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
					if (stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) + static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
					if (stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) + static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
					if (stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) + static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
					if (stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
					return static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
				}
				else
				{
					if (stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
					if (stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
					if (stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
					if (stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
					if (stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()))
						return static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
					return evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange;
				}
			default:
				assert(false);
				return scoreType::zero();
			}
		}
		scoreType moveFutilityValue_Implementation(const movebitsType& move) const noexcept
		{
			if (motorType::move().isCapture(move))
			{
				const squareType captureSquare{ motorType::move().captureSquare(this->stack().position(),move) };
				const pieceType capturedPiece{ this->stack().position().getPiece(captureSquare) };
				const scoreType victimValue{ static_cast<scoreType>(boardType::materialValue(capturedPiece, whitePlayer)) };
				if (motorType::move().isPromotion(move))
				{
					const pieceType promotedPiece{ motorType::move().promotedPiece(move) };
					const scoreType promotionValue{ static_cast<scoreType>(boardType::materialValue(promotedPiece, whitePlayer)) };
					return victimValue + promotionValue;
				}
				else
					return victimValue;
			}
			else
			{
				if (motorType::move().isPromotion(move))
				{
					const pieceType promotedPiece{ motorType::move().promotedPiece(move) };
					const scoreType promotionValue{ static_cast<scoreType>(boardType::materialValue(promotedPiece, whitePlayer)) };
					return promotionValue;
				}
				else
					return scoreType::zero();
			}
		}
	};
}