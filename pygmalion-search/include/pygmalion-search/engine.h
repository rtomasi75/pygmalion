namespace pygmalion::search
{
	template<typename NODE>
	class engine :
		public pygmalion::evaluation::engine<typename NODE::evaluatorType>,
		public NODE::descriptorSearch
	{
	public:
		using nodeType = NODE;
		using descriptorSearch = typename NODE::descriptorSearch;
#include "include_search.h"
	private:
		heuristicsType m_Heuristics;
		using stackType = typename NODE::stackType;
		static std::string variationToStringFromDepth(const stackType& stack, const variationType& variation, const depthType depth) noexcept
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
			stackType stack{ stackType(this->position(), this->history(),  this->position().movingPlayer()) };
			return variationToStringFromDepth(stack, variation, 0);
		}
		scoreType pvs(variationType& principalVariation, const depthType depthRemaining, std::ostream& str) noexcept
		{
			bool allowStoreTT;
			this->feedback().sortIndices(this->history().length());
			stackType stack{ stackType(this->position(), this->history(),  this->position().movingPlayer()) };
			std::atomic_bool isRunning{ true };
			m_Heuristics.beginSearch();
			nodeType node(stack, isRunning, m_Heuristics);
			principalVariation.clear();
			const scoreType score{ node.template search<false,true>(scoreType::minimum(),scoreType::maximum(), depthRemaining, this->history().length(), principalVariation, str, allowStoreTT) };
			m_Heuristics.endSearch();
			return score;
		}
		scoreType vpvs(variationType& principalVariation, const depthType depthRemaining, std::ostream& str) noexcept
		{
			bool allowStoreTT;
			this->feedback().sortIndices(this->history().length());
			stackType stack{ stackType(this->position(), this->history(),  this->position().movingPlayer()) };
			std::atomic_bool isRunning{ true };
			m_Heuristics.beginSearch();
			nodeType node(stack, isRunning, m_Heuristics);
			principalVariation.clear();
			const scoreType score{ node.template search<true,true>(scoreType::minimum(),scoreType::maximum(), depthRemaining, this->history().length(), principalVariation, str, allowStoreTT) };
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
			pygmalion::evaluation::engine<typename NODE::evaluatorType>(input, output),
			m_Heuristics{ heuristicsType(this->feedback()) }
		{
			this->template addCommand<command_debugSearch<descriptorSearch, nodeType>>();
			this->template addCommand<command_debugPvs<descriptorSearch, nodeType>>();
			this->template addCommand<command_debugTT<descriptorSearch, nodeType>>();
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "no game (search only)";
		}
	};
}