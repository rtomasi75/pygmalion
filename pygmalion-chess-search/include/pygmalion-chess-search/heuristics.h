namespace pygmalion::chess
{
	class heuristics :
		public pygmalion::heuristics<false, descriptor_search, heuristics>
	{
	public:
		heuristics() :
			pygmalion::heuristics<false, descriptor_search, heuristics>()
		{

		}
	};
}