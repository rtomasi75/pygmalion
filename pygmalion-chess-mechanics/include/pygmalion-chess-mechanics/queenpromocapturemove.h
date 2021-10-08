namespace pygmalion::chess
{
	class queenpromocapturemove :
		public promocapturemove<0x3>
	{
	public:
		PYGMALION_INLINE constexpr queenpromocapturemove() noexcept :
			promocapturemove<0x3>()
		{

		}
		PYGMALION_INLINE ~queenpromocapturemove() noexcept = default;
		PYGMALION_INLINE constexpr queenpromocapturemove(queenpromocapturemove&&) noexcept = default;
		PYGMALION_INLINE constexpr queenpromocapturemove(const queenpromocapturemove&) noexcept = default;
		PYGMALION_INLINE constexpr queenpromocapturemove& operator=(queenpromocapturemove&&) noexcept = default;
		PYGMALION_INLINE constexpr queenpromocapturemove& operator=(const queenpromocapturemove&) noexcept = default;
	};
}