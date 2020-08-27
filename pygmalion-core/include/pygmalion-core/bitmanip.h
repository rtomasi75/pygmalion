namespace pygmalion
{
#if defined(PYGMALION_INTRINSICS_GNU)
	struct clzll_tag {};
	struct clzl_tag : clzll_tag {};
	struct clz_tag : clzl_tag {};

	template <typename T, typename = typename std::enable_if<sizeof(T) <= sizeof(unsigned int)>::type>
	unsigned clz_impl(clz_tag, T x) noexcept
	{
		return __builtin_clz(x) - (sizeof(unsigned int) * CHAR_BIT - sizeof(T) * CHAR_BIT);
	}

	template <typename T, typename = typename std::enable_if<sizeof(T) <= sizeof(unsigned long)>::type>
	unsigned clz_impl(clzl_tag, T x) noexcept
	{
		return __builtin_clzl(x) - (sizeof(unsigned long) * CHAR_BIT - sizeof(T) * CHAR_BIT);
	}

	template <typename T, typename = typename std::enable_if<sizeof(T) <= sizeof(unsigned long long)>::type>
	unsigned clz_impl(clzll_tag, T x) noexcept
	{
		return __builtin_clzll(x) - (sizeof(unsigned long long) * CHAR_BIT - sizeof(T) * CHAR_BIT);
	}

	template <typename T, typename = typename std::enable_if<sizeof(T) <= sizeof(unsigned int)>::type>
	unsigned ffs_impl(clz_tag, T x) noexcept
	{
		return __builtin_ffs(x);
	}

	template <typename T, typename = typename std::enable_if<sizeof(T) <= sizeof(unsigned long)>::type>
	unsigned ffs_impl(clzl_tag, T x) noexcept
	{
		return __builtin_ffsl(x);
	}

	template <typename T, typename = typename std::enable_if<sizeof(T) <= sizeof(unsigned long long)>::type>
	unsigned ffs_impl(clzll_tag, T x) noexcept
	{
		return __builtin_ffsll(x);
	}

	template <typename T, typename = typename std::enable_if<sizeof(T) <= sizeof(unsigned int)>::type>
	unsigned popcount_impl(clz_tag, T x) noexcept
	{
		return __builtin_popcount(x);
	}

	template <typename T, typename = typename std::enable_if<sizeof(T) <= sizeof(unsigned long)>::type>
	unsigned popcount_impl(clzl_tag, T x) noexcept
	{
		return __builtin_popcountl(x);
	}

	template <typename T, typename = typename std::enable_if<sizeof(T) <= sizeof(unsigned long long)>::type>
	unsigned popcount_impl(clzll_tag, T x) noexcept
	{
		return __builtin_popcountll(x);
	}

	template <typename T, typename = typename std::enable_if<sizeof(T) <= sizeof(unsigned int)>::type>
	unsigned ctz_impl(clz_tag, T x) noexcept
	{
		return __builtin_ctz(x);
	}

	template <typename T, typename = typename std::enable_if<sizeof(T) <= sizeof(unsigned long)>::type>
	unsigned ctz_impl(clzl_tag, T x) noexcept
	{
		return __builtin_ctzl(x);
	}

	template <typename T, typename = typename std::enable_if<sizeof(T) <= sizeof(unsigned long long)>::type>
	unsigned ctz_impl(clzll_tag, T x) noexcept
	{
		return __builtin_ctzll(x);
	}


#endif

	class bitmanip
	{
	private:
#if defined(PYGMALION_INTRINSICS_GNU)
		static unsigned clz_gnu8(std::uint8_t x) noexcept
		{
			return clz_impl(clz_tag{}, x);
		}

		static unsigned clz_gnu16(std::uint16_t x) noexcept
		{
			return clz_impl(clz_tag{}, x);
		}

		static unsigned clz_gnu32(std::uint32_t x) noexcept
		{
			return clz_impl(clz_tag{}, x);
		}

		static unsigned clz_gnu64(std::uint64_t x) noexcept
		{
			return clz_impl(clz_tag{}, x);
		}

		static unsigned ffs_gnu8(std::uint8_t x) noexcept
		{
			return ffs_impl(clz_tag{}, x);
		}

		static unsigned ffs_gnu16(std::uint16_t x) noexcept
		{
			return ffs_impl(clz_tag{}, x);
		}

		static unsigned ffs_gnu32(std::uint32_t x) noexcept
		{
			return ffs_impl(clz_tag{}, x);
		}

		static unsigned ffs_gnu64(std::uint64_t x) noexcept
		{
			return ffs_impl(clz_tag{}, x);
		}

		static unsigned popcount_gnu8(std::uint8_t x) noexcept
		{
			return popcount_impl(clz_tag{}, x);
		}

		static unsigned popcount_gnu16(std::uint16_t x) noexcept
		{
			return popcount_impl(clz_tag{}, x);
		}

		static unsigned popcount_gnu32(std::uint32_t x) noexcept
		{
			return popcount_impl(clz_tag{}, x);
		}

		static unsigned popcount_gnu64(std::uint64_t x) noexcept
		{
			return popcount_impl(clz_tag{}, x);
		}

		static unsigned ctz_gnu8(std::uint8_t x) noexcept
		{
			return ctz_impl(clz_tag{}, x);
		}

		static unsigned ctz_gnu16(std::uint16_t x) noexcept
		{
			return ctz_impl(clz_tag{}, x);
		}

		static unsigned ctz_gnu32(std::uint32_t x) noexcept
		{
			return ctz_impl(clz_tag{}, x);
		}

		static unsigned ctz_gnu64(std::uint64_t x) noexcept
		{
			return ctz_impl(clz_tag{}, x);
		}
#endif
#if defined(PYGMALION_NOSHIFTS)
		constexpr static std::uint8_t m_SetMask8[16]
		{
			static_cast<std::uint8_t>(std::uint8_t(1) << 0),
			static_cast<std::uint8_t>(std::uint8_t(1) << 1),
			static_cast<std::uint8_t>(std::uint8_t(1) << 2),
			static_cast<std::uint8_t>(std::uint8_t(1) << 3),
			static_cast<std::uint8_t>(std::uint8_t(1) << 4),
			static_cast<std::uint8_t>(std::uint8_t(1) << 5),
			static_cast<std::uint8_t>(std::uint8_t(1) << 6),
			static_cast<std::uint8_t>(std::uint8_t(1) << 7)
		};
		constexpr static std::uint8_t m_ResetMask8[16]
		{
			static_cast<std::uint8_t>(~(std::uint8_t(1) << 0)),
			static_cast<std::uint8_t>(~(std::uint8_t(1) << 1)),
			static_cast<std::uint8_t>(~(std::uint8_t(1) << 2)),
			static_cast<std::uint8_t>(~(std::uint8_t(1) << 3)),
			static_cast<std::uint8_t>(~(std::uint8_t(1) << 4)),
			static_cast<std::uint8_t>(~(std::uint8_t(1) << 5)),
			static_cast<std::uint8_t>(~(std::uint8_t(1) << 6)),
			static_cast<std::uint8_t>(~(std::uint8_t(1) << 7))
		};
		constexpr static std::uint16_t m_SetMask16[16]
		{
			static_cast<std::uint16_t>(std::uint16_t(1) << 0),
			static_cast<std::uint16_t>(std::uint16_t(1) << 1),
			static_cast<std::uint16_t>(std::uint16_t(1) << 2),
			static_cast<std::uint16_t>(std::uint16_t(1) << 3),
			static_cast<std::uint16_t>(std::uint16_t(1) << 4),
			static_cast<std::uint16_t>(std::uint16_t(1) << 5),
			static_cast<std::uint16_t>(std::uint16_t(1) << 6),
			static_cast<std::uint16_t>(std::uint16_t(1) << 7),
			static_cast<std::uint16_t>(std::uint16_t(1) << 8),
			static_cast<std::uint16_t>(std::uint16_t(1) << 9),
			static_cast<std::uint16_t>(std::uint16_t(1) << 10),
			static_cast<std::uint16_t>(std::uint16_t(1) << 11),
			static_cast<std::uint16_t>(std::uint16_t(1) << 12),
			static_cast<std::uint16_t>(std::uint16_t(1) << 13),
			static_cast<std::uint16_t>(std::uint16_t(1) << 14),
			static_cast<std::uint16_t>(std::uint16_t(1) << 15)
		};
		constexpr static std::uint16_t m_ResetMask16[16]
		{
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 0)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 1)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 2)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 3)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 4)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 5)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 6)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 7)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 8)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 9)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 10)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 11)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 12)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 13)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 14)),
			static_cast<std::uint16_t>(~(std::uint16_t(1) << 15))
		};
		constexpr static std::uint32_t m_SetMask32[32]
		{
			static_cast<std::uint32_t>(std::uint32_t(1) << 0),
			static_cast<std::uint32_t>(std::uint32_t(1) << 1),
			static_cast<std::uint32_t>(std::uint32_t(1) << 2),
			static_cast<std::uint32_t>(std::uint32_t(1) << 3),
			static_cast<std::uint32_t>(std::uint32_t(1) << 4),
			static_cast<std::uint32_t>(std::uint32_t(1) << 5),
			static_cast<std::uint32_t>(std::uint32_t(1) << 6),
			static_cast<std::uint32_t>(std::uint32_t(1) << 7),
			static_cast<std::uint32_t>(std::uint32_t(1) << 8),
			static_cast<std::uint32_t>(std::uint32_t(1) << 9),
			static_cast<std::uint32_t>(std::uint32_t(1) << 10),
			static_cast<std::uint32_t>(std::uint32_t(1) << 11),
			static_cast<std::uint32_t>(std::uint32_t(1) << 12),
			static_cast<std::uint32_t>(std::uint32_t(1) << 13),
			static_cast<std::uint32_t>(std::uint32_t(1) << 14),
			static_cast<std::uint32_t>(std::uint32_t(1) << 15),
			static_cast<std::uint32_t>(std::uint32_t(1) << 16),
			static_cast<std::uint32_t>(std::uint32_t(1) << 17),
			static_cast<std::uint32_t>(std::uint32_t(1) << 18),
			static_cast<std::uint32_t>(std::uint32_t(1) << 19),
			static_cast<std::uint32_t>(std::uint32_t(1) << 20),
			static_cast<std::uint32_t>(std::uint32_t(1) << 21),
			static_cast<std::uint32_t>(std::uint32_t(1) << 22),
			static_cast<std::uint32_t>(std::uint32_t(1) << 23),
			static_cast<std::uint32_t>(std::uint32_t(1) << 24),
			static_cast<std::uint32_t>(std::uint32_t(1) << 25),
			static_cast<std::uint32_t>(std::uint32_t(1) << 26),
			static_cast<std::uint32_t>(std::uint32_t(1) << 27),
			static_cast<std::uint32_t>(std::uint32_t(1) << 28),
			static_cast<std::uint32_t>(std::uint32_t(1) << 29),
			static_cast<std::uint32_t>(std::uint32_t(1) << 30),
			static_cast<std::uint32_t>(std::uint32_t(1) << 31)
		};
		constexpr static std::uint32_t m_ResetMask32[32]
		{
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 0)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 1)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 2)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 3)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 4)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 5)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 6)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 7)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 8)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 9)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 10)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 11)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 12)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 13)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 14)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 15)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 16)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 17)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 18)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 19)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 20)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 21)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 22)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 23)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 24)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 25)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 26)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 27)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 28)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 29)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 30)),
			static_cast<std::uint32_t>(~(std::uint32_t(1) << 31))
		};
		constexpr static std::uint64_t m_SetMask64[64]
		{
			static_cast<std::uint64_t>(std::uint64_t(1) << 0),
			static_cast<std::uint64_t>(std::uint64_t(1) << 1),
			static_cast<std::uint64_t>(std::uint64_t(1) << 2),
			static_cast<std::uint64_t>(std::uint64_t(1) << 3),
			static_cast<std::uint64_t>(std::uint64_t(1) << 4),
			static_cast<std::uint64_t>(std::uint64_t(1) << 5),
			static_cast<std::uint64_t>(std::uint64_t(1) << 6),
			static_cast<std::uint64_t>(std::uint64_t(1) << 7),
			static_cast<std::uint64_t>(std::uint64_t(1) << 8),
			static_cast<std::uint64_t>(std::uint64_t(1) << 9),
			static_cast<std::uint64_t>(std::uint64_t(1) << 10),
			static_cast<std::uint64_t>(std::uint64_t(1) << 11),
			static_cast<std::uint64_t>(std::uint64_t(1) << 12),
			static_cast<std::uint64_t>(std::uint64_t(1) << 13),
			static_cast<std::uint64_t>(std::uint64_t(1) << 14),
			static_cast<std::uint64_t>(std::uint64_t(1) << 15),
			static_cast<std::uint64_t>(std::uint64_t(1) << 16),
			static_cast<std::uint64_t>(std::uint64_t(1) << 17),
			static_cast<std::uint64_t>(std::uint64_t(1) << 18),
			static_cast<std::uint64_t>(std::uint64_t(1) << 19),
			static_cast<std::uint64_t>(std::uint64_t(1) << 20),
			static_cast<std::uint64_t>(std::uint64_t(1) << 21),
			static_cast<std::uint64_t>(std::uint64_t(1) << 22),
			static_cast<std::uint64_t>(std::uint64_t(1) << 23),
			static_cast<std::uint64_t>(std::uint64_t(1) << 24),
			static_cast<std::uint64_t>(std::uint64_t(1) << 25),
			static_cast<std::uint64_t>(std::uint64_t(1) << 26),
			static_cast<std::uint64_t>(std::uint64_t(1) << 27),
			static_cast<std::uint64_t>(std::uint64_t(1) << 28),
			static_cast<std::uint64_t>(std::uint64_t(1) << 29),
			static_cast<std::uint64_t>(std::uint64_t(1) << 30),
			static_cast<std::uint64_t>(std::uint64_t(1) << 31),
			static_cast<std::uint64_t>(std::uint64_t(1) << 32),
			static_cast<std::uint64_t>(std::uint64_t(1) << 33),
			static_cast<std::uint64_t>(std::uint64_t(1) << 34),
			static_cast<std::uint64_t>(std::uint64_t(1) << 35),
			static_cast<std::uint64_t>(std::uint64_t(1) << 36),
			static_cast<std::uint64_t>(std::uint64_t(1) << 37),
			static_cast<std::uint64_t>(std::uint64_t(1) << 38),
			static_cast<std::uint64_t>(std::uint64_t(1) << 39),
			static_cast<std::uint64_t>(std::uint64_t(1) << 40),
			static_cast<std::uint64_t>(std::uint64_t(1) << 41),
			static_cast<std::uint64_t>(std::uint64_t(1) << 42),
			static_cast<std::uint64_t>(std::uint64_t(1) << 43),
			static_cast<std::uint64_t>(std::uint64_t(1) << 44),
			static_cast<std::uint64_t>(std::uint64_t(1) << 45),
			static_cast<std::uint64_t>(std::uint64_t(1) << 46),
			static_cast<std::uint64_t>(std::uint64_t(1) << 47),
			static_cast<std::uint64_t>(std::uint64_t(1) << 48),
			static_cast<std::uint64_t>(std::uint64_t(1) << 49),
			static_cast<std::uint64_t>(std::uint64_t(1) << 50),
			static_cast<std::uint64_t>(std::uint64_t(1) << 51),
			static_cast<std::uint64_t>(std::uint64_t(1) << 52),
			static_cast<std::uint64_t>(std::uint64_t(1) << 53),
			static_cast<std::uint64_t>(std::uint64_t(1) << 54),
			static_cast<std::uint64_t>(std::uint64_t(1) << 55),
			static_cast<std::uint64_t>(std::uint64_t(1) << 56),
			static_cast<std::uint64_t>(std::uint64_t(1) << 57),
			static_cast<std::uint64_t>(std::uint64_t(1) << 58),
			static_cast<std::uint64_t>(std::uint64_t(1) << 59),
			static_cast<std::uint64_t>(std::uint64_t(1) << 60),
			static_cast<std::uint64_t>(std::uint64_t(1) << 61),
			static_cast<std::uint64_t>(std::uint64_t(1) << 62),
			static_cast<std::uint64_t>(std::uint64_t(1) << 63)
		};
		constexpr static std::uint64_t m_ResetMask64[64]
		{
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 0)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 1)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 2)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 3)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 4)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 5)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 6)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 7)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 8)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 9)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 10)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 11)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 12)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 13)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 14)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 15)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 16)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 17)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 18)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 19)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 20)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 21)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 22)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 23)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 24)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 25)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 26)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 27)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 28)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 29)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 30)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 31)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 32)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 33)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 34)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 35)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 36)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 37)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 38)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 39)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 40)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 41)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 42)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 43)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 44)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 45)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 46)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 47)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 48)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 49)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 50)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 51)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 52)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 53)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 54)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 55)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 56)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 57)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 58)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 59)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 60)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 61)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 62)),
			static_cast<std::uint64_t>(~(std::uint64_t(1) << 63))
		};
