namespace pygmalion::chess
{
	namespace detail
	{
		class enpassantMovedata
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			uint_t<countFiles, false> m_OldFlags;
			squareType m_From;
			squareType m_To;
			squareType m_CaptureSquare;
			std::uint16_t m_ReversiblePlies{ 0 };
		public:
			constexpr std::uint16_t reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			constexpr const uint_t<countFiles, false>& oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			constexpr squareType from() const noexcept
			{
				return m_From;
			}
			constexpr squareType captureSquare() const noexcept
			{
				return m_CaptureSquare;
			}
			constexpr squareType to() const noexcept
			{
				return m_To;
			}
			constexpr enpassantMovedata(const squareType from_, const squareType to_, const uint_t<countFiles, false>& oldFlags_, const squareType captureSquare, const std::uint16_t reversiblePlies_) noexcept :
				m_From{ from_ },
				m_To{ to_ },
				m_OldFlags{ oldFlags_ },
				m_CaptureSquare{ captureSquare },
				m_ReversiblePlies{ reversiblePlies_ }
			{}
			constexpr enpassantMovedata() noexcept = default;
			constexpr enpassantMovedata(enpassantMovedata&&) noexcept = default;
			constexpr enpassantMovedata(const enpassantMovedata&) noexcept = default;
			constexpr enpassantMovedata& operator=(enpassantMovedata&&) noexcept = default;
			constexpr enpassantMovedata& operator=(const enpassantMovedata&) noexcept = default;
			~enpassantMovedata() noexcept = default;
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
		std::string name_Implementation() const noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename enpassantmove::movedataType) << ":" << enpassantmove::countBits << "@enpassant";
			return sstr.str();
		}
	private:
		constexpr static fileType extractFile2(const typename enpassantmove::movebitsType& movebits) noexcept
		{
			const fileType f{ fileType(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(movebits.template extractBits<countFileBits, countFileBits>())) };
			return f;
		}
		constexpr static void encodeFile2(typename enpassantmove::movebitsType& movebits, const fileType f) noexcept
		{
			movebits.template storeBits<countFileBits, countFileBits>(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(f));
		}
		constexpr static fileType extractFile1(const typename enpassantmove::movebitsType& movebits) noexcept
		{
			const fileType f{ fileType(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(movebits.template extractBits<0, countFileBits>())) };
			return f;
		}
		constexpr static void encodeFile1(typename enpassantmove::movebitsType& movebits, const fileType f) noexcept
		{
			movebits.template storeBits<0, countFileBits>(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(f));
		}
	public:
		constexpr enpassantmove() noexcept = default;
		~enpassantmove() noexcept = default;
		constexpr enpassantmove(enpassantmove&&) noexcept = default;
		constexpr enpassantmove(const enpassantmove&) noexcept = default;
		constexpr enpassantmove& operator=(enpassantmove&&) noexcept = default;
		constexpr enpassantmove& operator=(const enpassantmove&) noexcept = default;
		constexpr typename enpassantmove::movedataType doMove_Implementation(boardType& position, const typename enpassantmove::movebitsType& moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const playerType p2{ ++position.movingPlayer() };
			const fileType f1{ enpassantmove::extractFile1(moveBits) };
			const fileType f2{ enpassantmove::extractFile2(moveBits) };
			const uint_t<countFiles, false> oldFlags{ position.extractFlagRange<4, 11>() };
			const std::uint16_t reversiblePlies{ position.cumulation().reversiblePlies() };
			if (p == whitePlayer)
			{
				const rankType r1{ rank5 };
				const rankType r2{ rank6 };
				const squareType from{ f1 & r1 };
				const squareType to{ f2 & r2 };
				const squareType capture{ f2 & r1 };
				position.clearEnPassantFiles();
				position.removePiece(pawn, from, p);
				position.addPiece(pawn, to, p);
				position.removePiece(pawn, capture, p2);
				position.setMovingPlayer(p2);
				position.cumulation().reversiblePlies() = 0;
				return typename enpassantmove::movedataType(from, to, oldFlags, capture, reversiblePlies);
			}
			else
			{
				const rankType r1{ rank4 };
				const rankType r2{ rank3 };
				const squareType from{ f1 & r1 };
				const squareType to{ f2 & r2 };
				const squareType capture{ f2 & r1 };
				position.clearEnPassantFiles();
				position.removePiece(pawn, from, p);
				position.addPiece(pawn, to, p);
				position.removePiece(pawn, capture, p2);
				position.setMovingPlayer(p2);
				position.cumulation().reversiblePlies() = 0;
				return typename enpassantmove::movedataType(from, to, oldFlags, capture, reversiblePlies);
			}
		}
		constexpr void undoMove_Implementation(boardType& position, const typename enpassantmove::movedataType& data) const noexcept
		{
			const playerType p2{ position.movingPlayer() };
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.removePiece(pawn, data.to(), p);
			position.addPiece(pawn, data.from(), p);
			position.addPiece(pawn, data.captureSquare(), p2);
			position.storeFlagRange<4, 11>(data.oldFlags());
			position.cumulation().reversiblePlies() = data.reversiblePlies();
		}
		constexpr typename enpassantmove::movebitsType create(const fileType file1, const fileType file2) const noexcept
		{
			typename enpassantmove::movebitsType bits{ enpassantmove::movebitsType::zero() };
			enpassantmove::encodeFile1(bits, file1);
			enpassantmove::encodeFile2(bits, file2);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename enpassantmove::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			const playerType movingPlayer{ position.movingPlayer() };
			squareType from;
			squareType to;
			if (movingPlayer == whitePlayer)
			{
				if (boardType::parseSquare(temp, from))
				{
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::pawn))[from] && (from.rank() == rank5))
					{
						if (boardType::parseSquare(temp, to))
						{
							if ((position.checkEnPassantFile(to.file())) && (position.playerOccupancy(((movingPlayer + 1) % countPlayers)) & position.pieceOccupancy(descriptorState::pawn))[rank5 & to.file()] && (to.rank() == rank6))
							{
								if (!position.totalOccupancy()[to])
								{
									moveBits = create(from.file(), to.file());
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
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::pawn))[from] && (from.rank() == rank4))
					{
						if (boardType::parseSquare(temp, to))
						{
							if ((position.checkEnPassantFile(to.file())) && (position.playerOccupancy((movingPlayer + 1) % countPlayers) & position.pieceOccupancy(descriptorState::pawn))[rank4 & to.file()] && (to.rank() == rank3))
							{
								if (!position.totalOccupancy()[to])
								{
									moveBits = create(from.file(), to.file());
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
		std::string toString_Implementation(const boardType& position, const typename enpassantmove::movebitsType& moveBits) const noexcept
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
				return boardType::squareToString(from) + boardType::squareToString(to);
			}
			else
			{
				constexpr const rankType r1{ rank4 };
				constexpr const rankType r2{ rank3 };
				const squareType from{ f1 & r1 };
				const squareType to{ f2 & r2 };
				return boardType::squareToString(from) + boardType::squareToString(to);
			}
		}
		constexpr squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
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
		constexpr squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
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
		constexpr squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType& piece, const movebitsType& moveBits) const noexcept
		{
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
				return squaresType::none();
		}
		constexpr squareType fromSquare_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
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
		constexpr squareType toSquare_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
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