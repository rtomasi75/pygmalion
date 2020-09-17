namespace pygmalion::mechanics
{
	template<typename BOARD, typename INSTANCE>
	class move
	{
	public:
		using instanceType = INSTANCE;
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
	private:
		constexpr static size_t requiredBits() noexcept
		{
			return instanceType::requiredBits_Implementation();
		}
	public:
		constexpr static const size_t countBits{ requiredBits() };
		using movebitsType = uint_t<countBits, false>;
		using movedataType = typename instanceType::movedata;
		constexpr static movedataType doMove(boardType& position, const movebitsType& moveBits) noexcept
		{
			return instanceType::doMove_Implementation(position, moveBits);
		}
		constexpr static void undoMove(boardType& position, const movedataType& data, const playerType movingPlayer) noexcept
		{
			instanceType::undoMove_Implementation(position, data, movingPlayer);
		}
		static bool parse(const boardType& position, const std::string text, movebitsType& moveBits) noexcept
		{
			return instanceType::parse_Implementation(position, text, moveBits);
		}
		static std::string toString(const boardType& position, const movebitsType& moveBits) noexcept
		{
			return instanceType::toString_Implementation(position, moveBits);
		}
	};
}