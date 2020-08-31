namespace pygmalion::tictactoe
{
	using movetableinfo = bool;

	template<typename DESCRIPTOR_GENERATOR>
	class movetable :
		public pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movetableinfo, typename DESCRIPTOR_GENERATOR::squaresType::bitsType, movetable<DESCRIPTOR_GENERATOR>>
	{
	public:
		using descriptorGenerator = DESCRIPTOR_GENERATOR;
#include "pygmalion-core/include_generator.h"

		using bitsType = typename squaresType::bitsType;
	public:
		static void initializeValue_Implementation(movelistType& moves, const movetableinfo& info, const bitsType bitboard, const bitsType premask) noexcept
		{
			const bitsType masked{ bitboard & premask };
			moves.clear();
			for (const auto square : ~masked)
				moves.add(moveType({ static_cast<squareType>(square) }, {}, 0));
		}
		constexpr static bitsType calculatePremask(const movetableinfo& info) noexcept
		{
			return bitsType(bitsType::universe().bits() & ((1 << bitsType::countBits) - 1));
		}
		movetable() noexcept :
			pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movetableinfo, typename DESCRIPTOR_GENERATOR::squaresType::bitsType, movetable<DESCRIPTOR_GENERATOR>>(movetableinfo())
		{

		}
		movetable(const bitsType premask, const bitsType factor, const std::uint8_t countBits) noexcept :
			pygmalion::magictable<typename DESCRIPTOR_GENERATOR::movelistType, movetableinfo, typename DESCRIPTOR_GENERATOR::squaresType::bitsType, movetable<DESCRIPTOR_GENERATOR>>(movetableinfo(), premask, factor, countBits)
		{

		}
		movetable(const movetable&) noexcept = default;
		constexpr movetable(movetable&&) noexcept = default;
		~movetable() noexcept = default;
		const movelistType& operator[](const bitsType& occupancy) const
		{
			return this->value(occupancy);
		}
		movetable& operator=(const movetable&) noexcept = default;
		movetable& operator=(movetable&&) noexcept = default;

	};

}