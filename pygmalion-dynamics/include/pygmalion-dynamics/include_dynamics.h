
constexpr static const size_t countMaxGeneratedMoves{ descriptorDynamics::countMaxGeneratedMoves };
constexpr static const size_t countBitsBloomfilter{ descriptorDynamics::countBitsBloomfilter };
constexpr static const size_t countValuesBloomfilter{ descriptorDynamics::countValuesBloomfilter };
using movelistType = typename descriptorDynamics::movelistType;
using indexType = typename descriptorDynamics::indexType;
using motorType = typename descriptorDynamics::motorType;
using bloomfilterType = typename descriptorDynamics::bloomfilterType;

using descriptorMechanics = typename motorType::descriptorMechanics;
#include <pygmalion-mechanics/include_mechanics.h>
