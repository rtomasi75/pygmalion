namespace pygmalion::chess
{
	class combinedmoves :
		public pygmalion::mechanics::disjunctivemove<board, queenpromocapturemove, queenpromotionmove, rookpromocapturemove, rookpromotionmove, bishoppromocapturemove, bishoppromotionmove, knightpromocapturemove, knightpromotionmove, doublepushmove, enpassantmove, capturemove, quietmove, kingsidecastlemove, queensidecastlemove>,
		public board::descriptorState
	{
	public:
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
	private:
		constexpr static const muxbitsType muxQueenPromoCapture{ 0 };
		constexpr static const muxbitsType muxQueenPromo{ 1 };
		constexpr static const muxbitsType muxRookPromoCapture{ 2 };
		constexpr static const muxbitsType muxRookPromo{ 3 };
		constexpr static const muxbitsType muxBishopPromoCapture{ 4 };
		constexpr static const muxbitsType muxBishopPromo{ 5 };
		constexpr static const muxbitsType muxKnightPromoCapture{ 6 };
		constexpr static const muxbitsType muxKnightPromo{ 7 };
		constexpr static const muxbitsType muxCapture{ 8 };
		constexpr static const muxbitsType muxQuiet{ 9 };
		constexpr static const muxbitsType muxEnPassant{ 10 };
		constexpr static const muxbitsType muxDoublePush{ 11 };
		constexpr static const muxbitsType muxKingside{ 12 };
		constexpr static const muxbitsType muxQueenside{ 13 };
	public:
		constexpr static bool isPromotion(const movebitsType& movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxQueenPromo) || (mux == muxQueenPromoCapture) || (mux == muxKnightPromoCapture) || (mux == muxKnightPromoCapture) || (mux == muxRookPromoCapture) || (mux == muxRookPromoCapture) || (mux == muxBishopPromoCapture) || (mux == muxBishopPromoCapture);
		}
		constexpr static pieceType promotedPiece(const movebitsType& movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			assert(isPromotion(movebits));
			if ((mux == muxQueenPromo) || (mux == muxQueenPromoCapture))
				return queen;
			else if ((mux == muxKnightPromo) || (mux == muxKnightPromoCapture))
				return knight;
			else if ((mux == muxRookPromo) || (mux == muxRookPromoCapture))
				return rook;
			else 
				return bishop;
		}
		constexpr static bool isCapture(const movebitsType& movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxCapture) || (mux == muxQueenPromoCapture) || (mux == muxKnightPromoCapture) || (mux == muxRookPromoCapture) || (mux == muxBishopPromoCapture) || (mux == muxEnPassant);
		}
		constexpr static bool isEnPassant(const movebitsType& movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxEnPassant);
		}
		constexpr static bool isDoublePush(const movebitsType& movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxDoublePush);
		}
		constexpr static bool isKingsideCastle(const movebitsType& movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxKingside);
		}
		constexpr static bool isQueensideCastle(const movebitsType& movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxQueenside);
		}
		constexpr static bool isCastle(const movebitsType& movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxQueenside) || (mux == muxKingside);
		}
	};
}
