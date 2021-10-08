namespace pygmalion
{
	template<typename DESCRIPTION_MECHANICS, size_t COUNT_BITS_BLOOMFILTER, size_t COUNT_VALUES_BLOOMFILTER>
	class history :
		public DESCRIPTION_MECHANICS
	{
	public:
		using descriptorMechanics = DESCRIPTION_MECHANICS;
#include "include_mechanics.h"
	private:
		bloomfilterType m_Bloomfilter;
		std::vector<boardType> m_Boards;
		std::vector<movedataType> m_MovedataHistory;
		std::vector<movebitsType> m_MoveHistory;
	public:
		constexpr history() noexcept :
			m_Bloomfilter{ bloomfilterType() }
		{

		}
		~history() noexcept
		{
		}
		constexpr bool occurs(const boardType& position, const int times, int start = 4, const int frequency = 4) const noexcept
		{
			if (m_Bloomfilter[position.hash()] >= times)
			{
				int nCount{ 0 };
				if (start == 0)
					start = 4;
				for (int i = m_Boards.size() - start; i >= 0; i -= frequency)
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
			m_Bloomfilter.clear();
			m_MovedataHistory.resize(0);
			m_MoveHistory.resize(0);
			m_Boards.resize(0);
		}
		const boardType& board(const size_t index) const noexcept
		{
			return m_Boards[index];
		}
		const movedataType& movedata(const size_t index) const noexcept
		{
			return m_MovedataHistory[index];
		}
		const movebitsType& movebits(const size_t index) const noexcept
		{
			return m_MoveHistory[index];
		}
		template<typename motorType>
		void makeMove(boardType& position, const movebitsType movebits) noexcept
		{
			m_Boards.push_back(position);
			m_Bloomfilter.increment(position.hash());
			movedataType data;
			motorType::makeMove(position, movebits, data);
			m_MovedataHistory.push_back(std::move(data));
			m_MoveHistory.push_back(std::move(movebits));
		}
		template<typename motorType>
		void unmakeMove(boardType& position) noexcept
		{
			PYGMALION_ASSERT(m_MoveHistory.size() > 0);
			motorType::unmakeMove(position, m_MovedataHistory[m_MovedataHistory.size() - 1]);
			m_Bloomfilter.decrement(position.hash());
			m_MovedataHistory.resize(m_MovedataHistory.size() - 1);
			m_MoveHistory.resize(m_MoveHistory.size() - 1);
			m_Boards.resize(m_Boards.size() - 1);
		}
		constexpr size_t length() const noexcept
		{
			return m_MoveHistory.size();
		}
	};
}