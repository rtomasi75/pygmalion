namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class piece :
		public enumeration<DESCRIPTION_STATE::countPieces, DESCRIPTION_STATE::countHashBits, piece<DESCRIPTION_STATE>, set<piece<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::piecesType>>,
		public DESCRIPTION_STATE
	{
	public:
		using parentType = enumeration<DESCRIPTION_STATE::countPieces, DESCRIPTION_STATE::countHashBits, piece<DESCRIPTION_STATE>, set<piece<DESCRIPTION_STATE>, typename DESCRIPTION_STATE::piecesType>>;
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
		std::string toShortString() const noexcept
		{
			return descriptorState::boardInfo.playerpieces().pieces().toShortString(static_cast<size_t>(*this));
		}
		std::string toLongString() const noexcept
		{
			return descriptorState::boardInfo.playerpieces().pieces().toLongString(static_cast<size_t>(*this));
		}
		static bool parse(const std::string text, size_t& pos, piece& parsed) noexcept
		{
			size_t parsedIndex;
			if (descriptorState::boardInfo.playerpieces().pieces().parse(text, pos, parsedIndex))
			{
				parsed = piece(parsedIndex);
				return true;
			}
			else
				return false;
		}
		PYGMALION_INLINE constexpr playerpieceType operator&(const playerType player) const noexcept
		{
			return playerpieceType::fromPlayerPiece(player, *this);
		}
	private:
		constexpr static inline const std::array<bool, countPieces> m_RoyalPieceFlags{ arrayhelper::generate<countPieces,bool>([](const size_t pieceIndex) {return boardInfo.playerpieces().pieces().isRoyalPiece(pieceIndex); }) };
		constexpr static inline const std::array<bool, countPieces> m_StructuralPieceFlags{ arrayhelper::generate<countPieces,bool>([](const size_t pieceIndex) {return boardInfo.playerpieces().pieces().isStructuralPiece(pieceIndex); }) };
		constexpr static inline const std::array<royalpieceType, countPieces> m_InverseRoyalPieceIndex{ arrayhelper::generate<countPieces,royalpieceType>([](const size_t pieceIndex) { royalpieceType result{royalpieceType::invalid}; for (size_t i = 0; i < countRoyalPieces; i++) { if (boardInfo.playerpieces().pieces().indexRoyalPiece(i) == pieceIndex) { result = static_cast<royalpieceType>(i); break; } } return result; }) };
		constexpr static inline const std::array<structuralpieceType, countPieces> m_InverseStructuralPieceIndex{ arrayhelper::generate<countPieces,structuralpieceType>([](const size_t pieceIndex) { structuralpieceType result{structuralpieceType::invalid}; for (size_t i = 0; i < countStructuralPieces; i++) { if (boardInfo.playerpieces().pieces().indexStructuralPiece(i) == pieceIndex) { result = static_cast<structuralpieceType>(i); break; } } return result; }) };
	public:
		PYGMALION_INLINE constexpr bool isRoyal() const noexcept
		{
			return m_RoyalPieceFlags[*this];
		}
		PYGMALION_INLINE constexpr bool isStructural() const noexcept
		{
			return m_StructuralPieceFlags[*this];
		}
		PYGMALION_INLINE constexpr piece(const royalpieceType& other) noexcept :
			piece(piecesType::m_RoyalPieceIndex[other])
		{

		}
		PYGMALION_INLINE constexpr piece(const structuralpieceType& other) noexcept :
			piece(piecesType::m_StructuralPieceIndex[other])
		{

		}
		PYGMALION_INLINE constexpr operator royalpieceType() const noexcept
		{
			PYGMALION_ASSERT(this->isValid());
			PYGMALION_ASSERT(this->isRoyal());
			return m_InverseRoyalPieceIndex[*this];
		}
		PYGMALION_INLINE constexpr operator structuralpieceType() const noexcept
		{
			PYGMALION_ASSERT(this->isValid());
			PYGMALION_ASSERT(this->isStructural());
			return m_InverseStructuralPieceIndex[*this];
		}
	};
}