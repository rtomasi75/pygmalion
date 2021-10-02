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
			uint_t<countFlags, false> m_OldFlags;
			squareType m_From;
			squareType m_To;
			pieceType m_Piece;
			std::uint16_t m_ReversiblePlies{ 0 };
		public:
			constexpr std::uint16_t reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			constexpr const uint_t<countFlags, false> oldFlags() const noexcept
			{
				return m_OldFlags;
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
			constexpr quietMovedata(const pieceType transportedPiece, const squareType fromSquare, const squareType toSquare, const uint_t<countFlags, false> oldFlags_, const std::uint16_t reversiblePlies_) noexcept :
				m_Piece{ transportedPiece },
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OldFlags{ oldFlags_ },
				m_ReversiblePlies{ reversiblePlies_ }
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
		constexpr static squareType extractTo(const typename quietmove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		constexpr static squareType extractFrom(const typename quietmove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		constexpr static void encodeTo(typename quietmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
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
		constexpr typename quietmove::movedataType doMove_Implementation(boardType& position, const typename quietmove::movebitsType moveBits) const noexcept
		{
			const squareType from{ quietmove::extractFrom(moveBits) };
			const squareType to{ quietmove::extractTo(moveBits) };
			const pieceType pc{ position.getPiece(from) };
			const playerType p{ position.getPlayer(from) };
			const uint_t<countFlags, false> oldFlags{ position.extractFlagRange<0, 11>() };
			const std::uint16_t reversiblePlies{ position.cumulation().reversiblePlies() };
			position.clearEnPassantFiles();
			position.removePiece(pc, from, p);
			position.addPiece(pc, to, p);
			position.setMovingPlayer(++position.movingPlayer());
			if (pc == pawn)
				position.cumulation().reversiblePlies() = 0;
			else
				position.cumulation().reversiblePlies()++;
			if (p == whitePlayer)
			{
				switch (pc)
				{
				case king:
					position.clearCastleRightsWhite();
					break;
				case rook:
					switch (from)
					{
					case squareA1:
						position.clearCastleRightQueensideWhite();
						break;
					case squareH1:
						position.clearCastleRightKingsideWhite();
						break;
					}
					break;
				}
			}
			else
			{
				switch (pc)
				{
				case king:
					position.clearCastleRightsBlack();
					break;
				case rook:
					switch (from)
					{
					case squareA8:
						position.clearCastleRightQueensideBlack();
						break;
					case squareH8:
						position.clearCastleRightKingsideBlack();
						break;
					}
					break;
				}
			}
			return typename quietmove::movedataType(pc, from, to, oldFlags, reversiblePlies);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename quietmove::movedataType& data) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.removePiece(data.piece(), data.to(), p);
			position.addPiece(data.piece(), data.from(), p);
			position.storeFlagRange<0, 11>(data.oldFlags());
			position.cumulation().reversiblePlies() = data.reversiblePlies();
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
		std::string toString_Implementation(const boardType& position, const typename quietmove::movebitsType moveBits) const noexcept
		{
			const squareType from{ quietmove::extractFrom(moveBits) };
			const squareType to{ quietmove::extractTo(moveBits) };
			return boardType::squareToString(from) + boardType::squareToString(to);
		}
		constexpr squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return squaresType::none();
		}
		constexpr squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return squaresType(quietmove::extractFrom(moveBits)) ^ squaresType(quietmove::extractTo(moveBits));
		}
		constexpr squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType piece, const movebitsType moveBits) const noexcept
		{
			const squareType from{ quietmove::extractFrom(moveBits) };
			if (position.pieceOccupancy(piece)[from])
				return squaresType(from) ^ squaresType(quietmove::extractTo(moveBits));
			else
				return squaresType::none();
		}
		constexpr squareType fromSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return quietmove::extractFrom(moveBits);
		}
		constexpr squareType toSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return quietmove::extractTo(moveBits);
		}
	};
}