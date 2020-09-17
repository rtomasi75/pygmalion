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
		static std::string name() noexcept
		{
			return instanceType::name_Implementation();
		}
		constexpr static movedataType doMove(boardType& position, const movebitsType& moveBits) noexcept
		{
			return instanceType::doMove_Implementation(position, moveBits);
		}
		constexpr static void undoMove(boardType& position, const movedataType& data, const playerType movingPlayer) noexcept
		{
			instanceType::undoMove_Implementation(position, data, movingPlayer);
		}
		static bool parse(const boardType& position, std::string& text, movebitsType& moveBits) noexcept
		{
			return instanceType::parse_Implementation(position, text, moveBits);
		}
		static std::string toString(const boardType& position, const movebitsType& moveBits) noexcept
		{
			return instanceType::toString_Implementation(position, moveBits);
		}
	};
}