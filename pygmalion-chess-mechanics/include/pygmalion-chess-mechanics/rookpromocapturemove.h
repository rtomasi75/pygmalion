namespace pygmalion::chess
{
	class rookpromocapturemove :
		public promocapturemove
	{
	public:
		constexpr rookpromocapturemove() noexcept :
			promocapturemove(rook)
		{

		}
		~rookpromocapturemove() noexcept = default;
		constexpr rookpromocapturemove(rookpromocapturemove&&) noexcept = default;
		constexpr rookpromocapturemove(const rookpromocapturemove&) noexcept = default;
		constexpr rookpromocapturemove& operator=(rookpromocapturemove&&) noexcept = default;
		constexpr rookpromocapturemove& operator=(const rookpromocapturemove&) noexcept = default;
	};
}