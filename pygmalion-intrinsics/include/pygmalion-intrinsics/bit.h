namespace pygmalion
{
	template<size_t COUNT_BITS, size_t COUNT_HASHBITS>
	class bit :
		public enumeration<COUNT_BITS, COUNT_HASHBITS, bit<COUNT_BITS, COUNT_HASHBITS>>
	{
	public:
		constexpr bit(const bit&) noexcept = default;
		constexpr bit(bit&&) noexcept = default;
		constexpr bit() noexcept = default;
		constexpr bit(const typename enumeration<COUNT_BITS, COUNT_HASHBITS, bit<COUNT_BITS, COUNT_HASHBITS>>::baseType value) noexcept :
			enumeration<COUNT_BITS, COUNT_HASHBITS, bit<COUNT_BITS, COUNT_HASHBITS>>(value)
		{
		}
		constexpr bit(const typename enumeration<COUNT_BITS, COUNT_HASHBITS, bit<COUNT_BITS, COUNT_HASHBITS>>::valueType value) noexcept :
			enumeration<COUNT_BITS, COUNT_HASHBITS, bit<COUNT_BITS, COUNT_HASHBITS>>(value)
		{
		}
		constexpr bit& operator=(bit&&) noexcept = default;
		constexpr bit& operator=(const bit&) noexcept = default;
	};
}