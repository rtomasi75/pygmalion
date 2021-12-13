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
		template<size_t COUNTSTAGES>
		class evaluationdelta
		{
		private:
			deltaType m_CurrentStageDelta;
			evaluationdelta<COUNTSTAGES - 1> m_TailDelta;
		public:
			~evaluationdelta() noexcept = default;
			PYGMALION_INLINE evaluationdelta(const evaluationdelta&) noexcept = default;
			PYGMALION_INLINE evaluationdelta& operator=(const evaluationdelta&) noexcept = default;
			PYGMALION_INLINE evaluationdelta(evaluationdelta&&) noexcept = default;
			PYGMALION_INLINE evaluationdelta& operator=(evaluationdelta&&) noexcept = default;
			template<size_t EVALUATIONSTAGE>
			PYGMALION_INLINE const deltaType& stageDelta() const noexcept
			{
				if constexpr (EVALUATIONSTAGE == 0)
					return m_CurrentStageDelta;
				else
					return m_TailDelta.template stageDelta<EVALUATIONSTAGE - 1>();
			}
			PYGMALION_INLINE const deltaType& stageDelta(const size_t evaluationStage) const noexcept
			{
				if (evaluationStage == 0)
					return m_CurrentStageDelta;
				else
					return m_TailDelta.stageDelta(evaluationStage - 1);
			}
			PYGMALION_INLINE const deltaType& currentStageDelta() const noexcept
			{
				return m_CurrentStageDelta;
			}
			PYGMALION_INLINE deltaType& currentStageDelta() noexcept
			{
				return m_CurrentStageDelta;
			}
			PYGMALION_INLINE const evaluationdelta<COUNTSTAGES - 1>& tailDelta() const noexcept
			{
				return m_TailDelta;
			}
			PYGMALION_INLINE evaluationdelta<COUNTSTAGES - 1>& tailDelta() noexcept
			{
				return m_TailDelta;
			}
			evaluationdelta() noexcept :
				m_CurrentStageDelta{ deltaType() },
				m_TailDelta{ evaluationdelta<COUNTSTAGES - 1>() }
			{
			}
		};
		template<>
		class evaluationdelta<1>
		{
		private:
			deltaType m_CurrentStageDelta;
		public:
			~evaluationdelta() noexcept = default;
			PYGMALION_INLINE evaluationdelta(const evaluationdelta&) noexcept = default;
			PYGMALION_INLINE evaluationdelta& operator=(const evaluationdelta&) noexcept = default;
			PYGMALION_INLINE evaluationdelta(evaluationdelta&&) noexcept = default;
			PYGMALION_INLINE evaluationdelta& operator=(evaluationdelta&&) noexcept = default;
			template<size_t EVALUATIONSTAGE>
			PYGMALION_INLINE const deltaType& stageDelta() const noexcept
			{
				static_assert(EVALUATIONSTAGE == 0);
				return m_CurrentStageDelta;
			}
			PYGMALION_INLINE const deltaType& stageDelta(const size_t evaluationStage) const noexcept
			{
				PYGMALION_ASSERT(evaluationStage == 0);
				return m_CurrentStageDelta;
			}
			PYGMALION_INLINE const deltaType& currentStageDelta() const noexcept
			{
				return m_CurrentStageDelta;
			}
			PYGMALION_INLINE deltaType& currentStageDelta() noexcept
			{
				return m_CurrentStageDelta;
			}
			evaluationdelta() noexcept :
				m_CurrentStageDelta{ deltaType() }
			{
			}
		};
		template<>
		class evaluationdelta<0>
		{
		public:
			PYGMALION_INLINE evaluationdelta() noexcept
			{
			}
			~evaluationdelta() noexcept = default;
			evaluationdelta(const evaluationdelta&) noexcept = default;
			PYGMALION_INLINE evaluationdelta& operator=(const evaluationdelta&) noexcept = default;
			PYGMALION_INLINE evaluationdelta(evaluationdelta&&) noexcept = default;
			PYGMALION_INLINE evaluationdelta& operator=(evaluationdelta&&) noexcept = default;
		};
		using evaluationDeltaType = evaluationdelta<countEvaluationStages>;
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
		static void computeDelta(const scoreType* pParameters, evaluationdelta<1 + sizeof...(STAGES2)>& evaluationDelta) noexcept
		{
			if constexpr (sizeof...(STAGES2) > 0)
			{
				evaluator::template computeDelta<STAGES2...>(pParameters + STAGE::getParameterCount(), evaluationDelta.tailDelta());
				STAGE::computeDelta(pParameters, evaluationDelta.currentStageDelta());
				evaluationDelta.currentStageDelta() += evaluationDelta.tailDelta().currentStageDelta();
			}
			else
				STAGE::computeDelta(pParameters, evaluationDelta.currentStageDelta());
		}
		template<size_t PLAYER, bool QUIET, bool PROMO, bool CAPTURE, bool PROMOCAPTURE>
		PYGMALION_INLINE static bool isFutile(const typename generatorType::template stackType<PLAYER>& stack, const scoreType alpha, const scoreType beta, const scoreType approx, const deltaType& stageDelta) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType nextPlayer{ movingPlayer.next() };
			constexpr const scoreType zero{ scoreType::zero() };
			scoreType marginPlayer0{ zero };
			scoreType marginPlayer1{ zero };
			if constexpr (QUIET)
			{
				marginPlayer0 = scoreType::max(marginPlayer0, stageDelta.maxQuietChange(movingPlayer, movingPlayer, stack.position().pieces(movingPlayer)));
				marginPlayer1 = scoreType::max(marginPlayer1, stageDelta.maxQuietChange(nextPlayer, movingPlayer, stack.position().pieces(movingPlayer)));
			}
			if constexpr (PROMO)
			{
				marginPlayer0 = scoreType::max(marginPlayer0, stageDelta.maxPromotionChange(movingPlayer, movingPlayer, stack.position().pieces(movingPlayer)));
				marginPlayer1 = scoreType::max(marginPlayer1, stageDelta.maxPromotionChange(nextPlayer, movingPlayer, stack.position().pieces(movingPlayer)));
			}
			if constexpr (CAPTURE)
			{
				marginPlayer0 = scoreType::max(marginPlayer0, stageDelta.maxCaptureChange(movingPlayer, movingPlayer, stack.position().pieces(movingPlayer), stack.position().opponentPieces(movingPlayer)));
				marginPlayer1 = scoreType::max(marginPlayer1, stageDelta.maxCaptureChange(nextPlayer, movingPlayer, stack.position().pieces(movingPlayer), stack.position().opponentPieces(movingPlayer)));
			}
			if constexpr (PROMOCAPTURE)
			{
				marginPlayer0 = scoreType::max(marginPlayer0, stageDelta.maxPromoCaptureChange(movingPlayer, movingPlayer, stack.position().pieces(movingPlayer), stack.position().opponentPieces(movingPlayer)));
				marginPlayer1 = scoreType::max(marginPlayer1, stageDelta.maxPromoCaptureChange(nextPlayer, movingPlayer, stack.position().pieces(movingPlayer), stack.position().opponentPieces(movingPlayer)));
			}
			return (approx + marginPlayer0 <= alpha) && (approx + marginPlayer1 < beta);
		}
		template<size_t PLAYER, size_t INDEX, bool QUIET, bool PROMO, bool CAPTURE, bool PROMOCAPTURE, typename STAGE, typename... STAGES2>
		static scoreType computeStages(const scoreType alpha, const scoreType beta, const scoreType sc, const typename generatorType::template stackType<PLAYER>& stack, const dataType& data, const scoreType* pParameters, const evaluationDeltaType& evaluationDelta) noexcept
		{
			scoreType sc2{ sc };
			if (!evaluatorType::template isFutile<PLAYER, QUIET, PROMO, CAPTURE, PROMOCAPTURE>(stack, alpha, beta, sc, evaluationDelta.currentStageDelta()))
			{
				sc2 += STAGE::template evaluate<PLAYER>(data.template value<PLAYER, INDEX>(stack), pParameters);
				if constexpr (sizeof...(STAGES2) > 0)
					return evaluatorType::template computeStages<PLAYER, INDEX + 1, QUIET, PROMO, CAPTURE, PROMOCAPTURE, STAGES2...>(alpha, beta, sc2, stack, data, pParameters + STAGE::getParameterCount(), evaluationDelta);
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
		static parameterType stageParameter(const size_t index) noexcept
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
			if constexpr (sizeof...(STAGES2) > 0)
				evaluator::template computeDefaultParameters<STAGES2...>(parameters);
		}
		template<typename STAGE, typename... STAGES2>
		static void computeStageParameterNames(std::vector<std::string>& parameterNames) noexcept
		{
			constexpr const size_t n{ STAGE::getParameterCount() };
			for (size_t i = 0; i < n; i++)
			{
				parameterNames.emplace_back(STAGE::getParameter(i).name());
			}
		}
	protected:
		template<typename COMMAND>
		static void addCommand(std::deque<std::shared_ptr<pygmalion::intrinsics::command>>& list) noexcept
		{
			std::shared_ptr<pygmalion::intrinsics::command> pCommand{ createCommand<COMMAND>() };
			list.emplace_back(std::move(pCommand));
		}
	public:
		constexpr static const size_t countParameters() noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
				return evaluator::template stageParameterCount<STAGES...>();
			else
				return 0;
		};	
		static void defaultParameters(std::vector<scoreType>& parameters) noexcept
		{
			parameters.clear();
			if constexpr (sizeof...(STAGES) > 0)
				return evaluator::template computeDefaultParameters<STAGES...>(parameters);
		}
		static void parameterNames(std::vector<std::string>& parameterNames) noexcept
		{
			parameterNames.clear();
			if constexpr (sizeof...(STAGES) > 0)
				return evaluator::template computeStageParameterNames<STAGES...>(parameterNames);
		}
		static void createData(dataType& data) noexcept
		{
			data = dataType();
		}
		static void delta(const std::vector<scoreType>& parameters, evaluationDeltaType& evaluationDelta) noexcept
		{
			if constexpr (sizeof...(STAGES) > 0)
				evaluator::template computeDelta<STAGES...>(parameters.data(), evaluationDelta);
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
		static scoreType evaluate(const scoreType& alpha, const scoreType& beta, const typename generatorType::template stackType<PLAYER>& stack, const dataType& data, const std::vector<scoreType>& parameters, const evaluationDeltaType& evaluationDelta) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			const scoreType sc{ stack.position().material().template makeSubjective<PLAYER>() };
			bool bQuietPossible{ false };
			for (const auto quietPiece : stack.position().template pieces<static_cast<size_t>(movingPlayer)>())
			{
				if (stack.position().pieceOccupancy(quietPiece) & stack.position().playerOccupancy(movingPlayer) & generatorType::promotionOrigins(movingPlayer, quietPiece))
				{
					bQuietPossible = true;
					break;
				}
			}
			bool bPromotionPossible{ false };
			for (const auto promoPiece : (generatorType::promotionPieces(movingPlayer)& stack.position().template pieces<static_cast<size_t>(movingPlayer)>()))
			{
				if (stack.position().pieceOccupancy(promoPiece) & stack.position().playerOccupancy(movingPlayer) & generatorType::promotionOrigins(movingPlayer, promoPiece))
				{
					bPromotionPossible = true;
					break;
				}
			}
			bool bCapturePossible{ false };
			for (const auto capturePiece : stack.position().template pieces<static_cast<size_t>(movingPlayer)>())
			{
				if (stack.position().pieceOccupancy(capturePiece) & stack.position().playerOccupancy(movingPlayer) & generatorType::captureOrigins(movingPlayer, capturePiece))
				{
					bCapturePossible = true;
					break;
				}
			}
			bool bPromoCapturePossible{ false };
			for (const auto promoCapturePiece : (generatorType::promotionPieces(movingPlayer)& stack.position().template pieces<static_cast<size_t>(movingPlayer)>()))
			{
				if (stack.position().pieceOccupancy(promoCapturePiece) & stack.position().playerOccupancy(movingPlayer) & generatorType::promotionOrigins(movingPlayer, promoCapturePiece))
				{
					bPromoCapturePossible = true;
					break;
				}
			}
			if constexpr (sizeof...(STAGES) > 0)
			{
				const std::uint8_t possibilityFlags{ static_cast<std::uint8_t>(static_cast<std::uint8_t>(bQuietPossible) | (static_cast<std::uint8_t>(bPromotionPossible) << 1) | (static_cast<std::uint8_t>(bCapturePossible) << 2) | (static_cast<std::uint8_t>(bPromoCapturePossible) << 3)) };
				switch (possibilityFlags)
				{
				default:
					PYGMALION_UNREACHABLE;
					return scoreType::zero();
				case 0x0:
					return evaluatorType::template computeStages<PLAYER, 0, false, false, false, false, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0x1:
					return evaluatorType::template computeStages<PLAYER, 0, false, false, false, true, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0x2:
					return evaluatorType::template computeStages<PLAYER, 0, false, false, true, false, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0x3:
					return evaluatorType::template computeStages<PLAYER, 0, false, false, true, true, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0x4:
					return evaluatorType::template computeStages<PLAYER, 0, false, true, false, false, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0x5:
					return evaluatorType::template computeStages<PLAYER, 0, false, true, false, true, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0x6:
					return evaluatorType::template computeStages<PLAYER, 0, false, true, true, false, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0x7:
					return evaluatorType::template computeStages<PLAYER, 0, false, true, true, true, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0x8:
					return evaluatorType::template computeStages<PLAYER, 0, true, false, false, false, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0x9:
					return evaluatorType::template computeStages<PLAYER, 0, true, false, false, true, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0xa:
					return evaluatorType::template computeStages<PLAYER, 0, true, false, true, false, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0xb:
					return evaluatorType::template computeStages<PLAYER, 0, true, false, true, true, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0xc:
					return evaluatorType::template computeStages<PLAYER, 0, true, true, false, false, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0xd:
					return evaluatorType::template computeStages<PLAYER, 0, true, true, false, true, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0xe:
					return evaluatorType::template computeStages<PLAYER, 0, true, true, true, false, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				case 0xf:
					return evaluatorType::template computeStages<PLAYER, 0, true, true, true, true, STAGES...>(alpha, beta, sc, stack, data, parameters.data(), evaluationDelta);
				}
			}
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
		PYGMALION_INLINE static objectiveType staticMoveScore(const boardType& position, const movebitsType move, const materialTableType& materialTable) noexcept
		{
			return evaluatorType::template staticMoveScore_Implementation<PLAYER>(position, move, materialTable);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static objectiveType staticExchangeScore(const boardType& position, const movebitsType move, const materialTableType& materialTable) noexcept
		{
			return evaluatorType::template staticExchangeScore_Implementation<PLAYER>(position, move, materialTable);
		}
	};
}