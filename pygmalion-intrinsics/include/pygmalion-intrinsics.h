#if !defined(PYGMALION_INTRINSICS)
#define PYGMALION_INTRINSICS

#define _USE_MATH_DEFINES



//#define PYGMALION_NOSHIFTS 

#include <cstdint>
#include <cassert>
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

namespace intrinsics
{
#include "pygmalion-intrinsics/profiler.h"
#include "pygmalion-intrinsics/make_array.h"
#include "pygmalion-intrinsics/cpu.h"
#include "pygmalion-intrinsics/compiler.h"
#include "pygmalion-intrinsics/random.h"
#include "pygmalion-intrinsics/base.h"
#include "pygmalion-intrinsics/popcnt.h"
#include "pygmalion-intrinsics/bsf.h"
#include "pygmalion-intrinsics/bsr.h"
#include "pygmalion-intrinsics/uint_t.h"
#include "pygmalion-intrinsics/bitmanip.h"
#include "pygmalion-intrinsics/int_traits.h"
#include "pygmalion-intrinsics/parser.h"
}

#endif