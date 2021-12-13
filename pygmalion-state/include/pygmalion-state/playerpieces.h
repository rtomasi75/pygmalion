namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class playerpieces :
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
	private:
		std::array<piecesType, countPlayers> m_Pieces;
	public:
		PYGMALION_INLINE constexpr playerpieces(const std::array<piecesType, countPlayers>& pieces) noexcept :
			m_Pieces{ pieces }
		{
		}
		PYGMALION_INLINE constexpr playerpieces(const playerpieces&) noexcept = default;
		PYGMALION_INLINE constexpr playerpieces(playerpieces&&) noexcept = default;
		PYGMALION_INLINE constexpr playerpieces() noexcept = default;
		PYGMALION_INLINE ~playerpieces() noexcept = default;
		PYGMALION_INLINE constexpr playerpieces& operator=(playerpieces&&) noexcept = default;
		PYGMALION_INLINE constexpr playerpieces& operator=(const playerpieces&) noexcept = default;
		PYGMALION_INLINE constexpr const piecesType& pieces(const playerType pl) const noexcept
		{
			return m_Pieces[pl];
		}
		template<size_t PLAYER>
		PYGMALION_INLINE constexpr const piecesType& pieces() const noexcept
		{
			return m_Pieces[PLAYER];
		}
		PYGMALION_INLINE constexpr piecesType& pieces(const playerType pl) noexcept
		{
			return m_Pieces[pl];
		}
		template<size_t PLAYER>
		PYGMALION_INLINE constexpr piecesType& pieces() noexcept
		{
			return m_Pieces[PLAYER];
		}
		PYGMALION_INLINE constexpr void clear() noexcept
		{
			for (const auto pl : playerType::range)
				m_Pieces[pl].clear();
		}
		PYGMALION_INLINE playerpieceType first() const noexcept
		{
			size_t bit;
			for (size_t pl = 0; pl < countPlayers; pl++)
			{
				if (m_Pieces[pl].bitscanForward(bit))
					return playerpieceType(static_cast<playerType>(pl), static_cast<pieceType>(bit));
			}
			PYGMALION_UNREACHABLE;
			return playerpieceType::invalid;
		}
		PYGMALION_INLINE playerpieceType last() const noexcept
		{
			size_t bit;
			for (size_t pl = countPlayers; pl > 0; pl--)
			{
				if (m_Pieces[pl - 1].bitscanForward(bit))
					return playerpieceType(static_cast<playerType>(pl - 1), static_cast<pieceType>(bit));
			}
			PYGMALION_UNREACHABLE;
			return playerpieceType::invalid;
		}
		PYGMALION_INLINE constexpr static playerpiecesType none() noexcept
		{
			constexpr const playerpiecesType empty{ playerpiecesType(arrayhelper::make<countPlayers, piecesType>(piecesType::none())) };
			return empty;
		}
		PYGMALION_INLINE constexpr static playerpiecesType all() noexcept
		{
			constexpr const playerpiecesType full{ playerpiecesType(arrayhelper::make<countPlayers, piecesType>(piecesType::all())) };
			return full;
		}
		PYGMALION_INLINE constexpr playerpiecesType operator|(const playerpieceType& other) const noexcept
		{
			return playerpiecesType(arrayhelper::generate<countPlayers, piecesType>([this, &other](const size_t pl) {return this->m_Pieces[pl] | other.m_Pieces[pl]; }));
		}
		PYGMALION_INLINE constexpr playerpiecesType operator-(const playerpiecesType& other) const noexcept
		{
			return playerpiecesType(arrayhelper::generate<countPlayers, piecesType>([this, &other](const size_t pl) {return this->m_Pieces[pl] - other.m_Pieces[pl]; }));
		}
		PYGMALION_INLINE constexpr playerpiecesType operator&(const playerpiecesType& other) const noexcept
		{
			return playerpiecesType(arrayhelper::generate<countPlayers, piecesType>([this, &other](const size_t pl) {return this->m_Pieces[pl] & other.m_Pieces[pl]; }));
		}
		PYGMALION_INLINE constexpr playerpiecesType operator^(const playerpiecesType& other) const noexcept
		{
			return playerpiecesType(arrayhelper::generate<countPlayers, piecesType>([this, &other](const size_t pl) {return this->m_Pieces[pl] ^ other.m_Pieces[pl]; }));
		}
		PYGMALION_INLINE constexpr playerpiecesType operator~() const noexcept
		{
			return playerpiecesType(arrayhelper::generate<countPlayers, piecesType>([this](const size_t pl) {return ~this->m_Pieces[pl]; }));
		}
		PYGMALION_INLINE constexpr playerpiecesType& operator|=(const playerpiecesType& other) noexcept
		{
			for (size_t pl = 0; pl < countPlayers; pl++)
				m_Pieces[pl] |= other.m_Pieces[pl];
			return *static_cast<playerpiecesType*>(this);
		}
		PYGMALION_INLINE constexpr playerpiecesType& operator-=(const playerpiecesType& other) noexcept
		{
			for (size_t pl = 0; pl < countPlayers; pl++)
				m_Pieces[pl] -= other.m_Pieces[pl];
			return *static_cast<playerpiecesType*>(this);
		}
		PYGMALION_INLINE constexpr playerpiecesType& operator&=(const playerpiecesType& other) noexcept
		{
			for (size_t pl = 0; pl < countPlayers; pl++)
				m_Pieces[pl] &= other.m_Pieces[pl];
			return *static_cast<playerpiecesType*>(this);
		}
		PYGMALION_INLINE constexpr playerpiecesType& operator^=(const playerpiecesType& other) noexcept
		{
			for (size_t pl = 0; pl < countPlayers; pl++)
				m_Pieces[pl] ^= other.m_Pieces[pl];
			return *static_cast<playerpiecesType*>(this);
		}
		PYGMALION_INLINE constexpr bool operator==(const playerpiecesType& other) const noexcept
		{
			for (size_t pl = 0; pl < countPlayers; pl++)
			{
				if (m_Pieces[pl] != other.m_Pieces[pl])
					return false;
			}
			return true;
		}
		PYGMALION_INLINE constexpr bool operator!=(const playerpiecesType& other) const noexcept
		{
			for (size_t pl = 0; pl < countPlayers; pl++)
			{
				if (m_Pieces[pl] != other.m_Pieces[pl])
					return true;
			}
			return false;
		}
		PYGMALION_INLINE constexpr playerpiecesType& operator|=(const playerpieceType index) noexcept
		{
			const playerType pl{ index.player() };
			const pieceType pc{ index.piece() };
			m_Pieces[pl] |= pc;
			return *static_cast<playerpiecesType*>(this);
		}
		PYGMALION_INLINE constexpr playerpiecesType& operator&=(const playerpieceType index) noexcept
		{
			const playerType pl{ index.player() };
			const pieceType pc{ index.piece() };
			m_Pieces[pl] &= pc;
			return *static_cast<playerpiecesType*>(this);
		}
		PYGMALION_INLINE constexpr playerpiecesType& operator-=(const playerpieceType index) noexcept
		{
			const playerType pl{ index.player() };
			const pieceType pc{ index.piece() };
			m_Pieces[pl] -= pc;
			return *static_cast<playerpiecesType*>(this);
		}
		PYGMALION_INLINE constexpr playerpiecesType& operator^=(const playerpieceType index) noexcept
		{
			const playerType pl{ index.player() };
			const pieceType pc{ index.piece() };
			m_Pieces[pl] ^= pc;
			return *static_cast<playerpiecesType*>(this);
		}
		PYGMALION_INLINE constexpr bool operator[](const playerpieceType index) const noexcept
		{
			return m_Pieces[index.player()][index.piece()];
		}
		PYGMALION_INLINE constexpr operator bool() const noexcept
		{
			for (const auto pl : playerType::range)
			{
				if (m_Pieces[pl])
					return true;
			}
			return false;
		}
		PYGMALION_INLINE constexpr playerpieces(const playerpieceType index) noexcept :
			m_Pieces{ arrayhelper::make<countPlayers>(piecesType::none()) }
		{
			m_Pieces[index.player()].set(index.piece());
		}
		PYGMALION_INLINE size_t count() const noexcept
		{
			size_t count{ 0 };
			for (const auto pl : playerType::range)
				count += m_Pieces[pl].count();
		}
		PYGMALION_INLINE constexpr void clearElement(const playerpieceType index) noexcept
		{
			m_Pieces[index.player()].clearElement(index.piece());
		}
		PYGMALION_INLINE constexpr void setElement(const playerpieceType index) noexcept
		{
			m_Pieces[index.player()].setElement(index.piece());
		}
		PYGMALION_INLINE constexpr void checkElement(const playerpieceType index, bool bSet) noexcept
		{
			m_Pieces[index.player()].checkElement(index.piece(), bSet);
		}
	};
}