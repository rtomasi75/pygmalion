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
		using multiscoreType = multiscore<descriptorEvaluation, evaluatorType>;
	private:
		template<typename COMMAND>
		static std::shared_ptr<pygmalion::intrinsics::command> createCommand() noexcept
		{
			auto delCmd = [](pygmalion::intrinsics::command* pCmd)
			{
				delete static_cast<COMMAND*>(pCmd);
			};
			std::shared_ptr<pygmalion::intrinsics::command> pCommand(static_cast<pygmalion::intrinsics::command*>(new COMMAND()), delCmd);
			return pCommand;
		}
	protected:
		template<typename COMMAND>
		static void addCommand(std::deque<std::shared_ptr<pygmalion::intrinsics::command>>& list) noexcept
		{
			std::shared_ptr<pygmalion::intrinsics::command> pCommand{ createCommand<COMMAND>() };
			list.emplace_back(std::move(pCommand));
		}
	public:
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commands() noexcept
		{
			return evaluatorType::commandsImplementation();
		}
		constexpr static subjectiveType makeSubjective(const objectiveType sc, const playerType player) noexcept
		{
			return evaluatorType::makeSubjective_Implementation(sc, player);
		}
		static objectiveType evaluate(const multiscoreType& score, const typename generatorType::stackType& stack) noexcept
		{
			return evaluatorType::evaluate_Implementation(score, stack);
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