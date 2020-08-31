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
		std::uint8_t m_CountBits;
	protected:
		constexpr void setPremask(const bitsType premask) noexcept
		{
			assert(premask != bitsType::empty());
			m_Premask = premask;
			m_CountBits = m_Premask.populationCount();
		}
		constexpr magic(const bitsType& premask, const std::uint8_t countBits) noexcept :
			m_Premask{ premask },
			m_CountBits{ countBits }
		{
			assert(m_Premask != bitsType::empty());
		}
	public:
		magic(const bitsType& premask) noexcept :
			m_Premask{ premask },
			m_CountBits{ static_cast<std::uint8_t>(premask.populationCount()) }
		{
			assert(m_Premask != bitsType::empty());
		}
		constexpr magic(const magic&) = default;
		constexpr magic(magic&&) = default;
		constexpr magic(const bitsType& premask, const bitsType&, const std::uint8_t bits) noexcept :
			magic<BITS, true>(premask, bits)
		{
		}
		constexpr magic& operator=(const magic&) noexcept = default;
		constexpr magic& operator=(magic&&) noexcept = default;
		~magic() noexcept = default;
		constexpr bitsType premask() const noexcept
		{
			return m_Premask;
		}
		constexpr std::uint8_t countBits() const noexcept
		{
			return m_CountBits;
		}
		constexpr size_t countValues() const noexcept
		{
			return size_t(1) << m_CountBits;
		}
		size_t cast(const bitsType bitboard) const noexcept
		{
			return static_cast<size_t>(bitboard.pext(m_Premask).bits());
		}
	public:
		void find(bitsType& premask, bitsType& factor, int& countBits) const noexcept
		{
			premask = m_Premask;
			bitsType::findMagic(m_Premask, factor, countBits);
		}
	protected:
		void find(const bitsType premask, bitsType& factor) noexcept
		{
			assert(premask != bitsType::empty());
			m_Premask = premask;
			int countBits;
			bitsType::findMagic(m_Premask, factor, countBits);
			m_CountBits = countBits;
		}
	};

	template<typename BITS>
	class magic<BITS, false>
		: public magic<BITS, true>
	{
	public:
		using bitsType = BITS;
	protected:
		bitsType m_Factor;
	public:
		magic(const bitsType& premask) noexcept :
			magic<BITS, true>(premask),
			m_Factor{ 0 }
		{
			this->find(premask, m_Factor);
		}
		constexpr magic(const magic&) = default;
		constexpr magic(magic&&) = default;
		constexpr magic(const bitsType& premask, const bitsType& factor, const std::uint8_t bits) noexcept :
			magic<BITS, true>(premask, bits),
			m_Factor{ factor }
		{
		}
		constexpr magic& operator=(const magic&) noexcept = default;
		constexpr magic& operator=(magic&&) noexcept = default;
		~magic() noexcept = default;
		size_t cast(const bitsType& bitboard) const noexcept
		{
			return bitsType::castMagic(bitboard, this->premask(), m_Factor, this->countBits());
		}
		constexpr bitsType factor() const noexcept
		{
			return m_Factor;
		}
	};
}