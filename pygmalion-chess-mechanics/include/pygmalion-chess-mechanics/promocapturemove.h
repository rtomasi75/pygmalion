namespace pygmalion::chess
{
	namespace detail
	{
		class promocaptureMovedata
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			squareType m_From;
			squareType m_To;
			uint_t<countFlags, false> m_OldFlags;
			pieceType m_CapturedPiece;
		public:
			constexpr const uint_t<countFlags, false>& oldFlags() const noexcept
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
			constexpr pieceType capturedPiece() const noexcept
			{
				return m_CapturedPiece;
			}
			constexpr promocaptureMovedata(const squareType fromSquare, const squareType toSquare, const uint_t<countFlags, false>& oldFlags_, const pieceType capturedPiece_) noexcept :
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OldFlags{ oldFlags_ },
				m_CapturedPiece{ capturedPiece_ }
			{}
			constexpr promocaptureMovedata() noexcept = default;
			constexpr promocaptureMovedata(promocaptureMovedata&&) noexcept = default;
			constexpr promocaptureMovedata(const promocaptureMovedata&) noexcept = default;
			constexpr promocaptureMovedata& operator=(promocaptureMovedata&&) noexcept = default;
			constexpr promocaptureMovedata& operator=(const promocaptureMovedata&) noexcept = default;
			~promocaptureMovedata() noexcept = default;
		};
	}

	class promocapturemove :
		public pygmalion::mechanics::move<board, 2 * board::squareType::countUnsignedBits, detail::promocaptureMovedata, promocapturemove>,
		public board::descriptorState
	{
	public:
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countFromBits{ squareType::countUnsignedBits };
		constexpr static const size_t countToBits{ squareType::countUnsignedBits };
	private:
		pieceType m_PromotedPiece;
	public:
		std::string name_Implementation() const noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename promocapturemove::movedataType) << ":" << promocapturemove::countBits << "@promocapture" << boardType::pieceToString(m_PromotedPiece, whitePlayer);
			return sstr.str();
		}
	private:
		constexpr static squareType extractTo(const typename promocapturemove::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		constexpr static squareType extractFrom(const typename promocapturemove::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		constexpr static void encodeTo(typename promocapturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		constexpr static void encodeFrom(typename promocapturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	protected:
		constexpr promocapturemove(const pieceType promotedPiece) noexcept :
			m_PromotedPiece{ promotedPiece }
		{

		}
		~promocapturemove() noexcept = default;
		constexpr promocapturemove(promocapturemove&&) noexcept = default;
		constexpr promocapturemove(const promocapturemove&) noexcept = default;
		constexpr promocapturemove& operator=(promocapturemove&&) noexcept = default;
		constexpr promocapturemove& operator=(const promocapturemove&) noexcept = default;
	public:
		constexpr typename promocapturemove::movedataType doMove_Implementation(boardType& position, const typename promocapturemove::movebitsType& moveBits) const noexcept
		{
			const squareType from{ promocapturemove::extractFrom(moveBits) };
			const squareType to{ promocapturemove::extractTo(moveBits) };
			const playerType p{ position.movingPlayer() };
			const pieceType pc2{ position.getPiece(to) };
			const playerType p2{ ++position.movingPlayer() };
			const uint_t<countFlags, false> oldFlags{ position.extractFlagRange<0, 11>() };
			position.clearEnPassantFiles();
			position.removePiece(pawn, from, p);
			position.removePiece(pc2, to, p2);
			position.addPiece(m_PromotedPiece, to, p);
			position.setMovingPlayer(p2);
			if (p == whitePlayer)
			{
				if (pc2 == rook)
				{
					switch (to)
					{
					case squareA8:
						position.clearCastleRightQueensideBlack();
						break;
					case squareH8:
						position.clearCastleRightKingsideBlack();
						break;
					}
				}
			}
			else
			{
				if (pc2 == rook)
				{
					switch (to)
					{
					case squareA1:
						position.clearCastleRightQueensideWhite();
						break;
					case squareH1:
						position.clearCastleRightKingsideWhite();
						break;
					}
				}
			}
			return typename promocapturemove::movedataType(from, to, oldFlags, pc2);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename promocapturemove::movedataType& data) const noexcept
		{
			const playerType p2{ position.movingPlayer() };
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.removePiece(m_PromotedPiece, data.to(), p);
			position.addPiece(pawn, data.from(), p);
			position.addPiece(data.capturedPiece(), data.to(), p2);
			position.storeFlagRange<0, 11>(data.oldFlags());
		}
		constexpr typename promocapturemove::movebitsType create(const squareType from, const squareType to) const noexcept
		{
			typename promocapturemove::movebitsType bits{ promocapturemove::movebitsType::zero() };
			promocapturemove::encodeFrom(bits, from);
			promocapturemove::encodeTo(bits, to);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename promocapturemove::movebitsType& moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
			const playerType p2{ ++position.movingPlayer() };
			std::string temp{ text };
			squareType from;
			squareType to;
			if (boardType::parseSquare(temp, from))
			{
				if ((position.pieceOccupancy(pawn) & position.playerOccupancy(p))[from])
				{
					if (p == whitePlayer)
					{
						if (from.rank() == rank7)
						{
							if (boardType::parseSquare(temp, to))
							{
								if (to.rank() == rank8)
								{
									if ((position.pieceOccupancy(pawn) & position.playerOccupancy(p2))[to])
									{
										playerType p3;
										pieceType pc;
										if (boardType::parsePiece(temp, pc, p3))
										{
											if (pc == m_PromotedPiece)
											{
												moveBits = create(from, to);
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
						if (from.rank() == rank2)
						{
							if (boardType::parseSquare(temp, to))
							{
								if (to.rank() == rank1)
								{
									if (position.playerOccupancy(p2)[to])
									{
										playerType p3;
										pieceType pc;
										if (boardType::parsePiece(temp, pc, p3))
										{
											if (pc == m_PromotedPiece)
											{
												moveBits = create(from, to);
												text = temp;
												return true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename promocapturemove::movebitsType& moveBits) const noexcept
		{
			const squareType from{ promocapturemove::extractFrom(moveBits) };
			const squareType to{ promocapturemove::extractTo(moveBits) };
			return boardType::squareToString(from) + boardType::squareToString(to) + boardType::pieceToString(m_PromotedPiece, position.movingPlayer());
		}
		constexpr squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return squaresType(promocapturemove::extractTo(moveBits));
		}
		constexpr squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return squaresType(promocapturemove::extractFrom(moveBits)) ^ squaresType(promocapturemove::extractTo(moveBits));
		}
		constexpr squareType fromSquare_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return promocapturemove::extractFrom(moveBits);
		}
		constexpr squareType toSquare_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return promocapturemove::extractTo(moveBits);
		}
	};
}