#endif
	public:
		constexpr static std::uint8_t setMask8(const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 8);
#if defined(PYGMALION_NOSHIFTS)
			return m_SetMask8[idx];
#else
			return std::uint8_t(1) << idx;
#endif
		}

		constexpr static std::uint8_t resetMask8(const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 8);
#if defined(PYGMALION_NOSHIFTS)
			return m_ResetMask8[idx];
#else
			return ~(std::uint8_t(1) << idx);
#endif
		}

		constexpr static void setBit8(std::uint8_t& bits, const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 8);
			bits |= setMask8(idx);
		}

		constexpr static void clearBit8(std::uint8_t& bits, const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 8);
			bits &= resetMask8(idx);
		}

		constexpr static bool checkBit8(const std::uint8_t bits, const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 8);
			return bits & setMask8(idx);
		}

		constexpr static std::uint16_t setMask16(const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 16);
#if defined(PYGMALION_NOSHIFTS)
			return m_SetMask16[idx];
#else
			return std::uint16_t(1) << idx;
#endif
		}

		constexpr static std::uint16_t resetMask16(const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 16);
#if defined(PYGMALION_NOSHIFTS)
			return m_ResetMask16[idx];
#else
			return ~(std::uint16_t(1) << idx);
#endif
		}

		constexpr static void setBit16(std::uint16_t& bits, const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 16);
			bits |= setMask16(idx);
		}

		constexpr static void clearBit16(std::uint16_t& bits, const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 16);
			bits &= resetMask16(idx);
		}

		constexpr static bool checkBit16(const std::uint16_t bits, const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 16);
			return bits & setMask16(idx);
		}

		constexpr static std::uint32_t setMask32(const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 32);
