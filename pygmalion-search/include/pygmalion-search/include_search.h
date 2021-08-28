

using evaluatorType = typename descriptorSearch::evaluatorType;
using descriptorEvaluation = typename descriptorSearch::descriptorEvaluation;
using variationType = typename descriptorSearch::variationType;
using depthType = typename descriptorSearch::depthType;
using heuristicsType = typename descriptorSearch::heuristicsType;

constexpr static const size_t countSearchPlies{ descriptorSearch::countSearchPlies };
constexpr static const bool failSoft{ descriptorSearch::failSoft };
constexpr static const bool heuristicMoves{ descriptorSearch::heuristicMoves };
constexpr static const size_t killerMoves{ descriptorSearch::killerMoves };

#include <pygmalion-evaluation/include_evaluation.h>
