namespace pygmalion
{
	class searchFlags
	{
	public:
		constexpr static const unsigned int none{ 0 };
		constexpr static const unsigned int principalVariationSearch{ 1 };
		constexpr static const unsigned int iterativeDeepening{ 2 };
		constexpr static const unsigned int staticMoveScores{ 4 };
		constexpr static const unsigned int quietKillerMovesHeuristic{ 8 };
		constexpr static const unsigned int tacticalKillerMovesHeuristic{ 16 };
		constexpr static const unsigned int futilityPruning{ 32 };
		constexpr static const unsigned int nullMovePruning{ 64 };
		constexpr static const unsigned int aspirationWindows{ 128 };
		constexpr static const unsigned int transpositionTable{ 256 };
		constexpr static const unsigned int deltaPruning{ 512 };
		constexpr static const unsigned int dynamicMoveScores{ 1024 };
		constexpr static const unsigned int lateMoveReductions{ 2048 };
		constexpr static const unsigned int allowSelectionSort{ 4096 };
	};


	template<typename EVALUATOR, size_t COUNT_SEARCH_PLIES, unsigned int SEARCH_FLAGS, size_t COUNT_TT_BUCKETS, size_t KILLER_MOVES_QUIET, size_t KILLER_MOVES_TACTICAL, size_t KILLER_LOOKBACK_DISTANCE, size_t COUNT_MAX_EXTENSION, size_t COUNT_LATEMOVE_REDUCTION, size_t LATEMOVE_REDUCTION_MINDEPTH, typename HEURISTICS>
	class descriptor_search :
		public EVALUATOR::descriptorEvaluation
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = typename EVALUATOR::descriptorEvaluation;
		constexpr static const size_t countSearchPlies{ COUNT_SEARCH_PLIES };
		constexpr static const size_t lateMoveReductionPlies{ COUNT_LATEMOVE_REDUCTION };
		constexpr static const size_t lateMoveReductionMinDepth{ LATEMOVE_REDUCTION_MINDEPTH };
		constexpr static const bool allowSelectionSort{ (SEARCH_FLAGS & searchFlags::allowSelectionSort) != 0 };
		constexpr static const bool lateMoveReductions{ (SEARCH_FLAGS & searchFlags::lateMoveReductions) != 0 };
		constexpr static const bool staticMoveScores{ (SEARCH_FLAGS & searchFlags::staticMoveScores) != 0 };
		constexpr static const bool dynamicMoveScores{ (SEARCH_FLAGS & searchFlags::dynamicMoveScores) != 0 };
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
		constexpr static const depthType countMaxExtensions{ depthType(COUNT_MAX_EXTENSION) };
		using heuristicsType = HEURISTICS;
		using moveinfoType = moveinfo<descriptorEvaluation>;
		using ttmovesType = list<typename descriptorEvaluation::movebitsType, searchTranspositionTableBucketCount>;
		using quietKillermovesType = list<typename descriptorEvaluation::movebitsType, quietKillerMoves + quietKillerMoves * killerLookBackDistance>;
		using tacticalKillermovesType = list<typename descriptorEvaluation::movebitsType, tacticalKillerMoves + tacticalKillerMoves * killerLookBackDistance>;
		using knuthType = std::int8_t;
		using nodecounterType = std::uint64_t;
		using nodecountlistType = list<nodecounterType, descriptorEvaluation::countMaxGeneratedMoves>;
		using quietkillernodecountlistType = list<nodecounterType, quietKillerMoves + quietKillerMoves * killerLookBackDistance>;
		using tacticalkillernodecountlistType = list<nodecounterType, tacticalKillerMoves + tacticalKillerMoves * killerLookBackDistance>;
		using ttnodecountlistType = list<nodecounterType, searchTranspositionTableBucketCount>;
		constexpr static const knuthType PVSnode{ 0 };
		constexpr static const knuthType CUTnode{ 1 };
		constexpr static const knuthType ALLnode{ -1 };
	};

}