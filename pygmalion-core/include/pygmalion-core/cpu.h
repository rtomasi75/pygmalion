namespace pygmalion
{
	class cpu
	{
	public:
		constexpr static const bool BMI2
		{
#if defined(PYGMALION_CPU_BMI2)
			true
#else
			false
#endif
		};
		constexpr static const bool X64
		{
#if defined(PYGMALION_CPU_X64)
			true
#else
			false
#endif
		};
		constexpr static const bool X86
		{
#if defined(PYGMALION_CPU_X86)
			true
#else
			false
#endif
		};
	};
}