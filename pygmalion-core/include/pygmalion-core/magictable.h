namespace pygmalion
{
	template<typename VALUE, typename INFO, typename BITS, typename INSTANCE, bool USEBMI>
	class magictable
	{

	};

	template<typename VALUE, typename INFO, typename BITS, typename INSTANCE>
	class magictable<VALUE, INFO, BITS, INSTANCE, true>
	{
	public:
		using valueType = VALUE;
		using infoType = INFO;
		using bitsType = BITS;
		using instanceType = INSTANCE;
		using magicType = magic<bitsType, true>;
	private:
		infoType m_Info;
		magicType m_Magic;
		valueType* m_pValues;
		void initializeValue(valueType& value, const bitsType bitboard) const noexcept
		{
			instanceType::initializeValue_Implementation(value, m_Info, bitboard, m_Magic.premask());
		}
	protected:
		magictable() noexcept :
			m_pValues{ nullptr }
		{

		}
		magictable(const infoType& info) noexcept :
			m_Info{ info },
			m_Magic{ magicType(instanceType::calculatePremask(info), instanceType::calculatePremask(info).populationCount(), 1 << instanceType::calculatePremask(info).populationCount()) },
			m_pValues{ new valueType[1 << m_Magic.bits()] }
		{
			const std::uint16_t N{ static_cast<std::uint16_t>(1 << m_Magic.bits()) };
			for (std::uint16_t k = 0; k < N; k++)
			{
				const bitsType bb{ bitsType(k).pdep(m_Magic.premask()) };
				const std::uint16_t idx{ m_Magic.cast(bb) };
				assert(idx < N);
				initializeValue(m_pValues[idx], bb);
			}

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
				const std::uint16_t N{ static_cast<std::uint16_t>(1 << m_Magic.bits()) };
				for (std::uint16_t i = 0; i < N; i++)
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
		constexpr const auto& value(const bitsType bitboard) const noexcept
		{
			assert(m_pValues != nullptr);
			const std::uint16_t i{ m_Magic.cast(bitboard) };
			return m_pValues[i];
		}
	public:
		magictable& operator=(const magictable& other) noexcept
		{
			m_Info = other.m_Info;
			m_Magic = other.m_Magic;
			if (other.m_pValues != nullptr)
			{
				std::uint16_t N{ static_cast<std::uint16_t>(1 << other.m_Magic.bits()) };
				m_pValues = new valueType[N];
				for (std::uint16_t i = 0; i < N; i++)
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

	template<typename VALUE, typename INFO, typename BITS, typename INSTANCE>
	class magictable<VALUE, INFO, BITS, INSTANCE, false>
	{
	public:
		using valueType = VALUE;
		using infoType = INFO;
		using bitsType = BITS;
		using instanceType = INSTANCE;
		using magicType = magic<bitsType, false>;
	private:
		infoType m_Info;
		magicType m_Magic;
		valueType* m_pValues;
		void initializeValue(valueType& value, const bitsType bitboard) const noexcept
		{
			instanceType::initializeValue_Implementation(value, m_Info, bitboard, m_Magic.premask());
		}
	protected:
		magictable() noexcept :
			m_pValues{ nullptr }
		{

		}
		magictable(const infoType& info, const bitsType factor) noexcept :
			m_Info(info),
			m_Magic(instanceType::calculatePremask(info), factor, instanceType::calculatePremask(info).populationCount(), 1 << instanceType::calculatePremask(info).populationCount()),
			m_pValues(new valueType[1 << m_Magic.bits()])
		{
			const std::uint16_t N{ static_cast<std::uint16_t>(1 << m_Magic.bits()) };
			for (std::uint16_t k = 0; k < N; k++)
			{
				const bitsType bb{ bitsType(k).pdep(m_Magic.premask()) };
				const std::uint16_t idx{ m_Magic.cast(bb) };
				assert(idx < N);
				initializeValue(m_pValues[idx], bb);
			}

		}
		magictable(const infoType& info) noexcept :
			m_Info(info)
		{
			m_Magic.find(instanceType::calculatePremask(info));
			const std::uint16_t N{ static_cast<std::uint16_t>(1 << m_Magic.bits()) };
			m_pValues = new valueType[N];
			for (std::uint16_t k = 0; k < N; k++)
			{
				const bitsType bb{ bitsType(k).pdep(m_Magic.premask()) };
				const std::uint16_t idx{ m_Magic.cast(bb) };
				assert(idx < N);
				initializeValue(m_pValues[idx], bb);
			}
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
				const std::uint16_t N{ static_cast<std::uint16_t>(1 << m_Magic.bits()) };
				for (std::uint16_t i = 0; i < N; i++)
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
		constexpr const auto& value(const bitsType bitboard) const noexcept
		{
			assert(m_pValues != nullptr);
			const std::uint16_t i{ m_Magic.cast(bitboard) };
			return m_pValues[i];
		}
	public:
		bitsType factor() const noexcept
		{
			return m_Magic.factor();
		}
		magictable& operator=(const magictable& other) noexcept
		{
			m_Info = other.m_Info;
			m_Magic = other.m_Magic;
			if (other.m_pValues != nullptr)
			{
				std::uint16_t N{ static_cast<std::uint16_t>(1 << other.m_Magic.bits()) };
				m_pValues = new valueType[N];
				for (std::uint16_t i = 0; i < N; i++)
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