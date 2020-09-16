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
		constexpr explicit flags(const bitsType bits) noexcept :
			m_Bits{ bits }
		{

		}
		constexpr explicit operator bitsType()
		{
			return m_Bits;
		}
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
		class iterator
		{
			friend class flags;
		public:
			using value_type = flagType;
		private:
			typename bitsType::iterator m_Iterator;
			constexpr iterator(const typename bitsType::iterator& it) noexcept :
				m_Iterator{ it }
			{
			}
		public:
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::input_iterator_tag;
			constexpr iterator(const iterator&) noexcept = default;
			~iterator() noexcept = default;
			constexpr iterator&& operator++(int) noexcept
			{
				iterator ret(m_Iterator);
				++(*this);
				return std::move(ret);
			}
			constexpr iterator& operator++() noexcept
			{
				++m_Iterator;
				return *this;
			}
			constexpr value_type operator*() const noexcept
			{
				return static_cast<flagType>(*m_Iterator);
			}
			constexpr bool operator==(const iterator& other) const noexcept
			{
				return m_Iterator == other.m_Iterator;
			}
			constexpr bool operator!=(const iterator& other) const noexcept
			{
				return m_Iterator != other.m_Iterator;
			}
		};
		constexpr auto begin() const noexcept
		{
			return iterator(m_Bits.begin());
		}
		constexpr auto end() const noexcept
		{
			return iterator(m_Bits.end());
		}
	};
}