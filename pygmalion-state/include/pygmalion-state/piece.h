namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class piece :
		public enumeration<DESCRIPTION_STATE::countPieces, DESCRIPTION_STATE::countHashBits, piece<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countPieces, DESCRIPTION_STATE::countHashBits, piece<DESCRIPTION_STATE>>;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr piece(const piece&) noexcept = default;
		PYGMALION_INLINE constexpr piece(piece&&) noexcept = default;
		PYGMALION_INLINE constexpr piece() noexcept :
			parentType()
		{

		}
		PYGMALION_INLINE constexpr piece(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr piece(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		PYGMALION_INLINE constexpr piece& operator=(piece&&) noexcept = default;
		PYGMALION_INLINE constexpr piece& operator=(const piece&) noexcept = default;
	};
}