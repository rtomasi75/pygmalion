namespace pygmalion::chess
{
	class knightpromotionmove :
		public promotionmove
	{
	public:
		constexpr knightpromotionmove() noexcept :
			promotionmove(knight)
		{

		}
		~knightpromotionmove() noexcept = default;
		constexpr knightpromotionmove(knightpromotionmove&&) noexcept = default;
		constexpr knightpromotionmove(const knightpromotionmove&) noexcept = default;
		constexpr knightpromotionmove& operator=(knightpromotionmove&&) noexcept = default;
		constexpr knightpromotionmove& operator=(const knightpromotionmove&) noexcept = default;
	};
}