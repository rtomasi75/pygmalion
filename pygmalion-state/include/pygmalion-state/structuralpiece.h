namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class structuralpiece :
		public enumeration<DESCRIPTION_STATE::countStructuralPieces, DESCRIPTION_STATE::countHashBits, structuralpiece<DESCRIPTION_STATE>, set<structuralpiece<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::structuralpiecesType>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countStructuralPieces, DESCRIPTION_STATE::countHashBits, structuralpiece<DESCRIPTION_STATE>, set<structuralpiece<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::structuralpiecesType>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr structuralpiece(const structuralpiece&) noexcept = default;
		PYGMALION_INLINE constexpr structuralpiece(structuralpiece&&) noexcept = default;
		PYGMALION_INLINE constexpr structuralpiece() noexcept :
			parentType()
		{

		}
		PYGMALION_INLINE constexpr structuralpiece(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr structuralpiece(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr structuralpiece& operator=(structuralpiece&&) noexcept = default;
		PYGMALION_INLINE constexpr structuralpiece& operator=(const structuralpiece&) noexcept = default;
		PYGMALION_INLINE constexpr structuralpiecesType operator|(const structuralpiece other) const noexcept
		{
			return static_cast<structuralpiecesType>(*this) | structuralpiecesType(other);
		}
		PYGMALION_INLINE constexpr operator structuralpiecesType() const noexcept
		{
			return structuralpiecesType(*static_cast<structuralpiecesType>(this));
		}
		std::string toShortString() const noexcept
		{
			return static_cast<pieceType>(*this).toShortString();
		}
		std::string toLongString() const noexcept
		{
			return static_cast<pieceType>(*this).toLongString();
		}
		static bool parse(const std::string text, size_t& pos, structuralpiece& parsed) noexcept
		{
			size_t cnt{ pos };
			size_t parsedIndex;
			pieceType pc;
			if (pieceType::parse(text, cnt, pc))
			{
				if (pc.isRoyal())
				{
					parsed = static_cast<structuralpiece>(pc);
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