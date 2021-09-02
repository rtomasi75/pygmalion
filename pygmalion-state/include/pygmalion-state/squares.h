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
		constexpr static squares none()
		{
			return squares(bitsType::zero());
		}
		constexpr static squares all()
		{
			return ~none();
		}
		constexpr squares right() const noexcept
		{
			return static_cast<squares>((this->m_Bits & (~lastFileBits)) << 1);
		}
		constexpr squares left() const noexcept
		{
			return static_cast<squares>((this->m_Bits & (~firstFileBits)) >> 1);
		}
		constexpr squares down() const noexcept
		{
			return static_cast<squares>(this->m_Bits >> countFiles);
		}
		constexpr squares up() const noexcept
		{
			return static_cast<squares>(this->m_Bits << countFiles);
		}
		constexpr squares downRight() const noexcept
		{
			return down().right();
		}
		constexpr squares upRight() const noexcept
		{
			return up().right();
		}
		constexpr squares downLeft() const noexcept
		{
			return left().down();
		}
		constexpr squares upLeft() const noexcept
		{
			return left().up();
		}
		constexpr squares upUpLeft() const noexcept
		{
			return up().upLeft();
		}
		constexpr squares upUpRight() const noexcept
		{
			return up().upRight();
		}
		constexpr squares downDownLeft() const noexcept
		{
			return down().downLeft();
		}
		constexpr squares downDownRight() const noexcept
		{
			return down().downRight();
		}
		constexpr squares upLeftLeft() const noexcept
		{
			return upLeft().left();
		}
		constexpr squares downLeftLeft() const noexcept
		{
			return downLeft().left();
		}
		constexpr squares upRightRight() const noexcept
		{
			return upRight().right();
		}
		constexpr squares downRightRight() const noexcept
		{
			return downRight().right();
		}
		constexpr explicit squares(const bitsType bits) noexcept :
			m_Bits{ bits }
		{

		}
		constexpr explicit operator bitsType() const noexcept
		{
			return m_Bits;
		}
		constexpr squares operator|(const squares other) const noexcept
		{
			const bitsType bits{ m_Bits | other.m_Bits };
			return squares(std::move(bits));
		}
		constexpr squares operator-(const squares other) const noexcept
		{
			return squares(m_Bits & ~other.m_Bits);
		}
		constexpr squares operator&(const squares other) const noexcept
		{
			return squares(m_Bits & other.m_Bits);
		}
		constexpr squares operator^(const squares other) const noexcept
		{
			return squares(m_Bits ^ other.m_Bits);
		}
		constexpr squares operator~() const noexcept
		{
			return squares(~m_Bits);
		}
		constexpr squares& operator|=(const squares other) noexcept
		{
			m_Bits |= other.m_Bits;
			return *this;
		}
		constexpr squares& operator-=(const squares other) noexcept
		{
			m_Bits &= ~other.m_Bits;
			return *this;
		}
		constexpr squares& operator&=(const squares other) noexcept
		{
			m_Bits &= other.m_Bits;
			return *this;
		}
		constexpr squares& operator^=(const squares other) noexcept
		{
			m_Bits ^= other.m_Bits;
			return *this;
		}
		constexpr bool operator==(const squares other) const noexcept
		{
			return m_Bits == other.m_Bits;
		}
		constexpr bool operator!=(const squares other) const noexcept
		{
			return m_Bits != other.m_Bits;
		}
		constexpr squares& operator|=(const squareType square) noexcept
		{
			m_Bits.set(static_cast<typename squareType::baseType>(square));
			return *this;
		}
		constexpr squares& operator&=(const squareType square) noexcept
		{
			m_Bits &= bitsType::setMask(static_cast<typename squareType::baseType>(square));
			return *this;
		}
		constexpr squares& operator-=(const squareType square) noexcept
		{
			m_Bits.clear(static_cast<typename squareType::baseType>(square));
			return *this;
		}
		constexpr squares& operator^=(const squareType square) noexcept
		{
			m_Bits.toggle(static_cast<typename squareType::baseType>(square));
			return *this;
		}
		constexpr squares& operator|=(const fileType file) noexcept
		{
			m_Bits |= squares(file);
			return *this;
		}
		constexpr squares& operator&=(const fileType file) noexcept
		{
			m_Bits &= squares(file);
			return *this;
		}
		constexpr squares& operator-=(const fileType file) noexcept
		{
			m_Bits &= ~squares(file);
			return *this;
		}
		constexpr squares& operator^=(const fileType file) noexcept
		{
			m_Bits ^= squares(file);
			return *this;
		}
		constexpr squares& operator|=(const rankType rank) noexcept
		{
			m_Bits |= squares(rank);
			return *this;
		}
		constexpr squares& operator&=(const rankType rank) noexcept
		{
			m_Bits &= squares(rank);
			return *this;
		}
		constexpr squares& operator-=(const rankType rank) noexcept
		{
			m_Bits &= ~squares(rank);
			return *this;
		}
		constexpr squares& operator^=(const rankType rank) noexcept
		{
			m_Bits ^= squares(rank);
			return *this;
		}
		constexpr squares singlePiece() const noexcept
		{
			assert((*this) != squares::none());
			return squares(m_Bits & m_Bits.twosComplement());
		}
		constexpr bool operator[](const squareType square) const noexcept
		{
			return m_Bits[static_cast<typename squareType::baseType>(square)];
		}
		constexpr auto operator[](const squareType square) noexcept
		{
			return m_Bits[static_cast<typename squareType::baseType>(square)];
		}
		constexpr operator bool() const noexcept
		{
			return static_cast<bool>(m_Bits);
		}
		constexpr squares() noexcept :
			m_Bits{ bitsType::zero() }
		{

		}
		constexpr squares(const rankType rank) noexcept :
			m_Bits{ firstRankBits << (rank * countFiles) }
		{
		}
		constexpr squares(const fileType file) noexcept :
			m_Bits{ firstFileBits << file }
		{
		}
		constexpr squares(const squareType square) noexcept :
			m_Bits{ bitsType::zero() }
		{
			m_Bits.set(square);
		}
		constexpr squares(const squares&) noexcept = default;
		constexpr squares(squares&&) noexcept = default;
		constexpr squares& operator=(const squares&) = default;
		constexpr squares& operator=(squares&&) = default;
		~squares() noexcept = default;
		size_t count() const noexcept
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
				return static_cast<squareType>(*m_Iterator);
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

	template<typename DESCRIPTION_STATE>
	std::ostream& operator<<(std::ostream& str, const squares<DESCRIPTION_STATE>& squares) noexcept
	{
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
		using bitsType = uint_t<countSquares, false>;
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