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
	private:
		std::vector<scoreType> m_EvaluationParameters;
		deltaType m_EvaluationDelta;
	public:
		const std::vector<scoreType>& evaluationParameters() const noexcept
		{
			return m_EvaluationParameters;
		}
		virtual std::vector<scoreType> parameters() const noexcept override
		{
			std::vector<scoreType> vector1{ this->evaluationParameters() };
			std::vector<scoreType> vector2{ this->materialParameters() };
			vector1.insert(vector1.end(), vector2.begin(), vector2.end());
			return vector1;
		}
		PYGMALION_INLINE const deltaType& evaluationDelta() const noexcept
		{
			return m_EvaluationDelta;
		}
		virtual deltaType delta() const noexcept override
		{
			return this->materialDelta() + this->evaluationDelta();
		}
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::dynamics::engine<typename EVALUATOR::generatorType>(input, output)
		{
			evaluatorType::defaultParameters(m_EvaluationParameters);
			m_EvaluationDelta = std::move(evaluatorType::delta(m_EvaluationParameters));
			this->template addCommand<command_debugEvaluation<descriptorEvaluation, evaluatorType>>();
			this->template addCommand<command_debugEvaluate<descriptorEvaluation, evaluatorType>>();
			std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ evaluatorType::commands() };
			for (auto& cmd : list)
			{
				this->addCommand(cmd);
			}
		}
		virtual ~engine() noexcept = default;
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