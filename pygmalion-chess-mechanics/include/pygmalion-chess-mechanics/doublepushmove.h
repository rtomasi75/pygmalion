namespace pygmalion::chess
{
	namespace detail
	{
		class doublepushMovedata
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
			constexpr std::uint16_t reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			constexpr const uint_t<countFiles, false> oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			constexpr squareType from() const noexcept
			{
				return m_From;
			}
			constexpr squareType to() const noexcept
			{
				return m_To;
			}
			constexpr doublepushMovedata(const squareType from_, const squareType to_, const uint_t<countFiles, false>& oldFlags_, const std::uint16_t reversiblePlies_) noexcept :
				m_From{ from_ },
				m_To{ to_ },
				m_OldFlags{ oldFlags_ },
				m_ReversiblePlies{ reversiblePlies_ }
			{}
			constexpr doublepushMovedata() noexcept = default;
			constexpr doublepushMovedata(doublepushMovedata&&) noexcept = default;
			constexpr doublepushMovedata(const doublepushMovedata&) noexcept = default;
			constexpr doublepushMovedata& operator=(doublepushMovedata&&) noexcept = default;
			constexpr doublepushMovedata& operator=(const doublepushMovedata&) noexcept = default;
			~doublepushMovedata() noexcept = default;
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
		constexpr static fileType extractFile(const typename doublepushmove::movebitsType movebits) noexcept
		{
			const fileType f{ fileType(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(movebits.template extractBits<0, countFileBits>())) };
			return f;
		}
		constexpr static void encodeFile(typename doublepushmove::movebitsType& movebits, const fileType f) noexcept
		{
			movebits.template storeBits<0, countFileBits>(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(f));
		}
	public:
		doublepushmove() noexcept = default;
		~doublepushmove() noexcept = default;
		doublepushmove(doublepushmove&&) noexcept = default;
		doublepushmove(const doublepushmove&) noexcept = default;
		doublepushmove& operator=(doublepushmove&&) noexcept = default;
		doublepushmove& operator=(const doublepushmove&) noexcept = default;
		typename doublepushmove::movedataType doMove_Implementation(boardType& position, const typename doublepushmove::movebitsType& moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const fileType f{ doublepushmove::extractFile(moveBits) };
			const uint_t<countFiles, false> oldFlags{ position.extractFlagRange<4, 11>() };
			const std::uint16_t reversiblePlies{ position.cumulation().reversiblePlies() };
			if (p == whitePlayer)
			{
				const rankType r1{ rank2 };
				const rankType r2{ rank4 };
				const squareType from{ f & r1 };
				const squareType to{ f & r2 };
				position.clearEnPassantFiles();
				position.removePiece(pawn, from, p);
				position.addPiece(pawn, to, p);
				position.setEnPassantFile(f);
				position.setMovingPlayer(++position.movingPlayer());
				position.cumulation().reversiblePlies() = 0;
				return typename doublepushmove::movedataType(from, to, oldFlags, reversiblePlies);
			}
			else
			{
				const rankType r1{ rank7 };
				const rankType r2{ rank5 };
				const squareType from{ f & r1 };
				const squareType to{ f & r2 };
				position.clearEnPassantFiles();
				position.removePiece(pawn, from, p);
				position.addPiece(pawn, to, p);
				position.setEnPassantFile(f);
				position.setMovingPlayer(++position.movingPlayer());
				position.cumulation().reversiblePlies() = 0;
				return typename doublepushmove::movedataType(from, to, oldFlags, reversiblePlies);
			}
		}
		void undoMove_Implementation(boardType& position, const typename doublepushmove::movedataType& data) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.removePiece(pawn, data.to(), p);
			position.addPiece(pawn, data.from(), p);
			position.storeFlagRange<4, 11>(data.oldFlags());
			position.cumulation().reversiblePlies() = data.reversiblePlies();
		}
		typename doublepushmove::movebitsType create(const fileType file) const noexcept
		{
			typename doublepushmove::movebitsType bits{ doublepushmove::movebitsType::zero() };
			doublepushmove::encodeFile(bits, file);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename doublepushmove::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			playerType movingPlayer{ position.movingPlayer() };
			squareType from;
			squareType to;
			if (movingPlayer == whitePlayer)
			{
				if (boardType::parseSquare(temp, from))
				{
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::pawn))[from] && (from.rank() == rank2))
					{
						if (boardType::parseSquare(temp, to))
						{
							if ((!position.totalOccupancy()[to]) && (to.rank() == rank4))
							{
								if (!position.totalOccupancy()[from.file() & rank3])
								{
									moveBits = create(from.file());
									text = temp;
									return true;
								}
							}
						}
					}
				}
			}
			else
			{
				if (boardType::parseSquare(temp, from))
				{
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::pawn))[from] && (from.rank() == rank7))
					{
						if (boardType::parseSquare(temp, to))
						{
							if ((!position.totalOccupancy()[to]) && (to.rank() == rank5))
							{
								if (!position.totalOccupancy()[from.file() & rank6])
								{
									moveBits = create(from.file());
									text = temp;
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
				return boardType::squareToString(from) + boardType::squareToString(to);
			}
			else
			{
				constexpr const rankType r1{ rank7 };
				constexpr const rankType r2{ rank5 };
				const squareType from{ f & r1 };
				const squareType to{ f & r2 };
				return boardType::squareToString(from) + boardType::squareToString(to);
			}
		}
		squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			return none;
		}
		squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
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
		squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType piece, const movebitsType moveBits) const noexcept
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
		squareType fromSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
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
		squareType toSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
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