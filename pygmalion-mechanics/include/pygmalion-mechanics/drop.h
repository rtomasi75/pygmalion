namespace pygmalion::mechanics
{
	template<typename BOARD>
	class drop :
		public move<BOARD, drop<BOARD>>
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		class movedata
		{
		private:
			pieceType m_Piece;
			squareType m_Square;
		public:
			constexpr squareType square() const noexcept
			{
				return m_Square;
			}
			constexpr pieceType piece() const noexcept
			{
				return m_Piece;
			}
			constexpr movedata(const pieceType pc, const squareType sq) noexcept :
				m_Square{ sq },
				m_Piece{ pc }
			{}
		};
		constexpr static size_t requiredBits_Implementation() noexcept
		{
			return detail::requiredUnsignedBits(countPieces) + detail::requiredUnsignedBits(countSquares);
		}
		constexpr static movedata doMove_Implementation(boardType& position, const typename drop::movebitsType& moveBits) noexcept
		{
			constexpr const typename drop::movebitsType mask{ drop::movebitsType::one() << detail::requiredUnsignedBits(countSquares) };
			constexpr const size_t shift{ detail::requiredUnsignedBits(countPieces) };
			const squareType sq{ squareType(moveBits & mask) };
			const pieceType pc{ pieceType(moveBits >> shift) };
			const playerType p{ position.movingPlayer() };
			position.addPiece(pc, sq, p);
			return movedata(pc, sq);
		}
		constexpr static void undoMove_Implementation(boardType& position, const movedata& data, const playerType movingPlayer) noexcept
		{
			position.removePiece(data.piece(), data.square(), movingPlayer);
		}
		constexpr static typename drop::bitsType dropMove(const pieceType piece, const squareType square) noexcept
		{
			typename drop::movebitsType bits{ drop::movebitsType(piece) };
			constexpr const size_t shift{ detail::requiredUnsignedBits(countPieces) };
			bits <<= shift;
			bits |= typename drop::movebitsType(square);
			return bits;
		}
		static bool parse_Implementation(const boardType& position, const std::string text, typename drop::movebitsType& moveBits) noexcept
		{
			return instanceType::parse_Implementation(position, text, moveBits);
		}
		static std::string toString_Implementation(const boardType& position, const typename drop::movebitsType& moveBits) noexcept
		{
			return instanceType::toString_Implementation(position, moveBits);
		}
	};
}