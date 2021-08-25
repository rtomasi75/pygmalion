namespace pygmalion
{
	template<typename EVALUATOR, size_t COUNT_SEARCH_PLIES,bool FAIL_SOFT, typename HEURISTICS>
	class descriptor_search :
		public EVALUATOR::descriptorEvaluation
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = typename EVALUATOR::descriptorEvaluation;
		constexpr static const size_t countSearchPlies{ COUNT_SEARCH_PLIES };
		constexpr static const bool failSoft{ FAIL_SOFT };
		using variationType = list<typename descriptorEvaluation::movebitsType, countSearchPlies>;
		using depthType = typename variationType::counterType;
		using heuristicsType = HEURISTICS;
	};

}