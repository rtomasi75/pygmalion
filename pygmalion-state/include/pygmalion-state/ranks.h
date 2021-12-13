namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class ranks :
		public DESCRIPTION_STATE::rankType::template set<ranks<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr ranks(const typename DESCRIPTION_STATE::rankType::template set<ranks<DESCRIPTION_STATE>>::bitsType& bits) noexcept :
			DESCRIPTION_STATE::rankType::template set<ranks<DESCRIPTION_STATE>>(bits)
		{

		}
		PYGMALION_INLINE constexpr ranks(typename DESCRIPTION_STATE::rankType::template set<ranks<DESCRIPTION_STATE>>::bitsType&& bits) noexcept :
			DESCRIPTION_STATE::rankType::template set<ranks<DESCRIPTION_STATE>>(std::move(bits))
		{

		}
		PYGMALION_INLINE constexpr ranks(const ranks&) noexcept = default;
		PYGMALION_INLINE constexpr ranks(ranks&&) noexcept = default;
		PYGMALION_INLINE constexpr ranks() noexcept = default;
		PYGMALION_INLINE ~ranks() noexcept = default;
		PYGMALION_INLINE constexpr ranks& operator=(ranks&&) noexcept = default;
		PYGMALION_INLINE constexpr ranks& operator=(const ranks&) noexcept = default;
	};
}