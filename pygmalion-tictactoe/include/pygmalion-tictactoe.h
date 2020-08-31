#if !defined(PYGMALION_TICTACTOE)
#define PYGMALION_TICTACTOE

#include <pygmalion-core.h>

#include <utility>
#include <cstdint>
#include <cassert>
#include <vector>
#include <sstream>
#include <mutex>


#include <pygmalion-tictactoe/descriptor_board.h>
#include <pygmalion-tictactoe/board.h>
#include <pygmalion-tictactoe/descriptor_mechanics.h>
#include <pygmalion-tictactoe/mechanics.h>
#include <pygmalion-tictactoe/movemagic.h>
#include <pygmalion-tictactoe/descriptor_generator.h>
#include <pygmalion-tictactoe/generator.h>
#include <pygmalion-tictactoe/descriptor_evaluation.h>
#include <pygmalion-tictactoe/patterns.h>
#include <pygmalion-tictactoe/evaluation.h>
#include <pygmalion-tictactoe/heuristics.h>
#include <pygmalion-tictactoe/descriptor_search.h>
#include <pygmalion-tictactoe/search.h>
#include <pygmalion-tictactoe/descriptor_frontend.h>
#include <pygmalion-tictactoe/frontend.h>
#include <pygmalion-tictactoe/engine.h>

#endif