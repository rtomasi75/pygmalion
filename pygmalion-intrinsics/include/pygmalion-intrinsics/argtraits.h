namespace pygmalion::intrinsics
{
	namespace detail
	{
		struct argtraits_helper
		{
		public:
			constexpr static bool enableByValue(const size_t size) noexcept
			{
				return size < sizeof(void*);
			}
			constexpr static bool enableByReference(const size_t size) noexcept
			{
				return !enableByValue(size);
			}
		};
	}

	template<typename TYPE, typename = typename std::enable_if<detail::argtraits_helper::enableByReference(sizeof(TYPE))>::type>
	class argtraits
	{
	public:
		using constArgument = const TYPE&;
		using constReturn = const TYPE&;
	};

	template<typename TYPE>
	class argtraits<TYPE, typename std::enable_if<detail::argtraits_helper::enableByValue(sizeof(TYPE)) >::type>
	{
	public:
		using constArgument = const TYPE;
		using constReturn = TYPE;
	};
}