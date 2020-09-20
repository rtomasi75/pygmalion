namespace pygmalion::chess
{
	class bishoppromotionmove :
		public promotionmove
	{
	public:
		constexpr bishoppromotionmove() noexcept :
			promotionmove(bishop)
		{

		}
		~bishoppromotionmove() noexcept = default;
		constexpr bishoppromotionmove(bishoppromotionmove&&) noexcept = default;
		constexpr bishoppromotionmove(const bishoppromotionmove&) noexcept = default;
		constexpr bishoppromotionmove& operator=(bishoppromotionmove&&) noexcept = default;
		constexpr bishoppromotionmove& operator=(const bishoppromotionmove&) noexcept = default;
	};
}