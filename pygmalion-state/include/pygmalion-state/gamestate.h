namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class gamestate : 
		public enumeration<1 + detail::requiredUnsignedBits(DESCRIPTION_STATE::countPlayers), DESCRIPTION_STATE::countHashBits, gamestate<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<1 + detail::requiredUnsignedBits(DESCRIPTION_STATE::countPlayers), DESCRIPTION_STATE::countHashBits, gamestate<DESCRIPTION_STATE>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		constexpr gamestate(const gamestate&) noexcept = default;
		constexpr gamestate(gamestate&&) noexcept = default;
		constexpr gamestate() noexcept :
			parentType()
		{
		}
		constexpr gamestate(const typename parentType::baseType& value) noexcept :
			parentType(value)
		{
		}
		constexpr gamestate(const typename parentType::valueType& value) noexcept :
			parentType(value)
		{
		}
		constexpr gamestate& operator=(gamestate&&) noexcept = default;
		constexpr gamestate& operator=(const gamestate&) noexcept = default;
		constexpr static gamestate open() noexcept
		{
			return static_cast<gamestate>(0);
		}
		constexpr static bool isOpen(const gamestate& state) noexcept
		{
			return state == open();
		}
		constexpr static gamestate draw() noexcept
		{
			return static_cast<gamestate>(1);
		}
		constexpr static bool isDraw(const gamestate& state) noexcept
		{
			return state == draw();
		}
		constexpr static gamestate loss(const playerType& losingPlayer) noexcept
		{
			return static_cast<gamestate>(2 << (losingPlayer));
		}
		constexpr static bool isLoss(const gamestate& state, const playerType& p) noexcept
		{
			return state == loss(p);
		}
		constexpr static gamestate win(const playerType& winningPlayer) noexcept
		{
			gamestate result{ static_cast<gamestate>(0) };
			for (const auto i : playerType::range)
			{
				if (i != winningPlayer)
					result |= loss(i);
			}
			return result;
		}
		constexpr static bool isWin(const gamestate& state, const playerType& p) noexcept
		{
			return state == win(p);
		}
	};
}