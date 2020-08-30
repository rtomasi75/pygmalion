#include <pygmalion-chess.h>

namespace pygmalion::chess
{
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
	typename slidermagic::bitsType slidermagic::indexMask(const squareType square, const bool isDiagonal) noexcept
	{
		return movegen::sliderAttacks_untabled(square, bitsType::empty(), isDiagonal);
	}

	void slidermagic::initializeValue_Implementation(std::uint16_t& index, const slidermagicinfo& info, const bitsType bitboard, const bitsType premask) noexcept
	{
		assert(info.square().isValid());
		index = encode(indexMask(info.square(), info.isDiagonal()), movegen::sliderAttacks_untabled(info.square(), bitboard, info.isDiagonal()));
	}
#else
	void slidermagic::initializeValue_Implementation(bitsType& value, const slidermagicinfo& info, const bitsType bitboard, const bitsType premask) noexcept
	{
		assert(info.square().isValid());
		value = movegen::sliderAttacks_untabled(info.square(), bitboard, info.isDiagonal());
	}

#endif


}