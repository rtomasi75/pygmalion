namespace pygmalion
{
	template<typename DESCRIPTION_MECHANICS, size_t COUNT_BITS_BLOOMFILTER, size_t COUNT_VALUES_BLOOMFILTER>
	class history
	{
	public:
		using descriptorMechanics = DESCRIPTION_MECHANICS;
#include <pygmalion-mechanics/include_mechanics.h>
		using bloomfilterType = bloomfilter<typename descriptorMechanics::descriptorState::hashType, COUNT_BITS_BLOOMFILTER, COUNT_VALUES_BLOOMFILTER - 1>;
	private:
		int m_CountEntries;
		int m_Size;
		boardType* m_Boards;
		bloomfilterType m_Bloomfilter;
	public:
		history() noexcept :
			m_CountEntries{ 0 },
			m_Size{ 16 },
			m_Boards{ new boardType[m_Size] },
			m_Bloomfilter{ bloomfilterType() }
		{

		}
		~history() noexcept
		{
			delete[] m_Boards;
		}
		constexpr bool occurs(const boardType& position, const int times, const int start, const int frequency, const int reversibleMoves) const noexcept
		{
			if (m_Bloomfilter[position.hash()] >= times)
			{
				int nCount{ 0 };
				for (int i = std::max(reversibleMoves, m_CountEntries - start); i >= 0; i -= frequency)
				{
					if (m_Boards[i] == position)
					{
						nCount++;
						if (nCount >= times)
							return true;
					}
				}
			}
			return false;
		}
		void clear() noexcept
		{
			m_CountEntries = 0;
			m_Bloomfilter.clear();
		}
		void append(const boardType& position) noexcept
		{
			if (m_CountEntries == m_Size)
			{
				m_Size *= 2;
				boardType* newBoards = new boardType[m_Size];
				for (int i = 0; i < m_CountEntries; i++)
					newBoards[i] = m_Boards[i];
				delete[] m_Boards;
				m_Boards = newBoards;
			}
			m_Boards[m_CountEntries] = position;
			m_Bloomfilter.increment(position.hash());
			m_CountEntries++;
		}
		void removeLast() noexcept
		{
			assert(m_CountEntries > 0);
			m_Bloomfilter.decrement(m_Boards[m_CountEntries - 1]);
			m_CountEntries--;
		}
	};
}