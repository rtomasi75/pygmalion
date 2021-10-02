namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class file :
		public enumeration<DESCRIPTION_STATE::countFiles, DESCRIPTION_STATE::countHashBits, file<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countFiles, DESCRIPTION_STATE::countHashBits, file<DESCRIPTION_STATE>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		constexpr file(const file&) noexcept = default;
		constexpr file(file&&) noexcept = default;
		constexpr file() noexcept :
			parentType()
		{

		}
		constexpr file(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		constexpr file(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		constexpr file& operator=(file&&) noexcept = default;
		constexpr file& operator=(const file&) noexcept = default;
		constexpr file operator-() const noexcept
		{
			return countFiles - 1 - (*this);
		}
		constexpr squaresType operator|(const fileType other) const noexcept
		{
			return static_cast<squaresType>(*this) | static_cast<squaresType>(other);
		}
		constexpr squaresType operator&(const fileType other) const noexcept
		{
			return static_cast<squaresType>(*this) & static_cast<squaresType>(other);
		}
		constexpr squaresType operator^(const fileType other) const noexcept
		{
			return static_cast<squaresType>(*this) ^ static_cast<squaresType>(other);
		}
		constexpr squaresType operator~() const noexcept
		{
			return ~static_cast<squaresType>(*this);
		}
		constexpr squareType operator&(const rankType rank) const noexcept
		{
			return squareType::fromRankFile(rank, *this);
		}
		constexpr file left() const noexcept
		{
			return (*this) - 1;
		}
		constexpr file right() const noexcept
		{
			return (*this) + 1;
		}
	};

}