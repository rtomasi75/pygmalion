#if !defined(PYGMALION_CORE)
#define PYGMALION_CORE

#define _USE_MATH_DEFINES

#if (defined(_M_IX86)||defined(__i386__))
#define PYGMALION_CPU_X86
#endif
#if (defined(_M_X64)||defined(__x86_64__)||defined(__amd64__))
#define PYGMALION_CPU_X64
#endif
#if (defined(_M_ARM)||defined(__arm__))
#define PYGMALION_CPU_ARM
#endif
#if (defined(_M_ALPHA)||defined(__alpha__))
#define PYGMALION_CPU_ALPHA
#endif
#if (defined(__aarch64__))
#define PYGMALION_CPU_ARM64
#endif

#if (defined(__clang__)||defined(__GNUC__))
#define PYGMALION_INTRINSICS_GNU
#if (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
#include <x86intrin.h>
#if defined(__BMI2__)
#if !defined(PYGMALION_CPU_BMI2)
#define PYGMALION_CPU_BMI2
#endif
#endif
#if defined(__AVX__)
#if !defined(PYGMALION_CPU_AVX)
#define PYGMALION_CPU_AVX
#endif
#endif
#if defined(__AVX2__)
#if !defined(PYGMALION_CPU_AVX2)
#define PYGMALION_CPU_AVX2
#endif
#endif
#if defined(__AVX512__)
#if !defined(PYGMALION_CPU_AVX512)
#define PYGMALION_CPU_AVX512
#endif
#endif
#endif
#endif
#if defined(_MSC_VER)
#include <intrin.h>
#define PYGMALION_INTRINSICS_MSC
#if (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
#include <immintrin.h>
#endif
#endif

//#define PYGMALION_NOSHIFTS 

#include <type_traits>
#include <utility>
#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iostream>
#include <atomic>
#include <deque>
#include <mutex>
#include <sstream>
#include <memory>
#include <chrono>
#include <array>
#include <type_traits>
#include <iomanip>
#include <bitset>
#include <climits>

#include "pygmalion-core/bitmanip.h"
#include "pygmalion-core/int_traits.h"
#include "pygmalion-core/enumeration.h"
#include "pygmalion-core/score.h"
#include "pygmalion-core/multiscore.h"
#include "pygmalion-core/bitfield.h"
#include "pygmalion-core/movelist.h"
#include "pygmalion-core/board.h"
#include "pygmalion-core/parser.h"
#include "pygmalion-core/magic.h"
#include "pygmalion-core/magictable.h"
#include "pygmalion-core/movegen.h"
#include "pygmalion-core/evaluator.h"
#include "pygmalion-core/node.h"
#include "pygmalion-core/search.h"
#include "pygmalion-core/match.h"
#include "pygmalion-core/frontend.h"
#include "pygmalion-core/command.h"
#include "pygmalion-core/engine.h"

#endif