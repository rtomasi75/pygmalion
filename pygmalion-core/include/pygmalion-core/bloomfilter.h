namespace pygmalion
{
	template<size_t HASHBITS, size_t MAXVALUE>
	class bloomfilter
	{
	public:
		constexpr static size_t hashBits{ HASHBITS };
		constexpr static size_t maxValue{ MAXVALUE };
		constexpr static size_t countEntries{ 1 << hashBits };
		using hashValue = typename hashBase<hashBits>::hashValue;
		using valueType = typename int_traits<requiredUnsignedBytes(maxValue)>::UTYPE;
	private:
		constexpr static hashValue m_HashMask{ static_cast<hashValue>(countEntries - 1) };
		std::array<valueType, countEntries> m_Entry;
	public:
		constexpr void clear() noexcept
		{
			for (size_t i = 0; i < countEntries; i++)
				m_Entry[i] = 0;
		}
		constexpr bloomfilter() noexcept :
			m_Entry{ make_array_n<countEntries,valueType>(0) }
		{
		}
		~bloomfilter() noexcept = default;
		constexpr bloomfilter(const bloomfilter&) noexcept = default;
		constexpr bloomfilter& operator=(const bloomfilter&) noexcept = default;
		constexpr bloomfilter(bloomfilter&&) noexcept = default;
		constexpr bloomfilter& operator=(bloomfilter&&) noexcept = default;
		constexpr valueType operator[](const hashValue hash) const noexcept
		{
			return m_Entry[hash & m_HashMask];
		}
		constexpr void increment(const hashValue hash) noexcept
		{
			m_Entry[hash & m_HashMask]++;
		}
		constexpr void decrement(const hashValue hash) noexcept
		{
			m_Entry[hash & m_HashMask]--;
		}
	};
}