namespace pygmalion::chess
{
	class knightpromocapturemove :
		public promocapturemove<0x0>
	{
	public:
		PYGMALION_INLINE constexpr knightpromocapturemove() noexcept :
			promocapturemove<0x0>()
		{

		}
		PYGMALION_INLINE ~knightpromocapturemove() noexcept = default;
		PYGMALION_INLINE constexpr knightpromocapturemove(knightpromocapturemove&&) noexcept = default;
		PYGMALION_INLINE constexpr knightpromocapturemove(const knightpromocapturemove&) noexcept = default;
		PYGMALION_INLINE constexpr knightpromocapturemove& operator=(knightpromocapturemove&&) noexcept = default;
		PYGMALION_INLINE constexpr knightpromocapturemove& operator=(const knightpromocapturemove&) noexcept = default;
	};
}