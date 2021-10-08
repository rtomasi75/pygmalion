namespace pygmalion::chess
{
	class rookpromotionmove :
		public promotionmove<0x2>
	{
	public:
		PYGMALION_INLINE constexpr rookpromotionmove() noexcept :
			promotionmove<0x2>()
		{

		}
		PYGMALION_INLINE ~rookpromotionmove() noexcept = default;
		PYGMALION_INLINE constexpr rookpromotionmove(rookpromotionmove&&) noexcept = default;
		PYGMALION_INLINE constexpr rookpromotionmove(const rookpromotionmove&) noexcept = default;
		PYGMALION_INLINE constexpr rookpromotionmove& operator=(rookpromotionmove&&) noexcept = default;
		PYGMALION_INLINE constexpr rookpromotionmove& operator=(const rookpromotionmove&) noexcept = default;
	};
}