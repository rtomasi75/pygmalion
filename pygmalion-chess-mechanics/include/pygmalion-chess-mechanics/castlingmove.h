namespace pygmalion::chess
{
	namespace detail
	{
		class castlingMovedata
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			uint_t<countFlags, false> m_OldFlags;
			bool m_IsKingside;
		public:
			constexpr bool isKingside() const noexcept
			{
				return m_IsKingside;
			}
			constexpr const uint_t<countFlags, false>& oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			constexpr castlingMovedata(const bool isKingside_, const uint_t<countFlags, false>& oldFlags_) noexcept :
				m_IsKingside{ isKingside_ },
				m_OldFlags{ oldFlags_ }
			{}
			constexpr castlingMovedata() noexcept :
				m_IsKingside{ false }
			{}
			constexpr castlingMovedata(castlingMovedata&&) noexcept = default;
			constexpr castlingMovedata(const castlingMovedata&) noexcept = default;
			constexpr castlingMovedata& operator=(castlingMovedata&&) noexcept = default;
			constexpr castlingMovedata& operator=(const castlingMovedata&) noexcept = default;
			~castlingMovedata() noexcept = default;
		};
	}

	class castlingmove :
		public pygmalion::mechanics::move<board, 1, detail::castlingMovedata, castlingmove>,
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
			sstr << "" << sizeof(typename castlingmove::movedataType) << ":" << castlingmove::countBits << "@castling";
			return sstr.str();
		}
	private:
		constexpr static bool extractSide(const typename castlingmove::movebitsType& movebits) noexcept
		{
			const bool f{ movebits.template extractBits<0, 1>() };
			return f;
		}
		constexpr static void encodeSide(typename castlingmove::movebitsType& movebits, const bool isKingside) noexcept
		{
			movebits.template storeBits<0, 1>(static_cast<uint_t<countFlags, false>>(static_cast<unsigned char>(isKingside)));
		}
	public:
		constexpr castlingmove() noexcept = default;
		~castlingmove() noexcept = default;
		constexpr castlingmove(castlingmove&&) noexcept = default;
		constexpr castlingmove(const castlingmove&) noexcept = default;
		constexpr castlingmove& operator=(castlingmove&&) noexcept = default;
		constexpr castlingmove& operator=(const castlingmove&) noexcept = default;
		constexpr typename castlingmove::movedataType doMove_Implementation(boardType& position, const typename castlingmove::movebitsType& moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const bool side{ castlingmove::extractSide(moveBits) };
			const uint_t<countFlags, false> oldFlags{ position.extractFlagRange<0, 11>() };
			position.clearEnPassantFiles();
			position.setMovingPlayer(++position.movingPlayer());
			if (p == whitePlayer)
			{
				position.clearCastleRightsWhite();
				if (side)
				{
					constexpr const squareType kingFrom{ squareE1 };
					constexpr const squareType kingTo{ squareG1 };
					constexpr const squareType rookFrom{ squareH1 };
					constexpr const squareType rookTo{ squareF1 };
					position.removePiece(king, kingFrom, whitePlayer);
					position.removePiece(rook, rookFrom, whitePlayer);
					position.addPiece(king, kingTo, whitePlayer);
					position.addPiece(rook, rookTo, whitePlayer);
					return typename castlingmove::movedataType(true, oldFlags);
				}
				else
				{
					constexpr const squareType kingFrom{ squareE1 };
					constexpr const squareType kingTo{ squareC1 };
					constexpr const squareType rookFrom{ squareA1 };
					constexpr const squareType rookTo{ squareD1 };
					position.removePiece(king, kingFrom, whitePlayer);
					position.removePiece(rook, rookFrom, whitePlayer);
					position.addPiece(king, kingTo, whitePlayer);
					position.addPiece(rook, rookTo, whitePlayer);
					return typename castlingmove::movedataType(false, oldFlags);
				}
			}
			else
			{
				position.clearCastleRightsBlack();
				if (side)
				{
					constexpr const squareType kingFrom{ squareE8 };
					constexpr const squareType kingTo{ squareG8 };
					constexpr const squareType rookFrom{ squareH8 };
					constexpr const squareType rookTo{ squareF8 };
					position.removePiece(king, kingFrom, blackPlayer);
					position.removePiece(rook, rookFrom, blackPlayer);
					position.addPiece(king, kingTo, blackPlayer);
					position.addPiece(rook, rookTo, blackPlayer);
					return typename castlingmove::movedataType(true, oldFlags);
				}
				else
				{
					constexpr const squareType kingFrom{ squareE8 };
					constexpr const squareType kingTo{ squareC8 };
					constexpr const squareType rookFrom{ squareA8 };
					constexpr const squareType rookTo{ squareD8 };
					position.removePiece(king, kingFrom, blackPlayer);
					position.removePiece(rook, rookFrom, blackPlayer);
					position.addPiece(king, kingTo, blackPlayer);
					position.addPiece(rook, rookTo, blackPlayer);
					return typename castlingmove::movedataType(false, oldFlags);
				}
			}
		}
		constexpr void undoMove_Implementation(boardType& position, const typename castlingmove::movedataType& data) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.storeFlagRange<0, 11>(data.oldFlags());
			if (p == whitePlayer)
			{
				if (data.isKingside())
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
					constexpr const squareType kingFrom{ squareE1 };
					constexpr const squareType kingTo{ squareC1 };
					constexpr const squareType rookFrom{ squareA1 };
					constexpr const squareType rookTo{ squareD1 };
					position.addPiece(king, kingFrom, whitePlayer);
					position.addPiece(rook, rookFrom, whitePlayer);
					position.removePiece(king, kingTo, whitePlayer);
					position.removePiece(rook, rookTo, whitePlayer);
				}
			}
			else
			{
				if (data.isKingside())
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
			}
		}
		constexpr typename castlingmove::movebitsType create(const bool isKingside) const noexcept
		{
			typename castlingmove::movebitsType bits{ castlingmove::movebitsType::zero() };
			castlingmove::encodeSide(bits, isKingside);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename castlingmove::movebitsType& moveBits) const noexcept
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
										moveBits = create(true);
										text = temp;
										return true;
									}
								}
								else if (to == squareC1)
								{
									if (!position.totalOccupancy()[squareD1])
									{
										moveBits = create(false);
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
										moveBits = create(true);
										text = temp;
										return true;
									}
								}
								else if (to == squareC8)
								{
									if (!position.totalOccupancy()[squareD8])
									{
										moveBits = create(false);
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
		std::string toString_Implementation(const boardType& position, const typename castlingmove::movebitsType& moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const bool side{ castlingmove::extractSide(moveBits) };
			if (p == whitePlayer)
			{
				if (side)
				{
					constexpr const squareType kingFrom{ squareE1 };
					constexpr const squareType kingTo{ squareG1 };
					return boardType::squareToString(kingFrom)+ boardType::squareToString(kingTo);
				}
				else
				{
					constexpr const squareType kingFrom{ squareE1 };
					constexpr const squareType kingTo{ squareC1 };
					return boardType::squareToString(kingFrom) + boardType::squareToString(kingTo);
				}
			}
			else
			{
				if (side)
				{
					constexpr const squareType kingFrom{ squareE8 };
					constexpr const squareType kingTo{ squareG8 };
					return boardType::squareToString(kingFrom) + boardType::squareToString(kingTo);
				}
				else
				{
					constexpr const squareType kingFrom{ squareE8 };
					constexpr const squareType kingTo{ squareC8 };
					return boardType::squareToString(kingFrom) + boardType::squareToString(kingTo);
				}
			}
		}
	};

}