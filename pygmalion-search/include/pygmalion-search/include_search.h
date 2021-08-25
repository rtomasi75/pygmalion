

using evaluatorType = typename descriptorSearch::evaluatorType;
using descriptorEvaluation = typename descriptorSearch::descriptorEvaluation;
using variationType = typename descriptorSearch::variationType;
using depthType = typename descriptorSearch::depthType;
using heuristicsType = typename descriptorSearch::heuristicsType;

constexpr static const size_t countSearchPlies{ descriptorSearch::countSearchPlies };
constexpr static const bool failSoft{ descriptorSearch::failSoft };

#include <pygmalion-evaluation/include_evaluation.h>
