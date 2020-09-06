class popcnt :
	protected detail::base
{
private:
	template <typename T, int iteration>
	constexpr static T popcount_ref(const T bits) noexcept
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

	template <size_t COUNT_CHANNELS, typename UINT>
	constexpr static bool enable_empty() noexcept
	{
		return COUNT_CHANNELS <= 0;
	}

	template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_empty<COUNT_CHANNELS, UINT>()>::type>
	constexpr static size_t impl(tag_best, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
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
	constexpr static size_t impl(tag_bool, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
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
		const std::array<size_t, countSlices> countsSlices{ transform_array_n<countSlices,size_t>(transformedSlices, lambdaSlice) };
		if constexpr (countOddChannels > 0)
		{
			const size_t countOdd{ impl<countOddChannels, UINT>(tag_best{},oddChannels,std::make_index_sequence<countOddChannels>{}) };
			return sum_array_n<countSlices, 0, countSlices, size_t>(countsSlices) + countOdd;
		}
		else
			return sum_array_n<countSlices, 0, countSlices, size_t>(countsSlices);
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
	constexpr static size_t impl(tag_char, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
	{
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned char) };
		constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned char) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
		const std::array<unsigned char, countSlices>& transformedSlices{ *reinterpret_cast<const std::array<unsigned char, countSlices>*>(&bits) };
		const std::array<UINT, countOddChannels>& oddChannels{ *(reinterpret_cast<const std::array<UINT, countOddChannels>*>(&bits) + countTransformedChannels) };
		constexpr const auto lambdaSlice = [](const UINT bits, const size_t index)->size_t
		{
#if defined(PYGMALION_INTRINSICS_MSC) && defined(PYGMALION_CPU_X86)
			if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				return __popcnt16(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
			if constexpr (compiler::supports(compiler::flags::GNU))
				return __builtin_popcount(bits);
#endif
			return popcount_ref<unsigned char, 0>(bits);
		};
		const std::array<size_t, countSlices> countsSlices{ transform_array_n<countSlices,size_t>(transformedSlices, lambdaSlice) };
		if constexpr (countOddChannels > 0)
		{
			const size_t countOdd{ impl<countOddChannels, UINT>(tag_best{},oddChannels,std::make_index_sequence<countOddChannels>{}) };
			return sum_array_n<countSlices, 0, countSlices, size_t>(countsSlices) + countOdd;
		}
		else
			return sum_array_n<countSlices, 0, countSlices, size_t>(countsSlices);
	}

	template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_char<COUNT_CHANNELS, UINT>()>::type>
	static std::string name(tag_char, std::index_sequence<CHANNEL...>) noexcept
	{
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned char) };
		constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned char) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
		std::stringstream sstr;
		for (size_t slice = 0; slice < countSlices; slice++)
		{
#if defined(PYGMALION_INTRINSICS_MSC) && defined(PYGMALION_CPU_X86)
			if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				sstr << "MSC16 ";
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
			if constexpr (compiler::supports(compiler::flags::GNU))
				sstr << "GNU" << (sizeof(unsigned int) * CHAR_BIT) << " ";
#endif
			sstr << (sizeof(unsigned char) * CHAR_BIT) << "bit";
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
	constexpr static size_t impl(tag_short, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
	{
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned short) };
		constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned short) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
		const std::array<unsigned short, countSlices>& transformedSlices{ *reinterpret_cast<const std::array<unsigned short, countSlices>*>(&bits) };
		const std::array<UINT, countOddChannels>& oddChannels{ *(reinterpret_cast<const std::array<UINT, countOddChannels>*>(&bits) + countTransformedChannels) };
		constexpr const auto lambdaSlice = [](const UINT bits, const size_t index)->size_t
		{
#if defined(PYGMALION_INTRINSICS_MSC) 
			if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				return __popcnt16(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
			if constexpr (compiler::supports(compiler::flags::GNU))
				return __builtin_popcount(bits);
#endif
			return popcount_ref<unsigned short, 0>(bits);
		};
		const std::array<size_t, countSlices> countsSlices{ transform_array_n<countSlices,size_t>(transformedSlices, lambdaSlice) };
		if constexpr (countOddChannels > 0)
		{
			const size_t countOdd{ impl<countOddChannels, UINT>(tag_best{},oddChannels,std::make_index_sequence<countOddChannels>{}) };
			return sum_array_n<countSlices, 0, countSlices, size_t>(countsSlices) + countOdd;
		}
		else
			return sum_array_n<countSlices, 0, countSlices, size_t>(countsSlices);
		}

	template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_short<COUNT_CHANNELS, UINT>()>::type>
	static std::string name(tag_short, std::index_sequence<CHANNEL...>) noexcept
	{
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned short) };
		constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned short) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
		std::stringstream sstr;
		for (size_t slice = 0; slice < countSlices; slice++)
		{
#if defined(PYGMALION_INTRINSICS_MSC) 
			if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				sstr << "MSC16 ";
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
			if constexpr (compiler::supports(compiler::flags::GNU))
				sstr << "GNU" << (sizeof(unsigned int) * CHAR_BIT) << " ";
#endif
			sstr << (sizeof(unsigned short) * CHAR_BIT) << "bit";
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
	constexpr static size_t impl(tag_int, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
	{
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned int) };
		constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned int) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
		const std::array<unsigned int, countSlices>& transformedSlices{ *reinterpret_cast<const std::array<unsigned int, countSlices>*>(&bits) };
		const std::array<UINT, countOddChannels>& oddChannels{ *(reinterpret_cast<const std::array<UINT, countOddChannels>*>(&bits) + countTransformedChannels) };
		constexpr const auto lambdaSlice = [](const UINT bits, const size_t index)->size_t
		{
#if defined(PYGMALION_INTRINSICS_MSC) 
			if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				return __popcnt(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
			if constexpr (compiler::supports(compiler::flags::GNU))
				return __builtin_popcount(bits);
#endif
			return popcount_ref<unsigned int, 0>(bits);
		};
		const std::array<size_t, countSlices> countsSlices{ transform_array_n<countSlices,size_t>(transformedSlices, lambdaSlice) };
		if constexpr (countOddChannels > 0)
		{
			const size_t countOdd{ impl<countOddChannels, UINT>(tag_best{},oddChannels,std::make_index_sequence<countOddChannels>{}) };
			return sum_array_n<countSlices, 0, countSlices, size_t>(countsSlices) + countOdd;
		}
		else
			return sum_array_n<countSlices, 0, countSlices, size_t>(countsSlices);
		}

	template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_int<COUNT_CHANNELS, UINT>()>::type>
	static std::string name(tag_int, std::index_sequence<CHANNEL...>) noexcept
	{
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned int) };
		constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned int) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
		std::stringstream sstr;
		for (size_t slice = 0; slice < countSlices; slice++)
		{
#if defined(PYGMALION_INTRINSICS_MSC)
			if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				sstr << "MSC32 ";
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
			if constexpr (compiler::supports(compiler::flags::GNU))
				sstr << "GNU" << (sizeof(unsigned int) * CHAR_BIT) << " ";
#endif
			sstr << (sizeof(unsigned int) * CHAR_BIT) << "bit";
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
	constexpr static size_t impl(tag_long, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
	{
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned long) };
		constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned long) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
		const std::array<unsigned long, countSlices>& transformedSlices{ *reinterpret_cast<const std::array<unsigned long, countSlices>*>(&bits) };
		const std::array<UINT, countOddChannels>& oddChannels{ *(reinterpret_cast<const std::array<UINT, countOddChannels>*>(&bits) + countTransformedChannels) };
		constexpr const auto lambdaSlice = [](const UINT bits, const size_t index)->size_t
		{
#if defined(PYGMALION_INTRINSICS_MSC)
			if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				return __popcnt(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
			if constexpr (compiler::supports(compiler::flags::GNU))
				return __builtin_popcountl(bits);
#endif
			return popcount_ref<unsigned long, 0>(bits);
		};
		const std::array<size_t, countSlices> countsSlices{ transform_array_n<countSlices,size_t>(transformedSlices, lambdaSlice) };
		if constexpr (countOddChannels > 0)
		{
			const size_t countOdd{ impl<countOddChannels, UINT>(tag_best{},oddChannels,std::make_index_sequence<countOddChannels>{}) };
			return sum_array_n<countSlices, 0, countSlices, size_t>(countsSlices) + countOdd;
		}
		else
			return sum_array_n<countSlices, 0, countSlices, size_t>(countsSlices);
		}

	template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_long<COUNT_CHANNELS, UINT>()>::type>
	static std::string name(tag_long, compiler::tag_generic, cpu::tag_generic, std::index_sequence<CHANNEL...>) noexcept
	{
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned long) };
		constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned long) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
		std::stringstream sstr;
		for (size_t slice = 0; slice < countSlices; slice++)
		{
#if defined(PYGMALION_INTRINSICS_MSC)
			if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				sstr << "MSC32 ";
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
			if constexpr (compiler::supports(compiler::flags::GNU))
				sstr << "GNU" << (sizeof(unsigned long) * CHAR_BIT) << " ";
#endif
			sstr << (sizeof(unsigned long) * CHAR_BIT) << "bit";
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
	constexpr static size_t impl(tag_long_long, const std::array<UINT, COUNT_CHANNELS>& bits, std::index_sequence<CHANNEL...>) noexcept
	{
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned long long) };
		constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned long long) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
		const std::array<unsigned long long, countSlices>& transformedSlices{ *reinterpret_cast<const std::array<unsigned long long, countSlices>*>(&bits) };
		const std::array<UINT, countOddChannels>& oddChannels{ *(reinterpret_cast<const std::array<UINT, countOddChannels>*>(&bits) + countTransformedChannels) };
		constexpr const auto lambdaSlice = [](const UINT bits, const size_t index)->size_t
		{
#if defined(PYGMALION_INTRINSICS_MSC)
			if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X64))
				return __popcnt64(bits);
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
			if constexpr (compiler::supports(compiler::flags::GNU))
				return __builtin_popcountll(bits);
