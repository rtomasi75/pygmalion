namespace pygmalion
{
	template<size_t COUNT_BITS, bool IS_COMPACT, typename = typename std::enable_if<true>::type>
	class uint_t;

	template<size_t BITCOUNT, size_t VALUECOUNT>
	class hashprovider
	{
	public:
		constexpr static size_t countBits{ BITCOUNT };
		constexpr static size_t countValues{ VALUECOUNT };
		using hashValue = uint_t<countBits, false>;
	private:
		std::array<hashValue, countValues> m_HashOfValue;
	public:
		hashprovider() noexcept :
			m_HashOfValue{ arrayhelper::generate<countValues, hashValue>([](const size_t idx) {return hashValue::random(); }) }
		{
		}
		constexpr hashprovider(hashprovider&&) noexcept = default;
		constexpr hashprovider(const hashprovider&) noexcept = default;
		constexpr hashprovider& operator=(hashprovider&&) noexcept = default;
		constexpr hashprovider& operator=(const hashprovider&) noexcept = default;
		~hashprovider() noexcept = default;
		constexpr const hashValue& operator[](const size_t value) const noexcept
		{
			assert(value >= 0);
			assert(value < countValues);
			return m_HashOfValue[value];
		}
	};
}