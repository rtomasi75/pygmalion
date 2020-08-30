namespace pygmalion
{

	template<bool VERBOSE, typename DESCRIPTION_MECHANICS, typename INSTANCE>
	class searchtable
	{

	};

	template<typename DESCRIPTION_MECHANICS, typename INSTANCE>
	class searchtable<false, DESCRIPTION_MECHANICS, INSTANCE> :
		public base_mechanics<DESCRIPTION_MECHANICS>
	{
		friend class searchtable<true, DESCRIPTION_MECHANICS, INSTANCE>;
	public:
		using instanceType = INSTANCE;

		using descriptorMechanics = DESCRIPTION_MECHANICS;
#include "include_mechanics.h"

	private:
#if !defined(NDEBUG)
		bool m_IsSearching;
#endif
		std::chrono::time_point<std::chrono::steady_clock> m_BeginSearchTime;
		std::chrono::time_point<std::chrono::steady_clock> m_EndSearchTime;
		std::uint64_t m_NodeCounter;
	protected:
		void onBeginSearch() noexcept
		{
			m_NodeCounter = 0;
			m_BeginSearchTime = std::chrono::high_resolution_clock::now();
		}

		void onEndSearch() noexcept
		{
			m_EndSearchTime = std::chrono::high_resolution_clock::now();
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
		void onBeginMove(const boardType& position, const moveType move) noexcept
		{
		}
		void onEndMoveRefuted(const boardType& position, const moveType move) noexcept
		{
		}
		void onEndMoveSilent(const boardType& position, const moveType move) noexcept
		{
		}
		void onEndMoveAccepted(const boardType& position, const moveType move) noexcept
		{
		}
		void onEndNodeCut(const boardType& position) noexcept
		{
		}
		void onEndNodeLeaf(const boardType& position) noexcept
		{
		}
	public:
		auto duration() const noexcept
		{
#if !defined(NDEBUG)
			assert(!m_IsSearching);
#endif
			return m_EndSearchTime - m_BeginSearchTime;
		}
		double nodesPerSecond() const noexcept
		{
			return parser::computeNodesPerSec(m_NodeCounter, duration());
		}
		std::string toString() const noexcept
		{
			std::stringstream sstr;
			sstr << std::setw(9) << parser::nodesCountToString(nodeCount()) << " in " << parser::durationToString(duration()) << " => " << parser::nodesPerSecondToString(nodesPerSecond()) << std::endl;
			return sstr.str();
		}
		constexpr std::uint64_t nodeCount() const noexcept
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
		void beginMove(const boardType& position, const moveType move) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onBeginMove(position, move);
		}
		void endMoveAccepted(const boardType& position, const moveType move) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onEndMoveAccepted(position, move);
		}
		void endMoveRefuted(const boardType& position, const moveType move) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onEndMoveRefuted(position, move);
		}
		void endMoveSilent(const boardType& position, const moveType move) noexcept
		{
#if !defined(NDEBUG)
			assert(m_IsSearching);
#endif
			reinterpret_cast<instanceType*>(this)->onEndMoveSilent(position, move);
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
		searchtable() noexcept :
#if !defined(NDEBUG)
			m_IsSearching{ false },
#endif
			m_NodeCounter{ 0 }
		{

		}
		~searchtable() noexcept = default;
	};

	template<typename DESCRIPTION_MECHANICS, typename INSTANCE>
	class searchtable<true, DESCRIPTION_MECHANICS, INSTANCE> : 
		public searchtable<false, DESCRIPTION_MECHANICS, INSTANCE>
	{
		friend class searchtable<false, DESCRIPTION_MECHANICS, INSTANCE>;
	public:
		using instanceType = INSTANCE;
		using baseclassType = searchtable<false, DESCRIPTION_MECHANICS, INSTANCE>;

		using descriptorMechanics = DESCRIPTION_MECHANICS;
#include "include_mechanics.h"

	private:
		std::uint64_t m_EarlyNodes;
		std::uint64_t m_LateNodes;
		std::uint64_t m_CutNodes;
		std::uint64_t m_LeafNodes;
	protected:
		void onBeginSearch() noexcept
		{
			reinterpret_cast<baseclassType*>(this)->onBeginSearch();
			m_EarlyNodes = 0;
			m_LateNodes = 0;
			m_CutNodes = 0;
			m_LeafNodes = 0;
		}
		void onEndNodeEarly(const boardType& position) noexcept
		{
			reinterpret_cast<baseclassType*>(this)->onEndNodeEarly(position);
			m_EarlyNodes++;
		}
		void onEndNodeLate(const boardType& position) noexcept
		{
			reinterpret_cast<baseclassType*>(this)->onEndNodeLate(position);
			m_LateNodes++;
		}
		void onEndNodeCut(const boardType& position) noexcept
		{
			reinterpret_cast<baseclassType*>(this)->onEndNodeCut(position);
			m_CutNodes++;
		}
		void onEndNodeLeaf(const boardType& position) noexcept
		{
			reinterpret_cast<baseclassType*>(this)->onEndNodeLeaf(position);
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
			sstr << std::setw(9) << parser::nodesCountToString(earlyNodeCount()) << " early " << std::setw(9) << parser::nodesCountToString(cutNodeCount()) << " cut " << std::setw(9) << parser::nodesCountToString(lateNodeCount()) << " late " << std::setw(9) << parser::nodesCountToString(leafNodeCount()) << " leaf" << std::endl;
			sstr << reinterpret_cast<const baseclassType*>(this)->toString();
			return sstr.str();
		}
		searchtable() noexcept :
			m_EarlyNodes{ 0 },
			m_LateNodes{ 0 },
			m_CutNodes{ 0 },
			m_LeafNodes{ 0 }
		{

		}
		~searchtable() noexcept = default;
	};

}