#endif
#if defined(PYGMALION_INTRINSICS_MSC)
			if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				return __popcnt(*(reinterpret_cast<const unsigned int*>(&bits) + 1)) + __popcnt(*reinterpret_cast<const unsigned int*>(&bits));
#endif
			return popcount_ref<unsigned long long, 0>(bits);
		};
		const std::array<size_t, countSlices> countsSlices{ transform_array_n<countSlices,size_t>(transformedSlices, lambdaSlice) };
		if constexpr (countOddChannels > 0)
		{
			const size_t countOdd{ impl<countOddChannels, UINT>(tag_best{},oddChannels,std::make_index_sequence<countOddChannels>{}) };
			return sum_array_n<countSlices, 0, countSlices, size_t>(countsSlices) + countOdd;
	}
		else
			return sum_array_n<countSlices, 0, countSlices, size_t>(countsSlices);
	}

	template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_long_long<COUNT_CHANNELS, UINT>()>::type>
	static std::string name(tag_long_long, std::index_sequence<CHANNEL...>) noexcept
	{
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned long long) };
		constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned long long) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
		std::stringstream sstr;
		for (size_t slice = 0; slice < countSlices; slice++)
		{
#if defined(PYGMALION_INTRINSICS_MSC)  
			if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X64))
				sstr << "MSC64 ";
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
			if constexpr (compiler::supports(compiler::flags::GNU))
				sstr << "GNU" << (sizeof(unsigned long) * CHAR_BIT) << " ";
