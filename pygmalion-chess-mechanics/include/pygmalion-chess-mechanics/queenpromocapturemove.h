namespace pygmalion::chess
{
	class queenpromocapturemove :
		public promocapturemove
	{
	public:
		constexpr queenpromocapturemove() noexcept :
			promocapturemove(queen)
		{

		}
		~queenpromocapturemove() noexcept = default;
		constexpr queenpromocapturemove(queenpromocapturemove&&) noexcept = default;
		constexpr queenpromocapturemove(const queenpromocapturemove&) noexcept = default;
		constexpr queenpromocapturemove& operator=(queenpromocapturemove&&) noexcept = default;
		constexpr queenpromocapturemove& operator=(const queenpromocapturemove&) noexcept = default;
	};
}