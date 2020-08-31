namespace pygmalion
{
	template<typename DESCRIPTION_BOARD>
	class square :
		public enumeration<DESCRIPTION_BOARD::countSquares, square<DESCRIPTION_BOARD>>,
		public base_board<DESCRIPTION_BOARD>
	{
	public:
		using descriptorBoard = DESCRIPTION_BOARD;
#include "include_board.h"
		constexpr static square fromRankFile(const rankType r, const fileType f) noexcept
		{
			assert(r.isValid());
			assert(f.isValid());
			return r * countFiles + f;
		}
		constexpr rankType rank() const noexcept
		{
			assert(this->isValid());
			return (*this) / countFiles;
		}
		constexpr fileType file() const noexcept
		{
			assert(this->isValid());
			return (*this) % countFiles;
		}
		constexpr square(const square&) noexcept = default;
		constexpr square(square&&) noexcept = default;
		constexpr square() noexcept :
			enumeration<countSquares, square>()
		{

		}
		constexpr square(const typename enumeration<countSquares, square>::baseType value) noexcept :
			enumeration<countSquares, square>(value)
		{
		}
		constexpr square(const typename enumeration<countSquares, square>::valueType value) noexcept :
			enumeration<countSquares, square>(value)
		{
		}
		constexpr square& operator=(square&&) noexcept = default;
		constexpr square& operator=(const square&) noexcept = default;
	};
}