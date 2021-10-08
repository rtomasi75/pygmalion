namespace pygmalion
{
	class memory
	{
	public:
		PYGMALION_INLINE static void prefetchRead(const void* pAddr) noexcept
		{
/*			if constexpr (compiler::supports(compiler::GNU))
			{

			}*/
#if defined(PYGMALION_CPU_SSE)
			if constexpr (cpu::supports(cpu::SSE))
			{
				_mm_prefetch(static_cast<const char*>(pAddr), _MM_HINT_T0);
			}
#endif
		}
	};
}