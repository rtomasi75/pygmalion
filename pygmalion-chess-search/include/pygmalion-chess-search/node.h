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
		static bool nullMoveAllowed_Implementation(const stackType& stack) noexcept
		{
			return ((stack.position().pieceOccupancy(knight) | stack.position().pieceOccupancy(bishop) | stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen)) == squaresType::none()) && !stack.isCheck();
		}
	};
}