namespace pygmalion::chess
{
	namespace detail
	{
		class queensidecastleMovedata
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			uint_t<countFlags, false> m_OldFlags;
			std::uint16_t m_ReversiblePlies{ 0 };
		public:
			constexpr std::uint16_t reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			constexpr const uint_t<countFlags, false>& oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			constexpr queensidecastleMovedata(const uint_t<countFlags, false>& oldFlags_, const std::uint16_t reversiblePlies_) noexcept :
				m_OldFlags{ oldFlags_ },
				m_ReversiblePlies{ reversiblePlies_ }
			{}
			constexpr queensidecastleMovedata() noexcept = default;
			constexpr queensidecastleMovedata(queensidecastleMovedata&&) noexcept = default;
			constexpr queensidecastleMovedata(const queensidecastleMovedata&) noexcept = default;
			constexpr queensidecastleMovedata& operator=(queensidecastleMovedata&&) noexcept = default;
			constexpr queensidecastleMovedata& operator=(const queensidecastleMovedata&) noexcept = default;
			~queensidecastleMovedata() noexcept = default;
		};
	}

	class queensidecastlemove :
		public pygmalion::mechanics::move<board, 0, detail::queensidecastleMovedata, queensidecastlemove>,
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
			sstr << "" << sizeof(typename queensidecastlemove::movedataType) << ":" << queensidecastlemove::countBits << "@queensidecastle";
			return sstr.str();
		}
		constexpr queensidecastlemove() noexcept = default;
		~queensidecastlemove() noexcept = default;
		constexpr queensidecastlemove(queensidecastlemove&&) noexcept = default;
		constexpr queensidecastlemove(const queensidecastlemove&) noexcept = default;
		constexpr queensidecastlemove& operator=(queensidecastlemove&&) noexcept = default;
		constexpr queensidecastlemove& operator=(const queensidecastlemove&) noexcept = default;
		constexpr typename queensidecastlemove::movedataType doMove_Implementation(boardType& position, const typename queensidecastlemove::movebitsType& moveBits) const noexcept
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
				constexpr const squareType kingTo{ squareC1 };
				constexpr const squareType rookFrom{ squareA1 };
				constexpr const squareType rookTo{ squareD1 };
				position.removePiece(king, kingFrom, whitePlayer);
				position.removePiece(rook, rookFrom, whitePlayer);
				position.addPiece(king, kingTo, whitePlayer);
				position.addPiece(rook, rookTo, whitePlayer);
				position.cumulation().reversiblePlies()++;
				return typename queensidecastlemove::movedataType(oldFlags, reversiblePlies);
			}
			else
			{
				position.clearCastleRightsBlack();
				constexpr const squareType kingFrom{ squareE8 };
				constexpr const squareType kingTo{ squareC8 };
				constexpr const squareType rookFrom{ squareA8 };
				constexpr const squareType rookTo{ squareD8 };
				position.removePiece(king, kingFrom, blackPlayer);
				position.removePiece(rook, rookFrom, blackPlayer);
				position.addPiece(king, kingTo, blackPlayer);
				position.addPiece(rook, rookTo, blackPlayer);
				position.cumulation().reversiblePlies()++;
				return typename queensidecastlemove::movedataType(oldFlags, reversiblePlies);
			}
		}
		constexpr void undoMove_Implementation(boardType& position, const typename queensidecastlemove::movedataType& data) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.storeFlagRange<0, 11>(data.oldFlags());
			if (p == whitePlayer)
			{
				constexpr const squareType kingFrom{ squareE1 };
				constexpr const squareType kingTo{ squareC1 };
				constexpr const squareType rookFrom{ squareA1 };
				constexpr const squareType rookTo{ squareD1 };
				position.addPiece(king, kingFrom, whitePlayer);
				position.addPiece(rook, rookFrom, whitePlayer);
				position.removePiece(king, kingTo, whitePlayer);
				position.removePiece(rook, rookTo, whitePlayer);
			}
			else
			{
				constexpr const squareType kingFrom{ squareE8 };
				constexpr const squareType kingTo{ squareC8 };
				constexpr const squareType rookFrom{ squareA8 };
				constexpr const squareType rookTo{ squareD8 };
				position.addPiece(king, kingFrom, blackPlayer);
				position.addPiece(rook, rookFrom, blackPlayer);
				position.removePiece(king, kingTo, blackPlayer);
				position.removePiece(rook, rookTo, blackPlayer);
			}
			position.cumulation().reversiblePlies() = data.reversiblePlies();
		}
		constexpr typename queensidecastlemove::movebitsType create() const noexcept
		{
			constexpr const typename queensidecastlemove::movebitsType bits{ queensidecastlemove::movebitsType::zero() };
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename queensidecastlemove::movebitsType& moveBits) const noexcept
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
								if (to == squareC1)
								{
									if (!position.totalOccupancy()[squareD1])
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
								if (to == squareC8)
								{
									if (!position.totalOccupancy()[squareD8])
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
		std::string toString_Implementation(const boardType& position, const typename queensidecastlemove::movebitsType& moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			if (p == whitePlayer)
			{
				constexpr const squareType kingFrom{ squareE1 };
				constexpr const squareType kingTo{ squareC1 };
				return boardType::squareToString(kingFrom) + boardType::squareToString(kingTo);
			}
			else
			{
				constexpr const squareType kingFrom{ squareE8 };
				constexpr const squareType kingTo{ squareC8 };
				return boardType::squareToString(kingFrom) + boardType::squareToString(kingTo);
			}
		}
		constexpr squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return squaresType::none();
		}
		constexpr squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			if (position.movingPlayer() == whitePlayer)
				return squaresType(squareE1) ^ squaresType(squareC1) ^ squaresType(squareA1) ^ squaresType(squareD1);
			else
				return squaresType(squareE8) ^ squaresType(squareC8) ^ squaresType(squareA8) ^ squaresType(squareD8);
		}
		constexpr squareType fromSquare_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			if (position.movingPlayer() == whitePlayer)
				return squareE1;
			else
				return squareE8;
		}
		constexpr squareType toSquare_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			if (position.movingPlayer() == whitePlayer)
				return squareC1;
			else
				return squareC8;
		}
};

}