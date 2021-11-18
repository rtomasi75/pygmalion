namespace pygmalion::chess::state
{
	class descriptor_state;

	class cumulation
	{
	public:
		using hashType = pygmalion::uint_t<64, false>;
	private:
		hashType m_PawnHash;
		materialScore m_Material;
		constexpr static const materialScore m_Zero{ materialScore::zero() };
	public:
		PYGMALION_INLINE constexpr void clear() noexcept
		{
			m_Material = m_Zero;
			m_PawnHash = 0;
		}
		PYGMALION_INLINE constexpr const hashType& pawnHash() const noexcept
		{
			return m_PawnHash;
		}
		PYGMALION_INLINE constexpr hashType& pawnHash() noexcept
		{
			return m_PawnHash;
		}
		PYGMALION_INLINE constexpr const materialScore& score() const noexcept
		{
			return m_Material;
		}
		PYGMALION_INLINE constexpr materialScore& score() noexcept
		{
			return m_Material;
		}
		constexpr cumulation() noexcept :
			m_Material{ m_Zero },
			m_PawnHash{ 0 }
		{
		}
		constexpr cumulation(cumulation&&) noexcept = default;
		constexpr cumulation(const cumulation&) noexcept = default;
		constexpr cumulation& operator=(cumulation&&) noexcept = default;
		constexpr cumulation& operator=(const cumulation&) noexcept = default;
		PYGMALION_INLINE constexpr bool operator==(const cumulation& other) const noexcept
		{
			return m_Material == other.m_Material && m_PawnHash == other.m_PawnHash;
		}
		PYGMALION_INLINE constexpr bool operator!=(const cumulation& other) const noexcept
		{
			return m_Material != other.m_Material || m_PawnHash != other.m_PawnHash;
		}
		~cumulation() noexcept = default;
	};
}