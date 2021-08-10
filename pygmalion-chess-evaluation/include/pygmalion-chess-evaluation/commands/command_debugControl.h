namespace pygmalion::chess::evaluation
{
	class command_debugControl :
		public pygmalion::evaluation::command<descriptor_evaluation, evaluator>
	{
	public:
		using evaluatorType = evaluator;
		using stackType = typename generatorType::stackType;
		using descriptorEvaluation = descriptor_evaluation;
#include <pygmalion-evaluation/include_evaluation.h>
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override;
		virtual std::string help() noexcept override
		{
			return "DEBUG-CONTROL";
		}
	};

}