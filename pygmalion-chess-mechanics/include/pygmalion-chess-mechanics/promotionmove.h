namespace pygmalion::chess
{
	namespace detail
	{
		class promotionMovedata :
			public pygmalion::mechanics::movedataBase<board>
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
			using materialTableType = pygmalion::state::materialTables<descriptorState, boardType>;
		private:
			squareType m_OldEnPassantSquare;
			squareType m_From;
			squareType m_To;
			size_t m_ReversiblePlies{ 0 };
			constexpr static const flagsType noFlags{ flagsType::none() };
		public:
			PYGMALION_INLINE const size_t& reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			PYGMALION_INLINE const squareType& from() const noexcept
			{
				return m_From;
			}
			PYGMALION_INLINE const squareType& to() const noexcept
			{
				return m_To;
			}
			PYGMALION_INLINE const squareType& oldEnPassantSquare() const noexcept
			{
				return m_OldEnPassantSquare;
			}
			PYGMALION_INLINE promotionMovedata(const squareType fromSquare, const squareType toSquare, const squareType oldEnPassantSquare_, const std::uint16_t reversiblePlies_) noexcept :
				m_From{ fromSquare },
				m_To{ toSquare },
				m_ReversiblePlies{ reversiblePlies_ },
				m_OldEnPassantSquare{ oldEnPassantSquare_ }
			{}
			PYGMALION_INLINE promotionMovedata() noexcept = default;
			PYGMALION_INLINE promotionMovedata(promotionMovedata&&) noexcept = default;
			PYGMALION_INLINE promotionMovedata(const promotionMovedata&) noexcept = default;
			PYGMALION_INLINE promotionMovedata& operator=(promotionMovedata&&) noexcept = default;
			PYGMALION_INLINE promotionMovedata& operator=(const promotionMovedata&) noexcept = default;
			PYGMALION_INLINE ~promotionMovedata() noexcept = default;
		};
	}

	template<size_t PIECE>
	class promotionmove :
		public pygmalion::mechanics::move<board, 2 * board::squareType::countUnsignedBits, detail::promotionMovedata, promotionmove<PIECE>>,
		public board::descriptorState
	{
	public:
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		using materialTableType = pygmalion::state::materialTables<descriptorState, boardType>;
		using movebitsType = typename pygmalion::mechanics::move<board, 2 * board::squareType::countUnsignedBits, detail::promotionMovedata, promotionmove<PIECE>>::movebitsType;
		constexpr static const size_t countFromBits{ squareType::countUnsignedBits };
		constexpr static const size_t countToBits{ squareType::countUnsignedBits };
	private:
		constexpr static const inline pieceType m_PromotedPiece{ static_cast<pieceType>(PIECE) };
	public:
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename promotionmove::movedataType) << ":" << promotionmove::countBits << "@promotion" << m_PromotedPiece.toShortString();
			return sstr.str();
		}
	private:
		PYGMALION_INLINE static squareType extractTo(const typename promotionmove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		PYGMALION_INLINE static squareType extractFrom(const typename promotionmove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		PYGMALION_INLINE static void encodeTo(typename promotionmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		PYGMALION_INLINE static void encodeFrom(typename promotionmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	protected:
		constexpr promotionmove() noexcept
		{

		}
		~promotionmove() noexcept = default;
		constexpr promotionmove(promotionmove&&) noexcept = default;
		constexpr promotionmove(const promotionmove&) noexcept = default;
	public:
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename promotionmove::movebitsType moveBits, typename promotionmove::movedataType& movedata, const materialTableType& materialTable) const noexcept
		{
			const squareType from{ promotionmove::extractFrom(moveBits) };
			const squareType to{ promotionmove::extractTo(moveBits) };
			const playerType p{ position.movingPlayer() };
			const squareType enPassantSquare{ position.enPassantSquare() };
			const size_t reversiblePlies{ position.getReversiblePlyCount() };
			position.clearEnPassantSquare();
			position.removePiece(pawn, from, p, materialTable);
			position.addPiece(m_PromotedPiece, to, p, materialTable);
			position.setMovingPlayer(++position.movingPlayer());
			position.resetReversiblePlyCount();
			movedata = typename promotionmove::movedataType(from, to, enPassantSquare, reversiblePlies);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename promotionmove::movedataType& data, const materialTableType& materialTable) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.removePiece(m_PromotedPiece, data.to(), p, materialTable);
			position.addPiece(pawn, data.from(), p, materialTable);
			position.setEnPassantSquare(data.oldEnPassantSquare());
			position.setReversiblePlyCount(static_cast<size_t>(data.reversiblePlies()));
		}
		PYGMALION_INLINE constexpr typename promotionmove::movebitsType create(const squareType from, const squareType to) const noexcept
		{
			typename promotionmove::movebitsType bits{ promotionmove::movebitsType::zero() };
			promotionmove::encodeFrom(bits, from);
			promotionmove::encodeTo(bits, to);
			return bits;
		}
		bool parse_Implementation(const boardType& position, const std::string& text, typename promotionmove::movebitsType& moveBits, size_t& count) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			squareType from;
			squareType to;
			size_t cnt{ 0 };
			if (squareType::parse(text,cnt, from))
			{
				if ((position.pieceOccupancy(pawn) & position.playerOccupancy(p))[from])
				{
					if (p == whitePlayer)
					{
						if (from.rank() == rank7)
						{
							if (squareType::parse(text, cnt, to))
							{
								if (to.rank() == rank8)
								{
									if (!position.totalOccupancy()[to])
									{
										pieceType pc;
										if (pieceType::parse(text, cnt, pc))
										{
											if (pc == m_PromotedPiece)
											{
												moveBits = create(from, to);
												count += cnt;
												return true;
											}
										}
									}
								}
							}
						}
					}
					else
					{
						if (from.rank() == rank2)
						{
							if (squareType::parse(text, cnt, to))
							{
								if (to.rank() == rank1)
								{
									if (!position.totalOccupancy()[to])
									{
										pieceType pc;
										if (pieceType::parse(text, cnt, pc))
										{
											if (pc == m_PromotedPiece)
											{
												moveBits = create(from, to);
												count += cnt;
												return true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename promotionmove::movebitsType moveBits) const noexcept
		{
			const squareType from{ promotionmove::extractFrom(moveBits) };
			const squareType to{ promotionmove::extractTo(moveBits) };
			return from.toShortString() + to.toShortString() + (m_PromotedPiece & whitePlayer).toShortString();
		}
		PYGMALION_INLINE squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			return none;
		}
		PYGMALION_INLINE squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return squaresType(promotionmove::extractFrom(moveBits)) ^ squaresType(promotionmove::extractTo(moveBits));
		}
		PYGMALION_INLINE squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType piece, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType delta{ none };
			if (piece == pawn)
				delta ^= promotionmove::extractFrom(moveBits);
			if (piece == m_PromotedPiece)
				delta ^= promotionmove::extractTo(moveBits);
			return delta;
		}
		PYGMALION_INLINE squareType fromSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return promotionmove::extractFrom(moveBits);
		}
		PYGMALION_INLINE squareType toSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return promotionmove::extractTo(moveBits);
		}
	};
}