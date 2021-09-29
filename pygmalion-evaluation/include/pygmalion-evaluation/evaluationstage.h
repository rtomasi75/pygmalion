namespace pygmalion
{
	template<typename DESCRIPTION_EVALUATION, typename INSTANCE>
	class evaluationstage :
		public DESCRIPTION_EVALUATION
	{
	public:
		using instanceType = INSTANCE;
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "include_evaluation.h"	
	public:
		constexpr static scoreType computeDelta() noexcept
		{
			return instanceType::computeDelta_Implementation();
		}
		static scoreType evaluate(const typename generatorType::stackType& stack) noexcept
		{
			return instanceType::evaluate_Implementation(stack);
		}
		static std::string name() noexcept
		{
			return instanceType::name_Implementation();
		}
	};
}