#if !defined(PYGMALION_CHESS_DYNAMICS)
#define PYGMALION_CHESS_DYNAMICS

#include <pygmalion-chess-mechanics.h>
#include <pygmalion-dynamics.h>

#include "pygmalion-chess-dynamics/descriptor_dynamics.h"
#include "pygmalion-chess-dynamics/rays.h"
#include "pygmalion-chess-dynamics/movegen_knight.h"
#include "pygmalion-chess-dynamics/movegen_pawn_push_white.h"
#include "pygmalion-chess-dynamics/movegen_pawn_push_black.h"
#include "pygmalion-chess-dynamics/movegen_pawn_capture_white.h"
#include "pygmalion-chess-dynamics/movegen_pawn_capture_black.h"
#include "pygmalion-chess-dynamics/movegen_pawn_doublepush_white.h"
#include "pygmalion-chess-dynamics/movegen_pawn_doublepush_black.h"
#include "pygmalion-chess-dynamics/movegen_pawn_promotion_white.h"
#include "pygmalion-chess-dynamics/movegen_pawn_promotion_black.h"
#include "pygmalion-chess-dynamics/movegen_pawn_promocapture_white.h"
#include "pygmalion-chess-dynamics/movegen_pawn_promocapture_black.h"
#include "pygmalion-chess-dynamics/movegen_sliders_hv.h"
#include "pygmalion-chess-dynamics/movegen_sliders_diag.h"
#include "pygmalion-chess-dynamics/movegen_king.h"
#include "pygmalion-chess-dynamics/tropism.h"
#include "pygmalion-chess-dynamics/generator.h"
#include "pygmalion-chess-dynamics/commands.h"
#include "pygmalion-chess-dynamics/engine.h"

#endif