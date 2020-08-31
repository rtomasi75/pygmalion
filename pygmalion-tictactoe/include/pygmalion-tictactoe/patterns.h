namespace pygmalion::tictactoe
{
	template<typename DESCRIPTION_BOARD>
	class patterns :
		public base_board<DESCRIPTION_BOARD>
	{
	public:
		using descriptorBoard = DESCRIPTION_BOARD;
#include "pygmalion-core/include_board.h"
		constexpr static int countLines{ countRanks * countFiles + 2 };
	private:
		std::array<squaresType, countLines> m_Lines;
	public:
		constexpr patterns() noexcept :
			m_Lines{ make_array_n<countLines,squaresType>(squaresType::none()) }
		{
			auto current = 0;
			for (const auto rank : rankType::range)
			{
				for (const auto file : fileType::range)
				{
					m_Lines[current] += squareType::fromRankFile(rank, file);
				}
				current++;
			}
			for (const auto file : fileType::range)
			{
				for (const auto rank : rankType::range)
				{
					m_Lines[current] += squareType::fromRankFile(rank, file);
				}
				current++;
			}
			for (int idx = 0; idx < std::min(countRanks, countFiles); idx++)
			{
				m_Lines[current] += squareType::fromRankFile(idx, idx);
				m_Lines[current + 1] += squareType::fromRankFile(std::min(countRanks, countFiles) - 1 - idx, idx);
			}
		}
		~patterns() noexcept = default;
		constexpr const squaresType& line(const int idx) const noexcept
		{
			assert(idx >= 0);
			assert(idx < countLines);
			return m_Lines[idx];
		}
	};
}