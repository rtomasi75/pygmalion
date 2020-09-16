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
			this->addCommand<command_debugPlayers<descriptorState, boardType>>();
			this->addCommand<command_debugPieces<descriptorState, boardType>>();
			this->addCommand<command_debugFiles<descriptorState, boardType>>();
			this->addCommand<command_debugRanks<descriptorState, boardType>>();
			this->addCommand<command_debugFlags<descriptorState, boardType>>();
			this->addCommand<command_debugBoard<descriptorState, boardType>>();
			this->addCommand<command_debugSetFlag<descriptorState, boardType>>();
			this->addCommand<command_debugClearFlag<descriptorState, boardType>>();
			this->addCommand<command_debugToggleFlag<descriptorState, boardType>>();
			this->addCommand<command_debugSetPlayer<descriptorState, boardType>>();
			this->addCommand<command_debugNextPlayer<descriptorState, boardType>>();
			this->addCommand<command_debugClearBoard<descriptorState, boardType>>();
			this->addCommand<command_debugAddPiece<descriptorState, boardType>>();
			this->addCommand<command_debugRemovePiece<descriptorState, boardType>>();
			this->addCommand<command_debugOccupancy<descriptorState, boardType>>();
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "no game (state only)";
		}
	};
}