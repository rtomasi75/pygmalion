namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class rank :
		public enumeration<DESCRIPTION_STATE::countRanks, rank<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countRanks, rank<DESCRIPTION_STATE>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		constexpr rank(const rank&) noexcept = default;
		constexpr rank(rank&&) noexcept = default;
		constexpr rank() noexcept :
			parentType()
		{

		}
		constexpr rank(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		constexpr rank(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		constexpr rank& operator=(rank&&) noexcept = default;
		constexpr rank& operator=(const rank&) noexcept = default;
		constexpr rank operator-() const noexcept
		{
			return rank(countRanks - 1 - (*this));
		}
		constexpr squareType operator&(const fileType file) const noexcept
		{
			return squareType::fromRankFile(*this, file);
		}
		constexpr squaresType operator|(const rankType other) const noexcept
		{
			return static_cast<squaresType>(*this) | static_cast<squaresType>(other);
		}
		constexpr squaresType operator&(const rankType other) const noexcept
		{
			return static_cast<squaresType>(*this) & static_cast<squaresType>(other);
		}
		constexpr squaresType operator^(const rankType other) const noexcept
		{
			return static_cast<squaresType>(*this) ^ static_cast<squaresType>(other);
		}
		constexpr squaresType operator~() const noexcept
		{
			return ~static_cast<squaresType>(*this);
		}
	};
}