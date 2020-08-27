namespace pygmalion
{
	template<typename SEARCH>
	class node
	{
	public:
		using searchType = SEARCH;
		using movegenType = typename searchType::movegenType;
		using movedataType = typename movegenType::movedataType;
		using evaluatorType = typename searchType::evaluatorType;
		using boardType = typename movegenType::boardType;
		using playerType = typename movegenType::playerType;
		using subjectiveType = typename searchType::subjectiveType;
		using objectiveType = typename searchType::objectiveType;
		using indexType = typename movegenType::indexType;
		using movelistType = typename movegenType::movelistType;
		using depthType = typename searchType::depthType;
		using variationType = typename searchType::variationType;
		using moveType = typename movegenType::moveType;
		using stackType = typename movegenType::stackType;
		using multiscoreType = typename searchType::multiscoreType;
		constexpr static size_t countPlayers{ boardType::countPlayers };
		constexpr static auto maxDepth{ searchType::maxDepth };
	private:
		stackType m_Stack;
		objectiveType lateScore() const noexcept
		{
			const auto lateState{ movegenType::lateResult(m_Stack) };
			assert(!boardType::isOpen(lateState));
			if (!boardType::isDraw(lateState))
				return evaluatorType::neutralScore();
			else
				return evaluatorType::lossScore(m_Stack.movingPlayer());
		}
		bool earlyScore(objectiveType& score) const noexcept
		{
			const auto earlyState{ movegenType::earlyResult(m_Stack) };
			if (!boardType::isOpen(earlyState))
			{
				if (boardType::isDraw(earlyState))
				{
					score = evaluatorType::neutralScore();
					return true;
				}
				else
				{
					for (const playerType i : playerType::range)
					{
						if (boardType::isWin(earlyState, i))
						{
							score = evaluatorType::winScore(i);
							return true;
						}
					}
					for (const playerType i : playerType::range)
					{
						if (boardType::isLoss(earlyState, i))
						{
							score = evaluatorType::lossScore(i);
							return true;
						}
					}
					assert(false);
				}
			}
			return false;
		}
	public:
		objectiveType eval(multiscoreType currentScore, const depthType depth, variationType& principalVariation, uint64_t& nodeCount) const noexcept
		{
			score early{ evaluatorType::neutralScore() };
			if (earlyScore(early))
				return early;
			const objectiveType stand_pat{ evaluatorType::evaluate(m_Stack) };
			const playerType movingPlayer{ m_Stack.movingPlayer() };
			if (currentScore.refuted(movingPlayer, stand_pat))
				return stand_pat;
			currentScore.accepted(movingPlayer, stand_pat);
			bool hasLegalMove{ false };
			moveType move;
			if (depth < maxDepth)
			{
				while (m_Stack.nextTacticalMove(move))
				{
					hasLegalMove = true;
					variationType subVariation;
					currentScore.plyDown();
					nodeCount++;
					node subnode(*this, move);
					objectiveType sc{ subnode.search(currentScore, -1, depth + 1, subVariation, nodeCount) };
					evaluatorType::plyUp(sc);
					currentScore.plyUp();
					if (currentScore.refuted(movingPlayer, sc))
						return sc;
					if (currentScore.accepted(movingPlayer, sc))
						principalVariation.combine(move, subVariation);
				}
			}
			if (!hasLegalMove)
				hasLegalMove = m_Stack.hasLegalMove();
			if (hasLegalMove)
				return currentScore.score(movingPlayer);
			else
				return lateScore();
		}
		objectiveType search(multiscoreType currentScore, const depthType depthRemaining, const depthType depth, variationType& principalVariation, uint64_t& nodeCount) const noexcept
		{
			if ((depthRemaining >= 0) && (depth < maxDepth))
			{
				score early{ evaluatorType::neutralScore() };
				if (earlyScore(early))
					return early;
				const playerType movingPlayer{ m_Stack.movingPlayer() };
				bool hasLegalMove{ false };
				moveType move;
				while (m_Stack.nextMove(move))
				{
					hasLegalMove = true;
					variationType subVariation;
					currentScore.plyDown();
					nodeCount++;
					node subnode(*this, move);
					objectiveType sc{ subnode.search(currentScore, depthRemaining - 1, depth + 1, subVariation, nodeCount) };
					evaluatorType::plyUp(sc);
					currentScore.plyUp();
					if (currentScore.refuted(movingPlayer, sc))
						return sc;
					if (currentScore.accepted(movingPlayer, sc))
						principalVariation.combine(move, subVariation);
				}
				if (hasLegalMove)
					return currentScore.score(movingPlayer);
				else
					return lateScore();
				return evaluatorType::neutralScore();
			}
			else
			{
				return eval(currentScore, depth, principalVariation, nodeCount);
			}
		}
		void perft(const depthType depthRemaining, const depthType depth, uint64_t& nodeCount) noexcept
		{
			if (!boardType::isOpen(movegenType::earlyResult(m_Stack)))
			{
				return;
			}
			if ((depthRemaining >= 0) && (depth < maxDepth))
			{
				movelistType moves;
				const playerType movingPlayer{ m_Stack.position().movingPlayer() };
				moveType move;
				while (m_Stack.nextMove(move))
				{
					nodeCount++;
					node subnode{ node(*this,move) };
					subnode.perft(depthRemaining - 1, depth + 1, nodeCount);
				}
			}
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