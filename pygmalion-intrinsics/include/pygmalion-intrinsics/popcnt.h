
namespace pygmalion::intrinsics
{
	namespace detail
	{
		template<size_t COUNT_BITS, typename T>
		size_t popcnt_reference(const T R) noexcept;

		template<size_t COUNT_BITS, typename = typename std::enable_if<true>::type>
		struct popcnt_traits {};

		template<size_t COUNT_BITS>
		struct popcnt_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS <= 64) && (COUNT_BITS > 32)>::type>
		{
			using refType = std::uint64_t;
			using intType = refType;
			static size_t reference(const refType& bits) noexcept
			{
				size_t count{ 0 };
				for (size_t i = 0; i < COUNT_BITS; i++)
				{
					if (bits & static_cast<refType>(refType(1) << i))
						count++;
				}
				return count;
			}
			static size_t baseline(const refType& bits) noexcept
			{
#if defined(PYGMALION_INTRINSICS_MSC) && defined(PYGMALION_CPU_X64)
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					return __popcnt64(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
				if constexpr (compiler::supports(compiler::flags::GNU))
				{
					if constexpr (sizeof(bits) <= sizeof(unsigned int))
						return __builtin_popcount(bits);
					else if constexpr (sizeof(bits) <= sizeof(unsigned long))
						return __builtin_popcountl(bits);
					else if constexpr (sizeof(bits) <= sizeof(unsigned long long))
						return __builtin_popcountll(bits);
				}
#endif
#if defined(PYGMALION_INTRINSICS_MSC) && defined(PYGMALION_CPU_X86)
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					return __popcnt(*(reinterpret_cast<const unsigned int*>(&bits) + 1)) + __popcnt(*reinterpret_cast<const unsigned int*>(&bits));
#endif
				return popcnt_reference<COUNT_BITS, refType>(bits);
			}
			static size_t generic(const refType& bits)
			{
				return popcnt_reference<COUNT_BITS, refType>(bits);
			}
		};

		template<size_t COUNT_BITS>
		struct popcnt_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS <= 32) && (COUNT_BITS > 16)>::type>
		{
			using refType = std::uint32_t;
			using intType = refType;
			static size_t reference(const refType& bits) noexcept
			{
				size_t count{ 0 };
				for (size_t i = 0; i < COUNT_BITS; i++)
				{
					if (bits & static_cast<refType>(refType(1) << i))
						count++;
				}
				return count;
			}
			static size_t baseline(const refType& bits) noexcept
			{
#if defined(PYGMALION_INTRINSICS_MSC) && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					return __popcnt(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
				if constexpr (compiler::supports(compiler::flags::GNU))
				{
					if constexpr (sizeof(bits) <= sizeof(unsigned int))
						return __builtin_popcount(bits);
					else if constexpr (sizeof(bits) <= sizeof(unsigned long))
						return __builtin_popcountl(bits);
					else if constexpr (sizeof(bits) <= sizeof(unsigned long long))
						return __builtin_popcountll(bits);
				}
#endif
				return popcnt_reference<COUNT_BITS, refType>(bits);
			}
			static size_t generic(const refType& bits)
			{
				return popcnt_reference<COUNT_BITS, refType>(bits);
			}
		};

