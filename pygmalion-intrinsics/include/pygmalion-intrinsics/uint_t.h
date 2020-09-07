#include "uint_t_traits.h"
#include "uint_t_detail.h"

template<size_t COUNT_BITS, bool IS_COMPACT, typename = typename std::enable_if<detail::isMultiWord<COUNT_BITS, IS_COMPACT>() || detail::isSingleWord<COUNT_BITS, IS_COMPACT>() || detail::isSingleBit<COUNT_BITS, IS_COMPACT>() || detail::isEmpty<COUNT_BITS, IS_COMPACT>()>::type>
class uint_t
{
};

template<size_t COUNT_BITS, bool IS_COMPACT>
class uint_t<COUNT_BITS, IS_COMPACT, typename std::enable_if<detail::isMultiWord<COUNT_BITS, IS_COMPACT>()>::type> :
	detail::base
{
public:
	constexpr static const bool isCompact{ IS_COMPACT };
	constexpr static const size_t countBits{ COUNT_BITS };
	constexpr static const size_t countBytes{ (countBits + 7) / 8 };
	using wordType = typename detail::uint_t_traits<countBytes, isCompact>::wordType;
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
	template<size_t INDEX>
	constexpr static wordType normalizeWords(const wordType word) noexcept
	{
		if constexpr (INDEX == (countWords - 1))
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
	template<size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM, size_t... INDICES>
	constexpr static std::array<wordType, SIZE> nullaryTransformWords(std::index_sequence<INDICES...>, const LAMBDA_TRANSFORM& transform) noexcept
	{
		if constexpr (NORMALIZE)
			return std::array<wordType, SIZE>{ (uint_t::normalizeWords<INDICES>(transform(INDICES)))... };
		else
			return std::array<wordType, SIZE>{ (transform(INDICES))... };
	}
	template<size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM, size_t... INDICES>
	constexpr static std::array<wordType, SIZE> unaryTransformWords(const std::array<wordType, SIZE>& words, std::index_sequence<INDICES...>, const LAMBDA_TRANSFORM& transform) noexcept
	{
		if constexpr (NORMALIZE)
			return std::array<wordType, SIZE>{ (uint_t::normalizeWords<INDICES>(transform(words[INDICES], INDICES)))... };
		else
			return std::array<wordType, SIZE>{ (transform(words[INDICES], INDICES))... };
	}
	template<size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM, size_t... INDICES>
	constexpr static std::array<wordType, SIZE> binaryTransformWords(const std::array<wordType, SIZE>& words1, const std::array<wordType, SIZE>& words2, std::index_sequence<INDICES...>, const LAMBDA_TRANSFORM& transform) noexcept
	{
		if constexpr (NORMALIZE)
			return std::array<wordType, SIZE>{ (uint_t::normalizeWords<INDICES>(transform(words1[INDICES], words2[INDICES], INDICES)))... };
		else
			return std::array<wordType, SIZE>{ (transform(words1[INDICES], words2[INDICES], INDICES))... };
	}
	template<size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM, size_t... INDICES>
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
	template<size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM>
	constexpr static std::array<wordType, SIZE> nullaryTransformWords(const LAMBDA_TRANSFORM& create) noexcept
	{
		return uint_t::nullaryTransformWords<SIZE, NORMALIZE>(std::make_index_sequence<countWords>{}, create);
	}
	template<size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM>
	constexpr static std::array<wordType, SIZE> unaryTransformWords(const std::array<wordType, SIZE>& words, LAMBDA_TRANSFORM transform) noexcept
	{
		return uint_t::unaryTransformWords<SIZE, NORMALIZE>(words, std::make_index_sequence<countWords>{}, transform);
	}
	template<size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM>
	constexpr static std::array<wordType, SIZE> binaryTransformWords(const std::array<wordType, SIZE>& words1, const std::array<wordType, SIZE>& words2, LAMBDA_TRANSFORM transform) noexcept
	{
		return uint_t::binaryTransformWords<SIZE, NORMALIZE>(words1, words2, std::make_index_sequence<countWords>{}, transform);
	}
	template<size_t SIZE, typename T, typename = typename std::enable_if<std::is_unsigned<T>::value>::type >
	constexpr static std::array<wordType, SIZE> encodeValue(const T value) noexcept
	{
		constexpr const size_t countBitsType{ sizeof(T) * CHAR_BIT };
		if constexpr (countBitsPerWord < countBitsType)
		{
			const auto lambda = [value, countBitsType](const size_t index)->wordType
			{
				const T mask{ static_cast<T>((T(1) << countBitsPerWord) - T(1)) };
				const size_t shift{ countBitsPerWord * index };
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
			return uint_t::nullaryTransformWords<countWords, true>(lambda);
		}
		else
		{
			const auto lambda = [value](const size_t index)->wordType
			{
				const size_t shift{ countBitsPerWord * index };
				return (value) >> shift;
			};
			return uint_t::nullaryTransformWords<countWords, true>(lambda);
		}
	}
	constexpr uint_t(const std::array<wordType, countWords>& words, bool) noexcept :
		m_Words{ words }
	{	}
	std::array<wordType, countWords> m_Words;
public:
	template<typename T, typename = typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value>::type>
	constexpr uint_t(const T value) noexcept :
		m_Words{ uint_t::encodeValue<countWords>(static_cast<typename std::make_unsigned<T>::type>(value)) }
	{}
	template<typename T, typename = typename std::enable_if<std::is_unsigned<T>::value && ((sizeof(T)* CHAR_BIT) >= countBits) && !std::is_same<bool, T>::value>::type>
	constexpr operator T() const noexcept
	{
		T result{ 0 };
		size_t shift{ 0 };
		for (size_t w = 0; (w < countWords) && (shift < (sizeof(T) * CHAR_BIT)); w++, shift += countBitsPerWord)
			result |= static_cast<T>(static_cast<T>(m_Words[w]) << shift);
		return result;
	}
	constexpr wordType word(const size_t index) const noexcept
	{
		assert(index < countWords);
		return m_Words[index];
	}
	constexpr uint_t() noexcept :
		m_Words{ make_array_n<countWords,wordType>(0) }
	{	}
	constexpr uint_t(const uint_t&) noexcept = default;
	constexpr uint_t(uint_t&&) noexcept = default;
	constexpr uint_t& operator=(const uint_t&) noexcept = default;
	constexpr uint_t& operator=(uint_t&&) noexcept = default;
	constexpr operator bool() const noexcept
	{
		for (size_t w = 0; w < countWords; w++)
		{
			if (m_Words[w])
				return true;
		}
		return false;
	}
	size_t populationCount() const noexcept
	{
		return popcnt::implementation(m_Words);
	}
	operator std::string() const noexcept
	{
		std::stringstream sstr;
		if constexpr (isCompact)
			sstr << "(" << countBits << ")";
		else
			sstr << "{" << countBits << "}";
		sstr << "[";
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
		sstr << "]";
		return sstr.str();
	}
	constexpr auto operator~() const noexcept
	{
		constexpr const auto lambda = [](const wordType a, const size_t)->wordType { return ~a; };
		return uint_t(uint_t::unaryTransformWords<countWords, true>(m_Words, lambda), false);
	}
	constexpr uint_t& operator&=(const uint_t& other) noexcept
	{
		constexpr const auto lambda = [&other](wordType& a, const wordType b, const size_t)->wordType { a &= b; };
		uint_t::binaryTransformWordsInplace<countWords, false>(m_Words, other.m_Words, lambda);
		return *this;
	}
	constexpr uint_t& operator|=(const uint_t& other) noexcept
	{
		constexpr const auto lambda = [&other](wordType& a, const wordType b, const size_t)->wordType { a |= b; };
		uint_t::binaryTransformWordsInplace<countWords, false>(m_Words, other.m_Words, lambda);
		return *this;
	}
	constexpr uint_t& operator^=(const uint_t& other) noexcept
	{
		constexpr const auto lambda = [](wordType& a, const wordType b, const size_t)->void { a ^= b; };
		uint_t::binaryTransformWordsInplace<countWords, false>(m_Words, other.m_Words, lambda);
		return *this;
	}
	constexpr auto operator&(const uint_t& other) const noexcept
	{
		constexpr const auto lambda = [](const wordType a, const wordType b, const size_t)->wordType { return a & b; };
		return uint_t(uint_t::binaryTransformWords<countWords, false>(m_Words, other.m_Words, lambda), false);
	}
	constexpr auto operator|(const uint_t& other) const noexcept
	{
		constexpr const auto lambda = [](const wordType a, const wordType b, const size_t)->wordType { return a | b; };
		return uint_t(uint_t::binaryTransformWords<countWords, false>(m_Words, other.m_Words, lambda), false);
	}
	constexpr auto operator^(const uint_t& other) const noexcept
	{
		constexpr const auto lambda = [](const wordType a, const wordType b, const size_t)->wordType { return a ^ b; };
		return uint_t(uint_t::binaryTransformWords<countWords, false>(m_Words, other.m_Words, lambda), false);
	}
	constexpr auto operator+(const uint_t& other) const noexcept
	{
		std::array<wordType, countWords> results{ make_array_n<countWords,wordType>(wordType(0)) };
		bool carryFlag{ false };
		for (size_t i = 0; i < countWords - 1; i++)
		{
			const wordType temp{ static_cast<wordType>(carryFlag + m_Words[i]) };
			carryFlag = !temp;
			results[i] = temp + other.m_Words[i];
			carryFlag |= results[i] < temp;
		}
		results[countWords - 1] = uint_t::normalizeHighestWord(carryFlag + m_Words[countWords - 1] + other.m_Words[countWords - 1]);
		return uint_t(results, false);
	}
	constexpr uint_t& operator+=(const uint_t& other)  noexcept
	{
		bool carryFlag{ false };
		for (size_t i = 0; i < countWords - 1; i++)
		{
			const wordType temp{ static_cast<wordType>(carryFlag + other.m_Words[i]) };
			carryFlag = !temp;
			m_Words[i] += temp;
			carryFlag |= m_Words[i] < temp;
		}
		m_Words[countWords - 1] = uint_t::normalizeHighestWord(carryFlag + m_Words[countWords - 1] + other.m_Words[countWords - 1]);
		return *this;
	}
	static auto random() noexcept
	{
		const auto lambda = [](const size_t index)->wordType
		{
			wordType w{ wordType(0) };
			for (size_t c = 0; c < sizeof(wordType); c++)
			{
				const wordType randomChar{ static_cast<wordType>(uint_t::nextRandom32() % UCHAR_MAX) };
				w |= randomChar << (CHAR_BIT * c);
			}
			return w;
		};
		return uint_t(uint_t::nullaryTransformWords<countWords, true>(lambda), false);
	}
	static uint_t&& sparse() noexcept
	{
		const auto lambda = [](const size_t index)->wordType
		{
			wordType w{ wordType(0) };
			for (size_t c = 0; c < sizeof(wordType); c++)
			{
				const wordType randomChar{ static_cast<wordType>((uint_t::nextRandom32() % UCHAR_MAX) & (uint_t::nextRandom32() % UCHAR_MAX) & (uint_t::nextRandom32() % UCHAR_MAX)) };
				w |= randomChar << (CHAR_BIT * c);
			}
			return w;
		};
		return std::move(uint_t(uint_t::nullaryTransformWords<countWords, true>(lambda), false));
	}
	constexpr bool operator==(const uint_t& other) const noexcept
	{
		for (size_t index = 0; index < countWords; index++)
		{
			if (other.m_Words[index] != m_Words[index])
				return false;
		}
		return true;
	}
	constexpr bool operator!=(const uint_t& other) const noexcept
	{
		return !((*this) == other);
	}
	static const inline std::string populationCount_Intrinsic{ popcnt::implementationName<countWords,wordType>() };
	template<size_t COUNT_BITS2, bool IS_COMPACT2>
	constexpr uint_t(const uint_t<COUNT_BITS2, IS_COMPACT2>& other) noexcept :
		m_Words{ uint_t::nullaryTransformWords<countWords,false>([this,&other](const size_t currentWord)->wordType {
					using wordType2 = typename uint_t<COUNT_BITS2,IS_COMPACT2>::wordType;
					size_t currentWordBit{ 0 };
					size_t currentBit{ currentWord * this->countBitsPerWord };
					size_t currentRemaining{ this->countBitsPerWord };
					size_t otherWord{ currentBit / other.countBitsPerWord };
					size_t otherWordBit{ currentBit % other.countBitsPerWord };
					size_t otherBit{ otherWord * other.countBitsPerWord + otherWordBit };
					size_t otherRemaining{ other.countBitsPerWord - otherWordBit };
					constexpr const size_t slice{std::min(this->countBitsPerWord,other.countBitsPerWord)};
					constexpr const wordType2 mask{ (wordType2(1) << slice) - wordType(1) };
					wordType result{ wordType(0) };
					while (otherBit < other.countBits)
					{
						result |= ((other.word(otherWord) & (mask << otherWordBit)) >> otherWordBit) << currentWordBit;
						const size_t increment{std::min(slice,std::min(otherRemaining,currentRemaining))};
						currentWordBit += increment;
						if (currentWordBit == this->countBitsPerWord)
							return result;
						otherWordBit += increment;
						otherBit += increment;
						if (otherWordBit >= other.countBitsPerWord)
						{
							otherWordBit = 0;
							otherWord++;
						}
					}
					return result;
				}) }
	{}
};

template<size_t COUNT_BITS, bool IS_COMPACT>
class uint_t<COUNT_BITS, IS_COMPACT, typename std::enable_if <detail::isSingleWord<COUNT_BITS, IS_COMPACT>()>::type> :
	detail::base
{
public:
	constexpr static const bool isCompact{ IS_COMPACT };
	constexpr static const size_t countBits{ COUNT_BITS };
	constexpr static const size_t countBytes{ (countBits + 7) / 8 };
	using wordType = typename detail::uint_t_traits<countBytes, isCompact>::wordType;
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
	constexpr uint_t(const wordType word, bool) noexcept :
		m_Word{ word }
	{	}
public:
	template<typename T, typename = typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value>::type>
	constexpr uint_t(const T value) noexcept :
		m_Word{ static_cast<wordType>(static_cast<typename std::make_unsigned<T>::type>(value)) }
	{}
	template<typename T, typename = typename std::enable_if<std::is_unsigned<T>::value && ((sizeof(T)* CHAR_BIT) >= countBits) && !std::is_same<bool, T>::value>::type>
	constexpr operator T() const noexcept
	{
		return static_cast<T>(m_Word);
	}
	constexpr wordType word(const size_t index) const noexcept
	{
		assert(index == 0);
		return m_Word;
	}
	constexpr uint_t() noexcept :
		m_Word{ wordType(0) }
	{	}
	constexpr operator bool() const noexcept
	{
		return m_Word != wordType(0);
	}
	constexpr uint_t(const uint_t&) noexcept = default;
	constexpr uint_t(uint_t&&) noexcept = default;
	constexpr uint_t& operator=(const uint_t&) noexcept = default;
	constexpr uint_t& operator=(uint_t&&) noexcept = default;
	size_t populationCount() const noexcept
	{
		return popcnt::implementation<1, wordType>({ m_Word });
	}
	operator std::string() const noexcept
	{
		std::stringstream sstr;
		if constexpr (isCompact)
			sstr << "(" << countBits << ")";
		else
			sstr << "{" << countBits << "}";
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
	constexpr uint_t&& operator~() const noexcept
	{
		return std::move(uint_t(normalizeWord(~m_Word), false));
	}
	constexpr uint_t& operator&=(const uint_t& other) noexcept
	{
		m_Word = m_Word & other.m_Word;
		return *this;
	}
	constexpr uint_t& operator+=(const uint_t& other) noexcept
	{
		m_Word = normalizeWord(m_Word + other.m_Word);
		return *this;
	}
	constexpr uint_t& operator*=(const uint_t& other) noexcept
	{
		m_Word = normalizeWord(m_Word * other.m_Word);
		return *this;
	}
	constexpr uint_t& operator|=(const uint_t& other) noexcept
	{
		m_Word = m_Word | other.m_Word;
		return *this;
	}
	constexpr uint_t& operator^=(const uint_t& other) noexcept
	{
		m_Word = m_Word & other.m_Word;
		return *this;
	}
	constexpr uint_t&& operator&(const uint_t& other) const noexcept
	{
		return std::move(uint_t(m_Word & other.m_Word, false));
	}
	constexpr uint_t&& operator|(const uint_t& other) const noexcept
	{
		return std::move(uint_t(m_Word | other.m_Word, false));
	}
	constexpr uint_t&& operator^(const uint_t& other) const noexcept
	{
		return std::move(uint_t(m_Word ^ other.m_Word, false));
	}
	constexpr uint_t&& operator+(const uint_t& other) const noexcept
	{
		return std::move(uint_t(normalizeWord(m_Word + other.m_Word), false));
	}
	constexpr uint_t&& operator*(const uint_t& other) const noexcept
	{
		return std::move(uint_t(normalizeWord(m_Word * other.m_Word), false));
	}
	static uint_t random() noexcept
	{
		wordType w{ wordType(0) };
		for (size_t c = 0; c < sizeof(wordType); c++)
		{
			const wordType randomChar{ static_cast<wordType>(uint_t::nextRandom32() % UCHAR_MAX) };
			w |= randomChar << (CHAR_BIT * c);
		}
		return uint_t(normalizeWord(std::move(w)), false);
	}
	static uint_t sparse() noexcept
	{
		wordType w{ wordType(0) };
		for (size_t c = 0; c < sizeof(wordType); c++)
		{
			const wordType randomChar{ static_cast<wordType>((uint_t::nextRandom32() % UCHAR_MAX) & (uint_t::nextRandom32() % UCHAR_MAX) & (uint_t::nextRandom32() % UCHAR_MAX)) };
			w |= randomChar << (CHAR_BIT * c);
		}
		return uint_t(normalizeWord(std::move(w)), false);
	}
	constexpr bool operator==(const uint_t& other) const noexcept
	{
		return m_Word == other.m_Word;
	}
	constexpr bool operator!=(const uint_t& other) const noexcept
	{
		return m_Word != other.m_Word;
	}
	static const inline std::string populationCount_Intrinsic{ popcnt::implementationName<countWords,wordType>() };
	template<size_t COUNT_BITS2, bool IS_COMPACT2>
	constexpr uint_t(const uint_t<COUNT_BITS2, IS_COMPACT2>& other) noexcept :
		m_Word{ ([this,&other]()->wordType {
					using wordType2 = typename uint_t<COUNT_BITS2,IS_COMPACT2>::wordType;
					size_t currentWordBit{ 0 };
					size_t currentBit{ 0 };
					size_t currentRemaining{ this->countBitsPerWord };
					size_t otherWord{ currentBit / other.countBitsPerWord };
					size_t otherWordBit{ currentBit % other.countBitsPerWord };
					size_t otherBit{ otherWord * other.countBitsPerWord + otherWordBit };
					size_t otherRemaining{ other.countBitsPerWord - otherWordBit };
					constexpr const size_t slice{std::min(this->countBitsPerWord,other.countBitsPerWord)};
					constexpr const wordType2 mask{ (wordType2(1) << slice) - wordType(1) };
					wordType result{ wordType(0) };
					while (otherBit < other.countBits)
					{
						result |= ((other.word(otherWord) & (mask << otherWordBit)) >> otherWordBit) << currentWordBit;
						const size_t increment{std::min(slice,std::min(otherRemaining,currentRemaining))};
						currentWordBit += increment;
						if (currentWordBit == this->countBitsPerWord)
							return result;
						otherWordBit += increment;
						otherBit += increment;
						if (otherWordBit >= other.countBitsPerWord)
						{
							otherWordBit = 0;
							otherWord++;
						}
					}
					return result;
				})() }
	{}
};

template<size_t COUNT_BITS, bool IS_COMPACT>
class uint_t<COUNT_BITS, IS_COMPACT, typename std::enable_if <detail::isSingleBit<COUNT_BITS, IS_COMPACT>()>::type> :
	detail::base
{
public:
	constexpr static const bool isCompact{ IS_COMPACT };
	constexpr static const size_t countBits{ 1 };
	constexpr static const size_t countBytes{ (countBits + 7) / 8 };
	using wordType = bool;
	constexpr static const size_t countBitsPerWord{ 1 };
	constexpr static const size_t countWords{ 1 };
	constexpr static const size_t countStorageBits{ countBitsPerWord };
private:
	wordType m_Word;
	constexpr uint_t(const wordType word, bool) noexcept :
		m_Word{ word }
	{	}
public:
	template<typename T, typename = typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value>::type>
	constexpr uint_t(const T value) noexcept : m_Word{ static_cast<wordType>(value) } {}
	template<typename T, typename = typename std::enable_if<std::is_unsigned<T>::value && ((sizeof(T)* CHAR_BIT) >= countBits) && !std::is_same<bool, T>::value>::type>
	constexpr operator T() const noexcept
	{
		return static_cast<T>(m_Word);
	}
	constexpr wordType word(const size_t index) const noexcept
	{
		assert(index == 0);
		return m_Word;
	}
	constexpr uint_t() noexcept :
		m_Word{ wordType(0) }
	{	}
	constexpr operator bool() const noexcept
	{
		return m_Word;
	}
	constexpr uint_t(const uint_t&) noexcept = default;
	constexpr uint_t(uint_t&&) noexcept = default;
	constexpr uint_t& operator=(const uint_t&) noexcept = default;
	constexpr uint_t& operator=(uint_t&&) noexcept = default;
	size_t populationCount() const noexcept
	{
		return popcnt::implementation<1, wordType>({ m_Word });
	}
	operator std::string() const noexcept
	{
		std::stringstream sstr;
		if constexpr (isCompact)
			sstr << "(1)";
		else
			sstr << "{1}";
		sstr << "[";
		sstr << (m_Word ? '1' : '0');
		sstr << "]";
		return sstr.str();
	}
	constexpr uint_t operator~() const noexcept
	{
		return std::move(uint_t(!m_Word, false));
	}
	constexpr uint_t& operator*=(const uint_t other) noexcept
	{
		m_Word &= other.m_Word;
		return *this;
	}
	constexpr uint_t& operator+=(const uint_t other) noexcept
	{
		m_Word ^= other.m_Word;
		return *this;
	}
	constexpr uint_t& operator&=(const uint_t other) noexcept
	{
		m_Word &= other.m_Word;
		return *this;
	}
	constexpr uint_t& operator|=(const uint_t other) noexcept
	{
		m_Word |= other.m_Word;
		return *this;
	}
	constexpr uint_t& operator^=(const uint_t other) noexcept
	{
		m_Word ^= other.m_Word;
		return *this;
	}
	constexpr uint_t operator+(const uint_t other) const noexcept
	{
		return uint_t(m_Word ^ other.m_Word, false);
	}
	constexpr uint_t operator*(const uint_t& other) const noexcept
	{
		return uint_t(m_Word & other.m_Word, false);
	}
	constexpr uint_t operator&(const uint_t other) const noexcept
	{
		return uint_t(m_Word & other.m_Word, false);
	}
	constexpr uint_t operator|(const uint_t other) const noexcept
	{
		return uint_t(m_Word | other.m_Word, false);
	}
	constexpr uint_t operator^(const uint_t other) const noexcept
	{
		return uint_t(m_Word ^ other.m_Word, false);
	}
	static uint_t random() noexcept
	{
		const wordType w{ static_cast<wordType>(uint_t::nextRandom32() % 2) };
		return uint_t(std::move(w), false);
	}
	static uint_t sparse() noexcept
	{
		const wordType a{ static_cast<wordType>(uint_t::nextRandom32() % 2) };
		const wordType b{ static_cast<wordType>(uint_t::nextRandom32() % 2) };
		const wordType c{ static_cast<wordType>(uint_t::nextRandom32() % 2) };
		return uint_t(a && b && c, false);
	}
	constexpr bool operator==(const uint_t other) const noexcept
	{
		return m_Word == other.m_Word;
	}
	constexpr bool operator!=(const uint_t other) const noexcept
	{
		return m_Word != other.m_Word;
	}
	static const inline std::string populationCount_Intrinsic{ popcnt::implementationName<countWords,wordType>() };
	template<size_t COUNT_BITS2, bool IS_COMPACT2>
	constexpr uint_t(const uint_t<COUNT_BITS2, IS_COMPACT2>& other) noexcept :
		m_Word{ ([this,&other]()->wordType {
					using wordType2 = typename uint_t<COUNT_BITS2,IS_COMPACT2>::wordType;
					size_t currentWordBit{ 0 };
					size_t currentBit{ 0 };
					size_t currentRemaining{ this->countBitsPerWord };
					size_t otherWord{ currentBit / other.countBitsPerWord };
					size_t otherWordBit{ currentBit % other.countBitsPerWord };
					size_t otherBit{ otherWord * other.countBitsPerWord + otherWordBit };
					size_t otherRemaining{ other.countBitsPerWord - otherWordBit };
					constexpr const size_t slice{std::min(this->countBitsPerWord,other.countBitsPerWord)};
					constexpr const wordType2 mask{ (wordType2(1) << slice) - wordType(1) };
					wordType result{ wordType(0) };
					while (otherBit < other.countBits)
					{
						result |= ((other.word(otherWord) & (mask << otherWordBit)) >> otherWordBit) << currentWordBit;
						const size_t increment{std::min(slice,std::min(otherRemaining,currentRemaining))};
						currentWordBit += increment;
						if (currentWordBit == this->countBitsPerWord)
							return result;
						otherWordBit += increment;
						otherBit += increment;
						if (otherWordBit >= other.countBitsPerWord)
						{
							otherWordBit = 0;
							otherWord++;
						}
					}
					return result;
				})() }
	{}
};

template<size_t COUNT_BITS, bool IS_COMPACT>
class uint_t<COUNT_BITS, IS_COMPACT, typename std::enable_if<detail::isEmpty<COUNT_BITS, IS_COMPACT>()>::type> :
	detail::base
{
public:
	constexpr static const bool isCompact{ IS_COMPACT };
	constexpr static const size_t countBits{ 0 };
	constexpr static const size_t countBytes{ 0 };
	using wordType = bool;
	constexpr static const size_t countBitsPerWord{ 0 };
	constexpr static const size_t countWords{ 0 };
	constexpr static const size_t countStorageBits{ 0 };
private:
public:
	template<typename T, typename = typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value>::type>
	constexpr uint_t(const T value) noexcept :uint_t()
	{

	}
	template<typename T, typename = typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<bool, T>::value>::type>
	constexpr operator T() const noexcept
	{
		return static_cast<T>(0);
	}
	constexpr wordType word(const size_t index) const noexcept
	{
		assert(0);
		return 0;
	}
	constexpr uint_t() noexcept = default;
	constexpr uint_t(const uint_t&) noexcept = default;
	constexpr uint_t(uint_t&&) noexcept = default;
	constexpr uint_t& operator=(const uint_t&) noexcept = default;
	constexpr uint_t& operator=(uint_t&&) noexcept = default;
	constexpr operator bool() const noexcept
	{
		return false;
	}
	size_t populationCount() const noexcept
	{
		return popcnt::implementation<0, wordType>({});
	}
	operator std::string() const noexcept
	{
		std::stringstream sstr;
		if constexpr (isCompact)
			sstr << "(0)";
		else
			sstr << "{0}";
		sstr << "[]";
		return sstr.str();
	}
	constexpr uint_t operator~() const noexcept
	{
		return *this;
	}
	constexpr uint_t operator*=(const uint_t other) noexcept
	{
		return *this;
	}
	constexpr uint_t operator+=(const uint_t other) noexcept
	{
		return *this;
	}
	constexpr uint_t operator&=(const uint_t other) noexcept
	{
		return *this;
	}
	constexpr uint_t operator|=(const uint_t other) noexcept
	{
		return *this;
	}
	constexpr uint_t operator^=(const uint_t other) noexcept
	{
		return *this;
	}
	constexpr uint_t operator+(const uint_t other) const noexcept
	{
		return *this;
	}
	constexpr uint_t operator*(const uint_t& other) const noexcept
	{
		return *this;
	}
	constexpr uint_t operator&(const uint_t other) const noexcept
	{
		return *this;
	}
	constexpr uint_t operator|(const uint_t other) const noexcept
	{
		return *this;
	}
	constexpr uint_t operator^(const uint_t other) const noexcept
	{
		return *this;
	}
	static uint_t random() noexcept
	{
		return uint_t();
	}
	static uint_t sparse() noexcept
	{
		return uint_t();
	}
	constexpr bool operator==(const uint_t other) const noexcept
	{
		return true;
	}
	constexpr bool operator!=(const uint_t other) const noexcept
	{
		return false;
	}
	static const inline std::string populationCount_Intrinsic{ popcnt::implementationName<0,wordType>() };
	template<size_t COUNT_BITS2, bool IS_COMPACT2>
	constexpr uint_t(const uint_t<COUNT_BITS2, IS_COMPACT2>& other) noexcept
	{}
};

template<size_t COUNT_BITS>
using uint_least_t = uint_t<COUNT_BITS, true>;

template<size_t COUNT_BITS>
using uint_fast_t = uint_t<COUNT_BITS, false>;

template<size_t COUNT_BITS, bool IS_COMPACT>

std::ostream& operator<<(std::ostream& str, const uint_t<COUNT_BITS, IS_COMPACT>& value) noexcept
{
	str << static_cast<std::string>(value);
	return str;
}
