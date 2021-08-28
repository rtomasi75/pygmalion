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
		constexpr static bool isFutile(const scoreType alpha, const scoreType beta, const scoreType approx, const scoreType delta) noexcept
		{
			return (approx + delta <= alpha) && (approx + delta < beta);
		}
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commands() noexcept
		{
			return evaluatorType::commandsImplementation();
		}
		static scoreType evaluate(const scoreType alpha, const scoreType beta, const typename generatorType::stackType& stack) noexcept
		{
			return evaluatorType::evaluate_Implementation(alpha, beta, stack);
		}
		static gamestateType earlyResult(const typename generatorType::stackType& stack) noexcept
		{
			if (!gamestateType::isOpen(stack.position().arbitration()))
			{
				return stack.position().arbitration();
			}
			return evaluatorType::earlyResult_Implementation(stack);
		}
		static gamestateType lateResult(const typename generatorType::stackType& stack) noexcept
		{
			return evaluatorType::lateResult_Implementation(stack);
		}
		constexpr static scoreType aspirationWindowSize(const size_t index) noexcept
		{
			return evaluatorType::aspirationWindowSize_Implementation(index);
		}
		constexpr static size_t countAspirationWindows() noexcept
		{
			return evaluatorType::countAspirationWindows_Implementation();
		}
	};
}