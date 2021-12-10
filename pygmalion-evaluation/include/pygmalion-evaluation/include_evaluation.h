
using generatorType = typename descriptorEvaluation::generatorType;
using evaluationType = typename descriptorEvaluation::evaluationType;
using parameterType = typename descriptorEvaluation::parameterType;
constexpr static const size_t evaluationMantissa{ descriptorEvaluation::evaluationMantissa };
constexpr static const size_t evaluationShift{ descriptorEvaluation::evaluationShift };
constexpr static const size_t evaluationMaxDistance{ descriptorEvaluation::evaluationMaxDistance };

using descriptorDynamics = typename generatorType::descriptorDynamics;
#include <pygmalion-dynamics/include_dynamics.h>
