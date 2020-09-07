namespace detail
{
	class base;
}

class random
{
friend class detail::base;
private:
	std::uint_fast64_t x{ 0 };
	std::uint_fast64_t w{ 0 };
	std::uint_fast64_t s{ std::uint_fast64_t(0xb5ad4aceda1ce2a9) };
	std::uint_fast32_t next() noexcept
	{
		x *= x;
		x += (w += s);
		return static_cast<std::int_fast32_t>((x = (x >> 32) | (x << 32)));
	}
	random() noexcept :
		x{ 0 },
		w{ 0 },
		s{ std::uint_fast64_t(0xb5ad4aceda1ce2a9) }
	{}
};