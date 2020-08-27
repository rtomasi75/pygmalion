#if !defined(PYGMALION_CHESS)
#define PYGMALION_CHESS

#include <pygmalion-core.h>

#include <utility>
#include <cstdint>
#include <cassert>
#include <sstream>
#include <mutex>

//#define PYGMALION_CHESS_DEBUG_PAWNMOVEMAP

#include "pygmalion-chess/score.h"
#include "pygmalion-chess/board.h"
#include "pygmalion-chess/slidermagic.h"
#include "pygmalion-chess/movegenTables.h"
#include "pygmalion-chess/movegen.h"
#include "pygmalion-chess/evaluationTables.h"
#include "pygmalion-chess/evaluator.h"
#include "pygmalion-chess/frontend.h"
#include "pygmalion-chess/engine.h"

#endif