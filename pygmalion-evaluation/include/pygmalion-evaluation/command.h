namespace pygmalion::evaluation
{
	template<typename EVALUATOR>
	class engine;

	template<typename DESCRIPTION_EVALUATION, typename EVALUATOR>
	class command :
		public pygmalion::dynamics::command<typename DESCRIPTION_EVALUATION::descriptorDynamics, typename DESCRIPTION_EVALUATION::generatorType>,
		public DESCRIPTION_EVALUATION
	{
	public:
		using evaluatorType = EVALUATOR;
		using parentType = pygmalion::dynamics::command<typename DESCRIPTION_EVALUATION::descriptorDynamics, typename DESCRIPTION_EVALUATION::generatorType>;
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "include_evaluation.h"	
	public:
		engine<evaluatorType>& evaluationEngine() noexcept
		{
			return dynamic_cast<engine<evaluatorType>&>(this->dynamicsEngine());
		}
		const engine<evaluatorType>& evaluationEngine() const noexcept
		{
			return dynamic_cast<const engine<evaluatorType>&>(this->dynamicsEngine());
		}
	protected:
	};
}