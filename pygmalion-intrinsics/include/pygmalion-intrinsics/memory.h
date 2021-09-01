namespace pygmalion
{
	class memory
	{
	public:
		static void prefetchRead(const void* pAddr) noexcept
		{
#if defined(PYGMALION_CPU_SSE)
			if constexpr (cpu::supports(cpu::SSE))
			{
		//		_mm_prefetch(static_cast<const char*>(pAddr), _MM_HINT_T0);
			}
#endif
		}
	};
}