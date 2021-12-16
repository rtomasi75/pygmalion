namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class royalpiece :
		public enumeration<DESCRIPTION_STATE::countRoyalPieces, DESCRIPTION_STATE::countHashBits, royalpiece<DESCRIPTION_STATE>, set<royalpiece<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::royalpiecesType>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countRoyalPieces, DESCRIPTION_STATE::countHashBits, royalpiece<DESCRIPTION_STATE>, set<royalpiece<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::royalpiecesType>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr royalpiece(const royalpiece&) noexcept = default;
		PYGMALION_INLINE constexpr royalpiece(royalpiece&&) noexcept = default;
		PYGMALION_INLINE constexpr royalpiece() noexcept :
			parentType()
		{

		}
		PYGMALION_INLINE constexpr royalpiece(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr royalpiece(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr royalpiece& operator=(royalpiece&&) noexcept = default;
		PYGMALION_INLINE constexpr royalpiece& operator=(const royalpiece&) noexcept = default;
		PYGMALION_INLINE constexpr royalpiecesType operator|(const royalpiece other) const noexcept
		{
			return static_cast<royalpiecesType>(*this) | royalpiecesType(other);
		}
		PYGMALION_INLINE constexpr operator royalpiecesType() const noexcept
		{
			return royalpiecesType(*static_cast<royalpiecesType>(this));
		}
		std::string toShortString() const noexcept
		{
			return static_cast<pieceType>(*this).toShortString();
		}
		std::string toLongString() const noexcept
		{
			return static_cast<pieceType>(*this).toLongString();
		}
		static bool parse(const std::string text, size_t& pos, royalpiece& parsed) noexcept
		{
			size_t cnt{ pos };
			size_t parsedIndex;
			pieceType pc;
			if (pieceType::parse(text,cnt,pc))
			{
				if (pc.isRoyal())
				{
					parsed = static_cast<royalpiece>(pc);
					pos += cnt;
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
	};
}