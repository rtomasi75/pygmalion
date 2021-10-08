namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class signature :
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
		constexpr static inline size_t counterBits{ arrayhelper::requiredUnsignedBits(countSquares) };
		constexpr static inline size_t countBits{ counterBits * (countPieces + countPlayers) };
		using storageType = uint_t<counterBits, false>;
	private:
		std::array<storageType, countPieces> m_PieceCounts;
		std::array<storageType, countPlayers> m_PlayerCounts;
	public:
		PYGMALION_INLINE constexpr signature(const signature&) noexcept = default;
		PYGMALION_INLINE constexpr signature(signature&&) noexcept = default;
		PYGMALION_INLINE constexpr signature() noexcept :
			m_PieceCounts{ arrayhelper::make<countPieces,storageType>(storageType(0)) },
			m_PlayerCounts{ arrayhelper::make<countPlayers,storageType>(storageType(0)) }
		{

		}
		PYGMALION_INLINE constexpr void clear() noexcept
		{
			for (const auto pc : pieceType::range)
				m_PieceCounts[pc] = storageType(0);
			for (const auto pl : playerType::range)
				m_PlayerCounts[pl] = storageType(0);
		}
		PYGMALION_INLINE constexpr void addPiece(const pieceType pc, const playerType pl) noexcept
		{
			m_PieceCounts[pc]++;
			m_PlayerCounts[pl]++;
		}
		PYGMALION_INLINE constexpr void removePiece(const pieceType pc, const playerType pl) noexcept
		{
			m_PieceCounts[pc]--;
			m_PlayerCounts[pl]--;
		}
		PYGMALION_INLINE constexpr storageType count(const pieceType pc) const noexcept
		{
			return m_PieceCounts[pc];
		}
		PYGMALION_INLINE constexpr storageType count(const playerType pl) const noexcept
		{
			return m_PlayerCounts[pl];
		}
		std::string toString() const noexcept
		{
			std::stringstream str{ std::stringstream() };
			for (const auto pl : playerType::range)
			{
				str << static_cast<unsigned int>(m_PlayerCounts[pl]);
				str << "|";
			}
			for (const auto pc : pieceType::range)
			{
				str << "|";
				str << static_cast<unsigned int>(m_PieceCounts[pc]);
			}
			return str.str();
		}
		PYGMALION_INLINE constexpr signature& operator=(signature&&) noexcept = default;
		PYGMALION_INLINE constexpr signature& operator=(const signature&) noexcept = default;
		PYGMALION_INLINE constexpr bool operator==(const signature& other) const noexcept
		{
			for (const auto pl : playerType::range)
				if (m_PlayerCounts[pl] != other.m_PlayerCounts[pl]) return false;
			for (const auto pc : pieceType::range)
				if (m_PieceCounts[pc] != other.m_PieceCounts[pc]) return false;
			return true;
		}
		PYGMALION_INLINE constexpr bool operator!=(const signature& other) const noexcept
		{
			for (const auto pl : playerType::range)
				if (m_PlayerCounts[pl] != other.m_PlayerCounts[pl]) return true;
			for (const auto pc : pieceType::range)
				if (m_PieceCounts[pc] != other.m_PieceCounts[pc]) return true;
			return false;
		}
	};
}