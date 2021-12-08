namespace pygmalion::evaluation
{
	template<typename DESCRIPTION_EVALUATION, typename EVALUATOR>
	class command_debugEvaluationParameters :
		public pygmalion::evaluation::command<DESCRIPTION_EVALUATION, EVALUATOR>
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "../include_evaluation.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-evaluationparameters")
			{
				this->output() << std::endl;
				std::vector<scoreType> current = this->evaluationEngine().evaluationParameters();
				std::vector<scoreType> standard;
				std::vector<std::string> names;
				evaluatorType::defaultParameters(standard);
				evaluatorType::parameterNames(names);
				constexpr const size_t n{ evaluatorType::countParameters() };
				for (size_t i = 0; i < n; i++)
					this->output() << names[i] << ": \t" << current[i] << " [" << standard[i] << "]" << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-EVALUATIONPARAMETERS";
		}
	};

}