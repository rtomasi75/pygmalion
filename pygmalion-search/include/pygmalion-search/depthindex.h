namespace pygmalion
{

	template<typename DESCRIPTION_SEARCH>
	class depthindex :
		public DESCRIPTION_SEARCH
	{
	public:
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"
	private:
		depthType m_DepthRemaining;
	};
}