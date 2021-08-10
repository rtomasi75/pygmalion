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
		objectiveType lateScore() const noexcept
		{
			const gamestateType lateState{ evaluatorType::lateResult(m_Stack) };
			assert(!gamestateType::isOpen(lateState));
			if (gamestateType::isDraw(lateState))
			{
				return objectiveType::zero();
			}
			else
			{
				for (const playerType i : playerType::range)
				{
					if (gamestateType::isWin(lateState, i))
					{
						return  (i > 0) ? objectiveType::loss() : objectiveType::win();;
					}
				}
				for (const playerType i : playerType::range)
				{
					if (gamestateType::isLoss(lateState, i))
					{
						return (i > 0) ? objectiveType::win() : objectiveType::loss();
					}
				}
			}
			assert(false);
			return objectiveType::zero();
		}
		bool earlyScore(objectiveType& score) const noexcept
		{
			const gamestateType earlyState{ evaluatorType::earlyResult(m_Stack) };
			if (!gamestateType::isOpen(earlyState))
			{
				if (gamestateType::isDraw(earlyState))
				{
					score = objectiveType::zero();
					return true;
				}
				else
				{
					for (const playerType i : playerType::range)
					{
						if (gamestateType::isWin(earlyState, i))
						{
							score = (i > 0) ? objectiveType::loss() : objectiveType::win();
							return true;
						}
					}
					for (const playerType i : playerType::range)
					{
						if (gamestateType::isLoss(earlyState, i))
						{
							score = (i > 0) ? objectiveType::win() : objectiveType::loss();
							return true;
						}
					}
					assert(false);
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
		objectiveType eval(multiscoreType currentScore, const depthType depth, variationType& principalVariation, heuristicsType& heuristics, std::ostream& str) const noexcept
		{
			heuristics.beginNode(m_Stack.position());
			objectiveType early{ evaluatorType::neutralScore() };
			if (earlyScore(early))
			{
				heuristics.endNodeEarly(m_Stack.position());
				return early;
			}
			const objectiveType stand_pat{ evaluatorType::evaluate(currentScore,m_Stack) };
			const playerType movingPlayer{ m_Stack.movingPlayer() };
			if (currentScore.refuted(movingPlayer, stand_pat))
			{
				heuristics.endNodeLeaf(m_Stack.position());
				return stand_pat;
			}
			currentScore.accepted(movingPlayer, stand_pat);
			bool hasLegalMove{ false };
			movebitsType move;
			if (depth < countSearchPlies)
			{
				while (m_Stack.nextTacticalMove(move))
				{
					heuristics.beginMove(m_Stack.position(), move);
					hasLegalMove = true;
					variationType subVariation;
					currentScore.plyDown();
					objectiveType sc{ objectiveType::zero() };
					{
						node subnode(*this, move);
						sc = subnode.search<VERBOSE>(currentScore, -1, depth + 1, subVariation, heuristics, str);
					}
					sc = sc.plyUp();
					currentScore.plyUp();
					if (currentScore.refuted(movingPlayer, sc))
					{
						heuristics.endMoveRefuted(m_Stack.position(), move);
						heuristics.endNodeCut(m_Stack.position());
						return sc;
					}
					if (currentScore.accepted(movingPlayer, sc))
					{
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
				return currentScore.score(movingPlayer);
			else
				return lateScore();
		}
		template<bool VERBOSE>
		objectiveType search(multiscoreType currentScore, const depthType depthRemaining, const depthType depth, variationType& principalVariation, heuristicsType& heuristics, std::ostream& str) const noexcept
		{
			if ((depthRemaining >= 0) && (depth < countSearchPlies))
			{
				heuristics.beginNode(m_Stack.position());
				objectiveType early{ evaluatorType::neutralScore() };
				if (earlyScore(early))
				{
					heuristics.endNodeEarly(m_Stack.position());
					return early;
				}
				const playerType movingPlayer{ m_Stack.movingPlayer() };
				bool hasLegalMove{ false };
				movebitsType move;
				while (m_Stack.nextMove(move))
				{
					if constexpr (VERBOSE)
					{
						for (depthType d = 0; d < depth; d++)
							str << "      ";
						str << generatorType::moveToString(m_Stack, move);
					}
					heuristics.beginMove(m_Stack.position(), move);
					hasLegalMove = true;
					variationType subVariation;
					currentScore.plyDown();
					objectiveType sc{ objectiveType::zero() };
					{
						node subnode(*this, move);
						sc = subnode.search<VERBOSE>(currentScore, depthRemaining - 1, depth + 1, subVariation, heuristics, str);
					}
					sc = sc.plyUp();
					if constexpr (VERBOSE)
					{
						str << "  " << sc;
					}
					currentScore.plyUp();
					if (currentScore.refuted(movingPlayer, sc))
					{
						if constexpr (VERBOSE)
						{
							str << " REFUTED" << std::endl;
						}
						heuristics.endMoveRefuted(m_Stack.position(), move);
						heuristics.endNodeCut(m_Stack.position());
						return sc;
					}
					if (currentScore.accepted(movingPlayer, sc))
					{
						if constexpr (VERBOSE)
						{
							str << " ACCEPTED";
						}
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
				if (hasLegalMove)
				{
					return currentScore.score(movingPlayer);
				}
				else
				{
					return lateScore();
				}
				return evaluatorType::neutralScore();
			}
			else
				return this->template eval<VERBOSE>(currentScore, depth, principalVariation, heuristics, str);
		}
		node() = delete;
		constexpr node(const node&) = default;
		constexpr node(node&&) = default;
		constexpr node& operator=(const node&) = default;
		constexpr node(const stackType& stack) noexcept :
			m_Stack{ stack }
		{

		}
		constexpr node(const node& parent, const movebitsType moveBits) noexcept :
			m_Stack(parent.m_Stack, moveBits)
		{
		}
		~node() noexcept = default;
	};
}