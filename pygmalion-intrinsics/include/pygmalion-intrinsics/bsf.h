namespace detail
{
	template<size_t COUNT_BITS, typename T>
	bool bsf_reference(const T R, size_t& bit) noexcept;

	template<size_t COUNT_BITS, typename = typename std::enable_if<true>::type>
	struct bsf_traits {};

	template<size_t COUNT_BITS>
	struct bsf_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS <= 64) && (COUNT_BITS > 32)>::type>
	{
		using refType = std::uint64_t;
		using intType = refType;
		static bool reference(const refType bits, size_t& bit) noexcept
		{
			for (size_t i = 0; i < COUNT_BITS; i++)
			{
				if (bits & static_cast<refType>(refType(1) << i))
				{
					bit = i;
					return true;
				}
			}
			return false;
		}
		static bool baseline(const refType bits, size_t& bit) noexcept
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
		static bool generic(const refType bits, size_t& bit)
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
	};

	template<size_t COUNT_BITS>
	struct bsf_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS <= 32) && (COUNT_BITS > 16)>::type>
	{
		using refType = std::uint32_t;
		using intType = refType;
		static bool reference(const refType bits, size_t& bit) noexcept
		{
			for (size_t i = 0; i < COUNT_BITS; i++)
			{
				if (bits & static_cast<refType>(refType(1) << i))
				{
					bit = i;
					return true;
				}
			}
			return false;
		}
		static bool baseline(const refType bits, size_t& bit) noexcept
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
		static bool generic(const refType bits, size_t& bit)
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
	};

	template<size_t COUNT_BITS>
	struct bsf_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS <= 16) && (COUNT_BITS > 8)>::type>
	{
		using refType = std::uint16_t;
		using intType = refType;
		static bool reference(const refType bits, size_t& bit) noexcept
		{
			for (size_t i = 0; i < COUNT_BITS; i++)
			{
				if (bits & static_cast<refType>(refType(1) << i))
				{
					bit = i;
					return true;
				}
			}
			return false;
		}
		static bool baseline(const refType bits, size_t& bit) noexcept
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
		static bool generic(const refType bits, size_t& bit)
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
	};

	template<size_t COUNT_BITS>
	struct bsf_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS <= 8) && (COUNT_BITS > 1)>::type>
	{
		using refType = std::uint8_t;
		using intType = refType;
		static bool reference(const refType bits, size_t& bit) noexcept
		{
			for (size_t i = 0; i < COUNT_BITS; i++)
			{
				if (bits & static_cast<refType>(refType(1) << i))
				{
					bit = i;
					return true;
				}
			}
			return false;
		}
		static bool baseline(const refType bits, size_t& bit) noexcept
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
		static bool generic(const refType bits, size_t& bit)
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
	};

	template<size_t COUNT_BITS>
	struct bsf_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS == 1)>::type>
	{
		using refType = bool;
		using intType = std::uint8_t;
		static bool reference(const refType bits, size_t& bit) noexcept
		{
			if (bits)
			{
				bit = 0;
				return true;
			}
			else
				return false;
		}
		static bool baseline(const refType bits, size_t& bit) noexcept
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
		static bool generic(const refType bits, size_t& bit)
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
	};

	template<size_t COUNT_BITS>
	struct bsf_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS == 0)>::type>
	{
		using refType = std::uint8_t;
		using intType = std::uint8_t;
		static bool reference(const refType bits, size_t& bit) noexcept
		{
			return false;
		}
		static bool baseline(const refType bits, size_t& bit) noexcept
		{
			return false;
		}
		static bool generic(const refType bits, size_t& bit)
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
	};


	template<size_t COUNT_BITS>
	struct bsf_traits<COUNT_BITS, typename std::enable_if<(COUNT_BITS > 64)>::type>
	{
		using refType = std::uintmax_t;
		using intType = refType;
		static bool reference(const refType bits, size_t& bit) noexcept
		{
			for (size_t i = 0; i < COUNT_BITS; i++)
			{
				if (bits & static_cast<refType>(refType(1) << i))
				{
					bit = i;
					return true;
				}
			}
			return false;
		}
		static bool baseline(const refType bits, size_t& bit) noexcept
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
		static bool generic(const refType bits, size_t& bit)
		{
			return bsf_reference<COUNT_BITS, refType>(bits, bit);
		}
	};

}

