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
		template<typename SETINSTANCE>
		class set
		{
		public:
			using setType = SETINSTANCE;
			using bitsType = uint_t<countValues, false>;
		private:
			bitsType m_Bits;
			constexpr static size_t bit(const instanceType index) noexcept
			{
				return static_cast<typename instanceType::baseType>(index);
			}
		public:
			constexpr static inline const size_t countIndices{ 1 << countValues};
			PYGMALION_INLINE instanceType first() const noexcept
			{
				size_t bit;
#if defined(_DEBUG)
				const bool bResult{ m_Bits.bitscanForward(bit) };
				PYGMALION_ASSERT(bResult);
#else
				m_Bits.bitscanForward(bit);
#endif
				return static_cast<instanceType>(bit);
			}
			PYGMALION_INLINE instanceType last() const noexcept
			{
				size_t bit;
#if defined(_DEBUG)
				const bool bResult{ m_Bits.bitscanReverse(bit) };
				PYGMALION_ASSERT(bResult);
#else
				m_Bits.bitscanReverse(bit);
#endif
				return static_cast<instanceType>(bit);
			}
			PYGMALION_INLINE const bitsType& bits() const noexcept
			{
				return m_Bits;
			}
			PYGMALION_INLINE constexpr static setType none() noexcept
			{
				constexpr const bitsType zeroBits{ bitsType(0) };
				return setType(zeroBits);
			}
			PYGMALION_INLINE constexpr static setType all() noexcept
			{
				return ~none();
			}
			PYGMALION_INLINE constexpr void clear() noexcept
			{
				constexpr const bitsType zeroBits{ bitsType(0) };
				m_Bits = zeroBits;
			}
			PYGMALION_INLINE constexpr explicit set(const bitsType& bits) noexcept :
				m_Bits{ bits }
			{

			}
			PYGMALION_INLINE constexpr explicit operator bitsType() const noexcept
			{
				return m_Bits;
			}
			PYGMALION_INLINE constexpr setType operator*(const bool value) const noexcept
			{
				const bitsType bits{ m_Bits };
				const bitsType valueBits{ bitsType(static_cast<unsigned int>(value)) };
				return setType(bits * valueBits);
			}
			PYGMALION_INLINE constexpr setType operator|(const setType other) const noexcept
			{
				const bitsType bits{ m_Bits | other.m_Bits };
				return setType(std::move(bits));
			}
			PYGMALION_INLINE constexpr setType operator-(const setType other) const noexcept
			{
				return setType(m_Bits & ~other.m_Bits);
			}
			PYGMALION_INLINE constexpr setType operator&(const setType other) const noexcept
			{
				return setType(m_Bits & other.m_Bits);
			}
			PYGMALION_INLINE constexpr setType operator^(const setType other) const noexcept
			{
				return setType(m_Bits ^ other.m_Bits);
			}
			PYGMALION_INLINE constexpr setType operator~() const noexcept
			{
				return setType(~m_Bits);
			}
			PYGMALION_INLINE constexpr setType& operator|=(const setType other) noexcept
			{
				m_Bits |= other.m_Bits;
				return *static_cast<setType*>(this);
			}
			PYGMALION_INLINE constexpr setType& operator-=(const setType other) noexcept
			{
				m_Bits &= ~other.m_Bits;
				return *static_cast<setType*>(this);
			}
			PYGMALION_INLINE constexpr setType& operator&=(const setType other) noexcept
			{
				m_Bits &= other.m_Bits;
				return *static_cast<setType*>(this);
			}
			PYGMALION_INLINE constexpr setType& operator^=(const setType other) noexcept
			{
				m_Bits ^= other.m_Bits;
				return *static_cast<setType*>(this);
			}
			PYGMALION_INLINE constexpr bool operator==(const setType other) const noexcept
			{
				return m_Bits == other.m_Bits;
			}
			PYGMALION_INLINE constexpr bool operator!=(const setType other) const noexcept
			{
				return m_Bits != other.m_Bits;
			}
			PYGMALION_INLINE constexpr setType& operator|=(const instanceType index) noexcept
			{
				m_Bits.set(static_cast<typename instanceType::baseType>(index));
				return *static_cast<setType*>(this);
			}
			PYGMALION_INLINE constexpr setType& operator&=(const instanceType index) noexcept
			{
				m_Bits &= bitsType::setMask(static_cast<typename instanceType::baseType>(index));
				return *static_cast<setType*>(this);
			}
			PYGMALION_INLINE constexpr setType& operator-=(const instanceType index) noexcept
			{
				m_Bits.clear(static_cast<typename instanceType::baseType>(index));
				return *static_cast<setType*>(this);
			}
			PYGMALION_INLINE constexpr setType& operator^=(const instanceType index) noexcept
			{
				m_Bits.toggle(static_cast<typename instanceType::baseType>(index));
				return *static_cast<setType*>(this);
			}
			PYGMALION_INLINE constexpr setType singleElement() const noexcept
			{
				assert(m_Bits.populationCount() == 1);
				return setType(m_Bits.singleBit());
			}
			PYGMALION_INLINE constexpr bool operator[](const instanceType index) const noexcept
			{
				return m_Bits[static_cast<typename instanceType::baseType>(index)];
			}
			PYGMALION_INLINE constexpr operator bool() const noexcept
			{
				return static_cast<bool>(m_Bits);
			}
			PYGMALION_INLINE constexpr set() noexcept :
				m_Bits{ bitsType::zero() }
			{

			}
			PYGMALION_INLINE constexpr set(const instanceType square) noexcept :
				m_Bits{ bitsType::zero() }
			{
				m_Bits.set(square);
			}
			PYGMALION_INLINE constexpr set(const set&) noexcept = default;
			PYGMALION_INLINE constexpr set(set&&) noexcept = default;
			PYGMALION_INLINE constexpr set& operator=(const set&) = default;
			PYGMALION_INLINE constexpr set& operator=(set&&) = default;
			PYGMALION_INLINE ~set() noexcept = default;
			PYGMALION_INLINE size_t count() const noexcept
			{
				return m_Bits.populationCount();
			}
			class iterator
			{
				friend class set;
			public:
				using value_type = instanceType;
			private:
				typename bitsType::iterator m_Iterator;
				PYGMALION_INLINE constexpr iterator(const typename bitsType::iterator& it) noexcept :
					m_Iterator{ it }
				{
				}
			public:
				using difference_type = std::ptrdiff_t;
				using pointer = value_type*;
				using reference = value_type&;
				using iterator_category = std::input_iterator_tag;
				PYGMALION_INLINE constexpr iterator(const iterator&) noexcept = default;
				PYGMALION_INLINE ~iterator() noexcept = default;
				PYGMALION_INLINE constexpr iterator&& operator++(int) noexcept
				{
					iterator ret(m_Iterator);
					++(*this);
					return std::move(ret);
				}
				PYGMALION_INLINE constexpr iterator& operator++() noexcept
				{
					++m_Iterator;
					return *this;
				}
				PYGMALION_INLINE constexpr value_type operator*() const noexcept
				{
					return static_cast<value_type>(*m_Iterator);
				}
				PYGMALION_INLINE constexpr bool operator==(const iterator& other) const noexcept
				{
					return m_Iterator == other.m_Iterator;
				}
				PYGMALION_INLINE constexpr bool operator!=(const iterator& other) const noexcept
				{
					return m_Iterator != other.m_Iterator;
				}
			};
			class counterType
			{
				friend class set;
			private:
				typename bitsType::counterType m_Counter;
				PYGMALION_INLINE constexpr counterType(const set& it) noexcept :
					m_Counter{ it.counter() }
				{
				}
			public:
				PYGMALION_INLINE constexpr counterType(const counterType&) noexcept = default;
				PYGMALION_INLINE ~counterType() noexcept = default;
				PYGMALION_INLINE constexpr bool next() noexcept
				{
					return m_Counter.next();
				}
			};
			PYGMALION_INLINE constexpr auto begin() const noexcept
			{
				return iterator(m_Bits.begin());
			}
			PYGMALION_INLINE constexpr auto end() const noexcept
			{
				return iterator(m_Bits.end());
			}
			PYGMALION_INLINE constexpr auto counter() const noexcept
			{
				return counterType(*this);
			}
			template<typename LAMBDA>
			PYGMALION_INLINE constexpr void foreach(const LAMBDA& lambda) const noexcept
			{
				m_Bits.foreach([lambda](const size_t index) {lambda(static_cast<instanceType>(index)); });
			}
			PYGMALION_INLINE constexpr void clearElement(const instanceType index) noexcept
			{
				return m_Bits.clear(static_cast<size_t>(index));
			}
			PYGMALION_INLINE constexpr void setElement(const instanceType index) noexcept
			{
				return m_Bits.set(static_cast<size_t>(index));
			}
			PYGMALION_INLINE constexpr void checkElement(const instanceType index, bool bSet) noexcept
			{
				return m_Bits.check(static_cast<size_t>(index), bSet);
			}
			struct iteratorRange
			{
			private:
				size_t m_Current;
			public:
				typedef setType value_type;
				typedef std::ptrdiff_t difference_type;
				typedef setType* pointer;
				typedef setType& reference;
				typedef std::input_iterator_tag iterator_category;
				PYGMALION_INLINE constexpr iteratorRange(const bitsType& start) noexcept :
					m_Current{ start }
				{

				}
				PYGMALION_INLINE ~iteratorRange() noexcept = default;
				PYGMALION_INLINE constexpr auto operator++(int) noexcept
				{
					iterator ret(m_Current);
					++(*this);
					return std::move(ret);
				}
				PYGMALION_INLINE constexpr iteratorRange& operator++() noexcept
				{
					++m_Current;
					return *this;
				}
				PYGMALION_INLINE constexpr value_type operator*() const noexcept
				{
					return setType(m_Current);
				}
				PYGMALION_INLINE constexpr bool operator==(const iteratorRange& other) const noexcept
				{
					return m_Current == other.m_Current;
				}
				PYGMALION_INLINE constexpr bool operator!=(const iteratorRange& other) const noexcept
				{
					return m_Current != other.m_Current;
				}
			};
			struct setRange
			{
			public:
				PYGMALION_INLINE constexpr setRange() noexcept = default;
				PYGMALION_INLINE ~setRange() noexcept = default;
				PYGMALION_INLINE constexpr auto begin() const noexcept
				{
					return iteratorRange(0);
				}
				PYGMALION_INLINE constexpr auto end() const noexcept
				{
					constexpr iteratorRange endValue{ iteratorRange(countIndices) };
					return endValue;
				}
			};
			constexpr static setRange range{ setRange() };
			PYGMALION_INLINE constexpr size_t toIndex() const noexcept
			{
				return static_cast<size_t>(m_Bits);
			}
	};
	};
}