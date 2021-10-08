namespace pygmalion::chess
{
	class queenpromotionmove :
		public promotionmove<0x3>
	{
	public:
		PYGMALION_INLINE constexpr queenpromotionmove() noexcept :
			promotionmove<0x3>()
		{

		}
		PYGMALION_INLINE ~queenpromotionmove() noexcept = default;
		PYGMALION_INLINE constexpr queenpromotionmove(queenpromotionmove&&) noexcept = default;
		PYGMALION_INLINE constexpr queenpromotionmove(const queenpromotionmove&) noexcept = default;
		PYGMALION_INLINE constexpr queenpromotionmove& operator=(queenpromotionmove&&) noexcept = default;
		PYGMALION_INLINE constexpr queenpromotionmove& operator=(const queenpromotionmove&) noexcept = default;
	};
}