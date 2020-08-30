namespace pygmalion
{
	template<int COUNT_FILES>
	class file : public enumeration<COUNT_FILES, file<COUNT_FILES>>
	{
	public:
		constexpr file(const file&) noexcept = default;
		constexpr file(file&&) noexcept = default;
		constexpr file() noexcept :
			enumeration<COUNT_FILES, file<COUNT_FILES>>()
		{

		}
		constexpr file(const typename enumeration<COUNT_FILES, file<COUNT_FILES>>::baseType value) noexcept :
			enumeration<COUNT_FILES, file<COUNT_FILES>>(value)
		{
		}
		constexpr file(const typename enumeration<COUNT_FILES, file<COUNT_FILES>>::valueType value) noexcept :
			enumeration<COUNT_FILES, file<COUNT_FILES>>(value)
		{
		}
		constexpr file<COUNT_FILES>& operator=(file<COUNT_FILES>&&) noexcept = default;
		constexpr file<COUNT_FILES>& operator=(const file<COUNT_FILES>&) noexcept = default;
	};

}