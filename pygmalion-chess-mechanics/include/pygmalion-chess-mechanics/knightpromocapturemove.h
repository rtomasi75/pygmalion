namespace pygmalion::chess
{
	class knightpromocapturemove :
		public promocapturemove<0x0>
	{
	public:
		constexpr knightpromocapturemove() noexcept :
			promocapturemove<0x0>()
		{

		}
		~knightpromocapturemove() noexcept = default;
		constexpr knightpromocapturemove(knightpromocapturemove&&) noexcept = default;
		constexpr knightpromocapturemove(const knightpromocapturemove&) noexcept = default;
		constexpr knightpromocapturemove& operator=(knightpromocapturemove&&) noexcept
		{
			return *this;
		}
		constexpr knightpromocapturemove& operator=(const knightpromocapturemove&) noexcept
		{
			return *this;
		}
	};
}