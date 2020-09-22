namespace pygmalion::chess::dynamics
{
	template<typename DESCRIPTOR_DYNAMICS>
	class slidermagicinfo :
		public DESCRIPTOR_DYNAMICS
	{
	public:

		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include "pygmalion-dynamics/include_dynamics.h"

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

	template<typename DESCRIPTOR_DYNAMICS>
	class slidermagic :
		public DESCRIPTOR_DYNAMICS,
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
		public pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, slidermagicinfo<DESCRIPTOR_DYNAMICS>, std::uint16_t, slidermagic<DESCRIPTOR_DYNAMICS>>
#else
		public pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, typename DESCRIPTOR_DYNAMICS::squaresType, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS>>
#endif
	{
	public:
		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include "pygmalion-dynamics/include_dynamics.h"
	private:
#if defined(PYGMALION_CPU_BMI2)&& (defined(PYGMALION_CPU_X64)||defined(PYGMALION_CPU_X86))
		using parentType = pygmalion::magictable<descriptorDynamics::squaresType::countSquares, descriptorDynamics::squaresType::countSquares, slidermagicinfo<descriptorDynamics>, std::uint16_t, slidermagic<descriptorDynamics>>;
		using bitsType = typename parentType::bitsType;
		bitsType m_IndexMask;
		static std::uint16_t encode(const bitsType& mask, const bitsType& bitboard) noexcept
		{
			return static_cast<std::uint16_t>(bitboard.extractPattern(mask));
		}
		static squaresType decode(const std::uint16_t code, const bitsType& mask) noexcept
		{
			return static_cast<squaresType>(bitsType(code).deposePattern(mask));
		}
		bitsType indexMask(const squareType square, const bool isDiagonal) noexcept
		{
			return sliderAttacks_untabled(square, squaresType::none(), isDiagonal).bits();
		}
#else
		using parentType = pygmalion::magictable<descriptorDynamics::squaresType::countSquares, descriptorDynamics::squaresType::countSquares, typename descriptorDynamics::squaresType, slidermagicinfo<descriptorDynamics>, slidermagic<descriptorDynamics>>;
#endif
		using bitsType = typename parentType::bitsType;
		static squaresType sliderAttacks_untabled(const squareType square, const squaresType& blockers, const bool bDiag) noexcept
		{
			assert(square.isValid());
			squaresType result{ squaresType::none() };
			const rankType rank{ square.rank() };
			const fileType file{ square.file() };
			rankType r;
			fileType f;
			if (bDiag)
			{
				for (r = rank + 1, f = file + 1; (r < countRanks) && (f < countFiles); r++, f++)
				{
					const squareType sq{ r & f };
					result |= sq;
					if (blockers[sq])
						break;
				}
				for (r = rank + 1, f = file - 1; (r < countRanks) && (f >= 0); r++, f--)
				{
					const squareType sq{ r & f };
					result |= sq;
					if (blockers[sq])
						break;
				}
				for (r = rank - 1, f = file + 1; (r >= 0) && (f < countFiles); r--, f++)
				{
					const squareType sq{ r & f };
					result |= sq;
					if (blockers[sq])
						break;
				}
				for (r = rank - 1, f = file - 1; (r >= 0) && (f >= 0); r--, f--)
				{
					const squareType sq{ r & f };
					result |= sq;
					if (blockers[sq])
						break;
				}
			}
			else
			{
				for (r = rank + 1; r < countRanks; r++)
				{
					const squareType sq{ r & file };
					result |= sq;
					if (blockers[sq])
						break;
				}
				for (r = rank - 1; r >= 0; r--)
				{
					const squareType sq{ r & file };
					result |= sq;
					if (blockers[sq])
						break;
				}
				for (f = file + 1; f < countFiles; f++)
				{
					const squareType sq{ rank & f };
					result |= sq;
					if (blockers[sq])
						break;
				}
				for (f = file - 1; f >= 0; f--)
				{
					const squareType sq{ rank & f };
					result |= sq;
					if (blockers[sq])
						break;
				}
			}
			return result;
		}
	public:
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
		void initializeValue_Implementation(std::uint16_t& index, const slidermagicinfo<descriptorDynamics>& info, const bitsType& bitboard, const bitsType& premask) noexcept
		{
			assert(info.square().isValid());
			index = encode(indexMask(info.square(), info.isDiagonal()), sliderAttacks_untabled(info.square(), bitboard, info.isDiagonal()));
		}
#else
		void initializeValue_Implementation(squaresType& value, const slidermagicinfo<descriptorDynamics>& info, const bitsType& bitboard, const bitsType& premask) noexcept
		{
			assert(info.square().isValid());
			value = generatorType::sliderAttacks_untabled(info.square(), bitboard, info.isDiagonal());
		}
#endif
		static bitsType calculatePremask(const slidermagicinfo<descriptorDynamics>& info) noexcept
		{
			assert(info.square().isValid());
			squaresType squares{ bitsType::empty() };
			const auto rank{ info.square().rank() };
			const auto file{ info.square().file() };
			int r;
			int f;
			if (info.isDiagonal())
			{
				for (r = rank + 1, f = file + 1; (r < (countRanks - 1)) && (f < (countFiles - 1)); r++, f++)
					squares |= (r & f);
				for (r = rank + 1, f = file - 1; (r < (countRanks - 1)) && (f > 0); r++, f--)
					squares |= (r & f);
				for (r = rank - 1, f = file + 1; (r > 0) && (f < (countFiles - 1)); r--, f++)
					squares |= (r & f);
				for (r = rank - 1, f = file - 1; (r > 0) && (f > 0); r--, f--)
					squares |= (r & f);
			}
			else
			{
				for (r = rank + 1; (r < (countRanks - 1)); r++)
					squares |= (r & file);
				for (r = rank - 1; (r > 0); r--)
					squares |= (r & file);
				for (f = file + 1; (f < (countFiles - 1)); f++)
					squares |= (rank & f);
				for (f = file - 1; (f > 0); f--)
					squares |= (rank & f);
			}
			return static_cast<bitsType>(squares);
		}
		slidermagic(const slidermagicinfo<descriptorDynamics>& info) noexcept :
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
			parentType(info),
			m_IndexMask{ indexMask(info.square(),info.isDiagonal()) }
#else
			parentType(info)
#endif
		{
		}
#if !(defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64))
		slidermagic(const slidermagicinfo<descriptorDynamics>& info, const squaresType& factor) noexcept :
			parentType(info, factor)
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
		const squaresType& operator[](const squaresType& blockers) const
		{
			return value(static_cast<bitsType>(blockers));
		}
#endif
		slidermagic& operator=(const slidermagic&) noexcept = default;
		slidermagic& operator=(slidermagic&&) noexcept = default;
	};

}