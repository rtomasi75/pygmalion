namespace pygmalion::search
{
	template<typename NODE>
	class engine;

	template<typename DESCRIPTION_SEARCH, typename NODE>
	class command :
		public pygmalion::dynamics::command<typename DESCRIPTION_SEARCH::descriptorEvaluation, typename DESCRIPTION_SEARCH::objectiveType>,
		public DESCRIPTION_SEARCH
	{
	public:
		using nodeType = NODE;
		using parentType = pygmalion::dynamics::command<typename DESCRIPTION_SEARCH::descriptorEvaluation, typename DESCRIPTION_SEARCH::objectiveType>;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"	
	public:
		engine<nodeType>& searchEngine() noexcept
		{
			return dynamic_cast<engine<nodeType>&>(this->evaluationEngine());
		}
		const engine<nodeType>& evaluationEngine() const noexcept
		{
			return dynamic_cast<const engine<nodeType>&>(this->evaluationEngine());
		}
	protected:
	};
}