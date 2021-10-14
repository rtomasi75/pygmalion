namespace pygmalion::chess
{
	class rookpromotionmove :
		public promotionmove<0x2>
	{
	public:
		constexpr rookpromotionmove() noexcept :
			promotionmove<0x2>()
		{

		}
		~rookpromotionmove() noexcept = default;
		constexpr rookpromotionmove(rookpromotionmove&&) noexcept = default;
		constexpr rookpromotionmove(const rookpromotionmove&) noexcept = default;
		constexpr rookpromotionmove& operator=(rookpromotionmove&&) noexcept
		{
			return *this;
		}
		constexpr rookpromotionmove& operator=(const rookpromotionmove&) noexcept
		{
			return *this;
		}
	};
}