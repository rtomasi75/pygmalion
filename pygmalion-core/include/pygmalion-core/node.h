namespace pygmalion
{
	template<typename SEARCH, typename DESCRIPTOR_SEARCH>
	class node
	{
	public:
		using searchType = SEARCH;
		using stackType = typename searchType::stackType;

		using descriptorSearch = DESCRIPTOR_SEARCH;
#include "include_search.h"

	private:
		stackType m_Stack;
		scoreType lateScore() const noexcept
		{
			const auto lateState{ evaluationType::lateResult(m_Stack) };
			assert(!gamestateType::isOpen(lateState));
			if (!gamestateType::isDraw(lateState))
				return evaluationType::neutralScore();
			else
				return evaluationType::lossScore(m_Stack.movingPlayer());
		}
		bool earlyScore(scoreType& score) const noexcept
		{
			const auto earlyState{ evaluationType::earlyResult(m_Stack) };
			if (!gamestateType::isOpen(earlyState))
			{
				if (gamestateType::isDraw(earlyState))
				{
					score = evaluationType::neutralScore();
					return true;
				}
				else
				{
					for (const playerType i : playerType::range)
					{
						if (gamestateType::isWin(earlyState, i))
						{
							score = evaluationType::winScore(i);
							return true;
						}
					}
					for (const playerType i : playerType::range)
					{
						if (gamestateType::isLoss(earlyState, i))
						{
							score = evaluationType::lossScore(i);
							return true;
						}
					}
					assert(false);
				}
			}
			return false;
		}
	public:
		scoreType eval(multiscoreType currentScore, const depthType depth, variationType& principalVariation, heuristicsType& heuristics) const noexcept
		{
			heuristics.beginNode(m_Stack.position());
			score early{ evaluationType::neutralScore() };
			if (earlyScore(early))
			{
				heuristics.endNodeEarly(m_Stack.position());
				return early;
			}
			const scoreType stand_pat{ evaluationType::evaluate(m_Stack) };
			const playerType movingPlayer{ m_Stack.movingPlayer() };
			if (currentScore.refuted(movingPlayer, stand_pat))
			{
				heuristics.endNodeLeaf(m_Stack.position());
				return stand_pat;
			}
			currentScore.accepted(movingPlayer, stand_pat);
			bool hasLegalMove{ false };
			moveType move;
			if (depth < countSearchPlies)
			{
				while (m_Stack.nextTacticalMove(move))
				{
					heuristics.beginMove(m_Stack.position(), move);
					hasLegalMove = true;
					variationType subVariation;
					currentScore.plyDown();
					scoreType sc{ scoreType::zero() };
					{
						node subnode(*this, move);
						sc = subnode.search(currentScore, -1, depth + 1, subVariation, heuristics);
					}
					evaluationType::plyUp(sc);
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
		scoreType search(multiscoreType currentScore, const depthType depthRemaining, const depthType depth, variationType& principalVariation, heuristicsType& heuristics) const noexcept
		{
			if ((depthRemaining >= 0) && (depth < countSearchPlies))
			{
				heuristics.beginNode(m_Stack.position());
				score early{ evaluationType::neutralScore() };
				if (earlyScore(early))
				{
					heuristics.endNodeEarly(m_Stack.position());
					return early;
				}
				const playerType movingPlayer{ m_Stack.movingPlayer() };
				bool hasLegalMove{ false };
				moveType move;
				while (m_Stack.nextMove(move))
				{
					heuristics.beginMove(m_Stack.position(), move);
					hasLegalMove = true;
					variationType subVariation;
					currentScore.plyDown();
					scoreType sc{ scoreType::zero() };
					{
						node subnode(*this, move);
						sc = subnode.search(currentScore, depthRemaining - 1, depth + 1, subVariation, heuristics);
					}
					evaluationType::plyUp(sc);
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
				heuristics.endNodeLate(m_Stack.position());
				if (hasLegalMove)
					return currentScore.score(movingPlayer);
				else
					return lateScore();
				return evaluationType::neutralScore();
			}
			else
				return eval(currentScore, depth, principalVariation, heuristics);
		}
		void perft(const depthType depthRemaining, const depthType depth, heuristicsType& heuristics) noexcept
		{
			heuristics.beginNode(m_Stack.position());
			if (!gamestateType::isOpen(evaluationType::earlyResult(m_Stack)))
			{
				heuristics.endNodeEarly(m_Stack.position());
				return;
			}
			if ((depthRemaining >= 0) && (depth < countSearchPlies))
			{
				movelistType moves;
				const playerType movingPlayer{ m_Stack.position().movingPlayer() };
				moveType move;
				while (m_Stack.nextMove(move))
				{
					node subnode{ node(*this,move) };
					subnode.perft(depthRemaining - 1, depth + 1, heuristics);
				}
				heuristics.endNodeLate(m_Stack.position());
			}
			else
				heuristics.endNodeLeaf(m_Stack.position());
		}
		node() = delete;
		constexpr node(const node&) = default;
		constexpr node(node&&) = default;
		constexpr node& operator=(const node&) = default;
		constexpr node(boardType& board) noexcept :
			m_Stack(board, board.movingPlayer())
		{

		}
		constexpr node(const node& parent, const moveType mv) noexcept :
			m_Stack(parent.m_Stack, mv)
		{
		}
		~node() noexcept = default;
	};
}