namespace pygmalion
{
	template<size_t COUNT_MAXPATTERNBITS, size_t COUNT_BITS, typename VALUE, typename INFO, typename INSTANCE>
	class magictable
	{
	public:
		constexpr static const size_t countBits{ COUNT_BITS };
		constexpr static const size_t countMaxPatternBits{ COUNT_MAXPATTERNBITS };
		using valueType = VALUE;
		using infoType = INFO;
		using bitsType = uint_t<COUNT_BITS, false>;
		using instanceType = INSTANCE;
		using magicType = intrinsics::magic<countMaxPatternBits, bitsType, cpu::supports(cpu::flags::BMI2)>;
	private:
		const infoType m_Info;
		magicType m_Magic;
		valueType* m_pValues;
		void initializeValue(valueType& value, const bitsType& bitboard, void* pData) const noexcept
		{
			static_cast<const instanceType*>(this)->initializeValue_Implementation(value, m_Info, bitboard, m_Magic.premask(), pData);
		}
	protected:
		constexpr const infoType& info() const noexcept
		{
			return m_Info;
		}
		constexpr magictable(const infoType& info, const bitsType& factor, const size_t shift) noexcept :
			m_Info{ info },
			m_Magic(instanceType::calculatePremask(info), factor, shift),
			m_pValues{ new valueType[m_Magic.countValues()] }
		{
			void* pData{ static_cast<instanceType*>(this)->preInitialize_Implementation(info) };
			const size_t N{ m_Magic.countValues() };
			for (size_t k = 0; k < N; k++)
			{
				const bitsType bb{ bitsType(static_cast<typename std::make_unsigned<size_t>::type>(k)).deposePattern(m_Magic.premask()) };
				const size_t idx{ m_Magic.cast(bb) };
				PYGMALION_ASSERT(idx < N);
				initializeValue(m_pValues[idx], bb, pData);
			}
			static_cast<instanceType*>(this)->postInitialize_Implementation(info, pData);
		}
		magictable(const infoType& info) noexcept :
			m_Info{ info },
			m_Magic(instanceType::calculatePremask(info)),
			m_pValues{ new valueType[m_Magic.countValues()] }
		{
			void* pData{ static_cast<instanceType*>(this)->preInitialize_Implementation(info) };
			const size_t N{ m_Magic.countValues() };
			for (size_t k = 0; k < N; k++)
			{
				const bitsType bb{ bitsType(static_cast<typename std::make_unsigned<size_t>::type>(k)).deposePattern(m_Magic.premask()) };
				const size_t idx{ m_Magic.cast(bb) };
				PYGMALION_ASSERT(idx < N);
				initializeValue(m_pValues[idx], bb, pData);
			}
			static_cast<instanceType*>(this)->postInitialize_Implementation(info, pData);
		}
		magictable() noexcept :
			m_pValues{ nullptr }
		{

		}
		~magictable()
		{
			if (m_pValues)
				delete[] m_pValues;
		}
		magictable(const magictable& other) noexcept :
			m_Magic{ other.m_Magic },
			m_pValues{ new valueType[size_t(1) << m_Magic.bits()] },
			m_Info{ other.m_Info }
		{
			if (other.m_pValues != nullptr)
			{
				size_t N{ size_t(1) << other.m_Magic.bits() };
				for (size_t i = 0; i < N; i++)
					m_pValues[i] = other.m_pValues[i];
			}
		}
		constexpr magictable(magictable&& other) noexcept :
			m_Magic{ std::move(other.m_Magic) },
			m_pValues{ other.m_pValues },
			m_Info{ std::move(other.m_Info) }
		{
			other.m_pValues = nullptr;
		}
		constexpr const valueType& value(const bitsType& bitboard) const noexcept
		{
			PYGMALION_ASSERT(m_pValues != nullptr);
			const size_t i{ m_Magic.cast(bitboard) };
			return m_pValues[i];
		}
	public:
		const auto& magic() const noexcept
		{
			return m_Magic;
		}
		magictable& operator=(const magictable& other) noexcept
		{
			if (this == &other)
				return *this;
			m_Info = other.m_Info;
			m_Magic = other.m_Magic;
			if (other.m_pValues != nullptr)
			{
				size_t N{ size_t(1) << other.m_Magic.bits() };
				m_pValues = new valueType[N];
				for (size_t i = 0; i < N; i++)
					m_pValues[i] = other.m_pValues[i];
			}
			else
				m_pValues = nullptr;
			return *this;
		}
		constexpr magictable& operator=(magictable&& other) noexcept
		{
			m_Info = std::move(other.m_Info);
			m_Magic = std::move(other.m_Magic);
			m_pValues = other.m_pValues;
			other.m_pValues = nullptr;
			return *this;
		}
	};
}