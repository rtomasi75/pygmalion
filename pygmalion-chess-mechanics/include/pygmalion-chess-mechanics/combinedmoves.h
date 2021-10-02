namespace pygmalion::chess
{
	class combinedmoves :
		public pygmalion::mechanics::disjunctivemove<board, combinedmoves, capturemove,  quietmove, nullmove, doublepushmove, queenpromocapturemove, rookpromocapturemove, bishoppromocapturemove, knightpromocapturemove, queensidecastlemove, kingsidecastlemove, enpassantmove, queenpromotionmove, rookpromotionmove, bishoppromotionmove, knightpromotionmove>,
		public board::descriptorState
	{
	public:
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
	private:
		constexpr static const size_t indexCapture{ 0 };
		constexpr static const size_t indexQuiet{ 1 };
		constexpr static const size_t indexNull{ 2 };
		constexpr static const size_t indexDoublePush{ 3 };
		constexpr static const size_t indexQueenPromoCapture{ 4 };
		constexpr static const size_t indexRookPromoCapture{ 5 };
		constexpr static const size_t indexBishopPromoCapture{ 6 };
		constexpr static const size_t indexKnightPromoCapture{ 7 };
		constexpr static const size_t indexQueenside{ 8 };
		constexpr static const size_t indexKingside{ 9 };
		constexpr static const size_t indexEnPassant{ 10 };
		constexpr static const size_t indexQueenPromo{ 11 };
		constexpr static const size_t indexRookPromo{ 12 };
		constexpr static const size_t indexBishopPromo{ 13 };
		constexpr static const size_t indexKnightPromo{ 14 };
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
		constexpr static size_t getParseIndex_Implementation(const size_t index) noexcept
		{
			switch (index)
			{
			default:
				PYGMALION_UNREACHABLE;
				break;
			case indexQueenPromoCapture:
				return 0;
			case indexQueenPromo:
				return 1;
			case indexRookPromoCapture:
				return 2;
			case indexRookPromo:
				return 3;
			case indexBishopPromoCapture:
				return 4;
			case indexBishopPromo:
				return 5;
			case indexKnightPromoCapture:
				return 6;
			case indexKnightPromo:
				return 7;
			case indexDoublePush:
				return 8;
			case indexEnPassant:
				return 9;
			case indexKingside:
				return 10;
			case indexQueenside:
				return 11;
			case indexCapture:
				return 12;
			case indexQuiet:
				return 13;
			case indexNull:
				return 14;
			}
			return 0;
		}
		constexpr static bool isNull(const movebitsType movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return mux == muxNull;
		}
		constexpr static bool isPromotion(const movebitsType movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxQueenPromo) || (mux == muxQueenPromoCapture) || (mux == muxKnightPromo) || (mux == muxKnightPromoCapture) || (mux == muxRookPromo) || (mux == muxRookPromoCapture) || (mux == muxBishopPromo) || (mux == muxBishopPromoCapture);
		}
		static pieceType promotedPiece(const movebitsType movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			assert(isPromotion(movebits));
			const size_t mx{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			switch (mx)
			{
			default:
				PYGMALION_UNREACHABLE;
				break;
			case indexQueenPromo:
			case indexQueenPromoCapture:
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
		constexpr static bool isCapture(const movebitsType movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxCapture) || (mux == muxQueenPromoCapture) || (mux == muxKnightPromoCapture) || (mux == muxRookPromoCapture) || (mux == muxBishopPromoCapture) || (mux == muxEnPassant);
		}
		constexpr squareType captureSquare(const boardType& position, const movebitsType movebits) const noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			if ((mux == muxCapture) || (mux == muxQueenPromoCapture) || (mux == muxKnightPromoCapture) || (mux == muxRookPromoCapture) || (mux == muxBishopPromoCapture))
				return this->toSquare(position, movebits);
			else if (mux == muxEnPassant)
			{
				const fileType toFile{ this->toSquare(position, movebits).file() };
				const rankType fromRank{ this->fromSquare(position, movebits).rank() };
				return toFile & fromRank;
			}
			return squareType::invalid;
		}
		constexpr static bool isEnPassant(const movebitsType movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxEnPassant);
		}
		constexpr static bool isDoublePush(const movebitsType movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxDoublePush);
		}
		constexpr static bool isKingsideCastle(const movebitsType movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxKingside);
		}
		constexpr static bool isQueensideCastle(const movebitsType movebits) noexcept
		{
			const muxbitsType mux{ combinedmoves::muxbits(movebits) };
			return (mux == muxQueenside);
		}
		constexpr static bool isCastle(const movebitsType movebits) noexcept
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
