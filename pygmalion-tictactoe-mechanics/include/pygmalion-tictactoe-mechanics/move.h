namespace pygmalion::tictactoe
{
	namespace detail
	{
		class movedata
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			squareType m_Square;
		public:
			PYGMALION_INLINE squareType square() const noexcept
			{
				return m_Square;
			}
			PYGMALION_INLINE movedata() noexcept = default;
			PYGMALION_INLINE movedata(const squareType sq) noexcept :
				m_Square{ sq }
			{}
			PYGMALION_INLINE movedata(movedata&&) noexcept = default;
			PYGMALION_INLINE movedata(const movedata&) noexcept = default;
			PYGMALION_INLINE movedata& operator=(movedata&&) noexcept = default;
			PYGMALION_INLINE movedata& operator=(const movedata&) noexcept = default;
			PYGMALION_INLINE ~movedata() noexcept = default;
		};
	}

	class move :
		public pygmalion::mechanics::move<board, board::squareType::countUnsignedBits, detail::movedata, move>
	{
	public:
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countSquareBits{ squareType::countUnsignedBits };
		constexpr static const size_t countPieceBits{ pieceType::countUnsignedBits };
		constexpr static const size_t countOwnerBits{ playerType::countUnsignedBits };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename move::movedataType) << ":" << move::countBits << "drop";
			return sstr.str();
		}
		static squareType extractSquare(const typename move::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countSquareBits>())) };
			return sq;
		}
	private:
		static void encodeSquare(typename move::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countSquareBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		PYGMALION_INLINE constexpr move() noexcept = default;
		PYGMALION_INLINE ~move() noexcept = default;
		PYGMALION_INLINE constexpr move(move&&) noexcept = default;
		PYGMALION_INLINE constexpr move(const move&) noexcept = default;
		PYGMALION_INLINE constexpr move& operator=(move&&) noexcept = default;
		PYGMALION_INLINE constexpr move& operator=(const move&) noexcept = default;
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename move::movebitsType& moveBits, typename move::movedataType& movedata) const noexcept
		{
			const squareType sq{ move::extractSquare(moveBits) };
			constexpr const pieceType pc{ 0 };
			const playerType p{ position.movingPlayer() };
			const playerType p2{ ++position.movingPlayer() };
			position.setMovingPlayer(p2);
			position.addPiece(pc, sq, p);
			movedata = typename move::movedataType(sq);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename move::movedataType& data) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			constexpr const pieceType pc{ 0 };
			position.setMovingPlayer(p);
			position.removePiece(pc, data.square(), p);
		}
		PYGMALION_INLINE typename move::movebitsType create(const squareType square) const noexcept
		{
			typename move::movebitsType bits{ move::movebitsType::zero() };
			move::encodeSquare(bits, square);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename move::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			squareType sq;
			pieceType pc;
			playerType p;
			if (boardType::parseSquare(temp, sq))
			{
				if (!position.totalOccupancy()[sq])
				{
					moveBits = create(sq);
					text = temp;
					return true;
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename move::movebitsType& moveBits) const noexcept
		{
			const squareType sq{ move::extractSquare(moveBits) };
			return boardType::squareToString(sq);
		}
	};
}