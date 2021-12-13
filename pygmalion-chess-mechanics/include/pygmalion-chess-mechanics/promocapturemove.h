namespace pygmalion::chess
{
	namespace detail
	{
		class promocaptureMovedata :
			public pygmalion::mechanics::movedataBase<board>
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
			using materialTableType = pygmalion::state::materialTables<descriptorState, boardType>;
		private:
			squareType m_From;
			squareType m_To;
			flagsType m_OldFlags;
			squareType m_OldEnPassantSquare;
			pieceType m_CapturedPiece;
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
			PYGMALION_INLINE const squareType& oldEnPassantSquare() const noexcept
			{
				return m_OldEnPassantSquare;
			}
			PYGMALION_INLINE const squareType& from() const noexcept
			{
				return m_From;
			}
			PYGMALION_INLINE const squareType& to() const noexcept
			{
				return m_To;
			}
			PYGMALION_INLINE const pieceType& capturedPiece() const noexcept
			{
				return m_CapturedPiece;
			}
			PYGMALION_INLINE promocaptureMovedata(const squareType fromSquare, const squareType toSquare, const flagsType oldFlags_, const pieceType capturedPiece_, const size_t reversiblePlies_, const squareType  oldEnPassantSquare_) noexcept :
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OldFlags{ oldFlags_ },
				m_CapturedPiece{ capturedPiece_ },
				m_ReversiblePlies{ reversiblePlies_ },
				m_OldEnPassantSquare{ oldEnPassantSquare_ }
			{}
			PYGMALION_INLINE promocaptureMovedata() noexcept :
				m_OldFlags{ noFlags }
			{

			}
			PYGMALION_INLINE promocaptureMovedata(promocaptureMovedata&&) noexcept = default;
			PYGMALION_INLINE promocaptureMovedata(const promocaptureMovedata&) noexcept = default;
			PYGMALION_INLINE promocaptureMovedata& operator=(promocaptureMovedata&&) noexcept = default;
			PYGMALION_INLINE promocaptureMovedata& operator=(const promocaptureMovedata&) noexcept = default;
			PYGMALION_INLINE ~promocaptureMovedata() noexcept = default;
		};
	}

	template<size_t PIECE>
	class promocapturemove :
		public pygmalion::mechanics::move<board, 2 * board::squareType::countUnsignedBits, detail::promocaptureMovedata, promocapturemove<PIECE>>,
		public board::descriptorState
	{
	public:
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		using materialTableType = pygmalion::state::materialTables<descriptorState, boardType>;
		using movebitsType = typename pygmalion::mechanics::move<board, 2 * board::squareType::countUnsignedBits, detail::promocaptureMovedata, promocapturemove<PIECE>>::movebitsType;
		constexpr static const size_t countFromBits{ squareType::countUnsignedBits };
		constexpr static const size_t countToBits{ squareType::countUnsignedBits };
	private:
		constexpr static const inline pieceType m_PromotedPiece{ static_cast<pieceType>(PIECE) };
	public:
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename promocapturemove::movedataType) << ":" << promocapturemove::countBits << "@promocapture" << boardType::pieceToString(m_PromotedPiece, whitePlayer);
			return sstr.str();
		}
	private:
		PYGMALION_INLINE static squareType extractTo(const typename promocapturemove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		PYGMALION_INLINE static squareType extractFrom(const typename promocapturemove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		PYGMALION_INLINE static void encodeTo(typename promocapturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		PYGMALION_INLINE static void encodeFrom(typename promocapturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	protected:
		constexpr promocapturemove() noexcept
		{

		}
		~promocapturemove() noexcept = default;
		constexpr promocapturemove(promocapturemove&&) noexcept = default;
		constexpr promocapturemove(const promocapturemove&) noexcept = default;
	public:
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename promocapturemove::movebitsType moveBits, typename promocapturemove::movedataType& movedata, const materialTableType& materialTable) const noexcept
		{
			const squareType from{ promocapturemove::extractFrom(moveBits) };
			const squareType to{ promocapturemove::extractTo(moveBits) };
			const playerType p{ position.movingPlayer() };
			const pieceType pc2{ position.getPiece(to) };
			const playerType p2{ ++position.movingPlayer() };
			const flagsType oldFlags{ position.flags() };
			const squareType enPassantSquare{ position.enPassantSquare() };
			const size_t reversiblePlies{ position.getReversiblePlyCount() };
			position.clearEnPassantSquare();
			position.removePiece(pawn, from, p, materialTable);
			position.removePiece(pc2, to, p2, materialTable);
			position.addPiece(m_PromotedPiece, to, p, materialTable);
			position.setMovingPlayer(p2);
			position.resetReversiblePlyCount();
			if (p == whitePlayer)
			{
				if (pc2 == rook)
				{
					switch (to)
					{
					case squareA8:
						position.clearCastleRightQueensideBlack();
						break;
					case squareH8:
						position.clearCastleRightKingsideBlack();
						break;
					}
				}
			}
			else
			{
				if (pc2 == rook)
				{
					switch (to)
					{
					case squareA1:
						position.clearCastleRightQueensideWhite();
						break;
					case squareH1:
						position.clearCastleRightKingsideWhite();
						break;
					}
				}
			}
			movedata = typename promocapturemove::movedataType(from, to, oldFlags, pc2, reversiblePlies, enPassantSquare);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename promocapturemove::movedataType& data, const materialTableType& materialTable) const noexcept
		{
			const playerType p2{ position.movingPlayer() };
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.removePiece(m_PromotedPiece, data.to(), p, materialTable);
			position.addPiece(pawn, data.from(), p, materialTable);
			position.addPiece(data.capturedPiece(), data.to(), p2, materialTable);
			position.flags()=data.oldFlags();
			position.setReversiblePlyCount(data.reversiblePlies());
			position.setEnPassantSquare(data.oldEnPassantSquare());
		}
		PYGMALION_INLINE constexpr typename promocapturemove::movebitsType create(const squareType from, const squareType to) const noexcept
		{
			typename promocapturemove::movebitsType bits{ promocapturemove::movebitsType::zero() };
			promocapturemove::encodeFrom(bits, from);
			promocapturemove::encodeTo(bits, to);
			return bits;
		}
		bool parse_Implementation(const boardType& position, const std::string& text, typename promocapturemove::movebitsType& moveBits, size_t& count) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const playerType p2{ ++position.movingPlayer() };
			std::string temp{ text };
			squareType from;
			squareType to;
			size_t cnt{ 0 };
			if (boardType::parseSquare(temp, from, cnt))
			{
				std::string temp2{ temp.substr(cnt,temp.length() - cnt) };
				if ((position.pieceOccupancy(pawn) & position.playerOccupancy(p))[from])
				{
					if (p == whitePlayer)
					{
						if (from.rank() == rank7)
						{
							if (boardType::parseSquare(temp2, to, cnt))
							{
								std::string temp3{ temp.substr(cnt,temp.length() - cnt) };
								if (to.rank() == rank8)
								{
									if (position.playerOccupancy(p2)[to])
									{
										playerType p3;
										pieceType pc;
										if (boardType::parsePiece(temp3, pc, p3, cnt))
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
							if (boardType::parseSquare(temp2, to, cnt))
							{
								std::string temp3{ temp.substr(cnt,temp.length() - cnt) };
								if (to.rank() == rank1)
								{
									if (position.playerOccupancy(p2)[to])
									{
										playerType p3;
										pieceType pc;
										if (boardType::parsePiece(temp3, pc, p3, cnt))
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
		std::string toString_Implementation(const boardType& position, const typename promocapturemove::movebitsType moveBits) const noexcept
		{
			const squareType from{ promocapturemove::extractFrom(moveBits) };
			const squareType to{ promocapturemove::extractTo(moveBits) };
			return boardType::squareToString(from) + boardType::squareToString(to) + boardType::pieceToString(m_PromotedPiece, position.movingPlayer());
		}
		PYGMALION_INLINE squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return squaresType(promocapturemove::extractTo(moveBits));
		}
		PYGMALION_INLINE squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return squaresType(promocapturemove::extractFrom(moveBits)) ^ squaresType(promocapturemove::extractTo(moveBits));
		}
		PYGMALION_INLINE squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType piece, const movebitsType moveBits) const noexcept
		{
			const squareType to{ promocapturemove::extractTo(moveBits) };
			constexpr const squaresType none{ squaresType::none() };
			squaresType delta{ none };
			if (piece == pawn)
				delta ^= promocapturemove::extractFrom(moveBits);
			if (piece == m_PromotedPiece)
				delta ^= to;
			if (position.pieceOccupancy(piece)[to])
				delta ^= to;
			return delta;
		}
		PYGMALION_INLINE squareType fromSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return promocapturemove::extractFrom(moveBits);
		}
		PYGMALION_INLINE squareType toSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return promocapturemove::extractTo(moveBits);
		}
	};
}