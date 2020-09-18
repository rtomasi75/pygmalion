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
			playerType m_Owner;
		public:
			constexpr playerType owner() const noexcept
			{
				return m_Owner;
			}
			constexpr squareType square() const noexcept
			{
				return m_Square;
			}
			constexpr pieceType piece() const noexcept
			{
				return m_Piece;
			}
			constexpr dropMovedata(const pieceType pc, const squareType sq, const playerType p) noexcept :
				m_Square{ sq },
				m_Piece{ pc },
				m_Owner{ p }
			{}
		};
	}

	template<typename BOARD>
	class dropmove :
		public move<BOARD, BOARD::pieceType::countUnsignedBits + BOARD::squareType::countUnsignedBits + BOARD::playerType::countUnsignedBits, detail::dropMovedata<BOARD>, dropmove<BOARD>>
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countSquareBits{ squareType::countUnsignedBits };
		constexpr static const size_t countPieceBits{ pieceType::countUnsignedBits };
		constexpr static const size_t countOwnerBits{ playerType::countUnsignedBits };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << dropmove::countBits << "bit@drop";
			return sstr.str();
		}
	private:
		constexpr static playerType extractOwner(const typename dropmove::movebitsType& movebits) noexcept
		{
			const playerType p{ playerType(static_cast<typename std::make_unsigned<typename playerType::baseType>::type>(movebits.template extractBits<countSquareBits + countPieceBits,countOwnerBits>())) };
			return p;
		}
		constexpr static void encodeOwner(typename dropmove::movebitsType& movebits, const playerType p) noexcept
		{
			movebits.template storeBits<countSquareBits + countPieceBits, countOwnerBits>(static_cast<typename std::make_unsigned<typename playerType::baseType>::type>(p));
		}
		constexpr static pieceType extractPiece(const typename dropmove::movebitsType& movebits) noexcept
		{
			const pieceType pc{ pieceType(static_cast<typename std::make_unsigned<typename pieceType::baseType>::type>(movebits.template extractBits<countSquareBits,countPieceBits>())) };
			return pc;
		}
		constexpr static void encodePiece(typename dropmove::movebitsType& movebits, const pieceType pc) noexcept
		{
			movebits.template storeBits<countSquareBits, countPieceBits>(static_cast<typename std::make_unsigned<typename pieceType::baseType>::type>(pc));
		}
		constexpr static squareType extractSquare(const typename dropmove::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countSquareBits>())) };
			return sq;
		}
		constexpr static void encodeSquare(typename dropmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countSquareBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		constexpr static typename dropmove::movedataType doMove_Implementation(boardType& position, const typename dropmove::movebitsType& moveBits) noexcept
		{
			const squareType sq{ dropmove::extractSquare(moveBits) };
			const pieceType pc{ dropmove::extractPiece(moveBits) };
			const playerType p{ dropmove::extractOwner(moveBits) };
			position.addPiece(pc, sq, p);
			return typename dropmove::movedataType(pc, sq, p);
		}
		constexpr static void undoMove_Implementation(boardType& position, const typename dropmove::movedataType& data, const playerType movingPlayer) noexcept
		{
			position.removePiece(data.piece(), data.square(), data.owner());
		}
		constexpr static typename dropmove::movebitsType dropMove(const pieceType piece, const squareType square, const playerType owner) noexcept
		{
			typename dropmove::movebitsType bits{ dropmove::movebitsType::zero() };
			dropmove::encodeSquare(bits, square);
			dropmove::encodePiece(bits, piece);
			dropmove::encodeOwner(bits, owner);
			return bits;
		}
		static bool parse_Implementation(const boardType& position, std::string& text, typename dropmove::movebitsType& moveBits) noexcept
		{
			std::string temp{ text };
			squareType sq;
			pieceType pc;
			playerType p;
			if (boardType::parsePiece(temp, pc, p))
			{
				if (temp[0] == '@')
				{
					temp = temp.substr(1, temp.length() - 1);
					if (boardType::parseSquare(temp, sq))
					{
						if (!position.totalOccupancy()[sq])
						{
							moveBits = dropMove(pc, sq, p);
							text = temp;
							return true;
						}
					}
				}
			}
			return false;
		}
		static std::string toString_Implementation(const boardType& position, const typename dropmove::movebitsType& moveBits) noexcept
		{
			const squareType sq{ dropmove::extractSquare(moveBits) };
			const pieceType pc{ dropmove::extractPiece(moveBits) };
			const playerType p{ dropmove::extractOwner(moveBits) };
			return boardType::pieceToString(pc, p) + "@" + boardType::squareToString(sq);
		}
	};
}