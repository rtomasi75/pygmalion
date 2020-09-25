namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, size_t RANGE, typename INSTANCE, typename... RAYS >
	class propagator :
		public DESCRIPTION_DYNAMICS
	{
	public:
		using instanceType = INSTANCE;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
#include "include_dynamics.h"
		constexpr static const size_t countRays{ sizeof...(RAYS) };
	private:
		template<typename RAY>
		constexpr static void computeRayStep(const squaresType& seeds, squaresType& destinations) noexcept
		{
			squaresType pattern{ seeds };
			if constexpr (RAY::fileIncrement > 0)
			{
				for (int i = 0; i < RAY::fileIncrement; i++)
				{
					pattern = pattern.right();
				}
			}
			else if constexpr (RAY::fileIncrement < 0)
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
			else if constexpr (RAY::rankIncrement < 0)
			{
				for (int i = 0; i < -RAY::rankIncrement; i++)
				{
					pattern = pattern.down();
				}
			}
			destinations |= pattern;
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static void computeAttackRay(const squaresType& seeds, const squaresType& allowed, squaresType& destinations) noexcept
		{
			if constexpr (DISTANCE < RANGE)
			{
				squaresType pattern{ squaresType::none() };
				propagator::computeRayStep<RAY>(seeds, pattern);
				destinations |= pattern;
				propagator::computeAttackRay<RAY, DISTANCE + 1>(pattern & allowed, allowed, destinations);
			}
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static void computeTargetRay(const squaresType& seeds, const squaresType& allowed, squaresType& destinations) noexcept
		{
			if constexpr (DISTANCE < RANGE)
			{
				squaresType pattern{ squaresType::none() };
				propagator::computeRayStep<RAY>(seeds, pattern);
				const squaresType targets{ pattern & allowed };
				destinations |= targets;
				propagator::computeTargetRay<RAY, DISTANCE + 1>(targets, allowed, destinations);
			}
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static void computeRelevantRay(const squaresType& seeds, squaresType& destinations) noexcept
		{
			if constexpr ((DISTANCE + 1) < RANGE)
			{
				squaresType pattern{ squaresType::none() };
				propagator::computeRayStep<RAY>(seeds, pattern);
				if (pattern)
				{
					destinations |= seeds;
					propagator::computeRelevantRay<RAY, DISTANCE + 1>(pattern, destinations);
				}
			}
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeTargets(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::computeTargetRay<RAY, 0>(seeds, allowed, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeTargets<RAYS2...>(seeds, allowed, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeRelevant(const squaresType& seeds, squaresType& targets) noexcept
		{
			squaresType pattern{ squaresType::none() };
			propagator::computeRayStep<RAY>(seeds, pattern);
			if (pattern)
			{
				propagator::computeRelevantRay<RAY, 0>(pattern, targets);
			}
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeRelevant<RAYS2...>(seeds, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeAttacks(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::computeAttackRay<RAY, 0>(seeds, allowed, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeAttacks<RAYS2...>(seeds, allowed, targets);
		}
		constexpr static squaresType relevant(const squaresType& seeds) noexcept
		{
			squaresType mask{ squaresType::none() };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeRelevant<RAYS...>(seeds, mask);
			return mask;
		}
	private:
		static inline std::array<slidermagic<descriptorDynamics, propagator>, countSquares> m_Magic{ arrayhelper::generate<countSquares, slidermagic<descriptorDynamics, propagator>>([](const size_t index)->slidermagic<descriptorDynamics, propagator> { return slidermagic<descriptorDynamics, propagator>(slidermagicinfo<descriptorDynamics>(static_cast<squareType>(index)),instanceType::magicFactor(index),propagator::relevant(squaresType(static_cast<squareType>(static_cast<typename squareType::baseType>(index)))).count()); }) };
	public:
		constexpr static slidermagic<descriptorDynamics, propagator>& magic(const squareType sq) noexcept
		{
			return m_Magic[sq];
		}
		constexpr propagator() noexcept = default;
		constexpr propagator(const propagator&) noexcept = default;
		constexpr propagator(propagator&&) noexcept = default;
		constexpr propagator& operator=(const propagator&) noexcept = default;
		constexpr propagator& operator=(propagator&&) noexcept = default;
		~propagator() noexcept = default;
		constexpr static squaresType targets(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			squaresType targets{ squaresType::none() };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeTargets<RAYS...>(seeds, allowed, targets);
			return targets;
		}
		constexpr static squaresType attacks(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			squaresType attacks{ squaresType::none() };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeAttacks<RAYS...>(seeds, allowed, attacks);
			return attacks;
		}
		constexpr static squaresType targets(const squareType seed, const squaresType& allowed) noexcept
		{
			return m_Magic[seed][~allowed] & allowed;
		}
		constexpr static squaresType attacks(const squareType seed, const squaresType& allowed) noexcept
		{
			return m_Magic[seed][~allowed];
		}
		constexpr static squaresType relevant(const squareType seed) noexcept
		{
			return propagator::relevant(squaresType(seed));
		}
	};

	template<typename DESCRIPTION_DYNAMICS, typename INSTANCE, typename... RAYS >
	class propagator<DESCRIPTION_DYNAMICS, 1, INSTANCE, RAYS...> :
		public DESCRIPTION_DYNAMICS
	{
	public:
		using instanceType = INSTANCE;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
#include "include_dynamics.h"
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
			else if constexpr (RAY::fileIncrement < 0)
			{
				for (int i = RAY::fileIncrement; i < 0; i++)
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
			else if constexpr (RAY::rankIncrement < 0)
			{
				for (int i = RAY::rankIncrement; i < 0; i++)
				{
					pattern = pattern.down();
				}
			}
			destinations |= pattern;
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeTargets(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			squaresType ray{ squaresType::none() };
			propagator::propagateRayStep<RAY>(seeds, ray);
			targets |= ray & allowed;
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeTargets<RAYS2...>(seeds, allowed, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeAttacks(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::propagateRayStep<RAY>(seeds, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeAttacks<RAYS2...>(seeds, allowed, targets);
		}
	public:
		constexpr propagator() noexcept = default;
		constexpr propagator(const propagator&) noexcept = default;
		constexpr propagator(propagator&&) noexcept = default;
		constexpr propagator& operator=(const propagator&) noexcept = default;
		constexpr propagator& operator=(propagator&&) noexcept = default;
		~propagator() noexcept = default;
		constexpr static squaresType targets(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			squaresType targets{ squaresType::none() };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeTargets<RAYS...>(seeds, allowed, targets);
			return targets;
		}
		constexpr static squaresType attacks(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			squaresType attacks{ squaresType::none() };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeAttacks<RAYS...>(seeds, allowed, attacks);
			return attacks;
		}
	private:
		constexpr static const inline std::array<squaresType, countSquares> m_PropagationTable{ arrayhelper::generate<countSquares,squaresType>([](const size_t index)->squaresType { return attacks(static_cast<squaresType>(static_cast<squareType>(static_cast<typename std::make_unsigned<size_t>::type>(index))),squaresType::all()); }) };
	public:
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