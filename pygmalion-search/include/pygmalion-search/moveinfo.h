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
		PYGMALION_INLINE moveinfo() noexcept
		{

		}
		PYGMALION_INLINE moveinfo(const movebitsType moveBits) noexcept :
			m_MoveBits{ moveBits }
		{

		}
		PYGMALION_INLINE const movebitsType moveBits() const noexcept
		{
			return m_MoveBits;
		}
		PYGMALION_INLINE ~moveinfo() noexcept = default;
		PYGMALION_INLINE moveinfo(const moveinfo&) noexcept = default;
		PYGMALION_INLINE moveinfo(moveinfo&&) noexcept = default;
		PYGMALION_INLINE moveinfo& operator=(const moveinfo&) noexcept = default;
		PYGMALION_INLINE moveinfo& operator=(moveinfo&&) noexcept = default;
	};
}