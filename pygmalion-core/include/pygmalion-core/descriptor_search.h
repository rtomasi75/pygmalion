namespace pygmalion
{
	template<typename EVALUATION, int COUNT_SEARCH_PLIES, typename HEURISTICS>
	class descriptor_search :
		public base_evaluation<typename EVALUATION::descriptorEvaluation>
	{
	public:
		constexpr static int countSearchPlies{ COUNT_SEARCH_PLIES };
		using evaluationType = EVALUATION;
		using variationType = list<typename evaluationType::moveType, countSearchPlies>;
		using depthType = typename variationType::counterType;
		using heuristicsType = HEURISTICS;
		using multiscoreType = multiscore<evaluationType>;
	};

}