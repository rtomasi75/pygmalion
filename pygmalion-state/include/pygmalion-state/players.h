namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class players :
		public set<typename DESCRIPTION_STATE::playerType, players<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr players(const typename set<typename DESCRIPTION_STATE::playerType, players<DESCRIPTION_STATE>>::bitsType& bits) noexcept :
			set<typename DESCRIPTION_STATE::playerType, players<DESCRIPTION_STATE>>(bits)
		{

		}
		PYGMALION_INLINE constexpr players(typename set<typename DESCRIPTION_STATE::playerType, players<DESCRIPTION_STATE>>::bitsType&& bits) noexcept :
			set<typename DESCRIPTION_STATE::playerType, players<DESCRIPTION_STATE>>(std::move(bits))
		{

		}
		PYGMALION_INLINE constexpr players(const players&) noexcept = default;
		PYGMALION_INLINE constexpr players(players&&) noexcept = default;
		PYGMALION_INLINE constexpr players() noexcept = default;
		PYGMALION_INLINE ~players() noexcept = default;
		PYGMALION_INLINE constexpr players& operator=(players&&) noexcept = default;
		PYGMALION_INLINE constexpr players& operator=(const players&) noexcept = default;
	};
}