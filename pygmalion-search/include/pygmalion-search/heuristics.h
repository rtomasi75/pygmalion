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

	private:
#if !defined(NDEBUG)
		bool m_IsSearching;
#endif
		profiler m_SearchProfiler;
		std::uintmax_t m_NodeCounter;
		transpositiontable<descriptorSearch> m_TranspositionTable;
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
		void onBeginNode(const boardType& position) noexcept
		{
			m_NodeCounter++;
		}
		void onEndNodeEarly(const boardType& position) noexcept
		{
		}
		void onEndNodeLate(const boardType& position) noexcept
		{
		}
		void onBeginMove(const boardType& position, const movebitsType moveBits) noexcept
		{
		}
		void onEndMoveRefuted(const boardType& position, const movebitsType moveBits) noexcept
		{
		}
		void onEndMoveSilent(const boardType& position, const movebitsType moveBits) noexcept
		{
		}
		void onEndMoveAccepted(const boardType& position, const movebitsType moveBits) noexcept
		{
		}
		void onEndNodeCut(const boardType& position) noexcept
		{
		}
		void onEndNodeLeaf(const boardType& position) noexcept
		{
		}
	public:
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
			m_IsSearching = true;
#endif
			reinterpret_cast<instanceType*>(this)->onBeginSearch();
		}
		void endSearch() noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_IsSearching = false;
#endif
			reinterpret_cast<instanceType*>(this)->onEndSearch();
		}
		void beginNode(const boardType& position) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onBeginNode(position);
		}
		void endNodeEarly(const boardType& position) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onEndNodeEarly(position);
		}
		void endNodeLate(const boardType& position) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onEndNodeLate(position);
		}
		void beginMove(const boardType& position, const movebitsType moveBits) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onBeginMove(position, moveBits);
		}
		void endMoveAccepted(const boardType& position, const movebitsType moveBits) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onEndMoveAccepted(position, moveBits);
		}
		void endMoveRefuted(const boardType& position, const movebitsType moveBits) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onEndMoveRefuted(position, moveBits);
		}
		void endMoveSilent(const boardType& position, const movebitsType moveBits) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onEndMoveSilent(position, moveBits);
		}
		void endNodeCut(const boardType& position) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onEndNodeCut(position);
		}
		void endNodeLeaf(const boardType& position) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onEndNodeLeaf(position);
		}
		heuristics() noexcept :
#if !defined(NDEBUG)
			m_IsSearching{ false },
#endif
			m_NodeCounter{ 0 },
			m_TranspositionTable{ transpositiontable<descriptorSearch>() }
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
		}
		void onEndNodeEarly(const boardType& position) noexcept
		{
			baseclassType::onEndNodeEarly(position);
			m_EarlyNodes++;
		}
		void onEndNodeLate(const boardType& position) noexcept
		{
			baseclassType::onEndNodeLate(position);
			m_LateNodes++;
		}
		void onEndNodeCut(const boardType& position) noexcept
		{
			baseclassType::onEndNodeCut(position);
			m_CutNodes++;
		}
		void onEndNodeLeaf(const boardType& position) noexcept
		{
			baseclassType::onEndNodeLeaf(position);
			m_LeafNodes++;
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
		std::string toString() const noexcept
		{
			std::stringstream sstr;
			sstr << "early: " << std::setw(9) << parser::nodesCountToString(earlyNodeCount()) << std::endl;
			sstr << "cut:   " << std::setw(9) << parser::nodesCountToString(cutNodeCount()) << std::endl;
			sstr << "late:  " << std::setw(9) << parser::nodesCountToString(lateNodeCount()) << std::endl;
			sstr << "leaf:  " << std::setw(9) << parser::nodesCountToString(leafNodeCount()) << std::endl;
			return sstr.str();
		}
		heuristics() noexcept :
			m_EarlyNodes{ 0 },
			m_LateNodes{ 0 },
			m_CutNodes{ 0 },
			m_LeafNodes{ 0 }
		{

		}
		~heuristics() noexcept = default;
	};

}