namespace pygmalion::config
{
	template<size_t COUNTPLAYERS>
	class playersInfo
	{
	public:
		const std::array<playerInfo, COUNTPLAYERS> m_Players;
	protected:
		constexpr playersInfo(const std::array<playerInfo, COUNTPLAYERS>& players) noexcept :
			m_Players{ players }
		{
		}
	public:
		constexpr static const inline size_t countPlayers{ COUNTPLAYERS };
		~playersInfo() noexcept
		{

		}
		constexpr const playerInfo& player(const size_t playerIndex) const noexcept
		{
			return m_Players[playerIndex];
		}
	};
}