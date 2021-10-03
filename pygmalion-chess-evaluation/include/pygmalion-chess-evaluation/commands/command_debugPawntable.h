namespace pygmalion::chess::evaluation
{
	class command_debugPawntable :
		public pygmalion::evaluation::command<descriptor_evaluation, evaluator>
	{
	public:
		using evaluatorType = evaluator;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorEvaluation = descriptor_evaluation;
#include <pygmalion-evaluation/include_evaluation.h>
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override;
		virtual std::string help() noexcept override
		{
			return "DEBUG-PAWNTABLE";
		}
	};

}