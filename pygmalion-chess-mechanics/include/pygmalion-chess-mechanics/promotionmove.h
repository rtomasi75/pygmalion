namespace pygmalion::chess
{
	namespace detail
	{
		class promotionMovedata
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			uint_t<countFiles, false> m_OldFlags;
			squareType m_From;
			squareType m_To;
			std::uint16_t m_ReversiblePlies{ 0 };
		public:
			PYGMALION_INLINE std::uint16_t reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			PYGMALION_INLINE const uint_t<countFiles, false> oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			PYGMALION_INLINE squareType from() const noexcept
			{
				return m_From;
			}
			PYGMALION_INLINE squareType to() const noexcept
			{
				return m_To;
			}
			PYGMALION_INLINE promotionMovedata(const squareType fromSquare, const squareType toSquare, const uint_t<countFiles, false> oldFlags_, const std::uint16_t reversiblePlies_) noexcept :
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OldFlags{ oldFlags_ },
				m_ReversiblePlies{ reversiblePlies_ }
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
		using movebitsType = typename pygmalion::mechanics::move<board, 2 * board::squareType::countUnsignedBits, detail::promotionMovedata, promotionmove<PIECE>>::movebitsType;
		constexpr static const size_t countFromBits{ squareType::countUnsignedBits };
		constexpr static const size_t countToBits{ squareType::countUnsignedBits };
	private:
		constexpr static const inline pieceType m_PromotedPiece{ static_cast<pieceType>(PIECE) };
	public:
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename promotionmove::movedataType) << ":" << promotionmove::countBits << "@promotion" << boardType::pieceToString(m_PromotedPiece, whitePlayer);
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
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename promotionmove::movebitsType moveBits, typename promotionmove::movedataType& movedata) const noexcept
		{
			const squareType from{ promotionmove::extractFrom(moveBits) };
			const squareType to{ promotionmove::extractTo(moveBits) };
			const playerType p{ position.movingPlayer() };
			const uint_t<countFiles, false> oldFlags{ position.extractFlagRange<4, 11>() };
			const std::uint16_t reversiblePlies{ position.cumulation().reversiblePlies() };
			position.clearEnPassantFiles();
			position.removePiece(pawn, from, p);
			position.addPiece(m_PromotedPiece, to, p);
			position.setMovingPlayer(++position.movingPlayer());
			position.cumulation().reversiblePlies() = 0;
			movedata = typename promotionmove::movedataType(from, to, oldFlags, reversiblePlies);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename promotionmove::movedataType& data) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.removePiece(m_PromotedPiece, data.to(), p);
			position.addPiece(pawn, data.from(), p);
			position.storeFlagRange<4, 11>(data.oldFlags());
			position.cumulation().reversiblePlies() = data.reversiblePlies();
		}
		PYGMALION_INLINE constexpr typename promotionmove::movebitsType create(const squareType from, const squareType to) const noexcept
		{
			typename promotionmove::movebitsType bits{ promotionmove::movebitsType::zero() };
			promotionmove::encodeFrom(bits, from);
			promotionmove::encodeTo(bits, to);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename promotionmove::movebitsType& moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			std::string temp{ text };
			squareType from;
			squareType to;
			if (boardType::parseSquare(temp, from))
			{
				if ((position.pieceOccupancy(pawn) & position.playerOccupancy(p))[from])
				{
					if (p == whitePlayer)
					{
						if (from.rank() == rank7)
						{
							if (boardType::parseSquare(temp, to))
							{
								if (to.rank() == rank8)
								{
									if (!position.totalOccupancy()[to])
									{
										playerType p2;
										pieceType pc;
										if (boardType::parsePiece(temp, pc, p2))
										{
											if (pc == m_PromotedPiece)
											{
												moveBits = create(from, to);
												text = temp;
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
							if (boardType::parseSquare(temp, to))
							{
								if (to.rank() == rank1)
								{
									if (!position.totalOccupancy()[to])
									{
										playerType p2;
										pieceType pc;
										if (boardType::parsePiece(temp, pc, p2))
										{
											if (pc == m_PromotedPiece)
											{
												moveBits = create(from, to);
												text = temp;
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
			return boardType::squareToString(from) + boardType::squareToString(to) + boardType::pieceToString(m_PromotedPiece, position.movingPlayer());
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