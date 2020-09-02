namespace pygmalion
{
	template<int COUNT_BITS> class bitfield;

	template<int COUNT_BITS>
	class bit : public enumeration<COUNT_BITS, bit<COUNT_BITS>>
	{
	public:
		constexpr bit(const bit&) noexcept = default;
		constexpr bit(bit&&) noexcept = default;
		constexpr bit() noexcept :
			enumeration<COUNT_BITS, bit>()
		{

		}
		constexpr bit(const typename enumeration<COUNT_BITS, bit>::baseType value) noexcept :
			enumeration<COUNT_BITS, bit>(value)
		{
		}
		constexpr bit(const typename enumeration<COUNT_BITS, bit>::valueType value) noexcept :
			enumeration<COUNT_BITS, bit>(value)
		{
		}
		constexpr bit& operator=(bit&&) noexcept = default;
		constexpr bit& operator=(const bit&) noexcept = default;
		constexpr bitfield<COUNT_BITS> operator|(const bit other) const noexcept
		{
			return static_cast<bitfield<COUNT_BITS>>(*this) | static_cast<bitfield<COUNT_BITS>>(other);
		}
		constexpr bitfield<COUNT_BITS> operator&(const bit other) const noexcept
		{
			return static_cast<bitfield<COUNT_BITS>>(*this) & static_cast<bitfield<COUNT_BITS>>(other);
		}
		constexpr bitfield<COUNT_BITS> operator^(const bit other) const noexcept
		{
			return static_cast<bitfield<COUNT_BITS>>(*this) ^ static_cast<bitfield<COUNT_BITS>>(other);
		}
		constexpr bitfield<COUNT_BITS> operator~() const noexcept
		{
			return ~static_cast<bitfield<COUNT_BITS>>(*this);
		}
	};

}