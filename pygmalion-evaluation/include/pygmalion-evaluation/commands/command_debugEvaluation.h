namespace pygmalion::evaluation
{
	template<typename DESCRIPTION_EVALUATION, typename EVALUATOR>
	class command_debugEvaluation :
		public pygmalion::evaluation::command<DESCRIPTION_EVALUATION, EVALUATOR>
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "../include_evaluation.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-evaluation")
			{
				this->output() << std::endl;
				this->output() << "evaluation: " << std::setw(4) << sizeof(evaluationType) << " = " << sizeof(evaluationType) * CHAR_BIT << "bit" << std::endl;
				this->output() << std::endl;
				this->output() << "mantissa: " << std::setw(4) << evaluationMantissa << std::endl;
				this->output() << "shift:    " << std::setw(4) << evaluationShift << std::endl;
				this->output() << "distance: " << std::setw(4) << evaluationMaxDistance << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-EVALUATION";
		}
	};

}