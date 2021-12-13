namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class files :
		public DESCRIPTION_STATE::fileType::template set<files<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr files(const typename DESCRIPTION_STATE::fileType::template set<files<DESCRIPTION_STATE>>::bitsType& bits) noexcept :
			DESCRIPTION_STATE::fileType::template set<files<DESCRIPTION_STATE>>(bits)
		{

		}
		PYGMALION_INLINE constexpr files(typename DESCRIPTION_STATE::fileType::template set<files<DESCRIPTION_STATE>>::bitsType&& bits) noexcept :
			DESCRIPTION_STATE::fileType::template set<files<DESCRIPTION_STATE>>(std::move(bits))
		{

		}
		PYGMALION_INLINE constexpr files(const files&) noexcept = default;
		PYGMALION_INLINE constexpr files(files&&) noexcept = default;
		PYGMALION_INLINE constexpr files() noexcept = default;
		PYGMALION_INLINE ~files() noexcept = default;
		PYGMALION_INLINE constexpr files& operator=(files&&) noexcept = default;
		PYGMALION_INLINE constexpr files& operator=(const files&) noexcept = default;
	};
}