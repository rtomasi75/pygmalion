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
		constexpr static squaresType notFileH{ 0x7f7f7f7f7f7f7f7f };
		constexpr static squaresType notFileA{ 0xfefefefefefefefe };
		constexpr static squaresType notRank1{ 0xffffffffffffff00 };
		constexpr static squaresType notRank8{ 0x00ffffffffffffff };
		constexpr static squaresType right(const squaresType bits) noexcept
		{
			return (bits & notFileH) << 1;
		}
		constexpr static squaresType rightFast(const squaresType bits) noexcept
		{
			return bits << 1;
		}
		constexpr static squaresType left(const squaresType bits) noexcept
		{
			return (bits & notFileA) >> 1;
		}
		constexpr static squaresType left_lazy(const squaresType bits) noexcept
		{
			return bits >> 1;
		}
		constexpr static squaresType down(const squaresType bits) noexcept
		{
			return bits >> 8;
		}
		constexpr static squaresType up(const squaresType bits) noexcept
		{
			return bits << 8;
		}
		constexpr static squaresType downRight(const squaresType bits) noexcept
		{
			return (bits & notFileH) >> 7;
		}
		constexpr static squaresType downRight_lazy(const squaresType bits) noexcept
		{
			return bits >> 7;
		}
		constexpr static squaresType upRight(const squaresType bits) noexcept
		{
			return (bits & notFileH) << 9;
		}
		constexpr static squaresType upRight_lazy(const squaresType bits) noexcept
		{
			return bits << 9;
		}
		constexpr static squaresType downLeft(const squaresType bits) noexcept
		{
			return (bits & notFileA) >> 9;
		}
		constexpr static squaresType downLeft_lazy(const squaresType bits) noexcept
		{
			return bits >> 9;
		}
		constexpr static squaresType upLeft(const squaresType bits) noexcept
		{
			return (bits & notFileA) << 7;
		}
		constexpr static squaresType upLeft_lazy(const squaresType bits) noexcept
		{
			return bits << 7;
		}
		constexpr static squaresType upUpLeft(const squaresType bits) noexcept
		{
			return up(upLeft(bits));
		}
		constexpr static squaresType upUpRight(const squaresType bits) noexcept
		{
			return up(upRight(bits));
		}
		constexpr static squaresType downDownLeft(const squaresType bits) noexcept
		{
			return down(downLeft(bits));
		}
		constexpr static squaresType downDownRight(const squaresType bits) noexcept
		{
			return down(downRight(bits));
		}
		constexpr static squaresType upLeftLeft(const squaresType bits) noexcept
		{
			return upLeft(left(bits));
		}
		constexpr static squaresType downLeftLeft(const squaresType bits) noexcept
		{
			return downLeft(left(bits));
		}
		constexpr static squaresType upRightRight(const squaresType bits) noexcept
		{
			return upRight(right(bits));
		}
		constexpr static squaresType downRightRight(const squaresType bits) noexcept
		{
			return downRight(right(bits));
		}
	};
}