namespace pygmalion::chess
{

	class board : public pygmalion::board<descriptor_board>
	{
	public:
	private:
		score m_Material;
		uint8_t m_DistanceToDraw;
	public:
		constexpr score material() const noexcept
		{
			return m_Material;
		}
		constexpr score& material() noexcept
		{
			return m_Material;
		}
		constexpr uint8_t getDistanceToDraw() const noexcept
		{
			return m_DistanceToDraw;
		}
		constexpr void setDistanceToDraw(const uint8_t distance) noexcept
		{
			m_DistanceToDraw = distance;
		}
		constexpr score getMaterial() const noexcept
		{
			return m_Material;
		}
		constexpr void setMaterial(const score material) noexcept
		{
			m_Material = material;
		}
		constexpr board(const board&) noexcept = default;
		constexpr board(board&&) noexcept = default;
		~board() = default;
		board& operator=(const board&) = default;
		board& operator=(board&&) = default;
		board() noexcept;
	};
}