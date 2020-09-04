namespace detail
{
	template<size_t COUNT_BITS, bool COMPACT>
	struct unsigned_integer
	{
		constexpr static size_t countWords() noexcept
		{
			constexpr const bool isCompact{ COMPACT };
			constexpr const size_t countBits{ COUNT_BITS };
			constexpr const size_t countBytes{ (countBits + 7) / 8 };
			constexpr const size_t countBitsPerWord{ sizeof(typename integer_traits<countBytes, isCompact>::uword) * CHAR_BIT };
			return (countBits + countBitsPerWord - 1) / countBitsPerWord;
		}
		constexpr static size_t countBitsPerWord() noexcept
		{
			constexpr const bool isCompact{ COMPACT };
			constexpr const size_t countBits{ COUNT_BITS };
			constexpr const size_t countBytes{ (countBits + 7) / 8 };
			return sizeof(typename integer_traits<countBytes, isCompact>::uword) * CHAR_BIT;
		}
		constexpr static bool isMultiWord() noexcept
		{
			return unsigned_integer::countWords() > 1;
		}
		constexpr static bool isSingleBit() noexcept
		{
			constexpr const size_t countBits{ COUNT_BITS };
			return countBits == 1;
		}
		constexpr static bool isSingleWord() noexcept
		{
			return (unsigned_integer::countWords() == 1) && !isSingleBit();
		}
		constexpr static bool isEmpty() noexcept
		{
			return unsigned_integer::countWords() == 0;
		}
	};
}


