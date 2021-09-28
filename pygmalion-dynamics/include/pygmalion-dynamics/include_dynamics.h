
using movelistType = typename descriptorDynamics::movelistType;
using indexType = typename descriptorDynamics::indexType;
using motorType = typename descriptorDynamics::motorType;
using scoreType = typename descriptorDynamics::scoreType;

constexpr static const size_t countMaxGeneratedMoves{ descriptorDynamics::countMaxGeneratedMoves };
constexpr static const size_t evaluationMantissa{ descriptorDynamics::evaluationMantissa };
constexpr static const size_t evaluationShift{ descriptorDynamics::evaluationShift };
constexpr static const size_t evaluationMaxDistance{ descriptorDynamics::evaluationMaxDistance };
constexpr static const size_t countPasses{ descriptorDynamics::countPasses };
constexpr static const size_t countCriticalPasses{ descriptorDynamics::countCriticalPasses };
constexpr static const size_t countTacticalPasses{ descriptorDynamics::countTacticalPasses };
constexpr static const size_t countQuietCriticalPasses{ descriptorDynamics::countQuietCriticalPasses };
constexpr static const size_t countCriticalEvasionPasses{ descriptorDynamics::countCriticalEvasionPasses };
constexpr static const size_t countTacticalCriticalEvasionPasses{ descriptorDynamics::countTacticalCriticalEvasionPasses };

using descriptorMechanics = typename motorType::descriptorMechanics;
#include <pygmalion-mechanics/include_mechanics.h>
