namespace pygmalion
{
	template<int BITCOUNT>
	class bitfield
	{
	public:
		constexpr static int bitCount{ BITCOUNT };
		using traitsType = int_traits<requiredBitBytes(bitCount)>;
		using bitsType = typename traitsType::UTYPE;
		using bitType = bit<bitCount>;
		using invertorType = invertBits<requiredBitBytes(bitCount), bitCount>;
		using multiplierType = multiplyBits<requiredBitBytes(bitCount), bitCount>;
	private:
		bitsType m_Bits;
	public:
		constexpr void setBit(const bitType bit) noexcept
		{
			traitsType::setBit(m_Bits, bit);
		}
		constexpr void clearBit(const bitType bit) noexcept
		{
			traitsType::clearBit(m_Bits, bit);
		}
		constexpr bool getBit(const bitType bit) const noexcept
		{
			return traitsType::checkBit(m_Bits, bit);
		}
		constexpr bool operator[](const bitType bit) const noexcept
		{
			return traitsType::checkBit(m_Bits, bit);
		}
		constexpr bitsType bits() const noexcept
		{
			return m_Bits;
		}
		constexpr bitfield(const bitsType bits) noexcept :
			m_Bits(bits)
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
		constexpr static bitfield setMask(const bitType bit) noexcept
		{
			return bitfield(traitsType::setMask(bit));
		}
		constexpr static bitfield clearMask(const bitType bit) noexcept
		{
			return bitfield(traitsType::clearMask(bit));
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
		bool firstSetBit(bitType& bit) const noexcept
		{
			int ret;
			if (int_traits<requiredBitBytes(bitCount)>::bitScanForward(m_Bits, ret))
			{
				bit = ret;
				return true;
			}
			else
				return false;
		}
		bool lastSetBit(bitType& bit) const noexcept
		{
			int ret;
			if (int_traits<requiredBitBytes(bitCount)>::bitScanReverse(m_Bits, ret))
			{
				bit = ret;
				return true;
			}
			else
				return false;
		}
		int populationCount() const noexcept
		{
			return int_traits<requiredBitBytes(bitCount)>::populationCount(m_Bits);
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
			using value_type = bitType;
		private:
			bitfield m_State;
			value_type m_Current;
			constexpr iterator() noexcept :
				m_State{ 0 },
				m_Current{ -1 }
			{
			}
		public:
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::input_iterator_tag;
			constexpr explicit iterator(const bitfield state) noexcept :
				m_State{ state },
				m_Current{ bitType::invalid }
			{
				m_State.firstSetBit(m_Current);
			}
			constexpr iterator(const iterator&) noexcept = default;
			~iterator() noexcept = default;
			constexpr iterator operator++(int) noexcept
			{
				assert(m_Current.isValid());
				iterator ret(m_State);
				++(*this);
				return std::move(ret);
			}
			constexpr iterator& operator++() noexcept
			{
				assert(m_Current.isValid());
				m_State.clearBit(m_Current);
				if (!m_State.firstSetBit(m_Current))
					m_Current = -1;
				return *this;
			}
			constexpr value_type operator*() const noexcept
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