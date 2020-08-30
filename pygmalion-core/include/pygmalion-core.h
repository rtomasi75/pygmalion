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
#endif
#endif
#if defined(_MSC_VER)
#include <intrin.h>
#define PYGMALION_INTRINSICS_MSC
#if (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
#include <immintrin.h>
#endif
#endif

#if defined(__BMI2__)
#if !defined(PYGMALION_CPU_BMI2)
#define PYGMALION_CPU_BMI2
#endif
#endif
#if defined(__SSE41__)
#if !defined(PYGMALION_CPU_SSE41)
#define PYGMALION_CPU_SSE41
#endif
#endif
#if defined(__SSE42__)
#if !defined(PYGMALION_CPU_SSE42)
#define PYGMALION_CPU_SSE42
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
#if defined(__MMX__)
#if !defined(PYGMALION_CPU_MMX)
#define PYGMALION_CPU_MMX
#endif
#endif
#if defined(__SSE__)
#if !defined(PYGMALION_CPU_SSE)
#define PYGMALION_CPU_SSE
#endif
#endif
#if defined(__SSE2__)
#if !defined(PYGMALION_CPU_SSE2)
#define PYGMALION_CPU_SSE2
#endif
#endif
#if defined(__SSE3__)
#if !defined(PYGMALION_CPU_SSE3)
#define PYGMALION_CPU_SSE3
#endif
#endif
#if defined(__SSSE3__)
#if !defined(PYGMALION_CPU_SSSE3)
#define PYGMALION_CPU_SSSE3
#endif
#endif
#if defined(__SSE41__)
#if !defined(PYGMALION_CPU_SSE41)
#define PYGMALION_CPU_SSE41
#endif
#endif
#if defined(__SSE42__)
#if !defined(PYGMALION_CPU_SSE42)
#define PYGMALION_CPU_SSE42
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
#include "pygmalion-core/hash.h"
#include "pygmalion-core/enumeration.h"
#include "pygmalion-core/movecode.h"
#include "pygmalion-core/player.h"
#include "pygmalion-core/piece.h"
#include "pygmalion-core/rank.h"
#include "pygmalion-core/file.h"
#include "pygmalion-core/gamestate.h"
#include "pygmalion-core/bit.h"
#include "pygmalion-core/flag.h"
#include "pygmalion-core/flags.h"
#include "pygmalion-core/score.h"
#include "pygmalion-core/bitfield.h"
#include "pygmalion-core/square.h"
#include "pygmalion-core/descriptor_board.h"
#include "pygmalion-core/base_board.h"
#include "pygmalion-core/list.h"
#include "pygmalion-core/move.h"
#include "pygmalion-core/descriptor_mechanics.h"
#include "pygmalion-core/base_mechanics.h"
#include "pygmalion-core/mechanics.h"
#include "pygmalion-core/descriptor_generator.h"
#include "pygmalion-core/base_generator.h"
#include "pygmalion-core/multiscore.h"
#include "pygmalion-core/searchtable.h"
#include "pygmalion-core/descriptor_evaluation.h"
#include "pygmalion-core/base_evaluation.h"
#include "pygmalion-core/bloomfilter.h"
#include "pygmalion-core/board.h"
#include "pygmalion-core/parser.h"
#include "pygmalion-core/magic.h"
#include "pygmalion-core/magictable.h"
#include "pygmalion-core/generator.h"
#include "pygmalion-core/evaluation.h"
#include "pygmalion-core/heuristics.h"
#include "pygmalion-core/descriptor_search.h"
#include "pygmalion-core/base_search.h"
#include "pygmalion-core/node.h"
#include "pygmalion-core/search.h"
#include "pygmalion-core/match.h"
#include "pygmalion-core/descriptor_frontend.h"
#include "pygmalion-core/base_frontend.h"
#include "pygmalion-core/frontend.h"
#include "pygmalion-core/command.h"
#include "pygmalion-core/engine.h"

#endif