namespace pygmalion
{
	template<typename DESCRIPTION_SEARCH, typename INSTANCE>
	class search :
		public base_search<DESCRIPTION_SEARCH>
	{
	public:
		using searchType = INSTANCE;

		using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"

		using nodeType = node<searchType, descriptorSearch>;

		class stack :
			public base_search<DESCRIPTION_SEARCH>,
			public evaluationType::stackType
		{
		public:
			using searchType = INSTANCE;

			using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"

			stack(const stack& parent, const moveType move) noexcept :
				evaluationType::stackType(parent, move)
			{
			}
			stack(boardType& position, const playerType oldPlayer) noexcept :
				evaluationType::stackType(position, oldPlayer)
			{
			}
			~stack() noexcept = default;
		};
		using stackType = typename pygmalion::search<DESCRIPTION_SEARCH, searchType>::stack;

	public:
		static scoreType pvs(const boardType& position, variationType& principalVariation, const depthType depthRemaining, heuristicsType& heuristics) noexcept
		{
			boardType b{ position };
			nodeType node(b);
			principalVariation.clear();
			multiscoreType alphabeta;
			heuristics.beginSearch();
			const scoreType score{ node.search(alphabeta, depthRemaining, 0, principalVariation, heuristics) };
			heuristics.endSearch();
			return score;
		}

		static void perft(const boardType& position, const depthType depthRemaining, heuristicsType& heuristics) noexcept
		{
			boardType b{ position };
			nodeType node(b);
			heuristics.beginSearch();
			node.perft(depthRemaining, 0, heuristics);
			heuristics.endSearch();
		}
	};
}