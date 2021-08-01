namespace pygmalion
{
	template<typename DESCRIPTOR_EVALUATION, typename INSTANCE >
	class evaluator :
		public DESCRIPTOR_EVALUATION
	{
	public:
		using evaluatorType = INSTANCE;
		using descriptorEvaluation = DESCRIPTOR_EVALUATION;
		#include "include_evaluation.h"
	public:
		static evaluationType evaluate(const boardType& position) noexcept
		{
			return evaluatorType::evaluate_Implementation(position);
		}
	};
} 