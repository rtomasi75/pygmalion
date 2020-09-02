namespace pygmalion
{
	template<typename DESCRIPTOR_BOARD, int COUNT_MOVE_SQUARES, int COUNT_MOVE_PIECES, int COUNT_MOVE_FLAGS>
	class move : 
		public base_board<DESCRIPTOR_BOARD>
	{
	public:
		using descriptorBoard = DESCRIPTOR_BOARD;
#include "include_board.h"

		constexpr static int countMoveSquares{ COUNT_MOVE_SQUARES };
		constexpr static int countMovePieces{ COUNT_MOVE_PIECES };
		constexpr static int countMoveFlags{ COUNT_MOVE_FLAGS };
		using moveflagsType = bitfield<COUNT_MOVE_FLAGS>;
		using moveflagbitType = typename moveflagsType::bitType;

		constexpr static int countSquareBits{ requiredUnsignedBits(squareType::countValues) };
		constexpr static int countPieceBits{ requiredUnsignedBits(pieceType::countValues) };
		constexpr static int countTotalBits{ countMoveSquares * countSquareBits + countMovePieces * countPieceBits + countMoveFlags };
		using baseType = typename int_traits<requiredBitBytes(countTotalBits)>::UTYPE;
	private:
		constexpr static int shiftSquare(const int indexSquare) noexcept
		{
			return indexSquare * countSquareBits;
		}
		constexpr static int shiftPiece(const int indexPiece) noexcept
		{
			return indexPiece * countPieceBits + countPieceBits * countMovePieces;
		}
		constexpr static int shiftFlags{ countSquareBits * countMoveSquares + countPieceBits * countMovePieces };
		constexpr static baseType maskSquare(const int indexSquare) noexcept
		{
			return static_cast<baseType>(((baseType(1) << countSquareBits) - 1) << shiftSquare(indexSquare));
		}
		constexpr static baseType maskPiece(const int indexPiece) noexcept
		{
			return static_cast<baseType>(((baseType(1) << countPieceBits) - 1) << shiftPiece(indexPiece));
		}
		const static baseType maskFlags{ static_cast<baseType>(((baseType(1) << countMoveFlags) - 1) << shiftFlags) };
		const static baseType encodeSquare(const squareType square, const int indexSquare) noexcept
		{
			return (square << shiftSquare(indexSquare)) & maskSquare(indexSquare);
		}
		const static baseType encodePiece(const pieceType piece, const int indexPiece) noexcept
		{
			return (piece << shiftPiece(indexPiece)) & maskPiece(indexPiece);
		}
		const static baseType encodeFlags(const moveflagsType flags) noexcept
		{
			return (flags.bits() << shiftFlags) & maskFlags;
		}
		const static squareType decodeSquare(const baseType bits, const int indexSquare) noexcept
		{
			return (bits & maskSquare(indexSquare)) >> shiftSquare(indexSquare);
		}
		const static pieceType decodePiece(const baseType bits, const int indexPiece) noexcept
		{
			return (bits & maskPiece(indexPiece)) >> shiftPiece(indexPiece);
		}
		const static moveflagsType decodeFlags(const baseType bits) noexcept
		{
			return (bits & maskFlags) >> shiftFlags;
		}
		const static baseType encodeSquares(const std::array<squareType, countMoveSquares>& squares) noexcept
		{
			baseType encoded{ 0 };
			for (int index = 0; index < countMoveSquares; index++)
				encoded |= encodeSquare(squares[index], index);
			return encoded;
		}
		const static baseType encodePieces(const std::array<pieceType, countMovePieces>& pieces) noexcept
		{
			baseType encoded{ 0 };
			for (int index = 0; index < countMovePieces; index++)
				encoded |= encodePiece(pieces[index], index);
			return encoded;
		}
		baseType m_Bits;
	public:
		constexpr move(const std::array<squareType, countMoveSquares>& squares, const std::array<pieceType, countMovePieces>& pieces, const moveflagsType flags) noexcept :
			m_Bits{ static_cast<baseType>(encodeSquares(squares) | encodePieces(pieces) | encodeFlags(flags)) }
		{
		}
		constexpr move() noexcept :
			m_Bits{ 0 }
		{
		}
		constexpr squareType square(const int indexSquare) const noexcept
		{
			return decodeSquare(m_Bits, indexSquare);
		}
		constexpr pieceType piece(const int indexPiece) const noexcept
		{
			return decodePiece(m_Bits, indexPiece);
		}
		constexpr moveflagsType flags() const noexcept
		{
			return decodeFlags(m_Bits);
		}
		constexpr move(const move&) noexcept = default;
		constexpr move(move&&) noexcept = default;
		constexpr move& operator=(const move&) noexcept = default;
		constexpr move& operator=(move&&) noexcept = default;
		~move() noexcept = default;
	public:
	};
}