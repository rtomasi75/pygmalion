namespace pygmalion
{
	template<typename EVALUATOR, size_t COUNT_SEARCH_PLIES, bool SEARCH_FAILSOFT, bool SEARCH_SCOUT, bool SEARCH_ITERATIVEDEEPENING, size_t COUNT_TT_BUCKETS, bool SEARCH_ASPIRATION, bool HEURISTIC_MOVES, size_t KILLER_MOVES, bool PRUNE_NULLMOVE, typename HEURISTICS>
	class descriptor_search :
		public EVALUATOR::descriptorEvaluation
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = typename EVALUATOR::descriptorEvaluation;
		constexpr static const size_t countSearchPlies{ COUNT_SEARCH_PLIES };
		constexpr static const bool failSoft{ SEARCH_FAILSOFT };
		constexpr static const bool heuristicMoves{ HEURISTIC_MOVES };
		constexpr static const size_t killerMoves{ KILLER_MOVES };
		constexpr static const bool pruneNullmove{ PRUNE_NULLMOVE && evaluatorType::generatorType::hasNullMove() };
		constexpr static const bool searchScout{ SEARCH_SCOUT };
		constexpr static const bool searchIterativeDeepening{ SEARCH_ITERATIVEDEEPENING };
		constexpr static const bool searchTranspositionTable{ COUNT_TT_BUCKETS > 0 };
		constexpr static const size_t searchTranspositionTableBucketCount{ COUNT_TT_BUCKETS};
		constexpr static const bool searchAspiration{ SEARCH_ASPIRATION };
		using variationType = list<typename descriptorEvaluation::movebitsType, countSearchPlies>;
		using depthType = typename variationType::counterType;
		using heuristicsType = HEURISTICS;
	};

}