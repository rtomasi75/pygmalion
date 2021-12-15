namespace pygmalion::chess
{
	namespace detail
	{
		class doublepushMovedata :
			public pygmalion::mechanics::movedataBase<board>
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			size_t m_ReversiblePlies{ 0 };
			squaresType m_OldEnPassantTargets;
			squareType m_OldEnPassantVictim;
			squareType m_From;
			squareType m_To;
		public:
			PYGMALION_INLINE const size_t& reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			PYGMALION_INLINE const squaresType& oldEnPassantTargets() const noexcept
			{
				return m_OldEnPassantTargets;
			}
			PYGMALION_INLINE const squareType& oldEnPassantVictim() const noexcept
			{
				return m_OldEnPassantVictim;
			}
			PYGMALION_INLINE const squareType& from() const noexcept
			{
				return m_From;
			}
			PYGMALION_INLINE const squareType& to() const noexcept
			{
				return m_To;
			}
			PYGMALION_INLINE doublepushMovedata(const squareType from_, const squareType to_, const squaresType oldEnPassantTargets_, const squareType oldEnPassantVictim_, const size_t reversiblePlies_) noexcept :
				m_From{ from_ },
				m_To{ to_ },
				m_OldEnPassantTargets{ oldEnPassantTargets_ },
				m_OldEnPassantVictim{ oldEnPassantVictim_ },
				m_ReversiblePlies{ reversiblePlies_ }
			{}
			PYGMALION_INLINE doublepushMovedata() noexcept = default;
			PYGMALION_INLINE doublepushMovedata(doublepushMovedata&&) noexcept = default;
			PYGMALION_INLINE doublepushMovedata(const doublepushMovedata&) noexcept = default;
			PYGMALION_INLINE doublepushMovedata& operator=(doublepushMovedata&&) noexcept = default;
			PYGMALION_INLINE doublepushMovedata& operator=(const doublepushMovedata&) noexcept = default;
			PYGMALION_INLINE ~doublepushMovedata() noexcept = default;
		};
	}

	class doublepushmove :
		public pygmalion::mechanics::move<board, board::playerType::countUnsignedBits + board::fileType::countUnsignedBits, detail::doublepushMovedata, doublepushmove>,
		public board::descriptorState
	{
	public:
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countFileBits{ fileType::countUnsignedBits };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename doublepushmove::movedataType) << ":" << doublepushmove::countBits << "@doublepush";
			return sstr.str();
		}
	private:
		PYGMALION_INLINE static fileType extractFile(const typename doublepushmove::movebitsType movebits) noexcept
		{
			const fileType f{ fileType(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(movebits.template extractBits<0, countFileBits>())) };
			return f;
		}
		PYGMALION_INLINE static void encodeFile(typename doublepushmove::movebitsType& movebits, const fileType f) noexcept
		{
			movebits.template storeBits<0, countFileBits>(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(f));
		}
	public:
		constexpr doublepushmove() noexcept = default;
		~doublepushmove() noexcept = default;
		constexpr doublepushmove(doublepushmove&&) noexcept = default;
		constexpr doublepushmove(const doublepushmove&) noexcept = default;
		constexpr doublepushmove& operator=(doublepushmove&&) noexcept
		{
			return *this;
		}
		constexpr doublepushmove& operator=(const doublepushmove&) noexcept
		{
			return *this;
		}
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename doublepushmove::movebitsType& moveBits, typename doublepushmove::movedataType& movedata, const materialTableType& materialTable) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const fileType f{ doublepushmove::extractFile(moveBits) };
			const squaresType oldEnPassantTargets{ position.enPassantTargets() };
			const squareType oldEnPassantVictim{ position.enPassantTargets() };
			const size_t reversiblePlies{ position.getReversiblePlyCount() };
			if (p == whitePlayer)
			{
				constexpr const rankType r1{ rank2 };
				constexpr const rankType r2{ rank4 };
				constexpr const rankType r3{ rank3 };
				const squareType from{ f & r1 };
				const squareType to{ f & r2 };
				const squareType ep{ f & r3 };
				position.movePiece(pawn, from, to, p, materialTable);
				position.setEnPassant(squaresType(ep), to);
				position.setMovingPlayer(++position.movingPlayer());
				position.resetReversiblePlyCount();
				movedata = doublepushmove::movedataType(from, to, oldEnPassantTargets, oldEnPassantVictim, reversiblePlies);
			}
			else
			{
				constexpr const rankType r1{ rank7 };
				constexpr const rankType r2{ rank5 };
				constexpr const rankType r3{ rank6 };
				const squareType from{ f & r1 };
				const squareType to{ f & r2 };
				const squareType ep{ f & r3 };
				position.movePiece(pawn, from, to, p, materialTable);
				position.setEnPassant(squaresType(ep), to);
				position.setMovingPlayer(++position.movingPlayer());
				position.resetReversiblePlyCount();
				movedata = doublepushmove::movedataType(from, to, oldEnPassantTargets, oldEnPassantVictim, reversiblePlies);
			}
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename doublepushmove::movedataType& data, const materialTableType& materialTable) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.movePiece(pawn, data.to(), data.from(), p, materialTable);
			position.setEnPassant(data.oldEnPassantTargets(), data.oldEnPassantVictim());
			position.setReversiblePlyCount(data.reversiblePlies());
		}
		PYGMALION_INLINE typename doublepushmove::movebitsType create(const fileType file) const noexcept
		{
			typename doublepushmove::movebitsType bits{ doublepushmove::movebitsType::zero() };
			doublepushmove::encodeFile(bits, file);
			return bits;
		}
		bool parse_Implementation(const boardType& position, const std::string& text, typename doublepushmove::movebitsType& moveBits, size_t& count) const noexcept
		{
			playerType movingPlayer{ position.movingPlayer() };
			squareType from;
			squareType to;
			size_t cnt{ 0 };
			if (movingPlayer == whitePlayer)
			{
				if (squareType::parse(text, cnt, from))
				{
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::pawn))[from] && (from.rank() == rank2))
					{
						if (squareType::parse(text, cnt, to))
						{
							if ((!position.totalOccupancy()[to]) && (to.rank() == rank4))
							{
								if (!position.totalOccupancy()[from.file() & rank3])
								{
									moveBits = create(from.file());
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
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::pawn))[from] && (from.rank() == rank7))
					{
						if (squareType::parse(text, cnt, to))
						{
							if ((!position.totalOccupancy()[to]) && (to.rank() == rank5))
							{
								if (!position.totalOccupancy()[from.file() & rank6])
								{
									moveBits = create(from.file());
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
		std::string toString_Implementation(const boardType& position, const typename doublepushmove::movebitsType moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const fileType f{ doublepushmove::extractFile(moveBits) };
			if (p == whitePlayer)
			{
				constexpr const rankType r1{ rank2 };
				constexpr const rankType r2{ rank4 };
				const squareType from{ f & r1 };
				const squareType to{ f & r2 };
				return from.toShortString() + to.toShortString();
			}
			else
			{
				constexpr const rankType r1{ rank7 };
				constexpr const rankType r2{ rank5 };
				const squareType from{ f & r1 };
				const squareType to{ f & r2 };
				return from.toShortString() + to.toShortString();
			}
		}
		PYGMALION_INLINE squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			return none;
		}
		PYGMALION_INLINE squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const fileType f{ doublepushmove::extractFile(moveBits) };
			if (p == whitePlayer)
			{
				constexpr const rankType r1{ rank2 };
				constexpr const rankType r2{ rank4 };
				const squareType from{ f & r1 };
				const squareType to{ f & r2 };
				return squaresType(from) ^ squaresType(to);
			}
			else
			{
				constexpr const rankType r1{ rank7 };
				constexpr const rankType r2{ rank5 };
				const squareType from{ f & r1 };
				const squareType to{ f & r2 };
				return squaresType(from) ^ squaresType(to);
			}
		}
		PYGMALION_INLINE squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType piece, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			if (piece == pawn)
			{
				const playerType p{ position.movingPlayer() };
				const fileType f{ doublepushmove::extractFile(moveBits) };
				if (p == whitePlayer)
				{
					constexpr const rankType r1{ rank2 };
					constexpr const rankType r2{ rank4 };
					const squareType from{ f & r1 };
					const squareType to{ f & r2 };
					return squaresType(from) ^ squaresType(to);
				}
				else
				{
					constexpr const rankType r1{ rank7 };
					constexpr const rankType r2{ rank5 };
					const squareType from{ f & r1 };
					const squareType to{ f & r2 };
					return squaresType(from) ^ squaresType(to);
				}
			}
			else
				return none;
		}
		PYGMALION_INLINE squareType fromSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const fileType f{ doublepushmove::extractFile(moveBits) };
			if (p == whitePlayer)
			{
				constexpr const rankType r1{ rank2 };
				const squareType from{ f & r1 };
				return from;
			}
			else
			{
				constexpr const rankType r1{ rank7 };
				const squareType from{ f & r1 };
				return from;
			}
		}
		PYGMALION_INLINE squareType toSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const fileType f{ doublepushmove::extractFile(moveBits) };
			if (p == whitePlayer)
			{
				constexpr const rankType r2{ rank4 };
				const squareType to{ f & r2 };
				return to;
			}
			else
			{
				constexpr const rankType r2{ rank5 };
				const squareType to{ f & r2 };
				return to;
			}
		}
	};

}