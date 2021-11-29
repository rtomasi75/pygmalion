namespace pygmalion::chess
{
	class heuristics;

	constexpr const unsigned int searchOptions
	{	searchFlags::none
		| searchFlags::principalVariationSearch
		| searchFlags::iterativeDeepening
		| searchFlags::staticMoveScores
		| searchFlags::dynamicMoveScores
		| searchFlags::quietKillerMovesHeuristic
		| searchFlags::tacticalKillerMovesHeuristic
		| searchFlags::futilityPruning
		| searchFlags::deltaPruning
		| searchFlags::nullMovePruning
//		| searchFlags::aspirationWindows
		| searchFlags::transpositionTable
//		| searchFlags::allowSelectionSort
//		| searchFlags::lateMoveReductions
	};

	constexpr const size_t countQuietKillerMoveSlots{ 2 };
	constexpr const size_t countTacticalKillerMoveSlots{ 2 };
	constexpr const size_t countTranspositionTableBuckets{ 2 };
	constexpr const size_t killerMovesLookBackDistance{ 1 };
	constexpr const size_t countQs1Plies{ 2 };
	constexpr const size_t countQs2Plies{ 2 };
	constexpr const size_t lateMoveReductionMinPlies{ 2 };
	constexpr const size_t lateMoveReductionMinDepth{ 1 };

	using descriptor_search = pygmalion::descriptor_search<evaluator, 63, searchOptions, countTranspositionTableBuckets, countQuietKillerMoveSlots, countTacticalKillerMoveSlots, killerMovesLookBackDistance, countQs1Plies, countQs2Plies, lateMoveReductionMinPlies, lateMoveReductionMinDepth, heuristics>;
}
