namespace pygmalion
{

	template<bool VERBOSE, typename DESCRIPTION_SEARCH>
	class heuristics
	{

	};

	template<typename DESCRIPTION_SEARCH>
	class heuristics<false, DESCRIPTION_SEARCH> :
		public DESCRIPTION_SEARCH
	{
		friend class heuristics<true, DESCRIPTION_SEARCH>;
	public:
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
		virtual void onBeginSearch() noexcept
		{
			m_NodeCounter = 0;
			m_SearchProfiler.start();
		}

		virtual void onEndSearch() noexcept
		{
			m_SearchProfiler.stop();
		}

		virtual void onBeginNode(const boardType& position) noexcept
		{
			m_NodeCounter++;
		}
		virtual void onEndNodeEarly(const boardType& position) noexcept
		{
		}
		virtual void onEndNodeLate(const boardType& position) noexcept
		{
		}
		virtual void onBeginMove(const boardType& position, const movebitsType moveBits) noexcept
		{
		}
		virtual void onEndMoveRefuted(const boardType& position, const movebitsType moveBits) noexcept
		{
		}
		virtual void onEndMoveSilent(const boardType& position, const movebitsType moveBits) noexcept
		{
		}
		virtual void onEndMoveAccepted(const boardType& position, const movebitsType moveBits) noexcept
		{
		}
		virtual void onEndNodeCut(const boardType& position) noexcept
		{
		}
		virtual void onEndNodeLeaf(const boardType& position) noexcept
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
			this->onBeginSearch();
		}
		void endSearch() noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
			m_IsSearching = false;
#endif
			this->onEndSearch();
		}
		void beginNode(const boardType& position) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			this->onBeginNode(position);
		}
		void endNodeEarly(const boardType& position) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			this->onEndNodeEarly(position);
		}
		void endNodeLate(const boardType& position) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			this->onEndNodeLate(position);
		}
		void beginMove(const boardType& position, const movebitsType moveBits) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			this->onBeginMove(position, moveBits);
		}
		void endMoveAccepted(const boardType& position, const movebitsType moveBits) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			this->onEndMoveAccepted(position, moveBits);
		}
		void endMoveRefuted(const boardType& position, const movebitsType moveBits) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			this->onEndMoveRefuted(position, moveBits);
		}
		void endMoveSilent(const boardType& position, const movebitsType moveBits) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			this->onEndMoveSilent(position, moveBits);
		}
		void endNodeCut(const boardType& position) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			this->onEndNodeCut(position);
		}
		void endNodeLeaf(const boardType& position) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			this->onEndNodeLeaf(position);
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

	template<typename DESCRIPTION_SEARCH>
	class heuristics<true, DESCRIPTION_SEARCH> :
		public heuristics<false, DESCRIPTION_SEARCH>
	{
		friend class heuristics<false, DESCRIPTION_SEARCH>;
	public:
		using baseclassType = heuristics<false, DESCRIPTION_SEARCH>;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"

	private:
		std::uint64_t m_EarlyNodes;
		std::uint64_t m_LateNodes;
		std::uint64_t m_CutNodes;
		std::uint64_t m_LeafNodes;
	protected:
		virtual void onBeginSearch() noexcept override
		{
			baseclassType::onBeginSearch();
			m_EarlyNodes = 0;
			m_LateNodes = 0;
			m_CutNodes = 0;
			m_LeafNodes = 0;
		}
		virtual void onEndNodeEarly(const boardType& position) noexcept override
		{
			baseclassType::onEndNodeEarly(position);
			m_EarlyNodes++;
		}
		virtual void onEndNodeLate(const boardType& position) noexcept override
		{
			baseclassType::onEndNodeLate(position);
			m_LateNodes++;
		}
		virtual void onEndNodeCut(const boardType& position) noexcept override
		{
			baseclassType::onEndNodeCut(position);
			m_CutNodes++;
		}
		virtual void onEndNodeLeaf(const boardType& position) noexcept override
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