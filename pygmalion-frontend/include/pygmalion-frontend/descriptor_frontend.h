namespace pygmalion
{
	template<typename GAMETREE>
	class descriptor_frontend :
		public GAMETREE::descriptorSearch
	{
	public:
		using gametreeType = GAMETREE;
		using descriptorSearch = typename gametreeType::descriptorSearch;
		using recordType = record<typename descriptorSearch::descriptorDynamics, typename descriptorSearch::generatorType>;
	};

}