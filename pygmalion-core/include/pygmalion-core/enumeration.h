namespace pygmalion
{
	template<size_t COUNT>
	class enumeration
	{
	public:
		using baseType = typename int_traits<requiredSignedBytes(COUNT)>::STYPE;
		enum valueType : baseType
		{
			invalid = -1
		};
	private:
		valueType m_Value;
	public:
		constexpr enumeration(const enumeration&) noexcept = default;
		constexpr enumeration(enumeration&&) noexcept = default;
		constexpr enumeration& operator=(enumeration&&) noexcept = default;
		constexpr enumeration& operator=(const enumeration&) noexcept = default;
		constexpr enumeration(const baseType value) noexcept :
			m_Value(static_cast<valueType>(value))
		{
		}
		constexpr enumeration() noexcept :
			m_Value(valueType::invalid)
		{

		}
		constexpr enumeration(const valueType value) noexcept :
			m_Value(value)
		{
		}
		constexpr operator baseType() const noexcept
		{
			return static_cast<baseType>(m_Value);
		}
		constexpr auto next() const noexcept
		{
			assert(this->isValid());
			return enumeration(static_cast<valueType>(((static_cast<baseType>(m_Value) + 1) % static_cast<baseType>(COUNT))));
		}
		constexpr bool isValid() const noexcept
		{
			return (static_cast<baseType>(m_Value) >= 0) && (static_cast<baseType>(m_Value) < COUNT);
		}
		constexpr static valueType countValues{ COUNT };
		constexpr auto operator%=(const enumeration divisor) noexcept
		{
			m_Value = static_cast<valueType>(static_cast<baseType>(m_Value) % static_cast<baseType>(divisor.m_Value));
		}
		constexpr auto operator++(int) noexcept
		{
			const enumeration temp{ m_Value };
			m_Value = static_cast<valueType>(static_cast<baseType>(m_Value) + 1);
			return std::move(temp);
		}
		constexpr enumeration& operator++() noexcept
		{
			m_Value = static_cast<valueType>(static_cast<baseType>(m_Value) + 1);
			return *this;
		}
		constexpr auto operator--(int) noexcept
		{
			const enumeration temp{ m_Value };
			m_Value = static_cast<valueType>(static_cast<baseType>(m_Value) - 1);
			return std::move(temp);
		}
		constexpr enumeration& operator--() noexcept
		{
			m_Value = static_cast<valueType>(static_cast<baseType>(m_Value) - 1);
			return *this;
		}
		constexpr enumeration& operator|=(const enumeration other) noexcept
		{
			m_Value = static_cast<valueType>(static_cast<baseType>(m_Value) | other);
			return *this;
		}
		struct iterator
		{
		private:
			baseType m_Current;
		public:
			typedef enumeration value_type;
			typedef std::ptrdiff_t difference_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			typedef std::input_iterator_tag iterator_category;
			constexpr iterator(const baseType start) noexcept :
				m_Current{ start }
			{

			}
			~iterator() noexcept = default;
			constexpr auto operator++(int) noexcept
			{
				iterator ret(m_Current);
				++(*this);
				return std::move(ret);
			}
			constexpr iterator& operator++() noexcept
			{
				assert(m_Current < COUNT);
				m_Current++;
				return *this;
			}
			constexpr value_type operator*() const noexcept
			{
				return m_Current;
			}
			constexpr bool operator==(const iterator& other) const noexcept
			{
				return m_Current == other.m_Current;
			}
			constexpr bool operator!=(const iterator& other) const noexcept
			{
				return m_Current != other.m_Current;
			}
		};
		struct enumerationRange
		{
		public:
			constexpr enumerationRange() noexcept = default;
			~enumerationRange() noexcept = default;
			constexpr auto begin() const noexcept
			{
				return iterator(0);
			}
			constexpr auto end() const noexcept
			{
				constexpr iterator endValue{ iterator(COUNT) };
				return endValue;
			}
		};
		constexpr static enumerationRange range{ enumerationRange() };
	};
}