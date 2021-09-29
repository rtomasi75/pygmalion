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
				typename generatorType::contextType context;
				typename generatorType::stackType stack(this->position(), this->history(), this->position().movingPlayer(), &context);
				this->output() << std::endl;
				for (size_t i = 0; i < evaluatorType::countStages; i++)
				{
					const scoreType value{ evaluatorType::stageScore(i,stack) };
					this->output() << evaluatorType::stageName(i) << ": \t" << value << std::endl;
				}
				this->output() << "___________________________________________" << std::endl;
				scoreType eval{ evaluatorType::evaluate(scoreType::minimum(), scoreType::maximum(),stack) };
				this->output() << "total: \t\t" << eval << std::endl;
				this->output() << std::endl;
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