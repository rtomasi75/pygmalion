#if !defined(PYGMALION_CHESS_EVALUATION)
#define PYGMALION_CHESS_EVALUATION

#include <pygmalion-chess-dynamics.h>
#include <pygmalion-evaluation.h>

#include "pygmalion-chess-evaluation/descriptor_evaluation.h"
#include "pygmalion-chess-evaluation/evaluationstage_control.h"
#include "pygmalion-chess-evaluation/evaluationstage_mobility.h"
#include "pygmalion-chess-evaluation/evaluationstage_attacks.h"
#include "pygmalion-chess-evaluation/evaluationstage_kingsafety.h"
#include "pygmalion-chess-evaluation/evaluationstage_kingareasafety.h"
#include "pygmalion-chess-evaluation/evaluationstage_pawnstructure.h"
#include "pygmalion-chess-evaluation/evaluator.h"
#include "pygmalion-chess-evaluation/commands.h"

#endif