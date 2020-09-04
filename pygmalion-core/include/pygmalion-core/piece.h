namespace pygmalion
{
	template<typename DESCRIPTION_BOARD>
	class piece :
		public enumeration<DESCRIPTION_BOARD::countPieces, piece<DESCRIPTION_BOARD>>,
		public DESCRIPTION_BOARD
	{
	public:
		using descriptorBoard = DESCRIPTION_BOARD;
#include "include_board.h"	
		constexpr piece(const piece&) noexcept = default;
		constexpr piece(piece&&) noexcept = default;
		constexpr piece() noexcept :
			enumeration<countPieces, piece>()
		{

		}
		constexpr piece(const typename enumeration<countPieces, piece>::baseType value) noexcept :
			enumeration<countPieces, piece>(value)
		{
		}
		constexpr piece(const typename enumeration<countPieces, piece>::valueType value) noexcept :
			enumeration<countPieces, piece>(value)
		{
		}
		constexpr piece& operator=(piece&&) noexcept = default;
		constexpr piece& operator=(const piece&) noexcept = default;
	};
}