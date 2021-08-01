namespace pygmalion::evaluation
{
	template<typename DESCRIPTION_EVALUATION, typename EVALUATOR>
	class command_debugEvaluate :
		public pygmalion::evaluation::command<DESCRIPTION_EVALUATION, EVALUATOR>
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "../include_evaluation.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-evaluate")
			{
				evaluationType eval{ evaluatorType::evaluate(this->position()) };
				this->output() << "objective score: " << eval << std::endl;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-EVALUATE";
		}
	};

}