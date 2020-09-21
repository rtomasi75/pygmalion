namespace pygmalion::chess
{
	namespace detail
	{
		class promotionMovedata
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			uint_t<countFiles, false> m_OldFlags;
			squareType m_From;
			squareType m_To;
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
			constexpr promotionMovedata(const squareType fromSquare, const squareType toSquare, const uint_t<countFiles, false>& oldFlags_) noexcept :
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OldFlags{ oldFlags_ }
			{}
			constexpr promotionMovedata() noexcept = default;
			constexpr promotionMovedata(promotionMovedata&&) noexcept = default;
			constexpr promotionMovedata(const promotionMovedata&) noexcept = default;
			constexpr promotionMovedata& operator=(promotionMovedata&&) noexcept = default;
			constexpr promotionMovedata& operator=(const promotionMovedata&) noexcept = default;
			~promotionMovedata() noexcept = default;
		};
	}

	class promotionmove :
		public pygmalion::mechanics::move<board, 2 * board::squareType::countUnsignedBits, detail::promotionMovedata, promotionmove>,
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
			sstr << "" << sizeof(typename promotionmove::movedataType) << ":" << promotionmove::countBits << "@promotion" << boardType::pieceToString(m_PromotedPiece, whitePlayer);
			return sstr.str();
		}
	private:
		constexpr static squareType extractTo(const typename promotionmove::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		constexpr static squareType extractFrom(const typename promotionmove::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		constexpr static void encodeTo(typename promotionmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		constexpr static void encodeFrom(typename promotionmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	protected:
		constexpr promotionmove(const pieceType promotedPiece) noexcept :
			m_PromotedPiece{ promotedPiece }
		{

		}
		~promotionmove() noexcept = default;
		constexpr promotionmove(promotionmove&&) noexcept = default;
		constexpr promotionmove(const promotionmove&) noexcept = default;
		constexpr promotionmove& operator=(promotionmove&&) noexcept = default;
		constexpr promotionmove& operator=(const promotionmove&) noexcept = default;
	public:
		constexpr typename promotionmove::movedataType doMove_Implementation(boardType& position, const typename promotionmove::movebitsType& moveBits) const noexcept
		{
			const squareType from{ promotionmove::extractFrom(moveBits) };
			const squareType to{ promotionmove::extractTo(moveBits) };
			const playerType p{ position.movingPlayer() };
			const uint_t<countFiles, false> oldFlags{ position.extractFlagRange<4, 11>() };
			position.clearEnPassantFiles();
			position.removePiece(pawn, from, p);
			position.addPiece(m_PromotedPiece, to, p);
			position.setMovingPlayer(++position.movingPlayer());
			return typename promotionmove::movedataType(from, to, oldFlags);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename promotionmove::movedataType& data) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.removePiece(m_PromotedPiece, data.to(), p);
			position.addPiece(pawn, data.from(), p);
			position.storeFlagRange<4, 11>(data.oldFlags());
		}
		constexpr typename promotionmove::movebitsType create(const squareType from, const squareType to) const noexcept
		{
			typename promotionmove::movebitsType bits{ promotionmove::movebitsType::zero() };
			promotionmove::encodeFrom(bits, from);
			promotionmove::encodeTo(bits, to);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename promotionmove::movebitsType& moveBits) const noexcept
		{
			const playerType p{ position.movingPlayer() };
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
									if (!position.totalOccupancy()[to])
									{
										playerType p2;
										pieceType pc;
										if (boardType::parsePiece(temp, pc, p2))
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
									if (!position.totalOccupancy()[to])
									{
										playerType p2;
										pieceType pc;
										if (boardType::parsePiece(temp, pc, p2))
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
		std::string toString_Implementation(const boardType& position, const typename promotionmove::movebitsType& moveBits) const noexcept
		{
			const squareType from{ promotionmove::extractFrom(moveBits) };
			const squareType to{ promotionmove::extractTo(moveBits) };
			return boardType::squareToString(from) + boardType::squareToString(to) + boardType::pieceToString(m_PromotedPiece, whitePlayer);
		}
	};
}