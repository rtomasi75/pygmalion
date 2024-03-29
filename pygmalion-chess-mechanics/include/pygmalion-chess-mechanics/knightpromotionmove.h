namespace pygmalion::chess
{
	class knightpromotionmove :
		public promotionmove<0x0>
	{
	public:
		constexpr knightpromotionmove() noexcept :
			promotionmove<0x0>()
		{

		}
		~knightpromotionmove() noexcept = default;
		constexpr knightpromotionmove(knightpromotionmove&&) noexcept = default;
		constexpr knightpromotionmove(const knightpromotionmove&) noexcept = default;
		constexpr knightpromotionmove& operator=(knightpromotionmove&&) noexcept
		{
			return *this;
		}
		constexpr knightpromotionmove& operator=(const knightpromotionmove&) noexcept
		{
			return *this;
		}
	};
}