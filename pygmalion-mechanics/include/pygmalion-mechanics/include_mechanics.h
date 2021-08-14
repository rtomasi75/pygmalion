
using moveType = typename descriptorMechanics::moveType;
using movedataType = typename descriptorMechanics::movedataType;
using boardType = typename descriptorMechanics::boardType;
using movebitsType = typename descriptorMechanics::movebitsType;
constexpr static const size_t countMoveBits{ descriptorMechanics::countMoveBits };
constexpr static const size_t countBitsBloomfilter{ descriptorMechanics::countBitsBloomfilter };
constexpr static const size_t countValuesBloomfilter{ descriptorMechanics::countValuesBloomfilter };
using historyType = typename descriptorMechanics::historyType;
using bloomfilterType = typename descriptorMechanics::bloomfilterType;
using gameType=typename descriptorMechanics::gameType;

using descriptorState = typename descriptorMechanics::descriptorState;
#include <pygmalion-state/include_state.h>
