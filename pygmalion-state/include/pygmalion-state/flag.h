namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class flag :
		public enumeration<DESCRIPTION_STATE::countFlags, DESCRIPTION_STATE::countHashBits, flag<DESCRIPTION_STATE>, set<flag<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::flagsType>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countFlags, DESCRIPTION_STATE::countHashBits, flag<DESCRIPTION_STATE>, set<flag<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::flagsType>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr flag(const flag&) noexcept = default;
		PYGMALION_INLINE constexpr flag(flag&&) noexcept = default;
		PYGMALION_INLINE constexpr flag() noexcept :
			parentType()
		{

		}
		PYGMALION_INLINE constexpr flag(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr flag(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr flag& operator=(flag&&) noexcept = default;
		PYGMALION_INLINE constexpr flag& operator=(const flag&) noexcept = default;
		PYGMALION_INLINE constexpr flagsType operator|(const flag other) const noexcept
		{
			return static_cast<flagsType>(*this) | flagsType(other);
		}
		PYGMALION_INLINE constexpr operator flagsType() const noexcept
		{
			return flagsType(*static_cast<flagsType>(this));
		}
	};
}