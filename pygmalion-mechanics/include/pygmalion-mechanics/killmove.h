namespace pygmalion::mechanics
{
	namespace detail
	{
		template<typename BOARD>
		class killMovedata
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			squareType m_Square;
			pieceType m_Piece;
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
			constexpr killMovedata() noexcept = default;
			constexpr killMovedata(const pieceType pc, const squareType sq, const playerType p) noexcept :
				m_Square{ sq },
				m_Piece{ pc },
				m_Owner{ p }
			{}
			constexpr killMovedata(killMovedata&&) noexcept = default;
			constexpr killMovedata(const killMovedata&) noexcept = default;
			constexpr killMovedata& operator=(killMovedata&&) noexcept = default;
			constexpr killMovedata& operator=(const killMovedata&) noexcept = default;
			~killMovedata() noexcept = default;
		};
	}

	template<typename BOARD>
	class killmove :
		public move<BOARD, BOARD::squareType::countUnsignedBits, detail::killMovedata<BOARD>, killmove<BOARD>>
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countSquareBits{ squareType::countUnsignedBits };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename killmove::movedataType) << ":" << killmove::countBits << "@kill";
			return sstr.str();
		}
	private:
		constexpr static squareType extractSquare(const typename killmove::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countSquareBits>())) };
			return sq;
		}
		constexpr static void encodeSquare(typename killmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countSquareBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		constexpr killmove() noexcept = default;
		~killmove() noexcept = default;
		constexpr killmove(killmove&&) noexcept = default;
		constexpr killmove(const killmove&) noexcept = default;
		constexpr killmove& operator=(killmove&&) noexcept = default;
		constexpr killmove& operator=(const killmove&) noexcept = default;
		constexpr typename killmove::movedataType doMove_Implementation(boardType& position, const typename killmove::movebitsType& moveBits) const noexcept
		{
			const squareType sq{ killmove::extractSquare(moveBits) };
			const pieceType pc{ position.getPiece(sq) };
			const playerType p{ position.getPlayer(sq) };
			position.removePiece(pc, sq, p);
			return typename killmove::movedataType(pc, sq, p);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename killmove::movedataType& data) const noexcept
		{
			position.addPiece(data.piece(), data.square(), data.owner());
		}
		constexpr typename killmove::movebitsType create(const squareType square) const noexcept
		{
			typename killmove::movebitsType bits{ killmove::movebitsType::zero() };
			killmove::encodeSquare(bits, square);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename killmove::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			squareType sq;
			if ((temp.length() > 0) && (temp[0] == '!'))
			{
				temp = temp.substr(1, temp.length() - 1);
				if (boardType::parseSquare(temp, sq))
				{
					if (position.totalOccupancy()[sq])
					{
						moveBits = create(sq);
						text = temp;
						return true;
					}
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename killmove::movebitsType& moveBits) const noexcept
		{
			const squareType sq{ killmove::extractSquare(moveBits) };
			return "!" + boardType::squareToString(sq);
		}
	};
}