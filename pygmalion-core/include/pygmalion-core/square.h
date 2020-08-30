namespace pygmalion
{
	template<int COUNT_RANKS, int COUNT_FILES>
	class square : public enumeration<COUNT_RANKS* COUNT_FILES, square<COUNT_RANKS, COUNT_FILES>>
	{
	public:
		constexpr static square fromRankFile(const rank<COUNT_RANKS> r, const file<COUNT_FILES> f) noexcept
		{
			assert(r.isValid());
			assert(f.isValid());
			return r * COUNT_FILES + f;
		}
		constexpr rank<COUNT_RANKS> rank() const noexcept
		{
			assert(this->isValid());
			return (*this) / COUNT_FILES;
		}
		constexpr file<COUNT_FILES> file() const noexcept
		{
			assert(this->isValid());
			return (*this) % COUNT_FILES;
		}
		constexpr square(const square&) noexcept = default;
		constexpr square(square&&) noexcept = default;
		constexpr square() noexcept :
			enumeration<COUNT_RANKS* COUNT_FILES, square<COUNT_RANKS, COUNT_FILES>>()
		{

		}
		constexpr square(const typename enumeration<COUNT_RANKS* COUNT_FILES, square<COUNT_RANKS, COUNT_FILES>>::baseType value) noexcept :
			enumeration<COUNT_RANKS* COUNT_FILES, square<COUNT_RANKS, COUNT_FILES>>(value)
		{
		}
		constexpr square(const typename enumeration<COUNT_RANKS* COUNT_FILES, square<COUNT_RANKS, COUNT_FILES>>::valueType value) noexcept :
			enumeration<COUNT_RANKS* COUNT_FILES, square<COUNT_RANKS, COUNT_FILES>>(value)
		{
		}
		constexpr square<COUNT_RANKS, COUNT_FILES>& operator=(square<COUNT_RANKS, COUNT_FILES>&&) noexcept = default;
		constexpr square<COUNT_RANKS, COUNT_FILES>& operator=(const square<COUNT_RANKS, COUNT_FILES>&) noexcept = default;
		constexpr operator bit<COUNT_RANKS* COUNT_FILES>() const noexcept
		{
			return bit<COUNT_RANKS* COUNT_FILES>(static_cast<typename enumeration<COUNT_RANKS* COUNT_FILES, square<COUNT_RANKS, COUNT_FILES>>::baseType>(*this));
		}
		constexpr square(const bit<COUNT_RANKS* COUNT_FILES>& bit) noexcept :
			square<COUNT_RANKS, COUNT_FILES>(static_cast<typename enumeration<COUNT_RANKS* COUNT_FILES, square<COUNT_RANKS, COUNT_FILES>>::baseType>(bit))
		{

		}
	};
}