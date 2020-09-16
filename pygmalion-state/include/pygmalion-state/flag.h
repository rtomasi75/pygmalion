namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class flag :
		public enumeration<DESCRIPTION_STATE::countFlags, flag<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countFlags, flag<DESCRIPTION_STATE>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		constexpr flag(const flag&) noexcept = default;
		constexpr flag(flag&&) noexcept = default;
		constexpr flag() noexcept :
			parentType()
		{

		}
		constexpr flag(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		constexpr flag(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		constexpr flag& operator=(flag&&) noexcept = default;
		constexpr flag& operator=(const flag&) noexcept = default;
	};
}