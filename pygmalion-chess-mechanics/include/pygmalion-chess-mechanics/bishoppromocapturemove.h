namespace pygmalion::chess
{
	class bishoppromocapturemove :
		public promocapturemove<0x1>
	{
	public:
		constexpr bishoppromocapturemove() noexcept :
			promocapturemove<0x1>()
		{

		}
		~bishoppromocapturemove() noexcept = default;
		constexpr bishoppromocapturemove(bishoppromocapturemove&&) noexcept = default;
		constexpr bishoppromocapturemove(const bishoppromocapturemove&) noexcept = default;
		constexpr bishoppromocapturemove& operator=(bishoppromocapturemove&&) noexcept = default;
		constexpr bishoppromocapturemove& operator=(const bishoppromocapturemove&) noexcept = default;
	};
}