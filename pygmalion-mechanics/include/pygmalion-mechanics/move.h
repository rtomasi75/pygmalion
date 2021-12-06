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
		using materialTableType = state::materialTables<descriptorState, boardType>;
		constexpr static const size_t countBits{ COUNT_BITS };
		using movebitsType = uint_t<countBits, false>;
		using movedataType = MOVEDATA;
	protected:
		PYGMALION_INLINE constexpr move() noexcept = default;
		PYGMALION_INLINE constexpr move(move&&) noexcept = default;
		PYGMALION_INLINE constexpr move(const move&) noexcept = default;
		PYGMALION_INLINE constexpr move& operator=(move&&) noexcept = default;
		PYGMALION_INLINE constexpr move& operator=(const move&) noexcept = default;
		PYGMALION_INLINE ~move() noexcept = default;
	public:
		static std::string name() noexcept
		{
			return instanceType::name_Implementation();
		}
		PYGMALION_INLINE void doMove(boardType& position, const movebitsType moveBits, movedataType& movedata, const materialTableType& materialTable) const noexcept
		{
			static_cast<const instanceType*>(this)->doMove_Implementation(position, moveBits, movedata, materialTable);
		}
		PYGMALION_INLINE void undoMove(boardType& position, const movedataType& data, const materialTableType& materialTable) const noexcept
		{
			static_cast<const instanceType*>(this)->undoMove_Implementation(position, data, materialTable);
		}
		bool parse(const boardType& position, const std::string& text, movebitsType& moveBits, size_t& count) const noexcept
		{
			return static_cast<const instanceType*>(this)->parse_Implementation(position, text, moveBits, count);
		}
		std::string toString(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->toString_Implementation(position, moveBits);
		}
		PYGMALION_INLINE squaresType otherOccupancyDelta(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->otherOccupancyDelta_Implementation(position, moveBits);
		}
		PYGMALION_INLINE squaresType ownOccupancyDelta(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->ownOccupancyDelta_Implementation(position, moveBits);
		}
		PYGMALION_INLINE squaresType pieceOccupancyDelta(const boardType& position, const pieceType piece, const movebitsType moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->pieceOccupancyDelta_Implementation(position, piece, moveBits);
		}
		PYGMALION_INLINE squareType fromSquare(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->fromSquare_Implementation(position, moveBits);
		}
		PYGMALION_INLINE squareType toSquare(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return static_cast<const instanceType*>(this)->toSquare_Implementation(position, moveBits);
		}
	};
}