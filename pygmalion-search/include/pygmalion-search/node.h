namespace pygmalion
{
	template<typename DESCRIPTION_SEARCH>
	class node :
		public DESCRIPTION_SEARCH
	{
	public:
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"	
		using stackType = typename generatorType::stackType;
	private:
		stackType m_Stack;
		std::atomic_bool& m_IsRunning;
		scoreType lateScore() const noexcept
		{
			const gamestateType lateState{ evaluatorType::lateResult(m_Stack) };
			assert(!gamestateType::isOpen(lateState));
			if (gamestateType::isDraw(lateState))
			{
				return scoreType::zero();
			}
			else
			{
				return gamestateType::isWin(lateState, m_Stack.movingPlayer()) ? scoreType::win() : scoreType::loss();
			}
		}
		bool earlyScore(scoreType& score) const noexcept
		{
			const gamestateType earlyState{ evaluatorType::earlyResult(m_Stack) };
			if (!gamestateType::isOpen(earlyState))
			{
				if (gamestateType::isDraw(earlyState))
				{
					score = scoreType::zero();
					return true;
				}
				else
				{
					score = gamestateType::isWin(earlyState, m_Stack.movingPlayer()) ? scoreType::win() : scoreType::loss();
					return true;
				}
			}
			return false;
		}
	public:
		constexpr const stackType& stack() const noexcept
		{
			return m_Stack;
		}
		template<bool VERBOSE>
		scoreType eval(scoreType alpha, scoreType beta, const depthType depth, variationType& principalVariation, heuristicsType& heuristics, std::ostream& str) const noexcept
		{
			if (!m_IsRunning)
				return scoreType::zero();
			heuristics.beginNode(m_Stack.position());
			scoreType early{ scoreType::zero() };
			if (earlyScore(early))
			{
				heuristics.endNodeEarly(m_Stack.position());
				return early;
			}
			const scoreType stand_pat{ evaluatorType::evaluate(alpha, beta, m_Stack) };
			const playerType movingPlayer{ m_Stack.movingPlayer() };
			if (stand_pat >= beta)
			{
				heuristics.endNodeLeaf(m_Stack.position());
				return beta;
			}
			if (stand_pat > alpha)
				alpha = stand_pat;
			bool hasLegalMove{ false };
			movebitsType move;
			if (depth < countSearchPlies)
			{
				while (m_Stack.nextTacticalMove(move))
				{
					heuristics.beginMove(m_Stack.position(), move);
					hasLegalMove = true;
					variationType subVariation;
					node subnode(*this, move);
					const scoreType sc{ -subnode.search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), -1, depth + 1, subVariation, heuristics, str).plyUp() };
					if (sc >= beta)
					{
						heuristics.endMoveRefuted(m_Stack.position(), move);
						heuristics.endNodeCut(m_Stack.position());
						return beta;
					}
					if (sc > alpha)
					{
						alpha = sc;
						heuristics.endMoveAccepted(m_Stack.position(), move);
						principalVariation.combine(move, subVariation);
					}
					else
						heuristics.endMoveSilent(m_Stack.position(), move);
				}
			}
			heuristics.endNodeLate(m_Stack.position());
			if (!hasLegalMove)
				hasLegalMove = m_Stack.hasLegalMove();
			if (hasLegalMove)
				return alpha;
			else
				return lateScore();
		}
		template<bool VERBOSE>
		scoreType search(scoreType alpha, scoreType beta, const depthType depthRemaining, const depthType depth, variationType& principalVariation, heuristicsType& heuristics, std::ostream& str) const noexcept
		{
			if (!m_IsRunning)
				return scoreType::zero();
			scoreType bestScore{ scoreType::zero() };
			if ((depthRemaining >= 0) && (depth < countSearchPlies))
			{
				heuristics.beginNode(m_Stack.position());
				scoreType early{ scoreType::zero() };
				if (earlyScore(early))
				{
					heuristics.endNodeEarly(m_Stack.position());
					return early;
				}
				const playerType movingPlayer{ m_Stack.movingPlayer() };
				movebitsType move;
				const bool hasLegalMove{ m_Stack.nextMove(move) };
				scoreType best{ scoreType::zero() };
				if (hasLegalMove)
				{
					heuristics.beginMove(m_Stack.position(), move);
					variationType subVariation;
					node subnode(*this, move);
					const scoreType sc{ -subnode.search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), depthRemaining - 1, depth + 1, subVariation, heuristics, str).plyUp() };
					best = sc;
					if constexpr (VERBOSE)
					{
						str << "  " << sc;
					}
					if (best > alpha)
					{
						if (best >= beta)
						{
							if constexpr (VERBOSE)
							{
								str << " REFUTED" << std::endl;
							}
							heuristics.endMoveRefuted(m_Stack.position(), move);
							heuristics.endNodeCut(m_Stack.position());
							return best;
						}
						if constexpr (VERBOSE)
						{
							str << " ACCEPTED";
						}
						principalVariation.combine(move, subVariation);
						heuristics.endMoveAccepted(m_Stack.position(), move);
						alpha = best;
					}
					heuristics.endMoveSilent(m_Stack.position(), move);
					if constexpr (VERBOSE)
					{
						str << std::endl;
					}
				}
				else
				{
					heuristics.endNodeLate(m_Stack.position());
					return lateScore();
				}
				while (m_Stack.nextMove(move))
				{
					if constexpr (VERBOSE)
					{
						for (depthType d = 0; d < depth; d++)
							str << "      ";
						str << generatorType::moveToString(m_Stack, move);
					}
					heuristics.beginMove(m_Stack.position(), move);
					scoreType sc;
					variationType subVariation;
					{
						node zwsubnode(*this, move);
						sc = -zwsubnode.zwsearch<VERBOSE>(-alpha.plyDown(), depthRemaining - 1, depth + 1, heuristics, str).plyUp();
					}
					node subnode(*this, move);
					if (sc > alpha && sc < beta)
					{
						sc = -subnode.search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), depthRemaining - 1, depth + 1, subVariation, heuristics, str).plyUp();
						if (sc > alpha)
							alpha = sc;
					}
					if constexpr (VERBOSE)
					{
						str << "  " << sc;
					}
					if (sc > best)
					{
						if (sc >= beta)
						{
							if constexpr (VERBOSE)
							{
								str << " REFUTED" << std::endl;
							}
							heuristics.endMoveRefuted(m_Stack.position(), move);
							heuristics.endNodeCut(m_Stack.position());
							return sc;
						}
						if constexpr (VERBOSE)
						{
							str << " ACCEPTED";
						}
						best = sc;
						heuristics.endMoveAccepted(m_Stack.position(), move);
						principalVariation.combine(move, subVariation);
					}
					else
						heuristics.endMoveSilent(m_Stack.position(), move);
					if constexpr (VERBOSE)
					{
						str << std::endl;
					}
				}
				heuristics.endNodeLate(m_Stack.position());
				return alpha;
			}
			else
				return this->template eval<VERBOSE>(alpha, beta, depth, principalVariation, heuristics, str);
		}
		template<bool VERBOSE>
		scoreType zweval(scoreType beta, const depthType depth, heuristicsType& heuristics, std::ostream& str) const noexcept
		{
			if (!m_IsRunning)
				return scoreType::zero();
			scoreType alpha{ beta.zeroWindow() };
			heuristics.beginNode(m_Stack.position());
			scoreType early{ scoreType::zero() };
			if (earlyScore(early))
			{
				heuristics.endNodeEarly(m_Stack.position());
				return early;
			}
			const scoreType stand_pat{ evaluatorType::evaluate(alpha, beta, m_Stack) };
			const playerType movingPlayer{ m_Stack.movingPlayer() };
			if (stand_pat >= beta)
			{
				heuristics.endNodeLeaf(m_Stack.position());
				return beta;
			}
			if (stand_pat > alpha)
				alpha = stand_pat;
			bool hasLegalMove{ false };
			movebitsType move;
			if (depth < countSearchPlies)
			{
				while (m_Stack.nextTacticalMove(move))
				{
					heuristics.beginMove(m_Stack.position(), move);
					hasLegalMove = true;
					variationType subVariation;
					node subnode(*this, move);
					const scoreType sc{ -subnode.search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), -1, depth + 1, subVariation, heuristics, str).plyUp() };
					if (sc >= beta)
					{
						heuristics.endMoveRefuted(m_Stack.position(), move);
						heuristics.endNodeCut(m_Stack.position());
						return beta;
					}
					if (sc > alpha)
					{
						alpha = sc;
						heuristics.endMoveAccepted(m_Stack.position(), move);
					}
					else
						heuristics.endMoveSilent(m_Stack.position(), move);
				}
			}
			heuristics.endNodeLate(m_Stack.position());
			if (!hasLegalMove)
				hasLegalMove = m_Stack.hasLegalMove();
			if (hasLegalMove)
				return alpha;
			else
				return lateScore();
		}
		template<bool VERBOSE>
		scoreType zwsearch(scoreType beta, const depthType depthRemaining, const depthType depth, heuristicsType& heuristics, std::ostream& str) const noexcept
		{
			if (!m_IsRunning)
				return scoreType::zero();
			scoreType alpha{ beta.zeroWindow() };
			scoreType bestScore{ scoreType::zero() };
			if ((depthRemaining >= 0) && (depth < countSearchPlies))
			{
				heuristics.beginNode(m_Stack.position());
				scoreType early{ scoreType::zero() };
				if (earlyScore(early))
				{
					heuristics.endNodeEarly(m_Stack.position());
					return early;
				}
				const playerType movingPlayer{ m_Stack.movingPlayer() };
				movebitsType move;
				const bool hasLegalMove{ m_Stack.nextMove(move) };
				scoreType best{ scoreType::zero() };
				if (hasLegalMove)
				{
					heuristics.beginMove(m_Stack.position(), move);
					variationType subVariation;
					node subnode(*this, move);
					const scoreType sc{ -subnode.search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), depthRemaining - 1, depth + 1, subVariation, heuristics, str).plyUp() };
					best = sc;
					if constexpr (VERBOSE)
					{
						str << "  " << sc;
					}
					if (best > alpha)
					{
						if (best >= beta)
						{
							if constexpr (VERBOSE)
							{
								str << " REFUTED" << std::endl;
							}
							heuristics.endMoveRefuted(m_Stack.position(), move);
							heuristics.endNodeCut(m_Stack.position());
							return best;
						}
						if constexpr (VERBOSE)
						{
							str << " ACCEPTED";
						}
						heuristics.endMoveAccepted(m_Stack.position(), move);
						alpha = best;
					}
					heuristics.endMoveSilent(m_Stack.position(), move);
					if constexpr (VERBOSE)
					{
						str << std::endl;
					}
				}
				else
				{
					heuristics.endNodeLate(m_Stack.position());
					return lateScore();
				}
				while (m_Stack.nextMove(move))
				{
					if constexpr (VERBOSE)
					{
						for (depthType d = 0; d < depth; d++)
							str << "      ";
						str << generatorType::moveToString(m_Stack, move);
					}
					heuristics.beginMove(m_Stack.position(), move);
					variationType zwsubVariation;
					scoreType sc;
					variationType subVariation;
					{
						node zwsubnode(*this, move);
						sc = -zwsubnode.search<VERBOSE>(-alpha.plyDown() - scoreType::atom(), -alpha.plyDown(), depthRemaining - 1, depth + 1, zwsubVariation, heuristics, str).plyUp();
					}
					node subnode(*this, move);
					if (sc > alpha && sc < beta)
					{
						sc = -subnode.search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), depthRemaining - 1, depth + 1, subVariation, heuristics, str).plyUp();
						if (sc > alpha)
							alpha = sc;
					}
					if constexpr (VERBOSE)
					{
						str << "  " << sc;
					}
					if (sc > best)
					{
						if (sc >= beta)
						{
							if constexpr (VERBOSE)
							{
								str << " REFUTED" << std::endl;
							}
							heuristics.endMoveRefuted(m_Stack.position(), move);
							heuristics.endNodeCut(m_Stack.position());
							return sc;
						}
						if constexpr (VERBOSE)
						{
							str << " ACCEPTED";
						}
						best = sc;
						heuristics.endMoveAccepted(m_Stack.position(), move);
					}
					else
						heuristics.endMoveSilent(m_Stack.position(), move);
					if constexpr (VERBOSE)
					{
						str << std::endl;
					}
				}
				heuristics.endNodeLate(m_Stack.position());
				return alpha;
			}
			else
			{
				return this->template zweval<VERBOSE>(beta, depth, heuristics, str);
			}
		}
		node() = delete;
		constexpr node(const node&) = default;
		constexpr node(node&&) = default;
		constexpr node& operator=(const node&) = default;
		constexpr node(const stackType& stack, std::atomic_bool& isRunning) noexcept :
			m_Stack{ stack },
			m_IsRunning{ isRunning }
		{

		}
		constexpr node(const node& parent, const movebitsType moveBits) noexcept :
			m_Stack(parent.m_Stack, moveBits),
			m_IsRunning{ parent.m_IsRunning }
		{
		}
		~node() noexcept = default;
	};
}