
using movelistType = typename descriptorDynamics::movelistType;
using indexType = typename descriptorDynamics::indexType;
using motorType = typename descriptorDynamics::motorType;
using scoreType = typename descriptorDynamics::scoreType;
using scorelistType = typename descriptorDynamics::scorelistType;
using passType = typename descriptorDynamics::passType;
using passlistType = typename descriptorDynamics::passlistType;
using stageType = typename descriptorDynamics::stageType;
using stagelistType = typename descriptorDynamics::stagelistType;

constexpr static const size_t countMaxGeneratedMoves{ descriptorDynamics::countMaxGeneratedMoves };
constexpr static const size_t countMovegenStages{ descriptorDynamics::countMovegenStages };
constexpr static const size_t evaluationMantissa{ descriptorDynamics::evaluationMantissa };
constexpr static const size_t evaluationShift{ descriptorDynamics::evaluationShift };
constexpr static const size_t evaluationMaxDistance{ descriptorDynamics::evaluationMaxDistance };
constexpr static const inline std::array<size_t, countMovegenStages> countMovegenPasses{ descriptorDynamics::countMovegenPasses };
constexpr static const size_t movegenStage_AllMoves{ descriptorDynamics::movegenStage_AllMoves };
constexpr static const size_t movegenStage_TacticalMoves{ descriptorDynamics::movegenStage_TacticalMoves };
constexpr static const size_t movegenStage_CriticalMoves{ descriptorDynamics::movegenStage_CriticalMoves };
constexpr static const size_t movegenStage_QuietCriticalMoves{ descriptorDynamics::movegenStage_QuietCriticalMoves };
constexpr static const size_t movegenStage_CriticalEvasionMoves{ descriptorDynamics::movegenStage_CriticalEvasionMoves };
constexpr static const size_t movegenStage_TacticalCriticalEvasionMoves{ descriptorDynamics::movegenStage_TacticalCriticalEvasionMoves };
constexpr static const size_t movegenStage_WinningMoves{ descriptorDynamics::movegenStage_WinningMoves };
constexpr static const size_t movegenStage_EqualMoves{ descriptorDynamics::movegenStage_EqualMoves };
constexpr static const size_t movegenStage_LosingMoves{ descriptorDynamics::movegenStage_LosingMoves };
constexpr static const size_t movegenStage_QuietMoves{ descriptorDynamics::movegenStage_QuietMoves };
constexpr static const size_t maxCountPasses{ descriptorDynamics::maxCountPasses };

using descriptorMechanics = typename motorType::descriptorMechanics;
#include <pygmalion-mechanics/include_mechanics.h>
