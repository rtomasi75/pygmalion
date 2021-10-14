namespace pygmalion::chess
{
	namespace detail
	{
		class kingsidecastleMovedata
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			uint_t<countFlags, false> m_OldFlags;
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
			PYGMALION_INLINE kingsidecastleMovedata(const uint_t<countFlags, false> oldFlags_, const std::uint16_t reversiblePlies_) noexcept :
				m_OldFlags{ oldFlags_ },
				m_ReversiblePlies{ reversiblePlies_ }
			{}
			PYGMALION_INLINE kingsidecastleMovedata() noexcept = default;
			PYGMALION_INLINE kingsidecastleMovedata(kingsidecastleMovedata&&) noexcept = default;
			PYGMALION_INLINE kingsidecastleMovedata(const kingsidecastleMovedata&) noexcept = default;
			PYGMALION_INLINE kingsidecastleMovedata& operator=(kingsidecastleMovedata&&) noexcept = default;
			PYGMALION_INLINE kingsidecastleMovedata& operator=(const kingsidecastleMovedata&) noexcept = default;
			PYGMALION_INLINE ~kingsidecastleMovedata() noexcept = default;
		};
	}

	class kingsidecastlemove :
		public pygmalion::mechanics::move<board, 0, detail::kingsidecastleMovedata, kingsidecastlemove>,
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
			sstr << "" << sizeof(typename kingsidecastlemove::movedataType) << ":" << kingsidecastlemove::countBits << "@kingsidecastle";
			return sstr.str();
		}
		constexpr kingsidecastlemove() noexcept = default;
		~kingsidecastlemove() noexcept = default;
		constexpr kingsidecastlemove(kingsidecastlemove&&) noexcept = default;
		constexpr kingsidecastlemove(const kingsidecastlemove&) noexcept = default;
		constexpr kingsidecastlemove& operator=(kingsidecastlemove&&) noexcept = default;
		constexpr kingsidecastlemove& operator=(const kingsidecastlemove&) noexcept = default;
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename kingsidecastlemove::movebitsType moveBits, typename kingsidecastlemove::movedataType& movedata) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const uint_t<countFlags, false> oldFlags{ position.extractFlagRange<0, 11>() };
			position.clearEnPassantFiles();
			position.setMovingPlayer(++position.movingPlayer());
			const std::uint16_t reversiblePlies{ position.cumulation().reversiblePlies() };
			if (p == whitePlayer)
			{
				position.clearCastleRightsWhite();
				constexpr const squareType kingFrom{ squareE1 };
				constexpr const squareType kingTo{ squareG1 };
				constexpr const squareType rookFrom{ squareH1 };
				constexpr const squareType rookTo{ squareF1 };
				position.removePiece(king, kingFrom, whitePlayer);
				position.removePiece(rook, rookFrom, whitePlayer);
				position.addPiece(king, kingTo, whitePlayer);
				position.addPiece(rook, rookTo, whitePlayer);
				position.cumulation().reversiblePlies()++;
				movedata = typename kingsidecastlemove::movedataType(oldFlags, reversiblePlies);
			}
			else
			{
				position.clearCastleRightsBlack();
				constexpr const squareType kingFrom{ squareE8 };
				constexpr const squareType kingTo{ squareG8 };
				constexpr const squareType rookFrom{ squareH8 };
				constexpr const squareType rookTo{ squareF8 };
				position.removePiece(king, kingFrom, blackPlayer);
				position.removePiece(rook, rookFrom, blackPlayer);
				position.addPiece(king, kingTo, blackPlayer);
				position.addPiece(rook, rookTo, blackPlayer);
				position.cumulation().reversiblePlies()++;
				movedata = typename kingsidecastlemove::movedataType(oldFlags, reversiblePlies);
			}
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename kingsidecastlemove::movedataType& data) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.storeFlagRange<0, 11>(data.oldFlags());
			if (p == whitePlayer)
			{
				constexpr const squareType kingFrom{ squareE1 };
				constexpr const squareType kingTo{ squareG1 };
				constexpr const squareType rookFrom{ squareH1 };
				constexpr const squareType rookTo{ squareF1 };
				position.addPiece(king, kingFrom, whitePlayer);
				position.addPiece(rook, rookFrom, whitePlayer);
				position.removePiece(king, kingTo, whitePlayer);
				position.removePiece(rook, rookTo, whitePlayer);
			}
			else
			{
				constexpr const squareType kingFrom{ squareE8 };
				constexpr const squareType kingTo{ squareG8 };
				constexpr const squareType rookFrom{ squareH8 };
				constexpr const squareType rookTo{ squareF8 };
				position.addPiece(king, kingFrom, blackPlayer);
				position.addPiece(rook, rookFrom, blackPlayer);
				position.removePiece(king, kingTo, blackPlayer);
				position.removePiece(rook, rookTo, blackPlayer);
			}
			position.cumulation().reversiblePlies() = data.reversiblePlies();
		}
		PYGMALION_INLINE typename kingsidecastlemove::movebitsType create() const noexcept
		{
			constexpr const typename kingsidecastlemove::movebitsType bits{ kingsidecastlemove::movebitsType::zero() };
			return bits;
		}
		PYGMALION_INLINE bool parse_Implementation(const boardType& position, std::string& text, typename kingsidecastlemove::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			playerType movingPlayer{ position.movingPlayer() };
			squareType from;
			squareType to;
			if (movingPlayer == whitePlayer)
			{
				if (boardType::parseSquare(temp, from))
				{
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::king))[from] && (from == squareE1))
					{
						if (boardType::parseSquare(temp, to))
						{
							if (!position.totalOccupancy()[to])
							{
								if (to == squareG1)
								{
									if (!position.totalOccupancy()[squareF1])
									{
										moveBits = create();
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
				if (boardType::parseSquare(temp, from))
				{
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::king))[from] && (from == squareE8))
					{
						if (boardType::parseSquare(temp, to))
						{
							if (!position.totalOccupancy()[to])
							{
								if (to == squareG8)
								{
									if (!position.totalOccupancy()[squareF8])
									{
										moveBits = create();
										text = temp;
										return true;
									}
								}
							}
						}
					}
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename kingsidecastlemove::movebitsType moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			if (p == whitePlayer)
			{
				constexpr const squareType kingFrom{ squareE1 };
				constexpr const squareType kingTo{ squareG1 };
				return boardType::squareToString(kingFrom) + boardType::squareToString(kingTo);
			}
			else
			{
				constexpr const squareType kingFrom{ squareE8 };
				constexpr const squareType kingTo{ squareG8 };
				return boardType::squareToString(kingFrom) + boardType::squareToString(kingTo);
			}
		}
		PYGMALION_INLINE squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			return none;
		}
		PYGMALION_INLINE squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			if (position.movingPlayer() == whitePlayer)
				return squaresType(squareE1) ^ squaresType(squareG1) ^ squaresType(squareH1) ^ squaresType(squareF1);
			else
				return squaresType(squareE8) ^ squaresType(squareG8) ^ squaresType(squareH8) ^ squaresType(squareF8);
		}
		PYGMALION_INLINE squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType piece, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			switch (piece)
			{
			default:
				return none;
			case king:
				if (position.movingPlayer() == whitePlayer)
					return squaresType(squareE1) ^ squaresType(squareG1);
				else
					return squaresType(squareE8) ^ squaresType(squareG8);
			case rook:
				if (position.movingPlayer() == whitePlayer)
					return squaresType(squareH1) ^ squaresType(squareF1);
				else
					return squaresType(squareH8) ^ squaresType(squareF8);
			}
		}
		PYGMALION_INLINE squareType fromSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			if (position.movingPlayer() == whitePlayer)
				return squareE1;
			else
				return squareE8;
		}
		PYGMALION_INLINE squareType toSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			if (position.movingPlayer() == whitePlayer)
				return squareG1;
			else
				return squareG8;
		}
	};

}