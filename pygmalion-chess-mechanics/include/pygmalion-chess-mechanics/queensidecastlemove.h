namespace pygmalion::chess
{
	namespace detail
	{
		class queensidecastleMovedata :
			public pygmalion::mechanics::movedataBase<board>
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			flagsType m_OldFlags;
			squareType m_OldEnPassantSquare;
			constexpr static const flagsType noFlags{ flagsType::none() };
		public:
			PYGMALION_INLINE const flagsType& oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			PYGMALION_INLINE const squareType& oldEnPassantSquare() const noexcept
			{
				return m_OldEnPassantSquare;
			}
			PYGMALION_INLINE queensidecastleMovedata(const flagsType oldFlags_, const squareType oldEnPassantSquare_) noexcept :
				m_OldFlags{ oldFlags_ },
				m_OldEnPassantSquare{ oldEnPassantSquare_ }
			{}
			PYGMALION_INLINE queensidecastleMovedata() noexcept :
				m_OldFlags{ noFlags }
			{}
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
			const flagsType oldFlags{ position.flags() };
			const squareType oldEnPassantSquare{ position.enPassantSquare() };
			position.clearEnPassantSquare();
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
				movedata = typename queensidecastlemove::movedataType(oldFlags, oldEnPassantSquare);
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
				movedata = typename queensidecastlemove::movedataType(oldFlags, oldEnPassantSquare);
			}
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename queensidecastlemove::movedataType& data, const materialTableType& materialTable) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.checkFlags(data.oldFlags());
			position.setEnPassantSquare(data.oldEnPassantSquare());
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
			playerType movingPlayer{ position.movingPlayer() };
			squareType from;
			squareType to;
			size_t cnt{ 0 };
			if (movingPlayer == whitePlayer)
			{
				if (squareType::parse(text, cnt, from))
				{
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::king))[from] && (from == squareE1))
					{
						if (squareType::parse(text, cnt, to))
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
				if (squareType::parse(text, cnt, from))
				{
					if ((position.playerOccupancy(movingPlayer) & position.pieceOccupancy(descriptorState::king))[from] && (from == squareE8))
					{
						if (squareType::parse(text, cnt, to))
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
				return kingFrom.toShortString() + kingTo.toShortString();
			}
			else
			{
				constexpr const squareType kingFrom{ squareE8 };
				constexpr const squareType kingTo{ squareC8 };
				return kingFrom.toShortString() + kingTo.toShortString();
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