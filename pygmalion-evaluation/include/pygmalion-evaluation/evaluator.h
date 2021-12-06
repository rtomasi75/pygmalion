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
		constexpr static const inline size_t countEvaluationStages{ sizeof...(STAGES) };
		using evaluationFlagsType = uint_t<countEvaluationStages + 1, false>;
		template<size_t INDEX>
		using evaluatorStageType = std::tuple_element_t<INDEX, std::tuple<STAGES...>>;
		template<size_t INDEX>
		using evaluatorStageSataType = typename evaluatorStageType<INDEX>::dataType;
		class dataType
		{
		private:
			mutable std::tuple<typename STAGES::dataType...> m_Values;
			mutable scoreType m_Delta;
			mutable evaluationFlagsType m_Flags;
		public:
			template<size_t PLAYER, size_t INDEX>
			const evaluatorStageSataType<INDEX>& value(const typename generatorType::template stackType<PLAYER>& stack) const noexcept
			{
				if (!m_Flags.template extractBits<INDEX, 1>())
				{
					evaluatorStageType<INDEX>::computeData(stack, std::get<INDEX>(m_Values));
					m_Flags.template setBits<INDEX, 1>();
				}
				return std::get<INDEX>(m_Values);
			}
			dataType() noexcept :
				m_Flags{ evaluationFlagsType(0) }
			{
			}
			~dataType() noexcept = default;
			dataType(const dataType&) noexcept = default;
			dataType(dataType&&) noexcept = default;
			dataType& operator=(const dataType&) noexcept = default;
			dataType& operator=(dataType&&) noexcept = default;
		};
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
		static deltaType&& computeDelta(const scoreType* pParameters) noexcept
		{
			deltaType sc2{ STAGE::computeDelta(pParameters) };
			if constexpr (sizeof...(STAGES2) > 0)
				return std::move(sc2 + computeDelta<STAGES2...>(pParameters + STAGE::getParameterCount()));
			else
				return std::move(sc2);
		}
		template<size_t PLAYER, size_t INDEX, typename STAGE, typename... STAGES2>
		PYGMALION_INLINE static scoreType computeStages(const scoreType alpha, const scoreType beta, const scoreType sc, const typename generatorType::template stackType<PLAYER>& stack, const dataType& data, const scoreType* pParameters) noexcept
		{
			scoreType sc2{ sc };
			const scoreType delta{ computeDelta<STAGE,STAGES2...>(pParameters) };
			if (!isFutile(alpha, beta, sc, delta))
			{
				sc2 += STAGE::template evaluate<PLAYER>(data.template value<PLAYER, INDEX>(stack), pParameters);
				if constexpr (sizeof...(STAGES2) > 0)
					return evaluatorType::template computeStages<PLAYER, INDEX + 1, STAGES2...>(alpha, beta, sc2, stack, data, pParameters + STAGE::getParameterCount());
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
		template<size_t PLAYER, size_t INDEX, typename STAGE, typename... STAGES2>
		static scoreType stageScores(const size_t index, const dataType& data, const typename generatorType::template stackType<PLAYER>& stack, const scoreType* pParameters) noexcept
		{
			if (index == INDEX)
				return STAGE::template evaluate<PLAYER>(data.template value<PLAYER, INDEX>(stack), pParameters);
			else
			{
				if constexpr (sizeof...(STAGES2) > 0)
					return evaluatorType::template stageScores<PLAYER, INDEX + 1, STAGES2...>(index, data, stack, pParameters + STAGE::getParameterCount());
				else
				{
					PYGMALION_ASSERT(false);
					return scoreType::zero();
				}
			}
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
		static void computeDefaultParameters(std::vector<scoreType>& parameters) noexcept
		{
			constexpr const size_t n{ STAGE::getParameterCount() };
			for (size_t i = 0; i < n; i++)
			{
				parameters.emplace_back(STAGE::getParameter(i).defaultValue());
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
		constexpr static const inline size_t countStages{ sizeof...(STAGES) };
		static void defaultParameters(std::vector<scoreType>& parameters) noexcept
		{
			parameters.clear();
			if constexpr (sizeof...(STAGES) > 0)
				return computeDefaultParameters(parameters);
		}
		PYGMALION_INLINE static void createData(dataType& data) noexcept
		{
			data = dataType();
		}
		static deltaType&& delta(const std::vector<scoreType>& parameters) noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
				return computeDelta<STAGES...>(parameters.data());
			else
			{
				deltaType delta;
				return std::move(delta);
			}
		}
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
		static scoreType stage(const size_t stageIndex, const typename generatorType::template stackType<PLAYER>& stack, const dataType& data, const std::vector<scoreType>& parameters) noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
				return evaluatorType::template stageScores<PLAYER, 0, STAGES...>(stageIndex, data, stack, parameters.data());
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
		PYGMALION_INLINE static scoreType evaluate(const scoreType& alpha, const scoreType& beta, const typename generatorType::template stackType<PLAYER>& stack, const dataType& data, const std::vector<scoreType>& parameters) noexcept
		{
			const scoreType sc{ stack.position().template materialRelative<PLAYER>() };
			if constexpr (sizeof...(STAGES) > 0)
				return evaluatorType::template computeStages<PLAYER, 0, STAGES...>(alpha, beta, sc, stack, data, parameters.data());
			else
				return sc;
		}
		template<size_t PLAYER, bool LAZY>
		PYGMALION_INLINE static gamestateType earlyResult(const typename generatorType::template stackType<PLAYER>& stack, bool& allowStoreTT) noexcept
		{
			if (!gamestateType::isOpen(stack.position().arbitration()))
			{
				allowStoreTT = false;
				return stack.position().arbitration();
			}
			return evaluatorType::template earlyResult_Implementation<PLAYER, LAZY>(stack, allowStoreTT);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static gamestateType lateResult(const typename generatorType::template stackType<PLAYER>& stack) noexcept
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
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType staticMoveScore(const boardType& position, const movebitsType move, const materialTableType& materialTable) noexcept
		{
			return evaluatorType::template staticMoveScore_Implementation<PLAYER>(position, move, materialTable);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType staticExchangeScore(const boardType& position, const movebitsType move, const materialTableType& materialTable) noexcept
		{
			return evaluatorType::template staticExchangeScore_Implementation<PLAYER>(position, move, materialTable);
		}
	};
}