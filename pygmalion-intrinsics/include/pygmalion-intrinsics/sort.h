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
			template<size_t IDX1, size_t IDX2>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
#if defined(SORT_IL8)
				const IL8 operand1 = _mm_insert_epi16(_mm_loadu_si16(pValues + IDX1), pScores[IDX1], 1);
				const IL8 operand2 = _mm_insert_epi16(_mm_loadu_si16(pValues + IDX2), pScores[IDX2], 1);
				const IL8 mask = _mm_shufflelo_epi16(_mm_cmpgt_epi16(operand2, operand1), 0b00001010);
#if defined(__SSE41__)
				const IL8 result1 = _mm_blendv_epi8(operand1, operand2, mask);
				const IL8 result2 = _mm_blendv_epi8(operand2, operand1, mask);
#else
				const IL8 delta = _mm_and_si128(_mm_xor_si128(operand1, operand2), mask);
				const IL8 result1 = _mm_xor_si128(operand1, delta);
				const IL8 result2 = _mm_xor_si128(operand2, delta);
#endif
				_mm_storeu_si16(pValues + IDX1, result1);
				pScores[IDX1] = _mm_extract_epi16(result1, 1);
				_mm_storeu_si16(pValues + IDX2, result2);
				pScores[IDX2] = _mm_extract_epi16(result2, 1);
#else
				if (pScores[IDX1] < pScores[IDX2])
				{
					std::swap(pValues[IDX1], pValues[IDX2]);
					std::swap(pScores[IDX1], pScores[IDX2]);
				}
#endif
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
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
#if defined(SORT_IL8)
				const IL8 score1 = _mm_insert_epi16(_mm_loadu_si16(pScores + IDX1a), pScores[IDX2a], 1);
				const IL8 score2 = _mm_insert_epi16(_mm_loadu_si16(pScores + IDX1b), pScores[IDX2b], 1);
				const IL8 operand1 = _mm_insert_epi16(_mm_insert_epi16(score1, pValues[IDX1a], 2), pValues[IDX2a], 3);
				const IL8 operand2 = _mm_insert_epi16(_mm_insert_epi16(score2, pValues[IDX1b], 2), pValues[IDX2b], 3);
				const IL8 mask = _mm_shufflelo_epi16(_mm_cmpgt_epi16(operand2, operand1), 0b01000100);
#if defined(__SSE41__)
				const IL8 result1 = _mm_blendv_epi8(operand1, operand2, mask);
				const IL8 result2 = _mm_blendv_epi8(operand2, operand1, mask);
#else
				const IL8 delta = _mm_and_si128(_mm_xor_si128(operand1, operand2), mask);
				const IL8 result1 = _mm_xor_si128(operand1, delta);
				const IL8 result2 = _mm_xor_si128(operand2, delta);
#endif
				_mm_storeu_si16(pScores + IDX1a, result1);
				pScores[IDX2a] = _mm_extract_epi16(result1, 1);
				pValues[IDX1a] = _mm_extract_epi16(result1, 2);
				pValues[IDX2a] = _mm_extract_epi16(result1, 3);
				_mm_storeu_si16(pScores + IDX1b, result2);
				pScores[IDX2b] = _mm_extract_epi16(result2, 1);
				pValues[IDX1b] = _mm_extract_epi16(result2, 2);
				pValues[IDX2b] = _mm_extract_epi16(result2, 3);
#elif defined(SORT_IL16)
				const IL16 score1 = _mm256_insert_epi16(_mm256_castsi128_si256(_mm_loadu_si16(pScores + IDX1a)), pScores[IDX2a], 1);
				const IL16 score2 = _mm256_insert_epi16(_mm256_castsi128_si256(_mm_loadu_si16(pScores + IDX1b)), pScores[IDX2b], 1);
				const IL16 operand1 = _mm256_insert_epi16(_mm256_insert_epi16(score1, pValues[IDX1a], 2), pValues[IDX2a], 3);
				const IL16 operand2 = _mm256_insert_epi16(_mm256_insert_epi16(score2, pValues[IDX1b], 2), pValues[IDX2b], 3);
				const IL16 mask = _mm256_shufflelo_epi16(_mm256_cmpgt_epi16(operand2, operand1), 0b01000100);
