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
		constexpr movegen(const squaresType allowedTo, const squaresType allowedFrom) noexcept :
			m_AllowedToSquares{ allowedTo },
			m_AllowedFromSquares{ allowedFrom }
		{}
		~movegen() noexcept = default;
		constexpr movegen(const movegen&) noexcept = default;
		constexpr movegen(movegen&&) noexcept = default;
		constexpr movegen& operator=(const movegen&) noexcept = default;
		constexpr movegen& operator=(movegen&&) noexcept = default;
		constexpr squaresType propagate(const squareType seed) const noexcept
		{
			if (m_AllowedFromSquares[seed])
				return propagatorType::propagate(seed) & m_AllowedToSquares;
			else
				return squaresType::none();
		}
		constexpr squaresType targets(const squareType seed, const squaresType& allowed) const noexcept
		{
			if (m_AllowedFromSquares[seed])
				return propagatorType::targets(seed, allowed) & m_AllowedToSquares;
			else
				return squaresType::none();
		}
		constexpr squaresType attacks(const squareType seed, const squaresType& allowed) const noexcept
		{
			if (m_AllowedFromSquares[seed])
				return propagatorType::attacks(seed, allowed) & m_AllowedToSquares;
			else
				return squaresType::none();
		}
		constexpr squaresType propagate(const squaresType& seeds) const noexcept
		{
			return propagatorType::propagate(seeds & m_AllowedFromSquares) & m_AllowedToSquares;
		}
		constexpr squaresType targets(const squaresType& seeds, const squaresType& allowed) const noexcept
		{
			return propagatorType::targets(seeds & m_AllowedFromSquares, allowed) & m_AllowedToSquares;
		}
		constexpr squaresType attacks(const squaresType& seeds, const squaresType& allowed) const noexcept
		{
			return propagatorType::attacks(seeds & m_AllowedFromSquares, allowed) & m_AllowedToSquares;
		}
	};
}