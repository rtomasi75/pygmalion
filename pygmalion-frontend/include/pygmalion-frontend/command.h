namespace pygmalion::frontend
{
	template<typename FRONT>
	class engine;

	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command :
		public pygmalion::search::command<typename DESCRIPTION_FRONTEND::descriptorSearch, typename DESCRIPTION_FRONTEND::nodeType>,
		public DESCRIPTION_FRONTEND
	{
	public:
		using frontType = FRONT;
		using parentType = pygmalion::search::command<typename DESCRIPTION_FRONTEND::descriptorSearch, typename DESCRIPTION_FRONTEND::nodeType>;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "include_frontend.h"	
	public:
		constexpr frontType& front() noexcept
		{
			return this->frontendEngine().front();
		}
		constexpr const frontType& front() const noexcept
		{
			return this->frontendEngine().front();
		}
		engine<frontType>& frontendEngine() noexcept
		{
			return *dynamic_cast<engine<frontType>*>(&this->searchEngine());
		}
		const engine<frontType>& frontendEngine() const noexcept
		{
			return *dynamic_cast<const engine<frontType>*>(&this->searchEngine());
		}
	protected:
	};
}