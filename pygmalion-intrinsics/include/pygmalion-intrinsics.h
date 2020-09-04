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

namespace intrinsics
{
#include "pygmalion-intrinsics/make_array.h"
#include "pygmalion-intrinsics/cpu.h"
#include "pygmalion-intrinsics/compiler.h"
#include "pygmalion-intrinsics/integer_intrinsics.h"
#include "pygmalion-intrinsics/integer_traits.h"
#include "pygmalion-intrinsics/unsigned_integer.h"
#include "pygmalion-intrinsics/bitmanip.h"
#include "pygmalion-intrinsics/int_traits.h"
}

#endif