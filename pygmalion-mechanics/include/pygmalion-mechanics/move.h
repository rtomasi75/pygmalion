namespace pygmalion::mechanics
{
	template<typename BOARD, size_t COUNT_BITS, typename MOVEDATA, typename INSTANCE>
	class move
	{
	public:
		using instanceType = INSTANCE;
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countBits{ COUNT_BITS };
		using movebitsType = uint_t<countBits, false>;
		using movedataType = MOVEDATA;
	protected:
		constexpr move() noexcept = default;
		constexpr move(move&&) noexcept = default;
		constexpr move(const move&) noexcept = default;
		constexpr move& operator=(move&&) noexcept = default;
		constexpr move& operator=(const move&) noexcept = default;
		~move() noexcept = default;
	public:
		std::string name() const noexcept
		{
			return static_cast<const instanceType*>(this)->name_Implementation();
		}
		constexpr movedataType doMove(boardType& position, const movebitsType& moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->doMove_Implementation(position, moveBits);
		}
		constexpr void undoMove(boardType& position, const movedataType& data) const noexcept
		{
			static_cast<const instanceType*>(this)->undoMove_Implementation(position, data);
		}
		bool parse(const boardType& position, std::string& text, movebitsType& moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->parse_Implementation(position, text, moveBits);
		}
		std::string toString(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->toString_Implementation(position, moveBits);
		}
		constexpr squaresType otherOccupancyDelta(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->otherOccupancyDelta_Implementation(position, moveBits);
		}
		constexpr squaresType ownOccupancyDelta(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->ownOccupancyDelta_Implementation(position, moveBits);
		}
		constexpr squaresType pieceOccupancyDelta(const boardType& position, const pieceType& piece, const movebitsType& moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->pieceOccupancyDelta_Implementation(position, piece, moveBits);
		}
		constexpr squareType fromSquare(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->fromSquare_Implementation(position, moveBits);
		}
		constexpr squareType toSquare(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->toSquare_Implementation(position, moveBits);
		}
	};
}