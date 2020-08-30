namespace pygmalion
{
	template<int COUNT_RANKS>
	class rank : public enumeration<COUNT_RANKS, rank<COUNT_RANKS>>
	{
	public:
		constexpr rank(const rank&) noexcept = default;
		constexpr rank(rank&&) noexcept = default;
		constexpr rank() noexcept :
			enumeration<COUNT_RANKS, rank<COUNT_RANKS>>()
		{

		}
		constexpr rank(const typename enumeration<COUNT_RANKS, rank<COUNT_RANKS>>::baseType value) noexcept :
			enumeration<COUNT_RANKS, rank<COUNT_RANKS>>(value)
		{
		}
		constexpr rank(const typename enumeration<COUNT_RANKS, rank<COUNT_RANKS>>::valueType value) noexcept :
			enumeration<COUNT_RANKS, rank<COUNT_RANKS>>(value)
		{
		}
		constexpr rank<COUNT_RANKS>& operator=(rank<COUNT_RANKS>&&) noexcept = default;
		constexpr rank<COUNT_RANKS>& operator=(const rank<COUNT_RANKS>&) noexcept = default;
	};
}