
#if defined(__GNUC__)||defined(__clang__)
#define PYGMALION_INTRINSICS_GNU
#endif
#if defined(_MSC_VER)
#define PYGMALION_INTRINSICS_MSC
#endif

#if (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
#if defined(__GNUC__)||defined(__clang__)
#include <x86intrin.h>
#endif
#if defined(_MSC_VER)&&!(defined(__GNUC__)||defined(__clang__))
#include <intrin.h>
#include <immintrin.h>
#endif
#endif




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

/*	struct tag_generic {};
	struct tag_MSC : tag_generic {};
	struct tag_GNU : tag_MSC {};
	struct tag_best : tag_GNU {};*/

/*	struct tag_generic {};
	struct tag_MSC : tag_generic {};
	struct tag_GNU : tag_generic {};
	struct tag_best : tag_GNU, tag_MSC {};*/


	constexpr static const bool supports(const flags FLAGS) noexcept
	{
		const bool R{ static_cast<bool>((computeFlags() & FLAGS) == FLAGS) };
		return R;
	};
};

std::ostream& operator<<(std::ostream& str, const intrinsics::compiler::flags f) noexcept
{
	if (f & intrinsics::compiler::flags::MSC)
		str << "MSC" << std::endl;
	if (f & intrinsics::compiler::flags::GNU)
		str << "GNU" << std::endl;
	return str;
}
