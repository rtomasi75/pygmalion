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
		void onBeginMove(const stackType& stack, const movebitsType moveBits, const bool isTactical, const size_t depth) noexcept
		{
		}
		void onEndMoveRefuted(const stackType& stack, const movebitsType moveBits, const bool isTactical, const size_t depth, const scoreType score) noexcept
		{
		}
		void onEndMoveSilent(const stackType& stack, const movebitsType moveBits, const bool isTactical, const size_t depth) noexcept
		{
		}
		void onEndMoveAccepted(const stackType& stack, const movebitsType moveBits, const bool isTactical, const size_t depth, const scoreType score) noexcept
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
	public:
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
		void beginSearch() noexcept
		{
#if !defined(NDEBUG)
			assert(!m_IsSearching);
			assert(m_NodeDepth == 0);
			assert(m_MoveDepth == 0);
			m_IsSearching = true;
#endif
			reinterpret_cast<instanceType*>(this)->onBeginSearch();
		}
		void endSearch() noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			assert(m_NodeDepth == 0);
			assert(m_MoveDepth == 0);
			m_IsSearching = false;
#endif
			reinterpret_cast<instanceType*>(this)->onEndSearch();
		}
		void beginNode(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth++;
#endif
			reinterpret_cast<instanceType*>(this)->onBeginNode(stack);
		}
		void endNodeEarly(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth--;
#endif
			reinterpret_cast<instanceType*>(this)->onEndNodeEarly(stack);
		}
		void endNodeLate(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth--;
#endif
			reinterpret_cast<instanceType*>(this)->onEndNodeLate(stack);
		}
		void endNodeTT(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth--;
#endif
			reinterpret_cast<instanceType*>(this)->onEndNodeTT(stack);
		}
		void beginMove(const stackType& stack, const movebitsType moveBits, const bool isTactical, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_MoveDepth++;
#endif
			reinterpret_cast<instanceType*>(this)->onBeginMove(stack, moveBits, isTactical, depth);
		}
		void endMoveAccepted(const stackType& stack, const movebitsType moveBits, const bool isTactical, const size_t depth, const scoreType score) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_MoveDepth--;
#endif
			if (isTactical)
				stack.tacticalAllMove(m_Feedback, depth, score);
			else
				stack.allMove(m_Feedback, depth, score);
			reinterpret_cast<instanceType*>(this)->onEndMoveAccepted(stack, moveBits, isTactical, depth, score);
		}
		void endMoveRefuted(const stackType& stack, const movebitsType moveBits, const bool isTactical, const size_t depth, const scoreType score) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_MoveDepth--;
#endif
			if (isTactical)
				stack.tacticalCutMove(m_Feedback, depth, score);
			else
				stack.cutMove(m_Feedback, depth, score);
			reinterpret_cast<instanceType*>(this)->onEndMoveRefuted(stack, moveBits, isTactical, depth, score);
		}
		void endMoveSilent(const stackType& stack, const movebitsType moveBits, const bool isTactical, const size_t depth) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_MoveDepth--;
#endif
			reinterpret_cast<instanceType*>(this)->onEndMoveSilent(stack, moveBits, isTactical, depth);
		}
		void endNodeCut(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth--;
#endif
			reinterpret_cast<instanceType*>(this)->onEndNodeCut(stack);
		}
		void endNodeLeaf(const stackType& stack) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_NodeDepth--;
#endif
			reinterpret_cast<instanceType*>(this)->onEndNodeLeaf(stack);
		}
		heuristics(movegenFeedback& feedback) noexcept :
#if !defined(NDEBUG)
			m_IsSearching{ false },
			m_NodeDepth{ 0 },
			m_MoveDepth{ 0 },
#endif
			m_NodeCounter{ 0 },
			m_TranspositionTable{ transpositiontable<descriptorSearch>() },
			m_Feedback{ feedback }
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
	protected:
		void onBeginSearch() noexcept
		{
			baseclassType::onBeginSearch();
			m_EarlyNodes = 0;
			m_LateNodes = 0;
			m_CutNodes = 0;
			m_LeafNodes = 0;
			m_TTNodes = 0;
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
			baseclassType::onEndNodeLeaf(stack);
			m_TTNodes++;
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
			return m_LeafNodes;
		}
		std::string toString() const noexcept
		{
			std::stringstream sstr;
			sstr << "early: " << std::setw(9) << parser::nodesCountToString(earlyNodeCount()) << std::endl;
			sstr << "cut:   " << std::setw(9) << parser::nodesCountToString(cutNodeCount()) << std::endl;
			sstr << "late:  " << std::setw(9) << parser::nodesCountToString(lateNodeCount()) << std::endl;
			sstr << "leaf:  " << std::setw(9) << parser::nodesCountToString(leafNodeCount()) << std::endl;
			sstr << "TT:    " << std::setw(9) << parser::nodesCountToString(TTNodeCount()) << std::endl;
			return sstr.str();
		}
		heuristics(movegenFeedback& feedback) noexcept :
			baseclassType(feedback),
			m_EarlyNodes{ 0 },
			m_LateNodes{ 0 },
			m_CutNodes{ 0 },
			m_TTNodes{ 0 },
			m_LeafNodes{ 0 }
		{

		}
		~heuristics() noexcept = default;
	};

}