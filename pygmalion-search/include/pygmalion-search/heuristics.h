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
			template<size_t PLAYER, int QSPHASE>
			PYGMALION_INLINE void tacticalKillers(const stackType<PLAYER>& stack, tacticalKillermovesType& killerMoves) const noexcept
			{
				for (size_t i = 0; i < m_TacticalKillerCount; i++)
				{
					if constexpr (QSPHASE == 0)
					{
						if (generatorType::isMoveLegal(stack, m_TacticalKillers[i]))
							killerMoves.add(m_TacticalKillers[i]);
					}
					else if constexpr (QSPHASE == 1)
					{
						if (generatorType::isMoveTactical(stack, m_TacticalKillers[i]))
						{
							if (generatorType::isMoveLegal(stack, m_TacticalKillers[i]))
								killerMoves.add(m_TacticalKillers[i]);
						}
					}
					else
					{
						constexpr const scoreType zero{ scoreType::zero() };
						if (generatorType::isMoveLegal(stack, m_TacticalKillers[i]))
							if (generatorType::isMoveTactical(stack, m_TacticalKillers[i]) && (evaluatorType::staticMoveScore(stack.position(), m_TacticalKillers[i]) > zero))
								killerMoves.add(m_TacticalKillers[i]);
					}
				}
			}
			template<size_t PLAYER, int QSPHASE>
			PYGMALION_INLINE void refuted(const stackType<PLAYER>& stack, const movebitsType moveBits) noexcept
			{
				bool contains{ false };
				if constexpr (QSPHASE >= 0)
				{
					if constexpr (QSPHASE < 2)
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
			template<size_t PLAYER, int QSPHASE>
			PYGMALION_INLINE void accepted(const stackType<PLAYER>& stack, const movebitsType moveBits) noexcept
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
	private:
#if !defined(NDEBUG)
		bool m_IsSearching;
		int m_NodeDepth;
		int m_MoveDepth;
#endif
		profiler m_SearchProfiler;
		nodecounterType m_NodeCounter;
		transpositiontable<descriptorSearch> m_TranspositionTable;
		movegenFeedback& m_Feedback;
		std::vector<killerslots> m_KillerSlots;
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
		template<size_t PLAYER, int QSPHASE>
		PYGMALION_INLINE void onBeginMove(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
		}
		template<size_t PLAYER, int QSPHASE>
		PYGMALION_INLINE void onEndMoveRefuted(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
		}
		template<size_t PLAYER, int QSPHASE>
		PYGMALION_INLINE void onEndMoveSilent(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
		}
		template<size_t PLAYER, int QSPHASE>
		PYGMALION_INLINE void onEndMoveFutile(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
		}
		template<size_t PLAYER, int QSPHASE>
		PYGMALION_INLINE void onEndMoveDelta(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
		}
		template<size_t PLAYER, int QSPHASE>
		PYGMALION_INLINE void onEndMoveAccepted(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
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
		}
		template<size_t PLAYER>
		PYGMALION_INLINE scoreType staticMoveScore(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
			return evaluatorType::staticMoveScore(stack.position(), moveBits);
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
		template<size_t PLAYER, int QSPHASE>
		void tacticalKillers(const stackType<PLAYER>& stack, const size_t depth, tacticalKillermovesType& killermoves) noexcept
		{
			if constexpr (tacticalKillerMoves > 0)
			{
				m_KillerSlots[depth].template tacticalKillers<PLAYER, QSPHASE>(stack, killermoves);
				if constexpr (killerLookBackDistance > 0)
				{
					tacticalKillermovesType lookBackKillers;
					for (size_t i = 1; i <= killerLookBackDistance; i++)
					{
						const size_t offset{ countPlayers * i };
						if (depth >= offset)
						{
							m_KillerSlots[depth - offset].template tacticalKillers<PLAYER, QSPHASE>(stack, lookBackKillers);
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
		nodecounterType nodeCount() const noexcept
		{
			return m_NodeCounter;
		}
		void clear() noexcept
		{
			if constexpr ((quietKillerMoves > 0) || (tacticalKillerMoves > 0))
				m_KillerSlots.clear();
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
		template<size_t PLAYER, int QSPHASE>
		PYGMALION_INLINE nodecounterType beginMove(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth++;
#endif
			static_cast<instanceType*>(this)->template onBeginMove<PLAYER, QSPHASE>(stack, moveBits, depth);
			return m_NodeCounter;
		}
		template<size_t PLAYER, bool PRUNED, int QSPHASE>
		PYGMALION_INLINE nodecounterType endMoveAccepted(const nodecounterType nodeCount, const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const depthType depthRemaining) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth--;
#endif
			if constexpr ((quietKillerMoves > 0) || (tacticalKillerMoves > 0))
			{
				m_KillerSlots[depth].template accepted<PLAYER, QSPHASE>(stack, moveBits);
			}
			static_cast<instanceType*>(this)->template onEndMoveAccepted<PLAYER, QSPHASE>(stack, moveBits, depth);
			return m_NodeCounter - nodeCount;
		}
		template<size_t PLAYER, bool PRUNED, int QSPHASE>
		PYGMALION_INLINE nodecounterType endMoveRefuted(const nodecounterType nodeCount, const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const depthType depthRemaining) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth--;
#endif
			if constexpr ((quietKillerMoves > 0) || (tacticalKillerMoves > 0))
			{
				m_KillerSlots[depth].template refuted<PLAYER, QSPHASE>(stack, moveBits);
			}
			static_cast<instanceType*>(this)->template onEndMoveRefuted<PLAYER, QSPHASE>(stack, moveBits, depth);
			return m_NodeCounter - nodeCount;
		}
		template<size_t PLAYER, int QSPHASE>
		PYGMALION_INLINE nodecounterType endMoveSilent(const nodecounterType nodeCount, const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const depthType depthRemaining) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndMoveSilent<PLAYER, QSPHASE>(stack, moveBits, depth);
			return m_NodeCounter - nodeCount;
		}
		template<size_t PLAYER, int QSPHASE>
		PYGMALION_INLINE void endMoveFutile(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndMoveFutile<PLAYER, QSPHASE>(stack, moveBits, depth);
		}
		template<size_t PLAYER, int QSPHASE>
		PYGMALION_INLINE void endMoveDelta(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndMoveDelta<PLAYER, QSPHASE>(stack, moveBits, depth);
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
			m_KillerSlots{ std::vector<killerslots>(0) }
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
		nodecounterType m_EarlyNodes;
		nodecounterType m_LateNodes;
		nodecounterType m_CutNodes;
		nodecounterType m_LeafNodes;
		nodecounterType m_TTNodes;
		nodecounterType m_NullNodes;
		nodecounterType m_FutileNodes;
		nodecounterType m_DeltaNodes;
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
		constexpr nodecounterType earlyNodeCount() const noexcept
		{
			return m_EarlyNodes;
		}
		constexpr nodecounterType lateNodeCount() const noexcept
		{
			return m_LateNodes;
		}
		constexpr nodecounterType cutNodeCount() const noexcept
		{
			return m_CutNodes;
		}
		constexpr nodecounterType leafNodeCount() const noexcept
		{
			return m_LeafNodes;
		}
		constexpr nodecounterType TTNodeCount() const noexcept
		{
			return m_TTNodes;
		}
		constexpr nodecounterType NullNodeCount() const noexcept
		{
			return m_NullNodes;
		}
		constexpr nodecounterType futileNodeCount() const noexcept
		{
			return m_FutileNodes;
		}
		constexpr nodecounterType deltaNodeCount() const noexcept
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