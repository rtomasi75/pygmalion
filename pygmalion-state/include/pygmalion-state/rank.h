namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class rank :
		public enumeration<DESCRIPTION_STATE::countRanks, DESCRIPTION_STATE::countHashBits, rank<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countRanks, DESCRIPTION_STATE::countHashBits, rank<DESCRIPTION_STATE>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr rank(const rank&) noexcept = default;
		PYGMALION_INLINE constexpr rank(rank&&) noexcept = default;
		PYGMALION_INLINE constexpr rank() noexcept :
			parentType()
		{

		}
		PYGMALION_INLINE constexpr rank(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr rank(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr rank& operator=(rank&&) noexcept = default;
		PYGMALION_INLINE constexpr rank& operator=(const rank&) noexcept = default;
		PYGMALION_INLINE constexpr rank operator-() const noexcept
		{
			return rank(countRanks - 1 - (*this));
		}
		PYGMALION_INLINE constexpr squareType operator&(const fileType file) const noexcept
		{
			return squareType::fromRankFile(*this, file);
		}
		PYGMALION_INLINE constexpr squaresType operator|(const rankType other) const noexcept
		{
			return static_cast<squaresType>(*this) | static_cast<squaresType>(other);
		}
		PYGMALION_INLINE constexpr squaresType operator&(const rankType other) const noexcept
		{
			return static_cast<squaresType>(*this) & static_cast<squaresType>(other);
		}
		PYGMALION_INLINE constexpr squaresType operator^(const rankType other) const noexcept
		{
			return static_cast<squaresType>(*this) ^ static_cast<squaresType>(other);
		}
		PYGMALION_INLINE constexpr squaresType operator~() const noexcept
		{
			return ~static_cast<squaresType>(*this);
		}
		PYGMALION_INLINE constexpr rank down() const noexcept
		{
			return (*this) - 1;
		}
		PYGMALION_INLINE constexpr rank up() const noexcept
		{
			return (*this) + 1;
		}
	};
}