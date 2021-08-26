namespace pygmalion::chess
{
	class heuristics :
		public pygmalion::heuristics<false, descriptor_search, heuristics>
	{
	public:
		heuristics(movegenFeedback& feedback) :
			pygmalion::heuristics<false, descriptor_search, heuristics>(feedback)
		{

		}
	};
}