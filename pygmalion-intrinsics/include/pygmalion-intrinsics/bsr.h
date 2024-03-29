namespace pygmalion::intrinsics
{
	namespace detail
	{
		template<size_t COUNT_BITS, typename T>
		bool bsr_reference(const T R, size_t& bit) noexcept;

		template<size_t COUNT_BITS, typename = typename std::enable_if<true>::type>
		struct bsr_traits {};

		template<size_t COUNT_BITS>
		struct bsr_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS <= 64) && (COUNT_BITS > 32)>::type>
		{
			using refType = std::uint64_t;
			using intType = refType;
			static bool reference(const refType& bits, size_t& bit) noexcept
			{
				for (size_t k = 0; k < COUNT_BITS; k++)
				{
					size_t i{ COUNT_BITS - 1 - k };
					if (bits & static_cast<refType>(refType(1) << i))
					{
						bit = i;
						return true;
					}
				}
				return false;
			}
			static bool baseline(const refType& bits, size_t& bit) noexcept
			{
#if defined(PYGMALION_INTRINSICS_MSC)  &&defined(PYGMALION_CPU_X64)
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X64))
				{
					unsigned long idx{ 0 };
					if (_BitScanReverse64(&idx, bits))
					{
						bit = static_cast<size_t>(idx);
						return true;
					}
					else
						return false;
				}
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
					{
						if (bits)
						{
							if constexpr (sizeof(bits) <= sizeof(unsigned int))
								bit = static_cast<size_t>(sizeof(unsigned int) * CHAR_BIT - 1 - __builtin_clz(bits));
							else if constexpr (sizeof(bits) <= sizeof(unsigned long))
								bit = static_cast<size_t>(sizeof(unsigned long) * CHAR_BIT - 1 - __builtin_clzl(bits));
							else if constexpr (sizeof(bits) <= sizeof(unsigned long long))
								bit = static_cast<size_t>(sizeof(unsigned long long) * CHAR_BIT - 1 - __builtin_clzll(bits));
							return true;
						}
						else
							return false;
					}
					else
#endif
#if defined(PYGMALION_INTRINSICS_MSC) &&defined(PYGMALION_CPU_X86)
						if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
						{
							unsigned long idx{ 0 };
							unsigned char ret = _BitScanReverse(&idx, static_cast<unsigned long>((bits & std::uint64_t(0xFFFFFFFF00000000)) >> 32));
							if (ret)
							{
								bit = static_cast<size_t>(idx + 32);
								return true;
							}
							ret = _BitScanReverse(&idx, static_cast<unsigned long>(bits & std::uint64_t(0x00000000FFFFFFFF)));
							if (ret)
							{
								bit = static_cast<size_t>(idx);
								return true;
							}
							else
								return false;
						}
						else
#endif
							return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
			static bool generic(const refType& bits, size_t& bit)
			{
				return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
		};

		template<size_t COUNT_BITS>
		struct bsr_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS <= 32) && (COUNT_BITS > 16)>::type>
		{
			using refType = std::uint32_t;
			using intType = refType;
			static bool reference(const refType& bits, size_t& bit) noexcept
			{
				for (size_t k = 0; k < COUNT_BITS; k++)
				{
					size_t i{ COUNT_BITS - 1 - k };
					if (bits & static_cast<refType>(refType(1) << i))
					{
						bit = i;
						return true;
					}
				}
				return false;
			}
			static bool baseline(const refType& bits, size_t& bit) noexcept
			{
#if defined(PYGMALION_INTRINSICS_MSC)  && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				{
					unsigned long idx{ 0 };
					if (_BitScanReverse(&idx, bits))
					{
						bit = static_cast<size_t>(idx);
						return true;
					}
					else
						return false;
				}
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
					{
						if (bits)
						{
							if constexpr (sizeof(bits) <= sizeof(unsigned int))
								bit = static_cast<size_t>(sizeof(unsigned int) * CHAR_BIT - 1 - __builtin_clz(bits));
							else if constexpr (sizeof(bits) <= sizeof(unsigned long))
								bit = static_cast<size_t>(sizeof(unsigned long) * CHAR_BIT - 1 - __builtin_clzl(bits));
							else if constexpr (sizeof(bits) <= sizeof(unsigned long long))
								bit = static_cast<size_t>(sizeof(unsigned long long) * CHAR_BIT - 1 - __builtin_clzll(bits));
							return true;
						}
						else
							return false;
					}
					else
#endif
						return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
			static bool generic(const refType& bits, size_t& bit)
			{
				return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
		};

		template<size_t COUNT_BITS>
		struct bsr_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS <= 16) && (COUNT_BITS > 8)>::type>
		{
			using refType = std::uint16_t;
			using intType = refType;
			static bool reference(const refType& bits, size_t& bit) noexcept
			{
				for (size_t k = 0; k < COUNT_BITS; k++)
				{
					size_t i{ COUNT_BITS - 1 - k };
					if (bits & static_cast<refType>(refType(1) << i))
					{
						bit = i;
						return true;
					}
				}
				return false;
			}
			static bool baseline(const refType& bits, size_t& bit) noexcept
			{
#if defined(PYGMALION_INTRINSICS_MSC)  && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				{
					unsigned long idx{ 0 };
					if (_BitScanReverse(&idx, bits))
					{
						bit = static_cast<size_t>(idx);
						return true;
					}
					else
						return false;
				}
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
					{
						if (bits)
						{
							if constexpr (sizeof(bits) <= sizeof(unsigned int))
								bit = static_cast<size_t>(sizeof(unsigned int) * CHAR_BIT - 1 - __builtin_clz(bits));
							else if constexpr (sizeof(bits) <= sizeof(unsigned long))
								bit = static_cast<size_t>(sizeof(unsigned long) * CHAR_BIT - 1 - __builtin_clzl(bits));
							else if constexpr (sizeof(bits) <= sizeof(unsigned long long))
								bit = static_cast<size_t>(sizeof(unsigned long long) * CHAR_BIT - 1 - __builtin_clzll(bits));
							return true;
						}
						else
							return false;
					}
					else
#endif
						return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
			static bool generic(const refType& bits, size_t& bit)
			{
				return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
		};

		template<size_t COUNT_BITS>
		struct bsr_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS <= 8) && (COUNT_BITS > 1)>::type>
		{
			using refType = std::uint8_t;
			using intType = refType;
			static bool reference(const refType& bits, size_t& bit) noexcept
			{
				for (size_t k = 0; k < COUNT_BITS; k++)
				{
					size_t i{ COUNT_BITS - 1 - k };
					if (bits & static_cast<refType>(refType(1) << i))
					{
						bit = i;
						return true;
					}
				}
				return false;
			}
			static bool baseline(const refType& bits, size_t& bit) noexcept
			{
#if defined(PYGMALION_INTRINSICS_MSC)  && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				{
					unsigned long idx{ 0 };
					if (_BitScanReverse(&idx, bits))
					{
						bit = static_cast<size_t>(idx);
						return true;
					}
					else
						return false;
				}
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
					{
						if (bits)
						{
							bit = static_cast<size_t>(sizeof(unsigned int) * CHAR_BIT - 1 - __builtin_clz(bits));
							return true;
						}
						else
							return false;
					}
					else
#endif
						return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
			static bool generic(const refType& bits, size_t& bit)
			{
				return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
		};

		template<size_t COUNT_BITS>
		struct bsr_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS == 1)>::type>
		{
			using refType = bool;
			using intType = std::uint8_t;
			static bool reference(const refType& bits, size_t& bit) noexcept
			{
				if (bits)
				{
					bit = 0;
					return true;
				}
				else
					return false;
			}
			static bool baseline(const refType& bits, size_t& bit) noexcept
			{
				return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
			static bool generic(const refType& bits, size_t& bit)
			{
				return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
		};

		template<size_t COUNT_BITS>
		struct bsr_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS == 0)>::type>
		{
			using refType = std::uint8_t;
			using intType = std::uint8_t;
			static bool reference(const refType& bits, size_t& bit) noexcept
			{
				return false;
			}
			static bool baseline(const refType& bits, size_t& bit) noexcept
			{
				return false;
			}
			static bool generic(const refType& bits, size_t& bit)
			{
				return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
		};


		template<size_t COUNT_BITS>
		struct bsr_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS > 64)>::type>
		{
			using refType = std::uintmax_t;
			using intType = refType;
			static bool reference(const refType& bits, size_t& bit) noexcept
			{
				for (size_t k = 0; k < COUNT_BITS; k++)
				{
					size_t i{ COUNT_BITS - 1 - k };
					if (bits & static_cast<refType>(refType(1) << i))
					{
						bit = i;
						return true;
					}
				}
				return false;
			}
			static bool baseline(const refType& bits, size_t& bit) noexcept
			{
#if defined(PYGMALION_INTRINSICS_GNU)
				if constexpr (compiler::supports(compiler::flags::GNU))
				{
					if (bits)
					{
						if constexpr (sizeof(bits) <= sizeof(unsigned int))
						{
							bit = static_cast<size_t>(sizeof(unsigned int) * CHAR_BIT - 1 - __builtin_clz(bits));
							return true;
						}
						else if constexpr (sizeof(bits) <= sizeof(unsigned long))
						{
							bit = static_cast<size_t>(sizeof(unsigned long) * CHAR_BIT - 1 - __builtin_clzl(bits));
							return true;
						}
						else if constexpr (sizeof(bits) <= sizeof(unsigned long long))
						{
							bit = static_cast<size_t>(sizeof(unsigned long long) * CHAR_BIT - 1 - __builtin_clzll(bits));
							return true;
						}
						else
						{
							bit = popcnt::implementation<1, refType>({ static_cast<refType>((bits & -bits) - refType(1)) });
						}
					}
					else
						return false;
				}
				else
#endif
					return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
			static bool generic(const refType& bits, size_t& bit)
			{
				return bsr_reference<COUNT_BITS, refType>(bits, bit);
			}
		};

	}

	class bsr :
		protected base
	{
	private:
		template <typename T>
		static bool bsr_ref(T bits, size_t& idx) noexcept
		{
			if (!bits)
				return false;
			else
			{
				if constexpr (std::is_same<bool, T>::value)
				{
					idx = 0;
					return true;
				}
				else
				{
					idx = 0;
					size_t shift{ sizeof(T) * CHAR_BIT };
					T mask{ static_cast<T>(~T(0)) };
					while (shift)
					{
						shift >>= 1;
						mask >>= shift;
						if (bits > mask)
						{
							bits >>= shift;
							idx += shift;
						}
					}
					return true;
				}
			}
		}

		template <size_t COUNT_CHANNELS, typename UINT>
		constexpr static bool enable_empty() noexcept
		{
			return COUNT_CHANNELS <= 0;
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_empty<COUNT_CHANNELS, UINT>()>::type>
		PYGMALION_INLINE static bool impl(tag_best, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
		{
			return false;
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
		PYGMALION_INLINE static bool impl(tag_bool, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
		{
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned char) };
			constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned char) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
			const std::array<unsigned char, countSlices>& transformedSlices{ *reinterpret_cast<const std::array<unsigned char, countSlices>*>(&bits) };
			const std::array<UINT, countOddChannels>& oddChannels{ *(reinterpret_cast<const std::array<UINT, countOddChannels>*>(&bits) + countTransformedChannels) };
			for (size_t k = 0; k < countSlices; k++)
			{
				const size_t i{ countSlices - 1 - k };
				if (transformedSlices[i])
				{
					bit = i;
					return true;
				}
			}
			if constexpr (countOddChannels > 0)
			{
				if (impl<countOddChannels, UINT>(tag_best{}, oddChannels, bit, std::make_index_sequence<countOddChannels>{}))
				{
					bit += countSlices;
					return true;
				}
				else
					return false;
			}
			else
				return false;
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
		PYGMALION_INLINE static bool impl(tag_char, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned char;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
			if constexpr (countOddChannels > 0)
			{
				const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
				if (impl<countOddChannels, UINT>(tag_best{}, oddChannels, bit, std::make_index_sequence<countOddChannels>{}))
				{
					bit += countSlices * sizeof(SLICE) * CHAR_BIT;
					return true;
				}
			}
			const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
			const std::array<SLICE, countSlices> transformedSlices{ mergeChannelsOrderly<UINT,SLICE,countSliceChannels>(sliceChannels) };
			for (size_t k = 0; k < countSlices; k++)
			{
				const size_t i{ countSlices - 1 - k };
#if defined(PYGMALION_INTRINSICS_MSC)  && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				{
					unsigned long idx{ 0 };
					if (_BitScanReverse(&idx, transformedSlices[i]))
					{
						bit = static_cast<size_t>(idx);
						bit += i * sizeof(SLICE) * CHAR_BIT;
						return true;
					}
				}
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
					{
						if (transformedSlices[i])
						{
							bit = static_cast<size_t>(sizeof(unsigned int) * CHAR_BIT - 1 - __builtin_clz(static_cast<unsigned int>(transformedSlices[i])));
							bit += i * sizeof(SLICE) * CHAR_BIT;
							return true;
						}
					}
					else
#endif
						if (bsr::bsr_ref(transformedSlices[i], bit))
						{
							bit += i * sizeof(SLICE) * CHAR_BIT;
							return true;
						}
			}
			return false;
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
		constexpr static bool enable_short() noexcept
		{
			return (!std::is_same<bool, UINT>::value) && (COUNT_CHANNELS * sizeof(UINT) >= sizeof(unsigned short));
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_short<COUNT_CHANNELS, UINT>()>::type>
		PYGMALION_INLINE static bool impl(tag_short, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned short;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
			if constexpr (countOddChannels > 0)
			{
				const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
				if (impl<countOddChannels, UINT>(tag_best{}, oddChannels, bit, std::make_index_sequence<countOddChannels>{}))
				{
					bit += countSlices * sizeof(SLICE) * CHAR_BIT;
					return true;
				}
			}
			const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
			const std::array<SLICE, countSlices> transformedSlices{ mergeChannelsOrderly<UINT,SLICE,countSliceChannels>(sliceChannels) };
			for (size_t k = 0; k < countSlices; k++)
			{
				const size_t i{ countSlices - 1 - k };
#if defined(PYGMALION_INTRINSICS_MSC)  && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				{
					unsigned long idx{ 0 };
					if (_BitScanReverse(&idx, transformedSlices[i]))
					{
						bit = static_cast<size_t>(idx);
						bit += i * sizeof(SLICE) * CHAR_BIT;
						return true;
					}
				}
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
					{
						if (transformedSlices[i])
						{
							bit = static_cast<size_t>(sizeof(unsigned int) * CHAR_BIT - 1 - __builtin_clz(static_cast<unsigned int>(transformedSlices[i])));
							bit += i * sizeof(SLICE) * CHAR_BIT;
							return true;
						}
					}
					else
#endif
						if (bsr::bsr_ref(transformedSlices[i], bit))
						{
							bit += i * sizeof(SLICE) * CHAR_BIT;
							return true;
						}
			}
			return false;
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
		constexpr static bool enable_int() noexcept
		{
			return (!std::is_same<bool, UINT>::value) && (COUNT_CHANNELS * sizeof(UINT) >= sizeof(unsigned int));
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_int<COUNT_CHANNELS, UINT>()>::type>
		PYGMALION_INLINE static bool impl(tag_int, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned int;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
			if constexpr (countOddChannels > 0)
			{
				const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
				if (impl<countOddChannels, UINT>(tag_best{}, oddChannels, bit, std::make_index_sequence<countOddChannels>{}))
				{
					bit += countSlices * sizeof(SLICE) * CHAR_BIT;
					return true;
				}
			}
			const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
			const std::array<SLICE, countSlices> transformedSlices{ mergeChannelsOrderly<UINT,SLICE,countSliceChannels>(sliceChannels) };
			for (size_t k = 0; k < countSlices; k++)
			{
				const size_t i{ countSlices - 1 - k };
#if defined(PYGMALION_INTRINSICS_MSC)  && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				{
					unsigned long idx{ 0 };
					if (_BitScanReverse(&idx, transformedSlices[i]))
					{
						bit = static_cast<size_t>(idx);
						bit += i * sizeof(SLICE) * CHAR_BIT;
						return true;
					}
				}
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
					{
						if (transformedSlices[i])
						{
							bit = static_cast<size_t>(sizeof(unsigned int) * CHAR_BIT - 1 - __builtin_clz(transformedSlices[i]));
							bit += i * sizeof(SLICE) * CHAR_BIT;
							return true;
						}
					}
					else
#endif
						if (bsr::bsr_ref(transformedSlices[i], bit))
						{
							bit += i * sizeof(SLICE) * CHAR_BIT;
							return true;
						}
			}
			return false;
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
		PYGMALION_INLINE static bool impl(tag_long, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned long;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
			if constexpr (countOddChannels > 0)
			{
				const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
				if (impl<countOddChannels, UINT>(tag_best{}, oddChannels, bit, std::make_index_sequence<countOddChannels>{}))
				{
					bit += countSlices * sizeof(SLICE) * CHAR_BIT;
					return true;
				}
			}
			const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
			const std::array<SLICE, countSlices> transformedSlices{ mergeChannelsOrderly<UINT,SLICE,countSliceChannels>(sliceChannels) };
			for (size_t k = 0; k < countSlices; k++)
			{
				const size_t i{ countSlices - 1 - k };
#if defined(PYGMALION_INTRINSICS_MSC)  && (defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				{
					unsigned long idx{ 0 };
					if (_BitScanReverse(&idx, transformedSlices[i]))
					{
						bit = static_cast<size_t>(idx);
						bit += i * sizeof(SLICE) * CHAR_BIT;
						return true;
					}
				}
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
					{
						if (transformedSlices[i])
						{
							bit = static_cast<size_t>(sizeof(unsigned long) * CHAR_BIT - 1 - __builtin_clzl(transformedSlices[i]));
							bit += i * sizeof(SLICE) * CHAR_BIT;
							return true;
						}
					}
					else
#endif
						if (bsr::bsr_ref(transformedSlices[i], bit))
						{
							bit += i * sizeof(SLICE) * CHAR_BIT;
							return true;
						}
			}
			return false;
		}

		template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_long<COUNT_CHANNELS, UINT>()>::type>
		static std::string name(tag_long, std::index_sequence<CHANNEL...>) noexcept
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
		PYGMALION_INLINE static bool impl(tag_long_long, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
		{
			using SLICE = unsigned long long;
			constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
			constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
			constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
			if constexpr (countOddChannels > 0)
			{
				const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
				if (impl<countOddChannels, UINT>(tag_best{}, oddChannels, bit, std::make_index_sequence<countOddChannels>{}))
				{
					bit += countSlices * sizeof(SLICE) * CHAR_BIT;
					return true;
				}
			}
			const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
			const std::array<SLICE, countSlices> transformedSlices{ mergeChannelsOrderly<UINT,SLICE,countSliceChannels>(sliceChannels) };
			for (size_t k = 0; k < countSlices; k++)
			{
				const size_t i{ countSlices - 1 - k };
#if defined(PYGMALION_INTRINSICS_MSC) &&defined(PYGMALION_CPU_X64)
				if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X64))
				{
					unsigned long idx{ 0 };
					if (_BitScanReverse64(&idx, transformedSlices[i]))
					{
						bit = static_cast<size_t>(idx);
						bit += i * sizeof(SLICE) * CHAR_BIT;
						return true;
					}
				}
				else
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					if constexpr (compiler::supports(compiler::flags::GNU))
					{
						if (transformedSlices[i])
						{
							bit = static_cast<size_t>(sizeof(unsigned long long) * CHAR_BIT - 1 - __builtin_clzll(transformedSlices[i]));
							bit += i * sizeof(SLICE) * CHAR_BIT;
							return true;
						}
					}
					else
#endif
#if defined(PYGMALION_INTRINSICS_MSC) &&defined(PYGMALION_CPU_X86)
						if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
						{
							unsigned long idx{ 0 };
							unsigned char ret = _BitScanReverse(&idx, static_cast<unsigned long>((transformedSlices[i] & std::uint64_t(0xFFFFFFFF00000000)) >> 32));
							if (ret)
							{
								bit = static_cast<size_t>(idx + 32);
								bit += i * sizeof(SLICE) * CHAR_BIT;
								return true;
							}
							ret = _BitScanReverse(&idx, static_cast<unsigned long>(transformedSlices[i] & std::uint64_t(0x00000000FFFFFFFF)));
							if (ret)
							{
								bit = static_cast<size_t>(idx);
								bit += i * sizeof(SLICE) * CHAR_BIT;
								return true;
							}
						}
						else
#endif
							if (bsr::bsr_ref(transformedSlices[i], bit))
							{
								bit += i * sizeof(SLICE) * CHAR_BIT;
								return true;
							}
			}
			return false;
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
#if defined(PYGMALION_INTRINSICS_MSC) &&defined(PYGMALION_CPU_X64)
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
		using refType = typename detail::bsr_traits<COUNT_BITS>::refType;
		template<size_t COUNT_BITS>
		static bool reference(const refType<COUNT_BITS> R, size_t& bit) noexcept
		{
			return bsr::bsr_ref<refType<COUNT_BITS>>(R, bit);
		}

		template <size_t COUNT_CHANNELS, typename UINT>
		PYGMALION_INLINE static bool implementation(const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit) noexcept
		{
			constexpr const compiler::flags comp{ compiler::computeFlags() };
			constexpr const cpu::flags cpu{ cpu::computeFlags() };
			return impl<COUNT_CHANNELS, UINT>(tag_best{}, bits, bit, std::make_index_sequence<COUNT_CHANNELS>{});
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
		bool bsr_reference(const T R, size_t& bit) noexcept
		{
			return bsr::reference<COUNT_BITS>(R, bit);
		}
	}
}