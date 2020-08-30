#if !defined(PYGMALION_CHESS)
#define PYGMALION_CHESS

#include <pygmalion-core.h>

#include <utility>
#include <cstdint>
#include <cassert>
#include <sstream>
#include <mutex>

#include "pygmalion-chess/score.h"
#include <pygmalion-chess/descriptor_board.h>
#include "pygmalion-chess/board.h"
#include <pygmalion-chess/descriptor_mechanics.h>
#include "pygmalion-chess/mechanics.h"
#include "pygmalion-chess/slidermagic.h"
#include "pygmalion-chess/generatorTables.h"
#include <pygmalion-chess/descriptor_generator.h>
#include "pygmalion-chess/stack.h"
#include "pygmalion-chess/generator.h"
#include "pygmalion-chess/evaluationTables.h"
#include "pygmalion-chess/evaluator.h"
#include "pygmalion-chess/frontend.h"
#include "pygmalion-chess/engine.h"

#endif