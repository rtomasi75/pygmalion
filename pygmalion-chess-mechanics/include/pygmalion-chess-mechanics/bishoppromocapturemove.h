namespace pygmalion::chess
{
	class bishoppromocapturemove :
		public promocapturemove<0x1>
	{
	public:
		PYGMALION_INLINE constexpr bishoppromocapturemove() noexcept :
			promocapturemove<0x1>()
		{

		}
		PYGMALION_INLINE ~bishoppromocapturemove() noexcept = default;
		PYGMALION_INLINE constexpr bishoppromocapturemove(bishoppromocapturemove&&) noexcept = default;
		PYGMALION_INLINE constexpr bishoppromocapturemove(const bishoppromocapturemove&) noexcept = default;
		PYGMALION_INLINE constexpr bishoppromocapturemove& operator=(bishoppromocapturemove&&) noexcept = default;
		PYGMALION_INLINE constexpr bishoppromocapturemove& operator=(const bishoppromocapturemove&) noexcept = default;
	};
}