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
			constexpr squareType square() const noexcept
			{
				return m_Square;
			}
			constexpr movedata() noexcept = default;
			constexpr movedata(const squareType sq) noexcept :
				m_Square{ sq }
			{}
			constexpr movedata(movedata&&) noexcept = default;
			constexpr movedata(const movedata&) noexcept = default;
			constexpr movedata& operator=(movedata&&) noexcept = default;
			constexpr movedata& operator=(const movedata&) noexcept = default;
			~movedata() noexcept = default;
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
		constexpr static squareType extractSquare(const typename move::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countSquareBits>())) };
			return sq;
		}
	private:
		constexpr static void encodeSquare(typename move::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countSquareBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		constexpr move() noexcept = default;
		~move() noexcept = default;
		constexpr move(move&&) noexcept = default;
		constexpr move(const move&) noexcept = default;
		constexpr move& operator=(move&&) noexcept = default;
		constexpr move& operator=(const move&) noexcept = default;
		constexpr typename move::movedataType doMove_Implementation(boardType& position, const typename move::movebitsType& moveBits) const noexcept
		{
			const squareType sq{ move::extractSquare(moveBits) };
			constexpr const pieceType pc{ 0 };
			const playerType p{ position.movingPlayer() };
			const playerType p2{ ++position.movingPlayer() };
			position.setMovingPlayer(p2);
			position.addPiece(pc, sq, p);
			return typename move::movedataType(sq);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename move::movedataType& data) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			constexpr const pieceType pc{ 0 };
			position.setMovingPlayer(p);
			position.removePiece(pc, data.square(), p);
		}
		constexpr typename move::movebitsType create(const squareType square) const noexcept
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