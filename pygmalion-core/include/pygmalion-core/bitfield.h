namespace pygmalion
{
	template<int BITCOUNT>
	class bitfield
	{
	public:
		constexpr static int bitCount{ BITCOUNT };
		using traitsType = int_traits<requiredBitBytes(bitCount)>;
		using baseType = typename traitsType::UTYPE;
		using invertorType = invertBits<requiredBitBytes(bitCount), bitCount>;
		using multiplierType = multiplyBits<requiredBitBytes(bitCount), bitCount>;
	private:
		baseType m_Bits;
	public:
		constexpr baseType bits() const noexcept
		{
			return m_Bits;
		}
		constexpr bitfield(const baseType value) noexcept :
			m_Bits(value)
		{

		}
		constexpr bitfield() noexcept :
			m_Bits(0)
		{

		}
		constexpr bitfield(const bitfield&) noexcept = default;
		constexpr bitfield(bitfield&&) noexcept = default;
		constexpr bitfield& operator=(const bitfield&) noexcept = default;
		constexpr bitfield& operator=(bitfield&&) noexcept = default;
		~bitfield() noexcept = default;
		constexpr static auto setMask(const int bit) noexcept
		{
			return bitfield(traitsType::setMask(bit));
		}
		constexpr static auto clearMask(const int bit) noexcept
		{
			return bitfield(traitsType::setMask(bit));
		}
		constexpr void setBit(const int bit) noexcept
		{
			traitsType::setBit(m_Bits, bit);
		}
		constexpr void clearBit(const int bit) noexcept
		{
			traitsType::clearBit(m_Bits, bit);
		}
		constexpr bool checkBit(const int bit) const noexcept
		{
			return traitsType::checkBit(m_Bits, bit);
		}
		constexpr bitfield operator|(const bitfield other) const noexcept
		{
			return bitfield(m_Bits | other.m_Bits);
		}
		constexpr bitfield operator&(const bitfield other) const noexcept
		{
			return bitfield(m_Bits & other.m_Bits);
		}
		constexpr bitfield operator^(const bitfield other) const noexcept
		{
			return bitfield(m_Bits ^ other.m_Bits);
		}
		constexpr bitfield operator~() const noexcept
		{
			return bitfield(invertorType::perform(m_Bits));
		}
		constexpr auto operator*(const bitfield other) const noexcept
		{
			return bitfield(multiplierType::perform(m_Bits, other.m_Bits));
		}
		constexpr auto operator*=(const bitfield other) noexcept
		{
			m_Bits = bitfield(multiplierType::perform(m_Bits, other.m_Bits));
			return *this;
		}
		constexpr auto operator |=(const bitfield other) noexcept
		{
			m_Bits |= other.m_Bits;
			return *this;
		}
		constexpr auto operator &=(const bitfield other) noexcept
		{
			m_Bits &= other.m_Bits;
			return *this;
		}
		constexpr auto operator ^=(const bitfield other) noexcept
		{
			m_Bits ^= other.m_Bits;
			return *this;
		}
		constexpr auto operator<<(const int shift) const noexcept
		{
			return bitfield(m_Bits << shift);
		}
		constexpr auto operator>>(const int shift) const noexcept
		{
			return bitfield(m_Bits >> shift);
		}
		constexpr bool operator==(const bitfield other) const noexcept
		{
			return m_Bits == other.m_Bits;
		}
		constexpr bool operator!=(const bitfield other) const noexcept
		{
			return m_Bits != other.m_Bits;
		}
		constexpr operator bool() const noexcept
		{
			return m_Bits;
		}
		auto populationCount() const noexcept
		{
			return int_traits<requiredBitBytes(bitCount)>::populationCount(m_Bits);
		}
		bool bitScanForward(int& bit) const noexcept
		{
			return int_traits<requiredBitBytes(bitCount)>::bitScanForward(m_Bits, bit);
		}
		bool bitScanReverse(int& bit) const noexcept
		{
			return int_traits<requiredBitBytes(bitCount)>::bitScanReverse(m_Bits, bit);
		}
		bitfield pext(const bitfield pattern) const noexcept
		{
			return  bitfield(int_traits<requiredBitBytes(bitCount)>::pext(m_Bits, pattern.bits()));
		}
		bitfield pdep(const bitfield pattern) const noexcept
		{
			return bitfield(int_traits<requiredBitBytes(bitCount)>::pdep(m_Bits, pattern.bits()));
		}
		static bitfield random() noexcept
		{
			return int_traits<requiredBitBytes(bitCount)>::rand();
		}
		static bitfield random_sparse() noexcept
		{
			return int_traits<requiredBitBytes(bitCount)>::rand_sparse();
		}
		constexpr static bitfield empty() noexcept
		{
			return bitfield(0);
		}
		constexpr static bitfield universe() noexcept
		{
			return bitfield(invertorType::perform(0));
		}
		class iterator
		{
			friend class bitfield;
		public:
			typedef int value_type;
		private:
			bitfield m_State;
			value_type m_Current;
			constexpr iterator() noexcept :
				m_State{ 0 },
				m_Current{ -1 }
			{

			}
		public:
			typedef std::ptrdiff_t difference_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			typedef std::input_iterator_tag iterator_category;
			constexpr explicit iterator(const bitfield state) noexcept :
				m_State{ state },
				m_Current{ -1 }
			{
				m_State.bitScanForward(m_Current);
			}
			constexpr iterator(const iterator&) noexcept = default;
			~iterator() noexcept = default;
			constexpr auto operator++(int) noexcept
			{
				iterator ret(m_State);
				++(*this);
				return std::move(ret);
			}
			constexpr iterator& operator++() noexcept
			{
				assert(m_Current >= 0);
				m_State.clearBit(m_Current);
				if (!m_State.bitScanForward(m_Current))
					m_Current = -1;
				return *this;
			}
			constexpr auto operator*() const noexcept
			{
				return m_Current;
			}
			constexpr bool operator==(const iterator& other) const noexcept
			{
				return m_State == other.m_State;
			}
			constexpr bool operator!=(const iterator& other) const noexcept
			{
				return m_State != other.m_State;
			}
		};
		constexpr auto begin() const noexcept
		{
			return iterator(*this);
		}
		constexpr auto end() const noexcept
		{
			constexpr iterator endValue;
			return endValue;
		}
	};

}