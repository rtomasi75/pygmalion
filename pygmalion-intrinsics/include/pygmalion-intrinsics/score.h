namespace pygmalion
{
	namespace detail
	{
		template<size_t BYTECOUNT>
		struct score_traits
		{
		};
		template<>
		struct score_traits<1>
		{
		public:
			using STYPE = std::int8_t;
			using SLONG = std::int16_t;
		};

		template<>
		struct score_traits<2>
		{
		public:
			using STYPE = std::int16_t;
			using SLONG = std::int32_t;
		};

		template<>
		struct score_traits<4>
		{
		public:
			using STYPE = std::int32_t;
			using SLONG = std::int64_t;
		};

		template<>
		struct score_traits<8>
		{
		public:
			using STYPE = std::int64_t;
			using SLONG = std::intmax_t;
		};
	}
	template<size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
	class score
	{
	private:
		constexpr static size_t requiredSignedBytes(const std::uintmax_t number) noexcept
		{
			if (number >= (UINTMAX_C(1) << 31))
				return 8;
			if (number >= (UINTMAX_C(1) << 15))
				return 4;
			if (number >= (UINTMAX_C(1) << 7))
				return 2;
			return 1;
		}
	public:
		using valueType = typename detail::score_traits < requiredSignedBytes((std::uintmax_t(1) << MANTISSA) - 1) > ::STYPE;
		constexpr static size_t countMantissaBits{ MANTISSA };
		constexpr static size_t countShiftBits{ SHIFT };
		constexpr static valueType granularity{ static_cast<valueType>(UINTMAX_C(1) << countShiftBits) };
		constexpr static size_t maxDistance{ MAXDIST };
	private:
		using longType = typename detail::score_traits < requiredSignedBytes((UINTMAX_C(1) << MANTISSA)) > ::STYPE;
	public:
		static constexpr valueType MAXVALUE{ valueType((longType(1) << MANTISSA) - 1) };
		static constexpr valueType MINVALUE{ valueType(-MAXVALUE) };
		static constexpr valueType WINVALUE{ valueType(MAXVALUE - 1) };
		static constexpr valueType LOSSVALUE{ valueType(MINVALUE + 1) };
		static constexpr valueType WINNINGVALUE{ valueType(MAXVALUE - 1 - MAXDIST) };
		static constexpr valueType LOSINGVALUE{ valueType(MINVALUE + 1 + MAXDIST) };
	private:
		valueType m_Value;
		constexpr score(const valueType& value, const int) noexcept :
			m_Value(value)
		{

		}
	public:
		PYGMALION_INLINE constexpr static score quota(const std::uintmax_t dividend, const std::uintmax_t divisor) noexcept
		{
			return score(static_cast<valueType>((dividend << countShiftBits) / divisor), 0);
		}
		PYGMALION_INLINE constexpr valueType get_Value() const noexcept
		{
			return m_Value;
		}
		explicit operator std::string() const noexcept
		{
			return toString();
		}
		PYGMALION_INLINE constexpr bool isPositive() const noexcept
		{
			return m_Value > 0;
		}
		PYGMALION_INLINE constexpr bool isNegative() const noexcept
		{
			return m_Value < 0;
		}
		PYGMALION_INLINE static constexpr score distantWin(const valueType& distance) noexcept
		{
			return score(WINVALUE - distance, 0);
		}
		PYGMALION_INLINE static constexpr score distantLoss(const valueType& distance) noexcept
		{
			return score(LOSSVALUE + distance, 0);
		}
		PYGMALION_INLINE constexpr valueType winDistance() const noexcept
		{
			return WINVALUE - m_Value;
		}
		PYGMALION_INLINE constexpr valueType lossDistance() const noexcept
		{
			return m_Value - LOSSVALUE;
		}
		PYGMALION_INLINE ~score() = default;
		template<size_t otherMantissa, size_t otherShift, size_t otherMaxDistance>
		PYGMALION_INLINE explicit constexpr score(const score<otherMantissa, otherShift, otherMaxDistance> other) noexcept :
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
				using combinedType = typename  detail::score_traits < requiredSignedBytes(std::uint64_t(1) << (std::max(countMantissaBits, otherMantissa) - 1)) > ::STYPE;
				constexpr const bool shiftRight{ otherShift > countShiftBits };
				if (shiftRight)
				{
					constexpr const size_t shift{ otherShift - countShiftBits };
					combinedType value{ static_cast<combinedType>(other.get_Value()) };
					value >>= shift;
					m_Value = static_cast<valueType>(value);
				}
				else
				{
					constexpr const size_t shift{ countShiftBits - otherShift };
					combinedType value{ static_cast<combinedType>(other.get_Value()) };
					value <<= shift;
					m_Value = static_cast<valueType>(value);
				}
			}
		}
		PYGMALION_INLINE explicit constexpr score(const double value) noexcept :
			m_Value(static_cast<valueType>(value* static_cast<double>(granularity)))
		{

		}
		PYGMALION_INLINE explicit constexpr score(const valueType& value) noexcept :
			m_Value(static_cast<valueType>(value* granularity))
		{

		}
		PYGMALION_INLINE explicit constexpr operator valueType() const noexcept
		{
			return static_cast<valueType>(m_Value / granularity);
		}
		PYGMALION_INLINE explicit constexpr operator double() const noexcept
		{
			return static_cast<double>(m_Value) / static_cast<double>(granularity);
		}
		PYGMALION_INLINE explicit constexpr score(const float value) noexcept :
			score(static_cast<double>(value))
		{

		}
		PYGMALION_INLINE explicit constexpr operator float() const noexcept
		{
			return static_cast<float>(m_Value) / static_cast<float>(granularity);
		}
		PYGMALION_INLINE constexpr score(score&&) noexcept = default;
		PYGMALION_INLINE constexpr score(const score&) noexcept = default;
		PYGMALION_INLINE constexpr score& operator=(score&&) noexcept = default;
		PYGMALION_INLINE constexpr score& operator=(const score&) noexcept = default;
		constexpr static score max(const score sc1, const score sc2) noexcept
		{
			//return score(sc1.m_Value > sc2.m_Value ? sc1.m_Value : sc2.m_Value, 0);
			//return score(sc1.m_Value ^ ((sc1.m_Value ^ sc2.m_Value) & -(sc1.m_Value < sc2.m_Value)), 0);
			return score(std::max(sc1.m_Value, sc2.m_Value), 0);
		}
		constexpr static score min(const score sc1, const score sc2) noexcept
		{
			//return score(sc1.m_Value < sc2.m_Value ? sc1.m_Value : sc2.m_Value, 0);
			//return score(sc1.m_Value ^ ((sc2.m_Value ^ sc1.m_Value) & -(sc2.m_Value < sc1.m_Value)), 0);
			return score(std::min(sc1.m_Value, sc2.m_Value), 0);
		}
		constexpr static score atom() noexcept
		{
			return score(1, 0);
		};
		constexpr static score one() noexcept
		{
			return score(granularity, 0);
		};
		constexpr static score zero() noexcept
		{
			return score(0, 0);
		}
		constexpr static score win() noexcept
		{
			return distantWin(0);
		}
		constexpr static score winning() noexcept
		{
			return score(WINNINGVALUE, 0);
		}
		constexpr static score losing() noexcept
		{
			return score(LOSINGVALUE, 0);
		}
		constexpr static score loss() noexcept
		{
			return distantLoss(0);
		}
		constexpr static score maximum() noexcept
		{
			return score(MAXVALUE, 0);
		}
		constexpr static score minimum() noexcept
		{
			return score(MINVALUE, 0);
		}
		PYGMALION_INLINE constexpr score() noexcept :
			score(0, 0)
		{

		}
		PYGMALION_INLINE constexpr score zeroWindow() const noexcept
		{
			return score(m_Value - 1, 0);
		}
		PYGMALION_INLINE constexpr bool isLosing() const noexcept
		{
			return m_Value <= LOSINGVALUE;
		}
		PYGMALION_INLINE constexpr bool isWinning() const noexcept
		{
			return m_Value >= WINNINGVALUE;
		}
		PYGMALION_INLINE constexpr bool isForced() const noexcept
		{
			return std::abs(m_Value) >= WINNINGVALUE;
		}
		PYGMALION_INLINE constexpr bool isOpen() const noexcept
		{
			return std::abs(m_Value) < WINNINGVALUE;
		}
		PYGMALION_INLINE constexpr bool isWon() const noexcept
		{
			return std::max(m_Value) >= WINVALUE;
		}
		PYGMALION_INLINE constexpr bool isLost() const noexcept
		{
			return std::max(m_Value) <= LOSSVALUE;
		}
		PYGMALION_INLINE constexpr bool isPositiveInfinity() const noexcept
		{
			return std::max(m_Value) >= MAXVALUE;
		}
		PYGMALION_INLINE constexpr bool isNegativeInfinity() const noexcept
		{
			return std::max(m_Value) <= MINVALUE;
		}
		PYGMALION_INLINE constexpr bool operator==(const score sc) const noexcept
		{
			return m_Value == sc.m_Value;
		}
		PYGMALION_INLINE constexpr bool operator!=(const score sc) const noexcept
		{
			return m_Value != sc.m_Value;
		}
		PYGMALION_INLINE constexpr bool operator>(const score sc) const noexcept
		{
			return m_Value > sc.m_Value;
		}
		PYGMALION_INLINE constexpr bool operator<(const score sc) const noexcept
		{
			return m_Value < sc.m_Value;
		}
		PYGMALION_INLINE constexpr bool operator>=(const score sc) const noexcept
		{
			return m_Value >= sc.m_Value;
		}
		PYGMALION_INLINE constexpr bool operator<=(const score sc) const noexcept
		{
			return m_Value <= sc.m_Value;
		}
		PYGMALION_INLINE constexpr auto operator+(const score sc) const noexcept
		{
			return score(m_Value + sc.m_Value, 0);
		}
		PYGMALION_INLINE constexpr auto operator-(const score sc) const noexcept
		{
			return score(m_Value - sc.m_Value, 0);
		}
		PYGMALION_INLINE constexpr auto operator-() const noexcept
		{
			return score(-m_Value, 0);
		}
		PYGMALION_INLINE constexpr auto operator*(const valueType& i) const noexcept
		{
			return score(static_cast<valueType>(m_Value * i), 0);
		}
		PYGMALION_INLINE constexpr auto operator/(const valueType& i) const noexcept
		{
			return score(static_cast<valueType>(m_Value / i), 0);
		}
		PYGMALION_INLINE constexpr auto operator*(const score sc) const noexcept
		{
			return score(static_cast<valueType>((static_cast<longType>(m_Value) * static_cast<longType>(sc.m_Value)) / granularity), 0);
		}
		PYGMALION_INLINE constexpr auto operator+=(const score sc) noexcept
		{
			m_Value += sc.m_Value;
		}
		PYGMALION_INLINE constexpr auto operator-=(const score sc) noexcept
		{
			m_Value -= sc.m_Value;
		}
		PYGMALION_INLINE constexpr auto operator*=(const score sc) noexcept
		{
			m_Value = static_cast<valueType>((static_cast<longType>(m_Value) * static_cast<longType>(sc.m_Value)) / granularity);
		}
		PYGMALION_INLINE constexpr auto operator*=(const valueType& i) noexcept
		{
			m_Value *= i;
		}
		PYGMALION_INLINE constexpr auto operator/=(const valueType& i) noexcept
		{
			m_Value /= i;
		}
		PYGMALION_INLINE constexpr auto plyUp() const noexcept
		{
			return score(m_Value + ((m_Value < LOSINGVALUE) & (m_Value > MINVALUE)) - ((m_Value > WINNINGVALUE) & (m_Value < MAXVALUE)), 0);
		}
		PYGMALION_INLINE constexpr auto plyDown() const noexcept
		{
			return score(m_Value - ((m_Value < LOSINGVALUE) & (m_Value > (MINVALUE + 1))) + ((m_Value > WINNINGVALUE) & (m_Value < (MAXVALUE - 1))), 0);
		}
		std::string toString() const noexcept
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
				size_t range = isPositive() ? winDistance() : lossDistance();
				sstr << (m_Value >= 0 ? "+" : "-");
				sstr << "M";
				sstr << range;
			}
			return sstr.str();
		}
	};

	template<size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
	constexpr auto operator*(const typename score<MANTISSA, SHIFT, MAXDIST>::valueType i, const score<MANTISSA, SHIFT, MAXDIST>& sc)
	{
		return sc * i;
	}

	template<size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
	std::ostream& operator<<(std::ostream& str, const score<MANTISSA, SHIFT, MAXDIST>& value) noexcept
	{
		str << value.toString();
		return str;
	}
}