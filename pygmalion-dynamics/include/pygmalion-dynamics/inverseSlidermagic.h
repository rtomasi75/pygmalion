namespace pygmalion::dynamics
{
	template<typename DESCRIPTOR_DYNAMICS>
	class inverseSlidermagicinfo :
		public DESCRIPTOR_DYNAMICS
	{
	public:

		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include "include_dynamics.h"

	private:
		squareType m_Square;
	public:
		constexpr inverseSlidermagicinfo() noexcept :
			m_Square{ squareType::invalid }
		{
		}
		constexpr inverseSlidermagicinfo(const squareType& square) noexcept :
			m_Square{ square }
		{

		}
		constexpr inverseSlidermagicinfo(const inverseSlidermagicinfo&) noexcept = default;
		constexpr inverseSlidermagicinfo(inverseSlidermagicinfo&&) noexcept = default;
		~inverseSlidermagicinfo() noexcept = default;
		constexpr inverseSlidermagicinfo& operator=(const inverseSlidermagicinfo&) noexcept = default;
		constexpr inverseSlidermagicinfo& operator=(inverseSlidermagicinfo&&) noexcept = default;
		constexpr auto square() const noexcept
		{
			return m_Square;
		}
	};

	namespace detail
	{
		class inverseSlidermagic_helper
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
				return inverseSlidermagic_helper::requiredUnsignedBits(PROPAGATOR::maxPossibilities());
			}
			template<typename PROPAGATOR>
			constexpr static size_t requiredValueBits() noexcept
			{
				return PROPAGATOR::maxInverseAttackSquares();
			}
		};
	}

	template<typename DESCRIPTOR_DYNAMICS, typename PROPAGATOR>
	class inverseSlidermagic :
		public DESCRIPTOR_DYNAMICS,
#if defined(PYGMALION_inverseSlidermagic_COMPACT)&&defined(PYGMALION_CPU_BMI2)
#if defined(PYGMALION_inverseSlidermagic_INDIRECT)
		public pygmalion::magictable<PROPAGATOR::maxInverseAttackSquares(), DESCRIPTOR_DYNAMICS::squaresType::countSquares, uint_t<detail::inverseSlidermagic_helper::requiredBits<PROPAGATOR>(), true>, inverseSlidermagicinfo<DESCRIPTOR_DYNAMICS>, inverseSlidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>
#else
		public pygmalion::magictable<PROPAGATOR::maxInverseAttackSquares(), DESCRIPTOR_DYNAMICS::squaresType::countSquares, uint_t<PROPAGATOR::maxInverseAttackSquares(), true>, inverseSlidermagicinfo<DESCRIPTOR_DYNAMICS>, inverseSlidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>
#endif
#else
#if defined(PYGMALION_inverseSlidermagic_INDIRECT)
		public pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, uint_t<detail::inverseSlidermagic_helper::requiredBits<PROPAGATOR>(), true>, inverseSlidermagicinfo<DESCRIPTOR_DYNAMICS>, inverseSlidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>
#else
		public pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, typename DESCRIPTOR_DYNAMICS::squaresType, inverseSlidermagicinfo<DESCRIPTOR_DYNAMICS>, inverseSlidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>
