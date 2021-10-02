namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class square :
		public enumeration<DESCRIPTION_STATE::countSquares, DESCRIPTION_STATE::countHashBits, square<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
		friend class file<DESCRIPTION_STATE>;
		friend class rank<DESCRIPTION_STATE>;
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countSquares, DESCRIPTION_STATE::countHashBits, square<DESCRIPTION_STATE>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
	private:
		constexpr static square fromRankFile(const rankType r, const fileType f) noexcept
		{
			PYGMALION_ASSERT(r.isValid());
			PYGMALION_ASSERT(f.isValid());
			return r * countFiles + f;
		}
	public:
		constexpr rankType rank() const noexcept
		{
			PYGMALION_ASSERT(this->isValid());
			return (*this) / countFiles;
		}
		constexpr fileType file() const noexcept
		{
			PYGMALION_ASSERT(this->isValid());
			return (*this) % countFiles;
		}
		constexpr bool isDark() const noexcept
		{
			return (rank() + file()) % 2 == 0;
		}
		constexpr square(const square&) noexcept = default;
		constexpr square(square&&) noexcept = default;
		constexpr square() noexcept :
			parentType()
		{

		}
		constexpr square(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		constexpr square(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		constexpr square& operator=(square&&) noexcept = default;
		constexpr square& operator=(const square&) noexcept = default;
		constexpr squaresType operator|(const square other) const noexcept
		{
			return static_cast<squaresType>(*this) | static_cast<squaresType>(other);
		}
		constexpr squaresType operator&(const square other) const noexcept
		{
			return static_cast<squaresType>(*this) & static_cast<squaresType>(other);
		}
		constexpr squaresType operator^(const square other) const noexcept
		{
			return static_cast<squaresType>(*this) ^ static_cast<squaresType>(other);
		}
		constexpr squaresType operator~() const noexcept
		{
			return ~static_cast<squaresType>(*this);
		}
		constexpr square up() const noexcept
		{
			PYGMALION_ASSERT(rank() < (countRanks - 1));
			return fromRankFile(rank() + 1, file());
		}
		constexpr square upLeft() const noexcept
		{
			PYGMALION_ASSERT(rank() < (countRanks - 1));
			PYGMALION_ASSERT(file() > 0);
			return fromRankFile(rank() + 1, file() - 1);
		}
		constexpr square upRight() const noexcept
		{
			PYGMALION_ASSERT(rank() < (countRanks - 1));
			PYGMALION_ASSERT(file() < (countRanks - 1));
			return fromRankFile(rank() + 1, file() + 1);
		}
		constexpr square down() const noexcept
		{
			PYGMALION_ASSERT(rank() > 0);
			return fromRankFile(rank() - 1, file());
		}
		constexpr square downLeft() const noexcept
		{
			PYGMALION_ASSERT(rank() > 0);
			PYGMALION_ASSERT(file() > 0);
			return fromRankFile(rank() - 1, file() - 1);
		}
		constexpr square downRight() const noexcept
		{
			PYGMALION_ASSERT(rank() > 0);
			PYGMALION_ASSERT(file() < (countRanks - 1));
			return fromRankFile(rank() - 1, file() + 1);
		}
		constexpr square right() const noexcept
		{
			PYGMALION_ASSERT(file() < (countRanks - 1));
			return fromRankFile(rank(), file() + 1);
		}
		constexpr square left() const noexcept
		{
			PYGMALION_ASSERT(file() > 0);
			return fromRankFile(rank(), file() - 1);
		}
	};
}