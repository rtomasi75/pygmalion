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
		template<typename RAY>
		constexpr static void computeInverseRayStep(const squaresType& seeds, squaresType& destinations) noexcept
		{
			squaresType pattern{ seeds };
			if constexpr (RAY::fileIncrement > 0)
			{
				for (int i = 0; i < RAY::fileIncrement; i++)
				{
					pattern = pattern.left();
				}
			}
			else if constexpr (RAY::fileIncrement < 0)
			{
				for (int i = 0; i < -RAY::fileIncrement; i++)
				{
					pattern = pattern.right();
				}
			}
			if constexpr (RAY::rankIncrement > 0)
			{
				for (int i = 0; i < RAY::rankIncrement; i++)
				{
					pattern = pattern.down();
				}
			}
			else if constexpr (RAY::rankIncrement < 0)
			{
				for (int i = 0; i < -RAY::rankIncrement; i++)
				{
					pattern = pattern.up();
				}
			}
			destinations |= pattern;
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static void computeAttackRay(const squaresType& seeds, const squaresType& allowed, squaresType& destinations) noexcept
		{
			if constexpr (DISTANCE < RANGE)
			{
				constexpr const squaresType none{ squaresType::none() };
				squaresType pattern{ none };
				propagator::computeRayStep<RAY>(seeds, pattern);
				destinations |= pattern;
				propagator::computeAttackRay<RAY, DISTANCE + 1>(pattern & allowed, allowed, destinations);
			}
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static void computeInverseAttackRay(const squaresType& seeds, const squaresType& allowed, squaresType& destinations) noexcept
		{
			if constexpr (DISTANCE < RANGE)
			{
				constexpr const squaresType none{ squaresType::none() };
				squaresType pattern{ none };
				propagator::computeInverseRayStep<RAY>(seeds, pattern);
				destinations |= pattern;
				propagator::computeInverseAttackRay<RAY, DISTANCE + 1>(pattern & allowed, allowed, destinations);
			}
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static void computeTargetRay(const squaresType& seeds, const squaresType& allowed, squaresType& destinations) noexcept
		{
			if constexpr (DISTANCE < RANGE)
			{
				constexpr const squaresType none{ squaresType::none() };
				squaresType pattern{ none };
				propagator::computeRayStep<RAY>(seeds, pattern);
				const squaresType targets{ pattern & allowed };
				destinations |= targets;
				propagator::computeTargetRay<RAY, DISTANCE + 1>(targets, allowed, destinations);
			}
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static void computeInverseTargetRay(const squaresType& seeds, const squaresType& allowed, squaresType& destinations) noexcept
		{
			if constexpr (DISTANCE < RANGE)
			{
				constexpr const squaresType none{ squaresType::none() };
				squaresType pattern{ none };
				propagator::computeInverseRayStep<RAY>(seeds, pattern);
				const squaresType targets{ pattern & allowed };
				destinations |= targets;
				propagator::computeInverseTargetRay<RAY, DISTANCE + 1>(targets, allowed, destinations);
			}
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static void computeRelevantRay(const squaresType& seeds, squaresType& destinations) noexcept
		{
			if constexpr ((DISTANCE + 1) < RANGE)
			{
				constexpr const squaresType none{ squaresType::none() };
				squaresType pattern{ none };
				propagator::computeRayStep<RAY>(seeds, pattern);
				if (pattern)
				{
					destinations |= seeds;
					propagator::computeRelevantRay<RAY, DISTANCE + 1>(pattern, destinations);
				}
			}
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static void computeInverseRelevantRay(const squaresType& seeds, squaresType& destinations) noexcept
		{
			if constexpr ((DISTANCE + 1) < RANGE)
			{
				constexpr const squaresType none{ squaresType::none() };
				squaresType pattern{ none };
				propagator::computeInverseRayStep<RAY>(seeds, pattern);
				if (pattern)
				{
					destinations |= seeds;
					propagator::computeInverseRelevantRay<RAY, DISTANCE + 1>(pattern, destinations);
				}
			}
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static size_t computePossibilitiesRay(const squaresType& seeds) noexcept
		{
			if constexpr ((DISTANCE + 1) < RANGE)
			{
				constexpr const squaresType none{ squaresType::none() };
				squaresType pattern{ none };
				propagator::computeRayStep<RAY>(seeds, pattern);
				if (pattern)
					return 1 + propagator::computePossibilitiesRay<RAY, DISTANCE + 1>(pattern);
			}
			return 0;
		}
		template<typename RAY, size_t DISTANCE>
		constexpr static size_t computeInversePossibilitiesRay(const squaresType& seeds) noexcept
		{
			if constexpr ((DISTANCE + 1) < RANGE)
			{
				constexpr const squaresType none{ squaresType::none() };
				squaresType pattern{ none };
				propagator::computeInverseRayStep<RAY>(seeds, pattern);
				if (pattern)
					return 1 + propagator::computeInversePossibilitiesRay<RAY, DISTANCE + 1>(pattern);
			}
			return 0;
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeTargets(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::computeTargetRay<RAY, 0>(seeds, allowed, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeTargets<RAYS2...>(seeds, allowed, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeInverseTargets(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::computeInverseTargetRay<RAY, 0>(seeds, allowed, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeInverseTargets<RAYS2...>(seeds, allowed, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeRelevant(const squaresType& seeds, squaresType& targets) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType pattern{ none };
			propagator::computeRayStep<RAY>(seeds, pattern);
			if (pattern)
			{
				propagator::computeRelevantRay<RAY, 0>(pattern, targets);
			}
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeRelevant<RAYS2...>(seeds, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeInverseRelevant(const squaresType& seeds, squaresType& targets) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType pattern{ none };
			propagator::computeInverseRayStep<RAY>(seeds, pattern);
			if (pattern)
			{
				propagator::computeInverseRelevantRay<RAY, 0>(pattern, targets);
			}
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeInverseRelevant<RAYS2...>(seeds, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static size_t computePossibilities(const squaresType& seeds) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType pattern{ none };
			propagator::computeRayStep<RAY>(seeds, pattern);
			size_t rayPossibilities{ 1 };
			if (pattern)
			{
				rayPossibilities += propagator::computePossibilitiesRay<RAY, 0>(pattern);
			}
			if constexpr (sizeof...(RAYS2) > 0)
				return rayPossibilities * propagator::computePossibilities<RAYS2...>(seeds);
			else
				return rayPossibilities;
		}
		template<typename RAY, typename... RAYS2>
		constexpr static size_t computeInversePossibilities(const squaresType& seeds) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType pattern{ none };
			propagator::computeInverseRayStep<RAY>(seeds, pattern);
			size_t rayPossibilities{ 1 };
			if (pattern)
			{
				rayPossibilities += propagator::computeInversePossibilitiesRay<RAY, 0>(pattern);
			}
			if constexpr (sizeof...(RAYS2) > 0)
				return rayPossibilities * propagator::computeInversePossibilities<RAYS2...>(seeds);
			else
				return rayPossibilities;
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeAttacks(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::computeAttackRay<RAY, 0>(seeds, allowed, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeAttacks<RAYS2...>(seeds, allowed, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeInverseAttacks(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::computeInverseAttackRay<RAY, 0>(seeds, allowed, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeInverseAttacks<RAYS2...>(seeds, allowed, targets);
		}
		constexpr static squaresType relevant(const squaresType& seeds) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType mask{ none };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeRelevant<RAYS...>(seeds, mask);
			return mask;
		}
		constexpr static squaresType inverseRelevant(const squaresType& seeds) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType mask{ none };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeInverseRelevant<RAYS...>(seeds, mask);
			return mask;
		}
		constexpr static size_t possibilities(const squaresType& seeds) noexcept
		{
			if constexpr (sizeof...(RAYS) > 0)
				return propagator::computePossibilities<RAYS...>(seeds);
			else
				return 1;
		}
		constexpr static size_t inversePossibilities(const squaresType& seeds) noexcept
		{
			if constexpr (sizeof...(RAYS) > 0)
				return propagator::computeInversePossibilities<RAYS...>(seeds);
			else
				return 1;
		}
	public:
		constexpr static squaresType targets(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType targets{ none };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeTargets<RAYS...>(seeds, allowed, targets);
			return targets;
		}
		constexpr static squaresType inverseTargets(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType targets{ none };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeInverseTargets<RAYS...>(seeds, allowed, targets);
			return targets;
		}
		constexpr static squaresType attacks(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType attacks{ none };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeAttacks<RAYS...>(seeds, allowed, attacks);
			return attacks;
		}
		constexpr static squaresType inverseAttacks(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType attacks{ none };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeInverseAttacks<RAYS...>(seeds, allowed, attacks);
			return attacks;
		}
		constexpr static size_t possibilities(const squareType seed) noexcept
		{
			return propagator::possibilities(squaresType(seed));
		}
		constexpr static size_t inversePossibilities(const squareType seed) noexcept
		{
			return propagator::inversePossibilities(squaresType(seed));
		}
		constexpr static size_t maxPossibilities() noexcept
		{
			size_t maxCount{ 0 };
			for (const auto sq : squareType::range)
				maxCount = std::max(maxCount, propagator::possibilities(sq));
			return maxCount;
		}
		constexpr static size_t maxInversePossibilities() noexcept
		{
			size_t maxCount{ 0 };
			for (const auto sq : squareType::range)
				maxCount = std::max(maxCount, propagator::inversePossibilities(sq));
			return maxCount;
		}
		constexpr static size_t countAttackSquares(const squareType seed) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			const squaresType attackSquares{ attacks(squaresType(seed),all) };
			size_t n{ 0 };
			for (const auto sq : squareType::range)
			{
				if (attackSquares[sq])
					n++;
			}
			return n;
		}
		constexpr static size_t countInverseAttackSquares(const squareType seed) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			const squaresType attackSquares{ inverseAttacks(squaresType(seed),all) };
			size_t n{ 0 };
			for (const auto sq : squareType::range)
			{
				if (attackSquares[sq])
					n++;
			}
			return n;
		}
		constexpr static size_t maxAttackSquares() noexcept
		{
			size_t n{ 0 };
			for (const auto sq : squareType::range)
				n = std::max(n, countAttackSquares(sq));
			return n;
		}
		constexpr static size_t maxInverseAttackSquares() noexcept
		{
			size_t n{ 0 };
			for (const auto sq : squareType::range)
				n = std::max(n, countInverseAttackSquares(sq));
			return n;
		}
	private:
		constexpr static typename squaresType::bitsType magicFactor(const size_t index) noexcept
		{
			return instanceType::magicFactor(index);
		}
		constexpr static typename squaresType::bitsType inverseMagicFactor(const size_t index) noexcept
		{
			return instanceType::inverseMagicFactor(index);
		}
		static inline std::array<slidermagic<descriptorDynamics, propagator>, countSquares> m_Magic{ arrayhelper::generate<countSquares, slidermagic<descriptorDynamics, propagator>>([](const size_t index)->slidermagic<descriptorDynamics, propagator> { return slidermagic<descriptorDynamics, propagator>(slidermagicinfo<descriptorDynamics>(static_cast<squareType>(index)),propagator::magicFactor(index),propagator::relevant(squaresType(static_cast<squareType>(static_cast<typename squareType::baseType>(index)))).count()); }) };
		static inline std::array<inverseSlidermagic<descriptorDynamics, propagator>, countSquares> m_InverseMagic{ arrayhelper::generate<countSquares, inverseSlidermagic<descriptorDynamics, propagator>>([](const size_t index)->inverseSlidermagic<descriptorDynamics, propagator> { return inverseSlidermagic<descriptorDynamics, propagator>(inverseSlidermagicinfo<descriptorDynamics>(static_cast<squareType>(index)),propagator::inverseMagicFactor(index),propagator::inverseRelevant(squaresType(static_cast<squareType>(static_cast<typename squareType::baseType>(index)))).count()); }) };
	public:
		constexpr static slidermagic<descriptorDynamics, propagator>& magic(const squareType sq) noexcept
		{
			return m_Magic[sq];
		}
		constexpr static inverseSlidermagic<descriptorDynamics, propagator>& inverseMagic(const squareType sq) noexcept
		{
			return m_InverseMagic[sq];
		}
		constexpr propagator() noexcept = default;
		constexpr propagator(const propagator&) noexcept = default;
		constexpr propagator(propagator&&) noexcept = default;
		constexpr propagator& operator=(const propagator&) noexcept = default;
		constexpr propagator& operator=(propagator&&) noexcept = default;
		~propagator() noexcept = default;
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
		constexpr static squaresType inverseRelevant(const squareType seed) noexcept
		{
			return propagator::inverseRelevant(squaresType(seed));
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
		template<typename RAY>
		constexpr static void propagateInverseRayStep(const squaresType& seeds, squaresType& destinations) noexcept
		{
			squaresType pattern{ seeds };
			if constexpr (RAY::fileIncrement > 0)
			{
				for (int i = 0; i < RAY::fileIncrement; i++)
				{
					pattern = pattern.left();
				}
			}
			else if constexpr (RAY::fileIncrement < 0)
			{
				for (int i = RAY::fileIncrement; i < 0; i++)
				{
					pattern = pattern.right();
				}
			}
			if constexpr (RAY::rankIncrement > 0)
			{
				for (int i = 0; i < RAY::rankIncrement; i++)
				{
					pattern = pattern.down();
				}
			}
			else if constexpr (RAY::rankIncrement < 0)
			{
				for (int i = RAY::rankIncrement; i < 0; i++)
				{
					pattern = pattern.up();
				}
			}
			destinations |= pattern;
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeTargets(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType ray{ none };
			propagator::propagateRayStep<RAY>(seeds, ray);
			targets |= ray & allowed;
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeTargets<RAYS2...>(seeds, allowed, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeInverseTargets(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType ray{ none };
			propagator::propagateInverseRayStep<RAY>(seeds, ray);
			targets |= ray & allowed;
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeInverseTargets<RAYS2...>(seeds, allowed, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeAttacks(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::propagateRayStep<RAY>(seeds, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeAttacks<RAYS2...>(seeds, allowed, targets);
		}
		template<typename RAY, typename... RAYS2>
		constexpr static void computeInverseAttacks(const squaresType& seeds, const squaresType& allowed, squaresType& targets) noexcept
		{
			propagator::propagateInverseRayStep<RAY>(seeds, targets);
			if constexpr (sizeof...(RAYS2) > 0)
				propagator::computeInverseAttacks<RAYS2...>(seeds, allowed, targets);
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
			constexpr const squaresType none{ squaresType::none() };
			squaresType targets{ none };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeTargets<RAYS...>(seeds, allowed, targets);
			return targets;
		}
		constexpr static squaresType inverseTargets(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType targets{ none };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeInverseTargets<RAYS...>(seeds, allowed, targets);
			return targets;
		}
		constexpr static squaresType attacks(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType attacks{ none };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeAttacks<RAYS...>(seeds, allowed, attacks);
			return attacks;
		}
		constexpr static squaresType inverseAttacks(const squaresType& seeds, const squaresType& allowed) noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType attacks{ none };
			if constexpr (sizeof...(RAYS) > 0)
				propagator::computeInverseAttacks<RAYS...>(seeds, allowed, attacks);
			return attacks;
		}
	private:
		constexpr static const inline std::array<squaresType, countSquares> m_PropagationTable{ arrayhelper::generate<countSquares,squaresType>([](const size_t index)->squaresType { return attacks(static_cast<squaresType>(static_cast<squareType>(static_cast<typename std::make_unsigned<size_t>::type>(index))),squaresType::all()); }) };
		constexpr static const inline std::array<squaresType, countSquares> m_InversePropagationTable{ arrayhelper::generate<countSquares,squaresType>([](const size_t index)->squaresType { return inverseAttacks(static_cast<squaresType>(static_cast<squareType>(static_cast<typename std::make_unsigned<size_t>::type>(index))),squaresType::all()); }) };
	public:
		constexpr static squaresType targets(const squareType seed, const squaresType& allowed) noexcept
		{
			return m_PropagationTable[seed] & allowed;
		}
		constexpr static squaresType inverseTargets(const squareType seed, const squaresType& allowed) noexcept
		{
			return m_InversePropagationTable[seed] & allowed;
		}
		constexpr static squaresType attacks(const squareType seed, const squaresType& allowed) noexcept
		{
			return m_PropagationTable[seed];
		}
		constexpr static squaresType inverseAttacks(const squareType seed, const squaresType& allowed) noexcept
		{
			return m_InversePropagationTable[seed];
		}
	};
}