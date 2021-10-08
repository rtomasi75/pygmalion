namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class gamestate : 
		public enumeration<1 + arrayhelper::requiredUnsignedBits(DESCRIPTION_STATE::countPlayers), DESCRIPTION_STATE::countHashBits, gamestate<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<1 + arrayhelper::requiredUnsignedBits(DESCRIPTION_STATE::countPlayers), DESCRIPTION_STATE::countHashBits, gamestate<DESCRIPTION_STATE>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr gamestate(const gamestate&) noexcept = default;
		PYGMALION_INLINE constexpr gamestate(gamestate&&) noexcept = default;
		PYGMALION_INLINE constexpr gamestate() noexcept :
			parentType()
		{
		}
		PYGMALION_INLINE constexpr gamestate(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr gamestate(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr gamestate& operator=(gamestate&&) noexcept = default;
		PYGMALION_INLINE constexpr gamestate& operator=(const gamestate&) noexcept = default;
		PYGMALION_INLINE constexpr static gamestate open() noexcept
		{
			return static_cast<gamestate>(0);
		}
		PYGMALION_INLINE constexpr static bool isOpen(const gamestate state) noexcept
		{
			return state == open();
		}
		PYGMALION_INLINE constexpr static gamestate draw() noexcept
		{
			return static_cast<gamestate>(1);
		}
		PYGMALION_INLINE constexpr static bool isDraw(const gamestate state) noexcept
		{
			return state == draw();
		}
		PYGMALION_INLINE constexpr static gamestate loss(const playerType losingPlayer) noexcept
		{
			return static_cast<gamestate>(2 << (losingPlayer));
		}
		PYGMALION_INLINE constexpr static bool isLoss(const gamestate state, const playerType p) noexcept
		{
			return state == loss(p);
		}
		PYGMALION_INLINE constexpr static gamestate win(const playerType winningPlayer) noexcept
		{
			gamestate result{ static_cast<gamestate>(0) };
			for (const auto i : playerType::range)
			{
				if (i != winningPlayer)
					result |= loss(i);
			}
			return result;
		}
		PYGMALION_INLINE constexpr static bool isWin(const gamestate state, const playerType p) noexcept
		{
			return state == win(p);
		}
	};
}