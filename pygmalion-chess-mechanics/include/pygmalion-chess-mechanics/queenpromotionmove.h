namespace pygmalion::chess
{
	class queenpromotionmove :
		public promotionmove
	{
	public:
		constexpr queenpromotionmove() noexcept :
			promotionmove(queen)
		{

		}
		~queenpromotionmove() noexcept = default;
		constexpr queenpromotionmove(queenpromotionmove&&) noexcept = default;
		constexpr queenpromotionmove(const queenpromotionmove&) noexcept = default;
		constexpr queenpromotionmove& operator=(queenpromotionmove&&) noexcept = default;
		constexpr queenpromotionmove& operator=(const queenpromotionmove&) noexcept = default;
	};
}