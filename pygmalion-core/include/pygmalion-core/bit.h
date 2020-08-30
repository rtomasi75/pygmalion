namespace pygmalion
{
	template<int COUNT_BITS>
	class bit : public enumeration<COUNT_BITS, bit<COUNT_BITS>>
	{
	public:
		constexpr bit(const bit&) noexcept = default;
		constexpr bit(bit&&) noexcept = default;
		constexpr bit() noexcept :
			enumeration<COUNT_BITS, bit<COUNT_BITS>>()
		{

		}
		constexpr bit(const typename enumeration<COUNT_BITS, bit<COUNT_BITS>>::baseType value) noexcept :
			enumeration<COUNT_BITS, bit<COUNT_BITS>>(value)
		{
		}
		constexpr bit(const typename enumeration<COUNT_BITS, bit<COUNT_BITS>>::valueType value) noexcept :
			enumeration<COUNT_BITS, bit<COUNT_BITS>>(value)
		{
		}
		constexpr bit<COUNT_BITS>& operator=(bit<COUNT_BITS>&&) noexcept = default;
		constexpr bit<COUNT_BITS>& operator=(const bit<COUNT_BITS>&) noexcept = default;
	};

}