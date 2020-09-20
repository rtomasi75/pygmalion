namespace pygmalion::chess
{
	namespace detail
	{
		class quietMovedata
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			squareType m_From;
			squareType m_To;
			uint_t<countFiles, false> m_OldFlags;
			pieceType m_Piece;
			playerType m_Player;
		public:
			constexpr const uint_t<countFiles, false>& oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			constexpr playerType player() const noexcept
			{
				return m_Player;
			}
			constexpr pieceType piece() const noexcept
			{
				return m_Piece;
			}
			constexpr squareType from() const noexcept
			{
				return m_From;
			}
			constexpr squareType to() const noexcept
			{
				return m_To;
			}
			constexpr quietMovedata(const pieceType transportedPiece, const squareType fromSquare, const squareType toSquare, const playerType owner, const uint_t<countFiles, false>& oldFlags_) noexcept :
				m_Piece{ transportedPiece },
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OldFlags{ oldFlags_ },
				m_Player{ owner }
			{}
			constexpr quietMovedata() noexcept = default;
			constexpr quietMovedata(quietMovedata&&) noexcept = default;
			constexpr quietMovedata(const quietMovedata&) noexcept = default;
			constexpr quietMovedata& operator=(quietMovedata&&) noexcept = default;
			constexpr quietMovedata& operator=(const quietMovedata&) noexcept = default;
			~quietMovedata() noexcept = default;
		};
	}

	class quietmove :
		public pygmalion::mechanics::move<board, 2 * board::squareType::countUnsignedBits, detail::quietMovedata, quietmove>,
		public board::descriptorState
	{
	public:
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countFromBits{ squareType::countUnsignedBits };
		constexpr static const size_t countToBits{ squareType::countUnsignedBits };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename quietmove::movedataType) << ":" << quietmove::countBits << "@quiet";
			return sstr.str();
		}
	private:
		constexpr static squareType extractTo(const typename quietmove::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		constexpr static void encodeTo(typename quietmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		constexpr static squareType extractFrom(const typename quietmove::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		constexpr static void encodeFrom(typename quietmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		constexpr quietmove() noexcept = default;
		~quietmove() noexcept = default;
		constexpr quietmove(quietmove&&) noexcept = default;
		constexpr quietmove(const quietmove&) noexcept = default;
		constexpr quietmove& operator=(quietmove&&) noexcept = default;
		constexpr quietmove& operator=(const quietmove&) noexcept = default;
		constexpr typename quietmove::movedataType doMove_Implementation(boardType& position, const typename quietmove::movebitsType& moveBits) const noexcept
		{
			const squareType from{ quietmove::extractFrom(moveBits) };
			const squareType to{ quietmove::extractTo(moveBits) };
			const pieceType pc{ position.getPiece(from) };
			const playerType p{ position.getPlayer(from) };
			const uint_t<countFiles, false> oldFlags{ position.extractFlagRange<4, 11>() };
			position.clearEnPassantFiles();
			position.removePiece(pc, from, p);
			position.addPiece(pc, to, p);
			position.setMovingPlayer(++position.movingPlayer());
			return typename quietmove::movedataType(pc, from, to, p, oldFlags);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename quietmove::movedataType& data) const noexcept
		{
			position.setMovingPlayer(--position.movingPlayer());
			position.removePiece(data.piece(), data.to(), data.player());
			position.addPiece(data.piece(), data.from(), data.player());
			position.storeFlagRange<4, 11>(data.oldFlags());
		}
		constexpr typename quietmove::movebitsType create(const squareType from, const squareType to) const noexcept
		{
			typename quietmove::movebitsType bits{ quietmove::movebitsType::zero() };
			quietmove::encodeFrom(bits, from);
			quietmove::encodeTo(bits, to);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename quietmove::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			squareType from;
			squareType to;
			if (boardType::parseSquare(temp, from))
			{
				if (position.playerOccupancy(position.movingPlayer())[from])
				{
					if (boardType::parseSquare(temp, to))
					{
						if (!position.totalOccupancy()[to])
						{
							moveBits = create(from, to);
							text = temp;
							return true;
						}
					}
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename quietmove::movebitsType& moveBits) const noexcept
		{
			const squareType from{ quietmove::extractFrom(moveBits) };
			const squareType to{ quietmove::extractTo(moveBits) };
			return boardType::squareToString(from) + boardType::squareToString(to);
		}
	};
}