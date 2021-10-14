namespace pygmalion::chess
{
	class bishoppromotionmove :
		public promotionmove<0x1>
	{
	public:
		constexpr bishoppromotionmove() noexcept :
			promotionmove<0x1>()
		{

		}
		~bishoppromotionmove() noexcept = default;
		constexpr bishoppromotionmove(bishoppromotionmove&&) noexcept = default;
		constexpr bishoppromotionmove(const bishoppromotionmove&) noexcept = default;
		constexpr bishoppromotionmove& operator=(bishoppromotionmove&&) noexcept
		{
			return *this;
		}
		constexpr bishoppromotionmove& operator=(const bishoppromotionmove&) noexcept
		{
			return *this;
		}
	};
}