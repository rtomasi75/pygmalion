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
		template<size_t PLAYER>
		static scoreType evaluate(const typename generatorType::template stackType<PLAYER>& stack) noexcept
		{
			return instanceType::template evaluate_Implementation<PLAYER>(stack);
		}
		static std::string name() noexcept
		{
			return instanceType::name_Implementation();
		}
	};
}