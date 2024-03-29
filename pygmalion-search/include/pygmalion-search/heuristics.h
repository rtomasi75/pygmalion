namespace pygmalion
{

	template<bool VERBOSE, typename DESCRIPTION_SEARCH, typename INSTANCE>
	class heuristics
	{

	};

	template<typename DESCRIPTION_SEARCH, typename INSTANCE>
	class heuristics<false, DESCRIPTION_SEARCH, INSTANCE> :
		public DESCRIPTION_SEARCH
	{
		friend class heuristics<true, DESCRIPTION_SEARCH, INSTANCE>;
	public:
		using instanceType = INSTANCE;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"
		using movegenFeedback = typename generatorType::movegenFeedback;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		class killerslots
		{
		private:
			std::array<movebitsType, quietKillerMoves> m_QuietKillers;
			std::array<movebitsType, tacticalKillerMoves> m_TacticalKillers;
			size_t m_QuietKillerCount;
			size_t m_TacticalKillerCount;
		public:
			killerslots() noexcept :
				m_QuietKillers{ arrayhelper::make<quietKillerMoves,movebitsType>(movebitsType(0)) },
				m_TacticalKillers{ arrayhelper::make<tacticalKillerMoves,movebitsType>(movebitsType(0)) },
				m_QuietKillerCount{ 0 },
				m_TacticalKillerCount{ 0 }
			{

			}
			~killerslots() = default;
			template<size_t PLAYER>
			PYGMALION_INLINE void quietKillers(const stackType<PLAYER>& stack, quietKillermovesType& killerMoves) const noexcept
			{
				for (size_t i = 0; i < m_QuietKillerCount; i++)
				{
					if (generatorType::isMoveLegal(stack, m_QuietKillers[i]))
						killerMoves.add(m_QuietKillers[i]);
				}
			}
			template<size_t PLAYER>
			PYGMALION_INLINE void tacticalKillers(const stackType<PLAYER>& stack, tacticalKillermovesType& killerMoves) const noexcept
			{
				for (size_t i = 0; i < m_TacticalKillerCount; i++)
				{
					if (generatorType::isMoveLegal(stack, m_TacticalKillers[i]))
						killerMoves.add(m_TacticalKillers[i]);
				}
			}
			template<size_t PLAYER, bool TACTICAL>
			PYGMALION_INLINE void refuted(const stackType<PLAYER>& stack, const movebitsType moveBits, const scoreType score, const scoreType eval) noexcept
			{
				bool contains{ false };
				if constexpr (TACTICAL)
				{
					if constexpr (tacticalKillerMoves > 0)
					{
						const boardType& position{ stack.position() };
						for (size_t i = 0; i < m_TacticalKillerCount; i++)
						{
							if (m_TacticalKillers[i] == moveBits)
							{
								if (i != 0)
								{
									for (size_t k = 0; k < i; k++)
									{
										const size_t idx{ tacticalKillerMoves - k - 1 };
										m_TacticalKillers[idx] = m_TacticalKillers[idx - 1];
									}
									m_TacticalKillers[0] = moveBits;
								}
								contains = true;
							}
						}
						if (!contains)
						{
							for (size_t k = 0; k < tacticalKillerMoves - 1; k++)
							{
								const size_t idx{ tacticalKillerMoves - k - 1 };
								m_TacticalKillers[idx] = m_TacticalKillers[idx - 1];
							}
							m_TacticalKillers[0] = moveBits;
							m_TacticalKillerCount = std::min(m_TacticalKillerCount + 1, tacticalKillerMoves);
						}
					}
				}
				else
				{
					if (generatorType::isMoveTactical(stack, moveBits))
					{
						if constexpr (tacticalKillerMoves > 0)
						{
							const boardType& position{ stack.position() };
							for (size_t i = 0; i < m_TacticalKillerCount; i++)
							{
								if (m_TacticalKillers[i] == moveBits)
								{
									if (i != 0)
									{
										for (size_t k = 0; k < i; k++)
										{
											const size_t idx{ tacticalKillerMoves - k - 1 };
											m_TacticalKillers[idx] = m_TacticalKillers[idx - 1];
										}
										m_TacticalKillers[0] = moveBits;
									}
									contains = true;
								}
							}
							if (!contains)
							{
								for (size_t k = 0; k < tacticalKillerMoves - 1; k++)
								{
									const size_t idx{ tacticalKillerMoves - k - 1 };
									m_TacticalKillers[idx] = m_TacticalKillers[idx - 1];
								}
								m_TacticalKillers[0] = moveBits;
								m_TacticalKillerCount = std::min(m_TacticalKillerCount + 1, tacticalKillerMoves);
							}
						}
					}
					else
					{
						if constexpr (quietKillerMoves > 0)
						{
							const boardType& position{ stack.position() };
							for (size_t i = 0; i < m_QuietKillerCount; i++)
							{
								if (m_QuietKillers[i] == moveBits)
								{
									if (i != 0)
									{
										for (size_t k = 0; k < i; k++)
										{
											const size_t idx{ quietKillerMoves - k - 1 };
											m_QuietKillers[idx] = m_QuietKillers[idx - 1];
										}
										m_QuietKillers[0] = moveBits;
									}
									contains = true;
								}
							}
							if (!contains)
							{
								for (size_t k = 0; k < quietKillerMoves - 1; k++)
								{
									const size_t idx{ quietKillerMoves - k - 1 };
									m_QuietKillers[idx] = m_QuietKillers[idx - 1];
								}
								m_QuietKillers[0] = moveBits;
								m_QuietKillerCount = std::min(m_QuietKillerCount + 1, quietKillerMoves);
							}
						}
					}
				}
			}
			template<size_t PLAYER, bool TACTICAL>
			PYGMALION_INLINE void accepted(const stackType<PLAYER>& stack, const movebitsType moveBits, const scoreType score, const scoreType eval) noexcept
			{
			}
			void clear() noexcept
			{
				m_QuietKillers = arrayhelper::make<quietKillerMoves, movebitsType>(movebitsType(0));
				m_TacticalKillers = arrayhelper::make<tacticalKillerMoves, movebitsType>(movebitsType(0));
				m_QuietKillerCount = 0;
				m_TacticalKillerCount = 0;
			}
		};
		class historybuckets
		{
		private:
			heuristicScore** m_pScoreBuckets;
			std::uint64_t** m_pCounterBuckets;
		public:
			historybuckets() noexcept
			{
				m_pScoreBuckets = new heuristicScore * [generatorType::countMoveBucketTypes()];
				m_pCounterBuckets = new std::uint64_t * [generatorType::countMoveBucketTypes()];
				for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
				{
					m_pScoreBuckets[bucketType] = new heuristicScore[generatorType::countMoveBuckets(bucketType)];
					m_pCounterBuckets[bucketType] = new std::uint64_t[generatorType::countMoveBuckets(bucketType)];
					for (size_t bucket = 0; bucket < generatorType::countMoveBuckets(bucketType); bucket++)
					{
						constexpr const heuristicScore zero{ heuristicScore::zero() };
						m_pScoreBuckets[bucketType][bucket] = zero;
						m_pCounterBuckets[bucketType][bucket] = 0;
					}
				}
			}
			historybuckets(const historybuckets& other) noexcept
			{
				if ((other.m_pCounterBuckets != nullptr) && (other.m_pScoreBuckets != nullptr))
				{
					m_pScoreBuckets = new heuristicScore * [generatorType::countMoveBucketTypes()];
					m_pCounterBuckets = new std::uint64_t * [generatorType::countMoveBucketTypes()];
					for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
					{
						m_pScoreBuckets[bucketType] = new heuristicScore[generatorType::countMoveBuckets(bucketType)];
						m_pCounterBuckets[bucketType] = new std::uint64_t[generatorType::countMoveBuckets(bucketType)];
						for (size_t bucket = 0; bucket < generatorType::countMoveBuckets(bucketType); bucket++)
						{
							m_pScoreBuckets[bucketType][bucket] = other.m_pScoreBuckets[bucketType][bucket];
							m_pCounterBuckets[bucketType][bucket] = other.m_pCounterBuckets[bucketType][bucket];
						}
					}
				}
				else
				{
					m_pScoreBuckets = nullptr;
					m_pCounterBuckets = nullptr;
				}
			}
			historybuckets(historybuckets&& other) noexcept
			{
				m_pScoreBuckets = other.m_pScoreBuckets;
				other.m_pScoreBuckets = nullptr;
				m_pCounterBuckets = other.m_pCounterBuckets;
				other.m_pCounterBuckets = nullptr;
			}
			historybuckets& operator=(historybuckets&& other)
			{
				if (other.m_pScoreBuckets != nullptr)
				{
					if (m_pScoreBuckets != nullptr)
					{
						for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
						{
							delete[] m_pScoreBuckets[bucketType];
						}
						delete[] m_pScoreBuckets;
					}
					m_pScoreBuckets = other.m_pScoreBuckets;
					other.m_pScoreBuckets = nullptr;
				}
				else
				{
					if (m_pScoreBuckets != nullptr)
					{
						for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
						{
							delete[] m_pScoreBuckets[bucketType];
						}
						delete[] m_pScoreBuckets;
					}
					m_pScoreBuckets = nullptr;
				}
				if (other.m_pCounterBuckets != nullptr)
				{
					if (m_pCounterBuckets != nullptr)
					{
						for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
						{
							delete[] m_pCounterBuckets[bucketType];
						}
						delete[] m_pCounterBuckets;
					}
					m_pCounterBuckets = other.m_pCounterBuckets;
					other.m_pCounterBuckets = nullptr;
				}
				else
				{
					if (m_pCounterBuckets != nullptr)
					{
						for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
						{
							delete[] m_pCounterBuckets[bucketType];
						}
						delete[] m_pCounterBuckets;
					}
					m_pCounterBuckets = nullptr;
				}
				return *this;
			}
			historybuckets& operator=(const historybuckets& other) noexcept
			{
				if (other.m_pScoreBuckets != nullptr)
				{
					if (m_pScoreBuckets != nullptr)
					{
						for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
						{
							for (size_t bucket = 0; bucket < generatorType::countMoveBuckets(bucketType); bucket++)
							{
								m_pScoreBuckets[bucketType][bucket] = other.m_pScoreBuckets[bucketType][bucket];
							}
						}
					}
					else
					{
						m_pScoreBuckets = new heuristicScore * [generatorType::countMoveBucketTypes()];
						for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
						{
							m_pScoreBuckets[bucketType] = new heuristicScore[generatorType::countMoveBuckets(bucketType)];
							for (size_t bucket = 0; bucket < generatorType::countMoveBuckets(bucketType); bucket++)
							{
								m_pScoreBuckets[bucketType][bucket] = other.m_pScoreBuckets[bucketType][bucket];
							}
						}
					}
				}
				else
				{
					if (m_pScoreBuckets != nullptr)
					{
						for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
						{
							delete[] m_pScoreBuckets[bucketType];
						}
						delete[] m_pScoreBuckets;
					}
					m_pScoreBuckets = nullptr;
				}
				if (other.m_pCounterBuckets != nullptr)
				{
					if (m_pCounterBuckets != nullptr)
					{
						for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
						{
							for (size_t bucket = 0; bucket < generatorType::countMoveBuckets(bucketType); bucket++)
							{
								m_pCounterBuckets[bucketType][bucket] = other.m_pCounterBuckets[bucketType][bucket];
							}
						}
					}
					else
					{
						m_pCounterBuckets = new std::uint64_t * [generatorType::countMoveBucketTypes()];
						for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
						{
							m_pCounterBuckets[bucketType] = new std::uint64_t[generatorType::countMoveBuckets(bucketType)];
							for (size_t bucket = 0; bucket < generatorType::countMoveBuckets(bucketType); bucket++)
							{
								m_pCounterBuckets[bucketType][bucket] = other.m_pCounterBuckets[bucketType][bucket];
							}
						}
					}
				}
				else
				{
					if (m_pCounterBuckets != nullptr)
					{
						for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
						{
							delete[] m_pCounterBuckets[bucketType];
						}
						delete[] m_pCounterBuckets;
					}
					m_pCounterBuckets = nullptr;
				}
				return *this;
			}
			~historybuckets() noexcept
			{
				if (m_pScoreBuckets != nullptr)
				{
					for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
					{
						delete[] m_pScoreBuckets[bucketType];
					}
					delete[] m_pScoreBuckets;
				}
				if (m_pCounterBuckets != nullptr)
				{
					for (size_t bucketType = 0; bucketType < generatorType::countMoveBucketTypes(); bucketType++)
					{
						delete[] m_pCounterBuckets[bucketType];
					}
					delete[] m_pCounterBuckets;
				}
			}
			template<size_t PLAYER>
			PYGMALION_INLINE void incrementMove(const stackType<PLAYER>& stack, const movebitsType moveBits, const scoreType score, const scoreType eval) noexcept
			{
				if (score.isOpen())
				{
					if (!generatorType::isMoveTactical(stack, moveBits))
					{
						constexpr const size_t countBucketTypes{ generatorType::countMoveBucketTypes() };
						for (size_t bucketType = 0; bucketType < countBucketTypes; bucketType++)
						{
							const size_t bucket{ generatorType::moveBucket(bucketType, stack.position(),moveBits) };
							m_pScoreBuckets[bucketType][bucket] += static_cast<heuristicScore>(score - eval);
							m_pCounterBuckets[bucketType][bucket]++;
						}
					}
				}
			}
			template<size_t PLAYER>
			PYGMALION_INLINE scoreType historyScore(const stackType<PLAYER>& stack, const movebitsType moveBits) noexcept
			{
				PYGMALION_ASSERT(m_pScoreBuckets != nullptr);
				PYGMALION_ASSERT(m_pCounterBuckets != nullptr);
				constexpr const size_t countBucketTypes{ generatorType::countMoveBucketTypes() };
				constexpr const heuristicScore zero{ heuristicScore::zero() };
				heuristicScore score{ zero };
				std::uint64_t counter{ 0 };
				for (size_t bucketType = 0; bucketType < countBucketTypes; bucketType++)
				{
					const size_t bucket{ generatorType::moveBucket(bucketType, stack.position(),moveBits) };
					score += m_pScoreBuckets[bucketType][bucket];
					counter += m_pCounterBuckets[bucketType][bucket];
				}
				constexpr const scoreType minimum{ scoreType::minimum() };
				if (counter == 0)
					return minimum;
				else
					return static_cast<scoreType>(score / counter);
			}
		};
	private:
#if !defined(NDEBUG)
		bool m_IsSearching;
		int m_NodeDepth;
		int m_MoveDepth;
#endif
		profiler m_SearchProfiler;
		std::uintmax_t m_NodeCounter;
		transpositiontable<descriptorSearch> m_TranspositionTable;
		movegenFeedback& m_Feedback;
		std::vector<killerslots> m_KillerSlots;
		std::vector<historybuckets> m_HistoryBuckets;
	protected:
		PYGMALION_INLINE void onBeginSearch() noexcept
		{
			m_NodeCounter = 0;
			m_SearchProfiler.start();
		}
		PYGMALION_INLINE void onEndSearch() noexcept
		{
			m_SearchProfiler.stop();
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void onBeginNode(const stackType<PLAYER>& stack) noexcept
		{
			m_NodeCounter++;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void onEndNodeEarly(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void onEndNodeLate(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER, bool TACTICAL>
		PYGMALION_INLINE void onBeginMove(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
		}
		template<size_t PLAYER, bool TACTICAL>
		PYGMALION_INLINE void onEndMoveRefuted(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const scoreType score) noexcept
		{
		}
		template<size_t PLAYER, bool TACTICAL>
		PYGMALION_INLINE void onEndMoveSilent(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
		}
		template<size_t PLAYER, bool TACTICAL>
		PYGMALION_INLINE void onEndMoveFutile(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
		}
		template<size_t PLAYER, bool TACTICAL>
		PYGMALION_INLINE void onEndMoveDelta(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
		}
		template<size_t PLAYER, bool TACTICAL>
		PYGMALION_INLINE void onEndMoveAccepted(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const scoreType score) noexcept
		{
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void onEndNodeCut(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void onEndNodeLeaf(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void onEndNodeTT(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void onEndNodeNull(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void onEndNodeFutile(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void onEndNodeDelta(const stackType<PLAYER>& stack) noexcept
		{
		}
		PYGMALION_INLINE void sortMoves(movelistType& moves, std::array<scoreType, countMaxGeneratedMoves>& scores, const indexType fromMoveIndex, const indexType fromScoreIndex) noexcept
		{
			const indexType length{ static_cast<indexType>(moves.length() - fromMoveIndex) };
			sort<movebitsType, scoreType>::sortValues(moves.ptr() + static_cast<size_t>(fromMoveIndex), scores.data() + static_cast<size_t>(fromScoreIndex), length);
		}
		PYGMALION_INLINE static int shift(const depthType depthRemaining) noexcept
		{
			return 4 * (1 + static_cast<int>(depthRemaining));
		}
		PYGMALION_INLINE static std::uintmax_t weight(const depthType depthRemaining) noexcept
		{
			return UINTMAX_C(1) << 2 * (1 + static_cast<int>(depthRemaining));
		}
	public:
		void expandToDepth(const size_t depth) noexcept
		{
			if constexpr ((quietKillerMoves > 0) || (tacticalKillerMoves > 0))
			{
				while (depth >= m_KillerSlots.size())
				{
					m_KillerSlots.emplace_back(killerslots());
				}
			}
			if constexpr (heuristicMoves)
			{
				while (depth >= m_HistoryBuckets.size())
				{
					m_HistoryBuckets.emplace_back(historybuckets());
				}
			}
			m_Feedback.expandToDepth(depth);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE scoreType moveScore(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
			constexpr const scoreType minimum{ scoreType::minimum() };
			if constexpr (heuristicMoves)
			{
				if (!generatorType::isMoveTactical(stack, moveBits))
				{
					if (depth >= 2)
					{
						return m_HistoryBuckets[depth - 2].template historyScore<PLAYER>(stack, moveBits);
					}
					else
					{
						return minimum;
					}
				}
				else
					return minimum;
			}
			else
			{
				return minimum;
			}
		}
		template<size_t PLAYER>
		void quietKillers(const stackType<PLAYER>& stack, const size_t depth, quietKillermovesType& killermoves) noexcept
		{
			if constexpr (quietKillerMoves > 0)
			{
				m_KillerSlots[depth].quietKillers(stack, killermoves);
				if constexpr (killerLookBackDistance > 0)
				{
					quietKillermovesType lookBackKillers;
					for (size_t i = 1; i <= killerLookBackDistance; i++)
					{
						const size_t offset{ countPlayers * i };
						if (depth >= offset)
						{
							m_KillerSlots[depth - offset].quietKillers(stack, lookBackKillers);
						}
						else
							break;
					}
					for (size_t i = 0; i < lookBackKillers.length(); i++)
					{
						if (!killermoves.contains(lookBackKillers[i]))
							killermoves.add(lookBackKillers[i]);
					}
				}
			}
		}
		template<size_t PLAYER>
		void tacticalKillers(const stackType<PLAYER>& stack, const size_t depth, tacticalKillermovesType& killermoves) noexcept
		{
			if constexpr (tacticalKillerMoves > 0)
			{
				m_KillerSlots[depth].tacticalKillers(stack, killermoves);
				if constexpr (killerLookBackDistance > 0)
				{
					tacticalKillermovesType lookBackKillers;
					for (size_t i = 1; i <= killerLookBackDistance; i++)
					{
						const size_t offset{ countPlayers * i };
						if (depth >= offset)
						{
							m_KillerSlots[depth - offset].tacticalKillers(stack, lookBackKillers);
						}
						else
							break;
					}
					for (size_t i = 0; i < lookBackKillers.length(); i++)
					{
						if (!killermoves.contains(lookBackKillers[i]))
							killermoves.add(lookBackKillers[i]);
					}
				}
			}
		}
		template<size_t PLAYER>
		void sortMoves(const stackType<PLAYER>& stack, movelistType& moves, const indexType fromMoveIndex, const size_t depth) noexcept
		{
			if constexpr (heuristicMoves)
			{
				std::array<scoreType, countMaxGeneratedMoves> scores;
				for (size_t i = static_cast<size_t>(fromMoveIndex); i < static_cast<size_t>(moves.length()); ++i)
				{
					scores[i - fromMoveIndex] = moveScore(stack, moves[i], depth);
				}
				this->sortMoves(moves, scores, fromMoveIndex, 0);
			}
		}
		PYGMALION_INLINE movegenFeedback& feedback() noexcept
		{
			return m_Feedback;
		}
		PYGMALION_INLINE const movegenFeedback& feedback() const noexcept
		{
			return m_Feedback;
		}
		PYGMALION_INLINE transpositiontable<descriptorSearch>& transpositionTable() noexcept
		{
			return m_TranspositionTable;
		}
		PYGMALION_INLINE const transpositiontable<descriptorSearch>& transpositionTable() const noexcept
		{
			return m_TranspositionTable;
		}
		auto duration() const noexcept
		{
			return m_SearchProfiler.duration();
		}
		auto nodesPerSecond() const noexcept
		{
			return m_SearchProfiler.computeSpeed(static_cast<double>(nodeCount()), "N");
		}
		std::string toString() const noexcept
		{
			std::stringstream sstr;
			sstr << std::setw(9) << parser::valueToString(static_cast<double>(nodeCount()), "N") << " in " << parser::durationToString(duration()) << " => " << nodesPerSecond() << std::endl;
			return sstr.str();
		}
		std::uintmax_t nodeCount() const noexcept
		{
			return m_NodeCounter;
		}
		void clear() noexcept
		{
			if constexpr ((quietKillerMoves > 0) || (tacticalKillerMoves > 0))
				m_KillerSlots.clear();
			if constexpr (heuristicMoves)
				m_HistoryBuckets.clear();
		}
		PYGMALION_INLINE void beginSearch() noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(!m_IsSearching);
			PYGMALION_ASSERT(m_NodeDepth == 0);
			PYGMALION_ASSERT(m_MoveDepth == 0);
			m_IsSearching = true;
#endif
			static_cast<instanceType*>(this)->onBeginSearch();
		}
		PYGMALION_INLINE void endSearch() noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			PYGMALION_ASSERT(m_NodeDepth == 0);
			PYGMALION_ASSERT(m_MoveDepth == 0);
			m_IsSearching = false;
#endif
			static_cast<instanceType*>(this)->onEndSearch();
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void beginNode(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth++;
#endif
			static_cast<instanceType*>(this)->template onBeginNode<PLAYER>(stack);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void endNodeEarly(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeEarly<PLAYER>(stack);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void endNodeLate(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeLate<PLAYER>(stack);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void endNodeTT(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeTT<PLAYER>(stack);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void endNodeNull(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeNull<PLAYER>(stack);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void endNodeFutile(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeFutile<PLAYER>(stack);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void endNodeDelta(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeDelta<PLAYER>(stack);
		}
		template<size_t PLAYER, bool TACTICAL>
		PYGMALION_INLINE void beginMove(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth++;
#endif
			static_cast<instanceType*>(this)->template onBeginMove<PLAYER, TACTICAL>(stack, moveBits, depth);
		}
		template<size_t PLAYER, bool PRUNED, bool TACTICAL>
		PYGMALION_INLINE void endMoveAccepted(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const scoreType score, const scoreType eval, const bool fromStack, const depthType depthRemaining) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth--;
#endif
			if (fromStack)
			{
				if constexpr (!PRUNED)
				{
					if constexpr (TACTICAL)
						stack.tacticalAllMove(m_Feedback, depth, score, eval);
					else
						stack.normalAllMove(m_Feedback, depth, score, eval);
				}
				else
					stack.criticalAllMove(m_Feedback, depth, score, eval);
			}
			if constexpr ((quietKillerMoves > 0) || (tacticalKillerMoves > 0))
			{
				m_KillerSlots[depth].template accepted<PLAYER, TACTICAL>(stack, moveBits, score, eval);
			}
			if constexpr (heuristicMoves)
			{
				m_HistoryBuckets[depth].template incrementMove<PLAYER>(stack, moveBits, score, eval);
			}
			static_cast<instanceType*>(this)->template onEndMoveAccepted<PLAYER, TACTICAL>(stack, moveBits, depth, score);
		}
		template<size_t PLAYER, bool PRUNED, bool TACTICAL>
		PYGMALION_INLINE void endMoveRefuted(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const scoreType score, const scoreType eval, const bool fromStack, const depthType depthRemaining) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth--;
#endif
			if (fromStack)
			{
				if constexpr (!PRUNED)
				{
					if constexpr (TACTICAL)
						stack.tacticalCutMove(m_Feedback, depth, score, eval);
					else
						stack.normalCutMove(m_Feedback, depth, score, eval);
				}
				else
					stack.criticalCutMove(m_Feedback, depth, score, eval);
			}
			if constexpr ((quietKillerMoves > 0) || (tacticalKillerMoves > 0))
			{
				m_KillerSlots[depth].template refuted<PLAYER, TACTICAL>(stack, moveBits, score, eval);
			}
			if constexpr (heuristicMoves)
			{
				m_HistoryBuckets[depth].template incrementMove<PLAYER>(stack, moveBits, score, eval);
			}
			static_cast<instanceType*>(this)->template onEndMoveRefuted<PLAYER, TACTICAL>(stack, moveBits, depth, score);
		}
		template<size_t PLAYER, bool TACTICAL>
		PYGMALION_INLINE void endMoveSilent(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const depthType depthRemaining) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndMoveSilent<PLAYER, TACTICAL>(stack, moveBits, depth);
		}
		template<size_t PLAYER, bool TACTICAL>
		PYGMALION_INLINE void endMoveFutile(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndMoveFutile<PLAYER, TACTICAL>(stack, moveBits, depth);
		}
		template<size_t PLAYER, bool TACTICAL>
		PYGMALION_INLINE void endMoveDelta(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndMoveDelta<PLAYER, TACTICAL>(stack, moveBits, depth);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void endNodeCut(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeCut<PLAYER>(stack);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE void endNodeLeaf(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeLeaf<PLAYER>(stack);
		}
		heuristics(movegenFeedback& feedback) noexcept :
#if !defined(NDEBUG)
			m_IsSearching{ false },
			m_NodeDepth{ 0 },
			m_MoveDepth{ 0 },
#endif
			m_NodeCounter{ 0 },
			m_TranspositionTable{ transpositiontable<descriptorSearch>() },
			m_Feedback{ feedback },
			m_KillerSlots{ std::vector<killerslots>(0) },
			m_HistoryBuckets{ std::vector<historybuckets>(0) }
		{
		}
		~heuristics() noexcept
		{
		}
		void age(const playerType movingPlayer) noexcept
		{
		}
		void unAge(const playerType movingPlayer) noexcept
		{
		}
	};

	template<typename DESCRIPTION_SEARCH, typename INSTANCE>
	class heuristics<true, DESCRIPTION_SEARCH, INSTANCE> :
		public heuristics<false, DESCRIPTION_SEARCH, INSTANCE>
	{
		friend class heuristics<false, DESCRIPTION_SEARCH, INSTANCE>;
	public:
		using baseclassType = heuristics<false, DESCRIPTION_SEARCH, INSTANCE>;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"
		using stackType = typename generatorType::stackType;
		using movegenFeedback = typename generatorType::movegenFeedback;
	private:
		std::uint64_t m_EarlyNodes;
		std::uint64_t m_LateNodes;
		std::uint64_t m_CutNodes;
		std::uint64_t m_LeafNodes;
		std::uint64_t m_TTNodes;
		std::uint64_t m_NullNodes;
		std::uint64_t m_FutileNodes;
		std::uint64_t m_DeltaNodes;
	protected:
		PYGMALION_INLINE void onBeginSearch() noexcept
		{
			baseclassType::onBeginSearch();
			m_EarlyNodes = 0;
			m_LateNodes = 0;
			m_CutNodes = 0;
			m_LeafNodes = 0;
			m_TTNodes = 0;
			m_NullNodes = 0;
			m_FutileNodes = 0;
		}
		PYGMALION_INLINE void onEndNodeEarly(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeEarly(stack);
			m_EarlyNodes++;
		}
		PYGMALION_INLINE void onEndNodeLate(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeLate(stack);
			m_LateNodes++;
		}
		PYGMALION_INLINE void onEndNodeCut(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeCut(stack);
			m_CutNodes++;
		}
		PYGMALION_INLINE void onEndNodeLeaf(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeLeaf(stack);
			m_LeafNodes++;
		}
		PYGMALION_INLINE void onEndNodeTT(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeTT(stack);
			m_TTNodes++;
		}
		PYGMALION_INLINE void onEndNodeNull(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeNull(stack);
			m_NullNodes++;
		}
		PYGMALION_INLINE void onEndNodeFutile(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeFutile(stack);
			m_FutileNodes++;
		}
		PYGMALION_INLINE void onEndNodeDelta(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeDelta(stack);
			m_DeltaNodes++;
		}
	public:
		constexpr std::uint64_t earlyNodeCount() const noexcept
		{
			return m_EarlyNodes;
		}
		constexpr std::uint64_t lateNodeCount() const noexcept
		{
			return m_LateNodes;
		}
		constexpr std::uint64_t cutNodeCount() const noexcept
		{
			return m_CutNodes;
		}
		constexpr std::uint64_t leafNodeCount() const noexcept
		{
			return m_LeafNodes;
		}
		constexpr std::uint64_t TTNodeCount() const noexcept
		{
			return m_TTNodes;
		}
		constexpr std::uint64_t NullNodeCount() const noexcept
		{
			return m_NullNodes;
		}
		constexpr std::uint64_t futileNodeCount() const noexcept
		{
			return m_FutileNodes;
		}
		constexpr std::uint64_t deltaNodeCount() const noexcept
		{
			return m_DeltaNodes;
		}
		std::string toString() const noexcept
		{
			std::stringstream sstr;
			sstr << "early:  " << std::setw(9) << parser::nodesCountToString(earlyNodeCount()) << std::endl;
			sstr << "cut:    " << std::setw(9) << parser::nodesCountToString(cutNodeCount()) << std::endl;
			sstr << "late:   " << std::setw(9) << parser::nodesCountToString(lateNodeCount()) << std::endl;
			sstr << "leaf:   " << std::setw(9) << parser::nodesCountToString(leafNodeCount()) << std::endl;
			sstr << "TT:     " << std::setw(9) << parser::nodesCountToString(TTNodeCount()) << std::endl;
			sstr << "null:   " << std::setw(9) << parser::nodesCountToString(NullNodeCount()) << std::endl;
			sstr << "futile: " << std::setw(9) << parser::nodesCountToString(futileNodeCount()) << std::endl;
			sstr << "delta:  " << std::setw(9) << parser::nodesCountToString(deltaNodeCount()) << std::endl;
			return sstr.str();
		}
		heuristics(movegenFeedback& feedback) noexcept :
			baseclassType(feedback),
			m_EarlyNodes{ 0 },
			m_LateNodes{ 0 },
			m_CutNodes{ 0 },
			m_TTNodes{ 0 },
			m_NullNodes{ 0 },
			m_FutileNodes{ 0 },
			m_DeltaNodes{ 0 },
			m_LeafNodes{ 0 }
		{

		}
		~heuristics() noexcept = default;
	};

}