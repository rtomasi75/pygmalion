namespace pygmalion::intrinsics
{
	class base
	{
	private:
		template<size_t COUNT_CHANNELS, size_t START, size_t LEN>
		PYGMALION_INLINE constexpr static bool enable_extractChannels() noexcept
		{
			return (START + LEN) <= COUNT_CHANNELS;
		}
		template<typename T, typename C>
		PYGMALION_INLINE constexpr static bool enable_splitChannels() noexcept
		{
			return ((sizeof(T) % sizeof(C)) == 0) && (sizeof(C) <= sizeof(T));
		}
		template<typename T, typename C>
		PYGMALION_INLINE constexpr static bool enable_mergeChannels() noexcept
		{
			return ((sizeof(C) % sizeof(T)) == 0) && (sizeof(T) <= sizeof(C));
		}
		template<typename T, typename C>
		PYGMALION_INLINE constexpr static bool enable_castChannels() noexcept
		{
			return enable_splitChannels<T, unsigned char>() && enable_mergeChannels<unsigned char, C>();
		}
		template<size_t COUNT_CHANNELS, typename T, typename C, typename LAMBDA, size_t... INDEX>
		PYGMALION_INLINE constexpr static auto transformChannels(const std::array<T, COUNT_CHANNELS>& values, const LAMBDA& lambda, std::index_sequence<INDEX...>) noexcept
		{
			return std::array<std::decay_t<C>, COUNT_CHANNELS>{(lambda(values[INDEX], INDEX))...};
		}
		template<size_t COUNT_CHANNELS_IN, size_t COUNT_CHANNELS_OUT, typename T, typename C, typename LAMBDA, size_t... INDEX>
		PYGMALION_INLINE constexpr static auto warpChannels(const std::array<T, COUNT_CHANNELS_IN>& values, const LAMBDA& lambda, std::index_sequence<INDEX...>) noexcept
		{
			return std::array<std::decay_t<C>, COUNT_CHANNELS_OUT>{(lambda(values, INDEX))...};
		}
	protected:
		template<size_t COUNT_CHANNELS, typename T, typename C, typename LAMBDA>
		PYGMALION_INLINE constexpr static std::array<C, COUNT_CHANNELS> transformChannels(const std::array<T, COUNT_CHANNELS>& old, const LAMBDA& lambda) noexcept
		{
			return base::transformChannels<COUNT_CHANNELS, T, C, LAMBDA>(old, lambda, std::make_index_sequence<COUNT_CHANNELS>{});
		}
		template<size_t COUNT_CHANNELS, size_t START, size_t LENGTH, typename T, typename ENABLED = typename std::enable_if<(LENGTH + START) <= COUNT_CHANNELS>::type>
		PYGMALION_INLINE constexpr static T sumChannels(const std::array<T, COUNT_CHANNELS>& values) noexcept
		{
			if constexpr (LENGTH == 0)
				return T(0);
			if constexpr (LENGTH == 1)
				return values[START];
			if constexpr ((LENGTH % 2) == 1)
				return base::sumChannels<COUNT_CHANNELS, START, 1>(values) + base::sumChannels<COUNT_CHANNELS, START + 1, LENGTH - 1>(values);
			else
				return base::sumChannels<COUNT_CHANNELS, START, LENGTH / 2>(values) + base::sumChannels<COUNT_CHANNELS, START + LENGTH / 2, LENGTH / 2>(values);
		}
		template<typename T, size_t COUNT_CHANNELS, size_t START, size_t LEN, typename = typename std::enable_if<enable_extractChannels<COUNT_CHANNELS, START, LEN>()>::type>
		PYGMALION_INLINE constexpr static const std::array<T, LEN>& extractChannels(const std::array<T, COUNT_CHANNELS>& old) noexcept
		{
			return *reinterpret_cast<const std::array<T, LEN>*>(&old[START]);
		}
		template<typename T, typename C, size_t COUNT_CHANNELS, typename = typename std::enable_if<enable_splitChannels<T, C>()>::type>
		PYGMALION_INLINE constexpr static size_t countSplitChannels() noexcept
		{
			return (COUNT_CHANNELS * sizeof(T)) / sizeof(C);
		}
		template<typename T, typename C, size_t COUNT_CHANNELS, typename = typename std::enable_if<enable_splitChannels<T, C>()>::type>
		PYGMALION_INLINE constexpr static const std::array<C, base::countSplitChannels<T, C, COUNT_CHANNELS>()>& splitChannels(const std::array<T, COUNT_CHANNELS>& old) noexcept
		{
			constexpr const size_t countSplitChannels{ base::countSplitChannels<T,C, COUNT_CHANNELS>() };
			return  *reinterpret_cast<const std::array<C, countSplitChannels>*>(&old);
		}
		template<typename T, typename C, size_t COUNT_CHANNELS, typename = typename std::enable_if<enable_mergeChannels<T, C>()>::type>
		PYGMALION_INLINE constexpr static size_t countMergedChannels() noexcept
		{
			return (COUNT_CHANNELS * sizeof(T)) / sizeof(C);
		}
		template<typename T, typename C, size_t COUNT_CHANNELS, typename = typename std::enable_if<enable_mergeChannels<T, C>()>::type>
		PYGMALION_INLINE constexpr static const std::array<C, base::countMergedChannels<T, C, COUNT_CHANNELS>()>& mergeChannels(const std::array<T, COUNT_CHANNELS>& old) noexcept
		{
			constexpr const size_t countMergedChannels{ base::countMergedChannels<T,C, COUNT_CHANNELS>() };
			return *reinterpret_cast<const std::array<C, countMergedChannels>*>(&old);
		}
		template<typename T, typename C, size_t COUNT_CHANNELS, typename = typename std::enable_if<enable_mergeChannels<T, C>()>::type>
		PYGMALION_INLINE constexpr static const std::array<C, base::countMergedChannels<T, C, COUNT_CHANNELS>()> mergeChannelsOrderly(const std::array<T, COUNT_CHANNELS>& old) noexcept
		{
			constexpr const size_t countMergedChannels{ base::countMergedChannels<T,C, COUNT_CHANNELS>() };
			constexpr const auto lambda = [](const std::array<T, COUNT_CHANNELS>& old, const size_t index)->C
			{
				C ret{ C(0) };
				constexpr const size_t mult{ COUNT_CHANNELS / base::countMergedChannels<T,C, COUNT_CHANNELS>() };
				if constexpr (mult == 1)
					return old[index];
				else
				{
					for (size_t i = 0; i < mult; i++)
					{
						ret |= static_cast<C>(static_cast<C>(old[index * mult + i]) << (i * sizeof(T) * CHAR_BIT));
					}
					return ret;
				}
			};
			return warpChannels<COUNT_CHANNELS, countMergedChannels, T, C>(old, lambda, std::make_index_sequence<countMergedChannels>{});
		}
		template<typename T, typename C, size_t COUNT_CHANNELS, typename = typename std::enable_if<enable_splitChannels<T, C>()>::type>
		PYGMALION_INLINE constexpr static const std::array<C, base::countSplitChannels<T, C, COUNT_CHANNELS>()> splitChannelsOrderly(const std::array<T, COUNT_CHANNELS>& old) noexcept
		{
			constexpr const size_t countSplitChannels{ base::countSplitChannels<T,C, COUNT_CHANNELS>() };
			constexpr const auto lambda = [](const std::array<T, COUNT_CHANNELS>& old, const size_t index)->C
			{
				C ret{ C(0) };
				constexpr const size_t mult{ countSplitChannels / COUNT_CHANNELS };
				if constexpr (mult == 1)
					return old[index];
				else
				{
					const size_t chT{ index / mult };
					const size_t iT{ index % mult };
					constexpr const T mask{ static_cast<T>(static_cast<T>(T(1) << (sizeof(C) * CHAR_BIT)) - T(1)) };
					return static_cast<C>((old[chT] & static_cast<T>(mask << (iT * sizeof(C) * CHAR_BIT))) >> (iT * sizeof(C) * CHAR_BIT));
				}
			};
			return warpChannels<COUNT_CHANNELS, countSplitChannels, T, C>(old, lambda, std::make_index_sequence<countSplitChannels>{});
		}
		template<typename T, typename C, size_t COUNT_CHANNELS, typename = typename std::enable_if<enable_castChannels<T, C>()>::type>
		PYGMALION_INLINE constexpr static size_t countCastChannels() noexcept
		{
			return (COUNT_CHANNELS * sizeof(T)) / sizeof(C);
		}
		template<typename T, typename C, size_t COUNT_CHANNELS, typename = typename std::enable_if<enable_castChannels<T, C>()>::type>
		PYGMALION_INLINE constexpr static const std::array<C, base::countCastChannels<T, C, COUNT_CHANNELS>()>& castChannels(const std::array<T, COUNT_CHANNELS>& old) noexcept
		{
			constexpr const size_t countCastChannels{ base::countCastChannels<T,C, COUNT_CHANNELS>() };
			return std::move(*static_cast<const std::array<C, countCastChannels>*>(&old));
		}
		struct tag_generic {};
		struct tag_bool :
			tag_generic {};
		struct tag_char :
			tag_bool {};
		struct tag_short :
			tag_char {};
		struct tag_int :
			tag_short {};
		struct tag_long :
			tag_int {};
		struct tag_long_long :
			tag_long {};
		struct tag_best :
			tag_long_long {};
	};
}