class bsf :
	protected detail::base
{
private:
	template <typename T>
	static bool bsf_ref(const T bits, size_t& idx) noexcept
	{
		if (!bits)
			return false;
		else
		{
			idx = popcnt::implementation<1, T>({ static_cast<T>((bits & -static_cast<T>(bits)) - T(1)) });
			return true;
		}
	}

	template <size_t COUNT_CHANNELS, typename UINT>
	constexpr static bool enable_empty() noexcept
	{
		return COUNT_CHANNELS <= 0;
	}

	template <size_t COUNT_CHANNELS, typename UINT, size_t... CHANNEL, typename = typename std::enable_if<enable_empty<COUNT_CHANNELS, UINT>()>::type>
	constexpr static bool impl(tag_best, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
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
	constexpr static bool impl(tag_bool, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
	{
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(unsigned char) };
		constexpr const size_t countTransformedChannels{ countSlices * sizeof(unsigned char) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countTransformedChannels };
		const std::array<unsigned char, countSlices>& transformedSlices{ *reinterpret_cast<const std::array<unsigned char, countSlices>*>(&bits) };
		const std::array<UINT, countOddChannels>& oddChannels{ *(reinterpret_cast<const std::array<UINT, countOddChannels>*>(&bits) + countTransformedChannels) };
		for (size_t i = 0; i < countSlices; i++)
		{
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
	constexpr static bool impl(tag_char, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
	{
		using SLICE = unsigned char;
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
		constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
		const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
		const std::array<SLICE, countSlices> transformedSlices{ mergeChannelsOrderly<UINT,SLICE,countSliceChannels>(sliceChannels) };
		for (size_t i = 0; i < countSlices; i++)
		{
			if (bsf::bsf_ref(transformedSlices[i], bit))
			{
				bit += i * sizeof(SLICE) * CHAR_BIT;
				return true;
			}
		}
		if constexpr (countOddChannels > 0)
		{
			const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
			if (impl<countOddChannels, UINT>(tag_best{}, oddChannels, bit, std::make_index_sequence<countOddChannels>{}))
			{
				bit += countSlices * sizeof(SLICE) * CHAR_BIT;
				return true;
			}
			else
				return false;
		}
		else
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
	constexpr static bool impl(tag_short, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
	{
		using SLICE = unsigned short;
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
		constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
		const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
		const std::array<SLICE, countSlices> transformedSlices{ mergeChannelsOrderly<UINT,SLICE,countSliceChannels>(sliceChannels) };
		for (size_t i = 0; i < countSlices; i++)
		{
			if (bsf::bsf_ref(transformedSlices[i], bit))
			{
				bit += i * sizeof(SLICE) * CHAR_BIT;
				return true;
			}
		}
		if constexpr (countOddChannels > 0)
		{
			const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
			if (impl<countOddChannels, UINT>(tag_best{}, oddChannels, bit, std::make_index_sequence<countOddChannels>{}))
			{
				bit += countSlices * sizeof(SLICE) * CHAR_BIT;
				return true;
			}
			else
				return false;
		}
		else
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
	constexpr static bool impl(tag_int, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
	{
		using SLICE = unsigned int;
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
		constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
		const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
		const std::array<SLICE, countSlices> transformedSlices{ mergeChannelsOrderly<UINT,SLICE,countSliceChannels>(sliceChannels) };
		for (size_t i = 0; i < countSlices; i++)
		{
			if (bsf::bsf_ref(transformedSlices[i], bit))
			{
				bit += i * sizeof(SLICE) * CHAR_BIT;
				return true;
			}
		}
		if constexpr (countOddChannels > 0)
		{
			const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
			if (impl<countOddChannels, UINT>(tag_best{}, oddChannels, bit, std::make_index_sequence<countOddChannels>{}))
			{
				bit += countSlices * sizeof(SLICE) * CHAR_BIT;
				return true;
			}
			else
				return false;
		}
		else
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
	constexpr static bool impl(tag_long, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
	{
		using SLICE = unsigned long;
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
		constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
		const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
		const std::array<SLICE, countSlices> transformedSlices{ mergeChannelsOrderly<UINT,SLICE,countSliceChannels>(sliceChannels) };
		for (size_t i = 0; i < countSlices; i++)
		{
			if (bsf::bsf_ref(transformedSlices[i], bit))
			{
				bit += i * sizeof(SLICE) * CHAR_BIT;
				return true;
			}
		}
		if constexpr (countOddChannels > 0)
		{
			const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
			if (impl<countOddChannels, UINT>(tag_best{}, oddChannels, bit, std::make_index_sequence<countOddChannels>{}))
			{
				bit += countSlices * sizeof(SLICE) * CHAR_BIT;
				return true;
			}
			else
				return false;
		}
		else
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
	constexpr static bool impl(tag_long_long, const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit, std::index_sequence<CHANNEL...>) noexcept
	{
		using SLICE = unsigned long long;
		constexpr const size_t countSlices{ COUNT_CHANNELS * sizeof(UINT) / sizeof(SLICE) };
		constexpr const size_t countSliceChannels{ countSlices * sizeof(SLICE) / sizeof(UINT) };
		constexpr const size_t countOddChannels{ COUNT_CHANNELS - countSliceChannels };
		const std::array<UINT, countSliceChannels>& sliceChannels{ extractChannels<UINT,COUNT_CHANNELS,0,countSliceChannels>(bits) };
		const std::array<SLICE, countSlices> transformedSlices{ mergeChannelsOrderly<UINT,SLICE,countSliceChannels>(sliceChannels) };
		for (size_t i = 0; i < countSlices; i++)
		{
			if (bsf::bsf_ref(transformedSlices[i], bit))
			{
				bit += i * sizeof(SLICE) * CHAR_BIT;
				return true;
			}
		}
		if constexpr (countOddChannels > 0)
		{
			const std::array<UINT, countOddChannels>& oddChannels{ extractChannels<UINT,COUNT_CHANNELS,countSliceChannels,countOddChannels>(bits) };
			if (impl<countOddChannels, UINT>(tag_best{}, oddChannels, bit, std::make_index_sequence<countOddChannels>{}))
			{
				bit += countSlices * sizeof(SLICE) * CHAR_BIT;
				return true;
			}
			else
				return false;
		}
		else
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
	using refType = typename detail::bsf_traits<COUNT_BITS>::refType;
	template<size_t COUNT_BITS>
	static bool reference(const refType<COUNT_BITS> R, size_t& bit) noexcept
	{
		return bsf::bsf_ref<refType<COUNT_BITS>>(R, bit);
	}

	template <size_t COUNT_CHANNELS, typename UINT>
	static bool implementation(const std::array<UINT, COUNT_CHANNELS>& bits, size_t& bit) noexcept
	{
		constexpr const intrinsics::compiler::flags comp{ intrinsics::compiler::computeFlags() };
		constexpr const intrinsics::cpu::flags cpu{ intrinsics::cpu::computeFlags() };
		if constexpr (std::is_same<bool, UINT>())
			return impl<COUNT_CHANNELS, bool>(tag_best{}, bits, bit, std::make_index_sequence<COUNT_CHANNELS>{});
		else
		{
			constexpr const size_t countChunks{ countSplitChannels<UINT, unsigned char, COUNT_CHANNELS>() };
			return impl<countChunks, unsigned char>(tag_best{}, splitChannelsOrderly<UINT, unsigned char, COUNT_CHANNELS>({ bits }), bit, std::make_index_sequence<countChunks>{});
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


namespace detail
{
	template<size_t COUNT_BITS, typename T>
	bool bsf_reference(const T R, size_t& bit) noexcept
	{
		return bsf::reference<COUNT_BITS>(R, bit);
	}
}