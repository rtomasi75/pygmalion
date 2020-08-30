namespace pygmalion
{
	template<int COUNT_CODES>
	class movecode : public enumeration<COUNT_CODES, movecode<COUNT_CODES>>
	{
	public:
		constexpr movecode(const movecode&) noexcept = default;
		constexpr movecode(movecode&&) noexcept = default;
		constexpr movecode() noexcept :
			enumeration<COUNT_CODES, movecode<COUNT_CODES>>()
		{

		}
		constexpr movecode(const typename enumeration<COUNT_CODES, movecode<COUNT_CODES>>::baseType value) noexcept :
			enumeration<COUNT_CODES, movecode<COUNT_CODES>>(value)
		{
		}
		constexpr movecode(const typename enumeration<COUNT_CODES, movecode<COUNT_CODES>>::valueType value) noexcept :
			enumeration<COUNT_CODES, movecode<COUNT_CODES>>(value)
		{
		}
		constexpr movecode<COUNT_CODES>& operator=(movecode<COUNT_CODES>&&) noexcept = default;
		constexpr movecode<COUNT_CODES>& operator=(const movecode<COUNT_CODES>&) noexcept = default;
	};
}