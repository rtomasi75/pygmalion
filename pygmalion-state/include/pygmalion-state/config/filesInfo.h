namespace pygmalion::config
{
	template<size_t COUNTFILES>
	class filesInfo
	{
	public:
		const std::array<fileInfo, COUNTFILES> m_Files;
	protected:
		constexpr filesInfo(const std::array<fileInfo, COUNTFILES>& files) noexcept :
			m_Files{ files }
		{
		}
	public:
		constexpr static const inline size_t countFiles{ COUNTFILES };
		~filesInfo() noexcept
		{

		}
		constexpr const fileInfo& file(const size_t fileIndex) const noexcept
		{
			return m_Files[fileIndex];
		}
	};
}