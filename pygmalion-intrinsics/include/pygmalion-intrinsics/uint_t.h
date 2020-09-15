#include "uint_t_traits.h"
#include "uint_t_detail.h"

template<size_t COUNT_BITS, bool IS_COMPACT, typename = typename std::enable_if<true>::type>
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
	using doubleType = typename detail::uint_t_traits<countBytes, isCompact>::doubleType;
	using halfType = typename detail::uint_t_traits<countBytes, isCompact>::halfType;
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
	constexpr static wordType sumWords(wordType& accumulator, const wordType operand, const wordType carry) noexcept
	{
		if constexpr (std::is_same<wordType, doubleType>::value)
		{
			accumulator += carry;
			wordType newCarry{ accumulator < carry };
			accumulator += operand;
			newCarry += (accumulator < operand);
			return newCarry;
		}
		else
		{
			constexpr const doubleType mask{ static_cast<doubleType>(static_cast<doubleType>(doubleType(1) << countBitsPerWord) - doubleType(1)) };
			const doubleType sum{ static_cast<doubleType>(static_cast<doubleType>(carry) + static_cast<doubleType>(operand) + static_cast<doubleType>(accumulator)) };
			accumulator = static_cast<wordType>(sum & mask);
			return (sum & static_cast<doubleType>(mask << countBitsPerWord)) >> countBitsPerWord;
		}
	}
	constexpr static wordType subtractWords(wordType& accumulator, const wordType operand, const wordType carry) noexcept
	{
		if constexpr (std::is_same<wordType, doubleType>::value)
		{
			const wordType old{ accumulator };
			accumulator -= carry;
			wordType newCarry{ accumulator > old };
			const wordType old2{ accumulator };
			accumulator -= operand;
			newCarry += (accumulator > old2);
			return newCarry;
		}
		else
		{
			constexpr const doubleType mask{ static_cast<doubleType>(static_cast<doubleType>(doubleType(1) << countBitsPerWord) - doubleType(1)) };
			const doubleType difference{ static_cast<doubleType>(static_cast<doubleType>(accumulator) - (static_cast<doubleType>(carry) + static_cast<doubleType>(operand))) };
			accumulator = static_cast<wordType>(difference & mask);
			return -static_cast<wordType>((difference & static_cast<doubleType>(mask << countBitsPerWord)) >> countBitsPerWord);
		}
	}
	constexpr static const void multiplyWords(const wordType A, const wordType B, wordType& R_low, wordType& R_high) noexcept
	{
		if constexpr (std::is_same<wordType, doubleType>::value)
		{
			constexpr const size_t shift{ countBitsPerWord >> 1 };
			constexpr const wordType mask_low{ static_cast<wordType>(static_cast<wordType>(wordType(1) << shift) - wordType(1)) };
			constexpr const wordType mask_high{ static_cast<wordType>(mask_low << shift) };
			const halfType low_A{ static_cast<halfType>(A & mask_low) };
			const halfType low_B{ static_cast<halfType>(B & mask_low) };
			const halfType high_A{ static_cast<halfType>(static_cast<wordType>(A & mask_high) >> shift) };
			const halfType high_B{ static_cast<halfType>(static_cast<wordType>(B & mask_high) >> shift) };
			const wordType ll{ static_cast<wordType>(static_cast<wordType>(low_A) * static_cast<wordType>(low_B)) };
			const wordType lh{ static_cast<wordType>(static_cast<wordType>(low_A) * static_cast<wordType>(high_B)) };
			const wordType hl{ static_cast<wordType>(static_cast<wordType>(high_A) * static_cast<wordType>(low_B)) };
			const wordType hh{ static_cast<wordType>(static_cast<wordType>(high_A) * static_cast<wordType>(high_B)) };
			bool carryFlag{ false };
			R_high = wordType(0);
			R_low = ll;
			const wordType low_lh{ static_cast<wordType>((lh & mask_low) << shift) };
			R_low += low_lh;
			R_high += static_cast<wordType>(R_low < low_lh);
			const wordType low_hl{ static_cast<wordType>((hl & mask_low) << shift) };
			R_low += low_hl;
			R_high += static_cast<wordType>(R_low < low_hl);
			R_high += hh;
			const wordType high_lh{ static_cast<wordType>((lh & mask_high) >> shift) };
			R_high += high_lh;
			const wordType high_hl{ static_cast<wordType>((hl & mask_high) >> shift) };
			R_high += high_hl;
		}
		else
		{
			const doubleType result{ static_cast<doubleType>(static_cast<doubleType>(A) * static_cast<doubleType>(B)) };
			constexpr const doubleType mask_low{ static_cast<doubleType>(static_cast<doubleType>(doubleType(1) << countBitsPerWord) - doubleType(1)) };
			constexpr const doubleType mask_high{ static_cast<doubleType>(mask_low << countBitsPerWord) };
			R_low = static_cast<wordType>(result & mask_low);
			R_high = static_cast<wordType>((result & mask_high) >> countBitsPerWord);
		}
	}
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
	constexpr explicit operator bool() const noexcept
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
	bool bitscanForward(size_t& bit) const noexcept
	{
		return bsf::implementation(m_Words, bit);
	}
	bool bitscanReverse(size_t& bit) const noexcept
	{
		return bsr::implementation(m_Words, bit);
	}
	/*	uint_t extractPattern(const uint_t& mask) const noexcept
		{
			uint_t res{ 0 };
			uint_t bb{ 1 };
			while (mask)
			{
				if ((*this) & mask & (-mask))
					res |= bb;
				mask &= mask - 1;
				bb <<= 1;
			}
			return res;
		}*/
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
	constexpr uint_t operator~() const noexcept
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
	constexpr uint_t operator&(const uint_t& other) const noexcept
	{
		constexpr const auto lambda = [](const wordType a, const wordType b, const size_t)->wordType { return a & b; };
		return uint_t(uint_t::binaryTransformWords<countWords, false>(m_Words, other.m_Words, lambda), false);
	}
	constexpr uint_t operator|(const uint_t& other) const noexcept
	{
		constexpr const auto lambda = [](const wordType a, const wordType b, const size_t)->wordType { return a | b; };
		return uint_t(uint_t::binaryTransformWords<countWords, false>(m_Words, other.m_Words, lambda), false);
	}
	constexpr uint_t operator^(const uint_t& other) const noexcept
	{
		constexpr const auto lambda = [](const wordType a, const wordType b, const size_t)->wordType { return a ^ b; };
		return uint_t(uint_t::binaryTransformWords<countWords, false>(m_Words, other.m_Words, lambda), false);
	}
	constexpr uint_t operator+(const uint_t& other) const noexcept
	{
		std::array<wordType, countWords> results{ m_Words };
		wordType carry{ 0 };
		for (size_t i = 0; i < countWords - 1; i++)
			carry = sumWords(results[i], other.m_Words[i], carry);
		results[countWords - 1] = uint_t::normalizeHighestWord(carry + results[countWords - 1] + other.m_Words[countWords - 1]);
		return uint_t(results, false);
	}
	constexpr uint_t operator-(const uint_t& other) const noexcept
	{
		std::array<wordType, countWords> results{ m_Words };
		wordType carry{ 0 };
		for (size_t i = 0; i < countWords - 1; i++)
			carry = subtractWords(results[i], other.m_Words[i], carry);
		results[countWords - 1] = uint_t::normalizeHighestWord(results[countWords - 1] - (other.m_Words[countWords - 1] + carry));
		return uint_t(results, false);
	}
	constexpr uint_t operator*(const uint_t& other) const noexcept
	{
		using halfType = wordType;
		std::array<wordType, countWords> results{ make_array_n<countWords,wordType>(wordType(0)) };
		std::array<wordType, countWords> temp{ make_array_n<countWords,wordType>(wordType(0)) };
		for (size_t i = 0; i < countWords; i++)
		{
			wordType carry{ wordType(0) };
			wordType carry2{ 0 };
			for (size_t j = 0; j < (countWords - i); j++)
			{
				wordType low{ wordType(0) };
				wordType high{ wordType(0) };
				multiplyWords(m_Words[i], other.m_Words[j], low, high);
				temp[j] = wordType(0);
				carry = sumWords(temp[j], low, carry);
				carry2 = sumWords(carry, high, carry2);
			}
			carry = 0;
			for (size_t j = 0; j < (countWords - i); j++)
				carry = sumWords(results[i + j], temp[j], carry);
		}
		results[countWords - 1] = uint_t::normalizeHighestWord(results[countWords - 1]);
		return uint_t(results, false);
	}
	constexpr uint_t operator/(const uint_t& other) const noexcept
	{
		assert(other);
		uint_t<countBits + 1, isCompact> dividend{ *this };
		uint_t<countBits + 1, isCompact> denom{ other };
		uint_t<countBits + 1, isCompact> current{ uint_t<countBits + 1,isCompact>(1) };
		uint_t<countBits + 1, isCompact> answer{ uint_t<countBits + 1,isCompact>(0) };

		if (denom > dividend)
			return uint_t(0);

		if (denom == dividend)
			return uint_t(1);

		while (denom <= dividend) 
		{
			denom = denom << size_t(1);
			current = current << size_t(1);
		}

		current = current >> size_t(1);
		denom = denom >> size_t(1);

		while (current) 
		{
			if (dividend >= denom)
			{
				dividend = dividend - denom;
				answer = answer | current;
			}
			current = current >> size_t(1);
			denom = denom >> size_t(1);
		}
		return static_cast<uint_t>(answer);
	}
	constexpr uint_t& operator+=(const uint_t& other)  noexcept
	{
		wordType carry{ 0 };
		for (size_t i = 0; i < countWords - 1; i++)
			carry = sumWords(m_Words[i], other.m_Words[i], carry);
		m_Words[countWords - 1] = uint_t::normalizeHighestWord(carry + m_Words[countWords - 1] + other.m_Words[countWords - 1]);
		return *this;
	}
	constexpr uint_t& operator++() noexcept
	{
		wordType carry{ 1 };
		size_t i{ 0 };
		while (carry && (i < (countWords - 1)))
		{
			m_Words[i]++;
			carry = (m_Words[i] == 0);
			i++;
		}
		m_Words[countWords - 1] = uint_t::normalizeHighestWord(carry + m_Words[countWords - 1]);
		return *this;
	}
	constexpr uint_t operator++(int) noexcept
	{
		const uint_t temp{ *this };
		++(*this);
		return temp;
	}
	constexpr uint_t operator-() const noexcept
	{
		return ++~(*this);
	}
	constexpr uint_t& operator*=(const uint_t& other) noexcept
	{
		using halfType = wordType;
		std::array<wordType, countWords> results{ make_array_n<countWords,wordType>(wordType(0)) };
		std::array<wordType, countWords> temp{ make_array_n<countWords,wordType>(wordType(0)) };
		for (size_t i = 0; i < countWords; i++)
		{
			wordType carry{ wordType(0) };
			wordType carry2{ 0 };
			for (size_t j = 0; j < (countWords - i); j++)
			{
				wordType low{ wordType(0) };
				wordType high{ wordType(0) };
				multiplyWords(m_Words[i], other.m_Words[j], low, high);
				temp[j] = wordType(0);
				carry = sumWords(temp[j], low, carry);
				carry2 = sumWords(carry, high, carry2);
			}
			carry = 0;
			for (size_t j = 0; j < (countWords - i); j++)
				carry = sumWords(results[i + j], temp[j], carry);
		}
		results[countWords - 1] = uint_t::normalizeHighestWord(results[countWords - 1]);
		m_Words = results;
		return *this;
	}
	static uint_t random() noexcept
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
	static uint_t sparse() noexcept
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
		return uint_t(uint_t::nullaryTransformWords<countWords, true>(lambda), false);
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
	constexpr bool operator>(const uint_t& other) const noexcept
	{
		for (size_t k = 0; k < countWords; k++)
		{
			const size_t i{ countWords - 1 - k };
			if (m_Words[i] > other.m_Words[i])
				return true;
			if (m_Words[i] < other.m_Words[i])
				return false;
		}
		return false;
	}
	constexpr bool operator<(const uint_t& other) const noexcept
	{
		for (size_t k = 0; k < countWords; k++)
		{
			const size_t i{ countWords - 1 - k };
			if (m_Words[i] < other.m_Words[i])
				return true;
			if (m_Words[i] > other.m_Words[i])
				return false;
		}
		return false;
	}
	constexpr bool operator>=(const uint_t& other) const noexcept
	{
		for (size_t k = 0; k < countWords; k++)
		{
			const size_t i{ countWords - 1 - k };
			if (m_Words[i] > other.m_Words[i])
				return true;
			if (m_Words[i] < other.m_Words[i])
				return false;
		}
		return true;
	}
	constexpr bool operator<=(const uint_t& other) const noexcept
	{
		for (size_t k = 0; k < countWords; k++)
		{
			const size_t i{ countWords - 1 - k };
			if (m_Words[i] < other.m_Words[i])
				return true;
			if (m_Words[i] > other.m_Words[i])
				return false;
		}
		return true;
	}
	constexpr uint_t operator<<(const size_t shift) const noexcept
	{
		assert(shift >= 0);
		const size_t words{ shift / countBitsPerWord };
		const size_t bits{ shift % countBitsPerWord };
		if (bits > 0)
		{
			const auto lambda = [this, words, bits](const size_t index)->wordType
			{
				wordType inWord1{ wordType(0) };
				wordType inWord2{ wordType(0) };
				const size_t word1 = { index - words };
				const size_t word2 = { index - words - 1 };
				if ((word1 >= 0) && (word1 < countWords))
				{
					inWord1 = this->word(word1);
					inWord1 <<= bits;
				}
				if ((word2 >= 0) && (word2 < countWords))
				{
					inWord2 = this->word(word2);
					inWord2 >>= (countBitsPerWord - bits);
				}
				const wordType res{ static_cast<wordType>(inWord1 | inWord2) };
				return res;
			};
			return uint_t(nullaryTransformWords<countWords, true>(lambda), false);
		}
		else
		{
			const auto lambda = [this, words, bits](const size_t index)->wordType
			{
				wordType inWord{ wordType(0) };
				const size_t word = { index - words };
				if ((word >= 0) && (word < countWords))
					inWord = this->word(word);
				return inWord;
			};
			return uint_t(nullaryTransformWords<countWords, true>(lambda), false);
		}
	}
	constexpr uint_t operator>>(const size_t shift) const noexcept
	{
		assert(shift >= 0);
		const size_t words{ shift / countBitsPerWord };
		const size_t bits{ shift % countBitsPerWord };
		if (bits > 0)
		{
			const auto lambda = [this, words, bits](const size_t index)->wordType
			{
				wordType inWord1{ wordType(0) };
				wordType inWord2{ wordType(0) };
				const size_t word1 = { index + words };
				const size_t word2 = { index + words + 1 };
				if ((word1 >= 0) && (word1 < countWords))
				{
					inWord1 = this->word(word1);
					inWord1 >>= bits;
				}
				if ((word2 >= 0) && (word2 < countWords))
				{
					inWord2 = this->word(word2);
					inWord2 <<= (countBitsPerWord - bits);
				}
				const wordType res{ static_cast<wordType>(inWord1 | inWord2) };
				return res;
			};
			return uint_t(nullaryTransformWords<countWords, true>(lambda), false);
		}
		else
		{
			const auto lambda = [this, words, bits](const size_t index)->wordType
			{
				wordType inWord{ wordType(0) };
				const size_t word = { index + words };
				if ((word >= 0) && (word < countWords))
					inWord = this->word(word);
				return inWord;
			};
			return uint_t(nullaryTransformWords<countWords, true>(lambda), false);
		}
	}
	static const inline std::string populationCount_Intrinsic{ popcnt::implementationName<countWords,wordType>() };
	static const inline std::string bitscanForward_Intrinsic{ bsf::implementationName<countWords,wordType>() };
	static const inline std::string bitscanReverse_Intrinsic{ bsr::implementationName<countWords,wordType>() };
	template<size_t COUNT_BITS2, bool IS_COMPACT2>
	constexpr uint_t(const uint_t<COUNT_BITS2, IS_COMPACT2>& other) noexcept :
		m_Words{ uint_t::nullaryTransformWords<countWords,false>([this,&other](const size_t currentWord)->wordType
				{
					if constexpr (COUNT_BITS2 == 0)
						return wordType(0);
					else if constexpr (COUNT_BITS2 == 1)
						return (currentWord == 0) ? static_cast<wordType>(other.word(0)) : wordType(0);
					else
					{
						using wordType2 = typename uint_t<COUNT_BITS2,IS_COMPACT2>::wordType;
						size_t currentWordBit{ 0 };
						size_t currentBit{ currentWord * this->countBitsPerWord };
						size_t otherWord{ currentBit / other.countBitsPerWord };
						size_t otherWordBit{ currentBit % other.countBitsPerWord };
						size_t otherBit{ otherWord * other.countBitsPerWord + otherWordBit };
						wordType result{ wordType(0) };
						while (true)
						{
							if ((otherBit >= other.countBits) || (currentWordBit >= countBitsPerWord) || (currentBit >= countBits))
								return result;
							const size_t otherRemaining{ std::min(other.countBitsPerWord - otherWordBit,other.countBits - otherBit) };
							const size_t currentRemaining{ std::min(countBitsPerWord - currentWordBit,countBits - currentBit) };
							const size_t slice{ std::min(otherRemaining,currentRemaining) };
							if (slice >= other.countBitsPerWord)
							{
								result |= static_cast<wordType>(static_cast<wordType>(other.word(otherWord) >> otherWordBit) << currentWordBit);
							}
							else
							{
								const wordType2 mask{ static_cast<wordType2>(static_cast<wordType2>(static_cast<wordType2>(wordType2(1) << slice) - wordType2(1)) << otherWordBit) };
								result |= static_cast<wordType>(static_cast<wordType>(static_cast<wordType2>(other.word(otherWord) & mask) >> otherWordBit) << currentWordBit);
							}
							otherBit += slice;
							otherWordBit += slice;
							if (otherWordBit >= other.countBitsPerWord)
							{
								otherWordBit = 0;
								otherWord++;
							}
							currentBit += slice;
							currentWordBit += slice;
						}
					}
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
	constexpr explicit operator bool() const noexcept
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
	bool bitscanForward(size_t& bit) const noexcept
	{
		return bsf::implementation<1, wordType>({ m_Word }, bit);
	}
	bool bitscanReverse(size_t& bit) const noexcept
	{
		return bsr::implementation<1, wordType>({ m_Word }, bit);
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
	constexpr uint_t operator~() const noexcept
	{
		return uint_t(normalizeWord(~m_Word), false);
	}
	constexpr uint_t& operator++() noexcept
	{
		m_Word = normalizeWord(m_Word + wordType(1));
		return *this;
	}
	constexpr uint_t operator++(int) noexcept
	{
		const uint_t temp{ *this };
		++(*this);
		return temp;
	}
	constexpr uint_t operator-() const noexcept
	{
		return uint_t(normalizeWord(static_cast<wordType>(-m_Word)), false);
	}
	constexpr uint_t& operator&=(const uint_t other) noexcept
	{
		m_Word = m_Word & other.m_Word;
		return *this;
	}
	constexpr uint_t& operator+=(const uint_t other) noexcept
	{
		m_Word = normalizeWord(m_Word + other.m_Word);
		return *this;
	}
	constexpr uint_t& operator*=(const uint_t other) noexcept
	{
		m_Word = normalizeWord(m_Word * other.m_Word);
		return *this;
	}
	constexpr uint_t& operator|=(const uint_t other) noexcept
	{
		m_Word = m_Word | other.m_Word;
		return *this;
	}
	constexpr uint_t& operator^=(const uint_t other) noexcept
	{
		m_Word = m_Word & other.m_Word;
		return *this;
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
	constexpr uint_t operator+(const uint_t other) const noexcept
	{
		return uint_t(normalizeWord(m_Word + other.m_Word), false);
	}
	constexpr uint_t operator-(const uint_t other) const noexcept
	{
		return uint_t(normalizeWord(static_cast<wordType>(m_Word - other.m_Word)), false);
	}
	constexpr uint_t operator*(const uint_t other) const noexcept
	{
		return uint_t(normalizeWord(m_Word * other.m_Word), false);
	}
	constexpr uint_t operator/(const uint_t other) const noexcept
	{
		assert(other.m_Word);
		return uint_t(m_Word / other.m_Word, false);
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
	constexpr bool operator==(const uint_t other) const noexcept
	{
		return m_Word == other.m_Word;
	}
	constexpr bool operator!=(const uint_t other) const noexcept
	{
		return m_Word != other.m_Word;
	}
	constexpr bool operator>(const uint_t& other) const noexcept
	{
		return m_Word > other.m_Word;
	}
	constexpr bool operator<(const uint_t& other) const noexcept
	{
		return m_Word < other.m_Word;
	}
	constexpr bool operator>=(const uint_t& other) const noexcept
	{
		return m_Word >= other.m_Word;
	}
	constexpr bool operator<=(const uint_t& other) const noexcept
	{
		return m_Word <= other.m_Word;
	}
	constexpr uint_t operator<<(const size_t shift) const noexcept
	{
		assert(shift >= 0);
		if (shift < countBitsPerWord)
			return uint_t(normalizeWord(m_Word << shift), false);
		else
			return uint_t(0, false);
	}
	constexpr uint_t operator>>(const size_t shift) const noexcept
	{
		assert(shift >= 0);
		if (shift < countBitsPerWord)
			return uint_t(m_Word >> shift, false);
		else
			return uint_t(0, false);
	}
	static const inline std::string populationCount_Intrinsic{ popcnt::implementationName<countWords,wordType>() };
	static const inline std::string bitscanForward_Intrinsic{ bsf::implementationName<countWords,wordType>() };
	static const inline std::string bitscanReverse_Intrinsic{ bsr::implementationName<countWords,wordType>() };
	template<size_t COUNT_BITS2, bool IS_COMPACT2>
	constexpr uint_t(const uint_t<COUNT_BITS2, IS_COMPACT2>& other) noexcept :
		m_Word{ ([this,&other]()->wordType {
					if constexpr (COUNT_BITS2 == 0)
						return wordType(0);
					else if constexpr (COUNT_BITS2 == 1)
						return static_cast<wordType>(other.word(0));
					else
					{
						using wordType2 = typename uint_t<COUNT_BITS2,IS_COMPACT2>::wordType;
						size_t currentWordBit{ 0 };
						size_t currentBit{ 0 };
						size_t otherWord{ currentBit / other.countBitsPerWord };
						size_t otherWordBit{ currentBit % other.countBitsPerWord };
						size_t otherBit{ otherWord * other.countBitsPerWord + otherWordBit };
						wordType result{ wordType(0) };
						while (true)
						{
							if ((otherBit >= other.countBits) || (currentWordBit >= countBitsPerWord) || (currentBit >= countBits))
								return result;
							const size_t otherRemaining{ std::min(other.countBitsPerWord - otherWordBit,other.countBits - otherBit) };
							const size_t currentRemaining{ std::min(countBitsPerWord - currentWordBit,countBits - currentBit) };
							const size_t slice{ std::min(otherRemaining,currentRemaining) };
							if (slice >= other.countBitsPerWord)
							{
								result |= static_cast<wordType>(static_cast<wordType>(other.word(otherWord) >> otherWordBit) << currentWordBit);
							}
							else
							{
								const wordType2 mask{ static_cast<wordType2>(static_cast<wordType2>(static_cast<wordType2>(wordType2(1) << slice) - wordType2(1)) << otherWordBit) };
								result |= static_cast<wordType>(static_cast<wordType>(static_cast<wordType2>(other.word(otherWord) & mask) >> otherWordBit) << currentWordBit);
							}
							otherBit += slice;
							otherWordBit += slice;
							if (otherWordBit >= other.countBitsPerWord)
							{
								otherWordBit = 0;
								otherWord++;
							}
							currentBit += slice;
							currentWordBit += slice;
						}
					}
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
	using wordType = std::uint8_t;
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
	constexpr explicit operator bool() const noexcept
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
	bool bitscanForward(size_t& bit) const noexcept
	{
		return bsf::implementation<1, wordType>({ m_Word }, bit);
	}
	bool bitscanReverse(size_t& bit) const noexcept
	{
		return bsr::implementation<1, wordType>({ m_Word }, bit);
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
	constexpr uint_t& operator++() noexcept
	{
		m_Word = !m_Word;
		return *this;
	}
	constexpr uint_t operator++(int) noexcept
	{
		const uint_t temp{ *this };
		++(*this);
		return temp;
	}
	constexpr uint_t operator-() const noexcept
	{
		return *this;
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
	constexpr uint_t operator-(const uint_t other) const noexcept
	{
		return uint_t(m_Word ^ other.m_Word, false);
	}
	constexpr uint_t operator*(const uint_t other) const noexcept
	{
		return uint_t(m_Word & other.m_Word, false);
	}
	constexpr uint_t operator/(const uint_t other) const noexcept
	{
		assert(other.m_Word);
		return uint_t(m_Word, false);
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
	constexpr bool operator>(const uint_t& other) const noexcept
	{
		return m_Word > other.m_Word;
	}
	constexpr bool operator<(const uint_t& other) const noexcept
	{
		return m_Word < other.m_Word;
	}
	constexpr bool operator>=(const uint_t& other) const noexcept
	{
		return m_Word >= other.m_Word;
	}
	constexpr bool operator<=(const uint_t& other) const noexcept
	{
		return m_Word <= other.m_Word;
	}
	constexpr uint_t operator<<(const size_t shift) const noexcept
	{
		assert(shift >= 0);
		return (shift == 0) ? *this : uint_t(false, false);
	}
	constexpr uint_t operator>>(const size_t shift) const noexcept
	{
		assert(shift >= 0);
		return (shift == 0) ? *this : uint_t(false, false);
	}
	static const inline std::string populationCount_Intrinsic{ popcnt::implementationName<countWords,wordType>() };
	static const inline std::string bitscanForward_Intrinsic{ bsf::implementationName<countWords,wordType>() };
	static const inline std::string bitscanReverse_Intrinsic{ bsr::implementationName<countWords,wordType>() };
	template<size_t COUNT_BITS2, bool IS_COMPACT2>
	constexpr uint_t(const uint_t<COUNT_BITS2, IS_COMPACT2>& other) noexcept :
		m_Word{ static_cast<wordType>((COUNT_BITS2 > 0) ? other.word(0) & 1 : 0) }
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
	constexpr explicit operator bool() const noexcept
	{
		return false;
	}
	size_t populationCount() const noexcept
	{
		return popcnt::implementation<0, wordType>({});
	}
	bool bitscanForward(size_t& bit) const noexcept
	{
		return bsf::implementation<0, wordType>({}, bit);
	}
	bool bitscanReverse(size_t& bit) const noexcept
	{
		return bsr::implementation<0, wordType>({}, bit);
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
	constexpr uint_t& operator++() noexcept
	{
		return *this;
	}
	constexpr uint_t operator++(int) noexcept
	{
		return *this;
	}
	constexpr uint_t operator-() const noexcept
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
	constexpr uint_t operator-(const uint_t other) const noexcept
	{
		return *this;
	}
	constexpr uint_t operator*(const uint_t other) const noexcept
	{
		return *this;
	}
	constexpr uint_t operator/(const uint_t other) const noexcept
	{
		assert(0);
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
	constexpr bool operator>(const uint_t& other) const noexcept
	{
		return false;
	}
	constexpr bool operator<(const uint_t& other) const noexcept
	{
		return false;
	}
	constexpr bool operator>=(const uint_t& other) const noexcept
	{
		return true;
	}
	constexpr bool operator<=(const uint_t& other) const noexcept
	{
		return true;
	}
	constexpr uint_t operator<<(const size_t shift) const noexcept
	{
		assert(shift >= 0);
		return *this;
	}
	constexpr uint_t operator>>(const size_t shift) const noexcept
	{
		assert(shift >= 0);
		return *this;
	}
	static const inline std::string populationCount_Intrinsic{ popcnt::implementationName<0,wordType>() };
	static const inline std::string bitscanForward_Intrinsic{ bsf::implementationName<0,wordType>() };
	static const inline std::string bitscanReverse_Intrinsic{ bsr::implementationName<0,wordType>() };
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
