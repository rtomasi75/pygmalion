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
		constexpr slidermagicinfo(const squareType& square) noexcept :
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
			constexpr static size_t requiredBits() noexcept
			{
				return slidermagic_helper::requiredUnsignedBits(PROPAGATOR::maxPossibilities());
			}
			template<typename PROPAGATOR>
			constexpr static size_t requiredValueBits() noexcept
			{
				return PROPAGATOR::maxAttackSquares();
			}
		};
	}

	template<typename DESCRIPTOR_DYNAMICS, typename PROPAGATOR>
	class slidermagic :
		public DESCRIPTOR_DYNAMICS,
#if defined(PYGMALION_SLIDERMAGIC_COMPACT)&&defined(PYGMALION_CPU_BMI2)
#if defined(PYGMALION_SLIDERMAGIC_INDIRECT)
		public pygmalion::magictable<PROPAGATOR::maxAttackSquares(), DESCRIPTOR_DYNAMICS::squaresType::countSquares, uint_t<detail::slidermagic_helper::requiredBits<PROPAGATOR>(), true>, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>
#else
		public pygmalion::magictable<PROPAGATOR::maxAttackSquares(), DESCRIPTOR_DYNAMICS::squaresType::countSquares, uint_t<PROPAGATOR::maxAttackSquares(), true>, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>
#endif
#else
#if defined(PYGMALION_SLIDERMAGIC_INDIRECT)
		public pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, uint_t<detail::slidermagic_helper::requiredBits<PROPAGATOR>(), true>, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>
#else
		public pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, typename DESCRIPTOR_DYNAMICS::squaresType, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>
