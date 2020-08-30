namespace pygmalion
{
	template<typename DESCRIPTOR_SEARCH>
	class base_search :
		public DESCRIPTOR_SEARCH
	{
	public:
		using descriptorSearch = DESCRIPTOR_SEARCH;
	};
}