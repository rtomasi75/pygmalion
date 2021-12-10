
#if defined(__GNUC__)||defined(__clang__)
#define PYGMALION_INTRINSICS_GNU
#endif
#if defined(_MSC_VER)
#define PYGMALION_INTRINSICS_MSC
#endif

#if defined(_MSC_VER)
/* Microsoft C/C++-compatible compiler */
#include <intrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
/* GCC-compatible compiler, targeting x86/x86-64 */
#include <x86intrin.h>
#elif defined(__GNUC__) && defined(__ARM_NEON__)
/* GCC-compatible compiler, targeting ARM with NEON */
#include <arm_neon.h>
#elif defined(__GNUC__) && defined(__IWMMXT__)
/* GCC-compatible compiler, targeting ARM with WMMX */
#include <mmintrin.h>
#elif (defined(__GNUC__) || defined(__xlC__)) && (defined(__VEC__) || defined(__ALTIVEC__))
/* XLC or GCC-compatible compiler, targeting PowerPC with VMX/VSX */
#include <altivec.h>
#elif defined(__GNUC__) && defined(__SPE__)
/* GCC-compatible compiler, targeting PowerPC with SPE */
#include <spe.h>
#endif

#if defined(__GNUC__)||defined(__clang__)
#if _DEBUG
#define PYGMALION_ASSERT(cond) assert(cond)
#define PYGMALION_UNREACHABLE  assert(false)
#else
#define PYGMALION_ASSERT(cond) do { if (!(cond)) __builtin_unreachable(); } while (0)
#define PYGMALION_UNREACHABLE  __builtin_unreachable()
#endif
#elif defined(_MSC_VER)
#if _DEBUG
#define PYGMALION_ASSERT(cond) assert(cond)
#define PYGMALION_UNREACHABLE  assert(false)
#else
#define PYGMALION_ASSERT(cond) 
#define PYGMALION_UNREACHABLE  __assume(false)
#endif
#else
#if _DEBUG
#define PYGMALION_ASSERT(cond) assert(cond)
#define PYGMALION_UNREACHABLE  assert(false)
#else
#define PYGMALION_ASSERT(cond) 
#define PYGMALION_UNREACHABLE  
#endif
#endif

#if defined(NDEBUG)
#if defined(_MSC_VER)
#define PYGMALION_INLINE __forceinline
#elif defined(__GNUC__)
#define PYGMALION_INLINE [[gnu::always_inline]]
#elif defined(__clang__) 
#define PYGMALION_INLINE [[gnu::always_inline]]
#else
#define PYGMALION_INLINE
#endif
#else
#define PYGMALION_INLINE
#endif
//#define PYGMALION_INLINE

namespace pygmalion
{
	class compiler
	{
	public:
	public:
		enum flags : int
		{
			any = 0b00000000,
			MSC = 0b00000001,
			GNU = 0b00000010,
		};
		constexpr static flags computeFlags() noexcept
		{
			int f{ any };
#if defined(PYGMALION_INTRINSICS_GNU)
			f |= static_cast<int>(flags::GNU);
#endif
#if defined(PYGMALION_INTRINSICS_MSC)
			f |= static_cast<int>(flags::MSC);
#endif
			return static_cast<flags>(f);
		}

		struct tag_emulation {};
		struct tag_generic : tag_emulation {};
		struct tag_GNU : tag_generic {};
		struct tag_MSC : tag_GNU {};
		struct tag_best : tag_MSC {};

		constexpr static bool supports(const flags FLAGS) noexcept
		{
			const bool R{ static_cast<bool>((computeFlags() & FLAGS) == FLAGS) };
			return R;
		};
	};

	std::ostream& operator<<(std::ostream& str, const compiler::flags f) noexcept;
}