namespace pygmalion::evaluation
{
	template<typename DESCRIPTION_EVALUATION>
	class parameter :
		public DESCRIPTION_EVALUATION
	{
	public:
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "include_evaluation.h"	
	private:
		scoreType m_DefaultValue;
		scoreType m_MinimumValue;
		scoreType m_MaximumValue;
		scoreType m_Delta;
		std::string m_Name;
	public:
		scoreType defaultValue() const noexcept
		{
			return m_DefaultValue;
		}
		scoreType minimumValue() const noexcept
		{
			return m_MinimumValue;
		}
		scoreType maximumValue() const noexcept
		{
			return m_MaximumValue;
		}
		scoreType delta() const noexcept
		{
			return m_Delta;
		}
		const std::string& name() const noexcept
		{
			return m_Name;
		}
		parameter() noexcept = delete;
		parameter(const scoreType defaultValue, const scoreType minimumValue, const scoreType maximumValue, const scoreType delta, const std::string& name) noexcept :
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