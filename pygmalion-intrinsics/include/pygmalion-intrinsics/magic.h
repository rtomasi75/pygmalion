namespace pygmalion::intrinsics
{
	template<size_t COUNT_VALUEBITS, size_t COUNT_MAXPATTERNBITS, bool USEBMI>
	class magic
	{

	};

	namespace detail
	{
		template<size_t COUNT_BYTES>
		class magic_traits
		{
		public:
			using UTYPE = std::uintmax_t;
		};

		template<>
		class magic_traits<1>
		{
		public:
			using UTYPE = std::uint8_t;
		};

		template<>
		class magic_traits<2>
		{
		public:
			using UTYPE = std::uint16_t;
		};

		template<>
		class magic_traits<3>
		{
		public:
			using UTYPE = std::uint32_t;
		};

		template<>
		class magic_traits<4>
		{
		public:
			using UTYPE = std::uint32_t;
		};

		template<>
		class magic_traits<5>
		{
		public:
			using UTYPE = std::uint64_t;
		};

		template<>
		class magic_traits<6>
		{
		public:
			using UTYPE = std::uint64_t;
		};

		template<>
		class magic_traits<7>
		{
		public:
			using UTYPE = std::uint64_t;
		};

		template<>
		class magic_traits<8>
		{
		public:
			using UTYPE = std::uint64_t;
		};
	}

	template<size_t COUNT_VALUEBITS, size_t COUNT_MAXPATTERNBITS>
	class magic<COUNT_VALUEBITS, COUNT_MAXPATTERNBITS, true>
	{
	protected:
		constexpr static size_t requiredBitBytes(const size_t bits) noexcept
		{
			if (bits > 32)
				return 8;
			if (bits > 16)
				return 4;
			if (bits > 8)
				return 2;
			return 1;
		}
	public:
		constexpr static const size_t countMaxPatternBits{ COUNT_MAXPATTERNBITS };
		constexpr static const size_t countValueBits{ COUNT_VALUEBITS };
		using bitsType = uint_t<countValueBits, false>;
		using sizeType = typename detail::magic_traits<magic::requiredBitBytes(countMaxPatternBits)>::UTYPE;
	private:
		bitsType m_Premask;
		sizeType m_CountBits;
	protected:
		constexpr void setPremask(const bitsType& premask) noexcept
		{
			m_Premask = premask;
			m_CountBits = m_Premask.populationCount();
			assert(m_Premask.populationCount() <= countMaxPatternBits);
		}
		constexpr magic(const bitsType& premask, const size_t countValueBits) noexcept :
			m_Premask{ premask },
			m_CountBits{ static_cast<sizeType>(static_cast<typename std::make_unsigned<size_t>::type>(countValueBits)) }
		{
			assert(m_Premask.populationCount() <= countMaxPatternBits);
		}
	public:
		magic(const bitsType& premask) noexcept :
			m_Premask{ premask },
			m_CountBits{ static_cast<sizeType>(premask.populationCount()) }
		{
			assert(m_Premask.populationCount() <= countMaxPatternBits);
		}
		constexpr magic(const magic&) = default;
		constexpr magic(magic&&) = default;
		constexpr magic(const bitsType& premask, const bitsType&, const sizeType bits) noexcept :
			magic<countValueBits, countMaxPatternBits, true>(premask, bits)
		{
		}
		constexpr magic& operator=(const magic&) noexcept = default;
		constexpr magic& operator=(magic&&) noexcept = default;
		~magic() noexcept = default;
		constexpr const bitsType& premask() const noexcept
		{
			return m_Premask;
		}
		constexpr size_t countBits() const noexcept
		{
			return m_CountBits;
		}
		constexpr size_t countValues() const noexcept
		{
			return static_cast<size_t>(size_t(1) << m_CountBits);
		}
		size_t cast(const bitsType& bitboard) const noexcept
		{
			return static_cast<size_t>(bitboard.extractPattern(m_Premask));
		}
	public:
		void find(bitsType& premask, bitsType& factor, size_t& countValueBits) const noexcept
		{
			premask = m_Premask;
			bitsType::findMagic(m_Premask, factor, countValueBits);
		}
	protected:
		void find(const bitsType& premask, bitsType& factor) noexcept
		{
			m_Premask = premask;
			assert(m_Premask.populationCount() <= countMaxPatternBits);
			size_t countValueBits;
			bitsType::findMagic(m_Premask, factor, countValueBits);
			m_CountBits = static_cast<sizeType>(static_cast<typename std::make_unsigned<size_t>::type>(countValueBits));
		}
	};

	template<size_t COUNT_VALUEBITS, size_t COUNT_MAXPATTERNBITS>
	class magic<COUNT_VALUEBITS, COUNT_MAXPATTERNBITS, false>
		: public magic<COUNT_VALUEBITS, COUNT_MAXPATTERNBITS, true>
	{
	public:
		constexpr static const size_t countMaxPatternBits{ COUNT_MAXPATTERNBITS };
		constexpr static const size_t countValueBits{ COUNT_VALUEBITS };
		using bitsType = uint_t<countValueBits, false>;
		using sizeType = typename detail::magic_traits<magic::requiredBitBytes(countMaxPatternBits)>::UTYPE;
	protected:
		bitsType m_Factor;
	private:
		constexpr static size_t castMagic(const bitsType& bits, const bitsType& premask, const bitsType& factor, const size_t countIndexBits) noexcept
		{
			return static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>((((bits & premask) * factor) >> (countValueBits - countIndexBits))));
		}
	public:
		magic(const bitsType& premask) noexcept :
			magic<countValueBits, countMaxPatternBits, true>(premask),
			m_Factor{ bitsType::zero() }
		{
			this->find(premask, m_Factor);
		}
		constexpr magic(const magic&) = default;
		constexpr magic(magic&&) = default;
		constexpr magic(const bitsType& premask, const bitsType& factor, const size_t bits) noexcept :
			magic<countValueBits, countMaxPatternBits, true>(premask, bits),
			m_Factor{ factor }
		{
		}
		constexpr magic& operator=(const magic&) noexcept = default;
		constexpr magic& operator=(magic&&) noexcept = default;
		~magic() noexcept = default;
		size_t cast(const bitsType& bitboard) const noexcept
		{
			return magic::castMagic(bitboard, this->premask(), m_Factor, this->countBits());
		}
		constexpr const bitsType& factor() const noexcept
		{
			return m_Factor;
		}
	};
}