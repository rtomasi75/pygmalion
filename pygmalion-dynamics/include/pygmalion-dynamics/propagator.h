namespace pygmalion::dynamics
{
	template<typename MOTOR, size_t RANGE, typename... RAYS >
	class propagator :
		public MOTOR::descriptorMechanics
	{
	public:
		using descriptorMechanics = typename MOTOR::descriptorMechanics;
#include "pygmalion-mechanics/include_mechanics.h"
		constexpr static const size_t countRays{ sizeof...(RAYS) };
	private:
		template<typename RAY>
		constexpr static void propagateRayStep(const squaresType& seeds, squaresType& destinations) noexcept
		{
			squaresType pattern{ seeds };
			if constexpr (RAY::fileIncrement > 0)
			{
				for (int i = 0; i < RAY::fileIncrement; i++)
				{
					pattern = pattern.right();
				}
			}
			else if constexpr (RAY::fileIncrement > 0)
			{
				for (int i = 0; i < -RAY::fileIncrement; i++)
				{
					pattern = pattern.left();
				}
			}
			if constexpr (RAY::rankIncrement > 0)
			{
				for (int i = 0; i < RAY::rankIncrement; i++)
				{
					pattern = pattern.up();
				}
			}
			else if constexpr (RAY::rankIncrement > 0)
			{
				for (int i = 0; i < -RAY::rankIncrement; i++)
				{
					pattern = pattern.down();
				}
			}
			destinations |= pattern;
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static void propagateRay(const squaresType& seeds, const squaresType& allowed, squaresType& destinations) noexcept
		{
			if constexpr (DISTANCE < RANGE)
			{
				squaresType pattern{ squaresType::none() };
				propagator::propagateRayStep<RAY>(seeds, pattern);
				const squaresType targets{ pattern & allowed };
				destinations |= targets;
				propagator::propagateRay<RAY, DISTANCE + 1>(targets, allowed, destinations);
			}
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void propagate(const squaresType& seeds, const squaresType& allowed, squaresType& destinations) noexcept
		{
			propagator::propagateRay<RAY, 0>(seeds, allowed, destinations);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::propagate<RAYS2...>(seeds, allowed, destinations);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void fillTargets(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::propagateRay<RAY, 0>(seeds, allowed, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::fillTargets<RAYS2...>(seeds, allowed, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void fillAttacks(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::propagateRay<RAY, 0>(seeds, allowed, targets);
			propagator::propagateRayStep<RAY>(targets, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::fillAttacks<RAYS2...>(seeds, allowed, targets);
		}
	public:
		constexpr propagator() noexcept = default;
		constexpr propagator(const propagator&) noexcept = default;
		constexpr propagator(propagator&&) noexcept = default;
		constexpr propagator& operator=(const propagator&) noexcept = default;
		constexpr propagator& operator=(propagator&&) noexcept = default;
		~propagator() noexcept = default;
		constexpr static squaresType propagate(const squaresType& seeds) noexcept
		{
			const squaresType destinations{ squaresType::none() };
			propagator::propagate<RAYS...>(seeds, destinations);
			return destinations;
		}
		constexpr static squaresType targets(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			squaresType targets{ squaresType::none() };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::fillTargets<RAYS...>(seeds, allowed, targets);
			return targets;
		}
		constexpr static squaresType attacks(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			squaresType attacks{ squaresType::none() };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::fillAttacks<RAYS...>(seeds, allowed, attacks);
			return targets;
		}
	};

	template<typename MOTOR, typename... RAYS >
	class propagator<MOTOR, 1, RAYS...> :
		public MOTOR::descriptorMechanics
	{
	public:
		using descriptorMechanics = typename MOTOR::descriptorMechanics;
#include "pygmalion-mechanics/include_mechanics.h"
		constexpr static const size_t countRays{ sizeof...(RAYS) };
	private:
		template<typename RAY>
		constexpr static void propagateRayStep(const squaresType& seeds, squaresType& destinations) noexcept
		{
			squaresType pattern{ seeds };
			if constexpr (RAY::fileIncrement > 0)
			{
				for (int i = 0; i < RAY::fileIncrement; i++)
				{
					pattern = pattern.right();
				}
			}
			else if constexpr (RAY::fileIncrement > 0)
			{
				for (int i = 0; i < -RAY::fileIncrement; i++)
				{
					pattern = pattern.left();
				}
			}
			if constexpr (RAY::rankIncrement > 0)
			{
				for (int i = 0; i < RAY::rankIncrement; i++)
				{
					pattern = pattern.up();
				}
			}
			else if constexpr (RAY::rankIncrement > 0)
			{
				for (int i = 0; i < -RAY::rankIncrement; i++)
				{
					pattern = pattern.down();
				}
			}
			destinations |= pattern;
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static void propagateRay(const squaresType& seeds, const squaresType& allowed, squaresType& destinations) noexcept
		{
			squaresType pattern{ squaresType::none() };
			propagator::propagateRayStep<RAY>(seeds, pattern);
			const squaresType targets{ pattern & allowed };
			destinations |= targets;
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void propagate(const squaresType& seeds, const squaresType& allowed, squaresType& destinations) noexcept
		{
			propagator::propagateRay<RAY, 0>(seeds, allowed, destinations);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::propagate<RAYS2...>(seeds, allowed, destinations);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void fillTargets(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::propagateRay<RAY, 0>(seeds, allowed, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::fillTargets<RAYS2...>(seeds, allowed, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void fillAttacks(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::propagateRayStep<RAY>(seeds, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::fillAttacks<RAYS2...>(seeds, allowed, targets);
		}
	public:
		constexpr propagator() noexcept = default;
		constexpr propagator(const propagator&) noexcept = default;
		constexpr propagator(propagator&&) noexcept = default;
		constexpr propagator& operator=(const propagator&) noexcept = default;
		constexpr propagator& operator=(propagator&&) noexcept = default;
		~propagator() noexcept = default;
		constexpr static squaresType propagate(const squaresType& seeds) noexcept
		{
			squaresType destinations{ squaresType::none() };
			propagator::propagate<RAYS...>(seeds, squaresType::all(), destinations);
			return destinations;
		}
		constexpr static squaresType targets(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			squaresType targets{ squaresType::none() };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::fillTargets<RAYS...>(seeds, allowed, targets);
			return targets;
		}
		constexpr static squaresType attacks(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			squaresType attacks{ squaresType::none() };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::fillAttacks<RAYS...>(seeds, allowed, attacks);
			return targets;
		}
	private:
		constexpr static const inline std::array<squaresType, countSquares> m_PropagationTable{ arrayhelper::generate<countSquares,squaresType>([](const size_t index)->squaresType { return propagate(static_cast<squaresType>(static_cast<squareType>(static_cast<typename std::make_unsigned<size_t>::type>(index)))); }) };
	public:
		constexpr static squaresType propagate(const squareType seed) noexcept
		{
			return m_PropagationTable[seed];
		}
		constexpr static squaresType targets(const squareType seed, const squaresType& allowed) noexcept
		{
			return m_PropagationTable[seed] & allowed;
		}
		constexpr static squaresType attacks(const squareType seed, const squaresType& allowed) noexcept
		{
			return m_PropagationTable[seed];
		}
	};
}