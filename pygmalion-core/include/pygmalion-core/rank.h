namespace pygmalion
{
	template<typename DESCRIPTION_BOARD>
	class rank :
		public enumeration<DESCRIPTION_BOARD::countRanks, rank<DESCRIPTION_BOARD>>,
		public base_board<DESCRIPTION_BOARD>
	{
	public:
		using descriptorBoard = DESCRIPTION_BOARD;
#include "include_board.h"	
		constexpr rank(const rank&) noexcept = default;
		constexpr rank(rank&&) noexcept = default;
		constexpr rank() noexcept :
			enumeration<countRanks, rank>()
		{

		}
		constexpr rank(const typename enumeration<countRanks, rank>::baseType value) noexcept :
			enumeration<countRanks, rank>(value)
		{
		}
		constexpr rank(const typename enumeration<countRanks, rank>::valueType value) noexcept :
			enumeration<countRanks, rank>(value)
		{
		}
		constexpr rank& operator=(rank&&) noexcept = default;
		constexpr rank& operator=(const rank&) noexcept = default;
		constexpr rank operator-() const noexcept
		{
			return countRanks - (*this);
		}
		constexpr squareType operator&(const fileType file) const noexcept
		{
			return squareType::fromRankFile(*this, file);
		}
	};
}