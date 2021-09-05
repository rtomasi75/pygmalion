namespace pygmalion::tictactoe
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
			return 0;
		}
		constexpr bool nullMoveAllowed_Implementation() const noexcept
		{
			return false;
		}
		constexpr bool pruningAllowed_Implementation() const noexcept
		{
			return false;
		}
	};
}