		template<size_t COUNT_BITS>
		struct popcnt_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS <= 16) && (COUNT_BITS > 8)>::type>
		{
			using refType = std::uint16_t;
			using intType = refType;
			static size_t reference(const refType& bits) noexcept
			{
				size_t count{ 0 };
				for (size_t i = 0; i < COUNT_BITS; i++)
				{
					if (bits & static_cast<refType>(refType(1) << i))
						count++;
				}
				return count;
			}
			static size_t baseline(const refType& bits) noexcept
			{
#if defined(PYGMALION_INTRINSICS_MSC) && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					return __popcnt16(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
				if constexpr (compiler::supports(compiler::flags::GNU))
				{
					if constexpr (sizeof(bits) <= sizeof(unsigned int))
						return __builtin_popcount(bits);
					else if constexpr (sizeof(bits) <= sizeof(unsigned long))
						return __builtin_popcountl(bits);
					else if constexpr (sizeof(bits) <= sizeof(unsigned long long))
						return __builtin_popcountll(bits);
				}
#endif
				return popcnt_reference<COUNT_BITS, refType>(bits);
			}
			static size_t generic(const refType& bits)
			{
				return popcnt_reference<COUNT_BITS, refType>(bits);
			}
		};

		template<size_t COUNT_BITS>
		struct popcnt_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS <= 8) && (COUNT_BITS > 1)>::type>
		{
			using refType = std::uint8_t;
			using intType = refType;
			static size_t reference(const refType& bits) noexcept
			{
				size_t count{ 0 };
				for (size_t i = 0; i < COUNT_BITS; i++)
				{
					if (bits & static_cast<refType>(refType(1) << i))
						count++;
				}
				return count;
			}
			static size_t baseline(const refType& bits) noexcept
			{
#if defined(PYGMALION_INTRINSICS_MSC) && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					return __popcnt16(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
				if constexpr (compiler::supports(compiler::flags::GNU))
				{
					if constexpr (sizeof(bits) <= sizeof(unsigned int))
						return __builtin_popcount(bits);
					else if constexpr (sizeof(bits) <= sizeof(unsigned long))
						return __builtin_popcountl(bits);
					else if constexpr (sizeof(bits) <= sizeof(unsigned long long))
						return __builtin_popcountll(bits);
				}
#endif
				return popcnt_reference<COUNT_BITS, refType>(bits);
			}
			static size_t generic(const refType& bits)
			{
				return popcnt_reference<COUNT_BITS, refType>(bits);
			}
		};

		template<size_t COUNT_BITS>
		struct popcnt_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS == 1)>::type>
		{
			using refType = bool;
			using intType = std::uint8_t;
			static size_t reference(const refType& bits) noexcept
			{
				return bits ? 1 : 0;
			}
			static size_t baseline(const refType& bits) noexcept
			{
				return bits;
			}
			static size_t generic(const refType& bits)
			{
				return popcnt_reference<COUNT_BITS, refType>(bits);
			}
		};

		template<size_t COUNT_BITS>
		struct popcnt_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS == 0)>::type>
		{
			using refType = std::uint8_t;
			using intType = std::uint8_t;
			static size_t reference(const refType& bits) noexcept
			{
				return 0;
			}
			static size_t baseline(const refType& bits) noexcept
			{
				return 0;
			}
			static size_t generic(const refType& bits)
			{
				return popcnt_reference<COUNT_BITS, refType>(bits);
			}
		};

		template<size_t COUNT_BITS>
		struct popcnt_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS > 64)>::type>
		{
			using refType = std::uintmax_t;
			using intType = refType;
			static size_t reference(const refType& bits) noexcept
			{
				size_t count{ 0 };
				for (size_t i = 0; i < COUNT_BITS; i++)
				{
					if (bits & static_cast<refType>(refType(1) << i))
						count++;
				}
				return count;
			}
			static size_t baseline(const refType& bits) noexcept
			{
#if defined(PYGMALION_INTRINSICS_GNU)
				if constexpr (compiler::supports(compiler::flags::GNU))
				{
					if constexpr (sizeof(bits) <= sizeof(unsigned int))
						return __builtin_popcount(bits);
					else if constexpr (sizeof(bits) <= sizeof(unsigned long))
						return __builtin_popcountl(bits);
					else if constexpr (sizeof(bits) <= sizeof(unsigned long long))
						return __builtin_popcountll(bits);
				}
#endif
				return popcnt_reference<COUNT_BITS, refType>(bits);
			}
			static size_t generic(const refType& bits)
			{
				return popcnt_reference<COUNT_BITS, refType>(bits);
			}
		};

	}

	class popcnt :
		protected base
	{
	private:
		template <typename T, int iteration>
		constexpr static T popcount_ref(const T bits) noexcept
		{
			if constexpr (std::is_same<T, bool>::value)
				return bits;
			else
			{
				constexpr const int shift{ 1 << iteration };
				if constexpr (shift >= (sizeof(T) * CHAR_BIT))
					return bits;
				else
				{
					constexpr const std::array<T, 2> masks
					{
						static_cast<T>(static_cast<T>(-T(1)) / ((T(1) << (1 << iteration)) + 1)),
						static_cast<T>(~(static_cast<T>(-T(1)) / ((T(1) << (1 << iteration)) + 1)))
					};
					const T low{ static_cast<T>(bits & masks[0]) };
					const T high{ static_cast<T>(bits & masks[1]) };
					const T value{ static_cast<T>((high >> shift) + low) };
					return popcount_ref<T, iteration + 1>(value);
				}
			}
		}

		template <size_t COUNT_CHANNELS, typename UINT>
		constexpr static bool enable_empty() noexcept
		{
			return COUNT_CHANNELS <= 0;
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_empty<COUNT_CHANNELS, UINT>()>::type>
		PYGMALION_INLINE static size_t impl(tag_best, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
		{
			return 0;
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_empty<COUNT_CHANNELS, UINT>()>::type>
		static std::string name(tag_best, std::index_sequence<CHANNEL...>) noexcept
		{
			return "0bit";
		}

		template <size_t COUNT_CHANNELS, typename UINT>
		constexpr static bool enable_bool() noexcept
		{
			return std::is_same<bool, UINT>::value;
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_bool<COUNT_CHANNELS, UINT>()>::type>
		PYGMALION_INLINE static size_t impl(tag_bool, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
		{
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned char) };
			constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned char) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
			const std::array<unsigned char, countSlices>& transformedSlices{ *reinterpret_cast<const std::array<unsigned char, countSlices>*>(&bits) };
			const std::array<UINT, countOddChannels>& oddChannels{ *(reinterpret_cast<const std::array<UINT, countOddChannels>*>(&bits) + countTransformedChannels) };
			constexpr const auto lambdaSlice = [](const bool bits, const size_t index)->size_t
			{
				return bits;
			};
			const std::array<size_t, countSlices> countsSlices{ arrayhelper::transform<countSlices,size_t>(transformedSlices, lambdaSlice) };
			if constexpr (countOddChannels > 0)
			{
				const size_t countOdd{ impl<countOddChannels, UINT>(tag_best{},oddChannels,std::make_index_sequence<countOddChannels>{}) };
				return base::sumChannels<countSlices, 0, countSlices, size_t>(countsSlices) + countOdd;
			}
			else
				return base::sumChannels<countSlices, 0, countSlices, size_t>(countsSlices);
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_bool<COUNT_CHANNELS, UINT>()>::type>
		static std::string name(tag_bool, std::index_sequence<CHANNEL...>) noexcept
		{
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned char) };
			constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned char) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
			std::stringstream sstr;
			for (size_t slice = 0; slice < countSlices; slice++)
			{
				sstr << "1bit";
				sstr << ((slice == countSlices - 1) ? "" : " | ");
			}
			if constexpr (countOddChannels > 0)
				sstr << " | " << name<countOddChannels, UINT>(tag_best{}, std::make_index_sequence<countOddChannels>{});
			return sstr.str();
		}

		template <size_t COUNT_CHANNELS, typename UINT>
		constexpr static bool enable_char() noexcept
		{
			return (!std::is_same<bool, UINT>::value) && (COUNT_CHANNELS * sizeof(UINT) >= sizeof(unsigned char));
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_char<COUNT_CHANNELS, UINT>()>::type>
		PYGMALION_INLINE static size_t impl(tag_char, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned char;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
			const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
			const std::array<SLICE, countSlices>& transformedSlices{ mergeChannels<UINT,SLICE,countSliceChannels>(sliceChannels) };
			constexpr const auto lambdaSlice = [](const SLICE bits, const size_t index)->size_t
			{
#if defined(PYGMALION_INTRINSICS_MSC) && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					return __popcnt16(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
				if constexpr (compiler::supports(compiler::flags::GNU))
					return __builtin_popcount(bits);
#endif
				return popcount_ref<SLICE, 0>(bits);
			};
			const std::array<size_t, countSlices> countsSlices{ base::transformChannels<countSlices,SLICE,size_t>(transformedSlices, lambdaSlice) };
			if constexpr (countOddChannels > 0)
			{
				const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
				const size_t countOdd{ impl<countOddChannels, UINT>(tag_best{},oddChannels,std::make_index_sequence<countOddChannels>{}) };
				return base::sumChannels<countSlices, 0, countSlices, size_t>(countsSlices) + countOdd;
			}
			else
				return base::sumChannels<countSlices, 0, countSlices, size_t>(countsSlices);
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_char<COUNT_CHANNELS, UINT>()>::type>
		static std::string name(tag_char, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned char;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countTransformedChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
			std::stringstream sstr;
			for (size_t slice = 0; slice < countSlices; slice++)
			{
#if defined(PYGMALION_INTRINSICS_MSC) && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					sstr << "MSC16 ";
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
						sstr << "GNU" << (sizeof(unsigned int) * CHAR_BIT) << " ";
					else
#endif
						sstr << "generic ";
				sstr << (sizeof(SLICE) * CHAR_BIT) << "bit";
				sstr << ((slice == countSlices - 1) ? "" : " | ");
			}
			if constexpr (countOddChannels > 0)
				sstr << " | " << name<countOddChannels, UINT>(tag_best{}, std::make_index_sequence<countOddChannels>{});
			return sstr.str();
		}

		template <size_t COUNT_CHANNELS, typename UINT>
		constexpr static bool enable_short() noexcept
		{
			return (!std::is_same<bool, UINT>::value) && (COUNT_CHANNELS * sizeof(UINT) >= sizeof(unsigned short));
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_short<COUNT_CHANNELS, UINT>()>::type>
		PYGMALION_INLINE static size_t impl(tag_short, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned short;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
			const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
			const std::array<SLICE, countSlices>& transformedSlices{ mergeChannels<UINT,SLICE,countSliceChannels>(sliceChannels) };
			constexpr const auto lambdaSlice = [](const SLICE bits, const size_t index)->size_t
			{
#if defined(PYGMALION_INTRINSICS_MSC) && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					return __popcnt16(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
				if constexpr (compiler::supports(compiler::flags::GNU))
					return __builtin_popcount(bits);
#endif
				return popcount_ref<SLICE, 0>(bits);
			};
			const std::array<size_t, countSlices> countsSlices{ base::transformChannels<countSlices,SLICE,size_t>(transformedSlices, lambdaSlice) };
			if constexpr (countOddChannels > 0)
			{
				const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
				const size_t countOdd{ impl<countOddChannels, UINT>(tag_best{},oddChannels,std::make_index_sequence<countOddChannels>{}) };
				return base::sumChannels<countSlices, 0, countSlices, size_t>(countsSlices) + countOdd;
			}
			else
				return base::sumChannels<countSlices, 0, countSlices, size_t>(countsSlices);
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_short<COUNT_CHANNELS, UINT>()>::type>
		static std::string name(tag_short, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned short;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countTransformedChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
			std::stringstream sstr;
			for (size_t slice = 0; slice < countSlices; slice++)
			{
#if defined(PYGMALION_INTRINSICS_MSC) && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					sstr << "MSC16 ";
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
						sstr << "GNU" << (sizeof(unsigned int) * CHAR_BIT) << " ";
					else
#endif
						sstr << "generic ";
				sstr << (sizeof(SLICE) * CHAR_BIT) << "bit";
				sstr << ((slice == countSlices - 1) ? "" : " | ");
			}
			if constexpr (countOddChannels > 0)
				sstr << " | " << name<countOddChannels, UINT>(tag_best{}, std::make_index_sequence<countOddChannels>{});
			return sstr.str();
		}

		template <size_t COUNT_CHANNELS, typename UINT>
		constexpr static bool enable_int() noexcept
		{
			return (!std::is_same<bool, UINT>::value) && (COUNT_CHANNELS * sizeof(UINT) >= sizeof(unsigned int));
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_int<COUNT_CHANNELS, UINT>()>::type>
		PYGMALION_INLINE static size_t impl(tag_int, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned int;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
			const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
			const std::array<SLICE, countSlices>& transformedSlices{ mergeChannels<UINT,SLICE,countSliceChannels>(sliceChannels) };
			constexpr const auto lambdaSlice = [](const SLICE bits, const size_t index)->size_t
			{
#if defined(PYGMALION_INTRINSICS_MSC) && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					return __popcnt(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
				if constexpr (compiler::supports(compiler::flags::GNU))
					return __builtin_popcount(bits);
#endif
				return popcount_ref<SLICE, 0>(bits);
			};
			const std::array<size_t, countSlices> countsSlices{ base::transformChannels<countSlices,SLICE,size_t>(transformedSlices, lambdaSlice) };
			if constexpr (countOddChannels > 0)
			{
				const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
				const size_t countOdd{ impl<countOddChannels, UINT>(tag_best{},oddChannels,std::make_index_sequence<countOddChannels>{}) };
				return base::sumChannels<countSlices, 0, countSlices, size_t>(countsSlices) + countOdd;
			}
			else
				return base::sumChannels<countSlices, 0, countSlices, size_t>(countsSlices);
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_int<COUNT_CHANNELS, UINT>()>::type>
		static std::string name(tag_int, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned int;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countTransformedChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
			std::stringstream sstr;
			for (size_t slice = 0; slice < countSlices; slice++)
			{
#if defined(PYGMALION_INTRINSICS_MSC) && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					sstr << "MSC32 ";
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
						sstr << "GNU" << (sizeof(unsigned int) * CHAR_BIT) << " ";
					else
#endif
						sstr << "generic ";
				sstr << (sizeof(SLICE) * CHAR_BIT) << "bit";
				sstr << ((slice == countSlices - 1) ? "" : " | ");
			}
			if constexpr (countOddChannels > 0)
				sstr << " | " << name<countOddChannels, UINT>(tag_best{}, std::make_index_sequence<countOddChannels>{});
			return sstr.str();
		}

		template <size_t COUNT_CHANNELS, typename UINT>
		constexpr static bool enable_long() noexcept
		{
			return (!std::is_same<bool, UINT>::value) && (COUNT_CHANNELS * sizeof(UINT) >= sizeof(unsigned long));
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_long<COUNT_CHANNELS, UINT>()>::type>
		PYGMALION_INLINE static size_t impl(tag_long, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned long;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
			const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
			const std::array<SLICE, countSlices>& transformedSlices{ mergeChannels<UINT,SLICE,countSliceChannels>(sliceChannels) };
			constexpr const auto lambdaSlice = [](const SLICE bits, const size_t index)->size_t
			{
#if defined(PYGMALION_INTRINSICS_MSC) && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					return __popcnt(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
				if constexpr (compiler::supports(compiler::flags::GNU))
					return __builtin_popcountl(bits);
#endif
				return popcount_ref<SLICE, 0>(bits);
			};
			const std::array<size_t, countSlices> countsSlices{ base::transformChannels<countSlices,SLICE,size_t>(transformedSlices, lambdaSlice) };
			if constexpr (countOddChannels > 0)
			{
				const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
				const size_t countOdd{ impl<countOddChannels, UINT>(tag_best{},oddChannels,std::make_index_sequence<countOddChannels>{}) };
				return base::sumChannels<countSlices, 0, countSlices, size_t>(countsSlices) + countOdd;
			}
			else
				return base::sumChannels<countSlices, 0, countSlices, size_t>(countsSlices);
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_long<COUNT_CHANNELS, UINT>()>::type>
		static std::string name(tag_long, compiler::tag_generic, cpu::tag_generic, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned long;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countTransformedChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
			std::stringstream sstr;
			for (size_t slice = 0; slice < countSlices; slice++)
			{
#if defined(PYGMALION_INTRINSICS_MSC) && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					sstr << "MSC32 ";
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
						sstr << "GNU" << (sizeof(unsigned long) * CHAR_BIT) << " ";
					else
#endif
						sstr << "generic ";
				sstr << (sizeof(SLICE) * CHAR_BIT) << "bit";
				sstr << ((slice == countSlices - 1) ? "" : " | ");
			}
			if constexpr (countOddChannels > 0)
				sstr << " | " << name<countOddChannels, UINT>(tag_best{}, std::make_index_sequence<countOddChannels>{});
			return sstr.str();
		}

		template <size_t COUNT_CHANNELS, typename UINT>
		constexpr static bool enable_long_long() noexcept
		{
			return (!std::is_same<bool, UINT>::value) && (COUNT_CHANNELS * sizeof(UINT) >= sizeof(unsigned long long));
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_long_long<COUNT_CHANNELS, UINT>()>::type>
		PYGMALION_INLINE static size_t impl(tag_long_long, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned long long;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
			const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
			const std::array<SLICE, countSlices>& transformedSlices{ mergeChannels<UINT,SLICE,countSliceChannels>(sliceChannels) };
			constexpr const auto lambdaSlice = [](const SLICE bits, const size_t index)->size_t
			{
#if defined(PYGMALION_INTRINSICS_MSC) && defined(PYGMALION_CPU_X64)
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X64))
					return __popcnt64(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
				if constexpr (compiler::supports(compiler::flags::GNU))
					return __builtin_popcountll(bits);
#endif
#if defined(PYGMALION_INTRINSICS_MSC) && defined(PYGMALION_CPU_X86)
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
					return __popcnt(*(reinterpret_cast<const unsigned int*>(&bits) + 1)) + __popcnt(*reinterpret_cast<const unsigned int*>(&bits));
#endif
				return popcount_ref<SLICE, 0>(bits);
			};
			const std::array<size_t, countSlices> countsSlices{ base::transformChannels<countSlices,SLICE,size_t>(transformedSlices, lambdaSlice) };
			if constexpr (countOddChannels > 0)
			{
				const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
				const size_t countOdd{ impl<countOddChannels, UINT>(tag_best{},oddChannels,std::make_index_sequence<countOddChannels>{}) };
				return base::sumChannels<countSlices, 0, countSlices, size_t>(countsSlices) + countOdd;
			}
			else
				return base::sumChannels<countSlices, 0, countSlices, size_t>(countsSlices);
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_long_long<COUNT_CHANNELS, UINT>()>::type>
		static std::string name(tag_long_long, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned long long;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countTransformedChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
			std::stringstream sstr;
			for (size_t slice = 0; slice < countSlices; slice++)
			{
#if defined(PYGMALION_INTRINSICS_MSC) && defined(PYGMALION_CPU_X64)
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X64))
					sstr << "MSC64 ";
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
						sstr << "GNU" << (sizeof(unsigned long long) * CHAR_BIT) << " ";
					else
#endif
#if defined(PYGMALION_INTRINSICS_MSC) && defined(PYGMALION_CPU_X86)
						if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
							sstr << "2xMSC32 ";
						else
#endif
							sstr << "generic ";
				sstr << (sizeof(SLICE) * CHAR_BIT) << "bit";
				sstr << ((slice == countSlices - 1) ? "" : " | ");
			}
			if constexpr (countOddChannels > 0)
				sstr << " | " << name<countOddChannels, UINT>(tag_best{}, std::make_index_sequence<countOddChannels>{});
			return sstr.str();
		}

	public:
		template<size_t COUNT_BITS>
		using refType = typename detail::popcnt_traits<COUNT_BITS>::refType;
		template<size_t COUNT_BITS>
		static size_t reference(const refType<COUNT_BITS> R) noexcept
		{
			return popcnt::popcount_ref<refType<COUNT_BITS>, 0>(R);
		}

		template <size_t COUNT_CHANNELS, typename UINT>
		PYGMALION_INLINE static size_t implementation(const std::array<UINT, COUNT_CHANNELS>& bits) noexcept
		{
			constexpr const compiler::flags comp{ compiler::computeFlags() };
			constexpr const cpu::flags cpu{ cpu::computeFlags() };
			if constexpr (std::is_same<bool, UINT>())
				return impl<COUNT_CHANNELS, bool>(tag_best{}, bits, std::make_index_sequence<COUNT_CHANNELS>{});
			else
			{
				constexpr const size_t countChunks{ countSplitChannels<UINT, unsigned char, COUNT_CHANNELS>() };
				return impl<countChunks, unsigned char>(tag_best{}, splitChannels<UINT, unsigned char, COUNT_CHANNELS>({ bits }), std::make_index_sequence<countChunks>{});
			}
		}

		template <size_t COUNT_CHANNELS, typename UINT>
		static std::string implementationName() noexcept
		{
			constexpr const compiler::flags comp{ compiler::computeFlags() };
			constexpr const cpu::flags cpu{ cpu::computeFlags() };
			if constexpr (std::is_same<bool, UINT>())
				return "[" + name<COUNT_CHANNELS, bool>(tag_best{}, std::make_index_sequence<COUNT_CHANNELS>{}) + "]";
			else
			{
				constexpr const size_t countChunks{ countSplitChannels<UINT, unsigned char, COUNT_CHANNELS>() };
				return "[" + name<countChunks, unsigned char>(tag_best{}, std::make_index_sequence<countChunks>{}) + "]";
			}
		}

	};

	namespace detail
	{
		template<size_t COUNT_BITS, typename T>
		size_t popcnt_reference(const T R) noexcept
		{
			return popcnt::reference<COUNT_BITS>(R);
		}
	}
}