#endif
#endif
	{
	public:
		using propagatorType = PROPAGATOR;
		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#if defined(PYGMALION_inverseSlidermagic_INDIRECT)
		using entryType = uint_t<detail::inverseSlidermagic_helper::requiredUnsignedBits(propagatorType::maxInversePossibilities()), true>;
#endif
#include "include_dynamics.h"
#if defined(PYGMALION_inverseSlidermagic_COMPACT)&&defined(PYGMALION_CPU_BMI2)
		using valueType = uint_t<propagatorType::maxInverseAttackSquares(), true>;
#else
		using valueType = squaresType;
#endif
#if defined(PYGMALION_inverseSlidermagic_COMPACT)&&defined(PYGMALION_CPU_BMI2)
#if defined(PYGMALION_inverseSlidermagic_INDIRECT)
		using parentType = pygmalion::magictable<PROPAGATOR::maxInverseAttackSquares(), DESCRIPTOR_DYNAMICS::squaresType::countSquares, uint_t<detail::inverseSlidermagic_helper::requiredBits<PROPAGATOR>(), true>, inverseSlidermagicinfo<DESCRIPTOR_DYNAMICS>, inverseSlidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>;
#else
		using parentType = pygmalion::magictable<PROPAGATOR::maxInverseAttackSquares(), DESCRIPTOR_DYNAMICS::squaresType::countSquares, valueType, inverseSlidermagicinfo<DESCRIPTOR_DYNAMICS>, inverseSlidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>;
#endif
#else
#if defined(PYGMALION_inverseSlidermagic_INDIRECT)
		using parentType = pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, uint_t<detail::inverseSlidermagic_helper::requiredBits<PROPAGATOR>(), true>, inverseSlidermagicinfo<DESCRIPTOR_DYNAMICS>, inverseSlidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>;
#else
		using parentType = pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, valueType, inverseSlidermagicinfo<DESCRIPTOR_DYNAMICS>, inverseSlidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>;
#endif
#endif
		using bitsType = typename parentType::bitsType;
	private:
		valueType* m_Table;
#if defined(PYGMALION_inverseSlidermagic_COMPACT)&&defined(PYGMALION_CPU_BMI2)
		bitsType m_Mask;
#endif
		constexpr squaresType decodeSquares(const valueType& value) const noexcept
		{
#if defined(PYGMALION_inverseSlidermagic_COMPACT)&&defined(PYGMALION_CPU_BMI2)
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
#if defined(PYGMALION_inverseSlidermagic_COMPACT)&&defined(PYGMALION_CPU_BMI2)
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
#if defined(PYGMALION_inverseSlidermagic_INDIRECT)
		void* preInitialize_Implementation(const inverseSlidermagicinfo<descriptorDynamics>& info) noexcept
		{
#if defined(PYGMALION_inverseSlidermagic_COMPACT)&&defined(PYGMALION_CPU_BMI2)
			constexpr const squaresType all{ squaresType::all() };
			m_Mask = static_cast<bitsType>(propagatorType::inverseAttacks(squaresType(info.square()), all));
#endif
			const size_t count{ propagatorType::inversePossibilities(info.square()) };
			bool* pUsage = new bool[count];
			m_Table = new valueType[count];
			for (size_t i = 0; i < count; i++)
				pUsage[i] = false;
			return static_cast<void*>(pUsage);
		}
		void postInitialize_Implementation(const inverseSlidermagicinfo<descriptorDynamics>& info, void* pData) noexcept
		{
			bool* pUsage = static_cast<bool*>(pData);
			delete[] pUsage;
		}
		void initializeValue_Implementation(entryType& value, const inverseSlidermagicinfo<descriptorDynamics>& info, const bitsType& blockers, const bitsType& premask, void* pData) const noexcept
		{
			PYGMALION_ASSERT(info.square().isValid());
			bool* pUsage = static_cast<bool*>(pData);
			const squaresType attacks{ propagatorType::inverseAttacks(squaresType(info.square()), squaresType(~blockers)) };
			const squareType sq{ info.square() };
			const size_t count{ propagatorType::inversePossibilities(sq) };
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
		void* preInitialize_Implementation(const inverseSlidermagicinfo<descriptorDynamics>& info) noexcept
		{
#if defined(PYGMALION_inverseSlidermagic_COMPACT)&&defined(PYGMALION_CPU_BMI2)
			constexpr const squaresType all{ squaresType::all() };
			m_Mask = static_cast<bitsType>(propagatorType::inverseAttacks(squaresType(info.square()), all));
#endif
			return nullptr;
		}
		void postInitialize_Implementation(const inverseSlidermagicinfo<descriptorDynamics>& info, void* pData) noexcept
		{
		}
		void initializeValue_Implementation(valueType& value, const inverseSlidermagicinfo<descriptorDynamics>& info, const bitsType& blockers, const bitsType& premask, void* pData) const noexcept
		{
			PYGMALION_ASSERT(info.square().isValid());
			value = encodeSquares(propagatorType::inverseAttacks(squaresType(info.square()), squaresType(~blockers)));
		}
#endif
		static bitsType calculatePremask(const inverseSlidermagicinfo<descriptorDynamics>& info) noexcept
		{
			PYGMALION_ASSERT(info.square().isValid());
			return static_cast<bitsType>(propagatorType::inverseRelevant(info.square()));
		}
		inverseSlidermagic(const inverseSlidermagicinfo<descriptorDynamics>& info) noexcept :
			parentType(info)
		{
#if defined(PYGMALION_inverseSlidermagic_COMPACT)&&defined(PYGMALION_CPU_BMI2)
			constexpr const squaresType all{ squaresType::all() };
			m_Mask = static_cast<bitsType>(propagatorType::inverseAttacks(squaresType(info.square()), all));
#endif
		}
		inverseSlidermagic(const inverseSlidermagicinfo<descriptorDynamics>& info, const bitsType& factor, const size_t shift) noexcept :
			parentType(info, factor, shift)
		{
#if defined(PYGMALION_inverseSlidermagic_COMPACT)&&defined(PYGMALION_CPU_BMI2)
			constexpr const squaresType all{ squaresType::all() };
			m_Mask = static_cast<bitsType>(propagatorType::inverseAttacks(squaresType(info.square()), all));
#endif
		}
		inverseSlidermagic() noexcept = default;
		inverseSlidermagic(const inverseSlidermagic& other) noexcept
		{
#if defined(PYGMALION_inverseSlidermagic_INDIRECT)
			const size_t count{ propagatorType::inversePossibilities(sq) };
			m_Table = new valueType[count];
			for (size_t i = 0; i < count; i++)
				m_Table[i] = other.m_Table[i];
#endif
		}
		constexpr inverseSlidermagic(inverseSlidermagic&& other) noexcept
		{
#if defined(PYGMALION_inverseSlidermagic_INDIRECT)
			m_Table = other.m_Table;
			other.m_Table = nullptr;
#endif
		}
		~inverseSlidermagic() noexcept
		{
#if defined(PYGMALION_inverseSlidermagic_INDIRECT)
			if (m_Table != nullptr)
				delete[] m_Table;
#endif
		}
		const squaresType operator[](const squaresType& blockers) const
		{
#if defined(PYGMALION_inverseSlidermagic_INDIRECT)
			const entryType idx{ inverseSlidermagic::value(static_cast<bitsType>(blockers)) };
			return inverseSlidermagic::decodeSquares(m_Table[static_cast<typename std::make_unsigned<size_t>::type>(idx)]);
#else
			return inverseSlidermagic::decodeSquares(inverseSlidermagic::value(static_cast<bitsType>(blockers)));
#endif
		}
		inverseSlidermagic& operator=(const inverseSlidermagic&) noexcept
		{
#if defined(PYGMALION_inverseSlidermagic_INDIRECT)
			const size_t count{ propagatorType::inversePossibilities(sq) };
			m_Table = new valueType[count];
			for (size_t i = 0; i < count; i++)
				m_Table[i] = other.m_Table[i];
#endif
			return *this;
		}
		inverseSlidermagic& operator=(inverseSlidermagic&&) noexcept
		{
#if defined(PYGMALION_inverseSlidermagic_INDIRECT)
			m_Table = other.m_Table;
			other.m_Table = nullptr;
#endif
			return *this;
		}
	};

}