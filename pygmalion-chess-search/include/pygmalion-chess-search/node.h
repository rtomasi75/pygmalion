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
		constexpr node(const node& parent, const movebitsType moveBits) noexcept :
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
			return (playerPieces != squaresType::none()) && !this->stack().isCheck();
		}
		bool pruningAllowed_Implementation() const noexcept
		{
			return !this->stack().isCheck();
		}
	};
}