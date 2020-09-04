namespace pygmalion
{
	template<typename DESCRIPTION_BOARD>
	class file :
		public enumeration<DESCRIPTION_BOARD::countFiles, file<DESCRIPTION_BOARD>>,
		public DESCRIPTION_BOARD
	{
	public:
		using descriptorBoard = DESCRIPTION_BOARD;
#include "include_board.h"	
		constexpr file(const file&) noexcept = default;
		constexpr file(file&&) noexcept = default;
		constexpr file() noexcept :
			enumeration<countFiles, file>()
		{

		}
		constexpr file(const typename enumeration<countFiles, file>::baseType value) noexcept :
			enumeration<countFiles, file>(value)
		{
		}
		constexpr file(const typename enumeration<countFiles, file>::valueType value) noexcept :
			enumeration<countFiles, file>(value)
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
		constexpr squaresType operator+(const fileType other) const noexcept
		{
			return static_cast<squaresType>(*this) + static_cast<squaresType>(other);
		}
		constexpr squaresType operator-(const fileType other) const noexcept
		{
			return static_cast<squaresType>(*this) - static_cast<squaresType>(other);
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
	};

}