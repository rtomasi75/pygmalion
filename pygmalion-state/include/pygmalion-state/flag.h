namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class flag :
		public enumeration<DESCRIPTION_STATE::countFlags, DESCRIPTION_STATE::countHashBits, flag<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countFlags, DESCRIPTION_STATE::countHashBits, flag<DESCRIPTION_STATE>>;
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
		constexpr flagsType operator|(const flag other) const noexcept
		{
			return static_cast<flagsType>(*this) | flagsType(other);
		}
		constexpr operator flagsType() const noexcept
		{
			flagsType f{ flagsType(0) };
			f.set(*this);
			return f;
		}
	};
}