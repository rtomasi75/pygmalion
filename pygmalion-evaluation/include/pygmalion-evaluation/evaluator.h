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
		PYGMALION_TUNABLE static scoreType computeDelta() noexcept
		{
			PYGMALION_TUNABLE const scoreType sc2{ STAGE::computeDelta() };
			if constexpr (sizeof...(STAGES2) > 0)
				return sc2 + computeDelta<STAGES2...>();
			else
				return sc2;
		}
		template<size_t PLAYER, typename STAGE, typename... STAGES2>
		PYGMALION_INLINE static scoreType computeStages(const scoreType alpha, const scoreType beta, const scoreType sc, const typename generatorType::template stackType<PLAYER>& stack) noexcept
		{
			scoreType sc2{ sc };
			PYGMALION_TUNABLE const scoreType delta{ computeDelta<STAGE,STAGES2...>() };
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
		PYGMALION_INLINE static scoreType stageScores(const size_t index, const size_t counter, const typename generatorType::template stackType<PLAYER>& stack) noexcept
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
		template<typename STAGE, typename... STAGES2>
		constexpr static size_t stageParameterCount() noexcept
		{
			size_t count{ STAGE::getParameterCount() };
			if constexpr (sizeof...(STAGES2) > 0)
				return count + evaluatorType::template stageParameterCount<STAGES2...>();
			else
				return count;
		}
		template<typename STAGE, typename... STAGES2>
		static parameter stageParameter(const size_t index) noexcept
		{
			size_t count{ STAGE::getParameterCount() };
			if (index < count)
				return STAGE::getParameter(index);
			if constexpr (sizeof...(STAGES2) > 0)
				return evaluatorType::template stageParameter<STAGES2...>(index - count);
			else
			{
				PYGMALION_ASSERT(false);
				return parameter(0.0, 0.0, 0.0, 0.0, "???");
			}
		}
		template<typename STAGE, typename... STAGES2>
		static void setStageParameter(const size_t index, const double value) noexcept
		{
			size_t count{ STAGE::getParameterCount() };
			if (index < count)
				STAGE::setParameter(index, value);
			else
			{
				if constexpr (sizeof...(STAGES2) > 0)
					evaluatorType::template setStageParameter<STAGES2...>(index - count, value);
				else
				{
					PYGMALION_ASSERT(false);
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
		PYGMALION_INLINE static bool isFutile(const scoreType alpha, const scoreType beta, const scoreType approx, const scoreType delta) noexcept
		{
			return (approx + delta <= alpha) && (approx + delta < beta);
		}
	public:
#if defined(PYGMALION_TUNE)
		constexpr static size_t getParameterCount() noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
				return evaluatorType::countParameters_Implementation() + evaluatorType::template stageParameterCount<STAGES...>();
			else
				return evaluatorType::countParameters_Implementation();

		}
		constexpr static inline const size_t countParameters{ getParameterCount() };
		static parameter getParameter(const size_t index) noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
			{
				constexpr size_t pars{ evaluatorType::countParameters_Implementation() };
				if (index < pars)
					return evaluatorType::getParameter_Implementation(index);
				return evaluatorType::template stageParameter<STAGES...>(index - pars);
			}
			else
			{
				return evaluatorType::getParameter_Implementation(index);
			}
		}
		static void setParameter(const size_t index, double value) noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
			{
				constexpr size_t pars{ evaluatorType::countParameters_Implementation() };
				if (index < pars)
					evaluatorType::setParameter_Implementation(index, value);
				else
					evaluatorType::template setStageParameter<STAGES...>(index - pars, value);
			}
			else
				evaluatorType::setParameter_Implementation(index, value);
		}
#endif
		PYGMALION_TUNABLE static scoreType rootDelta(const scoreType materialDelta) noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
				return materialDelta + computeDelta<STAGES...>();
			else
			{
				constexpr const scoreType zero{ scoreType::zero() };
				return materialDelta;
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
		PYGMALION_INLINE constexpr static scoreType initialAspirationWindowSize() noexcept
		{
			return evaluatorType::initialAspirationWindowSize_Implementation();
		}
		PYGMALION_INLINE constexpr static size_t countAspirationWindows() noexcept
		{
			return evaluatorType::countAspirationWindows_Implementation();;
		}
		PYGMALION_INLINE static scoreType staticMoveScore(const boardType& position, const movebitsType move) noexcept
		{
			return evaluatorType::staticMoveScore_Implementation(position, move);
		}
		PYGMALION_INLINE static scoreType staticExchangeScore(const boardType& position, const movebitsType move) noexcept
		{
			return evaluatorType::staticExchangeScore_Implementation(position, move);
		}
	};
}