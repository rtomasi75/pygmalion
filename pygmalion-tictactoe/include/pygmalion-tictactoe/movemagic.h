namespace pygmalion::tictactoe
{
	class movemagicinfo
	{
	public:
		constexpr movemagicinfo() noexcept = default;
		constexpr movemagicinfo(const movemagicinfo&) noexcept = default;
		constexpr movemagicinfo(movemagicinfo&&) noexcept = default;
		~movemagicinfo() noexcept = default;
		constexpr movemagicinfo& operator=(const movemagicinfo&) noexcept = default;
		constexpr movemagicinfo& operator=(movemagicinfo&&) noexcept = default;
	};

	template<typename DESCRIPTOR_GENERATOR>
	class movemagic :
		public base_generator<DESCRIPTOR_GENERATOR>,
#if defined(PYGMALION_CPU_BMI2)
		public pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movemagicinfo, typename DESCRIPTOR_GENERATOR::squaresType, movemagic<DESCRIPTOR_GENERATOR>, true>
#else
		public pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movemagicinfo, typename DESCRIPTOR_GENERATOR::squaresType, movemagic<DESCRIPTOR_GENERATOR>, false>
#endif
	{
	public:
		using descriptorGenerator = DESCRIPTOR_GENERATOR;
#include "pygmalion-core/include_generator.h"

	private:
	public:
		static void initializeValue_Implementation(movelistType& moves, const movemagicinfo& info, const squaresType bitboard, const squaresType premask) noexcept
		{
			const squaresType masked{ bitboard & premask };
			moves.clear();
			for (const squareType square : ~masked)
				moves.add(moveType({ square }, {}, 0));
		}
		constexpr static squaresType calculatePremask(const movemagicinfo& info) noexcept
		{
			return squaresType(squaresType::universe().bits() & ((1 << squaresType::bitCount) - 1));
		}
		movemagic(const movemagicinfo& info) noexcept :
#if defined(PYGMALION_CPU_BMI2)
			pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movemagicinfo, typename DESCRIPTOR_GENERATOR::squaresType, movemagic<DESCRIPTOR_GENERATOR>, true>(info)
#else
			pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movemagicinfo, typename DESCRIPTOR_GENERATOR::squaresType, movemagic<DESCRIPTOR_GENERATOR>, false>(info)
#endif
		{

		}
#if !defined(PYGMALION_CPU_BMI2)
		movemagic(const movemagicinfo& info, const squaresType factor) noexcept :
			pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movemagicinfo, typename DESCRIPTOR_GENERATOR::squaresType, movemagic<DESCRIPTOR_GENERATOR>, false>(info, factor)
		{

		}
#endif
		movemagic(const movemagic&) noexcept = default;
		constexpr movemagic(movemagic&&) noexcept = default;
		~movemagic() noexcept = default;
		const movelistType& operator[](const squaresType& occupancy) const
		{
			return this->value(occupancy);
		}
		movemagic& operator=(const movemagic&) noexcept = default;
		movemagic& operator=(movemagic&&) noexcept = default;

	};

}