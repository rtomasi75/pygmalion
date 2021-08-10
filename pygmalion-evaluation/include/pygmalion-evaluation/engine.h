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
	public:
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::dynamics::engine<typename EVALUATOR::generatorType>(input, output)
		{
			this->template addCommand<command_debugEvaluation<descriptorEvaluation, evaluatorType>>();
			this->template addCommand<command_debugEvaluate<descriptorEvaluation, evaluatorType>>();
			std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ evaluatorType::commands() };
			for (auto& cmd : list)
			{
				this->addCommand(cmd);
			}
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "no game (evaluation only)";
		}
	};
}