#endif
#endif
	{
	public:
		using propagatorType = PROPAGATOR;
		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#if defined(PYGMALION_SLIDERMAGIC_INDIRECT)
		using entryType = uint_t<detail::slidermagic_helper::requiredUnsignedBits(propagatorType::maxPossibilities()), true>;
#endif
#include "include_dynamics.h"
#if defined(PYGMALION_SLIDERMAGIC_COMPACT)&&defined(PYGMALION_CPU_BMI2)
		using valueType = uint_t<propagatorType::maxAttackSquares(), true>;
#else
		using valueType = squaresType;
#endif
#if defined(PYGMALION_SLIDERMAGIC_COMPACT)&&defined(PYGMALION_CPU_BMI2)
#if defined(PYGMALION_SLIDERMAGIC_INDIRECT)
		using parentType = pygmalion::magictable<PROPAGATOR::maxAttackSquares(), DESCRIPTOR_DYNAMICS::squaresType::countSquares, uint_t<detail::slidermagic_helper::requiredBits<PROPAGATOR>(), true>, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>;
#else
		using parentType = pygmalion::magictable<PROPAGATOR::maxAttackSquares(), DESCRIPTOR_DYNAMICS::squaresType::countSquares, valueType, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>;
#endif
#else
#if defined(PYGMALION_SLIDERMAGIC_INDIRECT)
		using parentType = pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, uint_t<detail::slidermagic_helper::requiredBits<PROPAGATOR>(), true>, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>;
#else
		using parentType = pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, valueType, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>;
#endif
#endif
		using bitsType = typename parentType::bitsType;
	private:
		valueType* m_Table;
#if defined(PYGMALION_SLIDERMAGIC_COMPACT)&&defined(PYGMALION_CPU_BMI2)
		bitsType m_Mask;
#endif
		constexpr squaresType decodeSquares(const valueType& value) const noexcept
		{
#if defined(PYGMALION_SLIDERMAGIC_COMPACT)&&defined(PYGMALION_CPU_BMI2)
			const bitsType extracted{ static_cast<bitsType>(value) };
			const bitsType squarebits{ extracted.deposePattern(m_Mask) };
			const squaresType squares{ squaresType(squarebits) };
			return squares;
#else
			return value;
#endif
		}
		constexpr valueType encodeSquares(const squaresType& squares) const noexcept
		{
#if defined(PYGMALION_SLIDERMAGIC_COMPACT)&&defined(PYGMALION_CPU_BMI2)
			const bitsType squarebits{ static_cast<bitsType>(squares) };
			const bitsType extracted{ squarebits.extractPattern(m_Mask) };
			const valueType value{ static_cast<valueType>(extracted) };
			PYGMALION_ASSERT(squarebits.populationCount() == value.populationCount());
			return value;
#else
			return squares;
#endif
		}
	public:
#if defined(PYGMALION_SLIDERMAGIC_INDIRECT)
		void* preInitialize_Implementation(const slidermagicinfo<descriptorDynamics>& info) noexcept
		{
#if defined(PYGMALION_SLIDERMAGIC_COMPACT)&&defined(PYGMALION_CPU_BMI2)
			constexpr const squaresType all{ squaresType::all() };
			m_Mask = static_cast<bitsType>(propagatorType::attacks(squaresType(info.square()), all));
#endif
			const size_t count{ propagatorType::possibilities(info.square()) };
			bool* pUsage = new bool[count];
			m_Table = new valueType[count];
			for (size_t i = 0; i < count; i++)
				pUsage[i] = false;
			return static_cast<void*>(pUsage);
		}
		void postInitialize_Implementation(const slidermagicinfo<descriptorDynamics>& info, void* pData) noexcept
		{
			bool* pUsage = static_cast<bool*>(pData);
			delete[] pUsage;
		}
		void initializeValue_Implementation(entryType& value, const slidermagicinfo<descriptorDynamics>& info, const bitsType& blockers, const bitsType& premask, void* pData) const noexcept
		{
			PYGMALION_ASSERT(info.square().isValid());
			bool* pUsage = static_cast<bool*>(pData);
			const squaresType attacks{ propagatorType::attacks(squaresType(info.square()), squaresType(~blockers)) };
			const squareType sq{ info.square() };
			const size_t count{ propagatorType::possibilities(sq) };
			for (size_t i = 0; i < count; i++)
			{
				if (pUsage[i])
				{
					if (m_Table[i] == encodeSquares(attacks))
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
					m_Table[i] = encodeSquares(attacks);
					value = static_cast<entryType>(static_cast<typename std::make_unsigned<size_t>::type>(i));
					pUsage[i] = true;
					return;
				}
			}
			PYGMALION_ASSERT(false);
		}
#else
		void* preInitialize_Implementation(const slidermagicinfo<descriptorDynamics>& info) noexcept
		{
#if defined(PYGMALION_SLIDERMAGIC_COMPACT)&&defined(PYGMALION_CPU_BMI2)
			constexpr const squaresType all{ squaresType::all() };
			m_Mask = static_cast<bitsType>(propagatorType::attacks(squaresType(info.square()), all));
#endif
			return nullptr;
		}
		void postInitialize_Implementation(const slidermagicinfo<descriptorDynamics>& info, void* pData) noexcept
		{
		}
		void initializeValue_Implementation(valueType& value, const slidermagicinfo<descriptorDynamics>& info, const bitsType& blockers, const bitsType& premask, void* pData) const noexcept
		{
			PYGMALION_ASSERT(info.square().isValid());
			value = encodeSquares(propagatorType::attacks(squaresType(info.square()), squaresType(~blockers)));
		}
#endif
		static bitsType calculatePremask(const slidermagicinfo<descriptorDynamics>& info) noexcept
		{
			PYGMALION_ASSERT(info.square().isValid());
			return static_cast<bitsType>(propagatorType::relevant(info.square()));
		}
		slidermagic(const slidermagicinfo<descriptorDynamics>& info) noexcept :
			parentType(info),
			m_Table{ nullptr }
		{
#if defined(PYGMALION_SLIDERMAGIC_COMPACT)&&defined(PYGMALION_CPU_BMI2)
			constexpr const squaresType all{ squaresType::all() };
			m_Mask = static_cast<bitsType>(propagatorType::attacks(squaresType(info.square()), all));
#endif
		}
		slidermagic(const slidermagicinfo<descriptorDynamics>& info, const bitsType& factor, const size_t shift) noexcept :
			parentType(info, factor, shift),
			m_Table{ nullptr }
		{
#if defined(PYGMALION_SLIDERMAGIC_COMPACT)&&defined(PYGMALION_CPU_BMI2)
			constexpr const squaresType all{ squaresType::all() };
			m_Mask = static_cast<bitsType>(propagatorType::attacks(squaresType(info.square()), all));
#endif
		}
		slidermagic() noexcept = default;
		slidermagic(const slidermagic&) noexcept = default;
		constexpr slidermagic(slidermagic&&) noexcept = default;
		~slidermagic() noexcept
		{
#if defined(PYGMALION_SLIDERMAGIC_INDIRECT)
			delete[] m_Table;
#endif
		}
		const squaresType operator[](const squaresType& blockers) const
		{
#if defined(PYGMALION_SLIDERMAGIC_INDIRECT)
			const entryType idx{ slidermagic::value(static_cast<bitsType>(blockers)) };
			return slidermagic::decodeSquares(m_Table[static_cast<typename std::make_unsigned<size_t>::type>(idx)]);
#else
			return slidermagic::decodeSquares(slidermagic::value(static_cast<bitsType>(blockers)));
#endif
		}
		slidermagic& operator=(const slidermagic&) noexcept = default;
		slidermagic& operator=(slidermagic&&) noexcept = default;
	};

}