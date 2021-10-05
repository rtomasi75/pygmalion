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
			std::array<movebitsType, killerMoves> m_Killers;
			std::array<movebitsType, killerMoves> m_TacticalKillers;
			size_t m_KillerCount;
			size_t m_TacticalKillerCount;
		public:
			constexpr killerslots() noexcept :
				m_Killers{ arrayhelper::make<killerMoves,movebitsType>(movebitsType(0)) },
				m_TacticalKillers{ arrayhelper::make<killerMoves,movebitsType>(movebitsType(0)) },
				m_KillerCount{ 0 },
				m_TacticalKillerCount{ 0 }
			{

			}
			template<size_t PLAYER>
			constexpr void killers(const stackType<PLAYER>& stack, killermovesType& killerMoves) const noexcept
			{
				for (size_t i = 0; i < m_KillerCount; i++)
				{
					if (generatorType::isMoveLegal(stack, m_Killers[i]))
						killerMoves.add(m_Killers[i]);
				}
			}
			template<size_t PLAYER>
			constexpr void tacticalKillers(const stackType<PLAYER>& stack, killermovesType& killerMoves) const noexcept
			{
				for (size_t i = 0; i < m_TacticalKillerCount; i++)
				{
					if (generatorType::isMoveLegal(stack, m_TacticalKillers[i]))
						killerMoves.add(m_TacticalKillers[i]);
				}
			}
			template<size_t PLAYER, bool TACTICAL>
			constexpr void refuted(const stackType<PLAYER>& stack, const movebitsType moveBits, const scoreType score, const scoreType eval) noexcept
			{
				bool contains{ false };
				if constexpr (TACTICAL)
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
									const size_t idx{ killerMoves - k - 1 };
									m_TacticalKillers[idx] = m_TacticalKillers[idx - 1];
								}
								m_TacticalKillers[0] = moveBits;
							}
							contains = true;
						}
					}
					if (!contains)
					{
						if constexpr (killerMoves > 0)
						{
							for (size_t k = 0; k < killerMoves - 1; k++)
							{
								const size_t idx{ killerMoves - k - 1 };
								m_TacticalKillers[idx] = m_TacticalKillers[idx - 1];
							}
							m_TacticalKillers[0] = moveBits;
							m_TacticalKillerCount = std::min(m_TacticalKillerCount + 1, killerMoves);
						}
					}
				}
				else
				{
					const boardType& position{ stack.position() };
					if (generatorType::isMoveTactical(stack, moveBits))
					{
						for (size_t i = 0; i < m_TacticalKillerCount; i++)
						{
							if (m_TacticalKillers[i] == moveBits)
							{
								if (i != 0)
								{
									for (size_t k = 0; k < i; k++)
									{
										const size_t idx{ killerMoves - k - 1 };
										m_TacticalKillers[idx] = m_TacticalKillers[idx - 1];
									}
									m_TacticalKillers[0] = moveBits;
								}
								contains = true;
							}
						}
						if (!contains)
						{
							if constexpr (killerMoves > 0)
							{
								for (size_t k = 0; k < killerMoves - 1; k++)
								{
									const size_t idx{ killerMoves - k - 1 };
									m_TacticalKillers[idx] = m_TacticalKillers[idx - 1];
								}
								m_TacticalKillers[0] = moveBits;
								m_TacticalKillerCount = std::min(m_TacticalKillerCount + 1, killerMoves);
							}
						}
					}
					else
					{
						for (size_t i = 0; i < m_KillerCount; i++)
						{
							if (m_Killers[i] == moveBits)
							{
								if (i != 0)
								{
									for (size_t k = 0; k < i; k++)
									{
										const size_t idx{ killerMoves - k - 1 };
										m_Killers[idx] = m_Killers[idx - 1];
									}
									m_Killers[0] = moveBits;
								}
								contains = true;
							}
						}
						if (!contains)
						{
							if constexpr (killerMoves > 0)
							{
								for (size_t k = 0; k < killerMoves - 1; k++)
								{
									const size_t idx{ killerMoves - k - 1 };
									m_Killers[idx] = m_Killers[idx - 1];
								}
								m_Killers[0] = moveBits;
								m_KillerCount = std::min(m_KillerCount + 1, killerMoves);
							}
						}
					}
				}
			}
			template<size_t PLAYER, bool TACTICAL>
			constexpr void accepted(const stackType<PLAYER>& stack, const movebitsType moveBits, const scoreType score, const scoreType eval) noexcept
			{
			}
			constexpr void clear() noexcept
			{
				m_Killers = arrayhelper::make<killerMoves, movebitsType>(movebitsType(0));
				m_TacticalKillers = arrayhelper::make<killerMoves, movebitsType>(movebitsType(0));
				m_KillerCount = 0;
				m_TacticalKillerCount = 0;
			}
		};
	private:
