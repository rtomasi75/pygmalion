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
		void* preInitialize_Implementation(const movetableinfo& info) noexcept
		{
			return nullptr;
		}
		void postInitialize_Implementation(const movetableinfo& info, void* pData) noexcept
		{}
		void initializeValue_Implementation(movelistType& moves, const movetableinfo& info, const bitsType& bitboard, const bitsType& premask, void* pData) const noexcept
		{
			const bitsType masked{ bitboard & premask };
			moves.clear();
			for (const squareType square : ~masked)
				moves.add(motorType::move().create(square));
		}
		constexpr static bitsType calculatePremask(const movetableinfo& info) noexcept
		{
			return bitsType(squaresType::all());
		}
		movetable() noexcept :
			pygmalion::magictable<DESCRIPTOR_DYNAMICS::boardType::countSquares, DESCRIPTOR_DYNAMICS::boardType::countSquares, typename DESCRIPTOR_DYNAMICS::movelistType, movetableinfo, movetable<DESCRIPTOR_DYNAMICS>>(movetableinfo())
		{

		}
		movetable(const bitsType& factor, const size_t shift) noexcept :
			pygmalion::magictable<DESCRIPTOR_DYNAMICS::boardType::countSquares, DESCRIPTOR_DYNAMICS::boardType::countSquares, typename DESCRIPTOR_DYNAMICS::movelistType, movetableinfo, movetable<DESCRIPTOR_DYNAMICS>>(movetableinfo(), factor, shift)
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