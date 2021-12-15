namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class piece :
		public enumeration<DESCRIPTION_STATE::countPieces, DESCRIPTION_STATE::countHashBits, piece<DESCRIPTION_STATE>, set<piece<DESCRIPTION_STATE>,typename DESCRIPTION_STATE::piecesType>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countPieces, DESCRIPTION_STATE::countHashBits, piece<DESCRIPTION_STATE>, set<piece<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::piecesType>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr piece(const piece&) noexcept = default;
		PYGMALION_INLINE constexpr piece(piece&&) noexcept = default;
		PYGMALION_INLINE constexpr piece() noexcept :
			parentType()
		{

		}
		PYGMALION_INLINE constexpr piece(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr piece(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr piece& operator=(piece&&) noexcept = default;
		PYGMALION_INLINE constexpr piece& operator=(const piece&) noexcept = default;
		std::string toShortString() const noexcept
		{
			return descriptorState::boardInfo.playerpieces().pieces().toShortString(static_cast<size_t>(*this));
		}
		std::string toLongString() const noexcept
		{
			return descriptorState::boardInfo.playerpieces().pieces().toLongString(static_cast<size_t>(*this));
		}
		static bool parse(const std::string text, size_t& pos, piece& parsed) noexcept
		{
			size_t parsedIndex;
			if (descriptorState::boardInfo.playerpieces().pieces().parse(text, pos, parsedIndex))
			{
				parsed = piece(parsedIndex);
				return true;
			}
			else
				return false;
		}
		PYGMALION_INLINE constexpr playerpieceType operator&(const playerType player) const noexcept
		{
			return playerpieceType::fromPlayerPiece(player, *this);
		}
	};
}