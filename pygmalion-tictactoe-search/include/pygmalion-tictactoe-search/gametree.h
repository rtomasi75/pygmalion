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
			using stackType = typename generatorType::template stackType<PLAYER>;
			PYGMALION_INLINE node(const stackType& stack, std::atomic_bool& isRunning, heuristicsType& heuristics, const size_t depth) noexcept :
				pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>(stack, isRunning, heuristics, depth)
			{

			}
			PYGMALION_INLINE node(const parentType& parent, const movebitsType moveBits) noexcept :
				pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>(parent, moveBits)
			{
			}
			PYGMALION_INLINE static bool futilityPruningEnabled_Implementation(const size_t depthRemaining) noexcept
			{
				return false;
			}
			PYGMALION_INLINE static scoreType futilityMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				return zero;
			}
			PYGMALION_INLINE static scoreType deltaMargin_Implementation(const stackType& stack) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				return zero;
			}
			PYGMALION_INLINE static scoreType futilityGlobalMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				return zero;
			}
			PYGMALION_INLINE static scoreType deltaGlobalMargin_Implementation(const stackType& stack) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				return zero;
			}
			PYGMALION_INLINE static depthType nullMoveReduction_Implementation(const size_t depthRemaining) noexcept
			{
				return 0;
			}
			PYGMALION_INLINE bool nullMoveAllowed_Implementation() const noexcept
			{
				return false;
			}
			PYGMALION_INLINE scoreType moveFutilityValue_Implementation(const movebitsType& move) const noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				return zero;
			}
			PYGMALION_INLINE scoreType moveDeltaValue_Implementation(const movebitsType& move) const noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				return zero;
			}
		};
		template<size_t PLAYER>
		using nodeType = node<PLAYER>;
	};
}