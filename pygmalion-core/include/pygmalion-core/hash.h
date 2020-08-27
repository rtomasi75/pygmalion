namespace pygmalion
{
	template<int BITCOUNT>
	class hashBase
	{
	public:
		constexpr static int countBits{ BITCOUNT };
		using hashValue = typename int_traits<requiredBitBytes(countBits)>::UTYPE;
	protected:
		constexpr static hashValue random() noexcept
		{
			return int_traits<requiredBitBytes(countBits)>::rand();
		}
	protected:
		constexpr hashBase() noexcept = default;
		constexpr hashBase(hashBase&&) noexcept = default;
		constexpr hashBase(const hashBase&) noexcept = default;
		constexpr hashBase& operator=(hashBase&&) noexcept = default;
		constexpr hashBase& operator=(const hashBase&) noexcept = default;
		~hashBase() noexcept = default;
	};
	template<int BITCOUNT, int VALUECOUNT>
	class hash : public hashBase<BITCOUNT>
	{
	public:
		constexpr static int countValues{ VALUECOUNT };
	private:
		typename hashBase<BITCOUNT>::hashValue m_HashOfValue[countValues];
	public:
		constexpr hash() noexcept :
			hashBase<BITCOUNT>()
		{
			for (int i = 0; i < countValues; i++)
			{
				m_HashOfValue[i] = this->random();
			}
		}
		constexpr hash(hash&&) noexcept = default;
		constexpr hash(const hash&) noexcept = default;
		constexpr hash& operator=(hash&&) noexcept = default;
		constexpr hash& operator=(const hash&) noexcept = default;
		~hash() noexcept = default;
		constexpr typename hashBase<BITCOUNT>::hashValue operator[](const int value) const noexcept
		{
			assert(value >= 0);
			assert(value < countValues);
			return m_HashOfValue[value];
		}
	};
}