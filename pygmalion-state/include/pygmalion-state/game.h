namespace pygmalion
{
	template<typename BOARD>
	class game :
		public BOARD::descriptorState
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename BOARD::descriptorState;
#include "include_state.h"	
	private:
		boardType m_Board;
		std::array<clock, countPlayers> m_Clock;
		int m_MaxDepth;
	public:
		game() noexcept :
			m_Clock{ arrayhelper::generate<countPlayers,clock>([](const size_t index) {return clock(); }) },
			m_Board{ boardType() },
			m_MaxDepth{ -1 }
		{
		}
		constexpr const boardType& position() const noexcept
		{
			return m_Board;
		}
		constexpr boardType& position() noexcept
		{
			return m_Board;
		}
		constexpr void initialize() noexcept
		{
			m_Board.initialize();
		}
	};
}