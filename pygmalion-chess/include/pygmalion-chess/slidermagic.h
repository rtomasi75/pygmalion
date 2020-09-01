namespace pygmalion::chess
{
	template<typename DESCRIPTOR_GENERATOR>
	class slidermagicinfo :
		public base_generator<DESCRIPTOR_GENERATOR>
	{
	public:

		using descriptorGenerator = DESCRIPTOR_GENERATOR;
#include "pygmalion-core/include_generator.h"

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

	template<typename DESCRIPTOR_GENERATOR>
	class slidermagic :
		public base_generator<DESCRIPTOR_GENERATOR>,
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
		public pygmalion::magictable<std::uint16_t, slidermagicinfo<DESCRIPTOR_GENERATOR>, typename DESCRIPTOR_GENERATOR::squaresType, slidermagic<DESCRIPTOR_GENERATOR>>
#else
		public pygmalion::magictable<typename DESCRIPTOR_GENERATOR::squaresType, slidermagicinfo<DESCRIPTOR_GENERATOR>, typename DESCRIPTOR_GENERATOR::squaresType, slidermagic<DESCRIPTOR_GENERATOR>>
#endif
	{
	public:

		using descriptorGenerator = DESCRIPTOR_GENERATOR;
#include "pygmalion-core/include_generator.h"

	private:
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
		squaresType m_IndexMask;
		static std::uint16_t encode(const squaresType mask, const squaresType bitboard) noexcept
		{
			return static_cast<std::uint16_t>(bitboard.pext(mask).bits());
		}
		static squaresType decode(const std::uint16_t code, const squaresType mask) noexcept
		{
			return bitsType(code).pdep(mask);
		}
		static squaresType indexMask(const squareType square, const bool isDiagonal) noexcept;
#endif
	public:
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
		static void initializeValue_Implementation(std::uint16_t& index, const slidermagicinfo<descriptorGenerator>& info, const squaresType bitboard, const squaresType premask) noexcept;
#else
		static void initializeValue_Implementation(squaresType& value, const slidermagicinfo<descriptorGenerator>& info, const squaresType bitboard, const squaresType premask) noexcept;
#endif
		static squaresType calculatePremask(const slidermagicinfo<descriptorGenerator>& info) noexcept 
		{
			assert(info.square().isValid());
			squaresType result{ squaresType::empty() };
			const auto rank{ info.square().rank() };
			const auto file{ info.square().file() };
			int r;
			int f;
			if (info.isDiagonal())
			{
				for (r = rank + 1, f = file + 1; r <= 6 && f <= 6; r++, f++)
					result.setBit(squareType::fromRankFile(r, f));
				for (r = rank + 1, f = file - 1; r <= 6 && f >= 1; r++, f--)
					result.setBit(squareType::fromRankFile(r, f));
				for (r = rank - 1, f = file + 1; r >= 1 && f <= 6; r--, f++)
					result.setBit(squareType::fromRankFile(r, f));
				for (r = rank - 1, f = file - 1; r >= 1 && f >= 1; r--, f--)
					result.setBit(squareType::fromRankFile(r, f));
			}
			else
			{
				for (r = rank + 1; r <= 6; r++)
					result.setBit(squareType::fromRankFile(r, file));
				for (r = rank - 1; r >= 1; r--)
					result.setBit(squareType::fromRankFile(r, file));
				for (f = file + 1; f <= 6; f++)
					result.setBit(squareType::fromRankFile(rank, f));
				for (f = file - 1; f >= 1; f--)
					result.setBit(squareType::fromRankFile(rank, f));
			}
			return result;
		}
		slidermagic(const slidermagicinfo<descriptorGenerator>& info) noexcept :
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
			pygmalion::magictable<std::uint16_t, slidermagicinfo<descriptorGenerator>, squaresType, slidermagic<descriptorGenerator>, true>(info),
			m_IndexMask{ indexMask(info.square(),info.isDiagonal()) }
#else
			pygmalion::magictable<squaresType, slidermagicinfo<descriptorGenerator>, squaresType, slidermagic<descriptorGenerator>, false>(info)
#endif
		{
		}
#if !(defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64))
		slidermagic(const slidermagicinfo<descriptorGenerator>& info, const squaresType factor) noexcept :
			pygmalion::magictable<squaresType, slidermagicinfo<descriptorGenerator>, squaresType, slidermagic<descriptorGenerator>, false>(info, factor)
		{
		}
#endif
		slidermagic() noexcept = default;
		slidermagic(const slidermagic&) noexcept = default;
		constexpr slidermagic(slidermagic&&) noexcept = default;
		~slidermagic() noexcept = default;
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
		squaresType operator[](const squaresType& blockers) const
		{
			return decode(value(blockers), m_IndexMask);
		}
#else
		const squaresType& operator[](const squaresType blockers) const
		{
			return value(blockers);
		}
#endif
		slidermagic& operator=(const slidermagic&) noexcept = default;
		slidermagic& operator=(slidermagic&&) noexcept = default;
	};

}