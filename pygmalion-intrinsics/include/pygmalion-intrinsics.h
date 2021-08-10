#if !defined(PYGMALION_INTRINSICS)
#define PYGMALION_INTRINSICS

#define _USE_MATH_DEFINES



//#define PYGMALION_NOSHIFTS 

#include <cstdint>
#include <cassert>
#include <cmath>
#include <type_traits>
#include <iterator>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <array>
#include <climits>
#include <limits>
#include <algorithm>
#include <chrono>
#include <atomic>
#include <deque>
#include <mutex>
#include <memory>

#include "pygmalion-intrinsics/arrayhelper.h"
#include "pygmalion-intrinsics/profiler.h"
#include "pygmalion-intrinsics/cpu.h"
#include "pygmalion-intrinsics/compiler.h"
#include "pygmalion-intrinsics/base.h"
#include "pygmalion-intrinsics/popcnt.h"
#include "pygmalion-intrinsics/bsf.h"
#include "pygmalion-intrinsics/bsr.h"
#include "pygmalion-intrinsics/hash.h"
#include "pygmalion-intrinsics/enumeration.h"
#include "pygmalion-intrinsics/bit.h"
#include "pygmalion-intrinsics/uint_t_traits.h"
#include "pygmalion-intrinsics/uint_t_detail.h"
#include "pygmalion-intrinsics/uint_t.h"
#include "pygmalion-intrinsics/list.h"
#include "pygmalion-intrinsics/magic.h"
#include "pygmalion-intrinsics/magictable.h"
#include "pygmalion-intrinsics/parser.h"
#include "pygmalion-intrinsics/score.h"
#include "pygmalion-intrinsics/command.h"
#include "pygmalion-intrinsics/command_quit.h"
#include "pygmalion-intrinsics/command_ver.h"
#include "pygmalion-intrinsics/command_help.h"
#include "pygmalion-intrinsics/command_debugCompiler.h"
#include "pygmalion-intrinsics/command_debugCpu.h"
#include "pygmalion-intrinsics/command_debugIntrinsics.h"
#include "pygmalion-intrinsics/engine.h"

#endif