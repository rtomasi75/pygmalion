namespace pygmalion::state
{
	template<typename BOARD>
	class engine :
		public pygmalion::intrinsics::engine,
		public BOARD::descriptorState
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename BOARD::descriptorState;
#include "include_state.h"
	private:
		boardType m_Position;
	public:
		boardType& position() noexcept
		{
			return m_Position;
		}
		const boardType& position() const noexcept
		{
			return m_Position;
		}
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::intrinsics::engine(input, output)
		{
			addCommand<command_debugPlayers<descriptorState, boardType>>();
			addCommand<command_debugPieces<descriptorState, boardType>>();
			addCommand<command_debugFiles<descriptorState, boardType>>();
			addCommand<command_debugRanks<descriptorState, boardType>>();
			addCommand<command_debugFlags<descriptorState, boardType>>();
			addCommand<command_debugBoard<descriptorState, boardType>>();
			addCommand<command_debugSetFlag<descriptorState, boardType>>();
			addCommand<command_debugClearFlag<descriptorState, boardType>>();
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "no game (state only)";
		}
	};
}