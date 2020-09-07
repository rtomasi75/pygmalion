namespace detail
{
	template<size_t COUNT_BYTES, bool IS_COMPACT = false, typename = typename std::enable_if<true>::type>
	class uint_t_traits
	{
	public:
		using wordType = std::uint_fast8_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, true, typename std::enable_if<(COUNT_BYTES >= 1) && ((COUNT_BYTES % 2) != 0)>::type>
	{
	public:
		using wordType = std::uint_least8_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, true, typename std::enable_if<(COUNT_BYTES >= 2) && ((COUNT_BYTES % 2) == 0) && ((COUNT_BYTES % 4) != 0) >::type>
	{
	public:
		using wordType = std::uint_least16_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, true, typename std::enable_if<(COUNT_BYTES >= 4) && ((COUNT_BYTES % 4) == 0) && ((COUNT_BYTES % 8) != 0)>::type>
	{
	public:
		using wordType = std::uint_least32_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, true, typename std::enable_if<(COUNT_BYTES >= 8) && ((COUNT_BYTES % 8) == 0)>::type>
	{
	public:
		using wordType = std::uint_least64_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, false, typename std::enable_if<(COUNT_BYTES <= 1)>::type>
	{
	public:
		using wordType = std::uint_fast8_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, false, typename std::enable_if<(COUNT_BYTES > 1) && (COUNT_BYTES < 2)>::type>
	{
	public:
		using wordType = std::uint_fast16_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits<COUNT_BYTES, false, typename std::enable_if<(COUNT_BYTES > 2) && (COUNT_BYTES < 4)>::type>
	{
	public:
		using wordType = std::uint_fast32_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits < COUNT_BYTES, false, typename std::enable_if < (COUNT_BYTES > 4) && (COUNT_BYTES < sizeof(std::uintmax_t))>::type >
	{
	public:
		using wordType = std::uint_fast64_t;
	};

	template<size_t COUNT_BYTES>
	class uint_t_traits < COUNT_BYTES, false, typename std::enable_if < (COUNT_BYTES >= sizeof(std::uintmax_t))>::type >
	{
	public:
		using wordType = std::uintmax_t;
	};
}