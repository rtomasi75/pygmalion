namespace pygmalion::chess::state
{
	struct cumulation
	{
	private:
		materialScore m_Material;
	public:
		constexpr void clear() noexcept
		{
			m_Material = materialScore::zero();
		}
		constexpr const materialScore& score() const noexcept
		{
			return m_Material;
		}
		constexpr materialScore& score() noexcept
		{
			return m_Material;
		}
		constexpr cumulation() noexcept :
			m_Material{ materialScore::zero()}
		{
		}
		constexpr cumulation(cumulation&&) noexcept = default;
		constexpr cumulation(const cumulation&) noexcept = default;
		constexpr cumulation& operator=(cumulation&&) noexcept = default;
		constexpr cumulation& operator=(const cumulation&) noexcept = default;
		~cumulation() noexcept = default;
	};
}