namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class file :
		public enumeration<DESCRIPTION_STATE::countFiles, DESCRIPTION_STATE::countHashBits, file<DESCRIPTION_STATE>, set<file<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::filesType>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countFiles, DESCRIPTION_STATE::countHashBits, file<DESCRIPTION_STATE>, set<file<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::filesType>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr file(const file&) noexcept = default;
		PYGMALION_INLINE constexpr file(file&&) noexcept = default;
		PYGMALION_INLINE constexpr file() noexcept :
			parentType()
		{

		}
		PYGMALION_INLINE constexpr file(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr file(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr file& operator=(file&&) noexcept = default;
		PYGMALION_INLINE constexpr file& operator=(const file&) noexcept = default;
		PYGMALION_INLINE constexpr file operator-() const noexcept
		{
			return countFiles - 1 - (*this);
		}
		PYGMALION_INLINE constexpr squaresType operator|(const fileType other) const noexcept
		{
			return static_cast<squaresType>(*this) | static_cast<squaresType>(other);
		}
		PYGMALION_INLINE constexpr squaresType operator&(const fileType other) const noexcept
		{
			return static_cast<squaresType>(*this) & static_cast<squaresType>(other);
		}
		PYGMALION_INLINE constexpr squaresType operator^(const fileType other) const noexcept
		{
			return static_cast<squaresType>(*this) ^ static_cast<squaresType>(other);
		}
		PYGMALION_INLINE constexpr squaresType operator|(const squareType other) const noexcept
		{
			return static_cast<squaresType>(*this) | other;
		}
		PYGMALION_INLINE constexpr squaresType operator&(const squareType other) const noexcept
		{
			return static_cast<squaresType>(*this) & other;
		}
		PYGMALION_INLINE constexpr squaresType operator^(const squareType other) const noexcept
		{
			return static_cast<squaresType>(*this) ^ other;
		}
		PYGMALION_INLINE constexpr squaresType operator~() const noexcept
		{
			return ~static_cast<squaresType>(*this);
		}
		PYGMALION_INLINE constexpr squareType operator&(const rankType rank) const noexcept
		{
			return squareType::fromRankFile(rank, *this);
		}
		PYGMALION_INLINE constexpr squaresType operator|(const squaresType other) const noexcept
		{
			return static_cast<squaresType>(*this) | other;
		}
		PYGMALION_INLINE constexpr squaresType operator&(const squaresType other) const noexcept
		{
			return static_cast<squaresType>(*this) & other;
		}
		PYGMALION_INLINE constexpr squaresType operator^(const squaresType other) const noexcept
		{
			return static_cast<squaresType>(*this) ^ other;
		}
		PYGMALION_INLINE constexpr bool operator==(const rankType rank) const noexcept
		{
			return static_cast<squaresType>(*this) == static_cast<squaresType>(rank);
		}
		PYGMALION_INLINE constexpr bool operator!=(const rankType rank) const noexcept
		{
			return static_cast<squaresType>(*this) != static_cast<squaresType>(rank);
		}
		PYGMALION_INLINE constexpr bool operator==(const squareType other) const noexcept
		{
			return static_cast<squaresType>(*this) == static_cast<squaresType>(other);
		}
		PYGMALION_INLINE constexpr bool operator!=(const squareType other) const noexcept
		{
			return static_cast<squaresType>(*this) != static_cast<squaresType>(other);
		}
		PYGMALION_INLINE constexpr bool operator==(const squaresType other) const noexcept
		{
			return static_cast<squaresType>(*this) == other;
		}
		PYGMALION_INLINE constexpr bool operator!=(const squaresType other) const noexcept
		{
			return static_cast<squaresType>(*this) != other;
		}
		PYGMALION_INLINE constexpr file left() const noexcept
		{
			return (*this) - 1;
		}
		PYGMALION_INLINE constexpr file right() const noexcept
		{
			return (*this) + 1;
		}
	};

}