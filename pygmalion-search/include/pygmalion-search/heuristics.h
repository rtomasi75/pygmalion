namespace pygmalion
{
	template<typename DESCRIPTION_SEARCH, bool VERBOSE>
	class heuristics :
		public searchtable<VERBOSE, DESCRIPTION_SEARCH, heuristics<DESCRIPTION_SEARCH, VERBOSE>>
	{
	public:
	};

}