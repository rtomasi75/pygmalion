namespace pygmalion::config
{
	class scoreInfo
	{
	public:
		const size_t mantissaBits;
		const size_t shiftBits;
		const size_t maxDTM;
	protected:
		constexpr scoreInfo(const size_t mantissaBits_, const size_t shiftBits, size_t maxDTM) noexcept :
			mantissaBits{ mantissaBits_ },
			shiftBits{ shiftBits },
			maxDTM{ maxDTM }
		{}
	};
}