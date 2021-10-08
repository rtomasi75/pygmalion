namespace pygmalion::chess
{
	class knightpromotionmove :
		public promotionmove<0x0>
	{
	public:
		PYGMALION_INLINE constexpr knightpromotionmove() noexcept :
			promotionmove<0x0>()
		{

		}
		PYGMALION_INLINE ~knightpromotionmove() noexcept = default;
		PYGMALION_INLINE constexpr knightpromotionmove(knightpromotionmove&&) noexcept = default;
		PYGMALION_INLINE constexpr knightpromotionmove(const knightpromotionmove&) noexcept = default;
		PYGMALION_INLINE constexpr knightpromotionmove& operator=(knightpromotionmove&&) noexcept = default;
		PYGMALION_INLINE constexpr knightpromotionmove& operator=(const knightpromotionmove&) noexcept = default;
	};
}