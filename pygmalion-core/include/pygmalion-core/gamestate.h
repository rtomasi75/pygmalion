namespace pygmalion
{
	template<int COUNT_PLAYERS>
	class gamestate : 
		public enumeration<1 + requiredUnsignedBits(COUNT_PLAYERS), gamestate<COUNT_PLAYERS>>
	{
	public:
		using playerType = player<COUNT_PLAYERS>;
		constexpr gamestate(const gamestate&) noexcept = default;
		constexpr gamestate(gamestate&&) noexcept = default;
		constexpr gamestate() noexcept :
			enumeration<1 + requiredUnsignedBits(COUNT_PLAYERS), gamestate<COUNT_PLAYERS>>()
		{

		}
		constexpr gamestate(const typename enumeration<1 + requiredUnsignedBits(COUNT_PLAYERS), gamestate<COUNT_PLAYERS>>::baseType value) noexcept :
			enumeration<1 + requiredUnsignedBits(COUNT_PLAYERS), gamestate<COUNT_PLAYERS>>(value)
		{
		}
		constexpr gamestate(const typename enumeration<1 + requiredUnsignedBits(COUNT_PLAYERS), gamestate<COUNT_PLAYERS>>::valueType value) noexcept :
			enumeration<1 + requiredUnsignedBits(COUNT_PLAYERS), gamestate<COUNT_PLAYERS>>(value)
		{
		}
		constexpr gamestate<COUNT_PLAYERS>& operator=(gamestate<COUNT_PLAYERS>&&) noexcept = default;
		constexpr gamestate<COUNT_PLAYERS>& operator=(const gamestate<COUNT_PLAYERS>&) noexcept = default;
		constexpr static gamestate<COUNT_PLAYERS> open() noexcept
		{
			return static_cast<gamestate<COUNT_PLAYERS>>(0);
		}
		constexpr static bool isOpen(const gamestate<COUNT_PLAYERS> state) noexcept
		{
			return state == open();
		}
		constexpr static gamestate<COUNT_PLAYERS> draw() noexcept
		{
			return static_cast<gamestate<COUNT_PLAYERS>>(1);
		}
		constexpr static bool isDraw(const gamestate<COUNT_PLAYERS> state) noexcept
		{
			return state == draw();
		}
		constexpr static gamestate<COUNT_PLAYERS> loss(const playerType losingPlayer) noexcept
		{
			return static_cast<gamestate<COUNT_PLAYERS>>(2 << (losingPlayer));
		}
		constexpr static bool isLoss(const gamestate<COUNT_PLAYERS> state, const playerType p) noexcept
		{
			return state == loss(p);
		}
		constexpr static gamestate<COUNT_PLAYERS> win(const playerType winningPlayer) noexcept
		{
			gamestate<COUNT_PLAYERS> result{ 0 };
			for (const auto i : playerType::range)
			{
				if (i != winningPlayer)
					result |= loss(i);
			}
			return result;
		}
		constexpr static bool isWin(const gamestate<COUNT_PLAYERS> state, const playerType p) noexcept
		{
			return state == win(p);
		}
	};

	template<int COUNT_PLAYERS>
	std::ostream& operator<<(std::ostream& str, const gamestate<COUNT_PLAYERS> r) noexcept
	{
		const std::streamsize w{ gamestate<COUNT_PLAYERS>::countUnsignedBits / 10 + 1 };
		str << std::setw(w);
		str << std::setfill('0');
		str << std::dec;
		str << static_cast<gamestate<COUNT_PLAYERS>::baseType>(r);
	}
}