template<size_t COUNT_BITS, bool COMPACT, typename ENABLED = typename std::enable_if <true>::type>
class unsigned_integer
{
public:
	constexpr static const bool isCompact{ COMPACT };
	constexpr static const size_t countBits{ COUNT_BITS };
	constexpr static const size_t countBytes{ (countBits + 7) / 8 };
	using wordType = typename integer_traits<countBytes, isCompact>::uword;
	constexpr static const size_t countBitsPerWord{ sizeof(wordType) * CHAR_BIT };
	constexpr static const size_t countWords{ (countBits + countBitsPerWord - 1) / countBitsPerWord };
	constexpr static const size_t countStorageBits{ countWords * countBitsPerWord };
private:
	constexpr static wordType normalizeHighestWord(const wordType word) noexcept
	{
		constexpr const size_t shift{ countBitsPerWord - (countStorageBits - countBits) };
		if constexpr (shift < countBitsPerWord)
		{
			constexpr const wordType mask{ static_cast<wordType>((wordType(1) << shift) - wordType(1)) };
			return static_cast<wordType>(word & mask);
		}
		else
			return word;
	}
	template<size_t index>
	constexpr static wordType normalizeWords(const wordType word) noexcept
	{
		if constexpr (index == (countWords - 1))
		{
			constexpr const size_t shift{ countBitsPerWord - (countStorageBits - countBits) };
			if constexpr (shift < countBitsPerWord)
			{
				constexpr const wordType mask{ static_cast<wordType>((wordType(1) << shift) - wordType(1)) };
				return static_cast<wordType>(word & mask);
			}
			else
				return word;
		}
		else
			return word;
	}
	template<std::size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM, std::size_t... INDICES>
	constexpr static std::array<wordType, SIZE> nullaryTransformWords(std::index_sequence<INDICES...>, const LAMBDA_TRANSFORM& transform) noexcept
	{
		if constexpr (NORMALIZE)
			return std::array<wordType, SIZE>{ (unsigned_integer::normalizeWords<INDICES>(transform(INDICES)))... };
		else
			return std::array<wordType, SIZE>{ (transform(INDICES))... };
	}
	template<std::size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM, std::size_t... INDICES>
	constexpr static std::array<wordType, SIZE> unaryTransformWords(const std::array<wordType, SIZE>& words, std::index_sequence<INDICES...>, const LAMBDA_TRANSFORM& transform) noexcept
	{
		if constexpr (NORMALIZE)
			return std::array<wordType, SIZE>{ (unsigned_integer::normalizeWords<INDICES>(transform(words[INDICES], INDICES)))... };
		else
			return std::array<wordType, SIZE>{ (transform(words[INDICES], INDICES))... };
	}
	template<std::size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM, std::size_t... INDICES>
	constexpr static std::array<wordType, SIZE> binaryTransformWords(const std::array<wordType, SIZE>& words1, const std::array<wordType, SIZE>& words2, std::index_sequence<INDICES...>, const LAMBDA_TRANSFORM& transform) noexcept
	{
		if constexpr (NORMALIZE)
			return std::array<wordType, SIZE>{ (unsigned_integer::normalizeWords<INDICES>(transform(words1[INDICES], words2[INDICES], INDICES)))... };
		else
			return std::array<wordType, SIZE>{ (transform(words1[INDICES], words2[INDICES], INDICES))... };
	}
	template<std::size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM, std::size_t... INDICES>
	constexpr static void binaryTransformWordsInplace(std::array<wordType, SIZE>& words1, const std::array<wordType, SIZE>& words2, const LAMBDA_TRANSFORM& transform) noexcept
	{
		for (size_t index = 0; index < SIZE; index++)
			transform(words1[index], words2[index], index);
		if constexpr (NORMALIZE)
		{
			constexpr const size_t shift{ countBitsPerWord - (countStorageBits - countBits) };
			constexpr const wordType mask{ static_cast<wordType>((wordType(1) << shift) - wordType(1)) };
			words1[countWords - 1] &= mask;
		}
	}
	template<std::size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM>
	constexpr static std::array<wordType, SIZE> nullaryTransformWords(const LAMBDA_TRANSFORM& create) noexcept
	{
		return unsigned_integer::nullaryTransformWords<SIZE, NORMALIZE>(std::make_index_sequence<countWords>{}, create);
	}
	template<std::size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM>
	constexpr static std::array<wordType, SIZE> unaryTransformWords(const std::array<wordType, SIZE>& words, LAMBDA_TRANSFORM transform) noexcept
	{
		return unsigned_integer::unaryTransformWords<SIZE, NORMALIZE>(words, std::make_index_sequence<countWords>{}, transform);
	}
	template<std::size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM>
	constexpr static std::array<wordType, SIZE> binaryTransformWords(const std::array<wordType, SIZE>& words1, const std::array<wordType, SIZE>& words2, LAMBDA_TRANSFORM transform) noexcept
	{
		return unsigned_integer::binaryTransformWords<SIZE, NORMALIZE>(words1, words2, std::make_index_sequence<countWords>{}, transform);
	}
	template<std::size_t SIZE, typename T >
	constexpr static std::array<wordType, SIZE> encodeValue(T&& value) noexcept
	{
		constexpr const size_t countBitsType{ sizeof(T) * CHAR_BIT };
		if constexpr (countBitsPerWord < countBitsType)
		{
			const auto lambda = [value, countBitsType](const std::size_t index)->wordType
			{
				const T mask{ static_cast<T>((T(1) << countBitsPerWord) - T(1)) };
				const std::size_t shift{ countBitsPerWord * index };
				if (shift < countBitsType)
				{
					const T mask_shifted{ static_cast<T>(mask << shift) };
					const T masked{ static_cast<T>(value & mask_shifted) };
					const T result{ static_cast<T>(masked >> shift) };
					return static_cast<wordType>(result);
				}
				else
					return wordType(0);
			};
			return unsigned_integer::nullaryTransformWords<countWords, true>(lambda);
		}
		else
		{
			const auto lambda = [value](const std::size_t index)->wordType
			{
				const std::size_t shift{ countBitsPerWord * index };
				return (value) >> shift;
			};
			return unsigned_integer::nullaryTransformWords<countWords, true>(lambda);
		}
	}
	constexpr unsigned_integer(const std::array<wordType, countWords>& words, bool) noexcept :
		m_Words{ words }
	{	}
	std::array<wordType, countWords> m_Words;
public:
	constexpr unsigned_integer() noexcept :
		m_Words{ make_array_n<countWords,wordType>(0) }
	{	}
	template<typename T>
	constexpr unsigned_integer(const T& value) noexcept :
		m_Words{ unsigned_integer::encodeValue<countWords>(value) }
	{	}
	constexpr unsigned_integer(const unsigned_integer&) noexcept = default;
	constexpr unsigned_integer(unsigned_integer&&) noexcept = default;
	constexpr unsigned_integer& operator=(const unsigned_integer&) noexcept = default;
	constexpr unsigned_integer& operator=(unsigned_integer&&) noexcept = default;
	size_t&& populationCount() const noexcept
	{
		size_t count{ 0 };
		for (size_t index = 0; index < countWords; index++)
			count += integer_intrinsics::popcount(m_Words[index]);
		return std::move(count);
	}
	operator std::string() const noexcept
	{
		std::stringstream sstr;
		for (size_t index = 0; index < countWords; index++)
		{
			sstr << (index > 0 ? ":" : "");
			for (size_t i = 0; i < countBitsPerWord; i++)
			{
				if (((countWords - 1 - index) * countBitsPerWord + countBitsPerWord - 1 - i) < countBits)
					sstr << ((m_Words[countWords - 1 - index] & (wordType(1) << (countBitsPerWord - 1 - i))) ? '1' : '0');
				else
					sstr << ((m_Words[countWords - 1 - index] & (wordType(1) << (countBitsPerWord - 1 - i))) ? 'E' : '_');

			}
		}
		return sstr.str();
	}
	unsigned_integer&& operator~() const noexcept
	{
		auto lambda = [](const wordType a, const std::size_t)->wordType { return ~a; };
		return std::move(unsigned_integer(unsigned_integer::unaryTransformWords<countWords, true>(m_Words, lambda), false));
	}
	unsigned_integer& operator&=(const unsigned_integer& other) noexcept
	{
		auto lambda = [&other](wordType& a, const wordType b, const std::size_t)->wordType { a &= b; };
		unsigned_integer::binaryTransformWordsInplace<countWords, false>(m_Words, other.m_Words, lambda);
		return *this;
	}
	unsigned_integer& operator|=(const unsigned_integer& other) noexcept
	{
		auto lambda = [&other](wordType& a, const wordType b, const std::size_t)->wordType { a |= b; };
		unsigned_integer::binaryTransformWordsInplace<countWords, false>(m_Words, other.m_Words, lambda);
		return *this;
	}
	unsigned_integer& operator^=(const unsigned_integer& other) noexcept
	{
		auto lambda = [](wordType& a, const wordType b, const std::size_t)->void { a ^= b; };
		unsigned_integer::binaryTransformWordsInplace<countWords, false>(m_Words, other.m_Words, lambda);
		return *this;
	}
	unsigned_integer&& operator&(const unsigned_integer& other) const noexcept
	{
		auto lambda = [](const wordType a, const wordType b, const std::size_t)->wordType { return a & b; };
		return std::move(unsigned_integer(unsigned_integer::binaryTransformWords<countWords, false>(m_Words, other.m_Words, lambda), false));
	}
	unsigned_integer&& operator|(const unsigned_integer& other) const noexcept
	{
		auto lambda = [](const wordType a, const wordType b, const std::size_t)->wordType { return a | b; };
		return std::move(unsigned_integer(unsigned_integer::binaryTransformWords<countWords, false>(m_Words, other.m_Words, lambda), false));
	}
	unsigned_integer&& operator^(const unsigned_integer& other) const noexcept
	{
		auto lambda = [](const wordType a, const wordType b, const std::size_t)->wordType { return a ^ b; };
		return std::move(unsigned_integer(unsigned_integer::binaryTransformWords<countWords, false>(m_Words, other.m_Words, lambda), false));
	}
	unsigned_integer&& operator+(const unsigned_integer& other) const noexcept
	{
		std::array<wordType, countWords> results{ make_array_n<countWords,wordType>(wordType(0)) };
		bool carryFlag{ false };
		for (size_t i = 0; i < countWords - 1; i++)
		{
			wordType temp{ carryFlag };
			temp += m_Words[i];
			carryFlag = !temp;
			results[i] = temp + other.m_Words[i];
			carryFlag = results[i] < temp;
		}
		results[countWords - 1] = unsigned_integer::normalizeHighestWord(carryFlag + m_Words[countWords - 1] + other.m_Words[countWords - 1]);
		return std::move(unsigned_integer(results, false));
	}
	unsigned_integer& operator+=(const unsigned_integer& other)  noexcept
	{
		bool carryFlag{ false };
		for (size_t i = 0; i < countWords - 1; i++)
		{
			wordType temp{ carryFlag };
			temp += m_Words[i];
			carryFlag = !temp;
			m_Words[i] = temp + other.m_Words[i];
			carryFlag = m_Words[i] < temp;
		}
		m_Words[countWords - 1] = unsigned_integer::normalizeHighestWord(carryFlag + m_Words[countWords - 1] + other.m_Words[countWords - 1]);
		return *this;
	}
	static unsigned_integer&& random() noexcept
	{
		const auto lambda = [](const size_t index)->wordType
		{
			wordType w{ wordType(0) };
			for (size_t c = 0; c < sizeof(wordType); c++)
			{
				const wordType randomChar{ static_cast<wordType>(std::rand() % UCHAR_MAX) };
				w |= randomChar << (CHAR_BIT * c);
			}
			return w;
		};
		return std::move(unsigned_integer(unsigned_integer::nullaryTransformWords<countWords, true>(lambda), false));
	}
	static unsigned_integer&& sparse() noexcept
	{
		const auto lambda = [](const size_t index)->wordType
		{
			wordType w{ wordType(0) };
			for (size_t c = 0; c < sizeof(wordType); c++)
			{
				const wordType randomChar{ static_cast<wordType>((std::rand() % UCHAR_MAX) & (std::rand() % UCHAR_MAX) & (std::rand() % UCHAR_MAX)) };
				w |= randomChar << (CHAR_BIT * c);
			}
			return w;
		};
		return std::move(unsigned_integer(unsigned_integer::nullaryTransformWords<countWords, true>(lambda), false));
	}
	constexpr bool operator==(const unsigned_integer& other) const noexcept
	{
		for (size_t index = 0; index < countWords; index++)
		{
			if (other.m_Words[index] != m_Words[index])
				return false;
		}
		return true;
	}
	constexpr bool operator!=(const unsigned_integer& other) const noexcept
	{
		return !((*this) == other);
	}
};