#if defined(__AVX2__)
				const IL16 result1 = _mm256_blendv_epi8(operand1, operand2, mask);
				const IL16 result2 = _mm256_blendv_epi8(operand2, operand1, mask);
#else
				const IL16 delta = _mm256_and_si256(_mm256_xor_si256(operand1, operand2), mask);
				const IL16 result1 = _mm256_xor_si256(operand1, delta);
				const IL16 result2 = _mm256_xor_si256(operand2, delta);
#endif
				_mm_storeu_si16(pScores + IDX1a, _mm256_castsi256_si128(result1));
				pScores[IDX2a] = _mm256_extract_epi16(result1, 1);
				pValues[IDX1a] = _mm256_extract_epi16(result1, 2);
				pValues[IDX2a] = _mm256_extract_epi16(result1, 3);
				_mm_storeu_si16(pScores + IDX1b, _mm256_castsi256_si128(result2));
				pScores[IDX2b] = _mm256_extract_epi16(result2, 1);
				pValues[IDX1b] = _mm256_extract_epi16(result2, 2);
				pValues[IDX2b] = _mm256_extract_epi16(result2, 3);
#else
				comparator<IDX1a, IDX2a>(pValues, pScores);
				comparator<IDX1b, IDX2b>(pValues, pScores);
#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
#if defined(SORT_IL8)
				IL8 values1 = IL8_Load<IDX1a, IDX1b, IDX1c>(reinterpret_cast<SCORE*>(pValues));
				IL8 values2 = IL8_Load<IDX2a, IDX2b, IDX2c>(reinterpret_cast<SCORE*>(pValues));
				IL8 scores1 = IL8_Load<IDX1a, IDX1b, IDX1c>(pScores);
				IL8 scores2 = IL8_Load<IDX2a, IDX2b, IDX2c>(pScores);
				IL8_Compare(values1, values2, scores1, scores2);
				IL8_Store<IDX1a, IDX1b, IDX1c>(values1, reinterpret_cast<SCORE*>(pValues));
				IL8_Store<IDX2a, IDX2b, IDX2c>(values2, reinterpret_cast<SCORE*>(pValues));
				IL8_Store<IDX1a, IDX1b, IDX1c>(scores1, pScores);
				IL8_Store<IDX2a, IDX2b, IDX2c>(scores2, pScores);
