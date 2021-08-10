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
		constexpr piece(const piece&) noexcept = default;
		constexpr piece(piece&&) noexcept = default;
		constexpr piece() noexcept :
			parentType()
		{

		}
		constexpr piece(const typename parentType::baseType value) noexcept :
			parentType(value)
		{
		}
		constexpr piece(const typename parentType::valueType value) noexcept :
			parentType(value)
		{
		}
		constexpr piece& operator=(piece&&) noexcept = default;
		constexpr piece& operator=(const piece&) noexcept = default;
	};
}