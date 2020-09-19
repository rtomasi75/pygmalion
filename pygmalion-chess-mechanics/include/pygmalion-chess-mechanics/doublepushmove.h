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
			playerType m_MovingPlayer;
			squareType m_From;
			squareType m_To;
			uint_t<countFiles, false> m_OldFlags;
		public:
			constexpr const uint_t<countFiles, false>& oldFlags() const noexcept
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
			constexpr playerType movingPlayer() const noexcept
			{
				return m_MovingPlayer;
			}
			constexpr doublepushMovedata(const playerType movingPlayer_, const squareType from_, const squareType to_, const uint_t<countFiles, false>& oldFlags_) noexcept :
				m_From{ from_ },
				m_To{ to_ },
				m_MovingPlayer{ movingPlayer_ },
				m_OldFlags{ oldFlags_ }
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
		constexpr static const size_t countPlayerBits{ playerType::countUnsignedBits };
		constexpr static const size_t countFileBits{ fileType::countUnsignedBits };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename doublepushmove::movedataType) << ":" << doublepushmove::countBits << "@doublepush";
			return sstr.str();
		}
	private:
		constexpr static fileType extractFile(const typename doublepushmove::movebitsType& movebits) noexcept
		{
			const fileType f{ fileType(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(movebits.template extractBits<countPlayerBits, countFileBits>())) };
			return f;
		}
		constexpr static void encodeFile(typename doublepushmove::movebitsType& movebits, const fileType f) noexcept
		{
			movebits.template storeBits<countPlayerBits, countFileBits>(static_cast<typename std::make_unsigned<typename fileType::baseType>::type>(f));
		}
		constexpr static playerType extractPlayer(const typename doublepushmove::movebitsType& movebits) noexcept
		{
			const playerType p{ playerType(static_cast<typename std::make_unsigned<typename playerType::baseType>::type>(movebits.template extractBits<0,countPlayerBits>())) };
			return p;
		}
		constexpr static void encodePlayer(typename doublepushmove::movebitsType& movebits, const playerType p) noexcept
		{
			movebits.template storeBits<0, countPlayerBits>(static_cast<typename std::make_unsigned<typename playerType::baseType>::type>(p));
		}
	public:
		constexpr doublepushmove() noexcept = default;
		~doublepushmove() noexcept = default;
		constexpr doublepushmove(doublepushmove&&) noexcept = default;
		constexpr doublepushmove(const doublepushmove&) noexcept = default;
		constexpr doublepushmove& operator=(doublepushmove&&) noexcept = default;
		constexpr doublepushmove& operator=(const doublepushmove&) noexcept = default;
		constexpr typename doublepushmove::movedataType doMove_Implementation(boardType& position, const typename doublepushmove::movebitsType& moveBits) const noexcept
		{
			const playerType p{ doublepushmove::extractPlayer(moveBits) };
			const fileType f{ doublepushmove::extractFile(moveBits) };
			const uint_t<countFiles, false> oldFlags{ position.extractFlagRange<4, 11>() };
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
				return typename doublepushmove::movedataType(p, from, to, oldFlags);
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
				return typename doublepushmove::movedataType(p, from, to, oldFlags);
			}
		}
		constexpr void undoMove_Implementation(boardType& position, const typename doublepushmove::movedataType& data) const noexcept
		{
			position.setMovingPlayer(--position.movingPlayer());
			position.removePiece(pawn, data.to(), data.movingPlayer());
			position.addPiece(pawn, data.from(), data.movingPlayer());
			position.storeFlagRange<4, 11>(data.oldFlags());
		}
		constexpr typename doublepushmove::movebitsType create(const playerType movingPlayer, const fileType file) const noexcept
		{
			typename doublepushmove::movebitsType bits{ doublepushmove::movebitsType::zero() };
			doublepushmove::encodePlayer(bits, movingPlayer);
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
									moveBits = create(movingPlayer, from.file());
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
									moveBits = create(movingPlayer, from.file());
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
		std::string toString_Implementation(const boardType& position, const typename doublepushmove::movebitsType& moveBits) const noexcept
		{
			const playerType p{ doublepushmove::extractPlayer(moveBits) };
			const fileType f{ doublepushmove::extractFile(moveBits) };
			if (p == whitePlayer)
			{
				const rankType r1{ rank2 };
				const rankType r2{ rank4 };
				const squareType from{ f & r1 };
				const squareType to{ f & r2 };
				return boardType::squareToString(from) + boardType::squareToString(to);
			}
			else
			{
				const rankType r1{ rank7 };
				const rankType r2{ rank5 };
				const squareType from{ f & r1 };
				const squareType to{ f & r2 };
				return boardType::squareToString(from) + boardType::squareToString(to);
			}
		}
	};

}