#if defined(PYGMALION_NOSHIFTS)
			return m_SetMask32[idx];
#else
			return std::uint32_t(1) << idx;
#endif
		}

		constexpr static std::uint32_t resetMask32(const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 32);
#if defined(PYGMALION_NOSHIFTS)
			return m_ResetMask32[idx];
#else
			return ~(std::uint32_t(1) << idx);
#endif
		}

		constexpr static void setBit32(std::uint32_t& bits, const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 32);
			bits |= setMask32(idx);
		}

		constexpr static void clearBit32(std::uint32_t& bits, const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 32);
			bits &= resetMask32(idx);
		}

		constexpr static bool checkBit32(const std::uint32_t bits, const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 32);
			return bits & setMask32(idx);
		}

		constexpr static std::uint64_t setMask64(const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 64);
#if defined(PYGMALION_NOSHIFTS)
			return m_SetMask64[idx];
#else
			return std::uint64_t(1) << idx;
#endif
		}

		constexpr static std::uint64_t resetMask64(const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 64);
#if defined(PYGMALION_NOSHIFTS)
			return m_ResetMask64[idx];
#else
			return ~(std::uint64_t(1) << idx);
#endif
		}

		constexpr static void setBit64(std::uint64_t& bits, const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 64);
			bits |= setMask64(idx);
		}

		constexpr static void clearBit64(std::uint64_t& bits, const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 64);
			bits &= resetMask64(idx);
		}

		constexpr static bool checkBit64(const std::uint64_t bits, const int idx) noexcept
		{
			assert(idx >= 0);
			assert(idx < 64);
			return bits & setMask64(idx);
		}

		static auto populationCount64(const std::uint64_t bits) noexcept
		{
#if defined(PYGMALION_INTRINSICS_GNU)
			return static_cast<int>(popcount_gnu64(bits));
#elif defined(PYGMALION_INTRINSICS_MSC)
#if defined(_M_X64)
			return static_cast<int>(__popcnt64(bits));
#else
			return static_cast<int>(__popcnt(static_cast<std::uint32_t>(bits & std::uint64_t(0x00000000FFFFFFFF))) + __popcnt(static_cast<std::uint32_t>(bits >> 32)));
#endif
#else
			std::uint64_t left{ static_cast<std::uint64_t>(bits & std::uint64_t(0xaaaaaaaaaaaaaaaa)) };
			std::uint64_t right{ static_cast<std::uint64_t>(bits & std::uint64_t(0x5555555555555555)) };
			std::uint64_t value = (left >> 1) + right;

			left = value & std::uint64_t(0xcccccccccccccccc);
			right = value & std::uint64_t(0x3333333333333333);
			value = (left >> 2) + right;

			left = value & std::uint64_t(0xf0f0f0f0f0f0f0f0);
			right = value & std::uint64_t(0x0f0f0f0f0f0f0f0f);
			value = (left >> 4) + right;

			left = value & std::uint64_t(0xff00ff00ff00ff00);
			right = value & std::uint64_t(0x00ff00ff00ff00ff);
			value = (left >> 8) + right;

			left = value & std::uint64_t(0xffff0000ffff0000);
			right = value & std::uint64_t(0x0000ffff0000ffff);
			value = (left >> 16) + right;

			left = value & std::uint64_t(0xffffffff00000000);
			right = value & std::uint64_t(0x00000000ffffffff);
			value = (left >> 32) + right;

			return static_cast<int>(value);
#endif
		}

		static bool bitScanForward64(const std::uint64_t bits, int& idx)
		{
#if defined(PYGMALION_INTRINSICS_GNU)
			if (bits)
			{
				idx = static_cast<int>(ctz_gnu64(bits));
				return true;
			}
			else
				return false;
#elif defined(PYGMALION_INTRINSICS_MSC)
#if defined(_M_X64)
			unsigned long square;
			if (_BitScanForward64(&square, bits))
			{
				idx = static_cast<int>(square);
				return true;
			}
			else
				return false;
#else
			unsigned long index;
			unsigned char ret = _BitScanForward(&index, static_cast<unsigned long>(bits & std::uint64_t(0x00000000FFFFFFFF)));
			if (ret)
			{
				idx = static_cast<int>(index);
				return true;
			}
			ret = _BitScanForward(&index, static_cast<unsigned long>((bits & std::uint64_t(0xFFFFFFFF00000000)) >> 32));
			idx = static_cast<int>(index + 32);
			return ret;
#endif
#else
			if (!bits)
				return false;
			else
			{
				idx = populationCount64(static_cast<std::uint64_t>((bits & -static_cast<std::int64_t>(bits)) - std::uint64_t(1)));
				return true;
			}
#endif
		}

		static bool bitScanReverse64(const std::uint64_t bits, int& idx)
		{
#if defined(PYGMALION_INTRINSICS_GNU)
			if (bits)
			{
				idx = 63 - static_cast<int>(clz_gnu64(bits));
				return true;
			}
			else
				return false;
#elif defined(PYGMALION_INTRINSICS_MSC)
#if defined(_M_X64)
			unsigned long square;
			if (_BitScanReverse64(&square, bits))
			{
				idx = static_cast<int>(square);
				return true;
			}
			else
				return false;
#else
			unsigned long index;
			unsigned char ret = _BitScanReverse(&index, static_cast<unsigned long>((bits & std::uint64_t(0xFFFFFFFF00000000)) >> 32));
			if (ret)
			{
				idx = static_cast<int>(index + 32);
				return true;
			}
			ret = _BitScanReverse(&index, static_cast<unsigned long>(bits & std::uint64_t(0x00000000FFFFFFFF)));
			idx = static_cast<int>(index);
			return ret;
#endif
#else
			if (bits)
			{
				std::uint64_t x{ bits };
				int r{ (x > 0xFFFFFFFF) << 5 };
				x >>= r;
				int q = (x > 0xFFFF) << 4;
				x >>= q;
				r |= q;
				q = (x > 0xFF) << 3;
				x >>= q;
				r |= q;
				q = (x > 0xF) << 2;
				x >>= q;
				r |= q;
				q = (x > 0x3) << 1;
				x >>= q;
				r |= q;
				idx = r | (x >> 1);
				return true;
			}
			else
				return false;
#endif
		}

		static auto populationCount32(const std::uint32_t bits) noexcept
		{
#if defined(PYGMALION_INTRINSICS_GNU)
			return static_cast<int>(popcount_gnu32(bits));
#elif defined(PYGMALION_INTRINSICS_MSC)
			return static_cast<int>(__popcnt(bits));
#else
			std::uint32_t left{ static_cast<std::uint32_t>(bits & std::uint32_t(0xaaaaaaaa)) };
			std::uint32_t right{ static_cast<std::uint32_t>(bits & std::uint32_t(0x55555555)) };
			std::uint32_t value = (left >> 1) + right;

			left = value & std::uint32_t(0xcccccccc);
			right = value & std::uint32_t(0x33333333);
			value = (left >> 2) + right;

			left = value & std::uint32_t(0xf0f0f0f0);
			right = value & std::uint32_t(0x0f0f0f0f);
			value = (left >> 4) + right;

			left = value & std::uint32_t(0xff00ff00);
			right = value & std::uint32_t(0x00ff00ff);
			value = (left >> 8) + right;

			left = value & std::uint32_t(0xffff0000);
			right = value & std::uint32_t(0x0000ffff);
			value = (left >> 16) + right;

			return static_cast<int>(value);
#endif
		}

		static bool bitScanForward32(const std::uint32_t bits, int& idx)
		{
#if defined(PYGMALION_INTRINSICS_GNU)
			if (bits)
			{
				idx = static_cast<int>(ctz_gnu32(bits));
				return true;
			}
			else
				return false;
#elif defined(PYGMALION_INTRINSICS_MSC)
			unsigned long square;
			if (_BitScanForward(&square, bits))
			{
				idx = static_cast<int>(square);
				return true;
			}
			else
				return false;
#else
			if (!bits)
				return false;
			else
			{
				idx = populationCount32(static_cast<std::uint32_t>((bits & -static_cast<std::int32_t>(bits)) - std::uint32_t(1)));
				return true;
			}
#endif
		}

		static bool bitScanReverse32(const std::uint32_t bits, int& idx)
		{
#if defined(PYGMALION_INTRINSICS_GNU)
			if (bits)
			{
				idx = 31 - static_cast<int>(clz_gnu32(bits));
				return true;
			}
			else
				return false;
#elif defined(PYGMALION_INTRINSICS_MSC)
			unsigned long square;
			if (_BitScanReverse(&square, bits))
			{
				idx = static_cast<int>(square);
				return true;
			}
			else
				return false;
#else
			if (bits)
			{
				std::uint32_t x{ bits };
				int r{ (x > 0xFFFF) << 4 };
				x >>= r;
				int q = (x > 0xFF) << 3;
				x >>= q;
				r |= q;
				q = (x > 0xF) << 2;
				x >>= q;
				r |= q;
				q = (x > 0x3) << 1;
				x >>= q;
				r |= q;
				idx = r | (x >> 1);
				return true;
			}
			else
				return false;
#endif
		}

		static auto populationCount16(const std::uint16_t bits) noexcept
		{
#if defined(PYGMALION_INTRINSICS_GNU)
			return static_cast<int>(popcount_gnu16(bits));
#elif defined(PYGMALION_INTRINSICS_MSC)
			return static_cast<int>(__popcnt16(bits));
#else
			std::uint16_t left{ static_cast<std::uint16_t>(bits & std::uint16_t(0xaaaa)) };
			std::uint16_t right{ static_cast<std::uint16_t>(bits & std::uint16_t(0x5555)) };
			std::uint16_t value = (left >> 1) + right;

			left = value & std::uint16_t(0xcccc);
			right = value & std::uint16_t(0x3333);
			value = (left >> 2) + right;

			left = value & std::uint16_t(0xf0f0);
			right = value & std::uint16_t(0x0f0f);
			value = (left >> 4) + right;

			left = value & std::uint16_t(0xff00);
			right = value & std::uint16_t(0x00ff);
			value = (left >> 8) + right;

			return static_cast<int>(value);
#endif
		}

		static bool bitScanForward16(const std::uint16_t bits, int& idx)
		{
#if defined(PYGMALION_INTRINSICS_GNU)
			if (bits)
			{
				idx = static_cast<int>(ctz_gnu16(bits));
				return true;
			}
			else
				return false;
#elif defined(PYGMALION_INTRINSICS_MSC)
			unsigned long square;
			if (_BitScanForward(&square, bits))
			{
				idx = static_cast<int>(square);
				return true;
			}
			else
				return false;
#else
			if (!bits)
				return false;
			else
			{
				idx = populationCount16(static_cast<std::uint16_t>((bits & -static_cast<std::int16_t>(bits)) - std::uint16_t(1)));
				return true;
			}
#endif
		}

		static bool bitScanReverse16(const std::uint16_t bits, int& idx)
		{
#if defined(PYGMALION_INTRINSICS_GNU)
			if (bits)
			{
				idx = 15 - static_cast<int>(clz_gnu16(bits));
				return true;
			}
			else
				return false;
#elif defined(PYGMALION_INTRINSICS_MSC)
			unsigned long square;
			if (_BitScanReverse(&square, bits))
			{
				idx = static_cast<int>(square);
				return true;
			}
			else
				return false;
#else
			if (bits)
			{
				std::uint16_t x{ bits };
				int r{ (x > 0xFF) << 3 };
				x >>= r;
				int q = (x > 0xF) << 2;
				x >>= q;
				r |= q;
				q = (x > 0x3) << 1;
				x >>= q;
				r |= q;
				idx = r | (x >> 1);
				return true;
			}
			else
				return false;
#endif
		}

		static auto populationCount8(const std::uint8_t bits) noexcept
		{
#if defined(PYGMALION_INTRINSICS_GNU)
			return static_cast<int>(popcount_gnu8(bits));
#elif defined(PYGMALION_INTRINSICS_MSC)
			return static_cast<int>(__popcnt16(bits));
#else
			std::uint16_t left{ static_cast<std::uint8_t>(bits & std::uint8_t(0xaa)) };
			std::uint16_t right{ static_cast<std::uint8_t>(bits & std::uint8_t(0x55)) };
			std::uint16_t value = (left >> 1) + right;

			left = value & std::uint8_t(0xcc);
			right = value & std::uint8_t(0x33);
			value = (left >> 2) + right;

			left = value & std::uint8_t(0xf0);
			right = value & std::uint8_t(0x0f);
			value = (left >> 4) + right;

			return static_cast<int>(value);
#endif
		}

		static bool bitScanForward8(const std::uint8_t bits, int& idx)
		{
#if defined(PYGMALION_INTRINSICS_GNU)
			if (bits)
			{
				idx = static_cast<int>(ctz_gnu8(bits));
				return true;
			}
			else
				return false;
#elif defined(PYGMALION_INTRINSICS_MSC)
			unsigned long square;
			if (_BitScanForward(&square, bits))
			{
				idx = static_cast<int>(square);
				return true;
			}
			else
				return false;
#else
			if (!bits)
				return false;
			else
			{
				idx = populationCount8(static_cast<std::uint8_t>((bits & -static_cast<std::int8_t>(bits)) - std::uint8_t(1)));
				return true;
			}
#endif
		}

		static bool bitScanReverse8(const std::uint8_t bits, int& idx)
		{
#if defined(PYGMALION_INTRINSICS_GNU)
			if (bits)
			{
				idx = 7 - static_cast<int>(clz_gnu8(bits));
				return true;
			}
			else
				return false;
#elif defined(PYGMALION_INTRINSICS_MSC)
			unsigned long square;
			if (_BitScanReverse(&square, bits))
			{
				idx = static_cast<int>(square);
				return true;
			}
			else
				return false;
#else
			if (bits)
			{
				std::uint8_t x{ bits };
				int r{ (x > 0xF) << 2 };
				x >>= r;
				int q = (x > 0x3) << 1;
				x >>= q;
				r |= q;
				idx = r | (x >> 1);
				return true;
			}
			else
				return false;
#endif
		}


		static std::uint64_t pext64(const std::uint64_t val, std::uint64_t mask) noexcept
		{
			//#if defined(PYGMALION_CPU_BMI2) && (defined(_M_X64)||defined(__x86_64__))
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
			return _pext_u64(val, mask);
#elif defined(PYGMALION_CPU_BMI2)
			const std::uint32_t highMask{ static_cast<std::uint32_t>((mask & std::uint64_t(0xffffffff00000000)) >> 32) };
			const std::uint32_t lowMask{ static_cast<std::uint32_t>((mask & std::uint64_t(0x00000000ffffffff)) >> 0) };
			const std::uint32_t highVal{ static_cast<std::uint32_t>((val & std::uint64_t(0xffffffff00000000)) >> 32) };
			const std::uint32_t lowVal{ static_cast<std::uint32_t>((val & std::uint64_t(0x00000000ffffffff)) >> 0) };
			const int lowBits{ populationCount32(lowMask) };
			const std::uint32_t highIndex{ _pext_u32(highVal, highMask) };
			const std::uint32_t lowIndex{ _pext_u32(lowVal, lowMask) };
			const std::uint64_t index{ (static_cast<std::uint64_t>(highIndex) << lowBits) | static_cast<std::uint64_t>(lowIndex) };
			return index;
#else
			std::uint64_t res{ 0 };
			std::uint64_t bb{ 1 };
			while (mask)
			{
				if (val & mask & -static_cast<std::int64_t>(mask))
					res |= bb;
				mask &= mask - 1;
				bb <<= 1;
			}
			return res;
#endif
		}

		static std::uint64_t pdep64(const std::uint64_t val, std::uint64_t mask) noexcept
		{
#if defined(PYGMALION_CPU_BMI2)&& defined(PYGMALION_CPU_X64)
			return _pdep_u64(val, mask);
#elif defined(PYGMALION_CPU_BMI2)
			const std::uint32_t highMask{ static_cast<std::uint32_t>((mask & std::uint64_t(0xffffffff00000000)) >> 32) };
			const std::uint32_t lowMask{ static_cast<std::uint32_t>((mask & std::uint64_t(0x00000000ffffffff)) >> 0) };
			const int lowBits{ populationCount32(lowMask) };
			const std::uint32_t highIndex{ static_cast<std::uint32_t>(val >> lowBits) };
			const std::uint32_t lowIndex{ static_cast<std::uint32_t>(val & ((std::uint64_t(1) << (lowBits + 1)) - 1)) };
			const std::uint32_t highVal{ _pdep_u32(highIndex, highMask) };
			const std::uint32_t lowVal{ _pdep_u32(lowIndex, lowMask) };
			const std::uint64_t value{ (static_cast<std::uint64_t>(highVal) << 32) | static_cast<std::uint64_t>(lowVal) };
			return value;
#else
			std::uint64_t src{ val };
			std::uint64_t res{ 0 };
			std::uint64_t lowest{ mask & -static_cast<std::int64_t>(mask) };
			while (lowest)
			{
				const std::uint64_t LSB{ static_cast<std::uint64_t>(static_cast<std::int64_t>(src << 63) >> 63) };
				res |= LSB & lowest;
				mask &= ~lowest;
				src >>= 1;
				lowest = (mask & -static_cast<std::int64_t>(mask));
			}
			return res;
#endif
		}

		static std::uint32_t pext32(const std::uint32_t val, std::uint32_t mask) noexcept
		{
#if defined(PYGMALION_CPU_BMI2)
			return _pext_u32(val, mask);
#else
			std::uint32_t res{ 0 };
			std::uint32_t bb{ 1 };
			while (mask)
			{
				if (val & mask & -static_cast<std::int32_t>(mask))
					res |= bb;
				mask &= mask - 1;
				bb <<= 1;
			}
			return res;
#endif
		}

		static std::uint32_t pdep32(const std::uint32_t val, std::uint32_t mask) noexcept
		{
#if defined(PYGMALION_CPU_BMI2)
			return _pdep_u32(val, mask);
#else
			std::uint32_t src{ val };
			std::uint32_t res{ 0 };
			std::uint32_t lowest{ mask & -static_cast<std::int32_t>(mask) };
			while (lowest)
			{
				const std::uint32_t LSB{ static_cast<std::uint32_t>(static_cast<std::int32_t>(src << 31) >> 31) };
				res |= LSB & lowest;
				mask &= ~lowest;
				src >>= 1;
				lowest = (mask & -static_cast<std::int32_t>(mask));
			}
			return res;
#endif
		}

		static std::uint16_t pext16(const std::uint16_t val, std::uint16_t mask) noexcept
		{
#if defined(PYGMALION_CPU_BMI2)
			return _pext_u32(val, mask);
#else
			std::uint16_t res{ 0 };
			std::uint16_t bb{ 1 };
			while (mask)
			{
				if (val & mask & -static_cast<std::int16_t>(mask))
					res |= bb;
				mask &= mask - 1;
				bb <<= 1;
			}
			return res;
#endif
		}

		static std::uint16_t pdep16(const std::uint16_t val, std::uint16_t mask) noexcept
		{
#if defined(PYGMALION_CPU_BMI2)
			return _pdep_u32(val, mask);
#else
			std::uint16_t src{ val };
			std::uint16_t res{ 0 };
			std::uint16_t lowest{ static_cast<std::uint16_t>(mask & -static_cast<std::int16_t>(mask)) };
			while (lowest)
			{
				const std::uint16_t LSB{ static_cast<std::uint16_t>(static_cast<std::int16_t>(src << 15) >> 15) };
				res |= LSB & lowest;
				mask &= ~lowest;
				src >>= 1;
				lowest = (mask & -static_cast<std::int16_t>(mask));
			}
			return res;
#endif
		}

		static std::uint8_t pext8(const std::uint8_t val, std::uint8_t mask) noexcept
		{
#if defined(PYGMALION_CPU_BMI2)
			return _pext_u32(val, mask);
#else
			std::uint8_t res{ 0 };
			std::uint8_t bb{ 1 };
			while (mask)
			{
				if (val & mask & -static_cast<std::int8_t>(mask))
					res |= bb;
				mask &= mask - 1;
				bb <<= 1;
			}
			return res;
#endif
		}

		static std::uint8_t pdep8(const std::uint8_t val, std::uint8_t mask) noexcept
		{
#if defined(PYGMALION_CPU_BMI2)
			return _pdep_u32(val, mask);
#else
			std::uint8_t src{ val };
			std::uint8_t res{ 0 };
			std::uint8_t lowest{ static_cast<std::uint8_t>(mask & -static_cast<std::int8_t>(mask)) };
			while (lowest)
			{
				const std::uint8_t LSB{ static_cast<std::uint8_t>(static_cast<std::int8_t>(src << 7) >> 7) };
				res |= LSB & lowest;
				mask &= ~lowest;
				src >>= 1;
				lowest = (mask & -static_cast<std::int8_t>(mask));
			}
			return res;
#endif
		}

	};
}