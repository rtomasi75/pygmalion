namespace detail
{
	template<size_t COUNT_BITS, bool COMPACT>
	constexpr size_t countWords() noexcept
	{
		constexpr const bool isCompact{ COMPACT };
		constexpr const size_t countBits{ COUNT_BITS };
		constexpr const size_t countBytes{ (countBits + 7) / 8 };
		constexpr const size_t countBitsPerWord{ sizeof(typename integer_traits<countBytes, isCompact>::uword) * CHAR_BIT };
		return (countBits + countBitsPerWord - 1) / countBitsPerWord;
	}
	template<size_t COUNT_BITS, bool COMPACT>
	constexpr size_t countBitsPerWord() noexcept
	{
		constexpr const bool isCompact{ COMPACT };
		constexpr const size_t countBits{ COUNT_BITS };
		constexpr const size_t countBytes{ (countBits + 7) / 8 };
		return sizeof(typename integer_traits<countBytes, isCompact>::uword) * CHAR_BIT;
	}
	template<size_t COUNT_BITS, bool COMPACT>
	constexpr bool isMultiWord() noexcept
	{
		return countWords<COUNT_BITS, COMPACT>() > 1;
	}
	template<size_t COUNT_BITS, bool COMPACT>
	constexpr bool isSingleBit() noexcept
	{
		constexpr const size_t countBits{ COUNT_BITS };
		return countBits == 1;
	}
	template<size_t COUNT_BITS, bool COMPACT>
	constexpr bool isSingleWord() noexcept
	{
		return (countWords<COUNT_BITS, COMPACT>() == 1) && !isSingleBit<COUNT_BITS, COMPACT>();
	}
	template<size_t COUNT_BITS, bool COMPACT>
	constexpr bool isEmpty() noexcept
	{
		return countWords<COUNT_BITS, COMPACT>() == 0;
	}
}
