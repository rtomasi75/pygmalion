namespace pygmalion::chess
{
	namespace detail
	{
		class enpassantMovedata :
			public pygmalion::mechanics::movedataBase<board>
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			squareType m_OldEnPassantSquare;
			squareType m_From;
			squareType m_To;
			squareType m_CaptureSquare;
			size_t m_ReversiblePlies{ 0 };
		public:
			PYGMALION_INLINE const size_t& reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			PYGMALION_INLINE const squareType& oldEnPassantSquare() const noexcept
			{
				return m_OldEnPassantSquare;
			}
			PYGMALION_INLINE const squareType& from() const noexcept
			{
				return m_From;
			}
			PYGMALION_INLINE const squareType& captureSquare() const noexcept
			{
				return m_CaptureSquare;
			}
			PYGMALION_INLINE const squareType& to() const noexcept
			{
				return m_To;
			}
			PYGMALION_INLINE enpassantMovedata(const squareType from_, const squareType to_, const squareType oldEnPassantSquare_, const squareType captureSquare, const size_t reversiblePlies_) noexcept :
				m_From{ from_ },
				m_To{ to_ },
				m_OldEnPassantSquare{ oldEnPassantSquare_ },
				m_CaptureSquare{ captureSquare },
				m_ReversiblePlies{ reversiblePlies_ }
			{}
			PYGMALION_INLINE enpassantMovedata() noexcept = default;
			PYGMALION_INLINE enpassantMovedata(enpassantMovedata&&) noexcept = default;
			PYGMALION_INLINE enpassantMovedata(const enpassantMovedata&) noexcept = default;
			PYGMALION_INLINE enpassantMovedata& operator=(enpassantMovedata&&) noexcept = default;
			PYGMALION_INLINE enpassantMovedata& operator=(const enpassantMovedata&) noexcept = default;
			PYGMALION_INLINE ~enpassantMovedata() noexcept = default;
		};
	}

	class enpassantmove :
		public pygmalion::mechanics::move<board, board::playerType::countUnsignedBits + 2 * board::fileType::countUnsignedBits, detail::enpassantMovedata, enpassantmove>,
		public board::descriptorState
	{
	public:
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countPlayerBits{ playerType::countUnsignedBits };
		constexpr static const size_t countFileBits{ fileType::countUnsignedBits };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename enpassantmove::movedataType) << ":" << enpassantmove::countBits << "@enpassant";
			return sstr.str();
		}
	private:
		PYGMALION_INLINE static fileType extractFile2(const typename enpassantmove::movebitsType movebits) noexcept
		{
			const fileType f{ fileType(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(movebits.template extractBits<countFileBits, countFileBits>())) };
			return f;
		}
		PYGMALION_INLINE static void encodeFile2(typename enpassantmove::movebitsType& movebits, const fileType f) noexcept
		{
			movebits.template storeBits<countFileBits, countFileBits>(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(f));
		}
		PYGMALION_INLINE static fileType extractFile1(const typename enpassantmove::movebitsType movebits) noexcept
		{
			const fileType f{ fileType(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(movebits.template extractBits<0, countFileBits>())) };
			return f;
		}
		PYGMALION_INLINE static void encodeFile1(typename enpassantmove::movebitsType& movebits, const fileType f) noexcept
		{
			movebits.template storeBits<0, countFileBits>(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(f));
		}
	public:
		constexpr enpassantmove() noexcept = default;
		~enpassantmove() noexcept = default;
		constexpr enpassantmove(enpassantmove&&) noexcept = default;
		constexpr enpassantmove(const enpassantmove&) noexcept = default;
		constexpr enpassantmove& operator=(enpassantmove&&) noexcept
		{
			return *this;
		}
		constexpr enpassantmove& operator=(const enpassantmove&) noexcept
		{
			return *this;
		}
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename enpassantmove::movebitsType moveBits, typename enpassantmove::movedataType& movedata, const materialTableType& materialTable) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const playerType p2{ ++position.movingPlayer() };
			const fileType f1{ enpassantmove::extractFile1(moveBits) };
			const fileType f2{ enpassantmove::extractFile2(moveBits) };
			const squareType oldEnPassantSquare{ position.enPassantSquare() };
			const size_t reversiblePlies{ position.getReversiblePlyCount() };
			if (p == whitePlayer)
			{
				constexpr const rankType r1{ rank5 };
				constexpr const rankType r2{ rank6 };
				const squareType from{ f1 & r1 };
				const squareType to{ f2 & r2 };
				const squareType capture{ f2 & r1 };
				if (to != oldEnPassantSquare)
					std::cout << position << position.getFen() << std::endl;
				PYGMALION_ASSERT(to == oldEnPassantSquare);
				position.clearEnPassantSquare();
				position.removePiece(pawn, capture, p2, materialTable);
				position.movePiece(pawn, from, to, p, materialTable);
				position.setMovingPlayer(p2);
				position.resetReversiblePlyCount();
				movedata = typename enpassantmove::movedataType(from, to, oldEnPassantSquare, capture, reversiblePlies);
			}
			else
			{
				constexpr const rankType r1{ rank4 };
				constexpr const rankType r2{ rank3 };
				const squareType from{ f1 & r1 };
				const squareType to{ f2 & r2 };
				const squareType capture{ f2 & r1 };
				if (to != oldEnPassantSquare)
					std::cout << position << position.getFen() << std::endl;
				PYGMALION_ASSERT(to == oldEnPassantSquare);
				position.clearEnPassantSquare();
				position.removePiece(pawn, capture, p2, materialTable);
				position.movePiece(pawn, from, to, p, materialTable);
				position.setMovingPlayer(p2);
				position.resetReversiblePlyCount();
				movedata = typename enpassantmove::movedataType(from, to, oldEnPassantSquare, capture, reversiblePlies);
			}
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename enpassantmove::movedataType& data, const materialTableType& materialTable) const noexcept
		{
			const playerType p2{ position.movingPlayer() };
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.movePiece(pawn, data.to(), data.from(), p, materialTable);
			position.addPiece(pawn, data.captureSquare(), p2, materialTable);
			position.setEnPassantSquare(data.oldEnPassantSquare());
			position.setReversiblePlyCount(data.reversiblePlies());
		}
		PYGMALION_INLINE typename enpassantmove::movebitsType create(const fileType file1, const fileType file2) const noexcept
		{
			typename enpassantmove::movebitsType bits{ enpassantmove::movebitsType::zero() };
			enpassantmove::encodeFile1(bits, file1);
			enpassantmove::encodeFile2(bits, file2);
			return bits;
		}
		bool parse_Implementation(const boardType& position, const std::string& text, typename enpassantmove::movebitsType& moveBits, size_t& count) const noexcept
		{
			const playerType movingPlayer{ position.movingPlayer() };
			squareType from;
			squareType to;
			size_t cnt{ 0 };
			if (movingPlayer == whitePlayer)
			{
				if (squareType::parse(text,cnt,from))
				{
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::pawn))[from] && (from.rank() == rank5))
					{
						if (squareType::parse(text, cnt, to))
						{
							if ((position.checkEnPassantSquare(to)) && (position.playerOccupancy(((movingPlayer + 1) % countPlayers)) & position.pieceOccupancy(descriptorState::pawn))[rank5 & to.file()] && (to.rank() == rank6))
							{
								if (!position.totalOccupancy()[to])
								{
									moveBits = create(from.file(), to.file());
									count += cnt;
									return true;
								}
							}
						}
					}
				}
			}
			else
			{
				if (squareType::parse(text, cnt, from))
				{
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::pawn))[from] && (from.rank() == rank4))
					{
						if (squareType::parse(text, cnt, to))
						{
							if ((position.checkEnPassantSquare(to)) && (position.playerOccupancy((movingPlayer + 1) % countPlayers) & position.pieceOccupancy(descriptorState::pawn))[rank4 & to.file()] && (to.rank() == rank3))
							{
								if (!position.totalOccupancy()[to])
								{
									moveBits = create(from.file(), to.file());
									count += cnt;
									return true;
								}
							}
						}
					}
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename enpassantmove::movebitsType moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const fileType f1{ enpassantmove::extractFile1(moveBits) };
			const fileType f2{ enpassantmove::extractFile2(moveBits) };
			if (p == whitePlayer)
			{
				constexpr const rankType r1{ rank5 };
				constexpr const rankType r2{ rank6 };
				const squareType from{ f1 & r1 };
				const squareType to{ f2 & r2 };
				return from.toShortString() + to.toShortString();
			}
			else
			{
				constexpr const rankType r1{ rank4 };
				constexpr const rankType r2{ rank3 };
				const squareType from{ f1 & r1 };
				const squareType to{ f2 & r2 };
				return from.toShortString() + to.toShortString();
			}
		}
		PYGMALION_INLINE squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const fileType f2{ enpassantmove::extractFile2(moveBits) };
			if (p == whitePlayer)
			{
				constexpr const rankType r1{ rank5 };
				constexpr const rankType r2{ rank6 };
				const squareType cap{ f2 & r1 };
				return squaresType(cap);
			}
			else
			{
				constexpr const rankType r1{ rank4 };
				constexpr const rankType r2{ rank3 };
				const squareType cap{ f2 & r1 };
				return squaresType(cap);
			}
		}
		PYGMALION_INLINE squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const fileType f1{ enpassantmove::extractFile1(moveBits) };
			const fileType f2{ enpassantmove::extractFile2(moveBits) };
			if (p == whitePlayer)
			{
				constexpr const rankType r1{ rank5 };
				constexpr const rankType r2{ rank6 };
				const squareType from{ f1 & r1 };
				const squareType to{ f2 & r2 };
				return squaresType(from) ^ squaresType(to);
			}
			else
			{
				constexpr const rankType r1{ rank4 };
				constexpr const rankType r2{ rank3 };
				const squareType from{ f1 & r1 };
				const squareType to{ f2 & r2 };
				return squaresType(from) ^ squaresType(to);
			}
		}
		PYGMALION_INLINE squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType piece, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			if (piece == pawn)
			{
				const playerType p{ position.movingPlayer() };
				const fileType f1{ enpassantmove::extractFile1(moveBits) };
				const fileType f2{ enpassantmove::extractFile2(moveBits) };
				if (p == whitePlayer)
				{
					constexpr const rankType r1{ rank5 };
					constexpr const rankType r2{ rank6 };
					const squareType from{ f1 & r1 };
					const squareType to{ f2 & r2 };
					const squareType cap{ f2 & r1 };
					return squaresType(from) ^ squaresType(to) ^ squaresType(cap);
				}
				else
				{
					constexpr const rankType r1{ rank4 };
					constexpr const rankType r2{ rank3 };
					const squareType from{ f1 & r1 };
					const squareType to{ f2 & r2 };
					const squareType cap{ f2 & r1 };
					return squaresType(from) ^ squaresType(to) ^ squaresType(cap);
				}
			}
			else
				return none;
		}
		PYGMALION_INLINE squareType fromSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const fileType f1{ enpassantmove::extractFile1(moveBits) };
			if (p == whitePlayer)
			{
				constexpr const rankType r1{ rank5 };
				const squareType from{ f1 & r1 };
				return from;
			}
			else
			{
				constexpr const rankType r1{ rank4 };
				const squareType from{ f1 & r1 };
				return from;
			}
		}
		PYGMALION_INLINE squareType toSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const fileType f2{ enpassantmove::extractFile2(moveBits) };
			if (p == whitePlayer)
			{
				constexpr const rankType r2{ rank6 };
				const squareType to{ f2 & r2 };
				return to;
			}
			else
			{
				constexpr const rankType r2{ rank3 };
				const squareType to{ f2 & r2 };
				return to;
			}
		}
	};

}