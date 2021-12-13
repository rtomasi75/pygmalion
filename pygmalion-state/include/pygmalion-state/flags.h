namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class flags :
		public set<typename DESCRIPTION_STATE::flagType, flags<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
	public:
		PYGMALION_INLINE constexpr explicit flags(const typename set<typename DESCRIPTION_STATE::flagType, flags<DESCRIPTION_STATE>>::bitsType& bits) noexcept :
			set<typename DESCRIPTION_STATE::flagType, flags<DESCRIPTION_STATE>>(bits)
		{

		}
		PYGMALION_INLINE constexpr flags(const flags&) noexcept = default;
		PYGMALION_INLINE constexpr flags(const flagType flag) noexcept :
			set<typename descriptorState::flagType, flags<descriptorState>>(flag)
		{

		}
		PYGMALION_INLINE constexpr flags(flags&&) noexcept = default;
		PYGMALION_INLINE constexpr flags& operator=(const flags&) = default;
		PYGMALION_INLINE constexpr flags& operator=(flags&&) = default;
		PYGMALION_INLINE ~flags() noexcept = default;
	};
}