namespace pygmalion::mechanics
{
	namespace detail
	{
		template<typename BOARD>
		class promotionMovedata
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			squareType m_From;
			squareType m_To;
			pieceType m_InitialPiece;
			pieceType m_PromotedPiece;
			playerType m_Player;
		public:
			PYGMALION_INLINE playerType player() const noexcept
			{
				return m_Player;
			}
			PYGMALION_INLINE pieceType initialPiece() const noexcept
			{
				return m_InitialPiece;
			}
			PYGMALION_INLINE pieceType promotedPiece() const noexcept
			{
				return m_PromotedPiece;
			}
			PYGMALION_INLINE squareType from() const noexcept
			{
				return m_From;
			}
			PYGMALION_INLINE squareType to() const noexcept
			{
				return m_To;
			}
			PYGMALION_INLINE promotionMovedata(const pieceType initialPiece_, const squareType fromSquare, const squareType toSquare, const playerType owner, const pieceType promotedPiece_) noexcept :
				m_InitialPiece{ initialPiece_ },
				m_PromotedPiece{ promotedPiece_ },
				m_From{ fromSquare },
				m_To{ toSquare },
				m_Player{ owner }
			{}
			PYGMALION_INLINE promotionMovedata() noexcept = default;
			PYGMALION_INLINE promotionMovedata(promotionMovedata&&) noexcept = default;
			PYGMALION_INLINE promotionMovedata(const promotionMovedata&) noexcept = default;
			PYGMALION_INLINE promotionMovedata& operator=(promotionMovedata&&) noexcept = default;
			PYGMALION_INLINE promotionMovedata& operator=(const promotionMovedata&) noexcept = default;
			PYGMALION_INLINE ~promotionMovedata() noexcept = default;
		};
	}

	template<typename BOARD>
	class promotionmove :
		public move<BOARD, 2 * BOARD::squareType::countUnsignedBits + BOARD::pieceType::countUnsignedBits + BOARD::playerType::countUnsignedBits, detail::promotionMovedata<BOARD>, promotionmove<BOARD>>
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countFromBits{ squareType::countUnsignedBits };
		constexpr static const size_t countToBits{ squareType::countUnsignedBits };
		constexpr static const size_t countPieceBits{ pieceType::countUnsignedBits };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename promotionmove::movedataType) << ":" << promotionmove::countBits << "@promotion";
			return sstr.str();
		}
	private:
		PYGMALION_INLINE static pieceType extractPiece(const typename promotionmove::movebitsType movebits) noexcept
		{
			const pieceType pc{ pieceType(static_cast<typename std::make_unsigned<typename pieceType::baseType>::type>(movebits.template extractBits<countFromBits + countToBits,countPieceBits>())) };
			return pc;
		}
		PYGMALION_INLINE static void encodePiece(typename promotionmove::movebitsType& movebits, const pieceType pc) noexcept
		{
			movebits.template storeBits<countFromBits + countToBits, countPieceBits>(static_cast<typename std::make_unsigned<typename pieceType::baseType>::type>(pc));
		}
		PYGMALION_INLINE static squareType extractTo(const typename promotionmove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		PYGMALION_INLINE static void encodeTo(typename promotionmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		PYGMALION_INLINE static squareType extractFrom(const typename promotionmove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		PYGMALION_INLINE static void encodeFrom(typename promotionmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		PYGMALION_INLINE constexpr promotionmove() noexcept = default;
		PYGMALION_INLINE ~promotionmove() noexcept = default;
		PYGMALION_INLINE constexpr promotionmove(promotionmove&&) noexcept = default;
		PYGMALION_INLINE constexpr promotionmove(const promotionmove&) noexcept = default;
		PYGMALION_INLINE constexpr promotionmove& operator=(promotionmove&&) noexcept = default;
		PYGMALION_INLINE constexpr promotionmove& operator=(const promotionmove&) noexcept = default;
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename promotionmove::movebitsType moveBits, typename promotionmove::movedataType& movedata) const noexcept
		{
			const squareType from{ promotionmove::extractFrom(moveBits) };
			const squareType to{ promotionmove::extractTo(moveBits) };
			const pieceType pc{ position.getPiece(from) };
			const pieceType pc2{ promotionmove::extractPiece(moveBits) };
			const playerType p{ position.getPlayer(from) };
			position.removePiece(pc, from, p);
			position.addPiece(pc2, to, p);
			movedata = typename promotionmove::movedataType(pc, from, to, p, pc2);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename promotionmove::movedataType& data) const noexcept
		{
			position.removePiece(data.promotedPiece(), data.to(), data.player());
			position.addPiece(data.initialPiece(), data.from(), data.player());
		}
		PYGMALION_INLINE typename promotionmove::movebitsType create(const squareType from, const squareType to, const pieceType pc) const noexcept
		{
			typename promotionmove::movebitsType bits{ promotionmove::movebitsType::zero() };
			promotionmove::encodeFrom(bits, from);
			promotionmove::encodeTo(bits, to);
			promotionmove::encodePiece(bits, pc);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename promotionmove::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			squareType from;
			squareType to;
			pieceType pc;
			playerType p;
			if (boardType::parsePiece(temp, pc, p))
			{
				if ((p == position.movingPlayer()) && (temp.length() > 0) && (temp[0] == '='))
				{
					temp = temp.substr(1, temp.length() - 1);
					if (boardType::parseSquare(temp, from))
					{
						if (position.totalOccupancy()[from])
						{
							if (boardType::parseSquare(temp, to))
							{
								if (!position.totalOccupancy()[to])
								{
									moveBits = create(from, to, pc);
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
		std::string toString_Implementation(const boardType& position, const typename promotionmove::movebitsType moveBits) const noexcept
		{
			const squareType from{ promotionmove::extractFrom(moveBits) };
			const squareType to{ promotionmove::extractTo(moveBits) };
			const pieceType pc{ promotionmove::extractPiece(moveBits) };
			return boardType::pieceToString(pc, position.movingPlayer()) + "=" + boardType::squareToString(from) + boardType::squareToString(to);
		}
	};
}