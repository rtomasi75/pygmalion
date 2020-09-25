namespace pygmalion::dynamics
{
	template<typename DESCRIPTOR_DYNAMICS>
	class slidermagicinfo :
		public DESCRIPTOR_DYNAMICS
	{
	public:

		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include "include_dynamics.h"

	private:
		squareType m_Square;
	public:
		constexpr slidermagicinfo() noexcept :
			m_Square{ squareType::invalid }
		{
		}
		constexpr slidermagicinfo(const squareType square) noexcept :
			m_Square{ square }
		{

		}
		constexpr slidermagicinfo(const slidermagicinfo&) noexcept = default;
		constexpr slidermagicinfo(slidermagicinfo&&) noexcept = default;
		~slidermagicinfo() noexcept = default;
		constexpr slidermagicinfo& operator=(const slidermagicinfo&) noexcept = default;
		constexpr slidermagicinfo& operator=(slidermagicinfo&&) noexcept = default;
		constexpr auto square() const noexcept
		{
			return m_Square;
		}
	};

	namespace detail
	{
		class slidermagic_helper
		{
		public:
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
			template<typename PROPAGATOR>
			constexpr static size_t requiredBits()
			{
				return slidermagic_helper::requiredUnsignedBits(PROPAGATOR::maxPossibilities());
			}
		};
	}

	template<typename DESCRIPTOR_DYNAMICS, typename PROPAGATOR>
	class slidermagic :
		public DESCRIPTOR_DYNAMICS,
#if defined(PYGMALION_COMPACTSLIDERS)
		public pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, uint_t<detail::slidermagic_helper::requiredBits<PROPAGATOR>(), true>, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>
#else
		public pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, typename DESCRIPTOR_DYNAMICS::squaresType, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>
#endif
	{
	public:
		using propagatorType = PROPAGATOR;
		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
		using entryType = uint_t<detail::slidermagic_helper::requiredUnsignedBits(propagatorType::maxPossibilities()), true>;
#include "include_dynamics.h"
	private:
#if defined(PYGMALION_COMPACTSLIDERS)
		using parentType = pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, uint_t<detail::slidermagic_helper::requiredBits<PROPAGATOR>(), true>, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>;
#else
		using parentType = pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, typename DESCRIPTOR_DYNAMICS::squaresType, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>;
#endif
		using bitsType = typename parentType::bitsType;
		squaresType* m_Table;
	public:
#if defined(PYGMALION_COMPACTSLIDERS)
		void* preInitialize_Implementation(const slidermagicinfo<descriptorDynamics>& info) noexcept
		{
			const size_t count{ propagatorType::possibilities(info.square()) };
			bool* pUsage = new bool[count];
			m_Table = new squaresType[count];
			for (size_t i = 0; i < count; i++)
				pUsage[i] = false;
			return static_cast<void*>(pUsage);
		}
		void postInitialize_Implementation(const slidermagicinfo<descriptorDynamics>& info, void* pData) noexcept
		{
			bool* pUsage = static_cast<bool*>(pData);
#if !defined(NDEBUG)
			const size_t count{ propagatorType::possibilities(info.square()) };
			for (size_t i = 0; i < count; i++)
				assert(pUsage[i]);
#endif
			delete[] pUsage;
		}
		void initializeValue_Implementation(entryType& value, const slidermagicinfo<descriptorDynamics>& info, const bitsType& blockers, const bitsType& premask, void* pData) const noexcept
		{
			assert(info.square().isValid());
			bool* pUsage = static_cast<bool*>(pData);
			const squaresType attacks{ propagatorType::attacks(squaresType(info.square()), squaresType(~blockers)) };
			const squareType sq{ info.square() };
			const size_t count{ propagatorType::possibilities(sq) };
			for (size_t i = 0; i < count; i++)
			{
				if (pUsage[i])
				{
					if (m_Table[i] == attacks)
					{
						value = static_cast<entryType>(static_cast<typename std::make_unsigned<size_t>::type>(i));
						return;
					}
				}
				else
					break;
			}
			for (size_t i = 0; i < count; i++)
			{
				if (!pUsage[i])
				{
					m_Table[i] = attacks;
					value = static_cast<entryType>(static_cast<typename std::make_unsigned<size_t>::type>(i));
					pUsage[i] = true;
					return;
				}
			}
			assert(false);
		}
#else
		void* preInitialize_Implementation(const slidermagicinfo<descriptorDynamics>& info) noexcept
		{
			return nullptr;
		}
		void postInitialize_Implementation(const slidermagicinfo<descriptorDynamics>& info, void* pData) noexcept
		{
		}
		void initializeValue_Implementation(squaresType& value, const slidermagicinfo<descriptorDynamics>& info, const bitsType& blockers, const bitsType& premask, void* pData) const noexcept
		{
			assert(info.square().isValid());
			value = propagatorType::attacks(squaresType(info.square()), squaresType(~blockers));
		}
#endif
		static bitsType calculatePremask(const slidermagicinfo<descriptorDynamics>& info) noexcept
		{
			assert(info.square().isValid());
			return static_cast<bitsType>(propagatorType::relevant(info.square()));
		}
		slidermagic(const slidermagicinfo<descriptorDynamics>& info) noexcept :
			parentType(info)
		{
		}
		slidermagic(const slidermagicinfo<descriptorDynamics>& info, const bitsType& factor, const size_t shift) noexcept :
			parentType(info, factor, shift)
		{
		}
		slidermagic() noexcept = default;
		slidermagic(const slidermagic&) noexcept = default;
		constexpr slidermagic(slidermagic&&) noexcept = default;
		~slidermagic() noexcept
		{
#if defined(PYGMALION_COMPACTSLIDERS)
			delete[] m_Table;
#endif
		}
		const squaresType& operator[](const squaresType& blockers) const
		{
#if defined(PYGMALION_COMPACTSLIDERS)
			const entryType idx{ slidermagic::value(static_cast<bitsType>(blockers)) };
			return m_Table[static_cast<typename std::make_unsigned<size_t>::type>(idx)];
#else
			return slidermagic::value(static_cast<bitsType>(blockers));
#endif
		}
		slidermagic& operator=(const slidermagic&) noexcept = default;
		slidermagic& operator=(slidermagic&&) noexcept = default;
	};

}