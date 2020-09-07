
template<size_t COUNT_BYTES, bool COMPACT = false, typename ENABLED = typename std::enable_if<true>::type>
class integer_traits
{
public:
	using uword = std::uint16_t;
};

template<size_t COUNT_BYTES>
class integer_traits<COUNT_BYTES, true, typename std::enable_if<true>::type>
{
public:
	using uword = std::uint8_t;
};
/*
template<size_t COUNT_BYTES>
class integer_traits<COUNT_BYTES, true, typename std::enable_if<(COUNT_BYTES >= 1) && ((COUNT_BYTES % 2) != 0)>::type>
{
public:
	using uword = std::uint_least8_t;
};

template<size_t COUNT_BYTES>
class integer_traits<COUNT_BYTES, true, typename std::enable_if<(COUNT_BYTES >= 2) && ((COUNT_BYTES % 2) == 0) && ((COUNT_BYTES % 4) != 0) >::type>
{
public:
	using uword = std::uint_least16_t;
};

template<size_t COUNT_BYTES>
class integer_traits<COUNT_BYTES, true, typename std::enable_if<(COUNT_BYTES >= 4) && ((COUNT_BYTES % 4) == 0) && ((COUNT_BYTES % 8) != 0)>::type>
{
public:
	using uword = std::uint_least32_t;
};

template<size_t COUNT_BYTES>
class integer_traits<COUNT_BYTES, true, typename std::enable_if<(COUNT_BYTES >= 8) && ((COUNT_BYTES % 8) == 0)>::type>
{
public:
	using uword = std::uint_least64_t;
};

template<size_t COUNT_BYTES>
class integer_traits<COUNT_BYTES, false, typename std::enable_if < (COUNT_BYTES > sizeof(std::uintmax_t)) >::type >
{
public:
	using uword = std::uintmax_t;
};
*/
/*template<size_t COUNT_BYTES>
class integer_traits<COUNT_BYTES, false, typename std::enable_if<(COUNT_BYTES <= 1)>::type>
{
public:
	using uword = std::uint_fast8_t;
};

template<size_t COUNT_BYTES>
class integer_traits<COUNT_BYTES, false, typename std::enable_if<(COUNT_BYTES >= 2) && (COUNT_BYTES < 3)>::type>
{
public:
	using uword = std::uint_fast16_t;
};

template<size_t COUNT_BYTES>
class integer_traits<COUNT_BYTES, false, typename std::enable_if<(COUNT_BYTES >= 3) && (COUNT_BYTES < 5)>::type>
{
public:
	using uword = std::uint_fast32_t;
};

template<size_t COUNT_BYTES>
class integer_traits < COUNT_BYTES, false, typename std::enable_if < (COUNT_BYTES >= 5) && (COUNT_BYTES < sizeof(std::uintmax_t))>::type >
{
public:
	using uword = std::uint_fast64_t;
};
*/