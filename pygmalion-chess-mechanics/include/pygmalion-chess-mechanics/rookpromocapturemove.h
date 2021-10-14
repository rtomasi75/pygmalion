namespace pygmalion::chess
{
	class rookpromocapturemove :
		public promocapturemove<0x2>
	{
	public:
		constexpr rookpromocapturemove() noexcept :
			promocapturemove<0x2>()
		{

		}
		~rookpromocapturemove() noexcept = default;
		constexpr rookpromocapturemove(rookpromocapturemove&&) noexcept = default;
		constexpr rookpromocapturemove(const rookpromocapturemove&) noexcept = default;
		constexpr rookpromocapturemove& operator=(rookpromocapturemove&&) noexcept
		{
			return *this;
		}
		constexpr rookpromocapturemove& operator=(const rookpromocapturemove&) noexcept
		{
			return *this;
		}
	};
}