template<size_t COUNT_BITS, bool COMPACT>
class unsigned_integer<COUNT_BITS, COMPACT, typename std::enable_if <detail::unsigned_integer<COUNT_BITS, COMPACT>::isSingleWord()>::type>
{
public:
	constexpr static const bool isCompact{ COMPACT };
	constexpr static const size_t countBits{ COUNT_BITS };
	constexpr static const size_t countBytes{ (countBits + 7) / 8 };
	using wordType = typename integer_traits<countBytes, isCompact>::uword;
	constexpr static const size_t countBitsPerWord{ sizeof(wordType) * CHAR_BIT };
	constexpr static const size_t countWords{ 1 };
	constexpr static const size_t countStorageBits{ countBitsPerWord };
private:
	wordType m_Word;
	constexpr static wordType normalizeWord(const wordType word) noexcept
	{
		constexpr const size_t shift{ countBitsPerWord - (countStorageBits - countBits) };
		if constexpr (shift < countBitsPerWord)
		{
			constexpr const wordType mask{ static_cast<wordType>((wordType(1) << shift) - wordType(1)) };
			return static_cast<wordType>(word & mask);
		}
		else
			return word;
	}
	constexpr unsigned_integer(const wordType word, bool) noexcept :
		m_Word{ word }
	{	}
public:
	constexpr unsigned_integer() noexcept :
		m_Word{ wordType(0) }
	{	}
	template<typename T>
	constexpr unsigned_integer(T&& value) noexcept :
		m_Word{ normalizeWord(static_cast<wordType>(value)) }
	{	}
	constexpr unsigned_integer(const unsigned_integer&) noexcept = default;
	constexpr unsigned_integer(unsigned_integer&&) noexcept = default;
	constexpr unsigned_integer& operator=(const unsigned_integer&) noexcept = default;
	constexpr unsigned_integer& operator=(unsigned_integer&&) noexcept = default;
	size_t&& populationCount() const noexcept
	{
		return std::move(integer_intrinsics::popcount(m_Word));
	}
	operator std::string() const noexcept
	{
		std::stringstream sstr;
		sstr << "[";
		for (size_t i = 0; i < countBitsPerWord; i++)
		{
			if ((countBitsPerWord - 1 - i) < countBits)
				sstr << ((m_Word & (wordType(1) << (countBitsPerWord - 1 - i))) ? '1' : '0');
			else
				sstr << ((m_Word & (wordType(1) << (countBitsPerWord - 1 - i))) ? 'E' : '_');

		}
		sstr << "]";
		return sstr.str();
	}
	unsigned_integer&& operator~() const noexcept
	{
		return std::move(unsigned_integer(normalizeWord(~m_Word), false));
	}
	unsigned_integer& operator&=(const unsigned_integer& other) noexcept
	{
		m_Word = m_Word & other.m_Word;
		return *this;
	}
	unsigned_integer& operator+=(const unsigned_integer& other) noexcept
	{
		m_Word = normalizeWord(m_Word + other.m_Word);
		return *this;
	}
	unsigned_integer& operator*=(const unsigned_integer& other) noexcept
	{
		m_Word = normalizeWord(m_Word * other.m_Word);
		return *this;
	}
	unsigned_integer& operator|=(const unsigned_integer& other) noexcept
	{
		m_Word = m_Word | other.m_Word;
		return *this;
	}
	unsigned_integer& operator^=(const unsigned_integer& other) noexcept
	{
		m_Word = m_Word & other.m_Word;
		return *this;
	}
	unsigned_integer&& operator&(const unsigned_integer& other) const noexcept
	{
		return std::move(unsigned_integer(m_Word & other.m_Word, false));
	}
	unsigned_integer&& operator|(const unsigned_integer& other) const noexcept
	{
		return std::move(unsigned_integer(m_Word | other.m_Word, false));
	}
	unsigned_integer&& operator^(const unsigned_integer& other) const noexcept
	{
		return std::move(unsigned_integer(m_Word ^ other.m_Word, false));
	}
	unsigned_integer&& operator+(const unsigned_integer& other) const noexcept
	{
		return std::move(unsigned_integer(normalizeWord(m_Word + other.m_Word), false));
	}
	unsigned_integer&& operator*(const unsigned_integer& other) const noexcept
	{
		return std::move(unsigned_integer(normalizeWord(m_Word * other.m_Word), false));
	}
	static unsigned_integer&& random() noexcept
	{
		wordType w{ wordType(0) };
		for (size_t c = 0; c < sizeof(wordType); c++)
		{
			const wordType randomChar{ static_cast<wordType>(std::rand() % UCHAR_MAX) };
			w |= randomChar << (CHAR_BIT * c);
		}
		return std::move(unsigned_integer(normalizeWord(std::move(w)), false));
	}
	static unsigned_integer&& sparse() noexcept
	{
		wordType w{ wordType(0) };
		for (size_t c = 0; c < sizeof(wordType); c++)
		{
			const wordType randomChar{ static_cast<wordType>((std::rand() % UCHAR_MAX) & (std::rand() % UCHAR_MAX) & (std::rand() % UCHAR_MAX)) };
			w |= randomChar << (CHAR_BIT * c);
		}
		return std::move(unsigned_integer(normalizeWord(std::move(w)), false));
	}
	constexpr bool operator==(const unsigned_integer& other) const noexcept
	{
		return m_Word == other.m_Word;
	}
	constexpr bool operator!=(const unsigned_integer& other) const noexcept
	{
		return m_Word != other.m_Word;
	}
};

