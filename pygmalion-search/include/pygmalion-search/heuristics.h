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
		using passType = typename generatorType::passType;
		using stackType = typename generatorType::stackType;
		class movebucket
		{
		private:
			std::array<std::uint64_t, generatorType::countMoveBuckets()> m_Counter;
			std::array<scoreType, generatorType::countMoveBuckets()> m_Score;
			std::array<movebitsType, killerMoves> m_Killers;
			std::array<movebitsType, killerMoves> m_TacticalKillers;
			size_t m_KillerCount;
			size_t m_TacticalKillerCount;
		public:
			constexpr movebucket() noexcept :
				m_Counter{ arrayhelper::make<generatorType::countMoveBuckets(),std::uint64_t>(0) },
				m_Score{ arrayhelper::make<generatorType::countMoveBuckets(),scoreType>(scoreType::zero()) },
				m_Killers{ arrayhelper::make<killerMoves,movebitsType>(movebitsType(0)) },
				m_TacticalKillers{ arrayhelper::make<killerMoves,movebitsType>(movebitsType(0)) },
				m_KillerCount{ 0 },
				m_TacticalKillerCount{ 0 }
			{

			}
			constexpr std::uint64_t counter(const boardType& position, const movebitsType& moveBits) const noexcept
			{
				return m_Counter[generatorType::moveBucket(position, moveBits)];
			}
			constexpr scoreType score(const boardType& position, const movebitsType& moveBits) const noexcept
			{
				const size_t bucket{ generatorType::moveBucket(position, moveBits) };
				if (m_Counter[bucket] == 0)
					return scoreType::minimum();
				if (m_Score[bucket].isOpen())
					return m_Score[bucket] / static_cast<typename scoreType::valueType>(m_Counter[bucket]);
				else
					return m_Score[bucket];
			}
			constexpr void killers(const stackType& stack, killermovesType& killerMoves) const noexcept
			{
				for (size_t i = 0; i < m_KillerCount; i++)
				{
					if (generatorType::isMoveLegal(stack, m_Killers[i]))
						killerMoves.add(m_Killers[i]);
				}
			}
			constexpr void tacticalKillers(const stackType& stack, killermovesType& killerMoves) const noexcept
			{
				for (size_t i = 0; i < m_TacticalKillerCount; i++)
				{
					if (generatorType::isMoveLegal(stack, m_TacticalKillers[i]))
						killerMoves.add(m_TacticalKillers[i]);
				}
			}
			constexpr void refuted(const stackType& stack, const movebitsType& moveBits, const scoreType& score) noexcept
			{
				const boardType& position{ stack.position() };
				const size_t index{ generatorType::moveBucket(position,moveBits) };
				m_Counter[index]++;
				if (score.isOpen())
				{
					if (m_Score[index].isOpen())
						m_Score[index] += score;
					else
						m_Score[index] = scoreType::max(score, m_Score[index]);
				}
				else
					m_Score[index] = scoreType::max(score, m_Score[index]);
				bool contains{ false };
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
			constexpr void accepted(const stackType& stack, const movebitsType& moveBits, const scoreType& score) noexcept
			{
				const boardType& position{ stack.position() };
				const size_t index{ generatorType::moveBucket(position,moveBits) };
				m_Counter[index]++;
				if (score.isOpen())
				{
					if (m_Score[index].isOpen())
						m_Score[index] += score;
					else
						m_Score[index] = scoreType::max(score, m_Score[index]);
				}
				else
					m_Score[index] = scoreType::max(score, m_Score[index]);
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
		std::vector<movebucket> m_MoveBuckets;
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
		void onBeginNode(const stackType& stack) noexcept
		{
			m_NodeCounter++;
		}
		void onEndNodeEarly(const stackType& stack) noexcept
		{
		}
		void onEndNodeLate(const stackType& stack) noexcept
		{
		}
		void onBeginMove(const stackType& stack, const movebitsType& moveBits, const bool isTactical, const size_t depth) noexcept
		{
		}
		void onEndMoveRefuted(const stackType& stack, const movebitsType& moveBits, const bool isTactical, const size_t depth, const scoreType& score) noexcept
		{
		}
		void onEndMoveSilent(const stackType& stack, const movebitsType& moveBits, const bool isTactical, const size_t depth) noexcept
		{
		}
		void onEndMoveFutile(const stackType& stack, const movebitsType& moveBits, const bool isTactical, const size_t depth) noexcept
		{
		}
		void onEndMoveAccepted(const stackType& stack, const movebitsType& moveBits, const bool isTactical, const size_t depth, const scoreType& score) noexcept
		{
		}
		void onEndNodeCut(const stackType& stack) noexcept
		{
		}
		void onEndNodeLeaf(const stackType& stack) noexcept
		{
		}
		void onEndNodeTT(const stackType& stack) noexcept
		{
		}
		void onEndNodeNull(const stackType& stack) noexcept
		{
		}
		void onEndNodeFutile(const stackType& stack) noexcept
		{
		}
		void sortMoves(movelistType& moves, list<scoreType, countMaxGeneratedMoves>& scores, const indexType& fromMoveIndex, const indexType& fromScoreIndex) noexcept
		{
			const indexType length{ static_cast<indexType>(moves.length() - fromMoveIndex) };
			sort<movebitsType, scoreType>::sortValues(moves.ptr() + static_cast<size_t>(fromMoveIndex), scores.ptr() + static_cast<size_t>(fromScoreIndex), length);
		}
	public:
		constexpr scoreType moveScore(const boardType& position, const movebitsType& movebits, const size_t depth) noexcept
		{
			while (depth >= m_MoveBuckets.size())
			{
				m_MoveBuckets.emplace_back(movebucket());
			}
			return m_MoveBuckets[depth].score(position, movebits);
		}
		constexpr void killers(const stackType& stack, const size_t depth, killermovesType& killermoves) noexcept
		{
			while (depth >= m_MoveBuckets.size())
			{
				m_MoveBuckets.emplace_back(movebucket());
			}
			return m_MoveBuckets[depth].killers(stack, killermoves);
		}
		constexpr void tacticalKillers(const stackType& stack, const size_t depth, killermovesType& killermoves) noexcept
		{
			while (depth >= m_MoveBuckets.size())
			{
				m_MoveBuckets.emplace_back(movebucket());
			}
			return m_MoveBuckets[depth].tacticalKillers(stack, killermoves);
		}
		void sortMoves(const boardType& position, movelistType& moves, const indexType& fromMoveIndex, const size_t depth) noexcept
		{
			list<scoreType, countMaxGeneratedMoves> scores{ list<scoreType, countMaxGeneratedMoves>() };
			while (depth >= m_MoveBuckets.size())
			{
				m_MoveBuckets.emplace_back(movebucket());
			}
			for (indexType i = fromMoveIndex; i < moves.length(); ++i)
			{
				scores.add(m_MoveBuckets[depth].score(position, moves[i]));
			}
			this->sortMoves(moves, scores, fromMoveIndex, 0);
		}
		void sortTacticalMoves(const boardType& position, movelistType& moves, const indexType& fromMoveIndex, const size_t depth) noexcept
		{
			list<scoreType, countMaxGeneratedMoves> scores{ list<scoreType, countMaxGeneratedMoves>() };
			for (indexType i = fromMoveIndex; i < moves.length(); ++i)
			{
				scores.add(evaluatorType::staticTacticalMoveScore(position, moves[i]));
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
			assert(!m_IsSearching);
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
			m_MoveBuckets.clear();
		}
		void beginSearch() noexcept
		{
#if !defined(NDEBUG)
			assert(!m_IsSearching);
			assert(m_NodeDepth == 0);
			assert(m_MoveDepth == 0);
			m_IsSearching = true;
#endif
			static_cast<instanceType*>(this)->onBeginSearch();
		}
		void endSearch() noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			assert(m_NodeDepth == 0);
			assert(m_MoveDepth == 0);
			m_IsSearching = false;
#endif
			static_cast<instanceType*>(this)->onEndSearch();
		}
		void beginNode(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth++;
#endif
			static_cast<instanceType*>(this)->onBeginNode(stack);
		}
		void endNodeEarly(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->onEndNodeEarly(stack);
		}
		void endNodeLate(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->onEndNodeLate(stack);
		}
		void endNodeTT(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->onEndNodeTT(stack);
		}
		void endNodeNull(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->onEndNodeNull(stack);
		}
		void endNodeFutile(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->onEndNodeFutile(stack);
		}
		void beginMove(const stackType& stack, const movebitsType& moveBits, const bool isTactical, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_MoveDepth++;
#endif
			static_cast<instanceType*>(this)->onBeginMove(stack, moveBits, isTactical, depth);
		}
		template<bool PRUNED>
		void endMoveAccepted(const stackType& stack, const movebitsType& moveBits, const bool isTactical, const size_t depth, const scoreType& score, const bool fromStack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_MoveDepth--;
#endif
			if (fromStack)
			{
				if constexpr (!PRUNED)
				{
					if (isTactical)
						stack.tacticalAllMove(m_Feedback, depth, score);
					else
						stack.allMove(m_Feedback, depth, score);
				}
				else
					stack.criticalAllMove(m_Feedback, depth, score);
			}
			if constexpr (heuristicMoves)
			{
				while (depth >= m_MoveBuckets.size())
				{
					m_MoveBuckets.emplace_back(movebucket());
				}
				m_MoveBuckets[depth].accepted(stack, moveBits, score);
			}
			static_cast<instanceType*>(this)->onEndMoveAccepted(stack, moveBits, isTactical, depth, score);
		}
		template<bool PRUNED>
		void endMoveRefuted(const stackType& stack, const movebitsType& moveBits, const bool isTactical, const size_t depth, const scoreType& score, const bool fromStack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_MoveDepth--;
#endif
			if (fromStack)
			{
				if constexpr (!PRUNED)
				{
					if (isTactical)
						stack.tacticalCutMove(m_Feedback, depth, score);
					else
						stack.cutMove(m_Feedback, depth, score);
				}
				else
					stack.criticalCutMove(m_Feedback, depth, score);
			}
			if constexpr (heuristicMoves)
			{
				while (depth >= m_MoveBuckets.size())
				{
					m_MoveBuckets.emplace_back(movebucket());
				}
				m_MoveBuckets[depth].refuted(stack, moveBits, score);
			}
			static_cast<instanceType*>(this)->onEndMoveRefuted(stack, moveBits, isTactical, depth, score);
		}
		void endMoveSilent(const stackType& stack, const movebitsType& moveBits, const bool isTactical, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_MoveDepth--;
#endif
			static_cast<instanceType*>(this)->onEndMoveSilent(stack, moveBits, isTactical, depth);
		}
		void endMoveFutile(const stackType& stack, const movebitsType& moveBits, const bool isTactical, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_MoveDepth--;
#endif
			static_cast<instanceType*>(this)->onEndMoveFutile(stack, moveBits, isTactical, depth);
		}
		void endNodeCut(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->onEndNodeCut(stack);
		}
		void endNodeLeaf(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth--;
#endif
			static_cast<instanceType*>(this)->onEndNodeLeaf(stack);
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
			m_MoveBuckets{ std::vector<movebucket>(0) }
		{

		}
		~heuristics() noexcept = default;
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