namespace pygmalion::chess
{
	class queenpromocapturemove :
		public promocapturemove<0x3>
	{
	public:
		constexpr queenpromocapturemove() noexcept :
			promocapturemove<0x3>()
		{

		}
		~queenpromocapturemove() noexcept = default;
		constexpr queenpromocapturemove(queenpromocapturemove&&) noexcept = default;
		constexpr queenpromocapturemove(const queenpromocapturemove&) noexcept = default;
		constexpr queenpromocapturemove& operator=(queenpromocapturemove&&) noexcept
		{
			return *this;
		}
		constexpr queenpromocapturemove& operator=(const queenpromocapturemove&) noexcept
		{
			return *this;
		}
	};
}