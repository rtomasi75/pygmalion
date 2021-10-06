namespace pygmalion
{
	template<typename EVALUATOR, size_t COUNT_SEARCH_PLIES, bool SEARCH_SCOUT, bool SEARCH_ITERATIVEDEEPENING, size_t COUNT_TT_BUCKETS, bool SEARCH_ASPIRATION, bool HEURISTIC_MOVES, size_t KILLER_MOVES_QUIET, size_t KILLER_MOVES_TACTICAL, size_t KILLER_LOOKBACK_DISTANCE, bool PRUNE_NULLMOVE,bool PRUNE_FUTILITY, typename HEURISTICS>
	class descriptor_search :
		public EVALUATOR::descriptorEvaluation
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = typename EVALUATOR::descriptorEvaluation;
		constexpr static const size_t countSearchPlies{ COUNT_SEARCH_PLIES };
		constexpr static const bool heuristicMoves{ HEURISTIC_MOVES };
		constexpr static const size_t quietKillerMoves{ KILLER_MOVES_QUIET };
		constexpr static const size_t killerLookBackDistance{ KILLER_LOOKBACK_DISTANCE };
		constexpr static const size_t tacticalKillerMoves{ KILLER_MOVES_TACTICAL };
		constexpr static const bool pruneNullmove{ PRUNE_NULLMOVE && evaluatorType::generatorType::hasNullMove() };
		constexpr static const bool pruneFutility{ PRUNE_FUTILITY };
		constexpr static const bool searchScout{ SEARCH_SCOUT };
		constexpr static const bool searchIterativeDeepening{ SEARCH_ITERATIVEDEEPENING };
		constexpr static const bool searchTranspositionTable{ COUNT_TT_BUCKETS > 0 };
		constexpr static const size_t searchTranspositionTableBucketCount{ COUNT_TT_BUCKETS};
		constexpr static const bool searchAspiration{ SEARCH_ASPIRATION };
		using variationType = list<typename descriptorEvaluation::movebitsType, countSearchPlies>;
		using depthType = typename variationType::counterType;
		using heuristicsType = HEURISTICS;
		using moveinfoType = moveinfo<descriptorEvaluation>;
		using ttmovesType = list<typename descriptorEvaluation::movebitsType, searchTranspositionTableBucketCount>;
		using quietKillermovesType = list<typename descriptorEvaluation::movebitsType, quietKillerMoves + quietKillerMoves * killerLookBackDistance>;
		using tacticalKillermovesType = list<typename descriptorEvaluation::movebitsType, tacticalKillerMoves + tacticalKillerMoves * killerLookBackDistance>;
	};

}