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
		constexpr static bool futilityPruningEnabled_Implementation(const size_t depthRemaining) noexcept
		{
			return false;
		}
		constexpr static scoreType futilityMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
		{
			assert(false);
			return scoreType::zero();
		}
		constexpr static scoreType futilityGlobalMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
		{
			assert(false);
			return scoreType::zero();
		}
		constexpr static depthType nullMoveReduction_Implementation(const size_t depthRemaining) noexcept
		{
			return 0;
		}
		constexpr bool nullMoveAllowed_Implementation() const noexcept
		{
			return false;
		}
		constexpr scoreType tacticalMoveValue_Implementation(const movebitsType& move) const noexcept
		{
			assert(false);
			return scoreType::zero();
		}
	};
}