template<size_t COUNT_BITS, bool COMPACT>
class unsigned_integer<COUNT_BITS, COMPACT, typename std::enable_if <detail::unsigned_integer<COUNT_BITS, COMPACT>::isSingleBit()>::type>
{
public:
	constexpr static const bool isCompact{ COMPACT };
	constexpr static const size_t countBits{ 1 };
	constexpr static const size_t countBytes{ (countBits + 7) / 8 };
	using wordType = bool;
	constexpr static const size_t countBitsPerWord{ sizeof(wordType) * CHAR_BIT };
	constexpr static const size_t countWords{ 1 };
	constexpr static const size_t countStorageBits{ countBitsPerWord };
private:
	constexpr unsigned_integer(const wordType word, bool) noexcept :
		m_Word{ word }
	{	}
public:
	wordType m_Word;
	constexpr unsigned_integer() noexcept :
		m_Word{ wordType(0) }
	{	}
	template<typename T>
	constexpr unsigned_integer(const T value) noexcept :
		m_Word{ static_cast<wordType>(value) }
	{	}
	constexpr unsigned_integer(const unsigned_integer&) noexcept = default;
	constexpr unsigned_integer(unsigned_integer&&) noexcept = default;
	constexpr unsigned_integer& operator=(const unsigned_integer&) noexcept = default;
	constexpr unsigned_integer& operator=(unsigned_integer&&) noexcept = default;
	size_t populationCount() const noexcept
	{
		return integer_intrinsics::popcount(m_Word);
	}
	operator std::string() const noexcept
	{
		std::stringstream sstr;
		sstr << "(";
		sstr << (m_Word ? '1' : '0');
		sstr << ")";
		return sstr.str();
	}
	unsigned_integer operator~() const noexcept
	{
		return std::move(unsigned_integer(!m_Word, false));
	}
	unsigned_integer& operator*=(const unsigned_integer other) noexcept
	{
		m_Word &= other.m_Word;
		return *this;
	}
	unsigned_integer& operator+=(const unsigned_integer other) noexcept
	{
		m_Word ^= other.m_Word;
		return *this;
	}
	unsigned_integer& operator&=(const unsigned_integer other) noexcept
	{
		m_Word &= other.m_Word;
		return *this;
	}
	unsigned_integer& operator|=(const unsigned_integer other) noexcept
	{
		m_Word |= other.m_Word;
		return *this;
	}
	unsigned_integer& operator^=(const unsigned_integer other) noexcept
	{
		m_Word ^= other.m_Word;
		return *this;
	}
	unsigned_integer operator+(const unsigned_integer other) const noexcept
	{
		return unsigned_integer(m_Word ^ other.m_Word, false);
	}
	unsigned_integer&& operator*(const unsigned_integer& other) const noexcept
	{
		return unsigned_integer(m_Word & other.m_Word, false);
	}
	unsigned_integer operator&(const unsigned_integer other) const noexcept
	{
		return unsigned_integer(m_Word & other.m_Word, false);
	}
	unsigned_integer operator|(const unsigned_integer other) const noexcept
	{
		return unsigned_integer(m_Word | other.m_Word, false);
	}
	unsigned_integer operator^(const unsigned_integer other) const noexcept
	{
		return unsigned_integer(m_Word ^ other.m_Word, false);
	}
	static unsigned_integer random() noexcept
	{
		const wordType w{ static_cast<wordType>(std::rand() % 2) };
		return std::move(unsigned_integer(std::move(w), false));
	}
	static unsigned_integer sparse() noexcept
	{
		const wordType a{ static_cast<wordType>(std::rand() % 2) };
		const wordType b{ static_cast<wordType>(std::rand() % 2) };
		const wordType c{ static_cast<wordType>(std::rand() % 2) };
		return std::move(unsigned_integer(a && b && c, false));
	}
	constexpr bool operator==(const unsigned_integer other) const noexcept
	{
		return m_Word == other.m_Word;
	}
	constexpr bool operator!=(const unsigned_integer other) const noexcept
	{
		return m_Word != other.m_Word;
	}
};

