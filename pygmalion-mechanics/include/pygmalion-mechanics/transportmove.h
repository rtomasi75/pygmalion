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
			pieceType m_Piece;
			squareType m_From;
			squareType m_To;
			playerType m_Player;
		public:
			constexpr playerType player() const noexcept
			{
				return m_Player;
			}
			constexpr pieceType piece() const noexcept
			{
				return m_Piece;
			}
			constexpr squareType from() const noexcept
			{
				return m_From;
			}
			constexpr squareType to() const noexcept
			{
				return m_To;
			}
			constexpr transportMovedata(const pieceType transportedPiece, const squareType fromSquare, const squareType toSquare, const playerType owner) noexcept :
				m_Piece{ transportedPiece },
				m_From{ fromSquare },
				m_To{ toSquare },
				m_Player{ owner }
			{}
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
			sstr << transportmove::countBits << "bit@transport";
			return sstr.str();
		}
	private:
		constexpr static squareType extractTo(const typename transportmove::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		constexpr static void encodeTo(typename transportmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		constexpr static squareType extractFrom(const typename transportmove::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		constexpr static void encodeFrom(typename transportmove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		constexpr static typename transportmove::movedataType doMove_Implementation(boardType& position, const typename transportmove::movebitsType& moveBits) noexcept
		{
			const squareType from{ transportmove::extractFrom(moveBits) };
			const squareType to{ transportmove::extractTo(moveBits) };
			const pieceType pc{ position.getPiece(from) };
			const playerType p{ position.getPlayer(from) };
			position.removePiece(pc, from, p);
			position.addPiece(pc, to, p);
			return typename transportmove::movedataType(pc, from, to, p);
		}
		constexpr static void undoMove_Implementation(boardType& position, const typename transportmove::movedataType& data, const playerType movingPlayer) noexcept
		{
			position.removePiece(data.piece(), data.to(), data.player());
			position.addPiece(data.piece(), data.from(), data.player());
		}
		constexpr static typename transportmove::movebitsType transportMove(const squareType from, const squareType to) noexcept
		{
			typename transportmove::movebitsType bits{ transportmove::movebitsType::zero() };
			transportmove::encodeFrom(bits, from);
			transportmove::encodeTo(bits, to);
			return bits;
		}
		static bool parse_Implementation(const boardType& position, std::string& text, typename transportmove::movebitsType& moveBits) noexcept
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
							moveBits = transportMove(from, to);
							text = temp;
							return true;
						}
					}
				}
			}
			return false;
		}
		static std::string toString_Implementation(const boardType& position, const typename transportmove::movebitsType& moveBits) noexcept
		{
			const squareType from{ transportmove::extractFrom(moveBits) };
			const squareType to{ transportmove::extractTo(moveBits) };
			return boardType::squareToString(from) + boardType::squareToString(to);
		}
	};
}