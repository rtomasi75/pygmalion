#if !defined(PYGMALION_STATE)
#define PYGMALION_STATE

#include <chrono>
#include <string_view>

#include <pygmalion-intrinsics.h>

#include "pygmalion-state/config.h"
#include "pygmalion-state/player.h"
#include "pygmalion-state/players.h"
#include "pygmalion-state/piece.h"
#include "pygmalion-state/pieces.h"
#include "pygmalion-state/playerpiece.h"
#include "pygmalion-state/playerpieces.h"
#include "pygmalion-state/rank.h"
#include "pygmalion-state/ranks.h"
#include "pygmalion-state/file.h"
#include "pygmalion-state/files.h"
#include "pygmalion-state/square.h"
#include "pygmalion-state/squares.h"
#include "pygmalion-state/flag.h"
#include "pygmalion-state/flags.h"
#include "pygmalion-state/royalpiece.h"
#include "pygmalion-state/royalpieces.h"
#include "pygmalion-state/structuralpiece.h"
#include "pygmalion-state/structuralpieces.h"
#include "pygmalion-state/gamestate.h"
#include "pygmalion-state/signature.h"
#include "pygmalion-state/materialTables.h"
#include "pygmalion-state/board.h"
#include "pygmalion-state/delta.h"
#include "pygmalion-state/descriptor_state.h"
#include "pygmalion-state/command.h"
#include "pygmalion-state/commands.h"
#include "pygmalion-state/game.h"
#include "pygmalion-state/engine.h"

#endif