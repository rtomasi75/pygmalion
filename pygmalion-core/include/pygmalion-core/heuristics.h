namespace pygmalion
{
	template<typename DESCRIPTION_MECHANICS, bool VERBOSE>
	class heuristics :
		public searchtable<VERBOSE, DESCRIPTION_MECHANICS, heuristics<DESCRIPTION_MECHANICS, VERBOSE>>
	{
	public:
	};

}