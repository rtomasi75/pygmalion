namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class signature :
		public enumeration<DESCRIPTION_STATE::countSquares, DESCRIPTION_STATE::countHashBits, square<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
		friend class file<DESCRIPTION_STATE>;
		friend class rank<DESCRIPTION_STATE>;
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
	private:
		constexpr static size_t requiredUnsignedBits(const size_t number) noexcept
		{
			size_t n = 1;
			size_t k = 0;
			while (number > n)
			{
				n *= 2;
				k++;
			}
			return k;
		}
	public:
		constexpr static inline size_t counterBits{ requiredUnsignedBits(countSquares) };
		constexpr static inline size_t countBits{ counterBits * (countPieces + countPlayers) };
		using storageType = uint_t<counterBits, false>;
	private:
		std::array<storageType, countPieces> m_PieceCounts;
		std::array<storageType, countPlayers> m_PlayerCounts;
	public:
		constexpr rankType rank() const noexcept
		{
			assert(this->isValid());
			return (*this) / countFiles;
		}
		constexpr fileType file() const noexcept
		{
			assert(this->isValid());
			return (*this) % countFiles;
		}
		constexpr bool isDark() const noexcept
		{
			return (rank() + file()) % 2 == 0;
		}
		constexpr signature(const signature&) noexcept = default;
		constexpr signature(signature&&) noexcept = default;
		constexpr signature() noexcept :
			m_PieceCounts{ arrayhelper::make<countPieces,storageType>(storageType(0)) },
			m_PlayerCounts{ arrayhelper::make<countPlayers,storageType>(storageType(0)) }
		{

		}
		constexpr void clear() noexcept
		{
			for (const auto pc : pieceType::range)
				m_PieceCounts[pc] = storageType(0);
			for (const auto pl : playerType::range)
				m_PlayerCounts[pl] = storageType(0);
		}
		constexpr void addPiece(const pieceType pc, const playerType pl) noexcept
		{
			m_PieceCounts[pc]++;
			m_PlayerCounts[pl]++;
		}
		constexpr void removePiece(const pieceType pc, const playerType pl) noexcept
		{
			m_PieceCounts[pc]--;
			m_PlayerCounts[pl]--;
		}
		constexpr storageType count(const pieceType pc) const noexcept
		{
			return m_PieceCounts[pc];
		}
		constexpr storageType count(const playerType pl) const noexcept
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
		constexpr signature& operator=(signature&&) noexcept = default;
		constexpr signature& operator=(const signature&) noexcept = default;
		constexpr bool operator==(const signature& other) const noexcept
		{
			for (const auto pl : playerType::range)
				if (m_PlayerCounts[pl] != other.m_PlayerCounts[pl]) return false;
			for (const auto pc : pieceType::range)
				if (m_PieceCounts[pc] != other.m_PieceCounts[pc]) return false;
			return true;
		}
		constexpr bool operator!=(const signature& other) const noexcept
		{
			for (const auto pl : playerType::range)
				if (m_PlayerCounts[pl] != other.m_PlayerCounts[pl]) return true;
			for (const auto pc : pieceType::range)
				if (m_PieceCounts[pc] != other.m_PieceCounts[pc]) return true;
			return false;
		}
	};
}