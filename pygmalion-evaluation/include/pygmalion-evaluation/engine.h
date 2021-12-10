namespace pygmalion::evaluation
{
	template<typename EVALUATOR>
	class engine :
		public pygmalion::dynamics::engine<typename EVALUATOR::generatorType>,
		public EVALUATOR::descriptorEvaluation
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = typename EVALUATOR::descriptorEvaluation;
#include "include_evaluation.h"
		using evaluationDeltaType = typename evaluatorType::evaluationDeltaType;
	private:
		std::vector<scoreType> m_EvaluationParameters;
		std::vector<scoreType> m_CombinedParameters;
		evaluationDeltaType* m_pEvaluationTotalDelta;
		deltaType* m_pEvaluationDelta;
	public:
		const std::vector<scoreType>& evaluationParameters() const noexcept
		{
			return m_EvaluationParameters;
		}
		virtual const std::vector<scoreType>& parameters() const noexcept override
		{
			return m_CombinedParameters;
		}
		PYGMALION_INLINE const evaluationDeltaType& evaluationDelta() const noexcept
		{
			return *m_pEvaluationTotalDelta;
		}
		virtual const deltaType& delta() const noexcept override
		{
			return *m_pEvaluationDelta;
		}
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::dynamics::engine<typename EVALUATOR::generatorType>(input, output),
			m_EvaluationParameters{ []() { std::vector<scoreType> result; evaluatorType::defaultParameters(result); return result; }() },
			m_pEvaluationTotalDelta{ new evaluationDeltaType() },
			m_pEvaluationDelta{ new deltaType() },
			m_CombinedParameters{ m_EvaluationParameters }
		{
			evaluatorType::delta(m_EvaluationParameters, *m_pEvaluationTotalDelta);
			(*m_pEvaluationDelta) += this->materialDelta();
			if constexpr (evaluatorType::countEvaluationStages > 0)
				(*m_pEvaluationDelta) += m_pEvaluationTotalDelta->currentStageDelta();
			this->template addCommand<command_debugEvaluation<descriptorEvaluation, evaluatorType>>();
			this->template addCommand<command_debugEvaluate<descriptorEvaluation, evaluatorType>>();
			this->template addCommand<command_debugEvaluationParameters<descriptorEvaluation, evaluatorType>>();
			this->template addCommand<command_debugEvaluationDelta<descriptorEvaluation, evaluatorType>>();
			std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ evaluatorType::commands() };
			for (auto& cmd : list)
			{
				this->addCommand(cmd);
			}
			std::vector<scoreType> vector2{ this->materialParameters() };
			m_CombinedParameters.insert(m_CombinedParameters.end(), vector2.begin(), vector2.end());
		}
		virtual ~engine() noexcept
		{
			delete m_pEvaluationDelta;
			delete m_pEvaluationTotalDelta;
		}

#if defined(PYGMALION_TUNE)
		std::array<parameter, evaluatorType::countParameters>&& getParameters() const noexcept
		{
			return std::move(arrayhelper::generate<evaluatorType::countParameters, parameter>([](const size_t index) {return evaluatorType::getParameter(index); }));
		}
		void setParameters(const std::array<parameter, evaluatorType::countParameters>& parameters) noexcept
		{
			for (size_t index = 0; index < evaluatorType::countParameters; index++)
				evaluatorType::setParameter(index, parameters[index].value());
	}
#endif
};
}