namespace pygmalion::chess
{
	class rookpromocapturemove :
		public promocapturemove<0x2>
	{
	public:
		PYGMALION_INLINE constexpr rookpromocapturemove() noexcept :
			promocapturemove<0x2>()
		{

		}
		PYGMALION_INLINE ~rookpromocapturemove() noexcept = default;
		PYGMALION_INLINE constexpr rookpromocapturemove(rookpromocapturemove&&) noexcept = default;
		PYGMALION_INLINE constexpr rookpromocapturemove(const rookpromocapturemove&) noexcept = default;
		PYGMALION_INLINE constexpr rookpromocapturemove& operator=(rookpromocapturemove&&) noexcept = default;
		PYGMALION_INLINE constexpr rookpromocapturemove& operator=(const rookpromocapturemove&) noexcept = default;
	};
}