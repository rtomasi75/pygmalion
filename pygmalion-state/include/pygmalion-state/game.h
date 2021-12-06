namespace pygmalion
{
	template<typename BOARD>
	class game :
		public BOARD::descriptorState
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename BOARD::descriptorState;
		using materialTableType = state::materialTables<descriptorState, boardType>;
#include "include_state.h"	
	private:
		boardType m_Board;
		std::array<clock, countPlayers> m_Clock;
		std::array<int, countPlayers> m_LastTimeControl;
		std::array <durationType, countPlayers> m_BaseTime;
		std::array <durationType, countPlayers> m_IncrementTime;
		int m_MovesPerTimeControl;
	public:
		constexpr durationType baseTime(const playerType player) const noexcept
		{
			return m_BaseTime[player];
		}
		constexpr durationType incrementTime(const playerType player) const noexcept
		{
			return m_IncrementTime[player];
		}
		constexpr int movesPerTimeControl() const noexcept
		{
			return m_MovesPerTimeControl;
		}
		constexpr void setTimeControl(const int movesPerTimeControl, const std::array<durationType, countPlayers>& baseTime, const std::array<durationType, countPlayers>& incrementTime) noexcept
		{
			m_MovesPerTimeControl = movesPerTimeControl;
			for (const auto pl : playerType::range)
			{
				m_BaseTime[pl] = baseTime[pl];
				m_IncrementTime[pl] = incrementTime[pl];
				m_LastTimeControl[pl] = 0;
			}
		}
		constexpr int lastTimeControl(const playerType pl) const noexcept
		{
			return m_LastTimeControl[pl];
		}
		constexpr void makeMove(const playerType pl) noexcept
		{
			m_LastTimeControl[pl]++;
		}
		constexpr void unmakeMove(const playerType pl) noexcept
		{
			m_LastTimeControl[pl]--;
		}
		constexpr void resetTimeControl() noexcept
		{
			for (const auto pl : playerType::range)
				m_LastTimeControl[pl] = 0;
		}
		game() noexcept :
			m_Clock{ arrayhelper::generate<countPlayers,clock>([](const size_t index) {return clock(); }) },
			m_LastTimeControl{ arrayhelper::make<countPlayers,int>(0) },
			m_Board{ boardType() },
			m_MovesPerTimeControl{ 0 },
			m_IncrementTime{ arrayhelper::make<countPlayers,durationType>(durationType(0)) },
			m_BaseTime{ arrayhelper::make<countPlayers,durationType>(durationType(0)) }
		{
		}
		constexpr const clock& playerClock(const playerType pl) const noexcept
		{
			return m_Clock[pl];
		}
		constexpr clock& playerClock(const playerType pl) noexcept
		{
			return m_Clock[pl];
		}
		constexpr const boardType& position() const noexcept
		{
			return m_Board;
		}
		constexpr boardType& position() noexcept
		{
			return m_Board;
		}
		constexpr void initialize(const materialTableType& materialTable) noexcept
		{
			m_Board.initialize(materialTable);
			resetTimeControl();
		}
	};
}