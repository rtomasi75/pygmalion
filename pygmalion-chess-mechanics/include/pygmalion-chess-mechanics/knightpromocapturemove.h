namespace pygmalion::chess
{
	class knightpromocapturemove :
		public promocapturemove
	{
	public:
		constexpr knightpromocapturemove() noexcept :
			promocapturemove(knight)
		{

		}
		~knightpromocapturemove() noexcept = default;
		constexpr knightpromocapturemove(knightpromocapturemove&&) noexcept = default;
		constexpr knightpromocapturemove(const knightpromocapturemove&) noexcept = default;
		constexpr knightpromocapturemove& operator=(knightpromocapturemove&&) noexcept = default;
		constexpr knightpromocapturemove& operator=(const knightpromocapturemove&) noexcept = default;
	};
}