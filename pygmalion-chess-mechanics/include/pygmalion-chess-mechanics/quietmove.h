namespace pygmalion::chess
{
	namespace detail
	{
		class quietMovedata :
			public pygmalion::mechanics::movedataBase<board>
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			flagsType m_OldFlags;
			squaresType m_OldEnPassantTargets;
			squareType m_OldEnPassantVictim;
			squareType m_From;
			squareType m_To;
			pieceType m_Piece;
			size_t m_ReversiblePlies{ 0 };
			constexpr static const flagsType noFlags{ flagsType::none() };
		public:
			PYGMALION_INLINE const size_t& reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			PYGMALION_INLINE const flagsType& oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			PYGMALION_INLINE const squaresType& oldEnPassantTargets() const noexcept
			{
				return m_OldEnPassantTargets;
			}
			PYGMALION_INLINE const squareType& oldEnPassantVictim() const noexcept
			{
				return m_OldEnPassantVictim;
			}
			PYGMALION_INLINE const pieceType& piece() const noexcept
			{
				return m_Piece;
			}
			PYGMALION_INLINE const squareType& from() const noexcept
			{
				return m_From;
			}
			PYGMALION_INLINE const squareType& to() const noexcept
			{
				return m_To;
			}
			PYGMALION_INLINE quietMovedata(const pieceType transportedPiece, const squareType fromSquare, const squareType toSquare, const flagsType oldFlags_, const size_t reversiblePlies_, const squaresType oldEnPassantTargets_, const squareType oldEnPassantVictim_) noexcept :
				m_Piece{ transportedPiece },
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OldFlags{ oldFlags_ },
				m_ReversiblePlies{ reversiblePlies_ },
				m_OldEnPassantTargets{ oldEnPassantTargets_ },
				m_OldEnPassantVictim{ oldEnPassantVictim_ }
			{}
			PYGMALION_INLINE quietMovedata() noexcept :
				m_OldFlags{ noFlags }
			{

			}
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
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename quietmove::movebitsType moveBits, typename quietmove::movedataType& movedata, const materialTableType& materialTable) const noexcept
		{
			const squareType from{ quietmove::extractFrom(moveBits) };
			const squareType to{ quietmove::extractTo(moveBits) };
			const pieceType pc{ position.getPiece(from) };
			const playerType p{ position.movingPlayer() };
			const flagsType oldFlags{ position.flags() };
			const size_t reversiblePlies{ position.getReversiblePlyCount() };
			const squaresType oldEnPassantTargets{ position.enPassantTargets() };
			const squareType oldEnPassantVictim{ position.enPassantVictim() };
			position.clearEnPassant();
			position.movePiece(pc, from, to, p, materialTable);
			position.setMovingPlayer(++position.movingPlayer());
			if (pc == pawn)
				position.resetReversiblePlyCount();
			else
				position.doReversiblePly();
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
			movedata = typename quietmove::movedataType(pc, from, to, oldFlags, reversiblePlies, oldEnPassantTargets, oldEnPassantVictim);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename quietmove::movedataType& data, const materialTableType& materialTable) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.movePiece(data.piece(), data.to(), data.from(), p, materialTable);
			position.checkFlags(data.oldFlags());
			position.setEnPassant(data.oldEnPassantTargets(), data.oldEnPassantVictim());
			position.setReversiblePlyCount(static_cast<size_t>(data.reversiblePlies()));
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
			squareType from;
			squareType to;
			size_t cnt{ 0 };
			if (squareType::parse(text, cnt, from))
			{
				if (position.playerOccupancy(position.movingPlayer())[from])
				{
					if (squareType::parse(text, cnt, to))
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
			return from.toShortString() + to.toShortString();
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