namespace pygmalion::tictactoe
{
	struct movemagicinfo
	{
	public:
		constexpr movemagicinfo() noexcept = default;
		constexpr movemagicinfo(const movemagicinfo&) noexcept = default;
		constexpr movemagicinfo(movemagicinfo&&) noexcept = default;
		~movemagicinfo() noexcept = default;
		constexpr movemagicinfo& operator=(const movemagicinfo&) noexcept = default;
		constexpr movemagicinfo& operator=(movemagicinfo&&) noexcept = default;
	};

	class movemagic :
#if defined(PYGMALION_CPU_BMI2)
		public pygmalion::magictable<typename movegen::movelistType, movemagicinfo, typename board::bitsType, movemagic, true>
#else
		public pygmalion::magictable<typename movegen::movelistType, movemagicinfo, typename board::bitsType, movemagic, false>
#endif
	{
	public:
		using bitsType = typename board::bitsType;
		using movelistType = typename movegen::movelistType;
		using moveType = typename movegen::moveType;
	private:
	public:
		static void initializeValue_Implementation(movelistType& moves, const movemagicinfo& info, const bitsType& bitboard, const bitsType& premask) noexcept
		{
			const bitsType masked{ bitboard & premask };
			moves.clear();
			for (const auto square : ~masked)
				moves.add(moveType(square));
		}
		constexpr static bitsType calculatePremask(const movemagicinfo& info) noexcept
		{
			return bitsType::universe();
		}
		movemagic(const movemagicinfo& info) noexcept :
#if defined(PYGMALION_CPU_BMI2)
			pygmalion::magictable<typename movegen::movelistType, movemagicinfo, typename board::bitsType, movemagic, true>(info)
#else
			pygmalion::magictable<typename movegen::movelistType, movemagicinfo, typename board::bitsType, movemagic, false>(info)
#endif
		{

		}
#if !defined(PYGMALION_CPU_BMI2)
		movemagic(const movemagicinfo& info, const bitsType factor) noexcept :
			pygmalion::magictable<typename movegen::movelistType, movemagicinfo, typename board::bitsType, movemagic, false>(info, factor)
		{

		}
#endif
		movemagic(const movemagic&) noexcept = default;
		constexpr movemagic(movemagic&&) noexcept = default;
		~movemagic() noexcept = default;
		const movelistType& operator[](const bitsType& occupancy) const
		{
			return value(occupancy);
		}
		movemagic& operator=(const movemagic&) noexcept = default;
		movemagic& operator=(movemagic&&) noexcept = default;

	};

}