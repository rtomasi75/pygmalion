namespace pygmalion
{
	template<typename DESCRIPTION_SEARCH>
	class transpositiontable :
		public DESCRIPTION_SEARCH
	{
	public:
		constexpr static inline bool UseDeepHits{ false };
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		struct transposition
		{
		public:
			hashType m_Hash;
			scoreType m_Value;
			movebitsType m_Move;
			depthType m_Draft;
			std::uint8_t m_Flags;
			constexpr static const scoreType m_Minimum{ scoreType::minimum() };
		public:
			transposition() noexcept :
				m_Hash{ hashType(0) },
				m_Value{ m_Minimum },
				m_Flags{ transpositiontable::flags_unused },
				m_Move{ movebitsType(0) },
				m_Draft{ depthType(0) }
			{
			}
			~transposition() = default;
			template<size_t PLAYER>
			bool isValid(const stackType<PLAYER>& stack) const noexcept
			{
				const bool bOk{ m_Hash == stack.position().hash() };
				if (bOk)
				{
					if (m_Flags & transpositiontable::flags_move)
					{
						return generatorType::isMoveLegal(stack, m_Move);
					}
					else
						return true;
				}
				else
					return false;
			}
			hashType hash() const noexcept
			{
				return m_Hash;
			}
			scoreType value() const noexcept
			{
				return m_Value;
			}
			movebitsType move() const noexcept
			{
				return m_Move;
			}
			depthType draft() const noexcept
			{
				return m_Draft;
			}
			std::uint8_t flags() const noexcept
			{
				return m_Flags;
			}
			template<size_t PLAYER>
			void update(const stackType<PLAYER>& stack, const std::uint8_t flags, const scoreType value, const movebitsType move)
			{
				if (flags & transpositiontable::flags_lower)
				{
					m_Flags |= transpositiontable::flags_lower;
					m_Value = scoreType::max(m_Value, value);
				}
				if (flags & transpositiontable::flags_exact)
				{
					m_Flags |= transpositiontable::flags_exact;
					m_Value = value;
				}
				if (flags & transpositiontable::flags_upper)
				{
					m_Flags |= transpositiontable::flags_upper;
					m_Value = scoreType::max(m_Value, value);
				}
				if (flags & transpositiontable::flags_move)
				{
					m_Move = move;
					m_Flags |= transpositiontable::flags_move;
				}
			}
			template<size_t PLAYER>
			void reset(const stackType<PLAYER>& stack, const scoreType value, const depthType draft, const std::uint8_t flags, const movebitsType move)
			{
				m_Hash = stack.position().hash();
				m_Draft = draft;
				m_Flags = flags_unused;
				if (flags & transpositiontable::flags_lower)
				{
					m_Flags |= transpositiontable::flags_lower;
					m_Value = value;
				}
				if (flags & transpositiontable::flags_upper)
				{
					m_Flags |= transpositiontable::flags_upper;
					m_Value = value;
				}
				if (flags & transpositiontable::flags_exact)
				{
					m_Flags |= transpositiontable::flags_exact;
					m_Value = value;
				}
				if (flags & transpositiontable::flags_move)
				{
					m_Move = move;
					m_Flags |= transpositiontable::flags_move;
				}
			}
		};
		constexpr static inline std::uint8_t flags_unused{ 0 };
		constexpr static inline std::uint8_t flags_upper{ 1 };
		constexpr static inline std::uint8_t flags_lower{ 2 };
		constexpr static inline std::uint8_t flags_exact{ 4 };
		constexpr static inline std::uint8_t flags_move{ 8 };
		constexpr static inline std::uint8_t flags_return{ 16 };
		constexpr static inline std::uint8_t flags_noNMP{ 32 };
		constexpr static inline std::uint8_t flags_hit{ flags_upper | flags_lower | flags_exact };
		constexpr static inline size_t countBuckets{ searchTranspositionTableBucketCount };
	private:
		size_t m_EntryCount;
		uint_t<128, false> m_WideEntryCount;
		mutable std::uint64_t m_Probes;
		mutable std::uint64_t m_Hits;
		mutable std::uint64_t m_AlphaHits;
		mutable std::uint64_t m_BetaHits;
		mutable std::uint64_t m_ExactHits;
		std::vector<transposition> m_Entry;
		size_t computeMaxEntries() const noexcept
		{
			return static_cast<size_t>(std::min(static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max() / (sizeof(transposition) * countBuckets)), ((UINT64_C(1) << std::min(static_cast<size_t>(63), countHashBits)) / (sizeof(transposition) * countBuckets))));
		}
		size_t computeIndex(const hashType& hash) const noexcept
		{
			if constexpr ((countHashBits > 32) && (static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max()) >= UINT64_C(0x100000000)))
			{
				if constexpr (uint_t<128, false>::countWords <= 2)
				{
					const uint_t<128, false> wideHash{ static_cast<uint_t<128,false>>(hash) };
					const uint_t<128, false> wideIndex{ wideHash * m_WideEntryCount };
					const std::uint64_t index{ static_cast<std::uint64_t>(wideIndex.extractBits<64,64>()) };
					return static_cast<size_t>(index);
				}
				else
				{
					if constexpr ((sizeof(long double) * CHAR_BIT >= 80) && (LDBL_MANT_DIG == 64) && (sizeof(std::uint64_t) < sizeof(long double)))
					{
						const long double floatHash{ static_cast<long double>(static_cast<std::uint64_t>(hash)) };
						const long double floatIndex{ static_cast<long double>(m_EntryCount) * floatHash };
						std::uint64_t index;
						memcpy(&index, &floatIndex, sizeof(std::uint64_t));
						return static_cast<size_t>(index);
					}
					else
					{
						const uint_t<128, false> wideHash{ static_cast<uint_t<128,false>>(hash) };
						const uint_t<128, false> wideIndex{ wideHash * m_WideEntryCount };
						const std::uint64_t index{ static_cast<std::uint64_t>(wideIndex.extractBits<64,64>()) };
						return static_cast<size_t>(index);
					}
				}
			}
			else
			{
				const std::uint64_t wideHash{ static_cast<std::uint64_t>(hash) & UINT64_C(0xffffffff) };
				const std::uint64_t wideIndex{ wideHash * static_cast<std::uint64_t>(m_EntryCount) };
				const std::uint64_t index{ wideIndex >> 32 };
				return static_cast<size_t>(index);
			}
		}
	public:
		void hitAlpha() const noexcept
		{
			m_Hits++;
			m_AlphaHits++;
		}
		void hitBeta() const noexcept
		{
			m_Hits++;
			m_BetaHits++;
		}
		void hitExact() const noexcept
		{
			m_Hits++;
			m_ExactHits++;
		}
		std::uint64_t countHits() const noexcept
		{
			return m_Hits;
		}
		std::uint64_t countAlphaHits() const noexcept
		{
			return m_AlphaHits;
		}
		std::uint64_t countBetaHits() const noexcept
		{
			return m_BetaHits;
		}
		std::uint64_t countExactHits() const noexcept
		{
			return m_ExactHits;
		}
		std::uint64_t countProbes() const noexcept
		{
			return m_Probes;
		}
		size_t countUsedEntries() const noexcept
		{
			size_t count{ 0 };
			const size_t n{ m_EntryCount * countBuckets };
			for (size_t i = 0; i < n; i++)
			{
				if ((m_Entry[i].flags() & flags_upper) || (m_Entry[i].flags() & flags_lower))
				{
					count++;
				}
			}
			return count;
		}
		size_t countRangeEntries() const noexcept
		{
			size_t count{ 0 };
			const size_t n{ m_EntryCount * countBuckets };
			for (size_t i = 0; i < n; i++)
			{
				if ((m_Entry[i].flags() & flags_upper) && (m_Entry[i].flags() & flags_lower))
				{
					count++;
				}
			}
			return count;
		}
		size_t countExactEntries() const noexcept
		{
			size_t count{ 0 };
			const size_t n{ m_EntryCount * countBuckets };
			for (size_t i = 0; i < n; i++)
			{
				if (m_Entry[i].flags() & flags_exact)
				{
					count++;
				}
			}
			return count;
		}
		size_t countMoveEntries() const noexcept
		{
			size_t count{ 0 };
			const size_t n{ m_EntryCount * countBuckets };
			for (size_t i = 0; i < n; i++)
			{
				if (m_Entry[i].flags() & flags_move)
				{
					count++;
				}
			}
			return count;
		}
		size_t countUpperBoundEntries() const noexcept
		{
			size_t count{ 0 };
			const size_t n{ m_EntryCount * countBuckets };
			for (size_t i = 0; i < n; i++)
			{
				if (m_Entry[i].flags() & flags_upper)
				{
					count++;
				}
			}
			return count;
		}
		size_t countLowerBoundEntries() const noexcept
		{
			size_t count{ 0 };
			const size_t n{ m_EntryCount * countBuckets };
			for (size_t i = 0; i < n; i++)
			{
				if (m_Entry[i].flags() & flags_lower)
				{
					count++;
				}
			}
			return count;
		}
		transpositiontable(const size_t sizeInBytes = 128 * 1024 * 1024) noexcept :
			m_EntryCount{ std::min(computeMaxEntries(),sizeInBytes / (sizeof(transposition) * countBuckets)) },
			m_Entry{ m_EntryCount * countBuckets },
			m_WideEntryCount{ static_cast<uint_t<128,false>>(static_cast<uint_t<64,false>>(static_cast<std::uint64_t>(m_EntryCount))) },
			m_Probes{ 0 },
			m_Hits{ 0 },
			m_AlphaHits{ 0 },
			m_BetaHits{ 0 },
			m_ExactHits{ 0 }
		{
		}
		size_t countEntries() const noexcept
		{
			return m_EntryCount;
		}
		size_t memoryUsed() const noexcept
		{
			return m_EntryCount * sizeof(transposition) * countBuckets;
		}
		template<size_t PLAYER>
		void probeMoves(const stackType<PLAYER>& stack, const depthType depthRemaining, ttmovesType& moves) const noexcept
		{
			if constexpr (countBuckets > 0)
			{
				const size_t idx{ computeIndex(stack.position().hash()) };
				depthType score[countBuckets];
				const size_t base{ idx * countBuckets };
				for (size_t j = 0; j < countBuckets; j++)
				{
					const size_t index{ base + j };
					if (m_Entry[index].isValid(stack))
					{
						if (m_Entry[index].flags() & flags_move)
						{
							if (!moves.contains(m_Entry[index].move()))
							{
								score[moves.length()] = -std::abs(m_Entry[index].draft() - depthRemaining);
								moves.add(m_Entry[index].move());
							}
						}
					}
				}
				sort<movebitsType, depthType>::sortValues(moves.ptr(), &score[0], moves.length());
			}
		}
		template<size_t PLAYER>
		void probeTacticalMoves(const stackType<PLAYER>& stack, ttmovesType& moves) const noexcept
		{
			if constexpr (countBuckets > 0)
			{
				const size_t idx{ computeIndex(stack.position().hash()) };
				depthType score[countBuckets];
				const size_t base{ idx * countBuckets };
				for (size_t j = 0; j < countBuckets; j++)
				{
					const size_t index{ base + j };
					if (m_Entry[index].isValid(stack))
					{
						if (m_Entry[index].flags() & flags_move)
						{
							if (generatorType::isMoveTactical(stack, m_Entry[index].move()))
							{
								if (!moves.contains(m_Entry[index].move()))
								{
									score[moves.length()] = -std::abs(m_Entry[index].draft() + 1);
									moves.add(m_Entry[index].move());
								}
							}
						}
					}
				}
				sort<movebitsType, depthType>::sortValues(moves.ptr(), &score[0], moves.length());
			}
		}
		template<size_t PLAYER>
		std::uint8_t probe(const stackType<PLAYER>& stack, const depthType depth, scoreType& alpha, scoreType& beta, scoreType& score, movebitsType& move) const noexcept
		{
			bool doNMP{ true };
			m_Probes++;
			if constexpr (UseDeepHits)
			{
				const size_t idx{ computeIndex(stack.position().hash()) };
				depthType best{ countSearchPlies + 1 };
				size_t bestidx{ 0 };
				const size_t base{ idx * countBuckets };
				for (size_t j = 0; j < countBuckets; j++)
				{
					const size_t index2 = base + j;
					if (m_Entry[index2].draft() < best)
					{
						best = m_Entry[index2].draft();
						bestidx = j;
					}
					if ((depth == m_Entry[index2].draft()) && m_Entry[index2].isValid(stack))
					{
						bestidx = j;
						break;
					}
				}
				const size_t index = base + bestidx;
				if (m_Entry[index].isValid(stack))
				{
					if (m_Entry[index].draft() >= depth)
					{
						if (m_Entry[index].flags() != flags_unused)
						{
							if (m_Entry[index].value() > alpha)
							{
								if (m_Entry[index].value() >= beta)
								{
									score = m_Entry[index].value();
									hitBeta();
									if (m_Entry[index].flags() & flags_move)
									{
										move = m_Entry[index].move();
										return flags_lower | flags_move | flags_return;
									}
									return flags_lower | flags_return;
								}
								score = m_Entry[index].value();
								if (m_Entry[index].flags() & flags_exact)
								{
									hitExact();
									if (m_Entry[index].flags() & flags_move)
									{
										move = m_Entry[index].move();
										return flags_exact | flags_move | flags_return;
									}
									return flags_exact | flags_return;
								}
								hitAlpha();
								alpha = m_Entry[index].value();
								if (m_Entry[index].flags() & flags_move)
								{
									move = m_Entry[index].move();
									return flags_upper | flags_move;
								}
								return flags_upper;
							}
						}
					}
					else
					{
						if (m_Entry[index].value() > alpha)
							doNMP = false;
					}
				}
			}
			else
			{
				const size_t idx{ computeIndex(stack.position().hash()) };
				const size_t base{ idx * countBuckets };
				for (size_t j = 0; j < countBuckets; j++)
				{
					const size_t index = base + j;
					if (m_Entry[index].isValid(stack))
					{
						if (m_Entry[index].draft() == depth)
						{
							if (m_Entry[index].flags() != flags_unused)
							{
								if (m_Entry[index].value() > alpha)
								{
									if (m_Entry[index].value() >= beta)
									{
										score = m_Entry[index].value();
										hitBeta();
										if (m_Entry[index].flags() & flags_move)
										{
											move = m_Entry[index].move();
											return flags_lower | flags_move | flags_return;
										}
										return flags_lower | flags_return;
									}
									score = m_Entry[index].value();
									if (m_Entry[index].flags() & flags_exact)
									{
										hitExact();
										if (m_Entry[index].flags() & flags_move)
										{
											move = m_Entry[index].move();
											return flags_exact | flags_move | flags_return;
										}
										return flags_exact | flags_return;
									}
									hitAlpha();
									alpha = m_Entry[index].value();
									if (m_Entry[index].flags() & flags_move)
									{
										move = m_Entry[index].move();
										return flags_upper | flags_move;
									}
									return flags_upper;
								}
							}
						}
						else
						{
							if (m_Entry[index].value() < beta)
								doNMP = false;
						}
					}
				}
			}
			return doNMP ? flags_unused : flags_noNMP;
		}
		template<size_t PLAYER>
		void store(const stackType<PLAYER>& stack, const depthType depth, const scoreType score, const std::uint8_t flags, const movebitsType move) noexcept
		{
			const size_t idx{ computeIndex(stack.position().hash()) };
			depthType best{ countSearchPlies + 1 };
			size_t bestidx{ 0 };
			const size_t base{ idx * countBuckets };
			for (size_t j = 0; j < countBuckets; j++)
			{
				const size_t index = base + j;
				if (m_Entry[index].draft() < best)
				{
					best = m_Entry[index].draft();
					bestidx = j;
				}
				if ((depth == m_Entry[index].draft()) && m_Entry[index].isValid(stack))
				{
					m_Entry[index].update(stack, flags, score, move);
					return;
				}
			}
			const size_t index2 = base + bestidx;
			m_Entry[index2].reset(stack, score, depth, flags, move);
		}
		template<size_t PLAYER>
		void prefetch(const stackType<PLAYER>& stack) const noexcept
		{
			const size_t idx{ computeIndex(stack.position().hash()) };
			const size_t base{ idx * countBuckets };
			memory::prefetchRead(&(m_Entry[base]));
		}
	};
}