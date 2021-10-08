namespace pygmalion
{
	template<size_t COUNT_BITS, size_t COUNT_HASHBITS>
	class bit :
		public enumeration<COUNT_BITS, COUNT_HASHBITS, bit<COUNT_BITS, COUNT_HASHBITS>>
	{
	public:
		PYGMALION_INLINE constexpr bit(const bit&) noexcept = default;
		PYGMALION_INLINE constexpr bit(bit&&) noexcept = default;
		PYGMALION_INLINE constexpr bit() noexcept = default;
		PYGMALION_INLINE constexpr bit(const typename enumeration<COUNT_BITS, COUNT_HASHBITS, bit<COUNT_BITS, COUNT_HASHBITS>>::baseType value) noexcept :
			enumeration<COUNT_BITS, COUNT_HASHBITS, bit<COUNT_BITS, COUNT_HASHBITS>>(value)
		{
		}
		PYGMALION_INLINE constexpr bit(const typename enumeration<COUNT_BITS, COUNT_HASHBITS, bit<COUNT_BITS, COUNT_HASHBITS>>::valueType value) noexcept :
			enumeration<COUNT_BITS, COUNT_HASHBITS, bit<COUNT_BITS, COUNT_HASHBITS>>(value)
		{
		}
		PYGMALION_INLINE constexpr bit& operator=(bit&&) noexcept = default;
		PYGMALION_INLINE constexpr bit& operator=(const bit&) noexcept = default;
	};
}