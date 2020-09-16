namespace pygmalion
{
	template<size_t COUNT_BITS>
	class bit :
		public enumeration<COUNT_BITS, bit<COUNT_BITS>>
	{
	public:
		constexpr bit(const bit&) noexcept = default;
		constexpr bit(bit&&) noexcept = default;
		constexpr bit() noexcept = default;
		constexpr bit(const typename enumeration<COUNT_BITS, bit<COUNT_BITS>>::baseType value) noexcept :
			enumeration<COUNT_BITS, bit<COUNT_BITS>>(value)
		{
		}
		constexpr bit(const typename enumeration<COUNT_BITS, bit<COUNT_BITS>>::valueType value) noexcept :
			enumeration<COUNT_BITS, bit<COUNT_BITS>>(value)
		{
		}
		constexpr bit& operator=(bit&&) noexcept = default;
		constexpr bit& operator=(const bit&) noexcept = default;
	};
}