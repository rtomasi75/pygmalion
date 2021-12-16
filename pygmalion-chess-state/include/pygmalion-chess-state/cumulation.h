namespace pygmalion::chess::state
{
	class descriptor_state;

	class cumulation
	{
	public:
	private:
	public:
		PYGMALION_INLINE constexpr void clear() noexcept
		{
		}
		constexpr cumulation() noexcept 
		{
		}
		constexpr cumulation(cumulation&&) noexcept = default;
		constexpr cumulation(const cumulation&) noexcept = default;
		constexpr cumulation& operator=(cumulation&&) noexcept = default;
		constexpr cumulation& operator=(const cumulation&) noexcept = default;
		PYGMALION_INLINE constexpr bool operator==(const cumulation& other) const noexcept
		{
			return true;
		}
		PYGMALION_INLINE constexpr bool operator!=(const cumulation& other) const noexcept
		{
			return false;
		}
		~cumulation() noexcept = default;
	};
}