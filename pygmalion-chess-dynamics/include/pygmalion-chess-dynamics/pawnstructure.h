namespace pygmalion::chess
{
	template<typename DESCRIPTOR_DYNAMICS>
	class pawnlookupPosition :
		DESCRIPTOR_DYNAMICS
	{
	public:
		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include <pygmalion-dynamics/include_dynamics.h>
		constexpr static const inline size_t countMaxSuccessors{ 10 };
	private:
		squaresType m_WhitePawns;
		squaresType m_BlackPawns;
		int m_Outcome;
		bool m_IsSolved;
		bool m_IsLegal;
		playerType m_MovingSide;
	public:
		playerType& movingSide() noexcept
		{
			return m_MovingSide;
		}
		const playerType& movingSide() const noexcept
		{
			return m_MovingSide;
		}
		pawnlookupPosition() noexcept :
			m_WhitePawns{ squaresType::none() },
			m_BlackPawns{ squaresType::none() },
			m_Outcome{ 0 },
			m_IsSolved{ false },
			m_IsLegal{ false },
			m_MovingSide{ playerType::invalid }
		{
		}
		squaresType& whitePawns() noexcept
		{
			return m_WhitePawns;
		}
		const squaresType& whitePawns() const noexcept
		{
			return m_WhitePawns;
		}
		squaresType& blackPawns() noexcept
		{
			return m_BlackPawns;
		}
		const squaresType& blackPawns() const noexcept
		{
			return m_BlackPawns;
		}
		bool& isSolved() noexcept
		{
			return m_IsSolved;
		}
		bool& isLegal() noexcept
		{
			return m_IsLegal;
		}
		int& outcome() noexcept
		{
			return m_Outcome;
		}
		std::uint32_t computeIndex() const noexcept
		{
			std::uint32_t A_white{ 0 };
			std::uint32_t B_white{ 0 };
			std::uint32_t C_white{ 0 };
			std::uint32_t A_black{ 0 };
			std::uint32_t B_black{ 0 };
			std::uint32_t C_black{ 0 };
			std::uint32_t side{ 0 };
			squareType sq;
			if (whitePawns() & descriptorDynamics::fileB)
			{
				sq = (whitePawns() & descriptorDynamics::fileB).last();
				A_white = static_cast<std::int8_t>(sq.rank());
			}
			else
				A_white = 0;
			if (whitePawns() & descriptorDynamics::fileC)
			{
				sq = (whitePawns() & descriptorDynamics::fileC).last();
				B_white = static_cast<std::int8_t>(sq.rank());
			}
			else
				B_white = 0;
			if (whitePawns() & descriptorDynamics::fileD)
			{
				sq = (whitePawns() & descriptorDynamics::fileD).last();
				C_white = static_cast<std::int8_t>(sq.rank());
			}
			else
				C_white = 0;
			if (blackPawns() & descriptorDynamics::fileB)
			{
				sq = (blackPawns() & descriptorDynamics::fileB).first();
				A_black = static_cast<std::int8_t>(sq.rank());
			}
			else
				A_black = 0;
			if (blackPawns() & descriptorDynamics::fileC)
			{
				sq = (blackPawns() & descriptorDynamics::fileC).first();
				B_black = static_cast<std::int8_t>(sq.rank());
			}
			else
				B_black = 0;
			if (blackPawns() & descriptorDynamics::fileD)
			{
				sq = (blackPawns() & descriptorDynamics::fileD).first();
				C_black = static_cast<std::int8_t>(sq.rank());
			}
			else
				C_black = 0;
			side = static_cast<std::int8_t>(movingSide());
			const std::uint32_t index2{ static_cast<std::uint32_t>(side + 2 * (A_white + 7 * (B_white + 7 * (C_white + 7 * (A_black + 7 * (B_black + 7 * C_black)))))) };
			return index2;
		}
		void generateSuccessors(std::array<pawnlookupPosition, 10>& successors, size_t& countSuccessors) const noexcept
		{
			countSuccessors = 0;
			if (m_MovingSide == descriptorDynamics::whitePlayer)
			{
				for (const auto from : m_WhitePawns)
				{
					const squareType to{ from.up() };
					if (!((m_BlackPawns | m_WhitePawns)[to]))
					{
						pawnlookupPosition successor;
						successor.blackPawns() = m_BlackPawns;
						successor.whitePawns() = m_WhitePawns;
						successor.whitePawns()[to] = true;
						successor.whitePawns()[from] = false;
						successor.movingSide() = m_MovingSide.next();
						successors[countSuccessors] = successor;
						countSuccessors++;
					}
					const squareType capLeft{ from.upLeft() };
					if ((!m_WhitePawns[capLeft]) && m_BlackPawns[capLeft])
					{
						pawnlookupPosition successor;
						successor.blackPawns() = m_BlackPawns;
						successor.whitePawns() = m_WhitePawns;
						successor.blackPawns()[capLeft] = false;
						successor.whitePawns()[capLeft] = true;
						successor.whitePawns()[from] = false;
						successor.movingSide() = m_MovingSide.next();
						successors[countSuccessors] = successor;
						countSuccessors++;
					}
					const squareType capRight{ from.upRight() };
					if ((!m_WhitePawns[capRight]) && m_BlackPawns[capRight])
					{
						pawnlookupPosition successor;
						successor.blackPawns() = m_BlackPawns;
						successor.whitePawns() = m_WhitePawns;
						successor.blackPawns()[capRight] = false;
						successor.whitePawns()[capRight] = true;
						successor.whitePawns()[from] = false;
						successor.movingSide() = m_MovingSide.next();
						successors[countSuccessors] = successor;
						countSuccessors++;
					}
				}
			}
			else
			{
				for (const auto from : m_BlackPawns)
				{
					const squareType to{ from.down() };
					if (!((m_BlackPawns | m_WhitePawns)[to]))
					{
						pawnlookupPosition successor;
						successor.blackPawns() = m_BlackPawns;
						successor.whitePawns() = m_WhitePawns;
						successor.blackPawns()[to] = true;
						successor.blackPawns()[from] = false;
						successor.movingSide() = m_MovingSide.next();
						successors[countSuccessors] = successor;
						countSuccessors++;
					}
					const squareType capLeft{ from.downLeft() };
					if ((!m_BlackPawns[capLeft]) && m_WhitePawns[capLeft])
					{
						pawnlookupPosition successor;
						successor.blackPawns() = m_BlackPawns;
						successor.whitePawns() = m_WhitePawns;
						successor.whitePawns()[capLeft] = false;
						successor.blackPawns()[capLeft] = true;
						successor.blackPawns()[from] = false;
						successor.movingSide() = m_MovingSide.next();
						successors[countSuccessors] = successor;
						countSuccessors++;
					}
					const squareType capRight{ from.downRight() };
					if ((!m_BlackPawns[capRight]) && m_WhitePawns[capRight])
					{
						pawnlookupPosition successor;
						successor.blackPawns() = m_BlackPawns;
						successor.whitePawns() = m_WhitePawns;
						successor.whitePawns()[capRight] = false;
						successor.blackPawns()[capRight] = true;
						successor.blackPawns()[from] = false;
						successor.movingSide() = m_MovingSide.next();
						successors[countSuccessors] = successor;
						countSuccessors++;
					}
				}
			}
			pawnlookupPosition pass;
			pass.blackPawns() = m_BlackPawns;
			pass.whitePawns() = m_WhitePawns;
			pass.movingSide() = m_MovingSide.next();
			successors[countSuccessors] = pass;
			countSuccessors++;
		}
		~pawnlookupPosition() noexcept = default;
		pawnlookupPosition(const pawnlookupPosition&) noexcept = default;
		pawnlookupPosition(pawnlookupPosition&&) noexcept = default;
		pawnlookupPosition& operator=(const pawnlookupPosition&) noexcept = default;
		pawnlookupPosition& operator=(pawnlookupPosition&&) noexcept = default;
	};

	class pawnlookup :
		public descriptor_dynamics
	{
		friend class pawnstructure;
	public:
		using descriptorDynamics = descriptor_dynamics;
#include "pygmalion-dynamics/include_dynamics.h"
		constexpr static inline const std::uint32_t countPositions{ 7 * 7 * 7 * 7 * 7 * 7 * 2 };
	private:
		constexpr static const std::uint32_t fileVersion{ UINT64_C(6) };
		signed char* m_pData;
		const signed char& entry(const std::uint32_t index) const noexcept
		{
			PYGMALION_ASSERT(index < countPositions);
			return m_pData[index];
		}
	public:
		void loadData() noexcept;
		pawnlookup() noexcept;
		~pawnlookup() noexcept;
	};

	class pawnstructure :
		public descriptor_dynamics
	{
	public:
		using descriptorDynamics = descriptor_dynamics;
#include "pygmalion-dynamics/include_dynamics.h"
	private:
		static const pawnlookup m_LookUp;
	public:
		static std::int8_t distance(const playerType movingPlayer, const std::int8_t file1white, const std::int8_t file2white, const std::int8_t file3white, const std::int8_t file1black, const std::int8_t file2black, const std::int8_t file3black) noexcept
		{
			const std::uint32_t index{ static_cast<std::uint32_t>(static_cast<std::uint32_t>(movingPlayer) + 2 * (file1white + 7 * (file2white + 7 * (file3white + 7 * (file1black + 7 * (file2black + 7 * file3black)))))) };
			return static_cast<std::int8_t>(m_LookUp.entry(index));
		}
	};
}