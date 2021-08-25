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
				typename generatorType::stackType stack(this->position(), this->history(), this->position().movingPlayer(), this->dynamicsEngine().feedback());
				scoreType eval{ evaluatorType::evaluate(scoreType::minimum(), scoreType::maximum(),stack) };
				this->output() << "evaluation score: " << eval << std::endl;
				return true;
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