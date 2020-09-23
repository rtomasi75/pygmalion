#if !defined(PYGMALION_CHESS_DYNAMICS)
#define PYGMALION_CHESS_DYNAMICS

#include <pygmalion-chess-mechanics.h>
#include <pygmalion-dynamics.h>

#include "pygmalion-chess-dynamics/descriptor_dynamics.h"
#include "pygmalion-chess-dynamics/movegen_knight.h"
#include "pygmalion-chess-dynamics/movegen_pawn_push_white.h"
#include "pygmalion-chess-dynamics/movegen_pawn_push_black.h"
#include "pygmalion-chess-dynamics/movegen_pawn_capture_white.h"
#include "pygmalion-chess-dynamics/movegen_pawn_capture_black.h"
#include "pygmalion-chess-dynamics/movegen_pawn_doublepush_white.h"
#include "pygmalion-chess-dynamics/movegen_pawn_doublepush_black.h"
#include "pygmalion-chess-dynamics/generator.h"
#include "pygmalion-chess-dynamics/commands.h"
#include "pygmalion-chess-dynamics/engine.h"

#endif