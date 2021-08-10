namespace pygmalion::evaluation
{
	template<typename EVALUATOR>
	class stage :
		public EVALUATOR::descriptorEvaluation
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = typename EVALUATOR::descriptorEvaluation;
#include "include_evaluation.h"
		using multiscoreType = multiscore<descriptorEvaluation, evaluatorType>;
		using stackType = typename generatorType::stackType;
		virtual subjectiveType delta(const stackType& stack) const noexcept
		{
			assert(false);
			return subjectiveType::zero();
		}
		virtual objectiveType evaluate(const stackType& stack) const noexcept
		{
			assert(false);
			return objectiveType::zero();
		}
	};
}