namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class player :
		public enumeration<DESCRIPTION_STATE::countPlayers, DESCRIPTION_STATE::countHashBits, player<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countPlayers, DESCRIPTION_STATE::countHashBits, player<DESCRIPTION_STATE>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		constexpr player(const player&) noexcept = default;
		constexpr player(player&&) noexcept = default;
		constexpr player() noexcept :
			parentType()
		{

		}
		constexpr player(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		constexpr player(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		constexpr player& operator=(player&&) noexcept = default;
		constexpr player& operator=(const player&) noexcept = default;
	};
}