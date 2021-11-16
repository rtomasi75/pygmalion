namespace pygmalion::tictactoe
{
	class heuristics;

	constexpr const unsigned int searchOptions
	{ searchFlags::none
		| searchFlags::principalVariationSearch
		| searchFlags::iterativeDeepening
		| searchFlags::staticMoveScores
		| searchFlags::quietKillerMovesHeuristic
		| searchFlags::tacticalKillerMovesHeuristic
		| searchFlags::aspirationWindows
		| searchFlags::transpositionTable
	};

	constexpr const size_t countQuietKillerMoveSlots{ 1 };
	constexpr const size_t countTacticalKillerMoveSlots{ 0 };
	constexpr const size_t countTranspositionTableBuckets{ 1 };
	constexpr const size_t killerMovesLookBackDistance{ 1 };

	using descriptor_search = pygmalion::descriptor_search<evaluator, 10, searchOptions, countTranspositionTableBuckets, countQuietKillerMoveSlots, countTacticalKillerMoveSlots, killerMovesLookBackDistance, 3, heuristics>;
}
