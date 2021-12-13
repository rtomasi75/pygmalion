namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class square :
		public enumeration < DESCRIPTION_STATE::countSquares, DESCRIPTION_STATE::countHashBits, square<DESCRIPTION_STATE>, set<square<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::squaresType>>,
		public DESCRIPTION_STATE
	{
		friend class file<DESCRIPTION_STATE>;
		friend class rank<DESCRIPTION_STATE>;
	public:
		using parentType = enumeration < DESCRIPTION_STATE::countSquares, DESCRIPTION_STATE::countHashBits, square<DESCRIPTION_STATE>, set<square<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::squaresType>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
	private:
		PYGMALION_INLINE constexpr static square fromRankFile(const rankType r, const fileType f) noexcept
		{
			return r * countFiles + f;
		}
	public:
		PYGMALION_INLINE constexpr rankType rank() const noexcept
		{
			return (*this) / countFiles;
		}
		PYGMALION_INLINE constexpr fileType file() const noexcept
		{
			return (*this) % countFiles;
		}
		PYGMALION_INLINE constexpr bool isDark() const noexcept
		{
			return (rank() + file()) % 2 == 0;
		}
		PYGMALION_INLINE constexpr square(const square&) noexcept = default;
		PYGMALION_INLINE constexpr square(square&&) noexcept = default;
		PYGMALION_INLINE constexpr square() noexcept :
			parentType()
		{

		}
		PYGMALION_INLINE constexpr square(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr square(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr square& operator=(square&&) noexcept = default;
		PYGMALION_INLINE constexpr square& operator=(const square&) noexcept = default;
		PYGMALION_INLINE constexpr squaresType operator|(const square other) const noexcept
		{
			return static_cast<squaresType>(*this) | static_cast<squaresType>(other);
		}
		PYGMALION_INLINE constexpr squaresType operator&(const square other) const noexcept
		{
			return static_cast<squaresType>(*this) & static_cast<squaresType>(other);
		}
		PYGMALION_INLINE constexpr squaresType operator^(const square other) const noexcept
		{
			return static_cast<squaresType>(*this) ^ static_cast<squaresType>(other);
		}
		PYGMALION_INLINE constexpr squaresType operator~() const noexcept
		{
			return ~static_cast<squaresType>(*this);
		}
		PYGMALION_INLINE constexpr square up() const noexcept
		{
			return fromRankFile(rank() + 1, file());
		}
		PYGMALION_INLINE constexpr square upLeft() const noexcept
		{
			return fromRankFile(rank() + 1, file() - 1);
		}
		PYGMALION_INLINE constexpr square upRight() const noexcept
		{
			return fromRankFile(rank() + 1, file() + 1);
		}
		PYGMALION_INLINE constexpr square down() const noexcept
		{
			return fromRankFile(rank() - 1, file());
		}
		PYGMALION_INLINE constexpr square downLeft() const noexcept
		{
			return fromRankFile(rank() - 1, file() - 1);
		}
		PYGMALION_INLINE constexpr square downRight() const noexcept
		{
			return fromRankFile(rank() - 1, file() + 1);
		}
		PYGMALION_INLINE constexpr square right() const noexcept
		{
			return fromRankFile(rank(), file() + 1);
		}
		PYGMALION_INLINE constexpr square left() const noexcept
		{
			return fromRankFile(rank(), file() - 1);
		}
		PYGMALION_INLINE constexpr square flipRank() const noexcept
		{
			return static_cast<rankType>(countRanks - static_cast<int>(this->rank()) - 1) & this->file();
		}
		PYGMALION_INLINE constexpr bool operator==(const rankType rank) const noexcept
		{
			return static_cast<squaresType>(*this) == static_cast<squaresType>(rank);
		}
		PYGMALION_INLINE constexpr bool operator!=(const rankType rank) const noexcept
		{
			return static_cast<squaresType>(*this) != static_cast<squaresType>(rank);
		}
		PYGMALION_INLINE constexpr bool operator==(const fileType other) const noexcept
		{
			return static_cast<squaresType>(*this) == static_cast<squaresType>(other);
		}
		PYGMALION_INLINE constexpr bool operator!=(const fileType other) const noexcept
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
	};
}