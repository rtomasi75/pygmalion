namespace pygmalion
{
	namespace detail
	{
		template<typename VALUE, typename SCORE>
		class sortTraits
		{
		public:
			constexpr static const bool inline isGeneric{ true };
		};

		template<>
		class sortTraits<std::uint8_t, std::int8_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint16_t, std::int8_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint32_t, std::int8_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint64_t, std::int8_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint8_t, std::int16_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint16_t, std::int16_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint32_t, std::int16_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint64_t, std::int16_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint8_t, std::int32_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint16_t, std::int32_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint32_t, std::int32_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint64_t, std::int32_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint8_t, std::int64_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint16_t, std::int64_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint32_t, std::int64_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint64_t, std::int64_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};


		template<typename VALUE, typename SCORE>
		class compare
		{
		public:
			template<size_t IDX1, size_t IDX2>
			constexpr static void scalar(VALUE* pValues, SCORE* pScores) noexcept
			{
				if (pScores[IDX1] < pScores[IDX2])
				{
					std::swap(pValues[IDX1], pValues[IDX2]);
					std::swap(pScores[IDX1], pScores[IDX2]);
				}
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			constexpr static void vector2(VALUE* pValues, SCORE* pScores) noexcept
			{
				scalar<IDX1a, IDX2a>(pValues, pScores);
				scalar<IDX1b, IDX2b>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			constexpr static void vector3(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				scalar<IDX1c, IDX2c>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			constexpr static void vector4(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				vector2<IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e>
			constexpr static void vector5(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				scalar<IDX1e, IDX2e>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			constexpr static void vector6(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector2<IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			constexpr static void vector7(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector3<IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			constexpr static void vector8(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector4<IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
			}
		};

		template<>
		class compare<std::uint16_t, std::int32_t>
		{
		public:
			using VALUE = std::uint16_t;
			using SCORE = std::int32_t;
		private:
			template<size_t IDX1, size_t IDX2>
			constexpr static void scalar_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				if (pScores[IDX1] < pScores[IDX2])
				{
					std::swap(pValues[IDX1], pValues[IDX2]);
					std::swap(pScores[IDX1], pScores[IDX2]);
				}
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			constexpr static void vector2_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				scalar<IDX1a, IDX2a>(pValues, pScores);
				scalar<IDX1b, IDX2b>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			constexpr static void vector3_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				scalar<IDX1c, IDX2c>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			constexpr static void vector4_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				vector2<IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e>
			constexpr static void vector5_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector3<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
				vector2<IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			constexpr static void vector6_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector3<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
				vector3<IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			constexpr static void vector7_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector3<IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			constexpr static void vector8_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector4<IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
			}
#if defined(PYGMALION_CPU_SSE2)
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			constexpr static void vector4_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				const __m128i score1{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX1a],0), pScores[IDX1b], 1), pScores[IDX1c], 2), pScores[IDX1d], 3) };
				const __m128i score2{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX2a],0), pScores[IDX2b], 1), pScores[IDX2c], 2), pScores[IDX2d], 3) };
				const __m128i value1{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX1a],0), pValues[IDX1b], 1), pValues[IDX1c], 6), pValues[IDX1d], 7) };
				const __m128i value2{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX2a],0), pValues[IDX2b], 1), pValues[IDX2c], 6), pValues[IDX2d], 7) };
				const __m128i comparision{ _mm_cmpgt_epi32(score2, score1) };
				const __m128i maskValue{ _mm_shufflehi_epi16(_mm_shufflelo_epi16(comparision, 0b00001000), 0b00001000) };
				const __m128i deltaScore{ _mm_and_si128(_mm_xor_si128(score1, score2), comparision) };
				const __m128i resultScore1{ _mm_xor_si128(score1, deltaScore) };
				const __m128i resultScore2{ _mm_xor_si128(score2, deltaScore) };
				const __m128i deltaValue{ _mm_and_si128(_mm_xor_si128(value1, value2), maskValue) };
				const __m128i resultValue1{ _mm_xor_si128(value1, deltaValue) };
				const __m128i resultValue2{ _mm_xor_si128(value2, deltaValue) };
				pScores[IDX1a] = _mm_extract_epi32(resultScore1, 0);
				pScores[IDX1b] = _mm_extract_epi32(resultScore1, 1);
				pScores[IDX1c] = _mm_extract_epi32(resultScore1, 2);
				pScores[IDX1d] = _mm_extract_epi32(resultScore1, 3);
				pScores[IDX2a] = _mm_extract_epi32(resultScore2, 0);
				pScores[IDX2b] = _mm_extract_epi32(resultScore2, 1);
				pScores[IDX2c] = _mm_extract_epi32(resultScore2, 2);
				pScores[IDX2d] = _mm_extract_epi32(resultScore2, 3);
				pValues[IDX1a] = _mm_extract_epi16(resultValue1, 0);
				pValues[IDX1b] = _mm_extract_epi16(resultValue1, 1);
				pValues[IDX1c] = _mm_extract_epi16(resultValue1, 6);
				pValues[IDX1d] = _mm_extract_epi16(resultValue1, 7);
				pValues[IDX2a] = _mm_extract_epi16(resultValue2, 0);
				pValues[IDX2b] = _mm_extract_epi16(resultValue2, 1);
				pValues[IDX2c] = _mm_extract_epi16(resultValue2, 6);
				pValues[IDX2d] = _mm_extract_epi16(resultValue2, 7);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			constexpr static void vector3_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				const __m128i score1{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX1a],0), pScores[IDX1b], 1), pScores[IDX1c], 2) };
				const __m128i score2{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX2a],0), pScores[IDX2b], 1), pScores[IDX2c], 2) };
				const __m128i value1{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX1a],0), pValues[IDX1b], 1), pValues[IDX1c], 6) };
				const __m128i value2{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX2a],0), pValues[IDX2b], 1), pValues[IDX2c], 6) };
				const __m128i comparision{ _mm_cmpgt_epi32(score2, score1) };
				const __m128i maskValue{ _mm_shufflehi_epi16(_mm_shufflelo_epi16(comparision, 0b00001000), 0b00001000) };
				const __m128i deltaScore{ _mm_and_si128(_mm_xor_si128(score1, score2), comparision) };
				const __m128i resultScore1{ _mm_xor_si128(score1, deltaScore) };
				const __m128i resultScore2{ _mm_xor_si128(score2, deltaScore) };
				const __m128i deltaValue{ _mm_and_si128(_mm_xor_si128(value1, value2), maskValue) };
				const __m128i resultValue1{ _mm_xor_si128(value1, deltaValue) };
				const __m128i resultValue2{ _mm_xor_si128(value2, deltaValue) };
				pScores[IDX1a] = _mm_extract_epi32(resultScore1, 0);
				pScores[IDX1b] = _mm_extract_epi32(resultScore1, 1);
				pScores[IDX1c] = _mm_extract_epi32(resultScore1, 2);
				pScores[IDX2a] = _mm_extract_epi32(resultScore2, 0);
				pScores[IDX2b] = _mm_extract_epi32(resultScore2, 1);
				pScores[IDX2c] = _mm_extract_epi32(resultScore2, 2);
				pValues[IDX1a] = _mm_extract_epi16(resultValue1, 0);
				pValues[IDX1b] = _mm_extract_epi16(resultValue1, 1);
				pValues[IDX1c] = _mm_extract_epi16(resultValue1, 6);
				pValues[IDX2a] = _mm_extract_epi16(resultValue2, 0);
				pValues[IDX2b] = _mm_extract_epi16(resultValue2, 1);
				pValues[IDX2c] = _mm_extract_epi16(resultValue2, 6);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			constexpr static void vector2_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				const __m128i score1{ _mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX1a],0), pScores[IDX1b], 1) };
				const __m128i score2{ _mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX2a],0), pScores[IDX2b], 1) };
				const __m128i value1{ _mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX1a],0), pValues[IDX1b], 1) };
				const __m128i value2{ _mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX2a],0), pValues[IDX2b], 1) };
				const __m128i comparision{ _mm_cmpgt_epi32(score2, score1) };
				const __m128i maskValue{ _mm_shufflelo_epi16(comparision, 0b00001000) };
				const __m128i deltaScore{ _mm_and_si128(_mm_xor_si128(score1, score2), comparision) };
				const __m128i resultScore1{ _mm_xor_si128(score1, deltaScore) };
				const __m128i resultScore2{ _mm_xor_si128(score2, deltaScore) };
				const __m128i deltaValue{ _mm_and_si128(_mm_xor_si128(value1, value2), maskValue) };
				const __m128i resultValue1{ _mm_xor_si128(value1, deltaValue) };
				const __m128i resultValue2{ _mm_xor_si128(value2, deltaValue) };
				pScores[IDX1a] = _mm_extract_epi32(resultScore1, 0);
				pScores[IDX1b] = _mm_extract_epi32(resultScore1, 1);
				pScores[IDX2a] = _mm_extract_epi32(resultScore2, 0);
				pScores[IDX2b] = _mm_extract_epi32(resultScore2, 1);
				pValues[IDX1a] = _mm_extract_epi16(resultValue1, 0);
				pValues[IDX1b] = _mm_extract_epi16(resultValue1, 1);
				pValues[IDX2a] = _mm_extract_epi16(resultValue2, 0);
				pValues[IDX2b] = _mm_extract_epi16(resultValue2, 1);
			}
