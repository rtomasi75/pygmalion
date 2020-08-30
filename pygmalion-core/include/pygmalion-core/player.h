namespace pygmalion
{
	template<int COUNT_PLAYERS>
	class player : public enumeration<COUNT_PLAYERS, player<COUNT_PLAYERS>>
	{
	public:
		constexpr player(const player&) noexcept = default;
		constexpr player(player&&) noexcept = default;
		constexpr player() noexcept :
			enumeration<COUNT_PLAYERS, player<COUNT_PLAYERS>>()
		{

		}
		constexpr player(const typename enumeration<COUNT_PLAYERS, player<COUNT_PLAYERS>>::baseType value) noexcept :
			enumeration<COUNT_PLAYERS, player<COUNT_PLAYERS>>(value)
		{
		}
		constexpr player(const typename enumeration<COUNT_PLAYERS, player<COUNT_PLAYERS>>::valueType value) noexcept :
			enumeration<COUNT_PLAYERS, player<COUNT_PLAYERS>>(value)
		{
		}
		constexpr player<COUNT_PLAYERS>& operator=(player<COUNT_PLAYERS>&&) noexcept = default;
		constexpr player<COUNT_PLAYERS>& operator=(const player<COUNT_PLAYERS>&) noexcept = default;
	};
}