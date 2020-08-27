namespace pygmalion
{
	template<typename BITS, bool USEBMI>
	class magic
	{

	};


	template<typename BITS>
	class magic<BITS, true>
	{
	public:
		using bitsType = BITS;
	private:
		bitsType m_Premask;
		std::uint16_t m_Count;
		std::uint8_t m_Bits;
	public:
		constexpr magic() noexcept = default;
		constexpr magic(const magic&) = default;
		constexpr magic(magic&&) = default;
		constexpr magic(const bitsType& premask, const std::uint8_t bits, const std::uint16_t count) noexcept :
			m_Premask{ premask },
			m_Bits{ bits },
			m_Count{ count }
		{
			assert(m_Premask != bitsType::empty());
		}
		constexpr magic& operator=(const magic&) noexcept = default;
		constexpr magic& operator=(magic&&) noexcept = default;
		~magic() noexcept = default;
		constexpr auto premask() const noexcept
		{
			return m_Premask;
		}
		constexpr auto bits() const noexcept
		{
			return m_Bits;
		}
		constexpr auto count() const noexcept
		{
			return m_Count;
		}
		std::uint16_t cast(const bitsType& bitboard) const noexcept
		{
			assert(m_Premask != bitsType::empty());
			return static_cast<std::uint16_t>(bitboard.pext(m_Premask).bits());
		}
		std::uint16_t find(const bitsType& premask) noexcept
		{
			assert(premask != bitsType::empty());
			m_Premask = premask;
			m_Bits = premask.populationCount();
			m_Count = std::uint16_t(1) << m_Bits;
			return m_Count;
		}
	};

	template<typename BITS>
	class magic<BITS, false>
	{
	public:
		using bitsType = BITS;
	private:
		bitsType m_Premask;
		bitsType m_Factor;
		std::uint16_t m_Count;
		std::uint8_t m_Bits;
	public:
		constexpr magic() noexcept = default;
		constexpr magic(const magic&) = default;
		constexpr magic(magic&&) = default;
		constexpr magic(const bitsType& premask, const bitsType& factor, const std::uint8_t bits, const std::uint16_t count) noexcept :
			m_Premask{ premask },
			m_Factor{ factor },
			m_Bits{ bits },
			m_Count{ count }
		{
			assert(premask != bitsType::empty());
		}
		constexpr magic& operator=(const magic&) noexcept = default;
		constexpr magic& operator=(magic&&) noexcept = default;
		~magic() noexcept = default;
		constexpr auto premask() const noexcept
		{
			return m_Premask;
		}
		constexpr auto factor() const noexcept
		{
			return m_Factor;
		}
		constexpr auto bits() const noexcept
		{
			return m_Bits;
		}
		constexpr auto count() const noexcept
		{
			return m_Count;
		}
		std::uint16_t cast(const bitsType& bitboard) const noexcept
		{
			assert(m_Premask != bitsType::empty());
			return static_cast<std::uint16_t>((((bitboard & m_Premask) * m_Factor) >> (bitsType::bitCount - m_Bits)).bits());
		}
		std::uint16_t find(const bitsType& premask) noexcept
		{
			assert(premask != bitsType::empty());
			m_Premask = premask;
			m_Bits = premask.populationCount();
			const std::uint16_t N{ static_cast<std::uint16_t>(1 << m_Bits) };
			std::uint16_t* pIndices = new std::uint16_t[N];
			bool* pUsed = new bool[N];
			while (true)
			{
				bool bFound{ true };
				m_Factor = bitsType::random_sparse();
				for (std::uint16_t i = 0; i < N; i++)
				{
					pIndices[i] = 0;
					pUsed[i] = false;
				}
				for (std::uint16_t k = 0; k < N; k++)
				{
					const bitsType pattern{ bitsType(k).pdep(premask) };
					const std::uint16_t idx{ cast(pattern) };
					assert(idx < N);
					if (pUsed[idx])
					{
						bFound = false;
						break;
					}
					pUsed[idx] = true;
					pIndices[idx] = k;
				}
				if (bFound)
					break;
			}
			delete[] pIndices;
			delete[] pUsed;
			m_Count = std::uint16_t(1) << m_Bits;
			return N;
		}
	};
}