#elif defined(SORT_IL16)
				IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c>(reinterpret_cast<SCORE*>(pValues));
				IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c>(reinterpret_cast<SCORE*>(pValues));
				IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c>(pScores);
				IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c>(pScores);
				IL16_Compare(values1, values2, scores1, scores2);
				IL16_Store<IDX1a, IDX1b, IDX1c>(values1, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX2a, IDX2b, IDX2c>(values2, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX1a, IDX1b, IDX1c>(scores1, pScores);
				IL16_Store<IDX2a, IDX2b, IDX2c>(scores2, pScores);
#else
				comparator<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				comparator<IDX1c, IDX2c>(pValues, pScores);
#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
#if defined(SORT_IL8)
				IL8 values1 = IL8_Load<IDX1a, IDX1b, IDX1c, IDX1d>(reinterpret_cast<SCORE*>(pValues));
				IL8 values2 = IL8_Load<IDX2a, IDX2b, IDX2c, IDX2d>(reinterpret_cast<SCORE*>(pValues));
				IL8 scores1 = IL8_Load<IDX1a, IDX1b, IDX1c, IDX1d>(pScores);
				IL8 scores2 = IL8_Load<IDX2a, IDX2b, IDX2c, IDX2d>(pScores);
				IL8_Compare(values1, values2, scores1, scores2);
				IL8_Store<IDX1a, IDX1b, IDX1c, IDX1d>(values1, reinterpret_cast<SCORE*>(pValues));
				IL8_Store<IDX2a, IDX2b, IDX2c, IDX2d>(values2, reinterpret_cast<SCORE*>(pValues));
				IL8_Store<IDX1a, IDX1b, IDX1c, IDX1d>(scores1, pScores);
				IL8_Store<IDX2a, IDX2b, IDX2c, IDX2d>(scores2, pScores);
#elif defined(SORT_IL16)
				IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d>(reinterpret_cast<SCORE*>(pValues));
				IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d>(reinterpret_cast<SCORE*>(pValues));
				IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d>(pScores);
				IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d>(pScores);
				IL16_Compare(values1, values2, scores1, scores2);
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d>(values1, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d>(values2, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d>(scores1, pScores);
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d>(scores2, pScores);
#else
				comparator<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				comparator<IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
#if defined(SORT_IL8)
				IL8 values1 = IL8_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e>(reinterpret_cast<SCORE*>(pValues));
				IL8 values2 = IL8_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e>(reinterpret_cast<SCORE*>(pValues));
				IL8 scores1 = IL8_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e>(pScores);
				IL8 scores2 = IL8_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e>(pScores);
				IL8_Compare(values1, values2, scores1, scores2);
				IL8_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e>(values1, reinterpret_cast<SCORE*>(pValues));
				IL8_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e>(values2, reinterpret_cast<SCORE*>(pValues));
				IL8_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e>(scores1, pScores);
				IL8_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e>(scores2, pScores);
#elif defined(SORT_IL16)
				IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e>(reinterpret_cast<SCORE*>(pValues));
				IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e>(reinterpret_cast<SCORE*>(pValues));
				IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e>(pScores);
				IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e>(pScores);
				IL16_Compare(values1, values2, scores1, scores2);
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e>(values1, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e>(values2, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e>(scores1, pScores);
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e>(scores2, pScores);
#else
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
				comparator<IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
#if defined(SORT_IL8)
				IL8 values1 = IL8_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f>(reinterpret_cast<SCORE*>(pValues));
				IL8 values2 = IL8_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f>(reinterpret_cast<SCORE*>(pValues));
				IL8 scores1 = IL8_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f>(pScores);
				IL8 scores2 = IL8_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f>(pScores);
				IL8_Compare(values1, values2, scores1, scores2);
				IL8_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f>(values1, reinterpret_cast<SCORE*>(pValues));
				IL8_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f>(values2, reinterpret_cast<SCORE*>(pValues));
				IL8_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f>(scores1, pScores);
				IL8_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f>(scores2, pScores);
#elif defined(SORT_IL16)
				IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f>(reinterpret_cast<SCORE*>(pValues));
				IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f>(reinterpret_cast<SCORE*>(pValues));
				IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f>(pScores);
				IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f>(pScores);
				IL16_Compare(values1, values2, scores1, scores2);
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f>(values1, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f>(values2, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f>(scores1, pScores);
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f>(scores2, pScores);
#else
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
				comparator<IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
#if defined(SORT_IL8)
				IL8 values1 = IL8_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g>(reinterpret_cast<SCORE*>(pValues));
				IL8 values2 = IL8_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g>(reinterpret_cast<SCORE*>(pValues));
				IL8 scores1 = IL8_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g>(pScores);
				IL8 scores2 = IL8_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g>(pScores);
				IL8_Compare(values1, values2, scores1, scores2);
				IL8_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g>(values1, reinterpret_cast<SCORE*>(pValues));
				IL8_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g>(values2, reinterpret_cast<SCORE*>(pValues));
				IL8_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g>(scores1, pScores);
				IL8_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g>(scores2, pScores);
#elif defined(SORT_IL16)
				IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g>(reinterpret_cast<SCORE*>(pValues));
				IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g>(reinterpret_cast<SCORE*>(pValues));
				IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g>(pScores);
				IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g>(pScores);
				IL16_Compare(values1, values2, scores1, scores2);
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g>(values1, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g>(values2, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g>(scores1, pScores);
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g>(scores2, pScores);
#else
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				comparator<IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
#if defined(SORT_IL8)
				IL8 values1 = IL8_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h>(reinterpret_cast<SCORE*>(pValues));
				IL8 values2 = IL8_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h>(reinterpret_cast<SCORE*>(pValues));
				IL8 scores1 = IL8_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h>(pScores);
				IL8 scores2 = IL8_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h>(pScores);
				IL8_Compare(values1, values2, scores1, scores2);
				IL8_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h>(values1, reinterpret_cast<SCORE*>(pValues));
				IL8_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h>(values2, reinterpret_cast<SCORE*>(pValues));
				IL8_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h>(scores1, pScores);
				IL8_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h>(scores2, pScores);
#elif defined(SORT_IL16)
				IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h>(reinterpret_cast<SCORE*>(pValues));
				IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h>(reinterpret_cast<SCORE*>(pValues));
				IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h>(pScores);
				IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h>(pScores);
				IL16_Compare(values1, values2, scores1, scores2);
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h>(values1, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h>(values2, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h>(scores1, pScores);
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h>(scores2, pScores);
#else
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				comparator<IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
#if defined(SORT_IL16)
				IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j>(reinterpret_cast<SCORE*>(pValues));
				IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j>(reinterpret_cast<SCORE*>(pValues));
				IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j>(pScores);
				IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j>(pScores);
				IL16_Compare(values1, values2, scores1, scores2);
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j>(values1, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j>(values2, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j>(scores1, pScores);
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j>(scores2, pScores);
#else
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
				comparator<IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j>(pValues, pScores);
#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
				/*#if defined(SORT_IL16)
						IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k>(reinterpret_cast<SCORE*>(pValues));
						IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k>(reinterpret_cast<SCORE*>(pValues));
						IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k>(pScores);
						IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k>(pScores);
						IL16_Compare(values1, values2, scores1, scores2);
						IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k>(values1, reinterpret_cast<SCORE*>(pValues));
						IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k>(values2, reinterpret_cast<SCORE*>(pValues));
						IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k>(scores1, pScores);
						IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k>(scores2, pScores);
				#else*/
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
				comparator<IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k>(pValues, pScores);
				//#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
				/*#if defined(SORT_IL16)
						IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l>(reinterpret_cast<SCORE*>(pValues));
						IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l>(reinterpret_cast<SCORE*>(pValues));
						IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l>(pScores);
						IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l>(pScores);
						IL16_Compare(values1, values2, scores1, scores2);
						IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l>(values1, reinterpret_cast<SCORE*>(pValues));
						IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l>(values2, reinterpret_cast<SCORE*>(pValues));
						IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l>(scores1, pScores);
						IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l>(scores2, pScores);
				#else*/
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
				comparator<IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l>(pValues, pScores);
				//#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
				/*#if defined(SORT_IL16)
						IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m>(reinterpret_cast<SCORE*>(pValues));
						IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m>(reinterpret_cast<SCORE*>(pValues));
						IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m>(pScores);
						IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m>(pScores);
						IL16_Compare(values1, values2, scores1, scores2);
						IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m>(values1, reinterpret_cast<SCORE*>(pValues));
						IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m>(values2, reinterpret_cast<SCORE*>(pValues));
						IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m>(scores1, pScores);
						IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m>(scores2, pScores);
				#else*/
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
				comparator<IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m>(pValues, pScores);
				//#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
				/*#if defined(SORT_IL16)
						IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n>(reinterpret_cast<SCORE*>(pValues));
						IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n>(reinterpret_cast<SCORE*>(pValues));
						IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n>(pScores);
						IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n>(pScores);
						IL16_Compare(values1, values2, scores1, scores2);
						IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n>(values1, reinterpret_cast<SCORE*>(pValues));
						IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n>(values2, reinterpret_cast<SCORE*>(pValues));
						IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n>(scores1, pScores);
						IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n>(scores2, pScores);
				#else*/
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
				comparator<IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n>(pValues, pScores);
				//#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
				/*#if defined(SORT_IL16)
						IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n, IDX1o>(reinterpret_cast<SCORE*>(pValues));
						IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n, IDX2o>(reinterpret_cast<SCORE*>(pValues));
						IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n, IDX1o>(pScores);
						IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n, IDX2o>(pScores);
						IL16_Compare(values1, values2, scores1, scores2);
						IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n, IDX1o>(values1, reinterpret_cast<SCORE*>(pValues));
						IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n, IDX2o>(values2, reinterpret_cast<SCORE*>(pValues));
						IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n, IDX1o>(scores1, pScores);
						IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n, IDX2o>(scores2, pScores);
				#else*/
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
				comparator<IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o>(pValues, pScores);
				//#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
				/*#if defined(SORT_IL16)
						IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n, IDX1o, IDX1p>(reinterpret_cast<SCORE*>(pValues));
						IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n, IDX2o, IDX2p>(reinterpret_cast<SCORE*>(pValues));
						IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n, IDX1o, IDX1p>(pScores);
						IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n, IDX2o, IDX2p>(pScores);
						IL16_Compare(values1, values2, scores1, scores2);
						IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n, IDX1o, IDX1p>(values1, reinterpret_cast<SCORE*>(pValues));
						IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n, IDX2o, IDX2p>(values2, reinterpret_cast<SCORE*>(pValues));
						IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n, IDX1o, IDX1p>(scores1, pScores);
						IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n, IDX2o, IDX2p>(scores2, pScores);
				#else*/
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				comparator<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p>(pValues, pScores);
				//#endif
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p, size_t IDX1q, size_t IDX2q>
			constexpr static void comparator(VALUE* pValues, SCORE* pScores)
			{
#if defined(SORT_IL16)
				IL16 values1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n, IDX1o, IDX1p, IDX1q>(reinterpret_cast<SCORE*>(pValues));
				IL16 values2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n, IDX2o, IDX2p, IDX2q>(reinterpret_cast<SCORE*>(pValues));
				IL16 scores1 = IL16_Load<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n, IDX1o, IDX1p, IDX1q>(pScores);
				IL16 scores2 = IL16_Load<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n, IDX2o, IDX2p, IDX2q>(pScores);
				IL16_Compare(values1, values2, scores1, scores2);
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n, IDX1o, IDX1p, IDX1q>(values1, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n, IDX2o, IDX2p, IDX2q>(values2, reinterpret_cast<SCORE*>(pValues));
				IL16_Store<IDX1a, IDX1b, IDX1c, IDX1d, IDX1e, IDX1f, IDX1g, IDX1h, IDX1j, IDX1k, IDX1l, IDX1m, IDX1n, IDX1o, IDX1p, IDX1q>(scores1, pScores);
				IL16_Store<IDX2a, IDX2b, IDX2c, IDX2d, IDX2e, IDX2f, IDX2g, IDX2h, IDX2j, IDX2k, IDX2l, IDX2m, IDX2n, IDX2o, IDX2p, IDX2q>(scores2, pScores);
#else
				comparator<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				comparator<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p, IDX1q, IDX2q>(pValues, pScores);
#endif
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
#if defined(SORT_IL8) && defined(SORT_ILX)
				IL8 values = IL8_Load3((SCORE*)pValues);
				IL8 scores = IL8_Load3((SCORE*)pScores);
				IL8_Compare<1, 2>(values, scores);
				IL8_Compare<0, 2>(values, scores);
				IL8_Compare<0, 1>(values, scores);
				IL8_Store3(values, (SCORE*)pValues);
				IL8_Store3(scores, (SCORE*)pScores);
#elif defined(SORT_IL16) && defined(SORT_ILX)
				IL16 values = IL16_Load3((SCORE*)pValues);
				IL16 scores = IL16_Load3((SCORE*)pScores);
				IL16_Compare<1, 2>(values, scores);
				IL16_Compare<0, 2>(values, scores);
				IL16_Compare<0, 1>(values, scores);
				IL16_Store3(values, (SCORE*)pValues);
				IL16_Store3(scores, (SCORE*)pScores);
#else
				comparator<1, 2>(pValues, pScores);
				comparator<0, 2>(pValues, pScores);
				comparator<0, 1>(pValues, pScores);
#endif
			}

			constexpr static void sort_N4(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(SORT_IL8) && defined(SORT_ILX)
				IL8 values = IL8_Load4((SCORE*)pValues);
				IL8 scores = IL8_Load4((SCORE*)pScores);
				IL8_Compare<0, 1, 2, 3>(values, scores);
				IL8_Compare<0, 2, 1, 3>(values, scores);
				IL8_Compare<1, 2>(values, scores);
				IL8_Store4(values, (SCORE*)pValues);
				IL8_Store4(scores, (SCORE*)pScores);
#elif defined(SORT_IL16) && defined(SORT_ILX)
				IL16 values = IL16_Load4((SCORE*)pValues);
				IL16 scores = IL16_Load4((SCORE*)pScores);
				IL16_Compare<0, 1, 2, 3>(values, scores);
				IL16_Compare<0, 2, 1, 3>(values, scores);
				IL16_Compare<1, 2>(values, scores);
				IL16_Store4(values, (SCORE*)pValues);
				IL16_Store4(scores, (SCORE*)pScores);
#else
				comparator<0, 1, 2, 3>(pValues, pScores); // FIRST 2-Lane
				comparator<0, 2, 1, 3>(pValues, pScores);
				comparator<1, 2>(pValues, pScores);
#endif
			}

			constexpr static void sort_N5(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(SORT_IL8) && defined(SORT_ILX)
				IL8 values = IL8_Load5((SCORE*)pValues);
				IL8 scores = IL8_Load5((SCORE*)pScores);
				IL8_Compare<0, 4, 1, 3>(values, scores);
				IL8_Compare<0, 2>(values, scores);
				IL8_Compare<2, 4, 0, 1>(values, scores);
				IL8_Compare<2, 3, 1, 4>(values, scores);
				IL8_Compare<1, 2, 3, 4>(values, scores);
				IL8_Store5(values, (SCORE*)pValues);
				IL8_Store5(scores, (SCORE*)pScores);
#elif defined(SORT_IL16) && defined(SORT_ILX)
				IL16 values = IL16_Load5((SCORE*)pValues);
				IL16 scores = IL16_Load5((SCORE*)pScores);
				IL16_Compare<0, 4, 1, 3>(values, scores);
				IL16_Compare<0, 2>(values, scores);
				IL16_Compare<2, 4, 0, 1>(values, scores);
				IL16_Compare<2, 3, 1, 4>(values, scores);
				IL16_Compare<1, 2, 3, 4>(values, scores);
				IL16_Store5(values, (SCORE*)pValues);
				IL16_Store5(scores, (SCORE*)pScores);
#else
				comparator<0, 4, 1, 3>(pValues, pScores);
				comparator<0, 2>(pValues, pScores);
				comparator<2, 4, 0, 1>(pValues, pScores);
				comparator<2, 3, 1, 4>(pValues, pScores);
				comparator<1, 2, 3, 4>(pValues, pScores);
#endif
			}

			constexpr static void sort_N6(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(SORT_IL8) && defined(SORT_ILX)
				IL8 values = IL8_Load6((SCORE*)pValues);
				IL8 scores = IL8_Load6((SCORE*)pScores);
				IL8_Compare<0, 4, 1, 5>(values, scores);
				IL8_Compare<0, 2, 1, 3>(values, scores);
				IL8_Compare<2, 4, 3, 5, 0, 1>(values, scores);
				IL8_Compare<2, 3, 4, 5>(values, scores);
				IL8_Compare<1, 4>(values, scores);
				IL8_Compare<1, 2, 3, 4>(values, scores);
				IL8_Store6(values, (SCORE*)pValues);
				IL8_Store6(scores, (SCORE*)pScores);
#elif defined(SORT_IL16) && defined(SORT_ILX)
				IL16 values = IL16_Load6((SCORE*)pValues);
				IL16 scores = IL16_Load6((SCORE*)pScores);
				IL16_Compare<0, 4, 1, 5>(values, scores);
				IL16_Compare<0, 2, 1, 3>(values, scores);
				IL16_Compare<2, 4, 3, 5, 0, 1>(values, scores);
				IL16_Compare<2, 3, 4, 5>(values, scores);
				IL16_Compare<1, 4>(values, scores);
				IL16_Compare<1, 2, 3, 4>(values, scores);
				IL16_Store6(values, (SCORE*)pValues);
				IL16_Store6(scores, (SCORE*)pScores);
#else
				comparator<0, 4, 1, 5>(pValues, pScores);
				comparator<0, 2, 1, 3>(pValues, pScores);
				comparator<2, 4, 3, 5, 0, 1>(pValues, pScores); // FIRST 3-Lane
				comparator<2, 3, 4, 5>(pValues, pScores);
				comparator<1, 4>(pValues, pScores);
				comparator<1, 2, 3, 4 >(pValues, pScores);
#endif
			}

			constexpr static void sort_N7(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(SORT_IL8) && defined(SORT_ILX)
				IL8 values = IL8_Load7((SCORE*)pValues);
				IL8 scores = IL8_Load7((SCORE*)pScores);
				IL8_Compare<0, 4, 1, 5, 2, 6>(values, scores);
				IL8_Compare<0, 2, 1, 3, 4, 6>(values, scores);
				IL8_Compare<2, 4, 3, 5, 0, 1>(values, scores);
				IL8_Compare<2, 3, 4, 5>(values, scores);
				IL8_Compare<1, 4, 3, 6>(values, scores);
				IL8_Compare<1, 2, 3, 4, 5, 6>(values, scores);
				IL8_Store7(values, (SCORE*)pValues);
				IL8_Store7(scores, (SCORE*)pScores);
#elif defined(SORT_IL16) && defined(SORT_ILX)
				IL16 values = IL16_Load7((SCORE*)pValues);
				IL16 scores = IL16_Load7((SCORE*)pScores);
				IL16_Compare<0, 4, 1, 5, 2, 6>(values, scores);
				IL16_Compare<0, 2, 1, 3, 4, 6>(values, scores);
				IL16_Compare<2, 4, 3, 5, 0, 1>(values, scores);
				IL16_Compare<2, 3, 4, 5>(values, scores);
				IL16_Compare<1, 4, 3, 6>(values, scores);
				IL16_Compare<1, 2, 3, 4, 5, 6>(values, scores);
				IL16_Store7(values, (SCORE*)pValues);
				IL16_Store7(scores, (SCORE*)pScores);
#else
				comparator<0, 4, 1, 5, 2, 6>(pValues, pScores);
				comparator<0, 2, 1, 3, 4, 6>(pValues, pScores);
				comparator<2, 4, 3, 5, 0, 1>(pValues, pScores);
				comparator<2, 3, 4, 5>(pValues, pScores);
				comparator<1, 4, 3, 6>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6>(pValues, pScores);
#endif
			}

			constexpr static void sort_N8(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(SORT_IL8) && defined(SORT_ILX)
				IL8 values = IL8_Load8((SCORE*)pValues);
				IL8 scores = IL8_Load8((SCORE*)pScores);
				IL8_Compare<0, 4, 1, 5, 2, 6, 3, 7>(values, scores);
				IL8_Compare<0, 2, 1, 3, 4, 6, 5, 7>(values, scores);
				IL8_Compare<2, 4, 3, 5, 0, 1, 6, 7>(values, scores);
				IL8_Compare<2, 3, 4, 5>(values, scores);
				IL8_Compare<1, 4, 3, 6>(values, scores);
				IL8_Compare<1, 2, 3, 4, 5, 6>(values, scores);
				IL8_Store8(values, (SCORE*)pValues);
				IL8_Store8(scores, (SCORE*)pScores);
#elif defined(SORT_IL16) && defined(SORT_ILX)
				IL16 values = IL16_Load8((SCORE*)pValues);
				IL16 scores = IL16_Load8((SCORE*)pScores);
				IL16_Compare<0, 4, 1, 5, 2, 6, 3, 7>(values, scores);
				IL16_Compare<0, 2, 1, 3, 4, 6, 5, 7>(values, scores);
				IL16_Compare<2, 4, 3, 5, 0, 1, 6, 7>(values, scores);
				IL16_Compare<2, 3, 4, 5>(values, scores);
				IL16_Compare<1, 4, 3, 6>(values, scores);
				IL16_Compare<1, 2, 3, 4, 5, 6>(values, scores);
				IL16_Store8(values, (SCORE*)pValues);
				IL16_Store8(scores, (SCORE*)pScores);
#else
				comparator<0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores); // FIRST 4-Lane
				comparator<0, 2, 1, 3, 4, 6, 5, 7>(pValues, pScores);
				comparator<2, 4, 3, 5, 0, 1, 6, 7>(pValues, pScores);
				comparator<2, 3, 4, 5>(pValues, pScores);
				comparator<1, 4, 3, 6>(pValues, pScores);
				comparator<1, 2, 3, 4, 5, 6>(pValues, pScores);
#endif
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
				detail::sortAlgorithm<VALUE,SCORE>::sortValues(pValues, pScores, length);
		}

	};
}