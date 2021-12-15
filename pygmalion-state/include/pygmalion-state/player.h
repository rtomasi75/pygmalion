namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class player :
		public enumeration<DESCRIPTION_STATE::countPlayers, DESCRIPTION_STATE::countHashBits, player<DESCRIPTION_STATE>, set<player<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::playersType>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countPlayers, DESCRIPTION_STATE::countHashBits, player<DESCRIPTION_STATE>, set<player<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::playersType>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr player(const player&) noexcept = default;
		PYGMALION_INLINE constexpr player(player&&) noexcept = default;
		PYGMALION_INLINE constexpr player() noexcept :
			parentType()
		{

		}
		PYGMALION_INLINE constexpr player(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr player(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr player& operator=(player&&) noexcept = default;
		PYGMALION_INLINE constexpr player& operator=(const player&) noexcept = default;
		std::string toShortString() const noexcept
		{
			return descriptorState::boardInfo.playerpieces().players().toShortString(static_cast<size_t>(*this));
		}
		std::string toLongString() const noexcept
		{
			return descriptorState::boardInfo.playerpieces().players().toLongString(static_cast<size_t>(*this));
		}
		static bool parse(const std::string text, size_t& pos, player& parsed) noexcept
		{
			size_t parsedIndex;
			if (descriptorState::boardInfo.playerpieces().players().parse(text, pos, parsedIndex))
			{
				parsed = player(parsedIndex);
				return true;
			}
			else
				return false;
		}
		PYGMALION_INLINE constexpr playerpieceType operator&(const pieceType piece) const noexcept
		{
			return playerpieceType::fromPlayerPiece(*this, piece);
		}
	};
}