namespace detail
{
	class base
	{
	private:
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
	protected:
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
		template<typename T, typename C, size_t SIZE, typename = typename std::enable_if<enable_splitChannels<T, C>()>::type>
		constexpr static size_t countSplitChannels() noexcept
		{
			return (SIZE * sizeof(T)) / sizeof(C);
		}
		template<typename T, typename C, size_t SIZE, typename = typename std::enable_if<enable_splitChannels<T, C>()>::type>
		constexpr static const std::array<C, base::countSplitChannels<T, C, SIZE>()>& splitChannels(const std::array<T, SIZE>& old) noexcept
		{
			constexpr const size_t countSplitChannels{ base::countSplitChannels<T,C, SIZE>() };
			return std::move(*reinterpret_cast<const std::array<C, countSplitChannels>*>(&old));
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
			return std::move(*reinterpret_cast<const std::array<C, countMergedChannels>*>(&old));
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
	};
}