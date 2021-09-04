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
		std::array<int, countPlayers> m_LastTimeControl;
		durationType m_BaseTime;
		durationType m_IncrementTime;
		int m_MovesPerTimeControl;
	public:
		constexpr durationType baseTime() const noexcept
		{
			return m_BaseTime;
		}
		constexpr durationType incrementTime() const noexcept
		{
			return m_IncrementTime;
		}
		constexpr int movesPerTimeControl() const noexcept
		{
			return m_MovesPerTimeControl;
		}
		constexpr void setTimeControl(const int movesPerTimeControl, const durationType baseTime, const durationType incrementTime) noexcept
		{
			m_MovesPerTimeControl = movesPerTimeControl;
			m_BaseTime = baseTime;
			m_IncrementTime = incrementTime;
			for (const auto pl : playerType::range)
				m_LastTimeControl[pl] = 0;
		}
		constexpr int lastTimeControl(const playerType& pl) const noexcept
		{
			return m_LastTimeControl[pl];
		}
		constexpr void makeMove(const playerType& pl) noexcept
		{
			m_LastTimeControl[pl]++;
		}
		constexpr void unmakeMove(const playerType& pl) noexcept
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
			m_IncrementTime{ 0 },
			m_BaseTime{ 0 }
		{
		}
		constexpr const clock& playerClock(const playerType& pl) const noexcept
		{
			return m_Clock[pl];
		}
		constexpr clock& playerClock(const playerType& pl) noexcept
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
		constexpr void initialize() noexcept
		{
			m_Board.initialize();
			resetTimeControl();
		}
	};
}