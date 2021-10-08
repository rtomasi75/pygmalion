namespace pygmalion
{
	namespace detail
	{
		template<size_t COUNT_BYTES>
		class enumeration_traits
		{
		public:
			using STYPE = std::intmax_t;
		};

		template<>
		class enumeration_traits<1>
		{
		public:
			using STYPE = std::int8_t;
		};

		template<>
		class enumeration_traits<2>
		{
		public:
			using STYPE = std::int16_t;
		};

		template<>
		class enumeration_traits<3>
		{
		public:
			using STYPE = std::int32_t;
		};

		template<>
		class enumeration_traits<4>
		{
		public:
			using STYPE = std::int32_t;
		};

		template<>
		class enumeration_traits<5>
		{
		public:
			using STYPE = std::int64_t;
		};

		template<>
		class enumeration_traits<6>
		{
		public:
			using STYPE = std::int64_t;
		};

		template<>
		class enumeration_traits<7>
		{
		public:
			using STYPE = std::int64_t;
		};

		template<>
		class enumeration_traits<8>
		{
		public:
			using STYPE = std::int64_t;
		};
	}

	template<size_t COUNT, size_t HASHBITS, typename INSTANCE>
	class enumeration
	{
	private:
		constexpr static size_t requiredSignedBytes(const size_t number) noexcept
		{
			if (number >= (size_t(1) << 31))
				return 8;
			if (number >= (size_t(1) << 15))
				return 4;
			if (number >= (size_t(1) << 7))
				return 2;
			return 1;
		}
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
	public:
		using instanceType = INSTANCE;
		constexpr static size_t countValues{ COUNT };
		constexpr static size_t countHashBits{ HASHBITS };
		constexpr static size_t countUnsignedBits{ requiredUnsignedBits(countValues) };
		constexpr static size_t countSignedBits{ countUnsignedBits + 1 };
		static inline const hashprovider<countHashBits, countValues> m_HashTable{ hashprovider<countHashBits, countValues>() };
		using baseType = typename detail::enumeration_traits<requiredSignedBytes(countValues)>::STYPE;
		using hashValue = typename hashprovider<countHashBits, countValues>::hashValue;
		enum valueType : baseType
		{
			invalid = -1,
			end = countValues
		};
	private:
		valueType m_Value;
	protected:
		PYGMALION_INLINE constexpr enumeration(const enumeration&) noexcept = default;
		PYGMALION_INLINE constexpr enumeration(enumeration&&) noexcept = default;
		PYGMALION_INLINE constexpr enumeration() noexcept :
			m_Value(valueType::invalid)
		{

		}
		PYGMALION_INLINE constexpr enumeration(const baseType& value) noexcept :
			m_Value(static_cast<valueType>(value))
		{
		}
		PYGMALION_INLINE constexpr enumeration(const valueType value) noexcept :
			m_Value(value)
		{
		}
		PYGMALION_INLINE constexpr enumeration& operator=(enumeration&&) noexcept = default;
		PYGMALION_INLINE constexpr enumeration& operator=(const enumeration&) noexcept = default;
	public:
		PYGMALION_INLINE constexpr static const hashValue& hash(const instanceType& instance) noexcept
		{
			return m_HashTable[instance];
		}
		PYGMALION_INLINE ~enumeration() noexcept = default;
		PYGMALION_INLINE constexpr operator baseType() const noexcept
		{
			return static_cast<baseType>(m_Value);
		}
		PYGMALION_INLINE constexpr instanceType next() const noexcept
		{
			return instanceType(static_cast<valueType>(((static_cast<baseType>(m_Value) + 1) % static_cast<baseType>(countValues))));
		}
		PYGMALION_INLINE constexpr instanceType previous() const noexcept
		{
			return instanceType(static_cast<valueType>(((static_cast<baseType>(m_Value) + countValues - 1) % static_cast<baseType>(countValues))));
		}
		PYGMALION_INLINE constexpr bool isValid() const noexcept
		{
			return (static_cast<baseType>(m_Value) >= 0) && (static_cast<baseType>(m_Value) < COUNT);
		}
		PYGMALION_INLINE constexpr instanceType operator++(int) noexcept
		{
			const instanceType temp{ m_Value };
			m_Value = static_cast<valueType>((static_cast<baseType>(m_Value) + 1) % countValues);
			return temp;
		}
		PYGMALION_INLINE constexpr instanceType& operator++() noexcept
		{
			m_Value = static_cast<valueType>((static_cast<baseType>(m_Value) + 1) % countValues);
			return *static_cast<instanceType*>(this);
		}
		PYGMALION_INLINE constexpr instanceType operator--(int) noexcept
		{
			const instanceType temp{ m_Value };
			m_Value = static_cast<valueType>((static_cast<baseType>(m_Value) + countValues - 1) % countValues);
			return temp;
		}
		PYGMALION_INLINE constexpr instanceType& operator--() noexcept
		{
			m_Value = static_cast<valueType>((static_cast<baseType>(m_Value) + countValues - 1) % countValues);
			return *static_cast<instanceType*>(this);
		}
		PYGMALION_INLINE constexpr instanceType& operator|=(const instanceType& other) noexcept
		{
			m_Value = static_cast<valueType>(static_cast<baseType>(m_Value) | other);
			return *static_cast<instanceType*>(this);
		}
		struct iterator
		{
		private:
			baseType m_Current;
		public:
			typedef instanceType value_type;
			typedef std::ptrdiff_t difference_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			typedef std::input_iterator_tag iterator_category;
			PYGMALION_INLINE constexpr iterator(const baseType& start) noexcept :
				m_Current{ start }
			{

			}
			PYGMALION_INLINE ~iterator() noexcept = default;
			PYGMALION_INLINE constexpr auto operator++(int) noexcept
			{
				iterator ret(m_Current);
				++(*this);
				return std::move(ret);
			}
			PYGMALION_INLINE constexpr iterator& operator++() noexcept
			{
				++m_Current;
				return *this;
			}
			PYGMALION_INLINE constexpr value_type operator*() const noexcept
			{
				return m_Current;
			}
			PYGMALION_INLINE constexpr bool operator==(const iterator& other) const noexcept
			{
				return m_Current == other.m_Current;
			}
			PYGMALION_INLINE constexpr bool operator!=(const iterator& other) const noexcept
			{
				return m_Current != other.m_Current;
			}
		};
		struct enumerationRange
		{
		public:
			PYGMALION_INLINE constexpr enumerationRange() noexcept = default;
			PYGMALION_INLINE ~enumerationRange() noexcept = default;
			PYGMALION_INLINE constexpr auto begin() const noexcept
			{
				return iterator(0);
			}
			PYGMALION_INLINE constexpr auto end() const noexcept
			{
				constexpr iterator endValue{ iterator(COUNT) };
				return endValue;
			}
		};
		constexpr static enumerationRange range{ enumerationRange() };
	};
}