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

	template<int MANTISSA, int SHIFT, int MAXDIST>
	class score
	{
	public:
		using valueType = typename int_traits < requiredSignedBytes((std::uint64_t(1) << MANTISSA) - 1) > ::STYPE;
		constexpr static int countMantissaBits{ MANTISSA };
		constexpr static int countShiftBits{ SHIFT };
		constexpr static valueType granularity{ size_t(1) << countShiftBits };
		constexpr static int maxDistance{ MAXDIST };
	private:
		using longType = typename int_traits < requiredSignedBytes((std::uint64_t(1) << MANTISSA)) > ::STYPE;
		static constexpr valueType MAXVALUE{ valueType((longType(1) << MANTISSA) - 1) };
		static constexpr valueType MINVALUE{ valueType(-MAXVALUE) };
		static constexpr valueType WINVALUE{ valueType(MAXVALUE - 1) };
		static constexpr valueType LOSSVALUE{ valueType(MINVALUE + 1) };
		static constexpr valueType WINNINGVALUE{ valueType(MAXVALUE - 1 - MAXDIST) };
		static constexpr valueType LOSINGVALUE{ valueType(MINVALUE + 1 + MAXDIST) };
		valueType m_Value;
		constexpr score(const valueType value, const int) noexcept :
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
				const double flt = static_cast<double>(m_Value) / static_cast<double>(valueType(1) << SHIFT);
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
				size_t range = isPositive() ? winDistance(m_Value) : lossDistance(m_Value);
				sstr << (m_Value >= 0 ? "+" : "-");
				sstr << "M";
				sstr << range;
			}
			return sstr.str();
		}
		constexpr bool isPositive() const noexcept
		{
			return m_Value > 0;
		}
		constexpr bool isNegative() const noexcept
		{
			return m_Value < 0;
		}
		static constexpr score win(const valueType distance) noexcept
		{
			return score(WINVALUE - distance, 0);
		}
		static constexpr score loss(const valueType distance) noexcept
		{
			return score(LOSSVALUE + distance, 0);
		}
		constexpr valueType winDistance(const valueType value) const noexcept
		{
			assert(isWinning());
			return WINVALUE - m_Value;
		}
		constexpr valueType lossDistance(const valueType value) const noexcept
		{
			assert(isLosing());
			return m_Value - LOSSVALUE;
		}
		~score() = default;
		template<int otherMantissa, int otherShift, int otherMaxDistance>
		explicit constexpr score(const score<otherMantissa, otherShift, otherMaxDistance> other) noexcept :
			m_Value{ 0 }
		{
			if (other.isWinning())
			{
				const auto otherDistance{ other.winDistance() };
				m_Value = WINVALUE - ((otherDistance > maxDistance) ? maxDistance : otherDistance);
			}
			else if (other.isLosing())
			{
				const auto otherDistance{ other.lossDistance() };
				m_Value = LOSSVALUE + ((otherDistance > maxDistance) ? maxDistance : otherDistance);
			}
			else
			{
				constexpr const bool useOtherMantissa{ otherMantissa > countMantissaBits };
				using combinedType = typename  int_traits<requiredSignedBytes((std::uint64_t(1) << countMantissaBits) - 1)>::STYPE;
				constexpr const bool shiftRight{ otherShift > countShiftBits };
				if (shiftRight)
				{
					constexpr const int shift{ otherShift - countShiftBits };
					m_Value = static_cast<combinedType>(other.m_Value) / static_cast<combinedType>(granularity);
				}
				else
				{
					constexpr const int shift{ countShiftBits - otherShift };
					m_Value = static_cast<combinedType>(other.m_Value) * static_cast<combinedType>(granularity);
				}
			}
		}
		explicit constexpr score(const double value) noexcept :
			m_Value(static_cast<valueType>(value* static_cast<double>(granularity)))
		{

		}
		explicit constexpr score(const valueType value) noexcept :
			m_Value(static_cast<valueType>(value* granularity))
		{

		}
		explicit constexpr operator valueType() const noexcept
		{
			assert(isOpen());
			return static_cast<valueType>(m_Value / granularity);
		}
		explicit constexpr operator double() const noexcept
		{
			assert(isOpen());
			return static_cast<double>(m_Value) / static_cast<double>(granularity);
		}
		explicit constexpr score(const float value) noexcept :
			score(static_cast<double>(value))
		{

		}
		explicit constexpr operator float() const noexcept
		{
			assert(isOpen());
			return static_cast<float>(m_Value) / static_cast<float>(granularity);
		}
		constexpr score(score&&) noexcept = default;
		constexpr score(const score&) noexcept = default;
		constexpr score& operator=(score&&) noexcept = default;
		constexpr score& operator=(const score&)  noexcept = default;
		static constexpr score atom() noexcept
		{
			return score(1, 0);
		};
		static constexpr score one() noexcept
		{
			return score(granularity, 0);
		};
		static constexpr score zero() noexcept
		{
			return score(0, 0);
		}
		static constexpr score win() noexcept
		{
			return win(0);
		}
		static constexpr score winning() noexcept
		{
			return score(WINNINGVALUE, 0);
		}
		static constexpr score losing() noexcept
		{
			return score(LOSINGVALUE, 0);
		}
		static constexpr score loss() noexcept
		{
			return loss(0);
		}
		static constexpr score maximum() noexcept
		{
			return score(MAXVALUE, 0);
		}
		static constexpr score minimum() noexcept
		{
			return score(MINVALUE, 0);
		}
		constexpr score() noexcept :
			score(0, 0)
		{

		}
		constexpr bool isLosing() const noexcept
		{
			return m_Value <= LOSINGVALUE;
		}
		constexpr bool isWinning() const noexcept
		{
			return m_Value >= WINNINGVALUE;
		}
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
		constexpr bool operator==(const score sc) const noexcept
		{
			return m_Value == sc.m_Value;
		}
		constexpr bool operator!=(const score sc) const noexcept
		{
			return m_Value != sc.m_Value;
		}
		constexpr bool operator>(const score sc) const noexcept
		{
			return m_Value > sc.m_Value;
		}
		constexpr bool operator<(const score sc) const noexcept
		{
			return m_Value < sc.m_Value;
		}
		constexpr bool operator>=(const score sc) const noexcept
		{
			return m_Value >= sc.m_Value;
		}
		constexpr bool operator<=(const score sc) const noexcept
		{
			return m_Value <= sc.m_Value;
		}
		constexpr auto operator+(const score sc) const noexcept
		{
			assert(isOpen());
			assert(sc.isOpen());
			return score(m_Value + sc.m_Value, 0);
		}
		constexpr auto operator-(const score sc) const noexcept
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
		constexpr auto operator*(const score sc) const noexcept
		{
			assert(isOpen());
			return score(static_cast<valueType>((static_cast<longType>(m_Value) * static_cast<longType>(sc.m_Value)) / granularity), 0);
		}
		constexpr auto operator+=(const score sc) noexcept
		{
			assert(isOpen());
			assert(sc.isOpen());
			m_Value += sc.m_Value;
		}
		constexpr auto operator-=(const score sc) noexcept
		{
			assert(isOpen());
			assert(sc.isOpen());
			m_Value -= sc.m_Value;
		}
		constexpr auto operator*=(const score sc) noexcept
		{
			assert(isOpen());
			assert(sc.isOpen());
			m_Value = static_cast<valueType>((static_cast<longType>(m_Value) * static_cast<longType>(sc.m_Value)) / granularity);
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

	template<int MANTISSA, int SHIFT, int MAXDIST>
	constexpr auto operator*(const typename score<MANTISSA, SHIFT, MAXDIST>::valueType i, const score<MANTISSA, SHIFT, MAXDIST>& sc)
	{
		return sc * i;
	}
}