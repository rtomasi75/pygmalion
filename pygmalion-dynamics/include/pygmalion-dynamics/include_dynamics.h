
using movelistType = typename descriptorDynamics::movelistType;
using indexType = typename descriptorDynamics::indexType;
using motorType = typename descriptorDynamics::motorType;
using scoreType = typename descriptorDynamics::scoreType;

constexpr static const size_t countMaxGeneratedMoves{ descriptorDynamics::countMaxGeneratedMoves };
constexpr static const size_t evaluationMantissa{ descriptorDynamics::evaluationMantissa };
constexpr static const size_t evaluationShift{ descriptorDynamics::evaluationShift };
constexpr static const size_t evaluationMaxDistance{ descriptorDynamics::evaluationMaxDistance };
constexpr static const size_t countPasses{ descriptorDynamics::countPasses };
constexpr static const size_t countTacticalPasses{ descriptorDynamics::countTacticalPasses };

using descriptorMechanics = typename motorType::descriptorMechanics;
#include <pygmalion-mechanics/include_mechanics.h>
