namespace pygmalion
{
	class searchFlags
	{
	public:
		constexpr static const unsigned int none{ 0 };
		constexpr static const unsigned int principalVariationSearch{ 1 };
		constexpr static const unsigned int iterativeDeepening{ 2 };
		constexpr static const unsigned int historyHeuristic{ 4 };
		constexpr static const unsigned int quietKillerMovesHeuristic{ 8 };
		constexpr static const unsigned int tacticalKillerMovesHeuristic{ 16 };
		constexpr static const unsigned int futilityPruning{ 32 };
		constexpr static const unsigned int nullMovePruning{ 64 };
		constexpr static const unsigned int aspirationWindows{ 128 };
		constexpr static const unsigned int transpositionTable{ 256 };
		constexpr static const unsigned int deltaPruning{ 512 };
	};


	template<typename EVALUATOR, size_t COUNT_SEARCH_PLIES, unsigned int SEARCH_FLAGS, size_t COUNT_TT_BUCKETS, size_t KILLER_MOVES_QUIET, size_t KILLER_MOVES_TACTICAL, size_t KILLER_LOOKBACK_DISTANCE, typename HEURISTICS>
	class descriptor_search :
		public EVALUATOR::descriptorEvaluation
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = typename EVALUATOR::descriptorEvaluation;
		constexpr static const size_t countSearchPlies{ COUNT_SEARCH_PLIES };
		constexpr static const bool heuristicMoves{ (SEARCH_FLAGS & searchFlags::historyHeuristic) != 0 };
		constexpr static const size_t quietKillerMoves{ ((SEARCH_FLAGS & searchFlags::quietKillerMovesHeuristic) != 0) ? KILLER_MOVES_QUIET : 0 };
		constexpr static const size_t killerLookBackDistance{ KILLER_LOOKBACK_DISTANCE };
		constexpr static const size_t tacticalKillerMoves{ ((SEARCH_FLAGS & searchFlags::tacticalKillerMovesHeuristic) != 0) ? KILLER_MOVES_TACTICAL : 0 };
		constexpr static const bool pruneNullmove{ ((SEARCH_FLAGS & searchFlags::nullMovePruning) != 0) && evaluatorType::generatorType::hasNullMove() };
		constexpr static const bool pruneFutility{ (SEARCH_FLAGS & searchFlags::futilityPruning) != 0 };
		constexpr static const bool pruneDelta{ (SEARCH_FLAGS & searchFlags::deltaPruning) != 0 };
		constexpr static const bool searchScout{ (SEARCH_FLAGS & searchFlags::principalVariationSearch) != 0 };
		constexpr static const bool searchIterativeDeepening{ (SEARCH_FLAGS & searchFlags::iterativeDeepening) != 0 };
		constexpr static const bool searchTranspositionTable{ (SEARCH_FLAGS & searchFlags::transpositionTable) != 0 };
		constexpr static const size_t searchTranspositionTableBucketCount{ COUNT_TT_BUCKETS };
		constexpr static const bool searchAspiration{ (SEARCH_FLAGS & searchFlags::aspirationWindows) != 0 };
		using variationType = list<typename descriptorEvaluation::movebitsType, countSearchPlies>;
		using depthType = typename variationType::counterType;
		using heuristicsType = HEURISTICS;
		using moveinfoType = moveinfo<descriptorEvaluation>;
		using ttmovesType = list<typename descriptorEvaluation::movebitsType, searchTranspositionTableBucketCount>;
		using quietKillermovesType = list<typename descriptorEvaluation::movebitsType, quietKillerMoves + quietKillerMoves * killerLookBackDistance>;
		using tacticalKillermovesType = list<typename descriptorEvaluation::movebitsType, tacticalKillerMoves + tacticalKillerMoves * killerLookBackDistance>;
	};

}