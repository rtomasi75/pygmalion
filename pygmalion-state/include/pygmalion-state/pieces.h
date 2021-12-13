namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class pieces :
		public set<typename DESCRIPTION_STATE::pieceType, pieces<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		PYGMALION_INLINE constexpr pieces(const typename set<typename DESCRIPTION_STATE::pieceType, pieces<DESCRIPTION_STATE>>::bitsType& bits) noexcept :
			set<typename DESCRIPTION_STATE::pieceType, pieces<DESCRIPTION_STATE>>(bits)
		{

		}
		PYGMALION_INLINE constexpr pieces(typename set<typename DESCRIPTION_STATE::pieceType, pieces<DESCRIPTION_STATE>>::bitsType&& bits) noexcept :
			set<typename DESCRIPTION_STATE::pieceType, pieces<DESCRIPTION_STATE>>(std::move(bits))
		{

		}
		PYGMALION_INLINE constexpr pieces(const pieces&) noexcept = default;
		PYGMALION_INLINE constexpr pieces(pieces&&) noexcept = default;
		PYGMALION_INLINE constexpr pieces() noexcept = default;
		PYGMALION_INLINE ~pieces() noexcept = default;
		PYGMALION_INLINE constexpr pieces& operator=(pieces&&) noexcept = default;
		PYGMALION_INLINE constexpr pieces& operator=(const pieces&) noexcept = default;
	};
}