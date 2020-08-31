namespace pygmalion
{
	template<typename DESCRIPTION_BOARD>
	class squares :
		public base_board<DESCRIPTION_BOARD>
	{
	public:
		using descriptorBoard = DESCRIPTION_BOARD;
#include "include_board.h"
		using bitsType = bitfield<countSquares>;
		using bitType = typename bitsType::bitType;
	private:
		bitsType m_Bits;
		constexpr static bitType bit(const squareType square) noexcept
		{
			return square;
		}
		constexpr static bitsType fromFile(const fileType file) noexcept
		{
			bitsType bits{ bitsType::empty() };
			for (const auto rank : rankType::range)
				bits.setBit(bit(squareType::fromRankFile(rank, file)));
			return bits;
		}
		constexpr static bitsType fromRank(const rankType rank) noexcept
		{
			bitsType bits{ bitsType::empty() };
			for (const auto file : fileType::range)
				bits.setBit(squareType::fromRankFile(rank, file));
			return bits;
		}
		constexpr static const bitsType firstFileBits{ fromFile(0) };
		constexpr static const bitsType lastFileBits{ fromFile(countFiles - 1) };
		constexpr static const bitsType firstRankBits{ fromRank(0) };
		constexpr static const bitsType lastRankBits{ fromRank(countFiles - 1) };
		constexpr static const bitsType notFirstFileBits{ ~firstFileBits };
		constexpr static const bitsType notLastFileBits{ ~lastFileBits };
		constexpr static const bitsType notFirstRankBits{ ~firstRankBits };
		constexpr static const bitsType notLastRankBits{ ~lastRankBits };
	public:
		constexpr static squares none()
		{
			return squares(bitsType::empty());
		}
		constexpr static squares right(const squares sqs) noexcept
		{
			return static_cast<squares>((sqs.m_Bits & notLastFileBits) << 1);
		}
		constexpr static squares left(const squares sqs) noexcept
		{
			return static_cast<squares>((sqs.m_Bits & notFirstFileBits) >> 1);
		}
		constexpr static squares down(const squares sqs) noexcept
		{
			return static_cast<squares>((sqs.m_Bits & notFirstRankBits) >> 8);
		}
		constexpr static squares up(const squares sqs) noexcept
		{
			return static_cast<squares>((sqs.m_Bits & notLastRankBits) << 8);
		}
		constexpr static squares downRight(const squares sqs) noexcept
		{
			return static_cast<squares>((sqs.m_Bits & notLastFileBits) >> 7);
		}
		constexpr static squares upRight(const squares sqs) noexcept
		{
			return static_cast<squares>((sqs.m_Bits & notLastFileBits) << 9);
		}
		constexpr static squares downLeft(const squares sqs) noexcept
		{
			return static_cast<squares>((sqs.m_Bits & notFirstFileBits) >> 9);
		}
		constexpr static squares upLeft(const squares sqs) noexcept
		{
			return static_cast<squares>((sqs.m_Bits & notFirstFileBits) << 7);
		}
		constexpr static squares upUpLeft(const squares sqs) noexcept
		{
			return up(upLeft(sqs));
		}
		constexpr static squares upUpRight(const squares sqs) noexcept
		{
			return up(upRight(sqs));
		}
		constexpr static squares downDownLeft(const squares sqs) noexcept
		{
			return down(downLeft(sqs));
		}
		constexpr static squares downDownRight(const squares sqs) noexcept
		{
			return down(downRight(sqs));
		}
		constexpr static squares upLeftLeft(const squares sqs) noexcept
		{
			return upLeft(left(sqs));
		}
		constexpr static squares downLeftLeft(const squares sqs) noexcept
		{
			return downLeft(left(sqs));
		}
		constexpr static squares upRightRight(const squares sqs) noexcept
		{
			return upRight(right(sqs));
		}
		constexpr static squares downRightRight(const squares sqs) noexcept
		{
			return downRight(right(sqs));
		}
		constexpr explicit squares(const bitsType& bits) noexcept :
			m_Bits{ bits }
		{

		}
		constexpr explicit operator bitsType()
		{
			return m_Bits;
		}
		constexpr squares operator|(const squares other) const noexcept
		{
			return squares(m_Bits | other.m_Bits);
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
		constexpr squares& operator+=(const squareType square) noexcept
		{
			m_Bits.setBit(square);
			return *this;
		}
		constexpr squares& operator-=(const squareType square) noexcept
		{
			m_Bits.clearBit(square);
			return *this;
		}
		constexpr bool operator[](const squareType square) const noexcept
		{
			return m_Bits[square];
		}
		constexpr operator bool() const noexcept
		{
			return m_Bits;
		}
		constexpr squares() noexcept :
			m_Bits{ bitsType::empty() }
		{

		}
		constexpr squares(const squares&) noexcept = default;
		constexpr squares(squares&&) noexcept = default;
		constexpr squares& operator=(const squares&) = default;
		constexpr squares& operator=(squares&&) = default;
		~squares() noexcept = default;
		auto count() const noexcept
		{
			return m_Bits.populationCount();
		}
	};
}