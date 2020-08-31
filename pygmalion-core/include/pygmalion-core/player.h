namespace pygmalion
{
	template<typename DESCRIPTION_BOARD>
	class player :
		public enumeration<DESCRIPTION_BOARD::countPlayers, player<DESCRIPTION_BOARD>>,
		public base_board<DESCRIPTION_BOARD>
	{
	public:
		using descriptorBoard = DESCRIPTION_BOARD;
#include "include_board.h"	
		constexpr player(const player&) noexcept = default;
		constexpr player(player&&) noexcept = default;
		constexpr player() noexcept :
			enumeration<countPlayers, player>()
		{

		}
		constexpr player(const typename enumeration<countPlayers, player>::baseType value) noexcept :
			enumeration<countPlayers, player>(value)
		{
		}
		constexpr player(const typename enumeration<countPlayers, player>::valueType value) noexcept :
			enumeration<countPlayers, player>(value)
		{
		}
		constexpr player& operator=(player&&) noexcept = default;
		constexpr player& operator=(const player&) noexcept = default;
	};
}