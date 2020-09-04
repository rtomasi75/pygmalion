template<size_t BYTECOUNT>
struct int_traits
{
};
template<>
struct int_traits<1>
{
public:
	using STYPE = std::int8_t;
	using SLONG = std::int16_t;
	using UTYPE = std::uint8_t;
	static int populationCount(const UTYPE value) noexcept
	{
		return bitmanip::populationCount8(value);
	}
	static auto bitScanForward(const UTYPE bb, int& idx) noexcept
	{
		return bitmanip::bitScanForward8(bb, idx);
	}
	static auto bitScanReverse(const UTYPE bb, int& idx) noexcept
	{
		return bitmanip::bitScanReverse8(bb, idx);
	}
	static auto pext(const UTYPE val, const UTYPE mask) noexcept
	{
		return bitmanip::pext8(val, mask);
	}
	static auto pdep(const UTYPE val, const UTYPE mask) noexcept
	{
		return bitmanip::pdep8(val, mask);
	}
	constexpr static auto setMask(const int idx) noexcept
	{
		return bitmanip::setMask8(idx);
	}
	constexpr static auto clearMask(const int idx) noexcept
	{
		return bitmanip::clearMask8(idx);
	}
	constexpr static auto checkBit(const UTYPE bb, const int idx) noexcept
	{
		return bitmanip::checkBit8(bb, idx);
	}
	constexpr static void setBit(UTYPE& bb, const int idx) noexcept
	{
		bitmanip::setBit8(bb, idx);
	}
	constexpr static void clearBit(UTYPE& bb, const int idx) noexcept
	{
		bitmanip::clearBit8(bb, idx);
	}
	constexpr static UTYPE invertBits(const UTYPE bb) noexcept
	{
		return ~bb;
	}
	static UTYPE rand() noexcept
	{
		UTYPE ru{ 0 };
		for (int k = 0; k < sizeof(UTYPE); k++)
		{
			ru |= static_cast<UTYPE>(std::rand() & 0xFF) << k;
		}
		return ru;
	}
	static UTYPE rand_sparse() noexcept
	{
		return rand() & rand() & rand();
	}
};
template<>
struct int_traits<2>
{
private:
public:
	using STYPE = std::int16_t;
	using SLONG = std::int32_t;
	using UTYPE = std::uint16_t;
	static int populationCount(const UTYPE value) noexcept
	{
		return bitmanip::populationCount16(value);
	}
	static auto bitScanForward(const UTYPE bb, int& idx) noexcept
	{
		return bitmanip::bitScanForward16(bb, idx);
	}
	static auto bitScanReverse(const UTYPE bb, int& idx) noexcept
	{
		return bitmanip::bitScanReverse16(bb, idx);
	}
	static auto pext(const UTYPE val, const UTYPE mask) noexcept
	{
		return bitmanip::pext16(val, mask);
	}
	static auto pdep(const UTYPE val, const UTYPE mask) noexcept
	{
		return bitmanip::pdep16(val, mask);
	}
	constexpr static auto setMask(const int idx) noexcept
	{
		return bitmanip::setMask16(idx);
	}
	constexpr static auto clearMask(const int idx) noexcept
	{
		return bitmanip::clearMask16(idx);
	}
	constexpr static auto checkBit(const UTYPE bb, const int idx) noexcept
	{
		return bitmanip::checkBit16(bb, idx);
	}
	constexpr static void setBit(UTYPE& bb, const int idx) noexcept
	{
		bitmanip::setBit16(bb, idx);
	}
	constexpr static void clearBit(UTYPE& bb, const int idx) noexcept
	{
		bitmanip::clearBit16(bb, idx);
	}
	constexpr static UTYPE invertBits(const UTYPE bb) noexcept
	{
		return ~bb;
	}
	static UTYPE rand() noexcept
	{
		UTYPE ru{ 0 };
		for (int k = 0; k < sizeof(UTYPE); k++)
		{
			ru |= static_cast<UTYPE>(std::rand() & 0xFF) << k;
		}
		return ru;
	}
	static UTYPE rand_sparse() noexcept
	{
		return rand() & rand() & rand();
	}
};
template<>
struct int_traits<4>
{
public:
	using STYPE = std::int32_t;
	using SLONG = std::int64_t;
	using UTYPE = std::uint32_t;
	static UTYPE bits_not(const UTYPE value) noexcept
	{
		return ~value;
	}
	static int populationCount(const UTYPE value) noexcept
	{
		return bitmanip::populationCount32(value);
	}
	static auto bitScanForward(const UTYPE bb, int& idx) noexcept
	{
		return bitmanip::bitScanForward32(bb, idx);
	}
	static auto bitScanReverse(const UTYPE bb, int& idx) noexcept
	{
		return bitmanip::bitScanReverse32(bb, idx);
	}
	static auto pext(const UTYPE val, const UTYPE mask) noexcept
	{
		return bitmanip::pext32(val, mask);
	}
	static auto pdep(const UTYPE val, const UTYPE mask) noexcept
	{
		return bitmanip::pdep32(val, mask);
	}
	constexpr static auto setMask(const int idx) noexcept
	{
		return bitmanip::setMask32(idx);
	}
	constexpr static auto clearMask(const int idx) noexcept
	{
		return bitmanip::clearMask32(idx);
	}
	constexpr static auto checkBit(const UTYPE bb, const int idx) noexcept
	{
		return bitmanip::checkBit32(bb, idx);
	}
	constexpr static void setBit(UTYPE& bb, const int idx) noexcept
	{
		bitmanip::setBit32(bb, idx);
	}
	constexpr static void clearBit(UTYPE& bb, const int idx) noexcept
	{
		bitmanip::clearBit32(bb, idx);
	}
	constexpr static UTYPE invertBits(const UTYPE bb) noexcept
	{
		return ~bb;
	}
	static UTYPE rand() noexcept
	{
		UTYPE ru{ 0 };
		for (int k = 0; k < sizeof(UTYPE); k++)
		{
			ru |= static_cast<UTYPE>(std::rand() & 0xFF) << k;
		}
		return ru;
	}
	static UTYPE rand_sparse() noexcept
	{
		return rand() & rand() & rand();
	}
};
template<>
struct int_traits<8>
{
public:
	using STYPE = std::int64_t;
	using SLONG = std::int64_t;
	using UTYPE = std::uint64_t;
	static UTYPE bits_and(const UTYPE value1, const UTYPE value2) noexcept
	{
		return value1 & value2;
	}
	static UTYPE bits_or(const UTYPE value1, const UTYPE value2) noexcept
	{
		return value1 | value2;
	}
	static UTYPE bits_xor(const UTYPE value1, const UTYPE value2) noexcept
	{
		return value1 ^ value2;
	}
	static UTYPE bits_not(const UTYPE value) noexcept
	{
		return ~value;
	}
	static int populationCount(const UTYPE value) noexcept
	{
		return bitmanip::populationCount64(value);
	}
	static auto bitScanForward(const UTYPE bb, int& idx) noexcept
	{
		return bitmanip::bitScanForward64(bb, idx);
	}
	static auto bitScanReverse(const UTYPE bb, int& idx) noexcept
	{
		return bitmanip::bitScanReverse64(bb, idx);
	}
	static auto pext(const UTYPE val, const UTYPE mask) noexcept
	{
		return bitmanip::pext64(val, mask);
	}
	static auto pdep(const UTYPE val, const UTYPE mask) noexcept
	{
		return bitmanip::pdep64(val, mask);
	}
	constexpr static auto setMask(const int idx) noexcept
	{
		return bitmanip::setMask64(idx);
	}
	constexpr static auto clearMask(const int idx) noexcept
	{
		return bitmanip::clearMask64(idx);
	}
	constexpr static auto checkBit(const UTYPE bb, const int idx) noexcept
	{
		return bitmanip::checkBit64(bb, idx);
	}
	constexpr static void setBit(UTYPE& bb, const int idx) noexcept
	{
		bitmanip::setBit64(bb, idx);
	}
	constexpr static void clearBit(UTYPE& bb, const int idx) noexcept
	{
		bitmanip::clearBit64(bb, idx);
	}
	constexpr static UTYPE invertBits(const UTYPE bb) noexcept
	{
		return ~bb;
	}
	static UTYPE rand() noexcept
	{
		UTYPE ru{ 0 };
		for (int k = 0; k < sizeof(UTYPE); k++)
		{
			ru |= static_cast<UTYPE>(std::rand() & 0xFF) << (8 * k);
		}
		return ru;
	}
	static UTYPE rand_sparse() noexcept
	{
		return rand() & rand() & rand();
	}
};

