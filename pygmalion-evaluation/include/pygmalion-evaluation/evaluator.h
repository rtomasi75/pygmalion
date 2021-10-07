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
		template<size_t PLAYER, typename STAGE, typename... STAGES2>
		static scoreType computeStages(const scoreType alpha, const scoreType beta, const scoreType sc, const typename generatorType::template stackType<PLAYER>& stack) noexcept
		{
			scoreType sc2{ sc };
			constexpr const scoreType delta{ computeDelta<STAGE,STAGES2...>() };
			if (!isFutile(alpha, beta, sc, delta))
			{
				sc2 += STAGE::evaluate(stack);
				if constexpr (sizeof...(STAGES2) > 0)
					return evaluatorType::template computeStages<PLAYER, STAGES2...>(alpha, beta, sc2, stack);
			}
			return sc2;
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
					PYGMALION_ASSERT(false);
					return "???";
				}
			}
		}
		template<size_t PLAYER, typename STAGE, typename... STAGES2>
		static scoreType stageScores(const size_t index, const size_t counter, const typename generatorType::template stackType<PLAYER>& stack) noexcept
		{
			if (index == counter)
				return STAGE::template evaluate<PLAYER>(stack);
			else
			{
				if constexpr (sizeof...(STAGES2) > 0)
					return evaluatorType::template stageScores<PLAYER, STAGES2...>(index, counter + 1, stack);
				else
				{
					PYGMALION_ASSERT(false);
					constexpr const scoreType zero{ scoreType::zero() };
					return zero;
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
		constexpr static bool isFutile(const scoreType alpha, const scoreType beta, const scoreType approx, const scoreType delta) noexcept
		{
			return (approx + delta <= alpha) && (approx + delta < beta);
		}
	public:
		constexpr static scoreType rootDelta() noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
				return computeDelta<STAGES...>();
			else
			{
				constexpr const scoreType zero{ scoreType::zero() };
				return zero;
			}
		}
		template<size_t PLAYER>
		static scoreType computeMaterial(const typename generatorType::template stackType<PLAYER>& stack) noexcept
		{
			return evaluatorType::template computeMaterial_Implementation<PLAYER>(stack);
		}
		constexpr static inline size_t countStages{ sizeof...(STAGES) };
		static std::string stageName(const size_t index) noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
				return evaluatorType::template stageNames<STAGES...>(index, 0);
			else
			{
				PYGMALION_ASSERT(false);
				return "???";
			}
		}
		template<size_t PLAYER>
		static scoreType stageScore(const size_t index, const typename generatorType::template stackType<PLAYER>& stack) noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
				return evaluatorType::template stageScores<PLAYER, STAGES...>(index, 0, stack);
			else
			{
				PYGMALION_ASSERT(false);
				return scoreType::zero();
			}
		}
		constexpr static inline scoreType MaxPositionChange{ rootDelta() };
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commands() noexcept
		{
			return evaluatorType::commandsImplementation();
		}
		template<size_t PLAYER>
		static scoreType evaluate(const scoreType& alpha, const scoreType& beta, const typename generatorType::template stackType<PLAYER>& stack) noexcept
		{
			const scoreType sc{ computeMaterial(stack) };
			if constexpr (sizeof...(STAGES) > 0)
				return evaluatorType::template computeStages<PLAYER, STAGES...>(alpha, beta, sc, stack);
			else
				return sc;
		}
		template<size_t PLAYER, bool LAZY>
		static gamestateType earlyResult(const typename generatorType::template stackType<PLAYER>& stack, bool& allowStoreTT) noexcept
		{
			if (!gamestateType::isOpen(stack.position().arbitration()))
			{
				allowStoreTT = false;
				return stack.position().arbitration();
			}
			return evaluatorType::template earlyResult_Implementation<PLAYER, LAZY>(stack, allowStoreTT);
		}
		template<size_t PLAYER>
		static gamestateType lateResult(const typename generatorType::template stackType<PLAYER>& stack) noexcept
		{
			return evaluatorType::template lateResult_Implementation<PLAYER>(stack);
		}
		constexpr static scoreType aspirationWindowSize(const size_t index) noexcept
		{
			return evaluatorType::aspirationWindowSize_Implementation(index);
		}
		constexpr static size_t countAspirationWindows() noexcept
		{
			return evaluatorType::countAspirationWindows_Implementation();
		}
		constexpr static scoreType staticTacticalMoveScore(const boardType& position, const movebitsType move) noexcept
		{
			return evaluatorType::staticTacticalMoveScore_Implementation(position, move);
		}
	};
}