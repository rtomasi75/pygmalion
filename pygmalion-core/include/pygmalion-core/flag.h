namespace pygmalion
{
	template<int COUNT_FLAGS>
	class flag : public enumeration<COUNT_FLAGS, flag<COUNT_FLAGS>>
	{
	public:
		constexpr flag(const flag&) noexcept = default;
		constexpr flag(flag&&) noexcept = default;
		constexpr flag() noexcept :
			enumeration<COUNT_FLAGS, flag<COUNT_FLAGS>>()
		{

		}
		constexpr flag(const typename enumeration<COUNT_FLAGS, flag<COUNT_FLAGS>>::baseType value) noexcept :
			enumeration<COUNT_FLAGS, flag<COUNT_FLAGS>>(value)
		{
		}
		constexpr flag(const typename enumeration<COUNT_FLAGS, flag<COUNT_FLAGS>>::valueType value) noexcept :
			enumeration<COUNT_FLAGS, flag<COUNT_FLAGS>>(value)
		{
		}
		constexpr flag<COUNT_FLAGS>& operator=(flag<COUNT_FLAGS>&&) noexcept = default;
		constexpr flag<COUNT_FLAGS>& operator=(const flag<COUNT_FLAGS>&) noexcept = default;
		constexpr operator bit<COUNT_FLAGS>() const noexcept
		{
			return bit<COUNT_FLAGS>(static_cast<typename enumeration<COUNT_FLAGS, flag<COUNT_FLAGS>>::baseType>(*this));
		}
		constexpr flag(const bit<COUNT_FLAGS>& bit) noexcept :
			flag<COUNT_FLAGS>(static_cast<typename enumeration<COUNT_FLAGS, flag<COUNT_FLAGS>>::baseType>(bit))
		{

		}
	};
}