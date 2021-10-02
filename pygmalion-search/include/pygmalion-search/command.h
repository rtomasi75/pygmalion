namespace pygmalion::search
{
	template<typename GAMETREE>
	class engine;

	template<typename DESCRIPTION_SEARCH, typename GAMETREE>
	class command :
		public pygmalion::evaluation::command<typename DESCRIPTION_SEARCH::descriptorEvaluation, typename DESCRIPTION_SEARCH::evaluatorType>,
		public DESCRIPTION_SEARCH
	{
	public:
		using gametreeType = GAMETREE;
		using parentType = pygmalion::evaluation::command<typename DESCRIPTION_SEARCH::descriptorEvaluation, typename DESCRIPTION_SEARCH::evaluatorType>;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"	
	public:
		typename generatorType::contextType* rootContext() noexcept
		{
			return this->searchEngine().rootContext();
		}
		engine<gametreeType>& searchEngine() noexcept
		{
			return *dynamic_cast<engine<gametreeType>*>(&(this->evaluationEngine()));
		}
		const engine<gametreeType>& searchEngine() const noexcept
		{
			return *dynamic_cast<const engine<gametreeType>*>(&(this->evaluationEngine()));
		}
	protected:
	};
}