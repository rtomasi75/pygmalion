namespace pygmalion
{

	template<size_t LEN>
	struct score_base
	{
	};

	template<>
	struct score_base<1>
	{
	public:
		using HTYPE = std::int16_t;
		using  STYPE = std::int8_t;
	};
	template<>
	struct score_base<2>
	{
	public:
		using HTYPE = std::int32_t;
		using STYPE = std::int16_t;
	};
	template<>
	struct score_base<3>
	{
	public:
		using HTYPE = std::int64_t;
		using STYPE = std::int32_t;
	};
	template<>
	struct score_base<4>
	{
	public:
		using HTYPE = std::int64_t;
		using STYPE = std::int32_t;
	};

	template<size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
	struct score
	{
	public:
		using valueType = typename score_base < requiredSignedBytes((size_t(1) << MANTISSA) - 1) > ::STYPE;
	private:
		using longType = typename score_base < requiredSignedBytes((size_t(1) << MANTISSA) - 1) > ::HTYPE;
		static constexpr valueType MAXVALUE{ valueType((size_t(1) << MANTISSA) - 1) };
		static constexpr valueType MINVALUE{ valueType(-MAXVALUE) };
		static constexpr valueType WINVALUE{ valueType(MAXVALUE - 1) };
		static constexpr valueType LOSSVALUE{ valueType(MINVALUE + 1) };
		static constexpr valueType WINNINGVALUE{ valueType(MAXVALUE - 1 - MAXDIST) };
		static constexpr valueType LOSINGVALUE{ valueType(MINVALUE + 1 + MAXDIST) };
		valueType m_Value;
		constexpr score(const valueType value, const int unused) noexcept :
			m_Value(value)
		{

		}
	public:
		explicit operator std::string() const noexcept
		{
			std::stringstream sstr;
			if (m_Value == 0)
			{
				sstr << "0";
			}
			else if (isOpen())
			{
				const double flt = static_cast<double>(m_Value) / static_cast<double>(1 << SHIFT);
				if (flt >= 0)
					sstr << "+";
				sstr << flt;
			}
			else if (m_Value >= MAXVALUE)
			{
				sstr << "+inf";
			}
			else if (m_Value <= MINVALUE)
			{
				sstr << "-inf";
			}
			else if (m_Value == WINNINGVALUE)
			{
				sstr << "+M?";
			}
			else if (m_Value == LOSINGVALUE)
			{
				sstr << "-M?";
			}
			else
			{
				size_t range = m_Value > 0 ? WINVALUE - m_Value : m_Value - LOSSVALUE;
				sstr << (m_Value >= 0 ? "+" : "-");
				sstr << "M";
				sstr << range;
			}
			return sstr.str();
		}
		~score() = default;
		explicit constexpr score(const double value) noexcept :
			m_Value(static_cast<valueType>(value* static_cast<double>(1 << SHIFT)))
		{

		}
		explicit constexpr score(const float value) noexcept :
			score(static_cast<double>(value))
		{

		}
		constexpr score(score&&) noexcept = default;
		constexpr score(const score&) noexcept = default;
		constexpr score& operator=(score&&) noexcept = default;
		constexpr score& operator=(const score&)  noexcept = default;
		static constexpr auto atom() noexcept
		{
			return score(1, 0);
		};
		static constexpr auto one() noexcept
		{
			return score(1 << SHIFT, 0);
		};
		static constexpr auto zero() noexcept
		{
			return score(0, 0);
		}
		static constexpr auto win() noexcept
		{
			return score(WINVALUE, 0);
		}
		static constexpr auto winning() noexcept
		{
			return score(WINNINGVALUE, 0);
		}
		static constexpr auto losing() noexcept
		{
			return score(LOSINGVALUE, 0);
		}
		static constexpr auto loss() noexcept
		{
			return score(LOSSVALUE, 0);
		}
		static constexpr auto maximum() noexcept
		{
			return score(MAXVALUE, 0);
		}
		static constexpr auto minimum() noexcept
		{
			return score(MINVALUE, 0);
		}
		constexpr score() noexcept = delete;
		constexpr bool isForced() const noexcept
		{
			return std::abs(m_Value) >= WINNINGVALUE;
		}
		constexpr bool isOpen() const noexcept
		{
			return  std::abs(m_Value) < WINNINGVALUE;
		}
		constexpr bool isWon() const noexcept
		{
			return std::max(m_Value) >= WINVALUE;
		}
		constexpr bool isLost() const noexcept
		{
			return std::max(m_Value) <= LOSSVALUE;
		}
		constexpr bool isPositiveInfinity() const noexcept
		{
			return std::max(m_Value) >= MAXVALUE;
		}
		constexpr bool isNegativeInfinity() const noexcept
		{
			return std::max(m_Value) <= MINVALUE;
		}
		constexpr bool operator==(const score& sc) const noexcept
		{
			return m_Value == sc.m_Value;
		}
		constexpr bool operator!=(const score& sc) const noexcept
		{
			return m_Value != sc.m_Value;
		}
		constexpr bool operator>(const score& sc) const noexcept
		{
			return m_Value > sc.m_Value;
		}
		constexpr bool operator<(const score& sc) const noexcept
		{
			return m_Value < sc.m_Value;
		}
		constexpr bool operator>=(const score& sc) const noexcept
		{
			return m_Value >= sc.m_Value;
		}
		constexpr bool operator<=(const score& sc) const noexcept
		{
			return m_Value <= sc.m_Value;
		}
		constexpr auto operator+(const score& sc) const noexcept
		{
			assert(isOpen());
			assert(sc.isOpen());
			return score(m_Value + sc.m_Value, 0);
		}
		constexpr auto operator-(const score& sc) const noexcept
		{
			assert(isOpen());
			assert(sc.isOpen());
			return score(m_Value - sc.m_Value, 0);
		}
		constexpr auto operator-() const noexcept
		{
			return score(-m_Value, 0);
		}
		constexpr auto operator*(const valueType i) const noexcept
		{
			assert(isOpen());
			return score(static_cast<valueType>(m_Value * i), 0);
		}
		constexpr auto operator*(const score& sc) const noexcept
		{
			assert(isOpen());
			return score(static_cast<valueType>((static_cast<longType>(m_Value) * static_cast<longType>(sc.m_Value)) >> SHIFT), 0);
		}
		constexpr auto operator+=(const score& sc) noexcept
		{
			assert(isOpen());
			assert(sc.isOpen());
			m_Value += sc.m_Value;
		}
		constexpr auto operator-=(const score& sc) noexcept
		{
			assert(isOpen());
			assert(sc.isOpen());
			m_Value -= sc.m_Value;
		}
		constexpr auto operator*=(const score& sc) noexcept
		{
			assert(isOpen());
			assert(sc.isOpen());
			m_Value = static_cast<valueType>((static_cast<longType>(m_Value) * static_cast<longType>(sc.m_Value)) >> SHIFT);
		}
		constexpr auto operator*=(const valueType i) noexcept
		{
			assert(isOpen());
			m_Value *= i;
		}
		constexpr auto plyUp() const noexcept
		{
			return score(m_Value + ((m_Value < LOSINGVALUE) & (m_Value > MINVALUE)) - ((m_Value > WINNINGVALUE) & (m_Value < MINVALUE)), 0);
		}
		constexpr auto plyDown() const noexcept
		{
			return score(m_Value - ((m_Value < LOSINGVALUE) & (m_Value > MINVALUE)) + ((m_Value > WINNINGVALUE) & (m_Value < MINVALUE)), 0);
		}
	};

	template<size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
	constexpr auto operator*(const typename score<MANTISSA, SHIFT, MAXDIST>::valueType i, const score<MANTISSA, SHIFT, MAXDIST>& sc)
	{
		return sc * i;
	}
}