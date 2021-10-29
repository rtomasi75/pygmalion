namespace pygmalion
{
	class parameter
	{
	private:
		double m_DefaultValue;
		double m_MinimumValue;
		double m_MaximumValue;
		double m_Delta;
		std::string m_Name;
	public:
		double defaultValue() const noexcept
		{
			return m_DefaultValue;
		}
		double minimumValue() const noexcept
		{
			return m_MinimumValue;
		}
		double maximumValue() const noexcept
		{
			return m_MaximumValue;
		}
		double delta() const noexcept
		{
			return m_Delta;
		}
		const std::string& name() const noexcept
		{
			return m_Name;
		}
		parameter() noexcept = delete;
		parameter(const double defaultValue, const double minimumValue, const double maximumValue, const double delta, const std::string& name) noexcept :
			m_DefaultValue{ defaultValue },
			m_MinimumValue{ minimumValue },
			m_MaximumValue{ maximumValue },
			m_Delta{ delta },
			m_Name{ name }
		{

		}
		~parameter() noexcept = default;
		parameter(const parameter&) noexcept = default;
		parameter(parameter&&) noexcept = default;
		parameter& operator=(const parameter&) = default;
		parameter& operator=(parameter&&) = default;
	};
}