#endif
#if defined PYGMALION_CPU_AVX2
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e>
			constexpr static void vector5_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				const __m128i score1low{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX1a],0), pScores[IDX1b], 1), pScores[IDX1c], 2), pScores[IDX1d], 3) };
				const __m128i score2low{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX2a],0), pScores[IDX2b], 1), pScores[IDX2c], 2), pScores[IDX2d], 3) };
				const __m128i score1high{ _mm_insert_epi32(_mm_undefined_si128(), pScores[IDX1e],0) };
				const __m128i score2high{ _mm_insert_epi32(_mm_undefined_si128(), pScores[IDX2e],0) };
				const __m256i score1{ _mm256_inserti128_si256(_mm256_castsi128_si256(score1low),score1high, 1) };
				const __m256i score2{ _mm256_inserti128_si256(_mm256_castsi128_si256(score2low),score2high, 1) };
				const __m128i value1low{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX1a],0), pValues[IDX1b], 1), pValues[IDX1c], 6), pValues[IDX1d], 7) };
				const __m128i value1high{ _mm_insert_epi16(_mm_undefined_si128(), pValues[IDX1e],0) };
				const __m256i value1{ _mm256_inserti128_si256(_mm256_castsi128_si256(value1low),value1high, 1) };
				const __m128i value2low{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX2a],0), pValues[IDX2b], 1), pValues[IDX2c], 6), pValues[IDX2d], 7) };
				const __m128i value2high{ _mm_insert_epi16(_mm_undefined_si128(), pValues[IDX2e],0) };
				const __m256i value2{ _mm256_inserti128_si256(_mm256_castsi128_si256(value2low),value2high, 1) };
				const __m256i comparision{ _mm256_cmpgt_epi32(score2, score1) };
				const __m256i maskValue{ _mm256_shufflehi_epi16(_mm256_shufflelo_epi16(comparision, 0b00001000), 0b00001000) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), maskValue) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1low{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1high{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2low{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2high{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1low{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1high{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2low{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2high{ _mm256_extracti128_si256(resultValue2, 1) };
				pScores[IDX1a] = _mm_extract_epi32(resultScore1low, 0);
				pScores[IDX1b] = _mm_extract_epi32(resultScore1low, 1);
				pScores[IDX1c] = _mm_extract_epi32(resultScore1low, 2);
				pScores[IDX1d] = _mm_extract_epi32(resultScore1low, 3);
				pScores[IDX1e] = _mm_extract_epi32(resultScore1high, 0);
				pScores[IDX2a] = _mm_extract_epi32(resultScore2low, 0);
				pScores[IDX2b] = _mm_extract_epi32(resultScore2low, 1);
				pScores[IDX2c] = _mm_extract_epi32(resultScore2low, 2);
				pScores[IDX2d] = _mm_extract_epi32(resultScore2low, 3);
				pScores[IDX2e] = _mm_extract_epi32(resultScore2high, 0);
				pValues[IDX1a] = _mm_extract_epi16(resultValue1low, 0);
				pValues[IDX1b] = _mm_extract_epi16(resultValue1low, 1);
				pValues[IDX1c] = _mm_extract_epi16(resultValue1low, 6);
				pValues[IDX1d] = _mm_extract_epi16(resultValue1low, 7);
				pValues[IDX1e] = _mm_extract_epi16(resultValue1high, 0);
				pValues[IDX2a] = _mm_extract_epi16(resultValue2low, 1);
				pValues[IDX2b] = _mm_extract_epi16(resultValue2low, 1);
				pValues[IDX2c] = _mm_extract_epi16(resultValue2low, 6);
				pValues[IDX2d] = _mm_extract_epi16(resultValue2low, 7);
				pValues[IDX2e] = _mm_extract_epi16(resultValue2high, 0);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			constexpr static void vector6_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				const __m128i score1low{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX1a],0), pScores[IDX1b], 1), pScores[IDX1c], 2), pScores[IDX1d], 3) };
				const __m128i score2low{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX2a],0), pScores[IDX2b], 1), pScores[IDX2c], 2), pScores[IDX2d], 3) };
				const __m128i score1high{ _mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX1e],0), pScores[IDX1f], 1) };
				const __m128i score2high{ _mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX2e],0), pScores[IDX2f], 1) };
				const __m256i score1{ _mm256_inserti128_si256(_mm256_castsi128_si256(score1low),score1high, 1) };
				const __m256i score2{ _mm256_inserti128_si256(_mm256_castsi128_si256(score2low),score2high, 1) };
				const __m128i value1low{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX1a],0), pValues[IDX1b], 1), pValues[IDX1c], 6), pValues[IDX1d], 7) };
				const __m128i value1high{ _mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX1e],0), pValues[IDX1f], 1) };
				const __m256i value1{ _mm256_inserti128_si256(_mm256_castsi128_si256(value1low),value1high, 1) };
				const __m128i value2low{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX2a],0), pValues[IDX2b], 1), pValues[IDX2c], 6), pValues[IDX2d], 7) };
				const __m128i value2high{ _mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX2e],0), pValues[IDX2f], 1) };
				const __m256i value2{ _mm256_inserti128_si256(_mm256_castsi128_si256(value2low),value2high, 1) };
				const __m256i comparision{ _mm256_cmpgt_epi32(score2, score1) };
				const __m256i maskValue{ _mm256_shufflehi_epi16(_mm256_shufflelo_epi16(comparision, 0b00001000), 0b00001000) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), maskValue) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1low{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1high{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2low{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2high{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1low{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1high{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2low{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2high{ _mm256_extracti128_si256(resultValue2, 1) };
				pScores[IDX1a] = _mm_extract_epi32(resultScore1low, 0);
				pScores[IDX1b] = _mm_extract_epi32(resultScore1low, 1);
				pScores[IDX1c] = _mm_extract_epi32(resultScore1low, 2);
				pScores[IDX1d] = _mm_extract_epi32(resultScore1low, 3);
				pScores[IDX1e] = _mm_extract_epi32(resultScore1high, 0);
				pScores[IDX1f] = _mm_extract_epi32(resultScore1high, 1);
				pScores[IDX2a] = _mm_extract_epi32(resultScore2low, 0);
				pScores[IDX2b] = _mm_extract_epi32(resultScore2low, 1);
				pScores[IDX2c] = _mm_extract_epi32(resultScore2low, 2);
				pScores[IDX2d] = _mm_extract_epi32(resultScore2low, 3);
				pScores[IDX2e] = _mm_extract_epi32(resultScore2high, 0);
				pScores[IDX2f] = _mm_extract_epi32(resultScore2high, 1);
				pValues[IDX1a] = _mm_extract_epi16(resultValue1low, 0);
				pValues[IDX1b] = _mm_extract_epi16(resultValue1low, 1);
				pValues[IDX1c] = _mm_extract_epi16(resultValue1low, 6);
				pValues[IDX1d] = _mm_extract_epi16(resultValue1low, 7);
				pValues[IDX1e] = _mm_extract_epi16(resultValue1high, 0);
				pValues[IDX1f] = _mm_extract_epi16(resultValue1high, 1);
				pValues[IDX2a] = _mm_extract_epi16(resultValue2low, 0);
				pValues[IDX2b] = _mm_extract_epi16(resultValue2low, 1);
				pValues[IDX2c] = _mm_extract_epi16(resultValue2low, 6);
				pValues[IDX2d] = _mm_extract_epi16(resultValue2low, 7);
				pValues[IDX2e] = _mm_extract_epi16(resultValue2high, 0);
				pValues[IDX2f] = _mm_extract_epi16(resultValue2high, 1);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			constexpr static void vector7_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				const __m128i score1low{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX1a],0), pScores[IDX1b], 1), pScores[IDX1c], 2), pScores[IDX1d], 3) };
				const __m128i score2low{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX2a],0), pScores[IDX2b], 1), pScores[IDX2c], 2), pScores[IDX2d], 3) };
				const __m128i score1high{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX1e],0), pScores[IDX1f], 1), pScores[IDX1g], 2) };
				const __m128i score2high{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX2e],0), pScores[IDX2f], 1), pScores[IDX2g], 2) };
				const __m256i score1{ _mm256_inserti128_si256(_mm256_castsi128_si256(score1low),score1high, 1) };
				const __m256i score2{ _mm256_inserti128_si256(_mm256_castsi128_si256(score2low),score2high, 1) };
				const __m128i value1low{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX1a],0), pValues[IDX1b], 1), pValues[IDX1c], 6), pValues[IDX1d], 7) };
				const __m128i value1high{_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX1e],0), pValues[IDX1f], 1), pValues[IDX1g], 6) };
				const __m256i value1{ _mm256_inserti128_si256(_mm256_castsi128_si256(value1low),value1high, 1) };
				const __m128i value2low{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX2a],0), pValues[IDX2b], 1), pValues[IDX2c], 6), pValues[IDX2d], 7) };
				const __m128i value2high{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX2e],0), pValues[IDX2f], 1), pValues[IDX2g], 6) };
				const __m256i value2{ _mm256_inserti128_si256(_mm256_castsi128_si256(value2low),value2high, 1) };
				const __m256i comparision{ _mm256_cmpgt_epi32(score2, score1) };
				const __m256i maskValue{ _mm256_shufflehi_epi16(_mm256_shufflelo_epi16(comparision, 0b00001000), 0b00001000) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), maskValue) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1low{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1high{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2low{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2high{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1low{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1high{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2low{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2high{ _mm256_extracti128_si256(resultValue2, 1) };
				pScores[IDX1a] = _mm_extract_epi32(resultScore1low, 0);
				pScores[IDX1b] = _mm_extract_epi32(resultScore1low, 1);
				pScores[IDX1c] = _mm_extract_epi32(resultScore1low, 2);
				pScores[IDX1d] = _mm_extract_epi32(resultScore1low, 3);
				pScores[IDX1e] = _mm_extract_epi32(resultScore1high, 0);
				pScores[IDX1f] = _mm_extract_epi32(resultScore1high, 1);
				pScores[IDX1g] = _mm_extract_epi32(resultScore1high, 2);
				pScores[IDX2a] = _mm_extract_epi32(resultScore2low, 0);
				pScores[IDX2b] = _mm_extract_epi32(resultScore2low, 1);
				pScores[IDX2c] = _mm_extract_epi32(resultScore2low, 2);
				pScores[IDX2d] = _mm_extract_epi32(resultScore2low, 3);
				pScores[IDX2e] = _mm_extract_epi32(resultScore2high, 0);
				pScores[IDX2f] = _mm_extract_epi32(resultScore2high, 1);
				pScores[IDX2g] = _mm_extract_epi32(resultScore2high, 2);
				pValues[IDX1a] = _mm_extract_epi16(resultValue1low, 0);
				pValues[IDX1b] = _mm_extract_epi16(resultValue1low, 1);
				pValues[IDX1c] = _mm_extract_epi16(resultValue1low, 6);
				pValues[IDX1d] = _mm_extract_epi16(resultValue1low, 7);
				pValues[IDX1e] = _mm_extract_epi16(resultValue1high, 0);
				pValues[IDX1f] = _mm_extract_epi16(resultValue1high, 1);
				pValues[IDX1g] = _mm_extract_epi16(resultValue1high, 6);
				pValues[IDX2a] = _mm_extract_epi16(resultValue2low, 0);
				pValues[IDX2b] = _mm_extract_epi16(resultValue2low, 1);
				pValues[IDX2c] = _mm_extract_epi16(resultValue2low, 6);
				pValues[IDX2d] = _mm_extract_epi16(resultValue2low, 7);
				pValues[IDX2e] = _mm_extract_epi16(resultValue2high, 0);
				pValues[IDX2f] = _mm_extract_epi16(resultValue2high, 1);
				pValues[IDX2g] = _mm_extract_epi16(resultValue2high, 6);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			constexpr static void vector8_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				const __m128i score1low{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX1a],0), pScores[IDX1b], 1), pScores[IDX1c], 2), pScores[IDX1d], 3) };
				const __m128i score2low{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX2a],0), pScores[IDX2b], 1), pScores[IDX2c], 2), pScores[IDX2d], 3) };
				const __m128i score1high{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX1e],0), pScores[IDX1f], 1), pScores[IDX1g], 2), pScores[IDX1h], 3) };
				const __m128i score2high{ _mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_insert_epi32(_mm_undefined_si128(), pScores[IDX2e],0), pScores[IDX2f], 1), pScores[IDX2g], 2), pScores[IDX2h], 3) };
				const __m256i score1{ _mm256_inserti128_si256(_mm256_castsi128_si256(score1low),score1high, 1) };
				const __m256i score2{ _mm256_inserti128_si256(_mm256_castsi128_si256(score2low),score2high, 1) };
				const __m128i value1low{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX1a],0), pValues[IDX1b], 1), pValues[IDX1c], 6), pValues[IDX1d], 7) };
				const __m128i value1high{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX1e],0), pValues[IDX1f], 1), pValues[IDX1g], 6), pValues[IDX1h], 7) };
				const __m256i value1{ _mm256_inserti128_si256(_mm256_castsi128_si256(value1low),value1high, 1) };
				const __m128i value2low{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX2a],0), pValues[IDX2b], 1), pValues[IDX2c], 6), pValues[IDX2d], 7) };
				const __m128i value2high{ _mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_insert_epi16(_mm_undefined_si128(), pValues[IDX2e],0), pValues[IDX2f], 1), pValues[IDX2g], 6), pValues[IDX2h], 7) };
				const __m256i value2{ _mm256_inserti128_si256(_mm256_castsi128_si256(value2low),value2high, 1) };
				const __m256i comparision{ _mm256_cmpgt_epi32(score2, score1) };
				const __m256i maskValue{ _mm256_shufflehi_epi16(_mm256_shufflelo_epi16(comparision, 0b00001000), 0b00001000) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), maskValue) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1low{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1high{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2low{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2high{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1low{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1high{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2low{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2high{ _mm256_extracti128_si256(resultValue2, 1) };
				pScores[IDX1a] = _mm_extract_epi32(resultScore1low, 0);
				pScores[IDX1b] = _mm_extract_epi32(resultScore1low, 1);
				pScores[IDX1c] = _mm_extract_epi32(resultScore1low, 2);
				pScores[IDX1d] = _mm_extract_epi32(resultScore1low, 3);
				pScores[IDX1e] = _mm_extract_epi32(resultScore1high, 0);
				pScores[IDX1f] = _mm_extract_epi32(resultScore1high, 1);
				pScores[IDX1g] = _mm_extract_epi32(resultScore1high, 2);
				pScores[IDX1h] = _mm_extract_epi32(resultScore1high, 3);
				pScores[IDX2a] = _mm_extract_epi32(resultScore2low, 0);
				pScores[IDX2b] = _mm_extract_epi32(resultScore2low, 1);
				pScores[IDX2c] = _mm_extract_epi32(resultScore2low, 2);
				pScores[IDX2d] = _mm_extract_epi32(resultScore2low, 3);
				pScores[IDX2e] = _mm_extract_epi32(resultScore2high, 0);
				pScores[IDX2f] = _mm_extract_epi32(resultScore2high, 1);
				pScores[IDX2g] = _mm_extract_epi32(resultScore2high, 2);
				pScores[IDX2h] = _mm_extract_epi32(resultScore2high, 3);
				pValues[IDX1a] = _mm_extract_epi16(resultValue1low, 0);
				pValues[IDX1b] = _mm_extract_epi16(resultValue1low, 1);
				pValues[IDX1c] = _mm_extract_epi16(resultValue1low, 6);
				pValues[IDX1d] = _mm_extract_epi16(resultValue1low, 7);
				pValues[IDX1e] = _mm_extract_epi16(resultValue1high, 0);
				pValues[IDX1f] = _mm_extract_epi16(resultValue1high, 1);
				pValues[IDX1g] = _mm_extract_epi16(resultValue1high, 6);
				pValues[IDX1h] = _mm_extract_epi16(resultValue1high, 7);
				pValues[IDX2a] = _mm_extract_epi16(resultValue2low, 0);
				pValues[IDX2b] = _mm_extract_epi16(resultValue2low, 1);
				pValues[IDX2c] = _mm_extract_epi16(resultValue2low, 6);
				pValues[IDX2d] = _mm_extract_epi16(resultValue2low, 7);
				pValues[IDX2e] = _mm_extract_epi16(resultValue2high, 0);
				pValues[IDX2f] = _mm_extract_epi16(resultValue2high, 1);
				pValues[IDX2g] = _mm_extract_epi16(resultValue2high, 6);
				pValues[IDX2h] = _mm_extract_epi16(resultValue2high, 7);
			}
#endif
		public:
			template<size_t IDX1, size_t IDX2>
			constexpr static void scalar(VALUE* pValues, SCORE* pScores) noexcept
			{
				scalar_Vanilla<IDX1, IDX2>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			constexpr static void vector2(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector2_SSE2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				else
#endif
					vector2_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			constexpr static void vector3(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector3_SSE2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
				else
#endif
					vector3_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			constexpr static void vector4(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector4_SSE2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				else
#endif
					vector4_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e>
			constexpr static void vector5(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_AVX2)
				if constexpr (cpu::supports(cpu::AVX2))
					vector5_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
				else
#endif
					vector5_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			constexpr static void vector6(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_AVX2)
				if constexpr (cpu::supports(cpu::AVX2))
					vector6_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
				else
#endif
					vector6_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			constexpr static void vector7(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_AVX2)
				if constexpr (cpu::supports(cpu::AVX2))
					vector7_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
				else
#endif
					vector7_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			constexpr static void vector8(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_AVX2)
				if constexpr (cpu::supports(cpu::AVX2))
					vector8_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				else
#endif
					vector8_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
			}
		};

		template<typename VALUE, typename SCORE>
		class sortAlgorithm
		{
		private:
			constexpr static void quickSort(const int low, const int high, VALUE* pValues, SCORE* pScores) noexcept
			{
				assert(low < high);
				const int pi{ partition(low, high, pValues, pScores) };
				sortValues(&pValues[low], &pScores[low], pi - low);
				sortValues(&pValues[pi + 1], &pScores[pi + 1], high - pi);
			}
			constexpr static int partition(const int low, const int high, VALUE* pValues, SCORE* pScores) noexcept
			{
				const SCORE pivotScore{ pScores[high] };
				int i{ low - 1 };
				for (int j = low; j <= high - 1; j++)
				{
					if (pScores[j] >= pivotScore)
					{
						i++;
						std::swap(pValues[i], pValues[j]);
						std::swap(pScores[i], pScores[j]);
					}
				}
				std::swap(pValues[i + 1], pValues[high]);
				std::swap(pScores[i + 1], pScores[high]);
				return (i + 1);
			}
			template<size_t IDX1, size_t IDX2>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				compare<VALUE, SCORE>::template scalar<IDX1, IDX2>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				compare<VALUE, SCORE>::template vector2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				compare<VALUE, SCORE>::template vector3<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				compare<VALUE, SCORE>::template vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				compare<VALUE, SCORE>::template vector5<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				compare<VALUE, SCORE>::template vector6<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				compare<VALUE, SCORE>::template vector7<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				compare<VALUE, SCORE>::template vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
				comparator<IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
				comparator<IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
				comparator<IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
				comparator<IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
				comparator<IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
				comparator<IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				comparator<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p, size_t IDX1q, size_t IDX2q>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				comparator<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p, IDX1q, IDX2q>(pValues, pScores);
			}
			constexpr static void sort_N1(VALUE* pValues, SCORE* pScores) noexcept
			{
			}
			constexpr static void sort_N2(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 1>(pValues, pScores); // FIRST 1-Lane
			}
			constexpr static void sort_N3(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<1, 2>(pValues, pScores);
				comparator<0, 2>(pValues, pScores);
				comparator<0, 1>(pValues, pScores);
			}
			constexpr static void sort_N4(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 1, 2, 3>(pValues, pScores); // FIRST 2-Lane
				comparator<0, 2, 1, 3>(pValues, pScores);
				comparator<1, 2>(pValues, pScores);
			}
			constexpr static void sort_N5(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 4, 1, 3>(pValues, pScores);
				comparator<0, 2>(pValues, pScores);
				comparator<2, 4, 0, 1>(pValues, pScores);
				comparator<2, 3, 1, 4>(pValues, pScores);
				comparator<1, 2, 3, 4>(pValues, pScores);
			}
			constexpr static void sort_N6(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 4, 1, 5>(pValues, pScores);
				comparator<0, 2, 1, 3>(pValues, pScores);
				comparator<2, 4, 3, 5, 0, 1>(pValues, pScores); // FIRST 3-Lane
				comparator<2, 3, 4, 5>(pValues, pScores);
				comparator<1, 4>(pValues, pScores);
				comparator<1, 2, 3, 4 >(pValues, pScores);
			}
			constexpr static void sort_N7(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 4, 1, 5, 2, 6>(pValues, pScores);
				comparator<0, 2, 1, 3, 4, 6>(pValues, pScores);
				comparator<2, 4, 3, 5, 0, 1>(pValues, pScores);
				comparator<2, 3, 4, 5>(pValues, pScores);
				comparator<1, 4, 3, 6>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6>(pValues, pScores);
			}
			constexpr static void sort_N8(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores); // FIRST 4-Lane
				comparator<0, 2, 1, 3, 4, 6, 5, 7>(pValues, pScores);
				comparator<2, 4, 3, 5, 0, 1, 6, 7>(pValues, pScores);
				comparator<2, 3, 4, 5>(pValues, pScores);
				comparator<1, 4, 3, 6>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6>(pValues, pScores);
			}
			constexpr static void sort_N9(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 8, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				comparator<0, 4, 1, 3, 5, 7>(pValues, pScores);
				comparator<4, 8, 0, 2, 3, 5>(pValues, pScores);
				comparator<4, 6, 2, 8, 0, 1>(pValues, pScores);
				comparator<2, 4, 6, 8>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 1, 8>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8>(pValues, pScores);
			}
			constexpr static void sort_N10(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<4, 9, 3, 8, 2, 7, 1, 6, 0, 5>(pValues, pScores);
				comparator<1, 4, 6, 9, 0, 3, 5, 8>(pValues, pScores);
				comparator<0, 2, 3, 6, 7, 9>(pValues, pScores);
				comparator<0, 1, 2, 4, 5, 7, 8, 9>(pValues, pScores);
				comparator<1, 2, 4, 6, 7, 8, 3, 5>(pValues, pScores);
				comparator<2, 5, 6, 8, 1, 3, 4, 7>(pValues, pScores);
				comparator<2, 3, 6, 7>(pValues, pScores);
				comparator<3, 4, 5, 6>(pValues, pScores);
				comparator<4, 5>(pValues, pScores);
			}
			constexpr static void sort_N11(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>(pValues, pScores);
				comparator<1, 3, 5, 7, 0, 2, 4, 6, 8, 10>(pValues, pScores);
				comparator<1, 2, 5, 6, 9, 10, 0, 4, 3, 7>(pValues, pScores);
				comparator<1, 5, 6, 10, 4, 8>(pValues, pScores);
				comparator<5, 9, 2, 6, 0, 4, 3, 8>(pValues, pScores);
				comparator<1, 5, 6, 10, 2, 3, 8, 9>(pValues, pScores);
				comparator<1, 4, 7, 10, 3, 5, 6, 8>(pValues, pScores);
				comparator<2, 4, 7, 9, 5, 6>(pValues, pScores);
				comparator<3, 4, 7, 8>(pValues, pScores);
			}
			constexpr static void sort_N12(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11>(pValues, pScores);
				comparator<1, 3, 5, 7, 9, 11, 0, 2, 4, 6, 8, 10>(pValues, pScores);
				comparator<1, 2, 5, 6, 9, 10, 0, 4, 7, 11>(pValues, pScores);
				comparator<1, 5, 6, 10, 3, 7, 4, 8>(pValues, pScores);
				comparator<5, 9, 2, 6, 0, 4, 7, 11, 3, 8>(pValues, pScores);
				comparator<1, 5, 6, 10, 2, 3, 8, 9>(pValues, pScores);
				comparator<1, 4, 7, 10, 3, 5, 6, 8>(pValues, pScores);
				comparator<2, 4, 7, 9, 5, 6>(pValues, pScores);
				comparator<3, 4, 7, 8>(pValues, pScores);
			}
			constexpr static void sort_N13(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<1, 7, 9, 11, 3, 4, 5, 8, 0, 12, 2, 6>(pValues, pScores);
				comparator<0, 1, 2, 3, 4, 6, 8, 11, 7, 12, 5, 9>(pValues, pScores);
				comparator<0, 2, 3, 7, 10, 11, 1, 4, 6, 12>(pValues, pScores);
				comparator<7, 8, 11, 12, 4, 9, 6, 10>(pValues, pScores);
				comparator<3, 4, 5, 6, 8, 9, 10, 11, 1, 7>(pValues, pScores);
				comparator<2, 6, 9, 11, 1, 3, 4, 7, 8, 10, 0, 5>(pValues, pScores);
				comparator<2, 5, 6, 8, 9, 10>(pValues, pScores);
				comparator<1, 2, 3, 5, 7, 8, 4, 6>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9>(pValues, pScores);
				comparator<3, 4, 5, 6>(pValues, pScores);
			}
			constexpr static void sort_N14(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13>(pValues, pScores);
				comparator<0, 2, 4, 6, 8, 10, 1, 3, 5, 7, 9, 11>(pValues, pScores);
				comparator<0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 3, 7>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13>(pValues, pScores);
				comparator<5, 10, 6, 9, 3, 12, 7, 11, 1, 2, 4, 8>(pValues, pScores);
				comparator<1, 4, 7, 13, 2, 8, 5, 6, 9, 10>(pValues, pScores);
				comparator<2, 4, 11, 13, 3, 8, 7, 12>(pValues, pScores);
				comparator<6, 8, 10, 12, 3, 5, 7, 9>(pValues, pScores);
				comparator<3, 4, 5, 6, 7, 8, 9, 10, 11, 12>(pValues, pScores);
				comparator<6, 7, 8, 9>(pValues, pScores);
			}
			constexpr static void sort_N15(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13>(pValues, pScores);
				comparator<0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11>(pValues, pScores);
				comparator<0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14>(pValues, pScores);
				comparator<5, 10, 6, 9, 3, 12, 13, 14, 7, 11, 1, 2, 4, 8>(pValues, pScores);
				comparator<1, 4, 7, 13, 2, 8, 11, 14, 5, 6, 9, 10>(pValues, pScores);
				comparator<2, 4, 11, 13, 3, 8, 7, 12>(pValues, pScores);
				comparator<6, 8, 10, 12, 3, 5, 7, 9>(pValues, pScores);
				comparator<3, 4, 5, 6, 7, 8, 9, 10, 11, 12>(pValues, pScores);
				comparator<6, 7, 8, 9>(pValues, pScores);
			}
			constexpr static void sort_N16(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15>(pValues, pScores);
				comparator<0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15>(pValues, pScores);
				comparator<0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				comparator<5, 10, 6, 9, 3, 12, 13, 14, 7, 11, 1, 2, 4, 8>(pValues, pScores);
				comparator<1, 4, 7, 13, 2, 8, 11, 14, 5, 6, 9, 10>(pValues, pScores);
				comparator<2, 4, 11, 13, 3, 8, 7, 12>(pValues, pScores);
				comparator<6, 8, 10, 12, 3, 5, 7, 9>(pValues, pScores);
				comparator<3, 4, 5, 6, 7, 8, 9, 10, 11, 12>(pValues, pScores);
				comparator<6, 7, 8, 9>(pValues, pScores);
			}
			constexpr static void sort_N17(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				comparator<0, 8, 1, 5, 2, 6, 3, 7, 9, 13, 10, 14, 11, 15>(pValues, pScores);
				comparator<8, 16, 0, 4, 5, 9, 6, 10, 7, 11, 1, 3, 13, 15>(pValues, pScores);
				comparator<8, 12, 4, 16, 0, 2, 5, 7, 9, 11>(pValues, pScores);
				comparator<4, 8, 12, 16, 3, 9, 7, 13, 0, 1>(pValues, pScores);
				comparator<4, 6, 8, 10, 12, 14, 2, 16, 3, 5, 7, 9, 11, 13>(pValues, pScores);
				comparator<2, 8, 6, 12, 10, 16>(pValues, pScores);
				comparator<2, 4, 6, 8, 10, 12, 14, 16>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 16>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 7, 14, 9, 16>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16>(pValues, pScores);
			}
			constexpr static void sort_N18(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 6, 3, 7, 10, 14, 11, 15>(pValues, pScores);
				comparator<8, 16, 9, 17, 0, 4, 1, 5, 6, 10, 7, 11>(pValues, pScores);
				comparator<8, 12, 9, 13, 4, 16, 5, 17, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 8, 5, 9, 12, 16, 13, 17, 0, 1>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 2, 16, 3, 17>(pValues, pScores);
				comparator<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>(pValues, pScores);
				comparator<1, 16, 3, 10, 5, 12, 7, 14>(pValues, pScores);
				comparator<1, 8, 9, 16, 3, 6, 7, 10, 11, 14>(pValues, pScores);
				comparator<1, 4, 5, 8, 9, 12, 13, 16>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16>(pValues, pScores);
			}
			constexpr static void sort_N19(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 7, 11, 15>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 0, 4, 1, 5, 2, 6, 7, 11>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 4, 16, 5, 17, 6, 18, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 8, 5, 9, 6, 10, 12, 16, 13, 17, 14, 18, 0, 1>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 3, 17>(pValues, pScores);
				comparator<2, 16, 3, 9, 6, 12, 7, 13, 11, 17>(pValues, pScores);
				comparator<2, 8, 10, 16, 3, 5, 7, 9, 11, 13, 15, 17>(pValues, pScores);
				comparator<2, 4, 6, 8, 10, 12, 14, 16>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 12, 7, 14>(pValues, pScores);
				comparator<1, 8, 3, 10, 9, 16, 11, 18>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18>(pValues, pScores);
			}
			constexpr static void sort_N20(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 4, 16, 5, 17, 6, 18, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 0, 1>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				comparator<2, 16, 3, 17, 6, 12, 7, 13, 18, 19>(pValues, pScores);
				comparator<2, 8, 3, 9, 10, 16, 11, 17>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 12, 7, 14>(pValues, pScores);
				comparator<1, 8, 3, 10, 9, 16, 11, 18>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18>(pValues, pScores);
			}
			constexpr static void sort_N21(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 5, 17, 6, 18, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 16, 5, 9, 6, 10, 7, 11, 13, 17, 14, 18, 15, 19, 0, 1>(pValues, pScores);
				comparator<4, 8, 12, 16, 5, 7, 9, 11, 13, 15, 17, 19>(pValues, pScores);
				comparator<4, 6, 8, 10, 12, 14, 16, 18, 3, 17, 7, 13>(pValues, pScores);
				comparator<2, 16, 6, 20, 3, 9, 11, 17>(pValues, pScores);
				comparator<2, 8, 6, 12, 10, 16, 14, 20, 3, 5, 7, 9, 11, 13, 15, 17>(pValues, pScores);
				comparator<2, 4, 6, 8, 10, 12, 14, 16, 18, 20>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 20, 7, 14>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 9, 16, 11, 18, 13, 20>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20>(pValues, pScores);
			}
			constexpr static void sort_N22(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 14, 7, 15>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 6, 18, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 16, 5, 17, 6, 10, 7, 11, 14, 18, 15, 19, 0, 1>(pValues, pScores);
				comparator<4, 8, 5, 9, 12, 16, 13, 17>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				comparator<2, 16, 3, 17, 6, 20, 7, 21>(pValues, pScores);
				comparator<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 20, 7, 14>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 9, 16, 11, 18, 13, 20>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20>(pValues, pScores);
			}
			constexpr static void sort_N23(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 15>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 16, 5, 17, 6, 18, 7, 11, 15, 19, 20, 22, 0, 1>(pValues, pScores);
				comparator<4, 8, 5, 9, 6, 10, 12, 16, 13, 17, 14, 18>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				comparator<2, 16, 3, 17, 6, 20, 7, 21>(pValues, pScores);
				comparator<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 20, 7, 22>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22>(pValues, pScores);
			}
			constexpr static void sort_N24(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 16, 5, 17, 6, 18, 7, 19, 20, 22, 21, 23, 0, 1>(pValues, pScores);
				comparator<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 22, 23>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				comparator<2, 16, 3, 17, 6, 20, 7, 21>(pValues, pScores);
				comparator<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 20, 7, 22>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22>(pValues, pScores);
			}
			constexpr static void sort_N25(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 21, 23, 0, 1>(pValues, pScores);
				comparator<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22>(pValues, pScores);
				comparator<2, 16, 3, 17, 6, 20, 7, 21, 10, 24>(pValues, pScores);
				comparator<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 20, 7, 22, 9, 24>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24>(pValues, pScores);
			}
			constexpr static void sort_N26(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 0, 1>(pValues, pScores);
				comparator<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23>(pValues, pScores);
				comparator<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25>(pValues, pScores);
				comparator<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 20, 7, 22, 9, 24>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24>(pValues, pScores);
			}
			constexpr static void sort_N27(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 0, 1>(pValues, pScores);
				comparator<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26>(pValues, pScores);
				comparator<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25>(pValues, pScores);
				comparator<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26>(pValues, pScores);
			}
			constexpr static void sort_N28(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				comparator<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				comparator<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 26, 27>(pValues, pScores);
				comparator<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26>(pValues, pScores);
			}
			constexpr static void sort_N29(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				comparator<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				comparator<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28>(pValues, pScores);
				comparator<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28>(pValues, pScores);
			}
			constexpr static void sort_N30(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28, 25, 29>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				comparator<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				comparator<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				comparator<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28, 15, 29>(pValues, pScores);
				comparator<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28, 23, 29>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28, 27, 29>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28>(pValues, pScores);
			}
			constexpr static void sort_N31(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29, 22, 30>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28, 25, 29, 26, 30>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3, 28, 30>(pValues, pScores);
				comparator<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				comparator<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				comparator<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28, 15, 29>(pValues, pScores);
				comparator<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28, 23, 29>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28, 27, 29>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28, 15, 30>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28, 23, 30>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28, 27, 30>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30>(pValues, pScores);
			}
			constexpr static void sort_N32(VALUE* pValues, SCORE* pScores) noexcept
			{
				comparator<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30, 15, 31>(pValues, pScores);
				comparator<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29, 22, 30, 23, 31>(pValues, pScores);
				comparator<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28, 25, 29, 26, 30, 27, 31>(pValues, pScores);
				comparator<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3, 28, 30, 29, 31>(pValues, pScores);
				comparator<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1, 30, 31>(pValues, pScores);
				comparator<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				comparator<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				comparator<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28, 15, 29>(pValues, pScores);
				comparator<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28, 23, 29>(pValues, pScores);
				comparator<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28, 27, 29>(pValues, pScores);
				comparator<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29>(pValues, pScores);
				comparator<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28, 15, 30>(pValues, pScores);
				comparator<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28, 23, 30>(pValues, pScores);
				comparator<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28, 27, 30>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30>(pValues, pScores);
			}
			typedef void SORTFUNCTION(VALUE* pValues, SCORE* pScores);
			constexpr static inline SORTFUNCTION* m_Sort[31]
			{
				&sort_N2,
				&sort_N3,
				&sort_N4,
				&sort_N5,
				&sort_N6,
				&sort_N7,
				&sort_N8,
				&sort_N9,
				&sort_N10,
				&sort_N11,
				&sort_N12,
				&sort_N13,
				&sort_N14,
				&sort_N15,
				&sort_N16,
				&sort_N17,
				&sort_N18,
				&sort_N19,
				&sort_N20,
				&sort_N21,
				&sort_N22,
				&sort_N23,
				&sort_N24,
				&sort_N25,
				&sort_N26,
				&sort_N27,
				&sort_N28,
				&sort_N29,
				&sort_N30,
				&sort_N31,
				&sort_N32
			};
			constexpr static size_t sort_tail() noexcept
			{
				return 32;
			}
		public:
			constexpr static void sortValues(VALUE* pValues, SCORE* pScores, const size_t length) noexcept
			{
				if (length > 1)
				{
					if (length <= sort_tail())
					{
						m_Sort[length - 2](pValues, pScores);
					}
					else
					{
						quickSort(0, length - 1, pValues, pScores);
					}
				}
			}
		};
	}


	template<typename VALUE, typename SCORE>
	class sort
	{
	public:
		constexpr static void sortValues(VALUE* pValues, SCORE* pScores, const size_t length) noexcept
		{
			if constexpr (sizeof(VALUE) == sizeof(std::uint8_t) && sizeof(SCORE) == sizeof(std::int8_t))
				detail::sortAlgorithm<std::uint8_t, std::int8_t>::sortValues(reinterpret_cast<std::uint8_t*>(pValues), reinterpret_cast<std::int8_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint8_t) && sizeof(SCORE) == sizeof(std::int16_t))
				detail::sortAlgorithm<std::uint8_t, std::int16_t>::sortValues(reinterpret_cast<std::uint8_t*>(pValues), reinterpret_cast<std::int16_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint8_t) && sizeof(SCORE) == sizeof(std::int32_t))
				detail::sortAlgorithm<std::uint8_t, std::int32_t>::sortValues(reinterpret_cast<std::uint8_t*>(pValues), reinterpret_cast<std::int32_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint8_t) && sizeof(SCORE) == sizeof(std::int64_t))
				detail::sortAlgorithm<std::uint8_t, std::int64_t>::sortValues(reinterpret_cast<std::uint8_t*>(pValues), reinterpret_cast<std::int64_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint16_t) && sizeof(SCORE) == sizeof(std::int8_t))
				detail::sortAlgorithm<std::uint16_t, std::int8_t>::sortValues(reinterpret_cast<std::uint16_t*>(pValues), reinterpret_cast<std::int8_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint16_t) && sizeof(SCORE) == sizeof(std::int16_t))
				detail::sortAlgorithm<std::uint16_t, std::int16_t>::sortValues(reinterpret_cast<std::uint16_t*>(pValues), reinterpret_cast<std::int16_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint16_t) && sizeof(SCORE) == sizeof(std::int32_t))
				detail::sortAlgorithm<std::uint16_t, std::int32_t>::sortValues(reinterpret_cast<std::uint16_t*>(pValues), reinterpret_cast<std::int32_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint16_t) && sizeof(SCORE) == sizeof(std::int64_t))
				detail::sortAlgorithm<std::uint16_t, std::int64_t>::sortValues(reinterpret_cast<std::uint16_t*>(pValues), reinterpret_cast<std::int64_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint32_t) && sizeof(SCORE) == sizeof(std::int8_t))
				detail::sortAlgorithm<std::uint32_t, std::int8_t>::sortValues(reinterpret_cast<std::uint32_t*>(pValues), reinterpret_cast<std::int8_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint32_t) && sizeof(SCORE) == sizeof(std::int16_t))
				detail::sortAlgorithm<std::uint32_t, std::int16_t>::sortValues(reinterpret_cast<std::uint32_t*>(pValues), reinterpret_cast<std::int16_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint32_t) && sizeof(SCORE) == sizeof(std::int32_t))
				detail::sortAlgorithm<std::uint32_t, std::int32_t>::sortValues(reinterpret_cast<std::uint32_t*>(pValues), reinterpret_cast<std::int32_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint32_t) && sizeof(SCORE) == sizeof(std::int64_t))
				detail::sortAlgorithm<std::uint32_t, std::int64_t>::sortValues(reinterpret_cast<std::uint32_t*>(pValues), reinterpret_cast<std::int64_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint64_t) && sizeof(SCORE) == sizeof(std::int8_t))
				detail::sortAlgorithm<std::uint64_t, std::int8_t>::sortValues(reinterpret_cast<std::uint64_t*>(pValues), reinterpret_cast<std::int8_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint64_t) && sizeof(SCORE) == sizeof(std::int16_t))
				detail::sortAlgorithm<std::uint64_t, std::int16_t>::sortValues(reinterpret_cast<std::uint64_t*>(pValues), reinterpret_cast<std::int16_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint64_t) && sizeof(SCORE) == sizeof(std::int32_t))
				detail::sortAlgorithm<std::uint64_t, std::int32_t>::sortValues(reinterpret_cast<std::uint64_t*>(pValues), reinterpret_cast<std::int32_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint64_t) && sizeof(SCORE) == sizeof(std::int64_t))
				detail::sortAlgorithm<std::uint64_t, std::int64_t>::sortValues(reinterpret_cast<std::uint64_t*>(pValues), reinterpret_cast<std::int64_t*>(pScores), length);
			else
				detail::sortAlgorithm<VALUE, SCORE>::sortValues(pValues, pScores, length);
		}
	};
}