template<size_t COUNT_BITS, bool COMPACT>
class unsigned_integer<COUNT_BITS, COMPACT, typename std::enable_if <detail::unsigned_integer<COUNT_BITS, COMPACT>::isEmpty()>::type>
{
public:
	constexpr static const bool isCompact{ COMPACT };
	constexpr static const size_t countBits{ 0 };
	constexpr static const size_t countBytes{ 0 };
	using wordType = void*;
	constexpr static const size_t countBitsPerWord{ 0 };
	constexpr static const size_t countWords{ 1 };
	constexpr static const size_t countStorageBits{ 0 };
	constexpr unsigned_integer() noexcept = default;
	template<typename T>
	constexpr unsigned_integer(T&& value) noexcept
	{	}
	constexpr unsigned_integer(const unsigned_integer&) noexcept = default;
	constexpr unsigned_integer(unsigned_integer&&) noexcept = default;
	constexpr unsigned_integer& operator=(const unsigned_integer&) noexcept = default;
	constexpr unsigned_integer& operator=(unsigned_integer&&) noexcept = default;
	constexpr size_t populationCount() const noexcept
	{
		return 0;
	}
	operator std::string() const noexcept
	{
		return "Z";
	}
	unsigned_integer operator~() const noexcept
	{
		return std::move(unsigned_integer());
	}
	unsigned_integer& operator&=(const unsigned_integer other) noexcept
	{
		return *this;
	}
	unsigned_integer& operator|=(const unsigned_integer other) noexcept
	{
		return *this;
	}
	unsigned_integer& operator+=(const unsigned_integer other) noexcept
	{
		return *this;
	}
	unsigned_integer& operator*=(const unsigned_integer other) noexcept
	{
		return *this;
	}
	unsigned_integer& operator^=(const unsigned_integer other) noexcept
	{
		return *this;
	}
	unsigned_integer operator&(const unsigned_integer other) const noexcept
	{
		return std::move(unsigned_integer());
	}
	unsigned_integer operator|(const unsigned_integer other) const noexcept
	{
		return std::move(unsigned_integer());
	}
	unsigned_integer operator^(const unsigned_integer other) const noexcept
	{
		return std::move(unsigned_integer());
	}
	unsigned_integer operator+(const unsigned_integer other) const noexcept
	{
		return std::move(unsigned_integer());
	}
	unsigned_integer operator*(const unsigned_integer other) const noexcept
	{
		return std::move(unsigned_integer());
	}
	static unsigned_integer&& random() noexcept
	{
		return std::move(unsigned_integer());
	}
	static unsigned_integer&& sparse() noexcept
	{
		return std::move(unsigned_integer());
	}
	constexpr bool operator==(const unsigned_integer other) const noexcept
	{
		return true;
	}
	constexpr bool operator!=(const unsigned_integer other) const noexcept
	{
		return false;
	}
};

template<size_t COUNT_BITS, bool COMPACT>
std::ostream& operator<<(std::ostream& str, const unsigned_integer<COUNT_BITS, COMPACT>& value) noexcept
{
	str << static_cast<std::string>(value);
	return str;
}