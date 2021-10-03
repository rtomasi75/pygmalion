namespace pygmalion::tictactoe
{
	class gametree :
		public pygmalion::gametree<descriptor_search, gametree>
	{
	public:
		template<size_t PLAYER>
		class node :
			public pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>
		{
		public:
			constexpr static inline const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			using parentType = node< static_cast<size_t>(movingPlayer.previous())>;
			using childType = node< static_cast<size_t>(movingPlayer.next())>;
			node(const stackType& stack, std::atomic_bool& isRunning, heuristicsType& heuristics) noexcept :
				pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>(stack, isRunning, heuristics)
			{

			}
			node(const parentType& parent, const movebitsType moveBits) noexcept :
				pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>(parent, moveBits)
			{
			}
			constexpr static bool futilityPruningEnabled_Implementation(const size_t depthRemaining) noexcept
			{
				return false;
			}
			constexpr static scoreType futilityMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
			{
				return scoreType::zero();
			}
			constexpr static scoreType futilityGlobalMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
			{
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
			constexpr scoreType moveFutilityValue_Implementation(const movebitsType& move) const noexcept
			{
				return scoreType::zero();
			}
		};
		template<size_t PLAYER>
		using nodeType = node<PLAYER>;
	};
}