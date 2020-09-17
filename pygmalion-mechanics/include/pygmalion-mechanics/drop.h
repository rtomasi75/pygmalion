namespace pygmalion::mechanics
{
	namespace detail
	{
		template<typename BOARD>
		class dropMovedata
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			pieceType m_Piece;
			squareType m_Square;
		public:
			constexpr squareType square() const noexcept
			{
				return m_Square;
			}
			constexpr pieceType piece() const noexcept
			{
				return m_Piece;
			}
			constexpr dropMovedata(const pieceType pc, const squareType sq) noexcept :
				m_Square{ sq },
				m_Piece{ pc }
			{}
		};
	}

	template<typename BOARD>
	class drop :
		public move<BOARD, BOARD::pieceType::countUnsignedBits + BOARD::squareType::countUnsignedBits, detail::dropMovedata<BOARD>, drop<BOARD>>
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countSquareBits{ squareType::countUnsignedBits };
		constexpr static const size_t countPieceBits{ pieceType::countUnsignedBits };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << drop::countBits << "bit@drop";
			return sstr.str();
		}
	private:
		constexpr static pieceType extractPiece(const typename drop::movebitsType& movebits) noexcept
		{
			const pieceType pc{ pieceType(static_cast<typename std::make_unsigned<typename pieceType::baseType>::type>(movebits.template extractBits<countSquareBits,countPieceBits>())) };
			return pc;
		}
		constexpr static void encodePiece(typename drop::movebitsType& movebits, const pieceType pc) noexcept
		{
			movebits.template storeBits<countSquareBits, countPieceBits>(static_cast<typename std::make_unsigned<typename pieceType::baseType>::type>(pc));
		}
		constexpr static squareType extractSquare(const typename drop::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countSquareBits>())) };
			return sq;
		}
		constexpr static void encodeSquare(typename drop::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countSquareBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		constexpr static typename drop::movedataType doMove_Implementation(boardType& position, const typename drop::movebitsType& moveBits) noexcept
		{
			const squareType sq{ drop::extractSquare(moveBits) };
			const pieceType pc{ drop::extractPiece(moveBits) };
			const playerType p{ position.movingPlayer() };
			position.addPiece(pc, sq, p);
			return typename drop::movedataType(pc, sq);
		}
		constexpr static void undoMove_Implementation(boardType& position, const typename drop::movedataType& data, const playerType movingPlayer) noexcept
		{
			position.removePiece(data.piece(), data.square(), movingPlayer);
		}
		constexpr static typename drop::movebitsType dropMove(const pieceType piece, const squareType square) noexcept
		{
			typename drop::movebitsType bits{ drop::movebitsType::zero() };
			drop::encodeSquare(bits, square);
			drop::encodePiece(bits, piece);
			return bits;
		}
		static bool parse_Implementation(const boardType& position, std::string& text, typename drop::movebitsType& moveBits) noexcept
		{
			std::string temp{ text };
			squareType sq;
			pieceType pc;
			if (boardType::parseSquare(temp, sq) && boardType::parsePiece(temp, pc))
			{
				if (!position.totalOccupancy()[sq])
				{
					moveBits = dropMove(pc, sq);
					text = temp;
					return true;
				}
			}
			return false;
		}
		static std::string toString_Implementation(const boardType& position, const typename drop::movebitsType& moveBits) noexcept
		{
			const squareType sq{ drop::extractSquare(moveBits) };
			const pieceType pc{ drop::extractPiece(moveBits) };
			return boardType::squareToString(sq) + boardType::pieceToString(pc);
		}
	};
}