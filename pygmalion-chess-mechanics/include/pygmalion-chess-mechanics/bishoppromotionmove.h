namespace pygmalion::chess
{
	class bishoppromotionmove :
		public promotionmove<0x1>
	{
	public:
		PYGMALION_INLINE constexpr bishoppromotionmove() noexcept :
			promotionmove<0x1>()
		{

		}
		PYGMALION_INLINE ~bishoppromotionmove() noexcept = default;
		PYGMALION_INLINE constexpr bishoppromotionmove(bishoppromotionmove&&) noexcept = default;
		PYGMALION_INLINE constexpr bishoppromotionmove(const bishoppromotionmove&) noexcept = default;
		PYGMALION_INLINE constexpr bishoppromotionmove& operator=(bishoppromotionmove&&) noexcept = default;
		PYGMALION_INLINE constexpr bishoppromotionmove& operator=(const bishoppromotionmove&) noexcept = default;
	};
}