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
#if defined(PYGMALION_CPU_BMI2)
		public pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movemagicinfo, typename DESCRIPTOR_GENERATOR::squaresType::bitsType, movemagic<DESCRIPTOR_GENERATOR>, true>
#else
		public pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movemagicinfo, typename DESCRIPTOR_GENERATOR::squaresType::bitsType, movemagic<DESCRIPTOR_GENERATOR>, false>
#endif
	{
	public:
		using descriptorGenerator = DESCRIPTOR_GENERATOR;
#include "pygmalion-core/include_generator.h"

		using bitsType = typename squaresType::bitsType;
	public:
		static void initializeValue_Implementation(movelistType& moves, const movemagicinfo& info, const bitsType bitboard, const bitsType premask) noexcept
		{
			const bitsType masked{ bitboard & premask };
			moves.clear();
			for (const auto square : ~masked)
				moves.add(moveType({ static_cast<squareType>(square) }, {}, 0));
		}
		constexpr static bitsType calculatePremask(const movemagicinfo& info) noexcept
		{
			return bitsType(bitsType::universe().bits() & ((1 << bitsType::bitCount) - 1));
		}
		movemagic(const movemagicinfo& info) noexcept :
#if defined(PYGMALION_CPU_BMI2)
			pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movemagicinfo, typename DESCRIPTOR_GENERATOR::squaresType::bitsType, movemagic<DESCRIPTOR_GENERATOR>, true>(info)
#else
			pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movemagicinfo, typename DESCRIPTOR_GENERATOR::squaresType::bitsType, movemagic<DESCRIPTOR_GENERATOR>, false>(info)
#endif
		{

		}
#if !defined(PYGMALION_CPU_BMI2)
		movemagic(const movemagicinfo& info, const bitsType factor) noexcept :
			pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movemagicinfo, typename DESCRIPTOR_GENERATOR::squaresType::bitsType, movemagic<DESCRIPTOR_GENERATOR>, false>(info, static_cast<typename DESCRIPTOR_GENERATOR::squaresType::bitsType>(factor))
		{

		}
#endif
		movemagic(const movemagic&) noexcept = default;
		constexpr movemagic(movemagic&&) noexcept = default;
		~movemagic() noexcept = default;
		const movelistType& operator[](const bitsType& occupancy) const
		{
			return this->value(occupancy);
		}
		movemagic& operator=(const movemagic&) noexcept = default;
		movemagic& operator=(movemagic&&) noexcept = default;

	};

}