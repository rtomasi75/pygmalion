namespace detail
{
	template<size_t COUNT_BYTES, bool IS_COMPACT = false, typename = typename std::enable_if<true>::type>
	class uint_t_traits
	{
	public:
		using wordType = std::uint8_t;
		using halfType = std::uint8_t;
		using doubleType = std::uint_fast16_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, true, typename std::enable_if<(COUNT_BYTES >= 1) && ((COUNT_BYTES % 2) != 0)>::type>
	{
	public:
		using wordType = std::uint8_t;
		using halfType = std::uint8_t;
		using doubleType = std::uint16_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, true, typename std::enable_if<(COUNT_BYTES >= 2) && ((COUNT_BYTES % 2) == 0) && ((COUNT_BYTES % 4) != 0) >::type>
	{
	public:
		using wordType = std::uint16_t;
		using halfType = std::uint8_t;
		using doubleType = std::uint32_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, true, typename std::enable_if<(COUNT_BYTES >= 4) && ((COUNT_BYTES % 4) == 0) && ((COUNT_BYTES % 8) != 0)>::type>
	{
	public:
		using wordType = std::uint32_t;
		using halfType = std::uint16_t;
		using doubleType = std::uint64_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, true, typename std::enable_if<(COUNT_BYTES >= 8) && ((COUNT_BYTES % 8) == 0)>::type>
	{
	public:
		using wordType = std::uint64_t;
		using halfType = std::uint32_t;
		using doubleType = std::uintmax_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, false, typename std::enable_if<(COUNT_BYTES <= 1)>::type>
	{
	public:
		using wordType = std::uint8_t;
		using halfType = std::uint8_t;
		using doubleType = std::uint16_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, false, typename std::enable_if<(COUNT_BYTES > 1) && (COUNT_BYTES <= 2)>::type>
	{
	public:
		using wordType = std::uint16_t;
		using halfType = std::uint8_t;
		using doubleType = std::uint32_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, false, typename std::enable_if<(COUNT_BYTES > 2) && (COUNT_BYTES <= 4)>::type>
	{
	public:
		using wordType = std::uint32_t;
		using halfType = std::uint16_t;
		using doubleType = std::uint64_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits < COUNT_BYTES, false, typename std::enable_if < (COUNT_BYTES > 4)>::type >
	{
	public:
		using wordType = std::uint64_t;
		using halfType = std::uint32_t;
		using doubleType = std::uintmax_t;
	};
}