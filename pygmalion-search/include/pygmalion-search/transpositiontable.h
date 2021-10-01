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
		using stackType = typename generatorType::stackType;
		struct transposition
		{
		public:
			hashType m_Hash;
			flagsType m_BoardFlags;
			playerType m_MovingPlayer;
			scoreType m_Value;
			movebitsType m_Move;
			signatureType m_Signature;
			depthType m_Draft;
			std::uint8_t m_Flags;
		public:
			constexpr transposition() noexcept :
				m_Hash{ hashType(0) },
				m_Value{ scoreType::minimum() },
				m_Flags{ transpositiontable::flags_unused },
				m_Move{ movebitsType(0) },
				m_Draft{ depthType(0) },
				m_MovingPlayer{ playerType(0) },
				m_BoardFlags{ flagsType(0) },
				m_Signature{ signatureType() }
			{
			}
			~transposition() = default;
			constexpr bool isValid(const stackType& stack) const noexcept
			{
				const bool bOk{ ((m_Hash == stack.position().hash()) && (m_MovingPlayer == stack.position().movingPlayer())) && ((m_BoardFlags == stack.position().flags()) && (m_Signature == stack.signature())) };
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
			constexpr hashType hash() const noexcept
			{
				return m_Hash;
			}
			constexpr scoreType value() const noexcept
			{
				return m_Value;
			}
			constexpr movebitsType move() const noexcept
			{
				return m_Move;
			}
			constexpr depthType draft() const noexcept
			{
				return m_Draft;
			}
			constexpr const signatureType& signature() const noexcept
			{
				return m_Signature;
			}
			constexpr flagsType boardFlags() const noexcept
			{
				return m_BoardFlags;
			}
			constexpr playerType movingPlayer() const noexcept
			{
				return m_MovingPlayer;
			}
			constexpr std::uint8_t flags() const noexcept
			{
				return m_Flags;
			}
			constexpr void update(const stackType& stack, const std::uint8_t flags, const scoreType& value, const movebitsType& move)
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
			void reset(const stackType& stack, const scoreType& value, const depthType& draft, const std::uint8_t flags, const movebitsType& move)
			{
				m_Hash = stack.position().hash();
				m_MovingPlayer = stack.position().movingPlayer();
				m_BoardFlags = stack.position().flags();
				m_Signature = stack.signature();
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
		size_t m_BitCount;
		mutable std::uint64_t m_Probes;
		mutable std::uint64_t m_Hits;
		mutable std::uint64_t m_AlphaHits;
		mutable std::uint64_t m_BetaHits;
		mutable std::uint64_t m_ExactHits;
		std::vector<transposition> m_Entry;
		constexpr hashType computeKey(const hashType& hash) const noexcept
		{
			const hashType mask{ (hashType(1) << m_BitCount) - hashType(1) };
			return hash & mask;
		}
	public:
		constexpr void hitAlpha() const noexcept
		{
			m_Hits++;
			m_AlphaHits++;
		}
		constexpr void hitBeta() const noexcept
		{
			m_Hits++;
			m_BetaHits++;
		}
		constexpr void hitExact() const noexcept
		{
			m_Hits++;
			m_ExactHits++;
		}
		constexpr std::uint64_t countHits() const noexcept
		{
			return m_Hits;
		}
		constexpr std::uint64_t countAlphaHits() const noexcept
		{
			return m_AlphaHits;
		}
		constexpr std::uint64_t countBetaHits() const noexcept
		{
			return m_BetaHits;
		}
		constexpr std::uint64_t countExactHits() const noexcept
		{
			return m_ExactHits;
		}
		constexpr std::uint64_t countProbes() const noexcept
		{
			return m_Probes;
		}
		constexpr size_t countUsedEntries() const noexcept
		{
			size_t count{ 0 };
			const size_t n{ (size_t(1) << m_BitCount) * countBuckets };
			for (size_t i = 0; i < n; i++)
			{
				if ((m_Entry[i].flags() & flags_upper) || (m_Entry[i].flags() & flags_lower))
				{
					count++;
				}
			}
			return count;
		}
		constexpr size_t countRangeEntries() const noexcept
		{
			size_t count{ 0 };
			const size_t n{ (size_t(1) << m_BitCount) * countBuckets };
			for (size_t i = 0; i < n; i++)
			{
				if ((m_Entry[i].flags() & flags_upper) && (m_Entry[i].flags() & flags_lower))
				{
					count++;
				}
			}
			return count;
		}
		constexpr size_t countExactEntries() const noexcept
		{
			size_t count{ 0 };
			const size_t n{ (size_t(1) << m_BitCount) * countBuckets };
			for (size_t i = 0; i < n; i++)
			{
				if (m_Entry[i].flags() & flags_exact)
				{
					count++;
				}
			}
			return count;
		}
		constexpr size_t countMoveEntries() const noexcept
		{
			size_t count{ 0 };
			const size_t n{ (size_t(1) << m_BitCount) * countBuckets };
			for (size_t i = 0; i < n; i++)
			{
				if (m_Entry[i].flags() & flags_move)
				{
					count++;
				}
			}
			return count;
		}
		constexpr size_t countUpperBoundEntries() const noexcept
		{
			size_t count{ 0 };
			const size_t n{ (size_t(1) << m_BitCount) * countBuckets };
			for (size_t i = 0; i < n; i++)
			{
				if (m_Entry[i].flags() & flags_upper)
				{
					count++;
				}
			}
			return count;
		}
		constexpr size_t countLowerBoundEntries() const noexcept
		{
			size_t count{ 0 };
			const size_t n{ (size_t(1) << m_BitCount) * countBuckets };
			for (size_t i = 0; i < n; i++)
			{
				if (m_Entry[i].flags() & flags_lower)
				{
					count++;
				}
			}
			return count;
		}
		constexpr size_t bitCount() const noexcept
		{
			return m_BitCount;
		}
		constexpr transpositiontable(const size_t countBits = 21) noexcept :
			m_BitCount{ countBits },
			m_Entry{ (size_t(1) << m_BitCount) * countBuckets },
			m_Probes{ 0 },
			m_Hits{ 0 },
			m_AlphaHits{ 0 },
			m_BetaHits{ 0 },
			m_ExactHits{ 0 }
		{
		}
		constexpr size_t countEntries() const noexcept
		{
			return m_Entry.size();
		}
		constexpr size_t memoryUsed() const noexcept
		{
			return m_Entry.size() * sizeof(transposition);
		}
		constexpr void probeMoves(const stackType& stack, const depthType& depthRemaining, ttmovesType& moves) const noexcept
		{
			if constexpr (countBuckets > 0)
			{
				const hashType i = { computeKey(stack.position().hash()) };
				depthType score[countBuckets];
				for (size_t j = 0; j < countBuckets; j++)
				{
					const size_t index = static_cast<std::uint64_t>(i) * countBuckets + j;
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
		constexpr void probeTacticalMoves(const stackType& stack, ttmovesType& moves) const noexcept
		{
			if constexpr (countBuckets > 0)
			{
				const hashType i = { computeKey(stack.position().hash()) };
				depthType score[countBuckets];
				for (size_t j = 0; j < countBuckets; j++)
				{
					const size_t index = static_cast<std::uint64_t>(i) * countBuckets + j;
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
		constexpr std::uint8_t probe(const stackType& stack, const depthType& depth, scoreType& alpha, scoreType& beta, scoreType& score, movebitsType& move) const noexcept
		{
			bool doNMP{ true };
			m_Probes++;
			if constexpr (UseDeepHits)
			{
				const hashType i = { computeKey(stack.position().hash()) };
				depthType best{ countSearchPlies + 1 };
				size_t bestidx{ 0 };
				for (size_t j = 0; j < countBuckets; j++)
				{
					const size_t index2 = static_cast<std::uint64_t>(i) * countBuckets + j;
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
				const size_t j{ bestidx };
				const size_t index = static_cast<std::uint64_t>(i) * countBuckets + j;
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
				const hashType i = { computeKey(stack.position().hash()) };
				for (size_t j = 0; j < countBuckets; j++)
				{
					const size_t index = static_cast<std::uint64_t>(i) * countBuckets + j;
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
		constexpr void store(const stackType& stack, const depthType& depth, const scoreType& score, const std::uint8_t flags, const movebitsType& move) noexcept
		{
			const hashType i = { computeKey(stack.position().hash()) };
			depthType best{ countSearchPlies + 1 };
			size_t bestidx{ 0 };
			for (size_t j = 0; j < countBuckets; j++)
			{
				const size_t index = static_cast<std::uint64_t>(i) * countBuckets + j;
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
			const size_t index2 = static_cast<std::uint64_t>(i) * countBuckets + bestidx;
			m_Entry[index2].reset(stack, score, depth, flags, move);
		}
		constexpr void prefetch(const stackType& stack) const noexcept
		{
			const hashType i = { computeKey(stack.position().hash()) };
			const size_t index = static_cast<std::uint64_t>(i) * countBuckets;
			memory::prefetchRead(&(m_Entry[index]));
		}
	};
}