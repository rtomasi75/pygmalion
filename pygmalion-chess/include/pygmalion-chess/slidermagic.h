namespace pygmalion::chess
{
	struct slidermagicinfo
	{
	public:
		using squareType = typename board::square;
	private:
		squareType m_Square;
		bool m_IsDiagonal;
	public:
		constexpr slidermagicinfo() noexcept :
			m_Square{ squareType::invalid },
			m_IsDiagonal{ false }
		{
		}
		constexpr slidermagicinfo(const squareType square, const bool isDiagonal) noexcept :
			m_Square{ square },
			m_IsDiagonal{ isDiagonal }
		{

		}
		constexpr slidermagicinfo(const slidermagicinfo&) noexcept = default;
		constexpr slidermagicinfo(slidermagicinfo&&) noexcept = default;
		~slidermagicinfo() noexcept = default;
		constexpr slidermagicinfo& operator=(const slidermagicinfo&) noexcept = default;
		constexpr slidermagicinfo& operator=(slidermagicinfo&&) noexcept = default;
		constexpr auto square() const noexcept
		{
			return m_Square;
		}
		constexpr auto isDiagonal() const noexcept
		{
			return m_IsDiagonal;
		}
	};

	class slidermagic :
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
		public pygmalion::magictable<std::uint16_t, slidermagicinfo, typename board::bitsType, slidermagic, true>
#else
		public pygmalion::magictable<typename board::bitsType, slidermagicinfo, typename board::bitsType, slidermagic, false>
#endif
	{
	public:
		using bitsType = typename board::bitsType;
		using squareType = typename board::square;
	private:
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
		bitsType m_IndexMask;
		static std::uint16_t encode(const bitsType mask, const bitsType bitboard) noexcept
		{
			return static_cast<std::uint16_t>(bitboard.pext(mask).bits());
		}
		static bitsType decode(const std::uint16_t code, const bitsType mask) noexcept
		{
			return bitsType(code).pdep(mask);
		}
		static bitsType indexMask(const squareType square, const bool isDiagonal) noexcept;
#endif
	public:
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
		static void initializeValue_Implementation(std::uint16_t& index, const slidermagicinfo& info, const bitsType bitboard, const bitsType premask) noexcept;
#else
		static void initializeValue_Implementation(bitsType& value, const slidermagicinfo& info, const bitsType bitboard, const bitsType premask) noexcept;
#endif
		static bitsType calculatePremask(const slidermagicinfo& info) noexcept;
		slidermagic(const slidermagicinfo& info) noexcept :
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
			pygmalion::magictable<std::uint16_t, slidermagicinfo, typename board::bitsType, slidermagic, true>(info),
			m_IndexMask{ indexMask(info.square(),info.isDiagonal()) }
#else
			pygmalion::magictable<typename board::bitsType, slidermagicinfo, typename board::bitsType, slidermagic, false>(info)
#endif
		{
		}
#if !(defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64))
		slidermagic(const slidermagicinfo& info, const bitsType factor) noexcept :
			pygmalion::magictable<typename board::bitsType, slidermagicinfo, typename board::bitsType, slidermagic, false>(info, factor)
		{
		}
#endif
		slidermagic() noexcept = default;
		slidermagic(const slidermagic&) noexcept = default;
		constexpr slidermagic(slidermagic&&) noexcept = default;
		~slidermagic() noexcept = default;
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
		bitsType operator[](const bitsType& blockers) const
		{
			return decode(value(blockers), m_IndexMask);
		}
#else
		const bitsType& operator[](const bitsType blockers) const
		{
			return value(blockers);
		}
#endif
		slidermagic& operator=(const slidermagic&) noexcept = default;
		slidermagic& operator=(slidermagic&&) noexcept = default;
	};

}