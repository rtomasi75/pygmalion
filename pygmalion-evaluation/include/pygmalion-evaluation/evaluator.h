namespace pygmalion
{
	template<typename DESCRIPTOR_EVALUATION, typename INSTANCE >
	class evaluator :
		public DESCRIPTOR_EVALUATION
	{
	public:
		using evaluatorType = INSTANCE;
		using descriptorEvaluation = DESCRIPTOR_EVALUATION;
#include "include_evaluation.h"
	public:
		constexpr static subjectiveType makeSubjective(const objectiveType sc, const playerType player) noexcept
		{
			return evaluatorType::makeSubjective_Implementation(sc, player);
		}
		static objectiveType evaluate(const typename generatorType::stackType& stack) noexcept
		{
			return evaluatorType::evaluate_Implementation(stack);
		}
		static gamestateType earlyResult(const typename generatorType::stackType& stack) noexcept
		{
			return evaluatorType::earlyResult_Implementation(stack);
		}
		static gamestateType lateResult(const typename generatorType::stackType& stack) noexcept
		{
			return evaluatorType::lateResult_Implementation(stack);
		}
		constexpr static objectiveType maxScore(const playerType player) noexcept
		{
			return evaluatorType::maxScore_Implementation(player);
		}
		constexpr static objectiveType neutralScore() noexcept
		{
			return evaluatorType::neutralScore_Implementation();
		}
		constexpr static objectiveType winScore(const playerType player) noexcept
		{
			return evaluatorType::winScore_Implementation(player);
		}
		constexpr static objectiveType lossScore(const playerType player) noexcept
		{
			return evaluatorType::lossScore_Implementation(player);
		}
		constexpr static objectiveType minScore(const playerType player) noexcept
		{
			return evaluatorType::minScore_Implementation(player);
		}
	};
}