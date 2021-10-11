namespace pygmalion::chess
{
	class heuristics;

	constexpr const unsigned int searchOptions
	{	searchFlags::none
		| searchFlags::principalVariationSearch
		| searchFlags::iterativeDeepening
		| searchFlags::historyHeuristic
		| searchFlags::quietKillerMovesHeuristic
		| searchFlags::tacticalKillerMovesHeuristic
		| searchFlags::futilityPruning
//		| searchFlags::deltaPruning
		| searchFlags::nullMovePruning
		| searchFlags::aspirationWindows
		| searchFlags::transpositionTable
	};

	constexpr const size_t countQuietKillerMoveSlots{ 2 };
	constexpr const size_t countTacticalKillerMoveSlots{ 2 };
	constexpr const size_t countTranspositionTableBuckets{ 2 };
	constexpr const size_t killerMovesLookBackDistance{ 1 };

	using descriptor_search = pygmalion::descriptor_search<evaluator, 31, searchOptions, countTranspositionTableBuckets, countQuietKillerMoveSlots, countTacticalKillerMoveSlots, killerMovesLookBackDistance, heuristics>;
}
