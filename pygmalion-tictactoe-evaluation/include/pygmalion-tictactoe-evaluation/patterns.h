namespace pygmalion::tictactoe
{
	template<typename DESCRIPTION_EVALUATION>
	class patterns :
		public DESCRIPTION_EVALUATION
	{
	public:
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "pygmalion-evaluation/include_evaluation.h"
		constexpr static int countLines{ countRanks * countFiles + 2 };
	private:
		std::array<squaresType, countLines> m_Lines;
	public:
		constexpr patterns() noexcept :
			m_Lines{ pygmalion::arrayhelper::make<countLines,squaresType>(squaresType::none()) }
		{
			auto current = 0;
			for (const auto rank : rankType::range)
			{
				for (const auto file : fileType::range)
				{
					m_Lines[current] |= (rank & file);
				}
				current++;
			}
			for (const auto file : fileType::range)
			{
				for (const auto rank : rankType::range)
				{
					m_Lines[current] |= (rank & file);
				}
				current++;
			}
			for (int idx = 0; idx < std::min(countRanks, countFiles); idx++)
			{
				m_Lines[current] |= (static_cast<rankType>(idx) & static_cast<fileType>(idx));
				m_Lines[current + 1] |= (static_cast<rankType>(std::min(countRanks, countFiles) - 1 - idx) & static_cast<rankType>(idx));
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