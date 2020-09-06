namespace detail
{
	class base
	{
	private:
		template<size_t SIZE, size_t START, size_t LEN>
		constexpr static bool enable_extractChannels() noexcept
		{
			return (START + LEN) <= SIZE;
		}
		template<typename T, typename C>
		constexpr static bool enable_splitChannels() noexcept
		{
			return ((sizeof(T) % sizeof(C)) == 0) && (sizeof(C) <= sizeof(T));
		}
		template<typename T, typename C>
		constexpr static bool enable_mergeChannels() noexcept
		{
			return ((sizeof(C) % sizeof(T)) == 0) && (sizeof(T) <= sizeof(C));
		}
		template<typename T, typename C>
		constexpr static bool enable_castChannels() noexcept
		{
			return enable_splitChannels<T, unsigned char>() && enable_mergeChannels<unsigned char, C>();
		}
		template<size_t SIZE, typename T, typename C, typename LAMBDA, size_t... INDEX>
		constexpr static auto transformChannels(const std::array<T, SIZE>& values, const LAMBDA& lambda, std::index_sequence<INDEX...>) noexcept
		{
			return std::array<std::decay_t<C>, SIZE>{(lambda(values[INDEX], INDEX))...};
		}
	protected:
		template<size_t SIZE, typename T, typename C, typename LAMBDA>
		constexpr static std::array<C, SIZE> transformChannels(const std::array<T, SIZE>& old, const LAMBDA& lambda) noexcept
		{
			return base::transformChannels<SIZE, T, C, LAMBDA>(old, lambda, std::make_index_sequence<SIZE>{});
		}
		template<size_t SIZE, size_t START, size_t LENGTH, typename T, typename ENABLED = typename std::enable_if<(LENGTH + START) <= SIZE>::type>
		constexpr static T sumChannels(const std::array<T, SIZE>& values) noexcept
		{
			if constexpr (LENGTH == 0)
				return T(0);
			if constexpr (LENGTH == 1)
				return values[START];
			if constexpr ((LENGTH % 2) == 1)
				return base::sumChannels<SIZE, START, 1>(values) + base::sumChannels<SIZE, START + 1, LENGTH - 1>(values);
			else
				return base::sumChannels<SIZE, START, LENGTH / 2>(values) + base::sumChannels<SIZE, START + LENGTH / 2, LENGTH / 2>(values);
		}
		template<typename T, size_t SIZE, size_t START, size_t LEN, typename = typename std::enable_if<enable_extractChannels<SIZE, START, LEN>()>::type>
		constexpr static const std::array<T, LEN>& extractChannels(const std::array<T, SIZE>& old) noexcept
		{
			return *reinterpret_cast<const std::array<T, LEN>*>(&old[START]);
		}
		template<typename T, typename C, size_t SIZE, typename = typename std::enable_if<enable_splitChannels<T, C>()>::type>
		constexpr static size_t countSplitChannels() noexcept
		{
			return (SIZE * sizeof(T)) / sizeof(C);
		}
		template<typename T, typename C, size_t SIZE, typename = typename std::enable_if<enable_splitChannels<T, C>()>::type>
		constexpr static const std::array<C, base::countSplitChannels<T, C, SIZE>()>& splitChannels(const std::array<T, SIZE>& old) noexcept
		{
			constexpr const size_t countSplitChannels{ base::countSplitChannels<T,C, SIZE>() };
			return  *reinterpret_cast<const std::array<C, countSplitChannels>*>(&old);
		}
		template<typename T, typename C, size_t SIZE, typename = typename std::enable_if<enable_mergeChannels<T, C>()>::type>
		constexpr static size_t countMergedChannels() noexcept
		{
			return (SIZE * sizeof(T)) / sizeof(C);
		}
		template<typename T, typename C, size_t SIZE, typename = typename std::enable_if<enable_mergeChannels<T, C>()>::type>
		constexpr static const std::array<C, base::countMergedChannels<T, C, SIZE>()>& mergeChannels(const std::array<T, SIZE>& old) noexcept
		{
			constexpr const size_t countMergedChannels{ base::countMergedChannels<T,C, SIZE>() };
			return *reinterpret_cast<const std::array<C, countMergedChannels>*>(&old);
		}
		template<typename T, typename C, size_t SIZE, typename = typename std::enable_if<enable_castChannels<T, C>()>::type>
		constexpr static size_t countCastChannels() noexcept
		{
			return (SIZE * sizeof(T)) / sizeof(C);
		}
		template<typename T, typename C, size_t SIZE, typename = typename std::enable_if<enable_castChannels<T, C>()>::type>
		constexpr static const std::array<C, base::countCastChannels<T, C, SIZE>()>& castChannels(const std::array<T, SIZE>& old) noexcept
		{
			constexpr const size_t countCastChannels{ base::countCastChannels<T,C, SIZE>() };
			return std::move(*reinterpret_cast<const std::array<C, countCastChannels>*>(&old));
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