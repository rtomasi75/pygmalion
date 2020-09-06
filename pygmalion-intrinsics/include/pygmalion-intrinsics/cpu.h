
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
#if defined(__BMI2__)
#if !defined(PYGMALION_CPU_BMI2)
#define PYGMALION_CPU_BMI2
#endif
#endif
#if defined(__BMI__)
#if !defined(PYGMALION_CPU_BMI)
#define PYGMALION_CPU_BMI
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


class cpu
{
public:
	enum flags : int
	{
		none = 0b00000000,
		X86 = 0b000000001,
		X64 = 0b00000011,
	};
	constexpr static flags computeFlags() noexcept
	{
		int f{ flags::none };
#if defined(PYGMALION_CPU_X86)
		f |= flags::X86;
#endif
#if defined(PYGMALION_CPU_X64)
		f |= flags::X86;
		f |= flags::X64;
#endif
		return static_cast<flags>(f);
	}

	struct tag_generic
	{};

	struct tag_X86 :
		tag_generic
	{};

	struct tag_X64 :
		tag_X86
	{};

	struct tag_best :
		tag_X64
	{};

	constexpr static const bool supports(const flags FLAGS) noexcept
	{
		const bool R{ static_cast<bool>((computeFlags() & FLAGS) == FLAGS) };
		return R;
	};
};

std::ostream& operator<<(std::ostream& str, const intrinsics::cpu::flags f) noexcept
{
	if (f & intrinsics::cpu::X86)
		str << "X86" << std::endl;
	if (f & intrinsics::cpu::X64)
		str << "X64" << std::endl;
	return str;
}
