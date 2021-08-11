namespace pygmalion
{
	template<typename HASHTYPE, size_t HASHBITS, size_t MAXVALUE>
	class bloomfilter
	{
	private:
		constexpr static size_t requiredUnsignedBits(const size_t number) noexcept
		{
			size_t n = 1;
			size_t k = 0;
			while (number > n)
			{
				n *= 2;
				k++;
			}
			return k;
		}
	public:
		constexpr static size_t hashBits{ HASHBITS };
		constexpr static size_t maxValue{ MAXVALUE };
		constexpr static size_t countEntries{ 1 << hashBits };
		using hashValue = HASHTYPE;
		using valueType = uint_t<requiredUnsignedBits(maxValue), false>;
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
			m_Entry{ arrayhelper::make<countEntries,valueType>(0) }
		{
		}
		~bloomfilter() noexcept = default;
		constexpr bloomfilter(const bloomfilter&) noexcept = default;
		constexpr bloomfilter& operator=(const bloomfilter&) noexcept = default;
		constexpr bloomfilter(bloomfilter&&) noexcept = default;
		constexpr bloomfilter& operator=(bloomfilter&&) noexcept = default;
		constexpr valueType operator[](const hashValue hash) const noexcept
		{
			return m_Entry[static_cast<size_t>(hash & m_HashMask)];
		}
		constexpr void increment(const hashValue hash) noexcept
		{
			m_Entry[static_cast<size_t>(hash & m_HashMask)]++;
		}
		constexpr void decrement(const hashValue hash) noexcept
		{
			m_Entry[static_cast<size_t>(hash & m_HashMask)]--;
		}
	};
}