
using generatorType = typename descriptorEvaluation::generatorType;
using scoreType = typename descriptorEvaluation::scoreType;

constexpr static const size_t evaluationMantissa{ descriptorEvaluation::evaluationMantissa };
constexpr static const size_t evaluationShift{ descriptorEvaluation::evaluationShift };
constexpr static const size_t evaluationMaxDistance{ descriptorEvaluation::evaluationMaxDistance };

using descriptorDynamics = typename generatorType::descriptorDynamics;
#include <pygmalion-dynamics/include_dynamics.h>