#endif
#if defined(PYGMALION_INTRINSICS_MSC)&& !defined(PYGMALION_CPU_X64)
			if constexpr (compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86))
				sstr << "2xMSC32 ";
#endif
			sstr << (sizeof(unsigned long long) * CHAR_BIT) << "bit";
			sstr << ((slice == countSlices - 1) ? "" : " | ");
		}
		if constexpr (countOddChannels > 0)
			sstr << " | " << name<countOddChannels, UINT>(tag_best{}, std::make_index_sequence<countOddChannels>{});
		return sstr.str();
	}
public:
	template <size_t COUNT_CHANNELS, typename UINT>
	constexpr static size_t implementation(const std::array<UINT, COUNT_CHANNELS>& bits) noexcept
	{
		constexpr const intrinsics::compiler::flags comp{ intrinsics::compiler::computeFlags() };
		constexpr const intrinsics::cpu::flags cpu{ intrinsics::cpu::computeFlags() };
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
		constexpr const intrinsics::compiler::flags comp{ intrinsics::compiler::computeFlags() };
		constexpr const intrinsics::cpu::flags cpu{ intrinsics::cpu::computeFlags() };
		if constexpr (std::is_same<bool, UINT>())
			return "[" + name<COUNT_CHANNELS, bool>(tag_best{}, std::make_index_sequence<COUNT_CHANNELS>{}) + "]";
		else
		{
			constexpr const size_t countChunks{ countSplitChannels<UINT, unsigned char, COUNT_CHANNELS>() };
			return "[" + name<countChunks, unsigned char>(tag_best{}, std::make_index_sequence<countChunks>{}) + "]";
		}
	}

	};

