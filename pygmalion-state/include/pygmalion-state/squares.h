namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class squares :
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
		using bitsType = uint_t<countSquares, false>;
	private:
		bitsType m_Bits;
		constexpr static size_t bit(const squareType square) noexcept
		{
			return static_cast<typename squareType::baseType>(square);
		}
		constexpr static bitsType fromFile(const fileType file) noexcept
		{
			bitsType bits{ bitsType::zero() };
			for (const rankType rank : rankType::range)
				bits.set(bit(rank & file));
			return bits;
		}
		constexpr static bitsType fromRank(const rankType rank) noexcept
		{
			bitsType bits{ bitsType::zero() };
			for (const fileType file : fileType::range)
				bits.set(bit(file & rank));
			return bits;
		}
		constexpr static const bitsType firstFileBits{ fromFile(0) };
		constexpr static const bitsType lastFileBits{ fromFile(countFiles - 1) };
		constexpr static const bitsType firstRankBits{ fromRank(0) };
		constexpr static const bitsType lastRankBits{ fromRank(countRanks - 1) };
	public:
		PYGMALION_INLINE squareType first() const noexcept
		{
			size_t bit;
#if defined(_DEBUG)
			const bool bResult{ m_Bits.bitscanForward(bit) };
			PYGMALION_ASSERT(bResult);
#else
			m_Bits.bitscanForward(bit);
#endif
			return static_cast<squareType>(bit);
		}
		PYGMALION_INLINE squareType last() const noexcept
		{
			size_t bit;
#if defined(_DEBUG)
			const bool bResult{ m_Bits.bitscanReverse(bit) };
			PYGMALION_ASSERT(bResult);
#else
			m_Bits.bitscanReverse(bit);
#endif
			return static_cast<squareType>(bit);
		}
		PYGMALION_INLINE const bitsType& bits() const noexcept
		{
			return m_Bits;
		}
		constexpr static squares none()
		{
			return squares(bitsType::zero());
		}
		constexpr static squares all()
		{
			return ~none();
		}
		PYGMALION_INLINE constexpr squares right() const noexcept
		{
			return static_cast<squares>((this->m_Bits & (~lastFileBits)) << 1);
		}
		PYGMALION_INLINE constexpr squares left() const noexcept
		{
			return static_cast<squares>((this->m_Bits & (~firstFileBits)) >> 1);
		}
		PYGMALION_INLINE constexpr squares down() const noexcept
		{
			return static_cast<squares>(this->m_Bits >> countFiles);
		}
		PYGMALION_INLINE constexpr squares up() const noexcept
		{
			return static_cast<squares>(this->m_Bits << countFiles);
		}
		PYGMALION_INLINE constexpr squares downRight() const noexcept
		{
			return down().right();
		}
		PYGMALION_INLINE constexpr squares upRight() const noexcept
		{
			return up().right();
		}
		PYGMALION_INLINE constexpr squares downLeft() const noexcept
		{
			return left().down();
		}
		PYGMALION_INLINE constexpr squares upLeft() const noexcept
		{
			return left().up();
		}
		PYGMALION_INLINE constexpr squares upUpLeft() const noexcept
		{
			return up().upLeft();
		}
		PYGMALION_INLINE constexpr squares upUpRight() const noexcept
		{
			return up().upRight();
		}
		PYGMALION_INLINE constexpr squares downDownLeft() const noexcept
		{
			return down().downLeft();
		}
		PYGMALION_INLINE constexpr squares downDownRight() const noexcept
		{
			return down().downRight();
		}
		PYGMALION_INLINE constexpr squares upLeftLeft() const noexcept
		{
			return upLeft().left();
		}
		PYGMALION_INLINE constexpr squares downLeftLeft() const noexcept
		{
			return downLeft().left();
		}
		PYGMALION_INLINE constexpr squares upRightRight() const noexcept
		{
			return upRight().right();
		}
		PYGMALION_INLINE constexpr squares downRightRight() const noexcept
		{
			return downRight().right();
		}
		PYGMALION_INLINE constexpr explicit squares(const bitsType& bits) noexcept :
			m_Bits{ bits }
		{

		}
		PYGMALION_INLINE constexpr explicit operator bitsType() const noexcept
		{
			return m_Bits;
		}
		PYGMALION_INLINE constexpr squares operator*(const bool value) const noexcept
		{
			const bitsType bits{ m_Bits };
			const bitsType valueBits{ bitsType(static_cast<unsigned int>(value)) };
			return squares(bits * valueBits);
		}
		PYGMALION_INLINE constexpr squares operator|(const squares other) const noexcept
		{
			const bitsType bits{ m_Bits | other.m_Bits };
			return squares(std::move(bits));
		}
		PYGMALION_INLINE constexpr squares operator-(const squares other) const noexcept
		{
			return squares(m_Bits & ~other.m_Bits);
		}
		PYGMALION_INLINE constexpr squares operator&(const squares other) const noexcept
		{
			return squares(m_Bits & other.m_Bits);
		}
		PYGMALION_INLINE constexpr squares operator^(const squares other) const noexcept
		{
			return squares(m_Bits ^ other.m_Bits);
		}
		PYGMALION_INLINE constexpr squares operator~() const noexcept
		{
			return squares(~m_Bits);
		}
		PYGMALION_INLINE constexpr squares& operator|=(const squares other) noexcept
		{
			m_Bits |= other.m_Bits;
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator-=(const squares other) noexcept
		{
			m_Bits &= ~other.m_Bits;
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator&=(const squares other) noexcept
		{
			m_Bits &= other.m_Bits;
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator^=(const squares other) noexcept
		{
			m_Bits ^= other.m_Bits;
			return *this;
		}
		PYGMALION_INLINE constexpr bool operator==(const squares other) const noexcept
		{
			return m_Bits == other.m_Bits;
		}
		PYGMALION_INLINE constexpr bool operator!=(const squares other) const noexcept
		{
			return m_Bits != other.m_Bits;
		}
		PYGMALION_INLINE constexpr squares& operator|=(const squareType square) noexcept
		{
			m_Bits.set(static_cast<typename squareType::baseType>(square));
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator&=(const squareType square) noexcept
		{
			m_Bits &= bitsType::setMask(static_cast<typename squareType::baseType>(square));
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator-=(const squareType square) noexcept
		{
			m_Bits.clear(static_cast<typename squareType::baseType>(square));
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator^=(const squareType square) noexcept
		{
			m_Bits.toggle(static_cast<typename squareType::baseType>(square));
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator|=(const fileType file) noexcept
		{
			m_Bits |= squares(file);
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator&=(const fileType file) noexcept
		{
			m_Bits &= squares(file);
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator-=(const fileType file) noexcept
		{
			m_Bits &= ~squares(file);
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator^=(const fileType file) noexcept
		{
			m_Bits ^= squares(file);
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator|=(const rankType rank) noexcept
		{
			m_Bits |= squares(rank);
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator&=(const rankType rank) noexcept
		{
			m_Bits &= squares(rank);
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator-=(const rankType rank) noexcept
		{
			m_Bits &= ~squares(rank);
			return *this;
		}
		PYGMALION_INLINE constexpr squares& operator^=(const rankType rank) noexcept
		{
			m_Bits ^= squares(rank);
			return *this;
		}
		PYGMALION_INLINE constexpr squares singlePiece() const noexcept
		{
			assert((*this) != squares::none());
			return squares(m_Bits.singleBit());
		}
		PYGMALION_INLINE constexpr bool operator[](const squareType& square) const noexcept
		{
			return m_Bits[static_cast<typename squareType::baseType>(square)];
		}
		PYGMALION_INLINE constexpr auto operator[](const squareType& square) noexcept
		{
			return m_Bits[static_cast<typename squareType::baseType>(square)];
		}
		PYGMALION_INLINE constexpr operator bool() const noexcept
		{
			return static_cast<bool>(m_Bits);
		}
		PYGMALION_INLINE constexpr squares() noexcept :
			m_Bits{ bitsType::zero() }
		{

		}
		PYGMALION_INLINE constexpr squares(const rankType rank) noexcept :
			m_Bits{ firstRankBits << (rank * countFiles) }
		{
		}
		PYGMALION_INLINE constexpr squares(const fileType file) noexcept :
			m_Bits{ firstFileBits << file }
		{
		}
		PYGMALION_INLINE constexpr squares(const squareType square) noexcept :
			m_Bits{ bitsType::zero() }
		{
			m_Bits.set(square);
		}
		PYGMALION_INLINE constexpr squares(const squares&) noexcept = default;
		PYGMALION_INLINE constexpr squares(squares&&) noexcept = default;
		PYGMALION_INLINE constexpr squares& operator=(const squares&) = default;
		PYGMALION_INLINE constexpr squares& operator=(squares&&) = default;
		PYGMALION_INLINE ~squares() noexcept = default;
		PYGMALION_INLINE size_t count() const noexcept
		{
			return m_Bits.populationCount();
		}
		class iterator
		{
			friend class squares;
		public:
			using value_type = squareType;
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
				return static_cast<squareType>(*m_Iterator);
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
		class counterType
		{
			friend class squares;
		private:
			typename bitsType::counterType m_Counter;
			PYGMALION_INLINE constexpr counterType(const squares& it) noexcept :
				m_Counter{ it.counter() }
			{
			}
		public:
			PYGMALION_INLINE constexpr counterType(const counterType&) noexcept = default;
			PYGMALION_INLINE ~counterType() noexcept = default;
			PYGMALION_INLINE constexpr bool next() noexcept
			{
				return m_Counter.next();
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
		PYGMALION_INLINE constexpr auto counter() const noexcept
		{
			return counterType(*this);
		}
		template<typename LAMBDA>
		PYGMALION_INLINE constexpr void foreach(const LAMBDA& lambda) const noexcept
		{
			m_Bits.foreach([lambda](const size_t index) {lambda(static_cast<squareType>(index)); });
		}
	};

	template<typename DESCRIPTION_STATE>
	std::ostream& operator<<(std::ostream& str, const squares<DESCRIPTION_STATE>& squares) noexcept
	{
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
		for (const auto r : rankType::range)
		{
			const rankType rank{ -r };
			for (const auto file : fileType::range)
			{
				const squareType sq{ rank & file };
				if (squares[sq])
					str << "#";
				else
					str << ".";
			}
			str << std::endl;
		}
		return str;
	}
}