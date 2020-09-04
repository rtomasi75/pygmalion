class integer_intrinsics
{
private:
	template<typename T>
	constexpr static T largestCommonDivisor(const T a, const T b) noexcept
	{
		const T max{ std::max(a,b) };
		for (T i = 0; i < (max - 1); i++)
		{
			const T n{ max - i - 1 };
			if (((a % n) == 0) && ((b % n) == 0))
				return n;
		}
		assert(false);
		return 0;
	}
public:
	struct tag_generic {};

	constexpr static size_t pow2(const size_t size) noexcept
	{
		size_t pow2_size{ 1 };
		while (pow2_size < size)
			pow2_size *= 2;
		return pow2_size;
	}

	template<size_t SIZE_ELEMENT, size_t SIZE_ARRAY, bool COMPACT = true>
	constexpr static bool aligned()
	{
		const size_t pow2_element{ pow2(SIZE_ELEMENT) };
		size_t lcd{ largestCommonDivisor(pow2_element,SIZE_ARRAY) };
		if (COMPACT)
		{
			const bool aligned{ lcd == pow2_element };
			return aligned;
		}
		else
		{
			const bool aligned{ lcd == pow2_element };
			return aligned;
		}
	}

	struct tag_long_long :
		tag_generic {};
	template<typename T>
	constexpr static bool enable_long_long() { return  (!std::is_same<T, void*>::value) && (!std::is_same<T, bool>::value) && (sizeof(T) <= sizeof(unsigned long long)); };

	struct tag_64bit :
		tag_long_long {};
	template<typename T>
	constexpr static bool enable_64bit() { return  (!std::is_same<T, void*>::value) && (!std::is_same<T, bool>::value) && (sizeof(T) <= sizeof(std::uint64_t)); };

	struct tag_long :
		tag_64bit {};
	template<typename T>
	constexpr static bool enable_long() { return  (!std::is_same<T, void*>::value) && (!std::is_same<T, bool>::value) && (sizeof(T) <= sizeof(unsigned long)); };

	struct tag_int :
		tag_long {};
	template<typename T>
	constexpr static bool enable_int() { return  (!std::is_same<T, void*>::value) && (!std::is_same<T, bool>::value) && (sizeof(T) <= sizeof(unsigned int)); };

	struct tag_32bit :
		tag_int {};
	template<typename T>
	constexpr static bool enable_32bit() { return  (!std::is_same<T, void*>::value) && (!std::is_same<T, bool>::value) && (sizeof(T) <= sizeof(std::uint32_t)); };

	struct tag_short :
		tag_32bit {};
	template<typename T>
	constexpr static bool enable_short() { return   (!std::is_same<T, void*>::value) && (!std::is_same<T, void>::value) && (!std::is_same<T, bool>::value) && (sizeof(T) <= sizeof(unsigned short)); };

	struct tag_16bit :
		tag_short {};
	template<typename T>
	constexpr static bool enable_16bit() { return (!std::is_same<T, void*>::value) && (!std::is_same<T, bool>::value) && (sizeof(T) <= sizeof(std::uint16_t)); };

	struct tag_char :
		tag_16bit {};
	template<typename T>
	constexpr static bool enable_char() { return  (!std::is_same<T, void*>::value) && (!std::is_same<T, bool>::value) && (sizeof(T) <= sizeof(unsigned char)); };

	struct tag_8bit :
		tag_char {};
	template<typename T>
	constexpr static bool enable_8bit() { return  (!std::is_same<T, void*>::value) && (!std::is_same<T, bool>::value) && (sizeof(T) <= sizeof(std::uint8_t)); };

	struct tag_1bit :
		tag_8bit {};
	template<typename T>
	constexpr static bool enable_1bit() { return std::is_same<T, bool>::value; };

	struct tag_0bit :
		tag_1bit {};
	template<typename T>
	constexpr static bool enable_0bit() { return std::is_same<T, void*>::value; };



	struct tag_best :
		tag_0bit
	{};

	template<typename T>
	constexpr static bool enable_any() { return true; };
	template <typename T, int iteration, size_t pow>
	constexpr static T popcount_ref(const T bits) noexcept
	{
		constexpr const int shift{ 1 << iteration };
		if constexpr (shift >= (sizeof(T) * CHAR_BIT))
			return bits;
		else
		{
			constexpr const std::array<T, 2> masks
			{
				static_cast<T>(static_cast<T>(-T(1)) / (pow + 1)),
				static_cast<T>(~(static_cast<T>(-T(1)) / (pow + 1)))
			};
			const T low{ static_cast<T>(bits & masks[0]) };
			const T high{ static_cast<T>(bits & masks[1]) };
			const T value{ static_cast<T>((high >> shift) + low) };
			return popcount_ref<T, iteration + 1, pow* pow>(value);
		}
	}

#if defined(PYGMALION_INTRINSICS_MSC)
	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_64bit<UINT>() && compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X64)>::type >
	constexpr static size_t popcount_impl(tag_64bit, compiler::tag_MSC, cpu::tag_X64, const UINT bits) noexcept
	{
		return static_cast<size_t>(__popcnt64(bits));
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_64bit<UINT>() && compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X64)>::type >
	static std::string popcount_name(tag_64bit, compiler::tag_MSC, cpu::tag_X64) noexcept
	{
		return "MSC X64 64bit";
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_64bit<UINT>() && compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86)>::type >
	constexpr static size_t popcount_impl(tag_64bit, compiler::tag_MSC, cpu::tag_X86, const UINT bits) noexcept
	{
		return __popcnt(static_cast<std::uint32_t>(bits & std::uint64_t(0x00000000FFFFFFFF))) + __popcnt(static_cast<std::uint32_t>(static_cast<uint64_t>(bits) >> 32));
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_64bit<UINT>() && compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86)>::type >
	static std::string popcount_name(tag_64bit, compiler::tag_MSC, cpu::tag_X86) noexcept
	{
		return "MSC X86 64bit";
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_32bit<UINT>() && compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86)>::type >
	constexpr static size_t popcount_impl(tag_32bit, compiler::tag_MSC, cpu::tag_X86, const UINT bits) noexcept
	{
		return static_cast<size_t>(__popcnt(bits));
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_32bit<UINT>() && compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86)>::type >
	static std::string popcount_name(tag_32bit, compiler::tag_MSC, cpu::tag_X86) noexcept
	{
		return "MSC X86 32bit";
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_32bit<UINT>() && compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X64)>::type >
	constexpr static size_t popcount_impl(tag_32bit, compiler::tag_MSC, cpu::tag_X64, const UINT bits) noexcept
	{
		return static_cast<size_t>(__popcnt(bits));
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_32bit<UINT>() && compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X64)>::type >
	static std::string popcount_name(tag_32bit, compiler::tag_MSC, cpu::tag_X64) noexcept
	{
		return "MSC X64 32bit";
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_16bit<UINT>() && compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86)>::type >
	constexpr static size_t popcount_impl(tag_16bit, compiler::tag_MSC, cpu::tag_X86, const UINT bits) noexcept
	{
		return static_cast<size_t>(__popcnt16(bits));
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_16bit<UINT>() && compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X86)>::type >
	static std::string popcount_name(tag_16bit, compiler::tag_MSC, cpu::tag_X86) noexcept
	{
		return "MSC X86 16bit";
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_16bit<UINT>() && compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X64)>::type >
	constexpr static size_t popcount_impl(tag_16bit, compiler::tag_MSC, cpu::tag_X64, const UINT bits) noexcept
	{
		return static_cast<size_t>(__popcnt16(bits));
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_16bit<UINT>() && compiler::supports(compiler::flags::MSC) && cpu::supports(cpu::flags::X64)>::type >
	static std::string popcount_name(tag_16bit, compiler::tag_MSC, cpu::tag_X64) noexcept
	{
		return "MSC X64 16bit";
	}
#endif

#if defined(PYGMALION_INTRINSICS_GNU)
	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_int<UINT>() && compiler::supports(compiler::flags::GNU)>::type >
	constexpr static size_t popcount_impl(tag_int, compiler::tag_GNU, cpu::tag_generic, const UINT bits) noexcept
	{
		return static_cast<size_t>(__builtin_popcount(bits));
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_int<UINT>() && compiler::supports(compiler::flags::GNU)>::type >
	static std::string popcount_name(tag_int, compiler::tag_GNU, cpu::tag_generic) noexcept
	{
		return "GNU int";
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_long<UINT>() && compiler::supports(compiler::flags::GNU)>::type >
	constexpr static size_t popcount_impl(tag_long, compiler::tag_GNU, cpu::tag_generic, const UINT bits) noexcept
	{
		return static_cast<size_t>(__builtin_popcountl(bits));
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_long<UINT>() && compiler::supports(compiler::flags::GNU)>::type >
	static std::string popcount_name(tag_long, compiler::tag_GNU, cpu::tag_generic) noexcept
	{
		return "GNU long";
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_long_long<UINT>() && compiler::supports(compiler::flags::GNU)>::type >
	constexpr static size_t popcount_impl(tag_long_long, compiler::tag_GNU, cpu::tag_generic, const UINT bits) noexcept
	{
		return static_cast<size_t>(__builtin_popcountl(bits));
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_long_long<UINT>() && compiler::supports(compiler::flags::GNU)>::type >
	static std::string popcount_name(tag_long_long, compiler::tag_GNU, cpu::tag_generic) noexcept
	{
		return "GNU long long";
	}
#endif

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<!(enable_0bit<UINT>() || enable_1bit<UINT>())>::type>
	constexpr static size_t popcount_impl(tag_generic, compiler::tag_generic, cpu::tag_generic, const UINT bits) noexcept
	{
		return popcount_ref<UINT, 0, 2>(bits);
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<!(enable_0bit<UINT>() || enable_1bit<UINT>())>::type>
	static std::string popcount_name(tag_generic, compiler::tag_generic, cpu::tag_generic) noexcept
	{
		return "generic";
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_1bit<UINT>()>::type>
	constexpr static size_t popcount_impl(tag_1bit, compiler::tag_generic, cpu::tag_generic, const UINT bits) noexcept
	{
		return static_cast<size_t>(bits);
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_1bit<UINT>()>::type>
	static std::string popcount_name(tag_1bit, compiler::tag_generic, cpu::tag_generic) noexcept
	{
		return "single bit";
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_0bit<UINT>()>::type>
	constexpr static size_t popcount_impl(tag_0bit, compiler::tag_generic, cpu::tag_generic, const UINT bits) noexcept
	{
		return 0;
	}

	template <typename UINT, compiler::flags COMPILER, cpu::flags CPU, typename = typename std::enable_if<enable_0bit<UINT>()>::type>
	static std::string popcount_name(tag_0bit, compiler::tag_generic, cpu::tag_generic) noexcept
	{
		return "constant";
	}

public:
	template <typename UINT>
	constexpr static size_t popcount(const UINT bits) noexcept
	{
		constexpr const intrinsics::compiler::flags comp{ intrinsics::compiler::computeFlags() };
		constexpr const intrinsics::cpu::flags cpu{ intrinsics::cpu::computeFlags() };
		return integer_intrinsics::popcount_impl<UINT, comp, cpu>(tag_best{}, intrinsics::compiler::tag_best{}, intrinsics::cpu::tag_best{}, bits);
	}

	template <typename UINT>
	static std::string popcount_name() noexcept
	{
		constexpr const intrinsics::compiler::flags comp{ intrinsics::compiler::computeFlags() };
		constexpr const intrinsics::cpu::flags cpu{ intrinsics::cpu::computeFlags() };
		return integer_intrinsics::popcount_name<UINT, comp, cpu>(tag_best{}, intrinsics::compiler::tag_best{}, intrinsics::cpu::tag_best{});
	}

};
