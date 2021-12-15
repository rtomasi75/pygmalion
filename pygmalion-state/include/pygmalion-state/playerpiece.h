namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class playerpiece :
		public enumeration<DESCRIPTION_STATE::countPlayerpieces, DESCRIPTION_STATE::countHashBits, playerpiece<DESCRIPTION_STATE>, set<playerpiece<DESCRIPTION_STATE>,typename DESCRIPTION_STATE::playerpiecesType>>,
		public DESCRIPTION_STATE
	{
		friend class player<DESCRIPTION_STATE>;
		friend class piece<DESCRIPTION_STATE>;
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countPlayerpieces, DESCRIPTION_STATE::countHashBits, playerpiece<DESCRIPTION_STATE>, set<playerpiece<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::playerpiecesType>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
	private:
		PYGMALION_INLINE constexpr static playerpiece fromPlayerPiece(const playerType pl, const pieceType pc) noexcept
		{
			return pl * countPieces + pc;
		}
	public:
		PYGMALION_INLINE constexpr playerType player() const noexcept
		{
			return (*this) / countPieces;
		}
		PYGMALION_INLINE constexpr pieceType piece() const noexcept
		{
			return (*this) % countPieces;
		}
		PYGMALION_INLINE constexpr playerpiece(const playerpiece&) noexcept = default;
		PYGMALION_INLINE constexpr playerpiece(playerpiece&&) noexcept = default;
		PYGMALION_INLINE constexpr playerpiece() noexcept :
			parentType()
		{

		}
		PYGMALION_INLINE constexpr playerpiece(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr playerpiece(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr playerpiece& operator=(playerpiece&&) noexcept = default;
		PYGMALION_INLINE constexpr playerpiece& operator=(const playerpiece&) noexcept = default;
		PYGMALION_INLINE constexpr playerpiecesType operator|(const playerpiece other) const noexcept
		{
			return static_cast<playerpiecesType>(*this) | static_cast<playerpiecesType>(other);
		}
		PYGMALION_INLINE constexpr playerpiecesType operator&(const playerpiece other) const noexcept
		{
			return static_cast<playerpiecesType>(*this) & static_cast<playerpiecesType>(other);
		}
		PYGMALION_INLINE constexpr playerpiecesType operator^(const playerpiece other) const noexcept
		{
			return static_cast<playerpiecesType>(*this) ^ static_cast<playerpiecesType>(other);
		}
		PYGMALION_INLINE constexpr playerpiecesType operator~() const noexcept
		{
			return ~static_cast<playerpiecesType>(*this);
		}
		std::string toShortString() const noexcept
		{
			return descriptorState::boardInfo.playerpieces().toShortString(static_cast<size_t>(*this));
		}
		std::string toLongString() const noexcept
		{
			return descriptorState::boardInfo.playerpieces().toLongString(static_cast<size_t>(*this));
		}
		static bool parse(const std::string text, size_t& pos, playerpiece& parsed) noexcept
		{
			size_t parsedIndex;
			if (descriptorState::boardInfo.playerpieces().parse(text, pos, parsedIndex))
			{
				parsed = playerpiece(parsedIndex);
				return true;
			}
			else
				return false;
		}
	};
}