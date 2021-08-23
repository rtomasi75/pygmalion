namespace pygmalion::chess
{
	class combinedmoves :
		public pygmalion::mechanics::disjunctivemove<board, queenpromocapturemove, queenpromotionmove, rookpromocapturemove, rookpromotionmove, bishoppromocapturemove, bishoppromotionmove, knightpromocapturemove, knightpromotionmove, doublepushmove, enpassantmove, kingsidecastlemove, queensidecastlemove, capturemove, quietmove, nullmove>,
		public board::descriptorState
	{
	public:
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
	private:
		constexpr static const size_t indexQueenPromoCapture{ 0 };
		constexpr static const size_t indexQueenPromo{ 1 };
		constexpr static const size_t indexRookPromoCapture{ 2 };
		constexpr static const size_t indexRookPromo{ 3 };
		constexpr static const size_t indexBishopPromoCapture{ 4 };
		constexpr static const size_t indexBishopPromo{ 5 };
		constexpr static const size_t indexKnightPromoCapture{ 6 };
		constexpr static const size_t indexKnightPromo{ 7 };
		constexpr static const size_t indexDoublePush{ 8 };
		constexpr static const size_t indexEnPassant{ 9 };
		constexpr static const size_t indexKingside{ 10 };
		constexpr static const size_t indexQueenside{ 11 };
		constexpr static const size_t indexCapture{ 12 };
		constexpr static const size_t indexQuiet{ 13 };
		constexpr static const size_t indexNull{ 14 };
		constexpr static const muxbitsType muxQueenPromoCapture{ indexQueenPromoCapture };
		constexpr static const muxbitsType muxQueenPromo{ indexQueenPromo };
		constexpr static const muxbitsType muxRookPromoCapture{ indexRookPromoCapture };
		constexpr static const muxbitsType muxRookPromo{ indexRookPromo };
		constexpr static const muxbitsType muxBishopPromoCapture{ indexBishopPromoCapture };
		constexpr static const muxbitsType muxBishopPromo{ indexBishopPromo };
		constexpr static const muxbitsType muxKnightPromoCapture{ indexKnightPromoCapture };
		constexpr static const muxbitsType muxKnightPromo{ indexKnightPromo };
		constexpr static const muxbitsType muxCapture{ indexCapture };
		constexpr static const muxbitsType muxQuiet{ indexQuiet };
		constexpr static const muxbitsType muxEnPassant{ indexEnPassant };
		constexpr static const muxbitsType muxDoublePush{ indexDoublePush };
		constexpr static const muxbitsType muxKingside{ indexKingside };
		constexpr static const muxbitsType muxQueenside{ indexQueenside };
		constexpr static const muxbitsType muxNull{ indexNull };
	public:
		constexpr static bool isNull(const movebitsType& movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return mux == muxNull;
		}
		constexpr static bool isPromotion(const movebitsType& movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxQueenPromo) || (mux == muxQueenPromoCapture) || (mux == muxKnightPromo) || (mux == muxKnightPromoCapture) || (mux == muxRookPromo) || (mux == muxRookPromoCapture) || (mux == muxBishopPromo) || (mux == muxBishopPromoCapture);
		}
		constexpr static pieceType promotedPiece(const movebitsType& movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			assert(isPromotion(movebits));
			const size_t mx{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			switch (mx)
			{
			default:
				return queen;
			case indexBishopPromo:
			case indexBishopPromoCapture:
				return bishop;
			case indexKnightPromo:
			case indexKnightPromoCapture:
				return knight;
			case indexRookPromo:
			case indexRookPromoCapture:
				return knight;
			}
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
		constexpr movebitsType createCapture(const squareType from, const squareType to) const noexcept
		{
			return create<indexCapture>(this->component<indexCapture>().create(from, to));
		}
		constexpr movebitsType createQuiet(const squareType from, const squareType to) const noexcept
		{
			return create<indexQuiet>(this->component<indexQuiet>().create(from, to));
		}
		constexpr movebitsType createDoublePush(const fileType file) const noexcept
		{
			return create<indexDoublePush>(this->component<indexDoublePush>().create(file));
		}
		constexpr movebitsType createEnPassant(const fileType file1, const fileType file2) const noexcept
		{
			return create<indexEnPassant>(this->component<indexEnPassant>().create(file1, file2));
		}
		constexpr movebitsType createKingsideCastle() const noexcept
		{
			return create<indexKingside>(this->component<indexKingside>().create());
		}
		constexpr movebitsType createQueensideCastle() const noexcept
		{
			return create<indexQueenside>(this->component<indexQueenside>().create());
		}
		constexpr movebitsType createPromotionQueen(const squareType from, const squareType to) const noexcept
		{
			return create<indexQueenPromo>(this->component<indexQueenPromo>().create(from, to));
		}
		constexpr movebitsType createPromotionRook(const squareType from, const squareType to) const noexcept
		{
			return create<indexRookPromo>(this->component<indexRookPromo>().create(from, to));
		}
		constexpr movebitsType createPromotionBishop(const squareType from, const squareType to) const noexcept
		{
			return create<indexBishopPromo>(this->component<indexBishopPromo>().create(from, to));
		}
		constexpr movebitsType createPromotionKnight(const squareType from, const squareType to) const noexcept
		{
			return create<indexKnightPromo>(this->component<indexKnightPromo>().create(from, to));
		}
		constexpr movebitsType createPromoCaptureQueen(const squareType from, const squareType to) const noexcept
		{
			return create<indexQueenPromoCapture>(this->component<indexQueenPromoCapture>().create(from, to));
		}
		constexpr movebitsType createPromoCaptureRook(const squareType from, const squareType to) const noexcept
		{
			return create<indexRookPromoCapture>(this->component<indexRookPromoCapture>().create(from, to));
		}
		constexpr movebitsType createPromoCaptureBishop(const squareType from, const squareType to) const noexcept
		{
			return create<indexBishopPromoCapture>(this->component<indexBishopPromoCapture>().create(from, to));
		}
		constexpr movebitsType createPromoCaptureKnight(const squareType from, const squareType to) const noexcept
		{
			return create<indexKnightPromoCapture>(this->component<indexKnightPromoCapture>().create(from, to));
		}
		constexpr movebitsType createNull() const noexcept
		{
			return create<indexNull>(this->component<indexNull>().create());
		}
	};
}