constexpr static size_t requiredSignedBytes(const size_t number) noexcept
{
	if (number >= (size_t(1) << 31))
	{
		assert(sizeof(size_t) > 4);
		return 8;
	}
	if (number >= (size_t(1) << 15))
		return 4;
	if (number >= (size_t(1) << 7))
		return 2;
	return 1;
}
constexpr static size_t requiredUnsignedBytes(const size_t number) noexcept
{
	if (static_cast<std::uint64_t>(number) >= (std::uint64_t(1) << 32))
		return 8;
	if (number >= (size_t(1) << 16))
		return 4;
	if (number >= (size_t(1) << 8))
		return 2;
	return 1;
}
constexpr static size_t requiredBitBytes(const size_t bits) noexcept
{
	if (bits > 32)
		return 8;
	if (bits > 16)
		return 4;
	if (bits > 8)
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


template<size_t BYTECOUNT, size_t BITCOUNT>
struct invertBits
{
	constexpr static typename int_traits<requiredBitBytes(BITCOUNT)>::UTYPE perform(const typename int_traits<requiredBitBytes(BITCOUNT)>::UTYPE bits)
	{
		return (~bits) & ((typename int_traits<requiredBitBytes(BITCOUNT)>::UTYPE(1) << BITCOUNT) - 1);
	}
};

template<>
struct invertBits<1, 8>
{
	constexpr static typename int_traits<1>::UTYPE perform(const typename int_traits<1>::UTYPE bits)
	{
		return ~bits;
	}
};

template<>
struct invertBits<2, 16>
{
	constexpr static typename int_traits<2>::UTYPE perform(const typename int_traits<2>::UTYPE bits)
	{
		return ~bits;
	}
};

template<>
struct invertBits<4, 32>
{
	constexpr static typename int_traits<4>::UTYPE perform(const typename int_traits<4>::UTYPE bits)
	{
		return ~bits;
	}
};

template<>
struct invertBits<8, 64>
{
	constexpr static typename int_traits<8>::UTYPE perform(const typename int_traits<8>::UTYPE bits)
	{
		return ~bits;
	}
};

template<size_t BYTECOUNT, size_t BITCOUNT>
struct multiplyBits
{
	constexpr static typename int_traits<requiredBitBytes(BITCOUNT)>::UTYPE perform(const typename int_traits<requiredBitBytes(BITCOUNT)>::UTYPE bits1, const typename int_traits<requiredBitBytes(BITCOUNT)>::UTYPE bits2)
	{
		return (bits1 * bits2) & ((typename int_traits<requiredBitBytes(BITCOUNT)>::UTYPE(1) << BITCOUNT) - 1);
	}
};

template<>
struct multiplyBits<1, 8>
{
	constexpr static typename int_traits<1>::UTYPE perform(const typename int_traits<1>::UTYPE bits1, const typename int_traits<1>::UTYPE bits2)
	{
		return bits1 * bits2;
	}
};

template<>
struct multiplyBits<2, 16>
{
	constexpr static typename int_traits<2>::UTYPE perform(const typename int_traits<2>::UTYPE bits1, const typename int_traits<2>::UTYPE bits2)
	{
		return bits1 * bits2;
	}
};

template<>
struct multiplyBits<4, 32>
{
	constexpr static typename int_traits<4>::UTYPE perform(const typename int_traits<4>::UTYPE bits1, const typename int_traits<4>::UTYPE bits2)
	{
		return bits1 * bits2;
	}
};

template<>
struct multiplyBits<8, 64>
{
	constexpr static typename int_traits<8>::UTYPE perform(const typename int_traits<8>::UTYPE bits1, const typename int_traits<8>::UTYPE bits2)
	{
		return bits1 * bits2;
	}
};

