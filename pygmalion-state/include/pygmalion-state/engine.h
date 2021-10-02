namespace pygmalion::state
{
	template<typename BOARD>
	class engine :
		public pygmalion::intrinsics::engine,
		public BOARD::descriptorState
	{
	public:
		using boardType = BOARD;
		using gameType = game<boardType>;
		using descriptorState = typename BOARD::descriptorState;
#include "include_state.h"
	private:
		gameType m_Game;
	public:
		gameType& currentGame() noexcept
		{
			return m_Game;
		}
		const gameType& currentGame() const noexcept
		{
			return m_Game;
		}
		boardType& position() noexcept
		{
			return m_Game.position();
		}
		const boardType& position() const noexcept
		{
			return m_Game.position();
		}
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::intrinsics::engine(input, output)
		{
			this->template addCommand<command_debugPlayers<descriptorState, boardType>>();
			this->template addCommand<command_debugPieces<descriptorState, boardType>>();
			this->template addCommand<command_debugFiles<descriptorState, boardType>>();
			this->template addCommand<command_debugFile<descriptorState, boardType>>();
			this->template addCommand<command_debugRanks<descriptorState, boardType>>();
			this->template addCommand<command_debugRank<descriptorState, boardType>>();
			this->template addCommand<command_debugFlags<descriptorState, boardType>>();
			this->template addCommand<command_debugBoard<descriptorState, boardType>>();
			this->template addCommand<command_debugSetFlag<descriptorState, boardType>>();
			this->template addCommand<command_debugClearFlag<descriptorState, boardType>>();
			this->template addCommand<command_debugToggleFlag<descriptorState, boardType>>();
			this->template addCommand<command_debugSetPlayer<descriptorState, boardType>>();
			this->template addCommand<command_debugNextPlayer<descriptorState, boardType>>();
			this->template addCommand<command_debugClearBoard<descriptorState, boardType>>();
			this->template addCommand<command_debugAddPiece<descriptorState, boardType>>();
			this->template addCommand<command_debugRemovePiece<descriptorState, boardType>>();
			this->template addCommand<command_debugOccupancy<descriptorState, boardType>>();
			this->template addCommand<command_debugSquares<descriptorState, boardType>>();
			this->template addCommand<command_debugState<descriptorState, boardType>>();
			m_Game.initialize();
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "Pygmalion";
		}
		virtual std::string author() const noexcept override
		{
			return "Roland Tomasi";
		}
	};
}