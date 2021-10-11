

using evaluatorType = typename descriptorSearch::evaluatorType;
using descriptorEvaluation = typename descriptorSearch::descriptorEvaluation;
using variationType = typename descriptorSearch::variationType;
using depthType = typename descriptorSearch::depthType;
using heuristicsType = typename descriptorSearch::heuristicsType;
using moveinfoType = typename descriptorSearch::moveinfoType;
using ttmovesType = typename descriptorSearch::ttmovesType;
using quietKillermovesType = typename descriptorSearch::quietKillermovesType;
using tacticalKillermovesType = typename descriptorSearch::tacticalKillermovesType;

constexpr static const size_t countSearchPlies{ descriptorSearch::countSearchPlies };
constexpr static const bool heuristicMoves{ descriptorSearch::heuristicMoves };
constexpr static const size_t quietKillerMoves{ descriptorSearch::quietKillerMoves };
constexpr static const size_t tacticalKillerMoves{ descriptorSearch::tacticalKillerMoves };
constexpr static const bool pruneNullmove{ descriptorSearch::pruneNullmove };
constexpr static const bool searchScout{ descriptorSearch::searchScout };
constexpr static const bool searchIterativeDeepening{ descriptorSearch::searchIterativeDeepening };
constexpr static const bool searchTranspositionTable{ descriptorSearch::searchTranspositionTable };
constexpr static const bool searchAspiration{ descriptorSearch::searchAspiration };
constexpr static const size_t searchTranspositionTableBucketCount{ descriptorSearch::searchTranspositionTableBucketCount };
constexpr static const bool pruneFutility{ descriptorSearch::pruneFutility };
constexpr static const bool pruneDelta{ descriptorSearch::pruneDelta };
constexpr static const size_t killerLookBackDistance{ descriptorSearch::killerLookBackDistance };

#include <pygmalion-evaluation/include_evaluation.h>
