
using movelistType = typename descriptorDynamics::movelistType;
using indexType = typename descriptorDynamics::indexType;
using motorType = typename descriptorDynamics::motorType;
using scorelistType = typename descriptorDynamics::scorelistType;
using passType = typename descriptorDynamics::passType;
using passlistType = typename descriptorDynamics::passlistType;
using stageType = typename descriptorDynamics::stageType;
using stagelistType = typename descriptorDynamics::stagelistType;
using heuristicScore = typename descriptorDynamics::heuristicScore;

constexpr static const size_t countMaxGeneratedMoves{ descriptorDynamics::countMaxGeneratedMoves };

using descriptorMechanics = typename motorType::descriptorMechanics;
#include <pygmalion-mechanics/include_mechanics.h>
