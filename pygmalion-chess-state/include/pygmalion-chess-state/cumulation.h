namespace pygmalion::chess::state
{
	struct cumulation
	{
	private:
		materialScore m_Material;
		std::uint16_t m_ReversiblePlies;
	public:
		constexpr void clear() noexcept
		{
			m_Material = materialScore::zero();
			m_ReversiblePlies = 0;
		}
		constexpr const materialScore& score() const noexcept
		{
			return m_Material;
		}
		constexpr materialScore& score() noexcept
		{
			return m_Material;
		}
		constexpr const std::uint16_t& reversiblePlies() const noexcept
		{
			return m_ReversiblePlies;
		}
		constexpr std::uint16_t& reversiblePlies() noexcept
		{
			return m_ReversiblePlies;
		}
		constexpr cumulation() noexcept :
			m_Material{ materialScore::zero() },
			m_ReversiblePlies{ 0 }
		{
		}
		constexpr cumulation(cumulation&&) noexcept = default;
		constexpr cumulation(const cumulation&) noexcept = default;
		constexpr cumulation& operator=(cumulation&&) noexcept = default;
		constexpr cumulation& operator=(const cumulation&) noexcept = default;
		~cumulation() noexcept = default;
	};
}