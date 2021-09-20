namespace pygmalion::dynamics
{
	template<typename MOTOR, typename PROPAGATOR>
	class movegen :
		public MOTOR::descriptorMechanics
	{
	public:
		using propagatorType = PROPAGATOR;
		using descriptorMechanics = typename MOTOR::descriptorMechanics;
#include "pygmalion-mechanics/include_mechanics.h"
	private:
		const squaresType m_AllowedToSquares;
		const squaresType m_AllowedFromSquares;
	public:
		constexpr const squaresType& allowedToSquares() const noexcept
		{
			return m_AllowedToSquares;
		}
		constexpr const squaresType& allowedFromSquares() const noexcept
		{
			return m_AllowedFromSquares;
		}
		constexpr movegen(const squaresType& allowedTo, const squaresType& allowedFrom) noexcept :
			m_AllowedToSquares{ allowedTo },
			m_AllowedFromSquares{ allowedFrom }
		{}
		~movegen() noexcept = default;
		constexpr movegen(const movegen&) noexcept = default;
		constexpr movegen(movegen&&) noexcept = default;
		constexpr movegen& operator=(const movegen&) noexcept = default;
		constexpr movegen& operator=(movegen&&) noexcept = default;
		constexpr squaresType targets(const squareType& seed, const squaresType& allowed) const noexcept
		{
			if (m_AllowedFromSquares[seed])
				return propagatorType::targets(seed, allowed) & m_AllowedToSquares;
			else
				return squaresType::none();
		}
		constexpr squaresType inverseTargets(const squareType& seed, const squaresType& allowed) const noexcept
		{
			if (m_AllowedToSquares[seed])
				return propagatorType::inverseTargets(seed, allowed) & m_AllowedFromSquares;
			else
				return squaresType::none();
		}
		constexpr squaresType untabled_targets(const squareType& seed, const squaresType& allowed) const noexcept
		{
			if (m_AllowedFromSquares[seed])
				return propagatorType::targets(squaresType(seed), allowed) & m_AllowedToSquares;
			else
				return squaresType::none();
		}
		constexpr squaresType untabled_inverseTargets(const squareType& seed, const squaresType& allowed) const noexcept
		{
			if (m_AllowedToSquares[seed])
				return propagatorType::inverseTargets(squaresType(seed), allowed) & m_AllowedFromSquares;
			else
				return squaresType::none();
		}
		constexpr squaresType attacks(const squareType& seed, const squaresType& allowed) const noexcept
		{
			if (m_AllowedFromSquares[seed])
				return propagatorType::attacks(seed, allowed) & m_AllowedToSquares;
			else
				return squaresType::none();
		}
		constexpr squaresType inverseAttacks(const squareType& seed, const squaresType& allowed) const noexcept
		{
			if (m_AllowedToSquares[seed])
				return propagatorType::inverseAttacks(seed, allowed) & m_AllowedFromSquares;
			else
				return squaresType::none();
		}
		constexpr squaresType untabled_attacks(const squareType& seed, const squaresType& allowed) const noexcept
		{
			if (m_AllowedFromSquares[seed])
				return propagatorType::attacks(squaresType(seed), allowed) & m_AllowedToSquares;
			else
				return squaresType::none();
		}
		constexpr squaresType untabled_inverseAttacks(const squareType& seed, const squaresType& allowed) const noexcept
		{
			if (m_AllowedToSquares[seed])
				return propagatorType::inverseAttacks(squaresType(seed), allowed) & m_AllowedFromSquares;
			else
				return squaresType::none();
		}
		constexpr squaresType targets(const squaresType& seeds, const squaresType& allowed) const noexcept
		{
			return propagatorType::targets(seeds & m_AllowedFromSquares, allowed) & m_AllowedToSquares;
		}
		constexpr squaresType inverseTargets(const squaresType& seeds, const squaresType& allowed) const noexcept
		{
			return propagatorType::inverseTargets(seeds & m_AllowedToSquares, allowed) & m_AllowedFromSquares;
		}
		constexpr squaresType attacks(const squaresType& seeds, const squaresType& allowed) const noexcept
		{
			return propagatorType::attacks(seeds & m_AllowedFromSquares, allowed) & m_AllowedToSquares;
		}
		constexpr squaresType inverseAttacks(const squaresType& seeds, const squaresType& allowed) const noexcept
		{
			return propagatorType::inverseAttacks(seeds & m_AllowedToSquares, allowed) & m_AllowedFromSquares;
		}
	};
}