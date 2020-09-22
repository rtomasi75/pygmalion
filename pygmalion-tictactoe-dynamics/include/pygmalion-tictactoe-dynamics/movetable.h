namespace pygmalion::tictactoe
{
	using movetableinfo = bool;

	template<typename DESCRIPTOR_DYNAMICS>
	class movetable :
		public pygmalion::magictable<DESCRIPTOR_DYNAMICS::boardType::countSquares, DESCRIPTOR_DYNAMICS::boardType::countSquares, typename DESCRIPTOR_DYNAMICS::movelistType, movetableinfo, movetable<DESCRIPTOR_DYNAMICS>>
	{
	public:
		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include "pygmalion-dynamics/include_dynamics.h"

		using bitsType = typename squaresType::bitsType;
	public:
		static void initializeValue_Implementation(movelistType& moves, const movetableinfo& info, const bitsType& bitboard, const bitsType& premask) noexcept
		{
			const bitsType masked{ bitboard & premask };
			moves.clear();
			for (const squareType square : ~masked)
				moves.add(motorType::move().create(square));
		}
		constexpr static bitsType calculatePremask(const movetableinfo& info) noexcept
		{
			return bitsType(squaresType::all().bits());
		}
		movetable() noexcept :
			pygmalion::magictable<DESCRIPTOR_DYNAMICS::boardType::countSquares, DESCRIPTOR_DYNAMICS::boardType::countSquares, typename DESCRIPTOR_DYNAMICS::movelistType, movetableinfo, movetable<DESCRIPTOR_DYNAMICS>>(movetableinfo())
		{

		}
		movetable(const bitsType& premask, const bitsType& factor, const size_t countBits) noexcept :
			pygmalion::magictable<DESCRIPTOR_DYNAMICS::boardType::countSquares, DESCRIPTOR_DYNAMICS::boardType::countSquares, typename DESCRIPTOR_DYNAMICS::movelistType, movetableinfo, movetable<DESCRIPTOR_DYNAMICS>>(movetableinfo(), premask, factor, countBits)
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