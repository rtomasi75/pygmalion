namespace pygmalion
{
	template<typename VALUE, typename INFO, typename BITS, typename INSTANCE>
	class magictable
	{
	public:
		using valueType = VALUE;
		using infoType = INFO;
		using bitsType = BITS;
		using instanceType = INSTANCE;
		using magicType = magic<bitsType, cpu::BMI2>;
	private:
		infoType m_Info;
		magicType m_Magic;
		valueType* m_pValues;
		void initializeValue(valueType& value, const bitsType bitboard) const noexcept
		{
			instanceType::initializeValue_Implementation(value, m_Info, bitboard, m_Magic.premask());
		}
	protected:
		constexpr magictable(const infoType& info, const bitsType premask, const bitsType factor, const std::uint8_t countBits) noexcept :
			m_Info{ info },
			m_Magic(premask, factor, countBits),
			m_pValues{ new valueType[m_Magic.countValues()] }
		{
			const size_t N{ m_Magic.countValues() };
			for (size_t k = 0; k < N; k++)
			{
				const bitsType bb{ bitsType(k).pdep(m_Magic.premask()) };
				const size_t idx{ m_Magic.cast(bb) };
				assert(idx < N);
				initializeValue(m_pValues[idx], bb);
			}
		}
		magictable(const infoType& info) noexcept :
			m_Info{ info },
			m_Magic(instanceType::calculatePremask(info)),
			m_pValues{ nullptr }
		{
			const size_t N{ m_Magic.countValues() };
			m_pValues = new valueType[N];
			for (size_t k = 0; k < N; k++)
			{
				const bitsType bb{ bitsType(k).pdep(m_Magic.premask()) };
				const size_t idx{ m_Magic.cast(bb) };
				assert(idx < N);
				initializeValue(m_pValues[idx], bb);
			}
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
			m_pValues{ new valueType[1 << m_Magic.bits()] },
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
		constexpr const valueType& value(const bitsType bitboard) const noexcept
		{
			assert(m_pValues != nullptr);
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