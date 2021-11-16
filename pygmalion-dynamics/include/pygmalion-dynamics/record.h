namespace pygmalion
{
	template<typename DESCRIPTOR_DYNAMICS>
	class record :
		public DESCRIPTOR_DYNAMICS
	{
	public:
		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include "include_dynamics.h"
	private:
		boardType m_StartPosition;
		std::vector<movebitsType> m_Moves;
		std::string m_Players[countPlayers];
		gamestateType m_Outcome;
	public:
		boardType position(const size_t ply) const noexcept
		{
			PYGMALION_ASSERT(ply < m_Moves.size());
			boardType pos{ boardType(m_StartPosition) };
			for (size_t i = 0; i < ply; i++)
			{
				movedataType data;
				motorType::makeMove(pos, m_Moves[i], data);
			}
			return pos;
		}
		PYGMALION_INLINE size_t length() const noexcept
		{
			return m_Moves.size();
		}
		const std::string& playerName(const playerType pl) const noexcept
		{
			return m_Players[pl];
		}
		gamestateType outcome() const noexcept
		{
			return m_Outcome;
		}
		record() noexcept
		{
			m_StartPosition.initialize();
			for (size_t i = 0; i < countPlayers; i++)
			{
				m_Players[i] = "Player_" + parser::fromInt(i);
			}
			m_Outcome = gamestateType::open();
		}
		~record() noexcept = default;
		record(const record&) noexcept = default;
		record(record&&) noexcept = default;
		record& operator=(const record&) = default;
		record& operator=(record&&) = default;
	};
}