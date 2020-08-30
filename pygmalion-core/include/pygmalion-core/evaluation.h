namespace pygmalion
{
	template<typename DESCRIPTION_EVALUATION, typename INSTANCE>
	class evaluation :
		public base_evaluation<DESCRIPTION_EVALUATION>
	{
	public:

		using evaluationType = INSTANCE;

		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "include_evaluation.h"

		class stack :
			public base_evaluation<DESCRIPTION_EVALUATION>,
			public generatorType::stackType
		{
		public:
			using evaluationType = INSTANCE;

			using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "include_evaluation.h"

			stack(const stack& parent, const moveType move) noexcept :
				generatorType::stackType(parent, move)
			{
			}
			stack(boardType& position, const playerType oldPlayer) noexcept :
				generatorType::stackType(position, oldPlayer)
			{
			}
			~stack() noexcept = default;
		};
		using stackType = typename pygmalion::evaluation<DESCRIPTION_EVALUATION, evaluationType>::stack;

		static gamestateType earlyResult(const stackType& stack) noexcept
		{
			return evaluationType::earlyResult_Implementation(stack);
		}
		static gamestateType lateResult(const stackType& stack) noexcept
		{
			return evaluationType::lateResult_Implementation(stack);
		}
		static objectiveType evaluate(const stackType& stack) noexcept
		{
			return evaluationType::evaluate_Implementation(stack);
		}
		constexpr static objectiveType makeSubjective(const objectiveType& sc, const playerType player) noexcept
		{
			return evaluationType::makeSubjective_Implementation(sc, player);
		}
		constexpr static objectiveType maxScore(const playerType player) noexcept
		{
			return evaluationType::maxScore_Implementation(player);
		}
		constexpr static objectiveType neutralScore() noexcept
		{
			return evaluationType::neutralScore_Implementation();
		}
		constexpr static objectiveType winScore(const playerType player) noexcept
		{
			return evaluationType::winScore_Implementation(player);
		}
		constexpr static objectiveType lossScore(const playerType player) noexcept
		{
			return evaluationType::lossScore_Implementation(player);
		}
		constexpr static objectiveType minScore(const playerType player) noexcept
		{
			return evaluationType::minScore_Implementation(player);
		}
		constexpr static void plyDown(objectiveType& sc) noexcept
		{
			evaluationType::plyDown_Implementation(sc);
		}
		constexpr static void plyUp(objectiveType& sc) noexcept
		{
			evaluationType::plyDown_Implementation(sc);
		}
	};
}