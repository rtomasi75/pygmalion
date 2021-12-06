namespace pygmalion
{
	template<typename DESCRIPTION_EVALUATION, typename INSTANCE, typename DATATYPE>
	class evaluationstage :
		public DESCRIPTION_EVALUATION
	{
	public:
		using instanceType = INSTANCE;
		using dataType = DATATYPE;
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "include_evaluation.h"	
	public:
		constexpr static size_t getParameterCount() noexcept
		{
			return instanceType::getParameterCount_Implementation();
		}
		static parameter getParameter(const size_t index) noexcept
		{
			return instanceType::getParameter_Implementation(index);
		}
		constexpr static deltaType computeDelta(const scoreType* pParameters) noexcept
		{
			return instanceType::computeDelta_Implementation(pParameters);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static void computeData(const typename generatorType::template stackType<PLAYER>& stack, dataType& data) noexcept
		{
			instanceType::template computeData_Implementation<PLAYER>(stack, data);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType evaluate(const dataType& data, const scoreType* pParameters) noexcept
		{
			return instanceType::template evaluate_Implementation<PLAYER>(data, pParameters);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType differentiate(const dataType, const size_t parameterIndex, const scoreType* pParameters) noexcept
		{
			return instanceType::template differentiate_Implementation<PLAYER>(data, parameterIndex, pParameters);
		}
		static std::string name() noexcept
		{
			return instanceType::name_Implementation();
		}
	};
}