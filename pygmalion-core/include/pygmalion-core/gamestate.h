namespace pygmalion
{
	template<typename DESCRIPTION_BOARD>
	class gamestate : 
		public enumeration<1 + requiredUnsignedBits(DESCRIPTION_BOARD::countPlayers), gamestate<DESCRIPTION_BOARD>>,
		public base_board<DESCRIPTION_BOARD>
	{
	public:
		using descriptorBoard = DESCRIPTION_BOARD;
#include "include_board.h"	
		constexpr gamestate(const gamestate&) noexcept = default;
		constexpr gamestate(gamestate&&) noexcept = default;
		constexpr gamestate() noexcept :
			enumeration<1 + requiredUnsignedBits(countPlayers), gamestate>()
		{

		}
		constexpr gamestate(const typename enumeration<1 + requiredUnsignedBits(countPlayers), gamestate >::baseType value) noexcept :
			enumeration<1 + requiredUnsignedBits(countPlayers), gamestate >(value)
		{
		}
		constexpr gamestate(const typename enumeration<1 + requiredUnsignedBits(countPlayers), gamestate >::valueType value) noexcept :
			enumeration<1 + requiredUnsignedBits(countPlayers), gamestate >(value)
		{
		}
		constexpr gamestate& operator=(gamestate&&) noexcept = default;
		constexpr gamestate& operator=(const gamestate&) noexcept = default;
		constexpr static gamestate open() noexcept
		{
			return static_cast<gamestate>(0);
		}
		constexpr static bool isOpen(const gamestate state) noexcept
		{
			return state == open();
		}
		constexpr static gamestate draw() noexcept
		{
			return static_cast<gamestate>(1);
		}
		constexpr static bool isDraw(const gamestate state) noexcept
		{
			return state == draw();
		}
		constexpr static gamestate loss(const playerType losingPlayer) noexcept
		{
			return static_cast<gamestate>(2 << (losingPlayer));
		}
		constexpr static bool isLoss(const gamestate state, const playerType p) noexcept
		{
			return state == loss(p);
		}
		constexpr static gamestate win(const playerType winningPlayer) noexcept
		{
			gamestate result{ static_cast<gamestate>(0) };
			for (const auto i : playerType::range)
			{
				if (i != winningPlayer)
					result |= loss(i);
			}
			return result;
		}
		constexpr static bool isWin(const gamestate state, const playerType p) noexcept
		{
			return state == win(p);
		}
	};
}