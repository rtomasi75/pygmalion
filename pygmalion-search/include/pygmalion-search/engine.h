namespace pygmalion::search
{
	template<typename GAMETREE>
	class engine :
		public pygmalion::evaluation::engine<typename GAMETREE::evaluatorType>,
		public GAMETREE::descriptorSearch
	{
	public:
		using gametreeType = GAMETREE;
		template<size_t PLAYER>
		using nodeType = typename gametreeType::template nodeType<PLAYER>;
		using descriptorSearch = typename gametreeType::descriptorSearch;
#include "include_search.h"
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
	private:
		heuristicsType m_Heuristics;
		using contextType = typename generatorType::contextType;
		contextType* m_pContexts;
		template<size_t PLAYER>
		static std::string variationToStringFromDepth(const stackType<PLAYER>& stack, const variationType& variation, const depthType& depth) noexcept
		{
			if (variation.length() > depth)
			{
				constexpr playerType player{ static_cast<playerType>(PLAYER) };
				constexpr playerType nextPlayer{ player.next() };
				std::stringstream sstr;
				sstr << stack.moveToString(variation[depth], depth) << " ";
				stackType<static_cast<size_t>(nextPlayer)> subStack{ stackType<static_cast<size_t>(nextPlayer)>(stack, variation[depth]) };
				sstr << variationToStringFromDepth<static_cast<size_t>(nextPlayer)>(subStack, variation, depth + 1);
				return sstr.str();
			}
			return "";
		}
	public:
		virtual void onMakeMove(const movebitsType movebits) noexcept override
		{
			pygmalion::evaluation::engine<typename GAMETREE::evaluatorType>::onMakeMove(movebits);
			m_Heuristics.age(this->position().movingPlayer());
		}
		virtual void onUnMakeMove() noexcept override
		{
			pygmalion::evaluation::engine<typename GAMETREE::evaluatorType>::onUnMakeMove();
			m_Heuristics.unAge(this->position().movingPlayer());
		}
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
		template<size_t PLAYER>
		std::string variationToString(const variationType& variation) noexcept
		{
			stackType<PLAYER> stack{ stackType<PLAYER>(this->position(), this->history(), this->rootContext()) };
			return variationToStringFromDepth(stack, variation, 0);
		}
		template<size_t PLAYER>
		scoreType pvs(variationType& principalVariation, const depthType& depthRemaining) noexcept
		{
			if constexpr (PLAYER >= countPlayers)
			{
				PYGMALION_ASSERT(false);
				constexpr const scoreType zero{ scoreType::zero() };
				return zero;
			}
			else
			{
				constexpr playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					this->feedback().sortIndices(this->history().length());
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(), this->history(), this->rootContext()) };
					std::atomic_bool isRunning{ true };
					m_Heuristics.beginSearch();
					nodeType<static_cast<size_t>(static_cast<playerType>(PLAYER))> node(stack, isRunning, m_Heuristics, this->history().length());
					principalVariation.clear();
					indexType currentMove;
					indexType countMoves;
					const scoreType score{ node.template searchRoot<false, false>(depthRemaining, principalVariation, this->outputStream(), currentMove, countMoves) };
					m_Heuristics.endSearch();
					return score;
				}
				else
					return pvs<PLAYER + 1>(principalVariation, depthRemaining);
			}
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