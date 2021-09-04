namespace pygmalion
{
	template<size_t COUNT_BITS, bool IS_COMPACT, typename>
	class uint_t
	{
	};

	template<size_t COUNT_BITS, bool IS_COMPACT>
	class uint_t<COUNT_BITS, IS_COMPACT, typename std::enable_if<detail::isMultiWord<COUNT_BITS, IS_COMPACT>()>::type>
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
		static unsigned char nextRandom() noexcept
		{
			return std::rand() % std::numeric_limits<unsigned char>::max();
		}
		constexpr static wordType normalizeHighestWord(const wordType& word) noexcept
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
		constexpr static wordType normalizeWords(const wordType& word) noexcept
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
		constexpr static wordType sumWords(wordType& accumulator, const wordType& operand, const wordType& carry) noexcept
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
		constexpr static wordType subtractWords(wordType& accumulator, const wordType& operand, const wordType& carry) noexcept
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
		constexpr static const void multiplyWords(const wordType& A, const wordType& B, wordType& R_low, wordType& R_high) noexcept
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
		constexpr static bool enableBit(const size_t bit) noexcept
		{
			return bit < countBits;
		}
		constexpr static bool enableExtract(const size_t start, const size_t length) noexcept
		{
			return (start + length) <= countBits;
		}
	public:
		template<size_t SIZE, bool NORMALIZE, typename LAMBDA_TRANSFORM>
		constexpr static std::array<wordType, SIZE> nullaryTransformWords(const LAMBDA_TRANSFORM& create) noexcept
		{
			return uint_t::nullaryTransformWords<SIZE, NORMALIZE>(std::make_index_sequence<countWords>{}, create);
		}
		constexpr uint_t(const std::array<wordType, countWords>& words, bool) noexcept :
			m_Words{ words }
		{	}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr void clearBits() noexcept
		{
			if constexpr (LEN == 0)
				return;
			else if constexpr (LEN == 1)
				clear<START>();
			else
			{
				constexpr const size_t w{ START / countBitsPerWord };
				constexpr const size_t b{ START % countBitsPerWord };
				constexpr const size_t r{ LEN };
				constexpr const size_t rw{ countBitsPerWord - b };
				if constexpr (r <= rw)
				{
					if constexpr (r < countBitsPerWord)
					{
						const wordType mask{ static_cast<wordType>(~(((wordType(1) << r) - wordType(1)) << b)) };
						m_Words[w] &= mask;
					}
					else
						m_Words[w] = wordType(0);
				}
				else
				{
					if constexpr (rw < countBitsPerWord)
					{
						const wordType mask{ static_cast<wordType>(~(((wordType(1) << rw) - wordType(1)) << b)) };
						m_Words[w] &= mask;
					}
					else
						m_Words[w] = wordType(0);
					constexpr const size_t w2{ w + 1 };
					constexpr const size_t r2{ r - rw };
					constexpr const size_t l{ r2 / countBitsPerWord };
					constexpr const size_t w3{ w2 + l };
					for (size_t i = w2; i < w3; i++)
					{
						m_Words[i] = wordType(0);
					}
					constexpr const size_t r3{ r2 - l * countBitsPerWord };
					if constexpr (r3 > 0)
					{
						constexpr const wordType mask2{ static_cast<wordType>(~((wordType(1) << r3) - wordType(1))) };
						m_Words[w3] &= mask2;
					}
				}
			}
		}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr void setBits() noexcept
		{
			if constexpr (LEN == 0)
				return;
			else if constexpr (LEN == 1)
				set<START>();
			else
			{
				constexpr const size_t w{ START / countBitsPerWord };
				constexpr const size_t b{ START % countBitsPerWord };
				constexpr const size_t r{ LEN };
				constexpr const size_t rw{ countBitsPerWord - b };
				if constexpr (r <= rw)
				{
					if constexpr (r < countBitsPerWord)
					{
						const wordType mask{ static_cast<wordType>((((wordType(1) << r) - wordType(1)) << b)) };
						m_Words[w] |= mask;
					}
					else
						m_Words[w] = static_cast<wordType>(~wordType(0));
				}
				else
				{
					if constexpr (rw < countBitsPerWord)
					{
						const wordType mask{ static_cast<wordType>((((wordType(1) << rw) - wordType(1)) << b)) };
						m_Words[w] |= mask;
					}
					else
						m_Words[w] = static_cast<wordType>(~wordType(0));
					constexpr const size_t w2{ w + 1 };
					constexpr const size_t r2{ r - rw };
					constexpr const size_t l{ r2 / countBitsPerWord };
					constexpr const size_t w3{ w2 + l };
					for (size_t i = w2; i < w3; i++)
					{
						m_Words[i] = static_cast<wordType>(~wordType(0));
					}
					constexpr const size_t r3{ r2 - l * countBitsPerWord };
					if constexpr (r3 > 0)
					{
						constexpr const wordType mask2{ static_cast<wordType>(((wordType(1) << r3) - wordType(1))) };
						m_Words[w3] |= mask2;
					}
				}
			}
		}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr void storeBits(const uint_t<LEN, isCompact>& bits) noexcept
		{
			using L = uint_t<LEN, isCompact>;
			using WT = typename L::wordType;
			if constexpr (LEN == 0)
				return;
			else if constexpr (LEN == 1)
			{
				(*this)[START] = bits[0];
			}
			else
			{
				size_t w{ START / countBitsPerWord };
				size_t b{ START % countBitsPerWord };
				size_t w2{ 0 };
				size_t b2{ 0 };
				size_t r{ LEN };
				while (r > 0)
				{
					const size_t rw{ countBitsPerWord - b };
					const size_t rw2{ L::countBitsPerWord - b2 };
					const size_t rl{ std::min(rw,rw2) };
					const size_t ol{ std::min(r,rl) };
					const wordType mask{ (ol < countBitsPerWord) ? static_cast<wordType>(((wordType(1) << ol) - wordType(1)) << b) : static_cast<wordType>(~wordType(0)) };
					const WT mask2{ (ol < L::countBitsPerWord) ? static_cast<WT>(((WT(1) << ol) - WT(1)) << b2) : static_cast<WT>(~WT(0)) };
					m_Words[w] &= ~mask;
					m_Words[w] |= static_cast<wordType>(static_cast<wordType>((bits.word(w2) & mask2) >> b2) << b);
					b += ol;
					if (b >= countBitsPerWord)
					{
						b -= countBitsPerWord;
						w++;
					}
					b2 += ol;
					if (b2 >= L::countBitsPerWord)
					{
						b2 -= L::countBitsPerWord;
						w2++;
					}
					r -= ol;
				}
			}
		}
		class bitref
		{
		private:
			const size_t m_Bit;
			uint_t& m_This;
		public:
			constexpr bitref(uint_t& ui, const size_t bit) noexcept :
				m_This{ ui },
				m_Bit{ bit }
			{

			}
			constexpr bitref(const bitref&) noexcept = delete;
			constexpr bitref(bitref&&) noexcept = delete;
			~bitref() noexcept = default;
			constexpr operator bool() const noexcept
			{
				return m_This.test(m_Bit);
			}
			constexpr bitref& operator=(const bool bit) noexcept
			{
				if (bit)
					m_This.set(m_Bit);
				else
					m_This.clear(m_Bit);
				return *this;
			}
			constexpr bitref& operator=(const bitref& other) noexcept
			{
				(*this) = other.m_This.test(other.m_Bit);
				return *this;
			}
		};
		constexpr bool operator[](const size_t bit) const noexcept
		{
			return test(bit);
		}
		constexpr bitref operator[](const size_t bit) noexcept
		{
			return bitref(*this, bit);
		}
		constexpr static uint_t one() noexcept
		{
			return uint_t(1);
		}
		constexpr static uint_t zero() noexcept
		{
			return uint_t(0);
		}
		constexpr static uint_t universe() noexcept
		{
			return ~uint_t(0);
		}
		constexpr bool test(const size_t bit) const noexcept
		{
			assert(bit < countBits);
			const size_t word{ bit / countBitsPerWord };
			const size_t wbit{ bit % countBitsPerWord };
			const wordType mask{ static_cast<wordType>(wordType(1) << wbit) };
			return m_Words[word] & mask;
		}
		constexpr void set(const size_t bit) noexcept
		{
			assert(bit < countBits);
			const size_t word{ bit / countBitsPerWord };
			const size_t wbit{ bit % countBitsPerWord };
			const wordType mask{ static_cast<wordType>(wordType(1) << wbit) };
			m_Words[word] |= mask;
		}
		constexpr void toggle(const size_t bit) noexcept
		{
			assert(bit < countBits);
			const size_t word{ bit / countBitsPerWord };
			const size_t wbit{ bit % countBitsPerWord };
			const wordType mask{ static_cast<wordType>(wordType(1) << wbit) };
			m_Words[word] ^= mask;
		}
		constexpr void clear(const size_t bit) noexcept
		{
			assert(bit < countBits);
			const size_t word{ bit / countBitsPerWord };
			const size_t wbit{ bit % countBitsPerWord };
			const wordType mask{ static_cast<wordType>(~static_cast<wordType>(wordType(1) << wbit)) };
			m_Words[word] &= mask;
		}
		template<size_t BIT, typename = typename std::enable_if<uint_t::enableBit(BIT)>::type>
		constexpr bool test() const noexcept
		{
			constexpr const size_t word{ BIT / countBitsPerWord };
			constexpr const size_t wbit{ BIT % countBitsPerWord };
			constexpr const wordType mask{ static_cast<wordType>(wordType(1) << wbit) };
			return m_Words[word] & mask;
		}
		template<size_t BIT, typename = typename std::enable_if<uint_t::enableBit(BIT)>::type>
		constexpr void set() noexcept
		{
			constexpr const size_t word{ BIT / countBitsPerWord };
			constexpr const size_t wbit{ BIT % countBitsPerWord };
			constexpr const wordType mask{ static_cast<wordType>(wordType(1) << wbit) };
			m_Words[word] |= mask;
		}
		template<size_t BIT, typename = typename std::enable_if<uint_t::enableBit(BIT)>::type>
		constexpr void toggle() noexcept
		{
			constexpr const size_t word{ BIT / countBitsPerWord };
			constexpr const size_t wbit{ BIT % countBitsPerWord };
			constexpr const wordType mask{ static_cast<wordType>(wordType(1) << wbit) };
			m_Words[word] ^= mask;
		}
		template<size_t BIT, typename = typename std::enable_if<uint_t::enableBit(BIT)>::type>
		constexpr void clear() noexcept
		{
			constexpr const size_t word{ BIT / countBitsPerWord };
			constexpr const size_t wbit{ BIT % countBitsPerWord };
			constexpr const wordType mask{ static_cast<wordType>(~static_cast<wordType>(wordType(1) << wbit)) };
			m_Words[word] &= mask;
		}
		template<typename T, typename = typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value>::type>
		constexpr uint_t(const T value) noexcept :
			m_Words{ uint_t::encodeValue<countWords>(static_cast<typename std::make_unsigned<T>::type>(value)) }
		{}
		template<typename T, typename = typename std::enable_if<std::is_unsigned<T>::value && ((sizeof(T)* CHAR_BIT) >= countBits) && !std::is_same<bool, T>::value>::type>
		constexpr explicit operator T() const noexcept
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
			m_Words{ arrayhelper::make<countWords,wordType>(0) }
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
			return intrinsics::popcnt::implementation(m_Words);
		}
		bool bitscanForward(size_t& bit) const noexcept
		{
			return intrinsics::bsf::implementation(m_Words, bit);
		}
		bool bitscanReverse(size_t& bit) const noexcept
		{
			return intrinsics::bsr::implementation(m_Words, bit);
		}
		uint_t deposePattern(uint_t mask) const noexcept
		{
#if (defined(PYGMALION_INTRINSICS_MSC)||defined(PYGMALION_INTRINSICS_GNU))&&(defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))&&defined(PYGMALION_CPU_BMI2)
			if constexpr ((sizeof(wordType) <= 4) && cpu::supports(cpu::flags::X86) && cpu::supports(cpu::flags::BMI2) && (compiler::supports(compiler::flags::GNU) || compiler::supports(compiler::flags::MSC)))
			{
				const auto lambdaBits = [&mask](const size_t index)->size_t
				{
					return intrinsics::popcnt::implementation<1, wordType>({ mask.m_Words[index] });
				};
				const std::array<size_t, countWords> bitCounts{ arrayhelper::generate<countWords,size_t>(lambdaBits) };
				std::array<wordType, countWords> indices{ arrayhelper::make<countWords,wordType>(wordType(0)) };
				size_t w{ 0 };
				size_t b{ 0 };
				for (size_t i = 0; i < countWords; i++)
				{
					size_t bits{ bitCounts[i] };
					size_t shift{ 0 };
					while (bits)
					{
						size_t remaining{ countBitsPerWord - b };
						size_t len{ std::min(remaining,bits) };
						wordType M{ (len < countBitsPerWord) ? static_cast<wordType>(static_cast<wordType>(wordType(1) << len) - wordType(1)) : static_cast<wordType>(~wordType(0)) };
						indices[i] |= ((m_Words[w] >> b) & M) << shift;
						shift += len;
						bits -= len;
						b += len;
						if (b >= countBitsPerWord)
						{
							b -= countBitsPerWord;
							w++;
						}
					}
				}
				const auto lambdaPDEP = [&indices, &mask](const size_t index)->wordType
				{
					return static_cast<wordType>(_pdep_u32(indices[index], mask.m_Words[index]));
				};
				std::array<wordType, countWords> result{ arrayhelper::generate<countWords,wordType>(lambdaPDEP) };
				return uint_t(result, false);
			}
			else
#endif
#if (defined(PYGMALION_INTRINSICS_MSC)||defined(PYGMALION_INTRINSICS_GNU))&&defined(PYGMALION_CPU_X64)&&defined(PYGMALION_CPU_BMI2)
				if constexpr ((sizeof(wordType) <= 8) && cpu::supports(cpu::flags::X64) && cpu::supports(cpu::flags::BMI2) && (compiler::supports(compiler::flags::GNU) || compiler::supports(compiler::flags::MSC)))
				{
					const auto lambdaBits = [&mask](const size_t index)->size_t
					{
						return intrinsics::popcnt::implementation<1, wordType>({ mask.m_Words[index] });
					};
					const std::array<size_t, countWords> bitCounts{ arrayhelper::generate<countWords,size_t>(lambdaBits) };
					std::array<wordType, countWords> indices{ arrayhelper::make<countWords,wordType>(wordType(0)) };
					size_t w{ 0 };
					size_t b{ 0 };
					for (size_t i = 0; i < countWords; i++)
					{
						size_t bits{ bitCounts[i] };
						size_t shift{ 0 };
						while (bits)
						{
							size_t remaining{ countBitsPerWord - b };
							size_t len{ std::min(remaining,bits) };
							wordType M{ (len < countBitsPerWord) ? static_cast<wordType>(static_cast<wordType>(wordType(1) << len) - wordType(1)) : static_cast<wordType>(~wordType(0)) };
							indices[i] |= ((m_Words[w] >> b) & M) << shift;
							shift += len;
							bits -= len;
							b += len;
							if (b >= countBitsPerWord)
							{
								b -= countBitsPerWord;
								w++;
							}
						}
					}
					const auto lambdaPDEP = [&indices, &mask](const size_t index)->wordType
					{
						return static_cast<wordType>(_pdep_u64(indices[index], mask.m_Words[index]));
					};
					std::array<wordType, countWords> result{ arrayhelper::generate<countWords,wordType>(lambdaPDEP) };
					return uint_t(result, false);
				}
				else
#endif
#if (defined(PYGMALION_INTRINSICS_MSC)||defined(PYGMALION_INTRINSICS_GNU))&&defined(PYGMALION_CPU_X86)&&defined(PYGMALION_CPU_BMI2)
					if constexpr ((sizeof(wordType) <= 8) && cpu::supports(cpu::flags::X86) && cpu::supports(cpu::flags::BMI2) && (compiler::supports(compiler::flags::GNU) || compiler::supports(compiler::flags::MSC)))
					{
						const auto lambdaBits = [&mask](const size_t index)->size_t
						{
							return intrinsics::popcnt::implementation<1, wordType>({ mask.m_Words[index] });
						};
						const std::array<size_t, countWords> bitCounts{ arrayhelper::generate<countWords,size_t>(lambdaBits) };
						std::array<wordType, countWords> indices{ arrayhelper::make<countWords,wordType>(wordType(0)) };
						size_t w{ 0 };
						size_t b{ 0 };
						for (size_t i = 0; i < countWords; i++)
						{
							size_t bits{ bitCounts[i] };
							size_t shift{ 0 };
							while (bits)
							{
								size_t remaining{ countBitsPerWord - b };
								size_t len{ std::min(remaining,bits) };
								wordType M{ (len < countBitsPerWord) ? static_cast<wordType>(static_cast<wordType>(wordType(1) << len) - wordType(1)) : static_cast<wordType>(~wordType(0)) };
								indices[i] |= ((m_Words[w] >> b) & M) << shift;
								shift += len;
								bits -= len;
								b += len;
								if (b >= countBitsPerWord)
								{
									b -= countBitsPerWord;
									w++;
								}
							}
						}
						const auto lambdaPDEP = [&indices, &mask](const size_t index)->wordType
						{
							const std::uint32_t highMask{ static_cast<std::uint32_t>((mask.m_Words[index] & std::uint64_t(0xffffffff00000000)) >> 32) };
							const std::uint32_t lowMask{ static_cast<std::uint32_t>((mask.m_Words[index] & std::uint64_t(0x00000000ffffffff)) >> 0) };
							const size_t lowBits{ intrinsics::popcnt::implementation<1,std::uint32_t>({lowMask}) };
							const std::uint32_t highIndex{ static_cast<std::uint32_t>(indices[index] >> lowBits) };
							const std::uint32_t lowIndex{ static_cast<std::uint32_t>(indices[index] & ((std::uint64_t(1) << (lowBits + 1)) - 1)) };
							const std::uint32_t highVal{ _pdep_u32(highIndex, highMask) };
							const std::uint32_t lowVal{ _pdep_u32(lowIndex, lowMask) };
							const std::uint64_t value{ (static_cast<std::uint64_t>(highVal) << 32) | static_cast<std::uint64_t>(lowVal) };
							return static_cast<wordType>(value);
						};
						std::array<wordType, countWords> result{ arrayhelper::generate<countWords,wordType>(lambdaPDEP) };
						return uint_t(result, false);
					}
					else
#endif
					{
						uint_t res{ zero() };
						for (uint_t bb = one(); mask; bb += bb)
						{
							if ((*this) & bb)
								res |= mask & -mask;
							mask &= mask - one();
						}
						return res;
					}
		}
		uint_t extractPattern(uint_t mask) const noexcept
		{
#if (defined(PYGMALION_INTRINSICS_MSC)||defined(PYGMALION_INTRINSICS_GNU))&&(defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))&&defined(PYGMALION_CPU_BMI2)
			if constexpr ((sizeof(wordType) <= 4) && cpu::supports(cpu::flags::X86) && cpu::supports(cpu::flags::BMI2) && (compiler::supports(compiler::flags::GNU) || compiler::supports(compiler::flags::MSC)))
			{
				const auto lambdaPEXT = [this, &mask](const size_t index)->wordType
				{
					return static_cast<wordType>(_pext_u32(this->m_Words[index], mask.m_Words[index]));
				};
				std::array<wordType, countWords> extractedWords{ arrayhelper::generate<countWords,wordType>(lambdaPEXT) };
				const auto lambdaBits = [&mask](const size_t index)->size_t
				{
					return intrinsics::popcnt::implementation<1, wordType>({ mask.m_Words[index] });
				};
				const std::array<size_t, countWords> bitCounts{ arrayhelper::generate<countWords,size_t>(lambdaBits) };
				std::array<wordType, countWords> result{ arrayhelper::make<countWords,wordType>(wordType(0)) };
				size_t w{ 0 };
				size_t b{ 0 };
				for (size_t i = 0; i < countWords; i++)
				{
					size_t bits{ bitCounts[i] };
					while (bits)
					{
						const size_t space{ countBitsPerWord - b };
						const size_t len{ std::min(space,bits) };
						const wordType mask{ (len > 0) ? static_cast<wordType>(static_cast<wordType>(wordType(1) << len) - wordType(1)) : static_cast<wordType>(~wordType(0)) };
						result[w] |= static_cast<wordType>(static_cast<wordType>(extractedWords[i] & mask) << b);
						b += len;
						if (b >= countBitsPerWord)
						{
							b -= countBitsPerWord;
							w++;
						}
						bits -= len;
						extractedWords[i] >>= len;
					}
				}
				return uint_t(result, false);
			}
			else
#endif
#if (defined(PYGMALION_INTRINSICS_MSC)||defined(PYGMALION_INTRINSICS_GNU))&&defined(PYGMALION_CPU_X64)&&defined(PYGMALION_CPU_BMI2)
				if constexpr ((sizeof(wordType) <= 8) && cpu::supports(cpu::flags::X64) && cpu::supports(cpu::flags::BMI2) && (compiler::supports(compiler::flags::GNU) || compiler::supports(compiler::flags::MSC)))
				{
					const auto lambdaPEXT = [this, &mask](const size_t index)->wordType
					{
						return static_cast<wordType>(_pext_u64(this->m_Words[index], mask.m_Words[index]));
					};
					std::array<wordType, countWords> extractedWords{ arrayhelper::generate<countWords,wordType>(lambdaPEXT) };
					const auto lambdaBits = [&mask](const size_t index)->size_t
					{
						return intrinsics::popcnt::implementation<1, wordType>({ mask.m_Words[index] });
					};
					const std::array<size_t, countWords> bitCounts{ arrayhelper::generate<countWords,size_t>(lambdaBits) };
					std::array<wordType, countWords> result{ arrayhelper::make<countWords,wordType>(wordType(0)) };
					size_t w{ 0 };
					size_t b{ 0 };
					for (size_t i = 0; i < countWords; i++)
					{
						size_t bits{ bitCounts[i] };
						while (bits)
						{
							const size_t space{ countBitsPerWord - b };
							const size_t len{ std::min(space,bits) };
							const wordType mask{ (len > 0) ? static_cast<wordType>(static_cast<wordType>(wordType(1) << len) - wordType(1)) : static_cast<wordType>(~wordType(0)) };
							result[w] |= static_cast<wordType>(static_cast<wordType>(extractedWords[i] & mask) << b);
							b += len;
							if (b >= countBitsPerWord)
							{
								b -= countBitsPerWord;
								w++;
							}
							bits -= len;
							extractedWords[i] >>= len;
						}
					}
					return uint_t(result, false);
				}
				else
#endif
#if (defined(PYGMALION_INTRINSICS_MSC)||defined(PYGMALION_INTRINSICS_GNU))&&defined(PYGMALION_CPU_X86)&&defined(PYGMALION_CPU_BMI2)
					if constexpr ((sizeof(wordType) <= 8) && cpu::supports(cpu::flags::X86) && cpu::supports(cpu::flags::BMI2) && (compiler::supports(compiler::flags::GNU) || compiler::supports(compiler::flags::MSC)))
					{
						const auto lambdaPEXT = [this, &mask](const size_t index)->wordType
						{
							const std::uint32_t highMask{ static_cast<std::uint32_t>((mask.m_Words[index] & std::uint64_t(0xffffffff00000000)) >> 32) };
							const std::uint32_t lowMask{ static_cast<std::uint32_t>((mask.m_Words[index] & std::uint64_t(0x00000000ffffffff)) >> 0) };
							const std::uint32_t highVal{ static_cast<std::uint32_t>((this->m_Words[index] & std::uint64_t(0xffffffff00000000)) >> 32) };
							const std::uint32_t lowVal{ static_cast<std::uint32_t>((this->m_Words[index] & std::uint64_t(0x00000000ffffffff)) >> 0) };
							const size_t lowBits{ intrinsics::popcnt::implementation<1,std::uint32_t>({lowMask}) };
							const std::uint32_t highIndex{ _pext_u32(highVal, highMask) };
							const std::uint32_t lowIndex{ _pext_u32(lowVal, lowMask) };
							const std::uint64_t idx{ (static_cast<std::uint64_t>(highIndex) << lowBits) | static_cast<std::uint64_t>(lowIndex) };
							return idx;
						};
						std::array<wordType, countWords> extractedWords{ arrayhelper::generate<countWords,wordType>(lambdaPEXT) };
						const auto lambdaBits = [&mask](const size_t index)->size_t
						{
							return intrinsics::popcnt::implementation<1, wordType>({ mask.m_Words[index] });
						};
						const std::array<size_t, countWords> bitCounts{ arrayhelper::generate<countWords,size_t>(lambdaBits) };
						std::array<wordType, countWords> result{ arrayhelper::make<countWords,wordType>(wordType(0)) };
						size_t w{ 0 };
						size_t b{ 0 };
						for (size_t i = 0; i < countWords; i++)
						{
							size_t bits{ bitCounts[i] };
							while (bits)
							{
								const size_t space{ countBitsPerWord - b };
								const size_t len{ std::min(space,bits) };
								const wordType mask{ (len > 0) ? static_cast<wordType>(static_cast<wordType>(wordType(1) << len) - wordType(1)) : static_cast<wordType>(~wordType(0)) };
								result[w] |= static_cast<wordType>(static_cast<wordType>(extractedWords[i] & mask) << b);
								b += len;
								if (b >= countBitsPerWord)
								{
									b -= countBitsPerWord;
									w++;
								}
								bits -= len;
								extractedWords[i] >>= len;
							}
						}
						return uint_t(result, false);
					}
					else
#endif
					{
						uint_t res{ zero() };
						for (uint_t bb = one(); mask; bb += bb)
						{
							if ((*this) & mask & -mask)
								res |= bb;
							mask &= mask - one();
						}
						return res;
					}
		}
		operator std::string() const noexcept
		{
			return toString();
		}
		constexpr uint_t operator~() const noexcept
		{
			constexpr const auto lambda = [](const wordType& a, const size_t)->wordType { return ~a; };
			return uint_t(uint_t::unaryTransformWords<countWords, true>(m_Words, lambda), false);
		}
		constexpr uint_t& operator&=(const uint_t& other) noexcept
		{
			constexpr const auto lambda = [](wordType& a, const wordType b, const size_t)->void { a &= b; };
			uint_t::binaryTransformWordsInplace<countWords, false>(m_Words, other.m_Words, lambda);
			return *this;
		}
		constexpr uint_t& operator|=(const uint_t& other) noexcept
		{
			constexpr const auto lambda = [](wordType& a, const wordType b, const size_t)->void { a |= b; };
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
			constexpr const auto lambda = [](const wordType& a, const wordType& b, const size_t)->wordType { return a & b; };
			return uint_t(uint_t::binaryTransformWords<countWords, false>(m_Words, other.m_Words, lambda), false);
		}
		constexpr uint_t operator|(const uint_t& other) const noexcept
		{
			constexpr const auto lambda = [](const wordType& a, const wordType& b, const size_t)->wordType { return a | b; };
			return uint_t(uint_t::binaryTransformWords<countWords, false>(m_Words, other.m_Words, lambda), false);
		}
		constexpr uint_t operator^(const uint_t& other) const noexcept
		{
			constexpr const auto lambda = [](const wordType& a, const wordType& b, const size_t)->wordType { return a ^ b; };
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
			std::array<wordType, countWords> results{ arrayhelper::make<countWords,wordType>(wordType(0)) };
			std::array<wordType, countWords> temp{ arrayhelper::make<countWords,wordType>(wordType(0)) };
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
			uint_t<countBits + 1, isCompact> current{ uint_t<countBits + 1,isCompact>::one() };
			uint_t<countBits + 1, isCompact> answer{ uint_t<countBits + 1,isCompact>::zero() };

			if (denom > dividend)
				return zero();

			if (denom == dividend)
				return one();

			while (denom <= dividend)
			{
				denom <<= 1;
				current <<= 1;
			}

			denom >>= 1;
			current >>= 1;

			while (current)
			{
				if (dividend >= denom)
				{
					dividend = dividend - denom;
					answer |= current;
				}
				denom >>= 1;
				current >>= 1;
			}
			return static_cast<uint_t>(answer);
		}
		constexpr uint_t operator%(const uint_t& other) const noexcept
		{
			assert(other);
			const uint_t q{ (*this) / other };
			return (*this) - (q * other);
		}
		constexpr uint_t& operator+=(const uint_t& other)  noexcept
		{
			wordType carry{ 0 };
			for (size_t i = 0; i < countWords - 1; i++)
				carry = sumWords(m_Words[i], other.m_Words[i], carry);
			m_Words[countWords - 1] = uint_t::normalizeHighestWord(carry + m_Words[countWords - 1] + other.m_Words[countWords - 1]);
			return *this;
		}
		constexpr uint_t& operator-=(const uint_t& other)  noexcept
		{
			wordType carry{ 0 };
			for (size_t i = 0; i < countWords - 1; i++)
				carry = subtractWords(m_Words[i], other.m_Words[i], carry);
			m_Words[countWords - 1] = uint_t::normalizeHighestWord(m_Words[countWords - 1] - (other.m_Words[countWords - 1] + carry));
			return *this;
		}
		constexpr uint_t& operator++() noexcept
		{
			wordType carry{ 1 };
			size_t i{ 0 };
			while (carry && (i < (countWords - 1)))
			{
				++(m_Words[i]);
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
		constexpr uint_t& operator--() noexcept
		{
			wordType carry{ 1 };
			size_t i{ 0 };
			while (carry && (i < (countWords - 1)))
			{
				carry = (m_Words[i] == 0);
				--(m_Words[i]);
				i++;
			}
			m_Words[countWords - 1] = uint_t::normalizeHighestWord(m_Words[countWords - 1] - carry);
			return *this;
		}
		constexpr uint_t operator--(int) noexcept
		{
			const uint_t temp{ *this };
			--(*this);
			return temp;
		}
		constexpr uint_t operator-() const noexcept
		{
			return ++~(*this);
		}
		constexpr uint_t& operator*=(const uint_t& other) noexcept
		{
			std::array<wordType, countWords> results{ arrayhelper::make<countWords,wordType>(wordType(0)) };
			std::array<wordType, countWords> temp{ arrayhelper::make<countWords,wordType>(wordType(0)) };
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
		constexpr uint_t& operator/=(const uint_t& other) noexcept
		{
			assert(other);
			(*this) = (*this) / other;
			return *this;
		}
		constexpr uint_t& operator%=(const uint_t& other) noexcept
		{
			assert(other);
			const uint_t q{ (*this) / other };
			(*this) -= q * other;
			return *this;
		}
		static uint_t random() noexcept
		{
			const auto lambda = [](const size_t index)->wordType
			{
				wordType w{ wordType(0) };
				for (size_t c = 0; c < sizeof(wordType); c++)
				{
					const wordType randomChar{ static_cast<wordType>(uint_t::nextRandom()) };
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
					const wordType randomChar{ static_cast<wordType>((uint_t::nextRandom()) & (uint_t::nextRandom()) & (uint_t::nextRandom())) };
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
		constexpr uint_t& operator<<=(const size_t shift) noexcept
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
				m_Words = nullaryTransformWords<countWords, true>(lambda);
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
				m_Words = nullaryTransformWords<countWords, true>(lambda);
			}
			return *this;
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
		constexpr uint_t& operator>>=(const size_t shift) noexcept
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
				m_Words = nullaryTransformWords<countWords, true>(lambda);
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
				m_Words = nullaryTransformWords<countWords, true>(lambda);
			}
			return *this;
		}
		constexpr static uint_t clearMask(const size_t bit) noexcept
		{
			const size_t w{ bit / countBitsPerWord };
			const size_t b{ bit % countBitsPerWord };
			const auto lambda = [w, b](const size_t index)->wordType
			{
				return static_cast<wordType>((index == w) ? (wordType(1) << b) : wordType(0));
			};
			return ~uint_t(arrayhelper::generate<countWords, wordType>(lambda), false);
		}
		constexpr static uint_t setMask(const size_t bit) noexcept
		{
			const size_t w{ bit / countBitsPerWord };
			const size_t b{ bit % countBitsPerWord };
			const auto lambda = [w, b](const size_t index)->wordType
			{
				return static_cast<wordType>((index == w) ? (wordType(1) << b) : wordType(0));
			};
			return uint_t(arrayhelper::generate<countWords, wordType>(lambda), false);
		}
		static const inline std::string populationCount_Intrinsic{ intrinsics::popcnt::implementationName<countWords,wordType>() };
		static const inline std::string bitscanForward_Intrinsic{ intrinsics::bsf::implementationName<countWords,wordType>() };
		static const inline std::string bitscanReverse_Intrinsic{ intrinsics::bsr::implementationName<countWords,wordType>() };
		std::string toString() const noexcept
		{
			std::stringstream sstr;
			if constexpr (isCompact)
				sstr << "(" << countBits << ")";
			else
				sstr << "{" << countBits << "}";
			sstr << "[";
			for (size_t index = 0; index < countWords; index++)
			{
				const size_t m{ countWords - 1 - index };
				if (index > 0)
					sstr << ":";
				for (size_t i = 0; i < countBitsPerWord; i++)
				{
					const size_t n{ countBitsPerWord - 1 - i };
					const size_t k{ (m * countBitsPerWord + n) < countBits };
					if (k < countBits)
					{
						if (m_Words[m] & static_cast<wordType>((wordType(1) << n)))
							sstr << "1";
						else
							sstr << "0";
					}
					else
					{
						if (m_Words[m] & static_cast<wordType>((wordType(1) << n)))
							sstr << "E";
						else
							sstr << "_";
					}
				}
			}
			sstr << "]";
			return sstr.str();
		}
		class iterator
		{
			friend class uint_t;
		public:
			using value_type = size_t;
		private:
			uint_t m_State;
			value_type m_Current;
			constexpr iterator() noexcept :
				m_State{ 0 },
				m_Current{ 0 }
			{
			}
			constexpr explicit iterator(const uint_t state) noexcept :
				m_State{ state },
				m_Current{ 0 }
			{
				m_State.bitscanForward(m_Current);
			}
		public:
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::input_iterator_tag;
			constexpr iterator(const iterator&) noexcept = default;
			~iterator() noexcept = default;
			constexpr iterator&& operator++(int) noexcept
			{
				iterator ret(m_State);
				++(*this);
				return std::move(ret);
			}
			constexpr iterator& operator++() noexcept
			{
				m_State.clear(m_Current);
				m_State.bitscanForward(m_Current);
				return *this;
			}
			constexpr value_type operator*() const noexcept
			{
				return m_Current;
			}
			constexpr bool operator==(const iterator& other) const noexcept
			{
				return m_State == other.m_State;
			}
			constexpr bool operator!=(const iterator& other) const noexcept
			{
				return m_State != other.m_State;
			}
		};
		constexpr auto begin() const noexcept
		{
			return iterator(*this);
		}
		constexpr auto end() const noexcept
		{
			constexpr iterator endValue;
			return endValue;
		}
		template<size_t COUNT_BITS2, bool IS_COMPACT2>
		constexpr uint_t(const uint_t<COUNT_BITS2, IS_COMPACT2>& other) noexcept :
			m_Words{ uint_t::nullaryTransformWords<countWords,false>([this,&other](const size_t currentWord)->wordType {
						if constexpr (COUNT_BITS2 == 0)
							return wordType(0);
						else if constexpr (COUNT_BITS2 == 1)
							return (currentWord == 0) ? static_cast<wordType>(other.word(0)) : wordType(0);
						else
						{
							using wordType2 = typename uint_t<COUNT_BITS2,IS_COMPACT2>::wordType;
							size_t currentWordBit{ 0 };
							size_t currentBit{ currentWord * this->countBitsPerWord };
							size_t otherWord{ (currentBit) / other.countBitsPerWord };
							size_t otherWordBit{ (currentBit) % other.countBitsPerWord };
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
		}}) }
		{}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr uint_t<LEN, isCompact> extractBits() const noexcept
		{
			using L = uint_t<LEN, isCompact>;
			using L = uint_t<LEN, isCompact>;
			if constexpr (LEN == 0)
				return L::zero();
			else if constexpr (LEN == 1)
				return L(static_cast<typename L::wordType>((*this)[START]), false);
			else if constexpr (L::countWords <= 1)
			{
				using WT = typename L::wordType;
				return L(([this]()->WT {
					if constexpr (LEN == 0)
						return WT(0);
					else if constexpr (LEN == 1)
						return WT(this->template test<START>());
					else
					{
						size_t currentWordBit{ 0 };
						size_t currentBit{ 0 };
						size_t otherWord{ (START + currentBit) / countBitsPerWord };
						size_t otherWordBit{ (START + currentBit) % countBitsPerWord };
						size_t otherBit{ otherWord * countBitsPerWord + otherWordBit };
						WT result{ WT(0) };
						while (true)
						{
							if ((otherBit >= countBits) || (currentWordBit >= uint_t<LEN, isCompact>::countBitsPerWord) || (currentBit >= LEN))
								return result;
							const size_t otherRemaining{ std::min(countBitsPerWord - otherWordBit,countBits - otherBit) };
							const size_t currentRemaining{ std::min(uint_t<LEN, isCompact>::countBitsPerWord - currentWordBit,LEN - currentBit) };
							const size_t slice{ std::min(otherRemaining,currentRemaining) };
							if (slice >= countBitsPerWord)
							{
								result |= static_cast<WT>(static_cast<WT>(this->word(otherWord) >> otherWordBit) << currentWordBit);
							}
							else
							{
								const wordType mask{ static_cast<wordType>(static_cast<wordType>(static_cast<wordType>(wordType(1) << slice) - wordType(1)) << otherWordBit) };
								result |= static_cast<WT>(static_cast<WT>(static_cast<wordType>(this->word(otherWord) & mask) >> otherWordBit) << currentWordBit);
							}
							otherBit += slice;
							otherWordBit += slice;
							if (otherWordBit >= countBitsPerWord)
							{
								otherWordBit = 0;
								otherWord++;
							}
							currentBit += slice;
							currentWordBit += slice;
						}
					}
					})(), false);
			}
			else
			{
				using WT = typename L::wordType;
				return L(L::template nullaryTransformWords<L::countWords, false>([this](const size_t currentWord)->WT
					{
						if constexpr (LEN == 0)
							return WT(0);
						else if constexpr (LEN == 1)
							return WT(this->template test<START>());
						else
						{
							size_t currentWordBit{ 0 };
							size_t currentBit{ currentWord * uint_t<LEN, isCompact>::countBitsPerWord };
							size_t otherWord{ (START + currentBit) / countBitsPerWord };
							size_t otherWordBit{ (START + currentBit) % countBitsPerWord };
							size_t otherBit{ otherWord * countBitsPerWord + otherWordBit };
							WT result{ WT(0) };
							while (true)
							{
								if ((otherBit >= countBits) || (currentWordBit >= uint_t<LEN, isCompact>::countBitsPerWord) || (currentBit >= LEN))
									return result;
								const size_t otherRemaining{ std::min(countBitsPerWord - otherWordBit,countBits - otherBit) };
								const size_t currentRemaining{ std::min(uint_t<LEN, isCompact>::countBitsPerWord - currentWordBit,LEN - currentBit) };
								const size_t slice{ std::min(otherRemaining,currentRemaining) };
								if (slice >= countBitsPerWord)
								{
									result |= static_cast<WT>(static_cast<WT>(this->word(otherWord) >> otherWordBit) << currentWordBit);
								}
								else
								{
									const wordType mask{ static_cast<wordType>(static_cast<wordType>(static_cast<wordType>(wordType(1) << slice) - wordType(1)) << otherWordBit) };
									result |= static_cast<WT>(static_cast<WT>(static_cast<wordType>(this->word(otherWord) & mask) >> otherWordBit) << currentWordBit);
								}
								otherBit += slice;
								otherWordBit += slice;
								if (otherWordBit >= countBitsPerWord)
								{
									otherWordBit = 0;
									otherWord++;
								}
								currentBit += slice;
								currentWordBit += slice;
							}
						}
					}
				), false);
			}
		}
		constexpr uint_t twosComplement() const noexcept
		{
			return (~(*this))++;
		}
	};

	template<size_t COUNT_BITS, bool IS_COMPACT>
	class uint_t<COUNT_BITS, IS_COMPACT, typename std::enable_if <detail::isSingleWord<COUNT_BITS, IS_COMPACT>()>::type>
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
		constexpr static wordType normalizeWord(const wordType& word) noexcept
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
		constexpr static bool enableBit(const size_t bit) noexcept
		{
			return bit < countBits;
		}
		static unsigned char nextRandom() noexcept
		{
			return std::rand() % std::numeric_limits<unsigned char>::max();
		}
		constexpr static bool enableExtract(const size_t start, const size_t length) noexcept
		{
			return (start + length) <= countBits;
		}
	public:
		constexpr uint_t(const wordType& word, bool) noexcept :
			m_Word{ word }
		{	}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr void clearBits() noexcept
		{
			if constexpr (LEN == 0)
				return;
			else if constexpr (LEN == 1)
				clear<START>();
			else if constexpr (LEN < countBitsPerWord)
			{
				constexpr const wordType mask{ static_cast<wordType>(~(((wordType(1) << LEN) - wordType(1)) << START)) };
				m_Word &= mask;
			}
			else
				m_Word = wordType(0);
		}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr void setBits() noexcept
		{
			if constexpr (LEN == 0)
				return;
			else if constexpr (LEN == 1)
				set<START>();
			else if constexpr (LEN < countBitsPerWord)
			{
				constexpr const wordType mask{ static_cast<wordType>((((wordType(1) << LEN) - wordType(1)) << START)) };
				m_Word |= mask;
			}
			else
				m_Word = static_cast<wordType>(~wordType(0));
		}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr void storeBits(const uint_t<LEN, isCompact>& bits) noexcept
		{
			using L = uint_t<LEN, isCompact>;
			using WT = typename L::wordType;
			if constexpr (LEN == 0)
				return;
			else if constexpr (LEN == 1)
			{
				(*this)[START] = bits[0];
			}
			else
			{
				size_t b{ START % countBitsPerWord };
				size_t w2{ 0 };
				size_t b2{ 0 };
				size_t r{ LEN };
				while (r > 0)
				{
					const size_t rw{ countBitsPerWord - b };
					const size_t rw2{ L::countBitsPerWord - b2 };
					const size_t rl{ std::min(rw,rw2) };
					const size_t ol{ std::min(r,rl) };
					const wordType mask{ (ol < countBitsPerWord) ? static_cast<wordType>(((wordType(1) << ol) - wordType(1)) << b) : static_cast<wordType>(~wordType(0)) };
					const WT mask2{ (ol < L::countBitsPerWord) ? static_cast<WT>(((WT(1) << ol) - WT(1)) << b2) : static_cast<WT>(~WT(0)) };
					m_Word &= ~mask;
					m_Word |= static_cast<wordType>(static_cast<wordType>((bits.word(w2) & mask2) >> b2) << b);
					b += ol;
					b2 += ol;
					if (b2 >= L::countBitsPerWord)
					{
						b2 -= L::countBitsPerWord;
						w2++;
					}
					r -= ol;
				}
			}
		}
		class bitref
		{
		private:
			const size_t m_Bit;
			uint_t& m_This;
		public:
			constexpr bitref(uint_t& ui, const size_t bit) noexcept :
				m_This{ ui },
				m_Bit{ bit }
			{

			}
			constexpr bitref(const bitref&) noexcept = delete;
			constexpr bitref(bitref&&) noexcept = delete;
			~bitref() noexcept = default;
			constexpr operator bool() const noexcept
			{
				return m_This.test(m_Bit);
			}
			constexpr bitref& operator=(const bool bit) noexcept
			{
				if (bit)
					m_This.set(m_Bit);
				else
					m_This.clear(m_Bit);
				return *this;
			}
			constexpr bitref& operator=(const bitref& other) noexcept
			{
				(*this) = other.m_This.test(other.m_Bit);
				return *this;
			}
		};
		constexpr bool operator[](const size_t bit) const noexcept
		{
			return test(bit);
		}
		constexpr bitref operator[](const size_t bit) noexcept
		{
			return bitref(*this, bit);
		}
		constexpr static uint_t one() noexcept
		{
			return uint_t(1, false);
		}
		constexpr static uint_t zero() noexcept
		{
			return uint_t(0, true);
		}
		constexpr static uint_t universe() noexcept
		{
			return ~uint_t(0, true);
		}
		uint_t deposePattern(uint_t mask) const noexcept
		{
#if (defined(PYGMALION_INTRINSICS_MSC)||defined(PYGMALION_INTRINSICS_GNU))&&(defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))&&defined(PYGMALION_CPU_BMI2)
			if constexpr ((sizeof(wordType) <= 4) && cpu::supports(cpu::flags::X86) && cpu::supports(cpu::flags::BMI2) && (compiler::supports(compiler::flags::GNU) || compiler::supports(compiler::flags::MSC)))
			{
				return uint_t(static_cast<wordType>(_pdep_u32(m_Word, mask.m_Word)), false);
			}
			else
#endif
#if (defined(PYGMALION_INTRINSICS_MSC)||defined(PYGMALION_INTRINSICS_GNU))&&defined(PYGMALION_CPU_X64)&&defined(PYGMALION_CPU_BMI2)
				if constexpr ((sizeof(wordType) <= 8) && cpu::supports(cpu::flags::X64) && cpu::supports(cpu::flags::BMI2) && (compiler::supports(compiler::flags::GNU) || compiler::supports(compiler::flags::MSC)))
				{
					return uint_t(static_cast<wordType>(_pdep_u64(m_Word, mask.m_Word)), false);
				}
				else
#endif
#if (defined(PYGMALION_INTRINSICS_MSC)||defined(PYGMALION_INTRINSICS_GNU))&&defined(PYGMALION_CPU_X86)&&defined(PYGMALION_CPU_BMI2)
					if constexpr ((sizeof(wordType) <= 8) && cpu::supports(cpu::flags::X86) && cpu::supports(cpu::flags::BMI2) && (compiler::supports(compiler::flags::GNU) || compiler::supports(compiler::flags::MSC)))
					{
						const std::uint32_t highMask{ static_cast<std::uint32_t>((mask.m_Word & std::uint64_t(0xffffffff00000000)) >> 32) };
						const std::uint32_t lowMask{ static_cast<std::uint32_t>((mask.m_Word & std::uint64_t(0x00000000ffffffff)) >> 0) };
						const size_t lowBits{ intrinsics::popcnt::implementation<1,std::uint32_t>({lowMask}) };
						const std::uint32_t highIndex{ static_cast<std::uint32_t>(m_Word >> lowBits) };
						const std::uint32_t lowIndex{ static_cast<std::uint32_t>(m_Word & ((std::uint64_t(1) << (lowBits + 1)) - 1)) };
						const std::uint32_t highVal{ _pdep_u32(highIndex, highMask) };
						const std::uint32_t lowVal{ _pdep_u32(lowIndex, lowMask) };
						const std::uint64_t value{ (static_cast<std::uint64_t>(highVal) << 32) | static_cast<std::uint64_t>(lowVal) };
						return uint_t(value, false);
					}
					else
#endif
					{
						wordType res{ 0 };
						for (wordType bb = wordType(1); mask.m_Word; bb += bb)
						{
							if (m_Word & bb)
								res |= mask.m_Word & -mask.m_Word;
							mask.m_Word &= mask.m_Word - 1;
						}
						return uint_t(res, false);
					}
		}
		uint_t extractPattern(uint_t mask) const noexcept
		{
#if (defined(PYGMALION_INTRINSICS_MSC)||defined(PYGMALION_INTRINSICS_GNU))&&(defined(PYGMALION_CPU_X86)||defined(PYGMALION_CPU_X64))&&defined(PYGMALION_CPU_BMI2)
			if constexpr ((sizeof(wordType) <= 4) && cpu::supports(cpu::flags::X86) && cpu::supports(cpu::flags::BMI2) && (compiler::supports(compiler::flags::GNU) || compiler::supports(compiler::flags::MSC)))
			{
				return uint_t(_pext_u32(m_Word, mask.m_Word), false);
			}
			else
#endif
#if (defined(PYGMALION_INTRINSICS_MSC)||defined(PYGMALION_INTRINSICS_GNU))&&defined(PYGMALION_CPU_X64)&&defined(PYGMALION_CPU_BMI2)
				if constexpr ((sizeof(wordType) <= 8) && cpu::supports(cpu::flags::X64) && cpu::supports(cpu::flags::BMI2) && (compiler::supports(compiler::flags::GNU) || compiler::supports(compiler::flags::MSC)))
				{
					return uint_t(_pext_u64(m_Word, mask.m_Word), false);
				}
				else
#endif
#if (defined(PYGMALION_INTRINSICS_MSC)||defined(PYGMALION_INTRINSICS_GNU))&&defined(PYGMALION_CPU_X86)&&defined(PYGMALION_CPU_BMI2)
					if constexpr ((sizeof(wordType) <= 8) && cpu::supports(cpu::flags::X86) && cpu::supports(cpu::flags::BMI2) && (compiler::supports(compiler::flags::GNU) || compiler::supports(compiler::flags::MSC)))
					{
						const std::uint32_t highMask{ static_cast<std::uint32_t>((mask.m_Word & std::uint64_t(0xffffffff00000000)) >> 32) };
						const std::uint32_t lowMask{ static_cast<std::uint32_t>((mask.m_Word & std::uint64_t(0x00000000ffffffff)) >> 0) };
						const std::uint32_t highVal{ static_cast<std::uint32_t>((m_Word & std::uint64_t(0xffffffff00000000)) >> 32) };
						const std::uint32_t lowVal{ static_cast<std::uint32_t>((m_Word & std::uint64_t(0x00000000ffffffff)) >> 0) };
						const size_t lowBits{ intrinsics::popcnt::implementation<1,std::uint32_t>({lowMask}) };
						const std::uint32_t highIndex{ _pext_u32(highVal, highMask) };
						const std::uint32_t lowIndex{ _pext_u32(lowVal, lowMask) };
						const std::uint64_t index{ (static_cast<std::uint64_t>(highIndex) << lowBits) | static_cast<std::uint64_t>(lowIndex) };
						return uint_t(index, false);
					}
					else
#endif
					{
						wordType res{ wordType(0) };
						for (wordType bb = wordType(1); mask.m_Word; bb += bb)
						{
							if (m_Word & mask.m_Word & -mask.m_Word)
								res |= bb;
							mask.m_Word &= mask.m_Word - wordType(1);
						}
						return uint_t(res, false);
					}
		}
		constexpr bool test(const size_t bit) const noexcept
		{
			assert(bit < countBits);
			const wordType mask{ static_cast<wordType>(wordType(1) << bit) };
			return m_Word & mask;
		}
		constexpr void set(const size_t bit) noexcept
		{
			assert(bit < countBits);
			const wordType mask{ static_cast<wordType>(wordType(1) << bit) };
			m_Word |= mask;
		}
		constexpr void toggle(const size_t bit) noexcept
		{
			assert(bit < countBits);
			const wordType mask{ static_cast<wordType>(wordType(1) << bit) };
			m_Word ^= mask;
		}
		constexpr void clear(const size_t bit) noexcept
		{
			assert(bit < countBits);
			const wordType mask{ static_cast<wordType>(~static_cast<wordType>(wordType(1) << bit)) };
			m_Word &= mask;
		}
		template<size_t BIT, typename = typename std::enable_if<uint_t::enableBit(BIT)>::type>
		constexpr bool test() const noexcept
		{
			constexpr const wordType mask{ static_cast<wordType>(wordType(1) << BIT) };
			return m_Word & mask;
		}
		template<size_t BIT, typename = typename std::enable_if<uint_t::enableBit(BIT)>::type>
		constexpr void set() noexcept
		{
			constexpr const wordType mask{ static_cast<wordType>(wordType(1) << BIT) };
			m_Word |= mask;
		}
		template<size_t BIT, typename = typename std::enable_if<uint_t::enableBit(BIT)>::type>
		constexpr void toggle() noexcept
		{
			constexpr const wordType mask{ static_cast<wordType>(wordType(1) << BIT) };
			m_Word ^= mask;
		}
		template<size_t BIT, typename = typename std::enable_if<uint_t::enableBit(BIT)>::type>
		constexpr void clear() noexcept
		{
			constexpr const wordType mask{ static_cast<wordType>(~static_cast<wordType>(wordType(1) << BIT)) };
			m_Word &= mask;
		}
		template<typename T, typename = typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value>::type>
		constexpr uint_t(const T value) noexcept :
			m_Word{ static_cast<wordType>(static_cast<typename std::make_unsigned<T>::type>(value)) }
		{}
		template<typename T, typename = typename std::enable_if<std::is_unsigned<T>::value && ((sizeof(T)* CHAR_BIT) >= countBits) && !std::is_same<bool, T>::value>::type>
		constexpr explicit operator T() const noexcept
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
			return intrinsics::popcnt::implementation<1, wordType>({ m_Word });
		}
		bool bitscanForward(size_t& bit) const noexcept
		{
			return intrinsics::bsf::implementation<1, wordType>({ m_Word }, bit);
		}
		bool bitscanReverse(size_t& bit) const noexcept
		{
			return intrinsics::bsr::implementation<1, wordType>({ m_Word }, bit);
		}
		operator std::string() const noexcept
		{
			return toString();
		}
		constexpr uint_t operator~() const noexcept
		{
			return uint_t(normalizeWord(~m_Word), false);
		}
		constexpr uint_t& operator++() noexcept
		{
			m_Word = normalizeWord(++m_Word);
			return *this;
		}
		constexpr uint_t operator++(int) noexcept
		{
			const uint_t temp{ *this };
			++(*this);
			return temp;
		}
		constexpr uint_t& operator--() noexcept
		{
			m_Word = normalizeWord(--m_Word);
			return *this;
		}
		constexpr uint_t operator--(int) noexcept
		{
			const uint_t temp{ *this };
			--(*this);
			return temp;
		}
		constexpr uint_t operator-() const noexcept
		{
			return uint_t(normalizeWord(static_cast<wordType>(-m_Word)), false);
		}
		constexpr uint_t& operator&=(const uint_t other) noexcept
		{
			m_Word &= other.m_Word;
			return *this;
		}
		constexpr uint_t& operator+=(const uint_t other) noexcept
		{
			m_Word = normalizeWord(m_Word + other.m_Word);
			return *this;
		}
		constexpr uint_t& operator-=(const uint_t other) noexcept
		{
			m_Word = normalizeWord(m_Word - other.m_Word);
			return *this;
		}
		constexpr uint_t& operator*=(const uint_t other) noexcept
		{
			m_Word = normalizeWord(m_Word * other.m_Word);
			return *this;
		}
		constexpr uint_t& operator/=(const uint_t other) noexcept
		{
			assert(other.m_Word);
			m_Word = normalizeWord(m_Word / other.m_Word);
			return *this;
		}
		constexpr uint_t& operator%=(const uint_t other) noexcept
		{
			assert(other.m_Word);
			m_Word %= other.m_Word;
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
		constexpr uint_t operator%(const uint_t other) const noexcept
		{
			assert(other.m_Word);
			return uint_t(m_Word % other.m_Word, false);
		}
		static uint_t random() noexcept
		{
			wordType w{ wordType(0) };
			for (size_t c = 0; c < sizeof(wordType); c++)
			{
				const wordType randomChar{ static_cast<wordType>(uint_t::nextRandom()) };
				w |= randomChar << (CHAR_BIT * c);
			}
			return uint_t(normalizeWord(std::move(w)), false);
		}
		static uint_t sparse() noexcept
		{
			wordType w{ wordType(0) };
			for (size_t c = 0; c < sizeof(wordType); c++)
			{
				const wordType randomChar{ static_cast<wordType>((uint_t::nextRandom()) & (uint_t::nextRandom()) & (uint_t::nextRandom())) };
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
			return uint_t((shift < countBitsPerWord) ? normalizeWord(m_Word << shift) : 0, false);
		}
		constexpr uint_t& operator<<=(const size_t shift) noexcept
		{
			assert(shift >= 0);
			m_Word = (shift < countBitsPerWord) ? normalizeWord(m_Word << shift) : 0;
			return *this;
		}
		constexpr uint_t operator>>(const size_t shift) const noexcept
		{
			assert(shift >= 0);
			return uint_t((shift < countBitsPerWord) ? (m_Word >> shift) : 0, false);
		}
		constexpr uint_t& operator>>=(const size_t shift) noexcept
		{
			assert(shift >= 0);
			m_Word = (shift < countBitsPerWord) ? (m_Word >> shift) : 0;
			return *this;
		}
		static const inline std::string populationCount_Intrinsic{ intrinsics::popcnt::implementationName<countWords,wordType>() };
		static const inline std::string bitscanForward_Intrinsic{ intrinsics::bsf::implementationName<countWords,wordType>() };
		static const inline std::string bitscanReverse_Intrinsic{ intrinsics::bsr::implementationName<countWords,wordType>() };
		std::string toString() const noexcept
		{
			std::stringstream sstr;
			if constexpr (isCompact)
				sstr << "(" << countBits << ")";
			else
				sstr << "{" << countBits << "}";
			sstr << "[";
			for (size_t i = 0; i < countBitsPerWord; i++)
			{
				const size_t n{ countBitsPerWord - 1 - i };
				if (n < countBits)
				{
					if (m_Word & static_cast<wordType>((wordType(1) << n)))
						sstr << "1";
					else
						sstr << "0";
				}
				else
				{
					if (m_Word & static_cast<wordType>((wordType(1) << n)))
						sstr << "E";
					else
						sstr << "_";
				}
			}
			sstr << "]";
			return sstr.str();
		}
		class iterator
		{
			friend class uint_t;
		public:
			using value_type = size_t;
		private:
			uint_t m_State;
			value_type m_Current;
			constexpr iterator() noexcept :
				m_State{ 0 },
				m_Current{ 0 }
			{
			}
		public:
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::input_iterator_tag;
			constexpr explicit iterator(const uint_t state) noexcept :
				m_State{ state },
				m_Current{ 0 }
			{
				m_State.bitscanForward(m_Current);
			}
			constexpr iterator(const iterator&) noexcept = default;
			~iterator() noexcept = default;
			constexpr iterator operator++(int) noexcept
			{
				iterator ret(m_State);
				++(*this);
				return std::move(ret);
			}
			constexpr iterator& operator++() noexcept
			{
				m_State.clear(m_Current);
				m_State.bitscanForward(m_Current);
				return *this;
			}
			constexpr value_type operator*() const noexcept
			{
				return m_Current;
			}
			constexpr bool operator==(const iterator& other) const noexcept
			{
				return m_State == other.m_State;
			}
			constexpr bool operator!=(const iterator& other) const noexcept
			{
				return m_State != other.m_State;
			}
		};
		constexpr auto begin() const noexcept
		{
			return iterator(*this);
		}
		constexpr auto end() const noexcept
		{
			constexpr iterator endValue;
			return endValue;
		}
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
					size_t otherWord{ (currentBit) / other.countBitsPerWord };
					size_t otherWordBit{ (currentBit) % other.countBitsPerWord };
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
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr uint_t<LEN, isCompact> extractBits() const noexcept
		{
			using L = uint_t<LEN, isCompact>;
			if constexpr (LEN == 0)
				return L::zero();
			else if constexpr (LEN == 1)
				return L(static_cast<typename L::wordType>((*this)[START]), false);
			else if constexpr (L::countWords <= 1)
			{
				using WT = typename L::wordType;
				return L(([this]()->WT {
					if constexpr (LEN == 0)
						return WT(0);
					else if constexpr (LEN == 1)
						return WT(this->template test<START>());
					else
					{
						size_t currentWordBit{ 0 };
						size_t currentBit{ 0 };
						size_t otherWord{ (START + currentBit) / countBitsPerWord };
						size_t otherWordBit{ (START + currentBit) % countBitsPerWord };
						size_t otherBit{ otherWord * countBitsPerWord + otherWordBit };
						WT result{ WT(0) };
						while (true)
						{
							if ((otherBit >= countBits) || (currentWordBit >= uint_t<LEN, isCompact>::countBitsPerWord) || (currentBit >= LEN))
								return result;
							const size_t otherRemaining{ std::min(countBitsPerWord - otherWordBit,countBits - otherBit) };
							const size_t currentRemaining{ std::min(uint_t<LEN, isCompact>::countBitsPerWord - currentWordBit,LEN - currentBit) };
							const size_t slice{ std::min(otherRemaining,currentRemaining) };
							if (slice >= countBitsPerWord)
							{
								result |= static_cast<WT>(static_cast<WT>(this->word(otherWord) >> otherWordBit) << currentWordBit);
							}
							else
							{
								const wordType mask{ static_cast<wordType>(static_cast<wordType>(static_cast<wordType>(wordType(1) << slice) - wordType(1)) << otherWordBit) };
								result |= static_cast<WT>(static_cast<WT>(static_cast<wordType>(this->word(otherWord) & mask) >> otherWordBit) << currentWordBit);
							}
							otherBit += slice;
							otherWordBit += slice;
							if (otherWordBit >= countBitsPerWord)
							{
								otherWordBit = 0;
								otherWord++;
							}
							currentBit += slice;
							currentWordBit += slice;
						}
					}
					})(), false);
			}
			else
			{
				using WT = typename L::wordType;
				return L(L::template nullaryTransformWords<L::countWords, false>([this](const size_t currentWord)->WT
					{
						if constexpr (LEN == 0)
							return WT(0);
						else if constexpr (LEN == 1)
							return WT(this->template test<START>());
						else
						{
							size_t currentWordBit{ 0 };
							size_t currentBit{ currentWord * uint_t<LEN, isCompact>::countBitsPerWord };
							size_t otherWord{ (START + currentBit) / countBitsPerWord };
							size_t otherWordBit{ (START + currentBit) % countBitsPerWord };
							size_t otherBit{ otherWord * countBitsPerWord + otherWordBit };
							WT result{ WT(0) };
							while (true)
							{
								if ((otherBit >= countBits) || (currentWordBit >= uint_t<LEN, isCompact>::countBitsPerWord) || (currentBit >= LEN))
									return result;
								const size_t otherRemaining{ std::min(countBitsPerWord - otherWordBit,countBits - otherBit) };
								const size_t currentRemaining{ std::min(uint_t<LEN, isCompact>::countBitsPerWord - currentWordBit,LEN - currentBit) };
								const size_t slice{ std::min(otherRemaining,currentRemaining) };
								if (slice >= countBitsPerWord)
								{
									result |= static_cast<WT>(static_cast<WT>(this->word(otherWord) >> otherWordBit) << currentWordBit);
								}
								else
								{
									const wordType mask{ static_cast<wordType>(static_cast<wordType>(static_cast<wordType>(wordType(1) << slice) - wordType(1)) << otherWordBit) };
									result |= static_cast<WT>(static_cast<WT>(static_cast<wordType>(this->word(otherWord) & mask) >> otherWordBit) << currentWordBit);
								}
								otherBit += slice;
								otherWordBit += slice;
								if (otherWordBit >= countBitsPerWord)
								{
									otherWordBit = 0;
									otherWord++;
								}
								currentBit += slice;
								currentWordBit += slice;
							}
						}
					}
				), false);
			}
		}
		constexpr uint_t twosComplement() const noexcept
		{
			return uint_t(static_cast<wordType>(-m_Word), false);
		}
	};

	template<size_t COUNT_BITS, bool IS_COMPACT>
	class uint_t<COUNT_BITS, IS_COMPACT, typename std::enable_if <detail::isSingleBit<COUNT_BITS, IS_COMPACT>()>::type>
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
		static unsigned char nextRandom() noexcept
		{
			return std::rand() % std::numeric_limits<unsigned char>::max();
		}
		constexpr static bool enableExtract(const size_t start, const size_t length) noexcept
		{
			return (start + length) <= countBits;
		}
	public:
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr void storeBits(const uint_t<LEN, isCompact>& bits) noexcept
		{
			using L = uint_t<LEN, isCompact>;
			using WT = typename L::wordType;
			if constexpr (LEN == 0)
				return;
			else
				m_Word = static_cast<wordType>(bits[0]);
		}
		constexpr uint_t(const wordType& word, bool) noexcept :
			m_Word{ word }
		{	}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr void clearBits() noexcept
		{
			if constexpr (LEN == 0)
				return;
			else
				m_Word = wordType(0);
		}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr void setBits() noexcept
		{
			if constexpr (LEN == 0)
				return;
			else
				m_Word = wordType(1);
		}
		constexpr bool operator[](const size_t bit) const noexcept
		{
			return m_Word;
		}
		constexpr bool& operator[](const size_t bit) noexcept
		{
			return m_Word;
		}
		constexpr static uint_t one() noexcept
		{
			return uint_t(1, false);
		}
		constexpr static uint_t zero() noexcept
		{
			return uint_t(0, true);
		}
		constexpr static uint_t universe() noexcept
		{
			return uint_t(1, false);
		}
		uint_t extractPattern(const uint_t mask) const noexcept
		{
			return uint_t(mask.m_Word & m_Word, false);
		}
		uint_t deposePattern(const uint_t mask) const noexcept
		{
			return uint_t(mask.m_Word & m_Word, false);
		}
		constexpr bool test(const size_t bit) const noexcept
		{
			assert(bit == 0);
			return m_Word;
		}
		constexpr void set(const size_t bit) noexcept
		{
			assert(bit == 0);
			m_Word = true;
		}
		constexpr void toggle(const size_t bit) noexcept
		{
			assert(bit == 0);
			m_Word = !m_Word;
		}
		constexpr void clear(const size_t bit) noexcept
		{
			assert(bit == 0);
			m_Word = false;
		}
		template<size_t BIT, typename = typename std::enable_if<BIT == 0>::type>
		constexpr bool test() const noexcept
		{
			return m_Word;
		}
		template<size_t BIT, typename = typename std::enable_if<BIT == 0>::type>
		constexpr void set() noexcept
		{
			m_Word = true;
		}
		template<size_t BIT, typename = typename std::enable_if<BIT == 0>::type>
		constexpr void toggle() noexcept
		{
			m_Word = !m_Word;
		}
		template<size_t BIT, typename = typename std::enable_if<BIT == 0>::type>
		constexpr void clear() noexcept
		{
			m_Word = false;
		}
		template<typename T, typename = typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value>::type>
		constexpr uint_t(const T value) noexcept : m_Word{ static_cast<wordType>(value) } {}
		template<typename T, typename = typename std::enable_if<std::is_unsigned<T>::value && ((sizeof(T)* CHAR_BIT) >= countBits) && !std::is_same<bool, T>::value>::type>
		constexpr explicit operator T() const noexcept
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
			return intrinsics::popcnt::implementation<1, wordType>({ m_Word });
		}
		bool bitscanForward(size_t& bit) const noexcept
		{
			return intrinsics::bsf::implementation<1, wordType>({ m_Word }, bit);
		}
		bool bitscanReverse(size_t& bit) const noexcept
		{
			return intrinsics::bsr::implementation<1, wordType>({ m_Word }, bit);
		}
		operator std::string() const noexcept
		{
			return toString();
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
		constexpr uint_t& operator--() noexcept
		{
			m_Word = !m_Word;
			return *this;
		}
		constexpr uint_t operator--(int) noexcept
		{
			const uint_t temp{ *this };
			--(*this);
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
		constexpr uint_t& operator/=(const uint_t other) noexcept
		{
			assert(other.m_Word);
			return *this;
		}
		constexpr uint_t& operator%=(const uint_t other) noexcept
		{
			assert(other.m_Word);
			m_Word = wordType(0);
			return *this;
		}
		constexpr uint_t& operator+=(const uint_t other) noexcept
		{
			m_Word ^= other.m_Word;
			return *this;
		}
		constexpr uint_t& operator-=(const uint_t other) noexcept
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
			return *this;
		}
		constexpr uint_t operator%(const uint_t other) const noexcept
		{
			assert(other.m_Word);
			return uint_t(0, false);
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
			const wordType w{ static_cast<wordType>(uint_t::nextRandom() % 2) };
			return uint_t(std::move(w), false);
		}
		static uint_t sparse() noexcept
		{
			const wordType a{ static_cast<wordType>(uint_t::nextRandom() % 2) };
			const wordType b{ static_cast<wordType>(uint_t::nextRandom() % 2) };
			const wordType c{ static_cast<wordType>(uint_t::nextRandom() % 2) };
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
		constexpr uint_t& operator<<=(const size_t shift) noexcept
		{
			assert(shift >= 0);
			m_Word = (shift == 0) ? m_Word : 0;
			return *this;
		}
		constexpr uint_t operator>>(const size_t shift) const noexcept
		{
			assert(shift >= 0);
			return (shift == 0) ? *this : uint_t(false, false);
		}
		constexpr uint_t& operator>>=(const size_t shift) noexcept
		{
			assert(shift >= 0);
			m_Word = (shift == 0) ? m_Word : 0;
			return *this;
		}
		static const inline std::string populationCount_Intrinsic{ intrinsics::popcnt::implementationName<countWords,wordType>() };
		static const inline std::string bitscanForward_Intrinsic{ intrinsics::bsf::implementationName<countWords,wordType>() };
		static const inline std::string bitscanReverse_Intrinsic{ intrinsics::bsr::implementationName<countWords,wordType>() };
		class iterator
		{
			friend class uint_t;
		public:
			using value_type = size_t;
		private:
			uint_t m_State;
			value_type m_Current;
			constexpr iterator() noexcept :
				m_State{ 0 },
				m_Current{ 0 }
			{
			}
		public:
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::input_iterator_tag;
			constexpr explicit iterator(const uint_t state) noexcept :
				m_State{ state },
				m_Current{ 0 }
			{
				m_State.bitscanForward(m_Current);
			}
			constexpr iterator(const iterator&) noexcept = default;
			~iterator() noexcept = default;
			constexpr iterator operator++(int) noexcept
			{
				iterator ret(m_State);
				++(*this);
				return std::move(ret);
			}
			constexpr iterator& operator++() noexcept
			{
				m_State.clear(m_Current);
				m_State.bitscanForward(m_Current);
				return *this;
			}
			constexpr value_type operator*() const noexcept
			{
				return m_Current;
			}
			constexpr bool operator==(const iterator& other) const noexcept
			{
				return m_State == other.m_State;
			}
			constexpr bool operator!=(const iterator& other) const noexcept
			{
				return m_State != other.m_State;
			}
		};
		constexpr auto begin() const noexcept
		{
			return iterator(*this);
		}
		constexpr auto end() const noexcept
		{
			constexpr iterator endValue;
			return endValue;
		}
		template<size_t COUNT_BITS2, bool IS_COMPACT2>
		constexpr uint_t(const uint_t<COUNT_BITS2, IS_COMPACT2>& other) noexcept :
			m_Word{ static_cast<wordType>((COUNT_BITS2 > 0) ? other.template test<0>() : 0) }
		{}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr uint_t<LEN, isCompact> extractBits() const noexcept
		{
			return uint_t<LEN, isCompact>((LEN > 0) ? (test<START>() ? uint_t<LEN, isCompact>::one() : uint_t<LEN, isCompact>::zero()) : uint_t<LEN, isCompact>::zero());
		}
		std::string toString() const noexcept
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
		constexpr uint_t twosComplement() const noexcept
		{
			return *this;
		}
	};

	template<size_t COUNT_BITS, bool IS_COMPACT>
	class uint_t<COUNT_BITS, IS_COMPACT, typename std::enable_if<detail::isEmpty<COUNT_BITS, IS_COMPACT>()>::type>
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
		constexpr static bool enableExtract(const size_t start, const size_t length) noexcept
		{
			return (start + length) <= countBits;
		}
	public:
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr void clearBits() noexcept
		{
		}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr void setBits() noexcept
		{
		}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr uint_t<LEN, isCompact> extractBits() const noexcept
		{
			return uint_t<LEN, isCompact>::zero();
		}
		template<size_t START, size_t LEN, typename = typename std::enable_if<enableExtract(START, LEN)>::type>
		constexpr void storeBits(const uint_t<LEN, isCompact>& bits) noexcept
		{
		}
		class bitref
		{
		private:
		public:
			constexpr bitref() noexcept = default;
			constexpr bitref(const bitref&) noexcept = delete;
			constexpr bitref(bitref&&) noexcept = delete;
			~bitref() noexcept = default;
			constexpr operator bool() const noexcept
			{
				return false;
			}
			constexpr bitref& operator=(const bool bit) noexcept
			{
				return *this;
			}
			constexpr bitref& operator=(const bitref& other) noexcept
			{
				return *this;
			}
		};
		constexpr bool operator[](const size_t bit) const noexcept
		{
			return false;
		}
		constexpr bitref operator[](const size_t bit) noexcept
		{
			return bitref();
		}
		constexpr static uint_t one() noexcept
		{
			return uint_t();
		}
		constexpr static uint_t zero() noexcept
		{
			return uint_t();
		}
		constexpr static uint_t universe() noexcept
		{
			return uint_t();
		}
		uint_t extractPattern(const uint_t mask) const noexcept
		{
			return *this;
		}
		uint_t deposePattern(const uint_t mask) const noexcept
		{
			return *this;
		}
		constexpr bool test(const size_t bit) const noexcept
		{
			assert(false);
			return false;
		}
		constexpr void set(const size_t bit) noexcept
		{
			assert(false);
		}
		constexpr void toggle(const size_t bit) noexcept
		{
			assert(false);
		}
		constexpr void clear(const size_t bit) noexcept
		{
			assert(false);
		}
		std::string toString() const noexcept
		{
			std::stringstream sstr;
			if constexpr (isCompact)
				sstr << "(0)";
			else
				sstr << "{0}";
			sstr << "[]";
			return sstr.str();
		}
		template<typename T, typename = typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value>::type>
		constexpr uint_t(const T value) noexcept :uint_t()
		{

		}
		template<typename T, typename = typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<bool, T>::value>::type>
		constexpr explicit operator T() const noexcept
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
			return intrinsics::popcnt::implementation<0, wordType>({});
		}
		bool bitscanForward(size_t& bit) const noexcept
		{
			return intrinsics::bsf::implementation<0, wordType>({}, bit);
		}
		bool bitscanReverse(size_t& bit) const noexcept
		{
			return intrinsics::bsr::implementation<0, wordType>({}, bit);
		}
		operator std::string() const noexcept
		{
			return toString();
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
		constexpr uint_t& operator--() noexcept
		{
			return *this;
		}
		constexpr uint_t operator--(int) noexcept
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
		constexpr uint_t operator/=(const uint_t other) noexcept
		{
			assert(0);
			return *this;
		}
		constexpr uint_t operator%=(const uint_t other) noexcept
		{
			assert(0);
			return *this;
		}
		constexpr uint_t operator+=(const uint_t other) noexcept
		{
			return *this;
		}
		constexpr uint_t operator-=(const uint_t other) noexcept
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
		constexpr uint_t operator%(const uint_t other) const noexcept
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
		constexpr uint_t& operator<<=(const size_t shift) noexcept
		{
			assert(shift >= 0);
			return *this;
		}
		constexpr uint_t operator>>(const size_t shift) const noexcept
		{
			assert(shift >= 0);
			return *this;
		}
		constexpr uint_t& operator>>=(const size_t shift) noexcept
		{
			assert(shift >= 0);
			return *this;
		}
		static const inline std::string populationCount_Intrinsic{ intrinsics::popcnt::implementationName<0,wordType>() };
		static const inline std::string bitscanForward_Intrinsic{ intrinsics::bsf::implementationName<0,wordType>() };
		static const inline std::string bitscanReverse_Intrinsic{ intrinsics::bsr::implementationName<0,wordType>() };
		class iterator
		{
			friend class uint_t;
		public:
			using value_type = size_t;
		private:
			uint_t m_State;
			value_type m_Current;
			constexpr iterator() noexcept :
				m_State{ 0 },
				m_Current{ 0 }
			{
			}
		public:
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::input_iterator_tag;
			constexpr explicit iterator(const uint_t state) noexcept :
				m_State{ state },
				m_Current{ 0 }
			{
				m_State.bitscanForward(m_Current);
			}
			constexpr iterator(const iterator&) noexcept = default;
			~iterator() noexcept = default;
			constexpr iterator operator++(int) noexcept
			{
				iterator ret(m_State);
				++(*this);
				return std::move(ret);
			}
			constexpr iterator& operator++() noexcept
			{
				m_State.clear(m_Current);
				m_State.bitscanForward(m_Current);
				return *this;
			}
			constexpr value_type operator*() const noexcept
			{
				return m_Current;
			}
			constexpr bool operator==(const iterator& other) const noexcept
			{
				return m_State == other.m_State;
			}
			constexpr bool operator!=(const iterator& other) const noexcept
			{
				return m_State != other.m_State;
			}
		};
		constexpr auto begin() const noexcept
		{
			return iterator(*this);
		}
		constexpr auto end() const noexcept
		{
			constexpr iterator endValue;
			return endValue;
		}
		template<size_t COUNT_BITS2, bool IS_COMPACT2>
		constexpr uint_t(const uint_t<COUNT_BITS2, IS_COMPACT2>& other) noexcept
		{}
		constexpr uint_t twosComplement() const noexcept
		{
			return *this;
		}
	};

	template<size_t COUNT_BITS>
	using uint_least_t = uint_t<COUNT_BITS, true>;

	template<size_t COUNT_BITS>
	using uint_fast_t = uint_t<COUNT_BITS, false>;

	template<size_t COUNT_BITS, bool IS_COMPACT>
	std::ostream& operator<<(std::ostream& str, const uint_t<COUNT_BITS, IS_COMPACT>& value) noexcept
	{
		str << value.toString();
		return str;
	}
}