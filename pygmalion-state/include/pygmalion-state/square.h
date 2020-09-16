namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class square :
		public enumeration<DESCRIPTION_STATE::countSquares, square<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
		friend class file<DESCRIPTION_STATE>;
		friend class rank<DESCRIPTION_STATE>;
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countSquares, square<DESCRIPTION_STATE>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
	private:
		constexpr static square fromRankFile(const rankType r, const fileType f) noexcept
		{
			assert(r.isValid());
			assert(f.isValid());
			return r * countFiles + f;
		}
	public:
		constexpr rankType rank() const noexcept
		{
			assert(this->isValid());
			return (*this) / countFiles;
		}
		constexpr fileType file() const noexcept
		{
			assert(this->isValid());
			return (*this) % countFiles;
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
	};
}