#if !defined(NDEBUG)
		bool m_IsSearching;
		int m_NodeDepth;
		int m_MoveDepth;
#endif
		std::array < std::array<std::uintmax_t, generatorType::countMoveBuckets()>, countPlayers> m_CutCounter;
		std::array < std::array<std::uintmax_t, generatorType::countMoveBuckets()>, countPlayers> m_TotalCounter;
		profiler m_SearchProfiler;
		std::uintmax_t m_NodeCounter;
		transpositiontable<descriptorSearch> m_TranspositionTable;
		movegenFeedback& m_Feedback;
		std::vector<killerslots> m_KillerSlots;
	protected:
		void onBeginSearch() noexcept
		{
			m_NodeCounter = 0;
			m_SearchProfiler.start();
		}
		void onEndSearch() noexcept
		{
			m_SearchProfiler.stop();
		}
		template<size_t PLAYER>
		void onBeginNode(const stackType<PLAYER>& stack) noexcept
		{
			m_NodeCounter++;
		}
		template<size_t PLAYER>
		void onEndNodeEarly(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER>
		void onEndNodeLate(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER, bool TACTICAL>
		void onBeginMove(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
		}
		template<size_t PLAYER, bool TACTICAL>
		void onEndMoveRefuted(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const scoreType score) noexcept
		{
		}
		template<size_t PLAYER, bool TACTICAL>
		void onEndMoveSilent(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
		}
		template<size_t PLAYER, bool TACTICAL>
		void onEndMoveFutile(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
		}
		template<size_t PLAYER, bool TACTICAL>
		void onEndMoveAccepted(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const scoreType score) noexcept
		{
		}
		template<size_t PLAYER>
		void onEndNodeCut(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER>
		void onEndNodeLeaf(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER>
		void onEndNodeTT(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER>
		void onEndNodeNull(const stackType<PLAYER>& stack) noexcept
		{
		}
		template<size_t PLAYER>
		void onEndNodeFutile(const stackType<PLAYER>& stack) noexcept
		{
		}
		void sortMoves(movelistType& moves, std::array<scoreType, countMaxGeneratedMoves>& scores, const indexType fromMoveIndex, const indexType fromScoreIndex) noexcept
		{
			const indexType length{ static_cast<indexType>(moves.length() - fromMoveIndex) };
			sort<movebitsType, scoreType>::sortValues(moves.ptr() + static_cast<size_t>(fromMoveIndex), scores.data() + static_cast<size_t>(fromScoreIndex), length);
		}
		constexpr void expandToDepth(const size_t depth) noexcept
		{
			while (depth >= m_KillerSlots.size())
			{
				m_KillerSlots.emplace_back(killerslots());
			}
			m_Feedback.expandToDepth(depth);
		}
		constexpr static int shift(const depthType depthRemaining) noexcept
		{
			return 4 * (1 + static_cast<int>(depthRemaining));
		}
		constexpr static std::uintmax_t weight(const depthType depthRemaining) noexcept
		{
			return UINTMAX_C(1) << 2 * (1 + static_cast<int>(depthRemaining));
		}
	public:
		template<size_t PLAYER>
		constexpr scoreType moveScore(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
			constexpr const scoreType minimum{ scoreType::minimum() };
			if constexpr (heuristicMoves)
			{
				const size_t bucket{ generatorType::moveBucket(stack.position(),moveBits) };
				constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
				if (m_CutCounter[movingPlayer][bucket])
					return scoreType::quota(m_CutCounter[movingPlayer][bucket], m_TotalCounter[movingPlayer][bucket]);
				else
					return minimum;
			}
			else
			{
				return minimum;
			}
		}
		template<size_t PLAYER>
		constexpr scoreType tacticalMoveScore(const stackType<PLAYER>& stack, const movebitsType movebits, const size_t depth) noexcept
		{
			return evaluatorType::staticTacticalMoveScore(stack.position(), movebits);
		}
		template<size_t PLAYER>
		constexpr void killers(const stackType<PLAYER>& stack, const size_t depth, killermovesType& killermoves) noexcept
		{
			return m_KillerSlots[depth].killers(stack, killermoves);
		}
		template<size_t PLAYER>
		constexpr void tacticalKillers(const stackType<PLAYER>& stack, const size_t depth, killermovesType& killermoves) noexcept
		{
			return m_KillerSlots[depth].tacticalKillers(stack, killermoves);
		}
		template<size_t PLAYER>
		void sortMoves(const stackType<PLAYER>& stack, movelistType& moves, const indexType fromMoveIndex, const size_t depth) noexcept
		{
			std::array<scoreType, countMaxGeneratedMoves> scores;
			for (size_t i = static_cast<size_t>(fromMoveIndex); i < static_cast<size_t>(moves.length()); ++i)
			{
				scores[i - fromMoveIndex] = moveScore(stack, moves[i], depth);
			}
			this->sortMoves(moves, scores, fromMoveIndex, 0);
		}
		template<size_t PLAYER>
		void sortTacticalMoves(const stackType<PLAYER>& stack, movelistType& moves, const indexType fromMoveIndex, const size_t depth) noexcept
		{
			std::array<scoreType, countMaxGeneratedMoves> scores;
			for (size_t i = static_cast<size_t>(fromMoveIndex); i < static_cast<size_t>(moves.length()); ++i)
			{
				scores[i - fromMoveIndex] = evaluatorType::staticTacticalMoveScore(stack.position(), moves[i]);
			}
			this->sortMoves(moves, scores, fromMoveIndex, 0);
		}
		constexpr movegenFeedback& feedback() noexcept
		{
			return m_Feedback;
		}
		constexpr const movegenFeedback& feedback() const noexcept
		{
			return m_Feedback;
		}
		constexpr transpositiontable<descriptorSearch>& transpositionTable() noexcept
		{
			return m_TranspositionTable;
		}
		constexpr const transpositiontable<descriptorSearch>& transpositionTable() const noexcept
		{
			return m_TranspositionTable;
		}
		auto duration() const noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(!m_IsSearching);
#endif
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
		constexpr std::uintmax_t nodeCount() const noexcept
		{
			return m_NodeCounter;
		}
		void clear() noexcept
		{
			for (size_t i = 0; i < m_KillerSlots.size(); i++)
				m_KillerSlots[i].clear();
			for (const auto pl : playerType::range)
			{
				for (size_t bucket = 0; bucket < generatorType::countMoveBuckets(); bucket++)
				{
					m_CutCounter[pl][bucket] = 0;
					m_TotalCounter[pl][bucket] = 0;
				}
			}
		}
		void beginSearch() noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(!m_IsSearching);
			PYGMALION_ASSERT(m_NodeDepth == 0);
			PYGMALION_ASSERT(m_MoveDepth == 0);
			m_IsSearching = true;
#endif
			static_cast<instanceType*>(this)->onBeginSearch();
		}
		void endSearch() noexcept
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
		void beginNode(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth++;
#endif
			static_cast<instanceType*>(this)->template onBeginNode<PLAYER>(stack);
		}
		template<size_t PLAYER>
		void endNodeEarly(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeEarly<PLAYER>(stack);
		}
		template<size_t PLAYER>
		void endNodeLate(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeLate<PLAYER>(stack);
		}
		template<size_t PLAYER>
		void endNodeTT(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeTT<PLAYER>(stack);
		}
		template<size_t PLAYER>
		void endNodeNull(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeNull<PLAYER>(stack);
		}
		template<size_t PLAYER>
		void endNodeFutile(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeFutile<PLAYER>(stack);
		}
		template<size_t PLAYER, bool TACTICAL>
		void beginMove(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth++;
#endif
			static_cast<instanceType*>(this)->template onBeginMove<PLAYER, TACTICAL>(stack, moveBits, depth);
		}
		template<size_t PLAYER, bool PRUNED, bool TACTICAL>
		void endMoveAccepted(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const scoreType score, const scoreType eval, const bool fromStack, const depthType depthRemaining) noexcept
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
			if constexpr (killerMoves > 0)
			{
				m_KillerSlots[depth].template accepted<PLAYER, TACTICAL>(stack, moveBits, score, eval);
			}
			if constexpr (heuristicMoves)
			{
				if constexpr (!TACTICAL)
				{
					if (!generatorType::isMoveTactical(stack, moveBits))
					{
						const size_t bucket{ generatorType::moveBucket(stack.position(),moveBits) };
						constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
						const uintmax_t weightValue{ weight(depthRemaining) };
						m_CutCounter[movingPlayer][bucket] += weightValue;
						m_TotalCounter[movingPlayer][bucket] += weightValue;
					}
				}
			}
			static_cast<instanceType*>(this)->template onEndMoveAccepted<PLAYER, TACTICAL>(stack, moveBits, depth, score);
		}
		template<size_t PLAYER, bool PRUNED, bool TACTICAL>
		void endMoveRefuted(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const scoreType score, const scoreType eval, const bool fromStack, const depthType depthRemaining) noexcept
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
			if constexpr (killerMoves > 0)
			{
				m_KillerSlots[depth].template refuted<PLAYER, TACTICAL>(stack, moveBits, score, eval);
			}
			if constexpr (heuristicMoves)
			{
				if constexpr (!TACTICAL)
				{
					if (!generatorType::isMoveTactical(stack, moveBits))
					{
						const size_t bucket{ generatorType::moveBucket(stack.position(),moveBits) };
						constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
						const uintmax_t weightValue{ weight(depthRemaining) };
						m_CutCounter[movingPlayer][bucket] += weightValue;
						m_TotalCounter[movingPlayer][bucket] += weightValue;
					}
				}
			}
			static_cast<instanceType*>(this)->template onEndMoveRefuted<PLAYER, TACTICAL>(stack, moveBits, depth, score);
		}
		template<size_t PLAYER, bool TACTICAL>
		void endMoveSilent(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth, const depthType depthRemaining) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth--;
#endif
			if constexpr (heuristicMoves)
			{
				if constexpr (!TACTICAL)
				{
					if (!generatorType::isMoveTactical(stack, moveBits))
					{
						const size_t bucket{ generatorType::moveBucket(stack.position(),moveBits) };
						constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
						const uintmax_t weightValue{ weight(depthRemaining) };
						m_TotalCounter[movingPlayer][bucket] += weightValue;
					}
				}
			}
			static_cast<instanceType*>(this)->template onEndMoveSilent<PLAYER, TACTICAL>(stack, moveBits, depth);
		}
		template<size_t PLAYER, bool TACTICAL>
		void endMoveFutile(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_MoveDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndMoveFutile<PLAYER, TACTICAL>(stack, moveBits, depth);
		}
		template<size_t PLAYER>
		void endNodeCut(const stackType<PLAYER>& stack) noexcept
		{
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->template onEndNodeCut<PLAYER>(stack);
		}
		template<size_t PLAYER>
		void endNodeLeaf(const stackType<PLAYER>& stack) noexcept
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
			expandToDepth(countSearchPlies);
			for (const auto pl : playerType::range)
			{
				for (size_t bucket = 0; bucket < generatorType::countMoveBuckets(); bucket++)
				{
					m_CutCounter[pl][bucket] = 0;
					m_TotalCounter[pl][bucket] = 0;
				}
			}
		}
		~heuristics() noexcept = default;
		constexpr void age(const playerType movingPlayer) noexcept
		{
			if constexpr (heuristicMoves)
			{
				for (size_t bucket = 0; bucket < generatorType::countMoveBuckets(); bucket++)
				{
					const int shiftValue{ shift(-1) };
					m_CutCounter[movingPlayer][bucket] >>= shiftValue;
					m_TotalCounter[movingPlayer][bucket] >>= shiftValue;
				}
			}
		}
		constexpr void unAge(const playerType movingPlayer) noexcept
		{
			if constexpr (heuristicMoves)
			{
				for (size_t bucket = 0; bucket < generatorType::countMoveBuckets(); bucket++)
				{
					const int shiftValue{ shift(-1) };
					m_CutCounter[movingPlayer][bucket] <<= shiftValue;
					m_TotalCounter[movingPlayer][bucket] <<= shiftValue;
				}
			}
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
	protected:
		void onBeginSearch() noexcept
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
		void onEndNodeEarly(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeEarly(stack);
			m_EarlyNodes++;
		}
		void onEndNodeLate(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeLate(stack);
			m_LateNodes++;
		}
		void onEndNodeCut(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeCut(stack);
			m_CutNodes++;
		}
		void onEndNodeLeaf(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeLeaf(stack);
			m_LeafNodes++;
		}
		void onEndNodeTT(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeTT(stack);
			m_TTNodes++;
		}
		void onEndNodeNull(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeNull(stack);
			m_NullNodes++;
		}
		void onEndNodeFutile(const stackType& stack) noexcept
		{
			baseclassType::onEndNodeFutile(stack);
			m_FutileNodes++;
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
			m_LeafNodes{ 0 }
		{

		}
		~heuristics() noexcept = default;
	};

}