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
		public:
			PYGMALION_INLINE const uint_t<countFlags, false> oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			PYGMALION_INLINE queensidecastleMovedata(const uint_t<countFlags, false> oldFlags_) noexcept :
				m_OldFlags{ oldFlags_ }
			{}
			PYGMALION_INLINE queensidecastleMovedata() noexcept = default;
			PYGMALION_INLINE queensidecastleMovedata(queensidecastleMovedata&&) noexcept = default;
			PYGMALION_INLINE queensidecastleMovedata(const queensidecastleMovedata&) noexcept = default;
			PYGMALION_INLINE queensidecastleMovedata& operator=(queensidecastleMovedata&&) noexcept = default;
			PYGMALION_INLINE queensidecastleMovedata& operator=(const queensidecastleMovedata&) noexcept = default;
			PYGMALION_INLINE ~queensidecastleMovedata() noexcept = default;
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
		constexpr queensidecastlemove& operator=(queensidecastlemove&&) noexcept
		{
			return *this;
		}
		constexpr queensidecastlemove& operator=(const queensidecastlemove&) noexcept
		{
			return *this;
		}
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename queensidecastlemove::movebitsType moveBits, typename queensidecastlemove::movedataType& movedata, const materialTableType& materialTable) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const uint_t<countFlags, false> oldFlags{ position.extractFlagRange<0, 11>() };
			position.clearEnPassantFiles();
			position.setMovingPlayer(++position.movingPlayer());
			if (p == whitePlayer)
			{
				position.clearCastleRightsWhite();
				constexpr const squareType kingFrom{ squareE1 };
				constexpr const squareType kingTo{ squareC1 };
				constexpr const squareType rookFrom{ squareA1 };
				constexpr const squareType rookTo{ squareD1 };
				position.movePiece(king, kingFrom, kingTo, whitePlayer, materialTable);
				position.movePiece(rook, rookFrom, rookTo, whitePlayer, materialTable);
				position.doReversiblePly();
				movedata = typename queensidecastlemove::movedataType(oldFlags);
			}
			else
			{
				position.clearCastleRightsBlack();
				constexpr const squareType kingFrom{ squareE8 };
				constexpr const squareType kingTo{ squareC8 };
				constexpr const squareType rookFrom{ squareA8 };
				constexpr const squareType rookTo{ squareD8 };
				position.movePiece(king, kingFrom, kingTo, blackPlayer, materialTable);
				position.movePiece(rook, rookFrom, rookTo, blackPlayer, materialTable);
				position.doReversiblePly();
				movedata = typename queensidecastlemove::movedataType(oldFlags);
			}
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename queensidecastlemove::movedataType& data, const materialTableType& materialTable) const noexcept
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
				position.movePiece(king, kingTo, kingFrom, whitePlayer, materialTable);
				position.movePiece(rook, rookTo, rookFrom, whitePlayer, materialTable);
			}
			else
			{
				constexpr const squareType kingFrom{ squareE8 };
				constexpr const squareType kingTo{ squareC8 };
				constexpr const squareType rookFrom{ squareA8 };
				constexpr const squareType rookTo{ squareD8 };
				position.movePiece(king, kingTo, kingFrom, blackPlayer, materialTable);
				position.movePiece(rook, rookTo, rookFrom, blackPlayer, materialTable);
			}
			position.undoReversiblePly();
		}
		PYGMALION_INLINE constexpr typename queensidecastlemove::movebitsType create() const noexcept
		{
			constexpr const typename queensidecastlemove::movebitsType bits{ queensidecastlemove::movebitsType::zero() };
			return bits;
		}
		bool parse_Implementation(const boardType& position, const std::string& text, typename queensidecastlemove::movebitsType& moveBits, size_t& count) const noexcept
		{
			std::string temp{ text };
			playerType movingPlayer{ position.movingPlayer() };
			squareType from;
			squareType to;
			size_t cnt{ 0 };
			if (movingPlayer == whitePlayer)
			{
				if (boardType::parseSquare(temp, from, cnt))
				{
					std::string temp2{ temp.substr(cnt,temp.length() - cnt) };
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::king))[from] && (from == squareE1))
					{
						if (boardType::parseSquare(temp2, to, cnt))
						{
							if (!position.totalOccupancy()[to])
							{
								if (to == squareC1)
								{
									if (!position.totalOccupancy()[squareD1])
									{
										moveBits = create();
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
				if (boardType::parseSquare(temp, from, cnt))
				{
					std::string temp2{ temp.substr(cnt,temp.length() - cnt) };
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::king))[from] && (from == squareE8))
					{
						if (boardType::parseSquare(temp2, to, cnt))
						{
							if (!position.totalOccupancy()[to])
							{
								if (to == squareC8)
								{
									if (!position.totalOccupancy()[squareD8])
									{
										moveBits = create();
										count += cnt;
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
		std::string toString_Implementation(const boardType& position, const typename queensidecastlemove::movebitsType moveBits) const noexcept
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
		PYGMALION_INLINE squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			return none;
		}
		PYGMALION_INLINE squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			if (position.movingPlayer() == whitePlayer)
				return squaresType(squareE1) ^ squaresType(squareC1) ^ squaresType(squareA1) ^ squaresType(squareD1);
			else
				return squaresType(squareE8) ^ squaresType(squareC8) ^ squaresType(squareA8) ^ squaresType(squareD8);
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
					return squaresType(squareE1) ^ squaresType(squareC1);
				else
					return squaresType(squareE8) ^ squaresType(squareC8);
			case rook:
				if (position.movingPlayer() == whitePlayer)
					return squaresType(squareA1) ^ squaresType(squareD1);
				else
					return squaresType(squareA8) ^ squaresType(squareD8);
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
				return squareC1;
			else
				return squareC8;
		}
	};

}