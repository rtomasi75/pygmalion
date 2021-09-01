
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
#if defined(__AVX512__)
#if !defined(PYGMALION_CPU_AVX512)
#define PYGMALION_CPU_AVX512
#endif
#endif
#if defined(__AVX2__)
#if !defined(PYGMALION_CPU_AVX2)
#define PYGMALION_CPU_AVX2
#endif
#endif
#if defined(__AVX__)
#if !defined(PYGMALION_CPU_AVX)
#define PYGMALION_CPU_AVX
#endif
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
#if defined(__SSE42__)
#if !defined(PYGMALION_CPU_SSE42)
#define PYGMALION_CPU_SSE42
#endif
#endif
#if defined(__SSE41__)
#if !defined(PYGMALION_CPU_SSE41)
#define PYGMALION_CPU_SSE41
#endif
#endif
#if defined(__SSSE3__)
#if !defined(PYGMALION_CPU_SSSE3)
#define PYGMALION_CPU_SSSE3
#endif
#endif
#if defined(__SSE3__)
#if !defined(PYGMALION_CPU_SSE3)
#define PYGMALION_CPU_SSE3
#endif
#endif
#if defined(__SSE2__)
#if !defined(PYGMALION_CPU_SSE2)
#define PYGMALION_CPU_SSE2
#endif
#endif
#if defined(__SSE__)
#if !defined(PYGMALION_CPU_SSE)
#define PYGMALION_CPU_SSE
#endif
#endif
#if defined(__MMX__)
#if !defined(PYGMALION_CPU_MMX)
#define PYGMALION_CPU_MMX
#endif
#endif

namespace pygmalion
{
	class cpu
	{
	public:
		enum flags : std::uint16_t
		{
			none = 0b0000000000000000,
			X86 = 0b00000000000000001,
			X64 = 0b0000000000000011,
			BMI = 0b0000000000100000,
			BMI2 = 0b0000000000000100,
			SSE = 0b0000000000001000,
			SSE2 = 0b0000000000010000,
			SSE41 = 0b0000000001000000,
			SSE42 = 0b0000000010000000,
			SSE3 = 0b0000000100000000,
			SSSE3 = 0b0000001000000000,
			MMX = 0b0000010000000000,
			AVX = 0b0000100000000000,
			AVX2 = 0b0001000000000000,
			AVX512 = 0b0010000000000000,
		};
		constexpr static flags computeFlags() noexcept
		{
			int f{ flags::none };
#if defined(PYGMALION_CPU_BMI)
			f |= flags::BMI;
#endif
#if defined(PYGMALION_CPU_BMI2)
			f |= flags::BMI2;
#endif
#if defined(PYGMALION_CPU_X86)
			f |= flags::X86;
#endif
#if defined(PYGMALION_CPU_X64)
			f |= flags::X86;
			f |= flags::X64;
#endif
#if defined(PYGMALION_CPU_MMX)
			f |= flags::MMX;
#endif
#if defined(PYGMALION_CPU_SSE)
			f |= flags::SSE;
#endif
#if defined(PYGMALION_CPU_SSE2)
			f |= flags::SSE2;
#endif
#if defined(PYGMALION_CPU_SSE3)
			f |= flags::SSE3;
#endif
#if defined(PYGMALION_CPU_SSSE3)
			f |= flags::SSSE3;
#endif
#if defined(PYGMALION_CPU_SSE41)
			f |= flags::SSE41;
#endif
#if defined(PYGMALION_CPU_SSE42)
			f |= flags::SSE42;
#endif
#if defined(PYGMALION_CPU_AVX)
			f |= flags::AVX;
#endif
#if defined(PYGMALION_CPU_AVX2)
			f |= flags::AVX2;
#endif
#if defined(PYGMALION_CPU_AVX512)
			f |= flags::AVX512;
#endif
			return static_cast<flags>(f);
		}

		struct tag_generic
		{};

		struct tag_BMI2
		{};

		struct tag_X86 :
			tag_generic
		{};

		struct tag_X64 :
			tag_X86
		{};

		struct tag_best :
			tag_X64,
			tag_BMI2
		{};

		constexpr static const bool supports(const flags FLAGS) noexcept
		{
			const bool R{ static_cast<bool>((computeFlags() & FLAGS) == FLAGS) };
			return R;
		};
	};

	std::ostream& operator<<(std::ostream& str, const cpu::flags f) noexcept;
}

