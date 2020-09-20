namespace pygmalion::chess
{
	class bishoppromocapturemove :
		public promocapturemove
	{
	public:
		constexpr bishoppromocapturemove() noexcept :
			promocapturemove(bishop)
		{

		}
		~bishoppromocapturemove() noexcept = default;
		constexpr bishoppromocapturemove(bishoppromocapturemove&&) noexcept = default;
		constexpr bishoppromocapturemove(const bishoppromocapturemove&) noexcept = default;
		constexpr bishoppromocapturemove& operator=(bishoppromocapturemove&&) noexcept = default;
		constexpr bishoppromocapturemove& operator=(const bishoppromocapturemove&) noexcept = default;
	};
}