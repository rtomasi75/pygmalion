namespace pygmalion
{
	template<typename ENUMERATION, typename INSTANCE>
	class set
	{
	public:
		using enumerationType = ENUMERATION;
		using setType = INSTANCE;
		using bitsType = uint_t<enumerationType::countValues, false>;
	private:
		bitsType m_Bits;
		PYGMALION_INLINE constexpr static size_t bit(const enumerationType index) noexcept
		{
			return static_cast<typename enumerationType::baseType>(index);
		}
		constexpr static bool enableRange(const size_t first, const size_t last) noexcept
		{
			return (first <= last) && (last < enumerationType::countValues);
		}
	public:
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<set::enableRange(FIRST, LAST)>::type>
		PYGMALION_INLINE constexpr void clearRange() noexcept
		{
			m_Bits.template clearBits<FIRST, 1 + LAST - FIRST>();
	}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<set::enableRange(FIRST, LAST)>::type>
		PYGMALION_INLINE constexpr void setRange() noexcept
		{
			m_Bits.template setBits<FIRST, 1 + LAST - FIRST>();
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<set::enableRange(FIRST, LAST)>::type>
		PYGMALION_INLINE constexpr uint_t<1 + LAST - FIRST, false> extractRange() const noexcept
		{
			return m_Bits.template extractBits<FIRST, 1 + LAST - FIRST>();
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<set::enableRange(FIRST, LAST)>::type>
		PYGMALION_INLINE constexpr void storeRange(const uint_t<1 + LAST - FIRST, false>& bits) noexcept
		{
			m_Bits.template storeBits<FIRST, 1 + LAST - FIRST>(bits);
		}
		constexpr static inline const size_t countIndices{ 1 << enumerationType::countValues };
		PYGMALION_INLINE enumerationType first() const noexcept
		{
			size_t bit;
#if defined(_DEBUG)
			const bool bResult{ m_Bits.bitscanForward(bit) };
			PYGMALION_ASSERT(bResult);
#else
			m_Bits.bitscanForward(bit);
#endif
			return static_cast<enumerationType>(bit);
		}
		PYGMALION_INLINE enumerationType last() const noexcept
		{
			size_t bit;
#if defined(_DEBUG)
			const bool bResult{ m_Bits.bitscanReverse(bit) };
			PYGMALION_ASSERT(bResult);
#else
			m_Bits.bitscanReverse(bit);
#endif
			return static_cast<enumerationType>(bit);
		}
		PYGMALION_INLINE constexpr const bitsType& bits() const noexcept
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
			const bitsType bits{ m_Bits | other.bits() };
			return setType(std::move(bits));
		}
		PYGMALION_INLINE constexpr setType operator-(const setType other) const noexcept
		{
			return setType(m_Bits & ~other.bits());
		}
		PYGMALION_INLINE constexpr setType operator&(const setType other) const noexcept
		{
			return setType(m_Bits & other.bits());
		}
		PYGMALION_INLINE constexpr setType operator^(const setType other) const noexcept
		{
			return setType(m_Bits ^ other.bits());
		}
		PYGMALION_INLINE constexpr setType operator~() const noexcept
		{
			return setType(~m_Bits);
		}
		PYGMALION_INLINE constexpr setType& operator|=(const setType other) noexcept
		{
			m_Bits |= other.bits();
			return *static_cast<setType*>(this);
		}
		PYGMALION_INLINE constexpr setType& operator-=(const setType other) noexcept
		{
			m_Bits &= ~other.bits();
			return *static_cast<setType*>(this);
		}
		PYGMALION_INLINE constexpr setType& operator&=(const setType other) noexcept
		{
			m_Bits &= other.bits();
			return *static_cast<setType*>(this);
		}
		PYGMALION_INLINE constexpr setType& operator^=(const setType other) noexcept
		{
			m_Bits ^= other.bits();
			return *static_cast<setType*>(this);
		}
		PYGMALION_INLINE constexpr bool operator==(const setType other) const noexcept
		{
			return m_Bits == other.bits();
		}
		PYGMALION_INLINE constexpr bool operator!=(const setType other) const noexcept
		{
			return m_Bits != other.bits();
		}
		PYGMALION_INLINE constexpr setType& operator|=(const enumerationType index) noexcept
		{
			m_Bits.set(static_cast<typename enumerationType::baseType>(index));
			return *static_cast<setType*>(this);
		}
		PYGMALION_INLINE constexpr setType& operator&=(const enumerationType index) noexcept
		{
			m_Bits &= bitsType::setMask(static_cast<typename enumerationType::baseType>(index));
			return *static_cast<setType*>(this);
		}
		PYGMALION_INLINE constexpr setType& operator-=(const enumerationType index) noexcept
		{
			m_Bits.clear(static_cast<typename enumerationType::baseType>(index));
			return *static_cast<setType*>(this);
		}
		PYGMALION_INLINE constexpr setType& operator^=(const enumerationType index) noexcept
		{
			m_Bits.toggle(static_cast<typename enumerationType::baseType>(index));
			return *static_cast<setType*>(this);
		}
		PYGMALION_INLINE constexpr setType operator|(const enumerationType index) const noexcept
		{
			bitsType bits{ m_Bits };
			bits.set(static_cast<typename enumerationType::baseType>(index));
			return setType(std::move(bits));
		}
		PYGMALION_INLINE constexpr setType operator-(const enumerationType index) const noexcept
		{
			bitsType bits{ m_Bits };
			bits.clear(static_cast<typename enumerationType::baseType>(index));
			return setType(std::move(bits));
		}
		PYGMALION_INLINE constexpr setType operator&(const enumerationType index) const noexcept
		{
			bitsType bits{ m_Bits };
			bits.check(static_cast<typename enumerationType::baseType>(index), bits.test(static_cast<typename enumerationType::baseType>(index)));
			return setType(std::move(bits));
		}
		PYGMALION_INLINE constexpr setType operator^(const enumerationType index) const noexcept
		{
			bitsType bits{ m_Bits };
			bits.check(static_cast<typename enumerationType::baseType>(index), !bits.test(static_cast<typename enumerationType::baseType>(index)));
			return setType(std::move(bits));
		}
		PYGMALION_INLINE constexpr setType singleElement() const noexcept
		{
			assert(m_Bits.populationCount() == 1);
			return setType(m_Bits.singleBit());
		}
		PYGMALION_INLINE constexpr bool operator[](const enumerationType index) const noexcept
		{
			return m_Bits[static_cast<typename enumerationType::baseType>(index)];
		}
		PYGMALION_INLINE constexpr operator bool() const noexcept
		{
			return static_cast<bool>(m_Bits);
		}
		PYGMALION_INLINE constexpr set() noexcept :
			m_Bits{ bitsType::zero() }
		{

		}
		PYGMALION_INLINE constexpr set(const enumerationType index) noexcept :
			m_Bits{ bitsType::zero() }
		{
			m_Bits.set(index);
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
			using value_type = enumerationType;
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
			m_Bits.foreach([lambda](const size_t index) {lambda(static_cast<enumerationType>(index)); });
		}
		PYGMALION_INLINE constexpr void clearElement(const enumerationType index) noexcept
		{
			m_Bits.clear(static_cast<size_t>(index));
		}
		PYGMALION_INLINE constexpr void setElement(const enumerationType index) noexcept
		{
			m_Bits.set(static_cast<size_t>(index));
		}
		PYGMALION_INLINE constexpr void checkElement(const enumerationType index, bool bSet) noexcept
		{
			m_Bits.check(static_cast<size_t>(index), bSet);
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
		struct setRangeBase
		{
		public:
			PYGMALION_INLINE constexpr setRangeBase() noexcept = default;
			PYGMALION_INLINE ~setRangeBase() noexcept = default;
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
		constexpr static setRangeBase range{ setRangeBase() };
		PYGMALION_INLINE constexpr size_t toIndex() const noexcept
		{
			return static_cast<size_t>(m_Bits);
		}
	};
}