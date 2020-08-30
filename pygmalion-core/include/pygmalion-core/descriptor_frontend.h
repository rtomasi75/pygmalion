namespace pygmalion
{
	template<typename SEARCH>
	class descriptor_frontend :
		public base_search<typename SEARCH::descriptorSearch>
	{
	public:
		using searchType = SEARCH;
		using nodeType = typename searchType::nodeType;
	};

}