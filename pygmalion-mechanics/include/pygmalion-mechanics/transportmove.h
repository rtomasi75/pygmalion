namespace pygmalion::mechanics
{
	namespace detail
	{
		template<typename BOARD>
		class transportMovedata
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			squareType m_From;
			squareType m_To;
			pieceType m_Piece;
			playerType m_Player;
		public:
			PYGMALION_INLINE playerType player() const noexcept
			{
				return m_Player;
			}
			PYGMALION_INLINE pieceType piece() const noexcept
			{
				return m_Piece;
			}
			PYGMALION_INLINE squareType from() const noexcept
			{
				return m_From;
			}
			PYGMALION_INLINE squareType to() const noexcept
			{
				return m_To;
			}
			PYGMALION_INLINE transportMovedata(const pieceType& transportedPiece, const squareType fromSquare, const squareType toSquare, const playerType owner) noexcept :
				m_Piece{ transportedPiece },
				m_From{ fromSquare },
				m_To{ toSquare },
				m_Player{ owner }
			{}
			PYGMALION_INLINE transportMovedata() noexcept = default;
			PYGMALION_INLINE transportMovedata(transportMovedata&&) noexcept = default;
			PYGMALION_INLINE transportMovedata(const transportMovedata&) noexcept = default;
			PYGMALION_INLINE transportMovedata& operator=(transportMovedata&&) noexcept = default;
			PYGMALION_INLINE transportMovedata& operator=(const transportMovedata&) noexcept = default;
			PYGMALION_INLINE ~transportMovedata() noexcept = default;
		};
	}

	template<typename BOARD>
	class transportmove :
		public move<BOARD, 2 * BOARD::squareType::countUnsignedBits, detail::transportMovedata<BOARD>, transportmove<BOARD>>
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countFromBits{ squareType::countUnsignedBits };
		constexpr static const size_t countToBits{ squareType::countUnsignedBits };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename transportmove::movedataType) << ":" << transportmove::countBits << "@transport";
			return sstr.str();
		}
	private:
		PYGMALION_INLINE static squareType extractTo(const typename transportmove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		PYGMALION_INLINE static void encodeTo(typename transportmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		PYGMALION_INLINE static squareType extractFrom(const typename transportmove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		PYGMALION_INLINE static void encodeFrom(typename transportmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		PYGMALION_INLINE constexpr transportmove() noexcept = default;
		PYGMALION_INLINE ~transportmove() noexcept = default;
		PYGMALION_INLINE constexpr transportmove(transportmove&&) noexcept = default;
		PYGMALION_INLINE constexpr transportmove(const transportmove&) noexcept = default;
		PYGMALION_INLINE constexpr transportmove& operator=(transportmove&&) noexcept = default;
		PYGMALION_INLINE constexpr transportmove& operator=(const transportmove&) noexcept = default;
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename transportmove::movebitsType moveBits, typename transportmove::movedataType& movedata) const noexcept
		{
			const squareType from{ transportmove::extractFrom(moveBits) };
			const squareType to{ transportmove::extractTo(moveBits) };
			const pieceType pc{ position.getPiece(from) };
			const playerType p{ position.getPlayer(from) };
			position.removePiece(pc, from, p);
			position.addPiece(pc, to, p);
			movedata = typename transportmove::movedataType(pc, from, to, p);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename transportmove::movedataType& data) const noexcept
		{
			position.removePiece(data.piece(), data.to(), data.player());
			position.addPiece(data.piece(), data.from(), data.player());
		}
		PYGMALION_INLINE typename transportmove::movebitsType create(const squareType from, const squareType to) const noexcept
		{
			typename transportmove::movebitsType bits{ transportmove::movebitsType::zero() };
			transportmove::encodeFrom(bits, from);
			transportmove::encodeTo(bits, to);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename transportmove::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			squareType from;
			squareType to;
			if (boardType::parseSquare(temp, from))
			{
				if (position.totalOccupancy()[from])
				{
					if (boardType::parseSquare(temp, to))
					{
						if (!position.totalOccupancy()[to])
						{
							moveBits = create(from, to);
							text = temp;
							return true;
						}
					}
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename transportmove::movebitsType moveBits) const noexcept
		{
			const squareType from{ transportmove::extractFrom(moveBits) };
			const squareType to{ transportmove::extractTo(moveBits) };
			return boardType::squareToString(from) + boardType::squareToString(to);
		}
	};
}