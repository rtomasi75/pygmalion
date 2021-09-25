namespace pygmalion
{
	template<typename DESCRIPTION_EVALUATION>
	class moveinfo :
		public DESCRIPTION_EVALUATION
	{
	public:
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include <pygmalion-evaluation/include_evaluation.h>
	private:
		movebitsType m_MoveBits;
	public:
		moveinfo() noexcept
		{

		}
		constexpr moveinfo(const movebitsType& moveBits) noexcept :
			m_MoveBits{ moveBits }
		{

		}
		constexpr const movebitsType& moveBits() const noexcept
		{
			return m_MoveBits;
		}
		~moveinfo() noexcept = default;
		constexpr moveinfo(const moveinfo&) noexcept = default;
		constexpr moveinfo(moveinfo&&) noexcept = default;
		constexpr moveinfo& operator=(const moveinfo&) noexcept = default;
		constexpr moveinfo& operator=(moveinfo&&) noexcept = default;
	};
}