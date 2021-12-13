namespace pygmalion::config
{
	template<size_t COUNTRANKS>
	class ranksInfo
	{
	public:
		const std::array<rankInfo, COUNTRANKS> m_Ranks;
	protected:
		constexpr ranksInfo(const std::array<rankInfo, COUNTRANKS>& ranks) noexcept :
			m_Ranks{ ranks }
		{
		}
	public:
		constexpr static const inline size_t countRanks{ COUNTRANKS };
		~ranksInfo() noexcept
		{

		}
		constexpr const rankInfo& rank(const size_t rankIndex) const noexcept
		{
			return m_Ranks[rankIndex];
		}
	};
}