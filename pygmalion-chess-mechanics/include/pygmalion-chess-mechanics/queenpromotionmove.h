namespace pygmalion::chess
{
	class queenpromotionmove :
		public promotionmove<0x3>
	{
	public:
		constexpr queenpromotionmove() noexcept :
			promotionmove<0x3>()
		{

		}
		~queenpromotionmove() noexcept = default;
		constexpr queenpromotionmove(queenpromotionmove&&) noexcept = default;
		constexpr queenpromotionmove(const queenpromotionmove&) noexcept = default;
		constexpr queenpromotionmove& operator=(queenpromotionmove&&) noexcept
		{
			return *this;
		}
		constexpr queenpromotionmove& operator=(const queenpromotionmove&) noexcept
		{
			return *this;
		}
	};
}