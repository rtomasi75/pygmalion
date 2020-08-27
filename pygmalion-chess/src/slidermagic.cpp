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

	typename slidermagic::bitsType slidermagic::calculatePremask(const slidermagicinfo& info) noexcept
	{
		assert(info.square().isValid());
		using rankType = typename board::rank;
		using fileType = typename board::file;
		bitsType result{ bitsType::empty() };
		const rankType rank = board::rankOfSquare(info.square());
		const fileType file = board::fileOfSquare(info.square());
		rankType r;
		fileType f;
		if (info.isDiagonal())
		{
			for (r = rank + 1, f = file + 1; r <= 6 && f <= 6; r++, f++)
				result.setBit(board::fromRankFile(r, f));
			for (r = rank + 1, f = file - 1; r <= 6 && f >= 1; r++, f--)
				result.setBit(board::fromRankFile(r, f));
			for (r = rank - 1, f = file + 1; r >= 1 && f <= 6; r--, f++)
				result.setBit(board::fromRankFile(r, f));
			for (r = rank - 1, f = file - 1; r >= 1 && f >= 1; r--, f--)
				result.setBit(board::fromRankFile(r, f));
		}
		else
		{
			for (r = rank + 1; r <= 6; r++)
				result.setBit(board::fromRankFile(r, file));
			for (r = rank - 1; r >= 1; r--)
				result.setBit(board::fromRankFile(r, file));
			for (f = file + 1; f <= 6; f++)
				result.setBit(board::fromRankFile(rank, f));
			for (f = file - 1; f >= 1; f--)
				result.setBit(board::fromRankFile(rank, f));
		}
		return result;
	}

}