namespace pygmalion
{
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
		static auto populationCount(const UTYPE value) noexcept
		{
			return pygmalion::bitmanip::populationCount8(value);
		}
		static auto bitScanForward(const UTYPE bb, int& idx) noexcept
		{
			return pygmalion::bitmanip::bitScanForward8(bb, idx);
		}
		static auto bitScanReverse(const UTYPE bb, int& idx) noexcept
		{
			return pygmalion::bitmanip::bitScanReverse8(bb, idx);
		}
		static auto pext(const UTYPE val, const UTYPE mask) noexcept
		{
			return pygmalion::bitmanip::pext8(val, mask);
		}
		static auto pdep(const UTYPE val, const UTYPE mask) noexcept
		{
			return pygmalion::bitmanip::pdep8(val, mask);
		}
		constexpr static auto setMask(const int idx) noexcept
		{
			return pygmalion::bitmanip::setMask8(idx);
		}
		constexpr static auto resetMask(const int idx) noexcept
		{
			return pygmalion::bitmanip::resetMask8(idx);
		}
		constexpr static auto checkBit(const UTYPE bb, const int idx) noexcept
		{
			return pygmalion::bitmanip::checkBit8(bb, idx);
		}
		constexpr static void setBit(UTYPE& bb, const int idx) noexcept
		{
			pygmalion::bitmanip::setBit8(bb, idx);
		}
		constexpr static void clearBit(UTYPE& bb, const int idx) noexcept
		{
			pygmalion::bitmanip::clearBit8(bb, idx);
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
				ru |= static_cast<UTYPE>(std::rand() & 0xFF) << (k * sizeof(UTYPE));
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
		static auto populationCount(const UTYPE value) noexcept
		{
			return pygmalion::bitmanip::populationCount16(value);
		}
		static auto bitScanForward(const UTYPE bb, int& idx) noexcept
		{
			return pygmalion::bitmanip::bitScanForward16(bb, idx);
		}
		static auto bitScanReverse(const UTYPE bb, int& idx) noexcept
		{
			return pygmalion::bitmanip::bitScanReverse16(bb, idx);
		}
		static auto pext(const UTYPE val, const UTYPE mask) noexcept
		{
			return pygmalion::bitmanip::pext16(val, mask);
		}
		static auto pdep(const UTYPE val, const UTYPE mask) noexcept
		{
			return pygmalion::bitmanip::pdep16(val, mask);
		}
		constexpr static auto setMask(const int idx) noexcept
		{
			return pygmalion::bitmanip::setMask16(idx);
		}
		constexpr static auto resetMask(const int idx) noexcept
		{
			return pygmalion::bitmanip::resetMask16(idx);
		}
		constexpr static auto checkBit(const UTYPE bb, const int idx) noexcept
		{
			return pygmalion::bitmanip::checkBit16(bb, idx);
		}
		constexpr static void setBit(UTYPE& bb, const int idx) noexcept
		{
			pygmalion::bitmanip::setBit16(bb, idx);
		}
		constexpr static void clearBit(UTYPE& bb, const int idx) noexcept
		{
			pygmalion::bitmanip::clearBit16(bb, idx);
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
				ru |= static_cast<UTYPE>(std::rand() & 0xFF) << (k * sizeof(UTYPE));
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
		static auto populationCount(const UTYPE value) noexcept
		{
			return pygmalion::bitmanip::populationCount32(value);
		}
		static auto bitScanForward(const UTYPE bb, int& idx) noexcept
		{
			return pygmalion::bitmanip::bitScanForward32(bb, idx);
		}
		static auto bitScanReverse(const UTYPE bb, int& idx) noexcept
		{
			return pygmalion::bitmanip::bitScanReverse32(bb, idx);
		}
		static auto pext(const UTYPE val, const UTYPE mask) noexcept
		{
			return pygmalion::bitmanip::pext32(val, mask);
		}
		static auto pdep(const UTYPE val, const UTYPE mask) noexcept
		{
			return pygmalion::bitmanip::pdep32(val, mask);
		}
		constexpr static auto setMask(const int idx) noexcept
		{
			return pygmalion::bitmanip::setMask32(idx);
		}
		constexpr static auto resetMask(const int idx) noexcept
		{
			return pygmalion::bitmanip::resetMask32(idx);
		}
		constexpr static auto checkBit(const UTYPE bb, const int idx) noexcept
		{
			return pygmalion::bitmanip::checkBit32(bb, idx);
		}
		constexpr static void setBit(UTYPE& bb, const int idx) noexcept
		{
			pygmalion::bitmanip::setBit32(bb, idx);
		}
		constexpr static void clearBit(UTYPE& bb, const int idx) noexcept
		{
			pygmalion::bitmanip::clearBit32(bb, idx);
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
				ru |= static_cast<UTYPE>(std::rand() & 0xFF) << (k * sizeof(UTYPE));
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
		static auto populationCount(const UTYPE value) noexcept
		{
			return pygmalion::bitmanip::populationCount64(value);
		}
		static auto bitScanForward(const UTYPE bb, int& idx) noexcept
		{
			return pygmalion::bitmanip::bitScanForward64(bb, idx);
		}
		static auto bitScanReverse(const UTYPE bb, int& idx) noexcept
		{
			return pygmalion::bitmanip::bitScanReverse64(bb, idx);
		}
		static auto pext(const UTYPE val, const UTYPE mask) noexcept
		{
			return pygmalion::bitmanip::pext64(val, mask);
		}
		static auto pdep(const UTYPE val, const UTYPE mask) noexcept
		{
			return pygmalion::bitmanip::pdep64(val, mask);
		}
		constexpr static auto setMask(const int idx) noexcept
		{
			return pygmalion::bitmanip::setMask64(idx);
		}
		constexpr static auto resetMask(const int idx) noexcept
		{
			return pygmalion::bitmanip::resetMask64(idx);
		}
		constexpr static auto checkBit(const UTYPE bb, const int idx) noexcept
		{
			return pygmalion::bitmanip::checkBit64(bb, idx);
		}
		constexpr static void setBit(UTYPE& bb, const int idx) noexcept
		{
			pygmalion::bitmanip::setBit64(bb, idx);
		}
		constexpr static void clearBit(UTYPE& bb, const int idx) noexcept
		{
			pygmalion::bitmanip::clearBit64(bb, idx);
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
				ru |= static_cast<UTYPE>(std::rand() & 0xFF) << (k * sizeof(UTYPE));
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
		if (sizeof(size_t) > 4)
		{
			if (number >= (size_t(1) << 31))
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
		if (sizeof(size_t) > 4)
		{
			if (number >= (std::uint64_t(1) << 32))
				return 8;
		}
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

	namespace detail {

		template<std::size_t size, typename T, std::size_t... indexes>
		constexpr auto make_array_n_impl(T&& value, std::index_sequence<indexes...>) noexcept
		{
			// Use the comma operator to expand the variadic pack
			// Move the last element in if possible. Order of evaluation is well-defined
			// for aggregate initialization, so there is no risk of copy-after-move
			return std::array<std::decay_t<T>, size>{ (static_cast<void>(indexes), value)..., std::forward<T>(value) };
		}

	}   // namespace detail

	template<typename T>
	constexpr auto make_array_n(std::integral_constant<std::size_t, 0>, T&&) noexcept
	{
		return std::array<std::decay_t<T>, 0>{};
	}

	template<std::size_t size, typename T>
	constexpr auto make_array_n(std::integral_constant<std::size_t, size>, T&& value) noexcept
	{
		return detail::make_array_n_impl<size>(std::forward<T>(value), std::make_index_sequence<size - 1>{});
	}

	template<std::size_t size, typename T>
	constexpr auto make_array_n(T&& value) noexcept
	{
		return make_array_n(std::integral_constant<std::size_t, size>{}, std::forward<T>(value));
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

}