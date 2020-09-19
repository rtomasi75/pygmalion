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
		static std::string name() noexcept
		{
			return instanceType::name_Implementation();
		}
		constexpr movedataType doMove(boardType& position, const movebitsType& moveBits) const noexcept
		{
			return reinterpret_cast<const instanceType*>(this)->doMove_Implementation(position, moveBits);
		}
		constexpr void undoMove(boardType& position, const movedataType& data) const noexcept
		{
			reinterpret_cast<const instanceType*>(this)->undoMove_Implementation(position, data);
		}
		bool parse(const boardType& position, std::string& text, movebitsType& moveBits) const noexcept
		{
			return reinterpret_cast<const instanceType*>(this)->parse_Implementation(position, text, moveBits);
		}
		std::string toString(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return reinterpret_cast<const instanceType*>(this)->toString_Implementation(position, moveBits);
		}
	};
}