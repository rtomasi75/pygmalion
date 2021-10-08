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
		constexpr static bool enableRange(const size_t first, const size_t last) noexcept
		{
			return (first <= last) && (last < countFlags);
		}
	public:
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<flags::enableRange(FIRST, LAST)>::type>
		PYGMALION_INLINE constexpr void clearRange() noexcept
		{
			m_Bits.template clearBits<FIRST, 1 + LAST - FIRST>();
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<flags::enableRange(FIRST, LAST)>::type>
		PYGMALION_INLINE constexpr void setRange() noexcept
		{
			m_Bits.template setBits<FIRST, 1 + LAST - FIRST>();
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<flags::enableRange(FIRST, LAST)>::type>
		PYGMALION_INLINE constexpr uint_t<1 + LAST - FIRST, false> extractRange() const noexcept
		{
			return m_Bits.template extractBits<FIRST, 1 + LAST - FIRST>();
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<flags::enableRange(FIRST, LAST)>::type>
		PYGMALION_INLINE constexpr void storeRange(const uint_t<1 + LAST - FIRST, false>& flags) noexcept
		{
			m_Bits.template storeBits<FIRST, 1 + LAST - FIRST>(flags);
		}
		PYGMALION_INLINE constexpr explicit flags(const bitsType& bits) noexcept :
			m_Bits{ bits }
		{

		}
		PYGMALION_INLINE constexpr explicit operator bitsType()
		{
			return m_Bits;
		}
		PYGMALION_INLINE constexpr void toggle(const flagType flag) noexcept
		{
			m_Bits.toggle(flag);
		}
		PYGMALION_INLINE constexpr void set(const flagType flag) noexcept
		{
			m_Bits.set(flag);
		}
		PYGMALION_INLINE constexpr void clear(const flagType flag) noexcept
		{
			m_Bits.clear(flag);
		}
		PYGMALION_INLINE constexpr bool operator[](const flagType flag) const noexcept
		{
			return m_Bits.test(flag);
		}
		PYGMALION_INLINE constexpr flags operator|(const flags other) const noexcept
		{
			return flags(m_Bits | other.m_Bits);
		}
		PYGMALION_INLINE constexpr flags operator-(const flags other) const noexcept
		{
			return flags(m_Bits & ~other.m_Bits);
		}
		PYGMALION_INLINE constexpr flags operator&(const flags other) const noexcept
		{
			return flags(m_Bits & other.m_Bits);
		}
		PYGMALION_INLINE constexpr flags operator^(const flags other) const noexcept
		{
			return flags(m_Bits ^ other.m_Bits);
		}
		PYGMALION_INLINE constexpr flags operator~() const noexcept
		{
			return flags(~m_Bits);
		}
		PYGMALION_INLINE constexpr flags& operator|=(const flags other) noexcept
		{
			m_Bits |= other.m_Bits;
			return *this;
		}
		PYGMALION_INLINE constexpr flags& operator-=(const flags other) noexcept
		{
			m_Bits &= ~other.m_Bits;
			return *this;
		}
		PYGMALION_INLINE constexpr flags& operator&=(const flags other) noexcept
		{
			m_Bits &= other.m_Bits;
			return *this;
		}
		PYGMALION_INLINE constexpr flags& operator^=(const flags other) noexcept
		{
			m_Bits ^= other.m_Bits;
			return *this;
		}
		PYGMALION_INLINE constexpr bool operator==(const flags other) const noexcept
		{
			return m_Bits == other.m_Bits;
		}
		PYGMALION_INLINE constexpr bool operator!=(const flags other) const noexcept
		{
			return m_Bits != other.m_Bits;
		}
		PYGMALION_INLINE constexpr squaresType& operator|=(const flagType flag) noexcept
		{
			m_Bits.set(static_cast<typename flagType::baseType>(flag));
			return *this;
		}
		PYGMALION_INLINE constexpr squaresType& operator&=(const flagType flag) noexcept
		{
			m_Bits &= bitsType::setMask(static_cast<typename flagType::baseType>(flag));
			return *this;
		}
		PYGMALION_INLINE constexpr squaresType& operator-=(const flagType flag) noexcept
		{
			m_Bits.clear(static_cast<typename flagType::baseType>(flag));
			return *this;
		}
		PYGMALION_INLINE constexpr squaresType& operator^=(const flagType& flag) noexcept
		{
			m_Bits.toggle(static_cast<typename flagType::baseType>(flag));
			return *this;
		}
		PYGMALION_INLINE constexpr flags(const flags&) noexcept = default;
		PYGMALION_INLINE constexpr flags(flags&&) noexcept = default;
		PYGMALION_INLINE constexpr flags& operator=(const flags&) = default;
		PYGMALION_INLINE constexpr flags& operator=(flags&&) = default;
		PYGMALION_INLINE constexpr void clear() noexcept
		{
			m_Bits = bitsType::zero();
		}
		PYGMALION_INLINE ~flags() noexcept = default;
		PYGMALION_INLINE constexpr bitsType bits() const noexcept
		{
			return m_Bits;
		}
		class iterator
		{
			friend class flags;
		public:
			using value_type = flagType;
		private:
			typename bitsType::iterator m_Iterator;
			PYGMALION_INLINE constexpr iterator(const typename bitsType::iterator& it) noexcept :
				m_Iterator{ it }
			{
			}
		public:
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::input_iterator_tag;
			PYGMALION_INLINE constexpr iterator(const iterator&) noexcept = default;
			PYGMALION_INLINE ~iterator() noexcept = default;
			PYGMALION_INLINE constexpr iterator&& operator++(int) noexcept
			{
				iterator ret(m_Iterator);
				++(*this);
				return std::move(ret);
			}
			PYGMALION_INLINE constexpr iterator& operator++() noexcept
			{
				++m_Iterator;
				return *this;
			}
			PYGMALION_INLINE constexpr value_type operator*() const noexcept
			{
				return static_cast<flagType>(*m_Iterator);
			}
			PYGMALION_INLINE constexpr bool operator==(const iterator& other) const noexcept
			{
				return m_Iterator == other.m_Iterator;
			}
			PYGMALION_INLINE constexpr bool operator!=(const iterator& other) const noexcept
			{
				return m_Iterator != other.m_Iterator;
			}
		};
		PYGMALION_INLINE constexpr auto begin() const noexcept
		{
			return iterator(m_Bits.begin());
		}
		PYGMALION_INLINE constexpr auto end() const noexcept
		{
			return iterator(m_Bits.end());
		}
	};
}