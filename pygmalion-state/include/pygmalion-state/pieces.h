namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class pieces :
		public set<typename DESCRIPTION_STATE::pieceType, pieces<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
		friend typename DESCRIPTION_STATE::pieceType;
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
		std::string toString(const playerType pl) const noexcept
		{
			std::stringstream str;
			for (const auto pc : pieceType::range)
			{
				if ((*this)[pc])
					str << (pc & pl).toShortString();
				else
					str << "_";
			}
			return str.str();
		}
	private:
		constexpr static inline const std::array<pieceType, countRoyalPieces> m_RoyalPieceIndex{ arrayhelper::generate<countRoyalPieces,pieceType>([](const size_t royalIndex) { return static_cast<pieceType>(boardInfo.playerpieces().pieces().indexRoyalPiece(royalIndex)); }) };
		constexpr static inline const std::array<pieceType, countStructuralPieces> m_StructuralPieceIndex{ arrayhelper::generate<countStructuralPieces,pieceType>([](const size_t structuralIndex) { return static_cast<pieceType>(boardInfo.playerpieces().pieces().indexStructuralPiece(structuralIndex)); }) };

	};
}