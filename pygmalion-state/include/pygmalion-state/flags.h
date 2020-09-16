namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class flags :
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
		using bitsType = uint_t<countFlags, false>;
	private:
		bitsType m_Bits;
	public:
		constexpr void toggle(const flagType flag) noexcept
		{
			m_Bits.toggle(flag);
		}
		constexpr void set(const flagType flag) noexcept
		{
			m_Bits.set(flag);
		}
		constexpr void clear(const flagType flag) noexcept
		{
			m_Bits.clear(flag);
		}
		constexpr bool operator[](const flagType flag) const noexcept
		{
			return m_Bits.test(flag);
		}
		constexpr explicit flags(const bitsType bits) noexcept :
			m_Bits{ bits }
		{

		}
		constexpr explicit operator bitsType()
		{
			return m_Bits;
		}
		constexpr flags operator|(const flags other) const noexcept
		{
			return flags(m_Bits | other.m_Bits);
		}
		constexpr flags operator-(const flags other) const noexcept
		{
			return flags(m_Bits & ~other.m_Bits);
		}
		constexpr flags operator&(const flags other) const noexcept
		{
			return flags(m_Bits & other.m_Bits);
		}
		constexpr flags operator^(const flags other) const noexcept
		{
			return flags(m_Bits ^ other.m_Bits);
		}
		constexpr flags operator~() const noexcept
		{
			return flags(~m_Bits);
		}
		constexpr flags& operator|=(const flags other) noexcept
		{
			m_Bits |= other.m_Bits;
			return *this;
		}
		constexpr flags& operator-=(const flags other) noexcept
		{
			m_Bits &= ~other.m_Bits;
			return *this;
		}
		constexpr flags& operator&=(const flags other) noexcept
		{
			m_Bits &= other.m_Bits;
			return *this;
		}
		constexpr flags& operator^=(const flags other) noexcept
		{
			m_Bits ^= other.m_Bits;
			return *this;
		}
		constexpr bool operator==(const flags other) const noexcept
		{
			return m_Bits == other.m_Bits;
		}
		constexpr bool operator!=(const flags other) const noexcept
		{
			return m_Bits != other.m_Bits;
		}
		constexpr squaresType& operator|=(const flagType flag) noexcept
		{
			m_Bits.set(static_cast<typename flagType::baseType>(flag));
			return *this;
		}
		constexpr squaresType& operator&=(const flagType flag) noexcept
		{
			m_Bits &= bitsType::setMask(static_cast<typename flagType::baseType>(flag));
			return *this;
		}
		constexpr squaresType& operator-=(const flagType flag) noexcept
		{
			m_Bits.clear(static_cast<typename flagType::baseType>(flag));
			return *this;
		}
		constexpr squaresType& operator^=(const flagType flag) noexcept
		{
			m_Bits.toggle(static_cast<typename flagType::baseType>(flag));
			return *this;
		}
		constexpr flags(const flags&) noexcept = default;
		constexpr flags(flags&&) noexcept = default;
		constexpr flags& operator=(const flags&) = default;
		constexpr flags& operator=(flags&&) = default;
		constexpr void clear() noexcept
		{
			m_Bits = bitsType::zero();
		}
		~flags() noexcept = default;
	};
}