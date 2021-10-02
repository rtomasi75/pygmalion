namespace pygmalion::search
{
	template<typename GAMETREE>
	class engine :
		public pygmalion::evaluation::engine<typename GAMETREE::evaluatorType>,
		public GAMETREE::descriptorSearch
	{
	public:
		using gametreeType = GAMETREE;
		using nodeType = typename gametreeType::nodeType;
		using descriptorSearch = typename gametreeType::descriptorSearch;
#include "include_search.h"
		using stackType = typename generatorType::stackType;
	private:
		heuristicsType m_Heuristics;
		using contextType = typename generatorType::contextType;
		contextType* m_pContexts;
		static std::string variationToStringFromDepth(const stackType& stack, const variationType& variation, const depthType& depth) noexcept
		{
			if (variation.length() > depth)
			{
				std::stringstream sstr;
				sstr << stack.moveToString(variation[depth], depth) << " ";
				stackType subStack(stack, variation[depth]);
				sstr << variationToStringFromDepth(subStack, variation, depth + 1);
				return sstr.str();
			}
			return "";
		}
	public:
		constexpr contextType* rootContext() noexcept
		{
			return m_pContexts;
		}
		constexpr transpositiontable<descriptorSearch>& transpositionTable() noexcept
		{
			return m_Heuristics.transpositionTable();
		}
		constexpr const transpositiontable<descriptorSearch>& transpositionTable() const noexcept
		{
			return m_Heuristics.transpositionTable();
		}
		std::string variationToString(const variationType& variation) noexcept
		{
			stackType stack{ stackType(this->position(), this->history(),  this->position().movingPlayer(), this->rootContext()) };
			return variationToStringFromDepth(stack, variation, 0);
		}
		scoreType pvs(variationType& principalVariation, const depthType& depthRemaining, std::ostream& str) noexcept
		{
			this->feedback().sortIndices(this->history().length());
			stackType stack{ stackType(this->position(), this->history(), this->position().movingPlayer(), this->rootContext()) };
			std::atomic_bool isRunning{ true };
			m_Heuristics.beginSearch();
			nodeType node(stack, isRunning, m_Heuristics);
			principalVariation.clear();
			const scoreType score{ node.template searchRoot<false>(depthRemaining, this->history().length(), principalVariation, str) };
			m_Heuristics.endSearch();
			return score;
		}
		scoreType vpvs(variationType& principalVariation, const depthType& depthRemaining, std::ostream& str) noexcept
		{
			this->feedback().sortIndices(this->history().length());
			stackType stack{ stackType(this->position(), this->history(),  this->position().movingPlayer(), this->rootContext()) };
			std::atomic_bool isRunning{ true };
			m_Heuristics.beginSearch();
			nodeType node(stack, isRunning, m_Heuristics);
			principalVariation.clear();
			const scoreType score{ node.template searchRoot<true>(depthRemaining, this->history().length(), principalVariation, str) };
			m_Heuristics.endSearch();
			return score;
		}
		const heuristicsType& heuristics() const noexcept
		{
			return m_Heuristics;
		}
		heuristicsType& heuristics() noexcept
		{
			return m_Heuristics;
		}
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::evaluation::engine<typename GAMETREE::evaluatorType>(input, output),
			m_Heuristics{ heuristicsType(this->feedback()) },
			m_pContexts{ new contextType[countSearchPlies] }
		{
			this->template addCommand<command_debugSearch<descriptorSearch, gametreeType>>();
			this->template addCommand<command_debugPvs<descriptorSearch, gametreeType>>();
			this->template addCommand<command_debugTT<descriptorSearch, gametreeType>>();
			this->template addCommand<command_debugNode<descriptorSearch, gametreeType>>();
		}
		virtual ~engine() noexcept
		{
			delete[] m_pContexts;
		}
	};
}