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
			PYGMALION_INLINE std::uint16_t reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			PYGMALION_INLINE const uint_t<countFlags, false> oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			PYGMALION_INLINE pieceType piece() const noexcept
			{
				return m_Piece;
			}
			PYGMALION_INLINE squareType from() const noexcept
			{
				return m_From;
			}
			PYGMALION_INLINE squareType to() const noexcept
			{
				return m_To;
			}
			PYGMALION_INLINE quietMovedata(const pieceType transportedPiece, const squareType fromSquare, const squareType toSquare, const uint_t<countFlags, false> oldFlags_, const std::uint16_t reversiblePlies_) noexcept :
				m_Piece{ transportedPiece },
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OldFlags{ oldFlags_ },
				m_ReversiblePlies{ reversiblePlies_ }
			{}
			PYGMALION_INLINE quietMovedata() noexcept = default;
			PYGMALION_INLINE quietMovedata(quietMovedata&&) noexcept = default;
			PYGMALION_INLINE quietMovedata(const quietMovedata&) noexcept = default;
			PYGMALION_INLINE quietMovedata& operator=(quietMovedata&&) noexcept = default;
			PYGMALION_INLINE quietMovedata& operator=(const quietMovedata&) noexcept = default;
			PYGMALION_INLINE ~quietMovedata() noexcept = default;
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
		PYGMALION_INLINE static squareType extractTo(const typename quietmove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		PYGMALION_INLINE static squareType extractFrom(const typename quietmove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		PYGMALION_INLINE constexpr static void encodeTo(typename quietmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		PYGMALION_INLINE constexpr static void encodeFrom(typename quietmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		constexpr quietmove() noexcept = default;
		~quietmove() noexcept = default;
		constexpr quietmove(quietmove&&) noexcept = default;
		constexpr quietmove(const quietmove&) noexcept = default;
		constexpr quietmove& operator=(quietmove&&) noexcept
		{
			return *this;
		}
		constexpr quietmove& operator=(const quietmove&) noexcept
		{
			return *this;
		}
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename quietmove::movebitsType moveBits, typename quietmove::movedataType& movedata) const noexcept
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
			movedata = typename quietmove::movedataType(pc, from, to, oldFlags, reversiblePlies);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename quietmove::movedataType& data) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.removePiece(data.piece(), data.to(), p);
			position.addPiece(data.piece(), data.from(), p);
			position.storeFlagRange<0, 11>(data.oldFlags());
			position.cumulation().reversiblePlies() = data.reversiblePlies();
		}
		PYGMALION_INLINE constexpr typename quietmove::movebitsType create(const squareType from, const squareType to) const noexcept
		{
			typename quietmove::movebitsType bits{ quietmove::movebitsType::zero() };
			quietmove::encodeFrom(bits, from);
			quietmove::encodeTo(bits, to);
			return bits;
		}
		bool parse_Implementation(const boardType& position, const std::string& text, typename quietmove::movebitsType& moveBits, size_t& count) const noexcept
		{
			std::string temp{ text };
			squareType from;
			squareType to;
			size_t cnt{ 0 };
			if (boardType::parseSquare(temp, from, cnt))
			{
				std::string temp2{ temp.substr(cnt,temp.length() - cnt) };
				if (position.playerOccupancy(position.movingPlayer())[from])
				{
					if (boardType::parseSquare(temp2, to, cnt))
					{
						if (!position.totalOccupancy()[to])
						{
							pieceType piece{ position.getPiece(from) };
							if (piece == pawn)
							{
								if (from.file() != to.file())
									return false;
								const rankType toRank{ to.rank() };
								if (toRank == rank1 || toRank == rank8)
									return false;
								const rankType fromRank{ from.rank() };
								if (position.movingPlayer() == whitePlayer)
								{
									if (toRank != fromRank.up())
										return false;
								}
								else
								{
									if (toRank != fromRank.down())
										return false;
								}
							}
							moveBits = create(from, to);
							count += cnt;
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
		PYGMALION_INLINE squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			return none;
		}
		PYGMALION_INLINE squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return squaresType(quietmove::extractFrom(moveBits)) ^ squaresType(quietmove::extractTo(moveBits));
		}
		PYGMALION_INLINE squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType piece, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			const squareType from{ quietmove::extractFrom(moveBits) };
			if (position.pieceOccupancy(piece)[from])
				return squaresType(from) ^ squaresType(quietmove::extractTo(moveBits));
			else
				return none;
		}
		PYGMALION_INLINE squareType fromSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return quietmove::extractFrom(moveBits);
		}
		PYGMALION_INLINE squareType toSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return quietmove::extractTo(moveBits);
		}
	};
}