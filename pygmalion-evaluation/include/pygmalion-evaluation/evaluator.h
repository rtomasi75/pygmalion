namespace pygmalion
{
	template<typename DESCRIPTOR_EVALUATION, typename INSTANCE, typename... STAGES >
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
		template<typename STAGE, typename... STAGES2>
		constexpr static scoreType computeDelta() noexcept
		{
			constexpr const scoreType sc2{ STAGE::computeDelta() };
			if constexpr (sizeof...(STAGES2) > 0)
				return sc2 + computeDelta<STAGES2...>();
			else
				return sc2;
		}
		template<typename STAGE, typename... STAGES2>
		static scoreType computeStages(const scoreType& alpha, const scoreType& beta, const scoreType& sc, const typename generatorType::stackType& stack) noexcept
		{
			scoreType sc2{ sc };
			constexpr const scoreType delta{ computeDelta<STAGE,STAGES2...>() };
			if (!isFutile(alpha, beta, sc, delta))
			{
				sc2 += STAGE::evaluate(stack);
				if constexpr (sizeof...(STAGES2) > 0)
					return evaluatorType::template computeStages<STAGES2...>(alpha, beta, sc2, stack);
			}
			return sc2;
		}
		static scoreType computeMaterial(const typename generatorType::stackType& stack) noexcept
		{
			return evaluatorType::computeMaterial_Implementation(stack);
		}
		constexpr static scoreType rootDelta() noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
				return computeDelta<STAGES...>();
			else
				return scoreType::zero();
		}
		template<typename STAGE, typename... STAGES2>
		static std::string stageNames(const size_t index, const size_t counter) noexcept
		{
			if (index == counter)
				return STAGE::name();
			else
			{
				if constexpr (sizeof...(STAGES2) > 0)
					return evaluatorType::template stageNames<STAGES2...>(index, counter + 1);
				else
				{
					assert(false);
					return "???";
				}
			}
		}
		template<typename STAGE, typename... STAGES2>
		static scoreType stageScores(const size_t index, const size_t counter, const typename generatorType::stackType& stack) noexcept
		{
			if (index == counter)
				return STAGE::evaluate(stack);
			else
			{
				if constexpr (sizeof...(STAGES2) > 0)
					return evaluatorType::template stageScores<STAGES2...>(index, counter + 1, stack);
				else
				{
					assert(false);
					return scoreType::zero();
				}
			}
		}
	protected:
		template<typename COMMAND>
		static void addCommand(std::deque<std::shared_ptr<pygmalion::intrinsics::command>>& list) noexcept
		{
			std::shared_ptr<pygmalion::intrinsics::command> pCommand{ createCommand<COMMAND>() };
			list.emplace_back(std::move(pCommand));
		}
		constexpr static bool isFutile(const scoreType& alpha, const scoreType& beta, const scoreType& approx, const scoreType& delta) noexcept
		{
			return (approx + delta <= alpha) && (approx + delta < beta);
		}
	public:
		constexpr static inline size_t countStages{ sizeof...(STAGES) };
		static std::string stageName(const size_t index) noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
				return evaluatorType::template stageNames<STAGES...>(index, 0);
			else
			{
				assert(false);
				return "???";
			}
		}
		static scoreType stageScore(const size_t index, const typename generatorType::stackType& stack) noexcept
		{
			if constexpr(sizeof...(STAGES) > 0)
				return evaluatorType::template stageScores<STAGES...>(index, 0, stack);
			else
			{
				assert(false);
				return scoreType::zero();
			}
		}
		constexpr static inline scoreType MaxPositionChange{ rootDelta() };
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commands() noexcept
		{
			return evaluatorType::commandsImplementation();
		}
		static scoreType evaluate(const scoreType& alpha, const scoreType& beta, const typename generatorType::stackType& stack) noexcept
		{
			const scoreType sc{ computeMaterial(stack) };
			if constexpr (sizeof...(STAGES) > 0)
				return evaluatorType::template computeStages<STAGES...>(alpha, beta, sc, stack);
			else
				return sc;
		}
		template<bool LAZY>
		static gamestateType earlyResult(const typename generatorType::stackType& stack, bool& allowStoreTT) noexcept
		{
			if (!gamestateType::isOpen(stack.position().arbitration()))
			{
				allowStoreTT = false;
				return stack.position().arbitration();
			}
			return evaluatorType::template earlyResult_Implementation<LAZY>(stack, allowStoreTT);
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
		constexpr static scoreType staticTacticalMoveScore(const boardType& position, const movebitsType& move) noexcept
		{
			return evaluatorType::staticTacticalMoveScore_Implementation(position, move);
		}
	};
}