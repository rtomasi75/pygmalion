namespace pygmalion::chess
{
	class rookpromotionmove :
		public promotionmove
	{
	public:
		constexpr rookpromotionmove() noexcept :
			promotionmove(rook)
		{

		}
		~rookpromotionmove() noexcept = default;
		constexpr rookpromotionmove(rookpromotionmove&&) noexcept = default;
		constexpr rookpromotionmove(const rookpromotionmove&) noexcept = default;
		constexpr rookpromotionmove& operator=(rookpromotionmove&&) noexcept = default;
		constexpr rookpromotionmove& operator=(const rookpromotionmove&) noexcept = default;
	};
}