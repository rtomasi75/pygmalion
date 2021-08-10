namespace pygmalion
{
	template<typename DESCRIPTION_EVALUATION, typename EVALUATOR>
	class multiscore :
		public DESCRIPTION_EVALUATION
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "include_evaluation.h"	
	private:
		std::array<objectiveType, playerType::countValues> m_Scores;
		constexpr multiscore(const std::array<objectiveType, playerType::countValues>& ar) noexcept :
			m_Scores(ar)
		{

		}
		constexpr multiscore(std::array<objectiveType, playerType::countValues>&& ar) noexcept :
			m_Scores(std::move(ar))
		{

		}
	public:
		constexpr void plyUp() noexcept
		{
			for (const playerType i : playerType::range)
			{
				m_Scores[i] = m_Scores[i].plyUp();
			}
		}
		constexpr void plyDown() noexcept
		{
			for (const playerType i : playerType::range)
			{
				m_Scores[i] = m_Scores[i].plyDown();
			}
		}
		constexpr objectiveType score(const playerType self) const noexcept
		{
			assert(self.isValid());
			return m_Scores[self];
		}
		constexpr bool refuted(playerType self, const objectiveType sc) noexcept
		{
			assert(self.isValid());
			playerType other{ self };
			for (int i = 1; i < playerType::countValues; i++)
			{
				other = other.next();
				const subjectiveType sc_other{ evaluatorType::makeSubjective(sc, other) };
				const subjectiveType beta_other{ evaluatorType::makeSubjective(m_Scores[other], other) };
				if (sc_other <= beta_other)
					return true;
			}
			return false;
		}
		constexpr bool accepted(const playerType self, const objectiveType sc) noexcept
		{
			assert(self.isValid());
			const subjectiveType sc_self{ evaluatorType::makeSubjective(sc, self) };
			const subjectiveType alpha_self{ evaluatorType::makeSubjective(m_Scores[self], self) };
			if (sc_self > alpha_self)
			{
				m_Scores[self] = sc;
				return true;
			}
			else
				return false;
		}
		constexpr bool isFutile(playerType self, const objectiveType approx, const subjectiveType delta) const noexcept
		{
			const subjectiveType sc_self{ evaluatorType::makeSubjective(approx, self) };
			const subjectiveType alpha_self{ evaluatorType::makeSubjective(m_Scores[self], self) };
			playerType other{ self };
			if (sc_self + delta > alpha_self)
				return false;
			for (int i = 1; i < playerType::countValues; i++)
			{
				other = other.next();
				const subjectiveType sc_other{ evaluatorType::makeSubjective(approx, other) };
				const subjectiveType beta_other{ evaluatorType::makeSubjective(m_Scores[other], other) };
				if (sc_other - delta <= beta_other)
					return false;
			}
			return true;
		}
		constexpr multiscore() noexcept :
			m_Scores{ arrayhelper::make<playerType::countValues,objectiveType>(evaluatorType::neutralScore()) }
		{
			for (const playerType p : playerType::range)
			{
				m_Scores[p] = evaluatorType::minScore(p);
			}
		}
		~multiscore() noexcept = default;
		constexpr multiscore(const multiscore&) noexcept = default;
		constexpr multiscore(multiscore&&) noexcept = default;
		constexpr multiscore& operator=(const multiscore&) noexcept = default;
		constexpr multiscore& operator=(multiscore&&) noexcept = default;
	};
}