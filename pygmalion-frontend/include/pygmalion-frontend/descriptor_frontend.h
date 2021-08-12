namespace pygmalion
{
	template<typename NODE>
	class descriptor_frontend :
		public NODE::descriptorSearch
	{
	public:
		using nodeType = NODE;
		using descriptorSearch = typename NODE::descriptorSearch;
	};

}