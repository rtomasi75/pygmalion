namespace pygmalion::intrinsics
{
	template<size_t COUNT_MAXPATTERNBITS, typename VALUE, bool USEBMI>
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

	template<size_t COUNT_MAXPATTERNBITS, typename VALUE>
	class magic<COUNT_MAXPATTERNBITS, VALUE, true>
	{
	protected:
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
		using bitsType = VALUE;
		using sizeType = typename detail::magic_traits<magic::requiredBitBytes(countMaxPatternBits)>::UTYPE;
	private:
		bitsType m_Premask;
		using shiftType = uint_t<requiredUnsignedBits(bitsType::countBits), true>;
		shiftType m_CountBits;
		constexpr static shiftType toShift(const size_t sz) noexcept
		{
			return shiftType(static_cast<typename std::make_unsigned<size_t>::type>(sz));
		}
		constexpr static size_t toSize(const shiftType& s) noexcept
		{
			return static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(s));
		}
	protected:
		constexpr void setPremask(const bitsType& premask) noexcept
		{
			m_Premask = premask;
			m_CountBits = toShift(m_Premask.populationCount());
			assert(m_Premask.populationCount() <= countMaxPatternBits);
		}
		constexpr magic(const bitsType& premask, const size_t countValueBits) noexcept :
			m_Premask{ premask },
			m_CountBits{ toShift(countValueBits) }
		{
			assert(m_Premask.populationCount() <= countMaxPatternBits);
		}
	public:
		magic(const bitsType& premask) noexcept :
			m_Premask{ premask },
			m_CountBits{ toShift(premask.populationCount()) }
		{
			assert(m_Premask.populationCount() <= countMaxPatternBits);
		}
		constexpr magic(const magic&) = default;
		constexpr magic(magic&&) = default;
		constexpr magic(const bitsType& premask, const bitsType&, const sizeType bits) noexcept :
			magic<countMaxPatternBits, VALUE, true>(premask, bits)
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
			return toSize(m_CountBits);
		}
		constexpr size_t countValues() const noexcept
		{
			return static_cast<size_t>(size_t(1) << toSize(m_CountBits));
		}
		size_t cast(const bitsType& bitboard) const noexcept
		{
			return static_cast<size_t>(bitboard.extractPattern(m_Premask));
		}
	public:
		void find(bitsType& premask, bitsType& factor, size_t& countIndexBits) const noexcept
		{
			premask = m_Premask;
			magic::findMagic(m_Premask, factor, countIndexBits);
		}
	protected:
		constexpr static size_t castMagic(const bitsType& bits, const bitsType& premask, const bitsType& factor, const size_t countIndexBits) noexcept
		{
			return static_cast<size_t>((((bits & premask) * factor) >> (bitsType::countBits - countIndexBits)));
		}
	private:
		static void findMagic(const bitsType& premask, bitsType& factor, size_t& countIndexBits) noexcept
		{
			countIndexBits = premask.populationCount();
			const size_t N{ size_t(1) << countIndexBits };
			size_t* pIndices = new size_t[N];
			bool* pUsed = new bool[N];
			while (true)
			{
				bool bFound{ true };
				factor = bitsType::sparse();
				for (size_t i = 0; i < N; i++)
				{
					pIndices[i] = 0;
					pUsed[i] = false;
				}
				const bitsType N2{ bitsType(static_cast<typename std::make_unsigned<size_t>::type>(N)) };
				for (bitsType k = 0; k < N; k++)
				{
					const bitsType pattern{ k.deposePattern(premask) };
					const size_t idx{ magic::castMagic(pattern,premask,factor,countIndexBits) };
					assert(idx < N);
					if (pUsed[idx])
					{
						bFound = false;
						break;
					}
					pUsed[idx] = true;
					pIndices[idx] = static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(k));
				}
				if (bFound)
					break;
			}
			delete[] pIndices;
			delete[] pUsed;
		}
	protected:
		void find(const bitsType& premask, bitsType& factor) noexcept
		{
			m_Premask = premask;
			assert(m_Premask.populationCount() <= countMaxPatternBits);
			size_t countIndexBits;
			magic::findMagic(m_Premask, factor, countIndexBits);
			m_CountBits = toShift(countIndexBits);
		}
	};

	template<size_t COUNT_MAXPATTERNBITS, typename VALUE>
	class magic<COUNT_MAXPATTERNBITS, VALUE, false>
		: public magic<COUNT_MAXPATTERNBITS, VALUE, true>
	{
	public:
		constexpr static const size_t countMaxPatternBits{ COUNT_MAXPATTERNBITS };
		using bitsType = VALUE;
		using sizeType = typename detail::magic_traits<magic::requiredBitBytes(countMaxPatternBits)>::UTYPE;
	protected:
		bitsType m_Factor;
	public:
		magic(const bitsType& premask) noexcept :
			magic<countMaxPatternBits, VALUE, true>(premask),
			m_Factor{ bitsType::zero() }
		{
			this->find(premask, m_Factor);
		}
		constexpr magic(const magic&) = default;
		constexpr magic(magic&&) = default;
		constexpr magic(const bitsType& premask, const bitsType& factor, const size_t bits) noexcept :
			magic<countMaxPatternBits, VALUE, true>(premask, bits),
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