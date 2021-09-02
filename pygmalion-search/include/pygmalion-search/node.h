namespace pygmalion
{
	template<typename DESCRIPTION_SEARCH, typename INSTANCE>
	class node :
		public DESCRIPTION_SEARCH
	{
	public:
		using nodeType = INSTANCE;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"	
		using stackType = typename generatorType::stackType;
	private:
		constexpr static inline bool allowLightPollution{ true };
		stackType m_Stack;
		heuristicsType& m_Heuristics;
		movelistType m_MovesTT;
		movelistType m_MovesKiller;
		movelistType m_Moves;
		movelistType m_TacticalMovesTT;
		movelistType m_TacticalMovesKiller;
		movelistType m_TacticalMoves;
		int m_MoveGeneratorStage;
		int m_TacticalMoveGeneratorStage;
		bool m_NeedsSorting;
		bool m_NeedsTacticalSorting;
		std::atomic_bool& m_IsRunning;
		indexType m_MoveTT;
		indexType m_MoveKiller;
		indexType m_TacticalMoveTT;
		indexType m_TacticalMoveKiller;
		indexType m_Move;
		indexType m_TacticalMove;
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
		template<bool LAZY>
		bool earlyScore(scoreType& score, bool& allowStoreTT) const noexcept
		{
			const gamestateType earlyState{ evaluatorType::template earlyResult<LAZY>(m_Stack,allowStoreTT) };
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
		constexpr void resetMoveGen()
		{
			m_Move = 0;
			m_TacticalMove = 0;
			m_MoveGeneratorStage = -1;
			m_MovesTT.clear();
			m_MovesKiller.clear();
			m_TacticalMoveGeneratorStage = -1;
			m_TacticalMovesTT.clear();
			m_TacticalMovesKiller.clear();
			m_NeedsSorting = true;
			m_NeedsTacticalSorting = true;
		}
		constexpr bool nextMove(const depthType depthRemaining, const size_t depth, movebitsType& movebits, bool& fromStack) noexcept
		{
			fromStack = false;
			if (m_MoveGeneratorStage < 0)
			{
				m_MoveGeneratorStage = 0;
				m_Heuristics.transpositionTable().probeMoves(m_Stack, depthRemaining, m_MovesTT);
				m_MoveTT = 0;
			}
			if (m_MoveGeneratorStage == 0)
			{
				while (m_MoveTT < m_MovesTT.length())
				{
					movebits = m_MovesTT[m_MoveTT];
					m_MoveTT++;
					return true;
				}
				m_MoveGeneratorStage = 1;
				m_Heuristics.killers(m_Stack, depth, m_MovesKiller);
				m_MoveKiller = 0;
			}
			if (m_MoveGeneratorStage == 1)
			{
				while (m_MoveKiller < m_MovesKiller.length())
				{
					movebits = m_MovesKiller[m_MoveKiller];
					bool bDouble{ m_MovesTT.contains(movebits) };
					m_MoveKiller++;
					if (!bDouble)
					{
						return true;
					}
				}
				m_MoveGeneratorStage = 2;
				m_Heuristics.tacticalKillers(m_Stack, depth, m_TacticalMovesKiller);
				m_TacticalMoveKiller = 0;
			}
			if (m_MoveGeneratorStage == 2)
			{
				while (m_TacticalMoveKiller < m_TacticalMovesKiller.length())
				{
					movebits = m_TacticalMovesKiller[m_TacticalMoveKiller];
					bool bDouble{ m_MovesTT.contains(movebits) };
					m_TacticalMoveKiller++;
					if (!bDouble)
					{
						return true;
					}
				}
				m_MoveGeneratorStage = 3;
			}
			if constexpr (heuristicMoves)
			{
				if (m_NeedsSorting)
				{
					m_Heuristics.sortMoves(m_Stack.position(), m_Moves, m_Move, depth);
					m_NeedsSorting = false;
				}
			}
			while (m_Move < m_Moves.length())
			{
				movebits = m_Moves[m_Move];
				bool bDouble{ m_MovesTT.contains(movebits) || m_MovesKiller.contains(movebits) };
				m_Move++;
				if (!bDouble)
				{
					return true;
				}
			}
			movebitsType testBits{ movebitsType(0) };
			if constexpr (heuristicMoves)
			{
				while (m_Stack.nextMove(testBits, depth, m_Heuristics.feedback(), [this, depth](const movebitsType& bits) { return this->m_Heuristics.moveScore(this->m_Stack.position(), bits, depth); }))
				{
					bool bDouble{ m_MovesTT.contains(testBits) || m_MovesKiller.contains(testBits) };
					if (!bDouble)
					{
						fromStack = true;
						movebits = testBits;
						m_Moves.add(movebits);
						m_Move++;
						return true;
					}
				}
			}
			else
			{
				while (m_Stack.nextMove(testBits, depth, m_Heuristics.feedback()))
				{
					bool bDouble{ m_MovesTT.contains(testBits) || m_MovesKiller.contains(testBits) };
					if (!bDouble)
					{
						fromStack = true;
						movebits = testBits;
						m_Moves.add(movebits);
						m_Move++;
						return true;
					}
				}
			}
			return false;
		}
		constexpr bool nextTacticalMove(const size_t depth, movebitsType& movebits, bool& fromStack) noexcept
		{
			fromStack = false;
			if (m_TacticalMoveGeneratorStage < 0)
			{
				m_TacticalMoveGeneratorStage = 0;
				m_Heuristics.transpositionTable().probeTacticalMoves(m_Stack, m_TacticalMovesTT);
				m_TacticalMoveTT = 0;
			}
			if (m_TacticalMoveGeneratorStage == 0)
			{
				while (m_TacticalMoveTT < m_TacticalMovesTT.length())
				{
					movebits = m_TacticalMovesTT[m_TacticalMoveTT];
					m_TacticalMoveTT++;
					m_TacticalMoves.add(movebits);
					m_TacticalMove++;
					return true;
				}
				m_TacticalMoveGeneratorStage = 1;
				m_Heuristics.tacticalKillers(m_Stack, depth, m_TacticalMovesKiller);
				m_TacticalMoveKiller = 0;
			}
			if (m_MoveGeneratorStage == 1)
			{
				while (m_TacticalMoveKiller < m_TacticalMovesKiller.length())
				{
					movebits = m_TacticalMovesKiller[m_TacticalMoveKiller];
					bool bDouble{ m_MovesTT.contains(movebits) };
					m_TacticalMoveKiller++;
					if (!bDouble)
					{
						return true;
					}
				}
				m_MoveGeneratorStage = 2;
			}
			if constexpr (heuristicMoves)
			{
				if (m_NeedsTacticalSorting)
				{
					m_Heuristics.sortMoves(m_Stack.position(), m_TacticalMoves, m_TacticalMove, depth);
					m_NeedsTacticalSorting = false;
				}
			}
			while (m_TacticalMove < m_TacticalMoves.length())
			{
				movebits = m_TacticalMoves[m_TacticalMove];
				bool bDouble{ m_TacticalMovesTT.contains(movebits) };
				m_TacticalMove++;
				if (!bDouble)
				{
					return true;
				}
			}
			movebitsType testBits{ movebitsType(0) };
			if constexpr (heuristicMoves)
			{
				while (m_Stack.nextTacticalMove(testBits, depth, m_Heuristics.feedback(), [this, depth](const movebitsType& bits) { return this->m_Heuristics.moveScore(this->m_Stack.position(), bits, depth); }))
				{
					bool bDouble{ m_TacticalMovesTT.contains(testBits) };
					if (!bDouble)
					{
						fromStack = true;
						movebits = testBits;
						m_TacticalMoves.add(testBits);
						m_TacticalMove++;
						return true;
					}
				}
			}
			else
			{
				while (m_Stack.nextTacticalMove(testBits, depth, m_Heuristics.feedback()))
				{
					bool bDouble{ m_TacticalMovesTT.contains(testBits) };
					if (!bDouble)
					{
						fromStack = true;
						movebits = testBits;
						m_TacticalMoves.add(testBits);
						m_TacticalMove++;
						return true;
					}
				}
			}
			return false;
		}
		constexpr static scoreType createAspiration(const scoreType sc, const scoreType window) noexcept
		{
			if (sc.isOpen())
				return sc + window;
			else
				return sc;
		}
		template<bool VERBOSE, bool LONGPV>
		constexpr scoreType searchMove(const movebitsType move, const scoreType alpha, const scoreType beta, const depthType depthRemaining, const size_t depth, variationType& principalVariation, std::ostream& str, bool& allowStoreTT) const noexcept
		{
			if constexpr (searchIterativeDeepening)
			{
				scoreType sc{ scoreType::zero() };
				node subnode(*this, move);
				if (depthRemaining >= 0)
				{
					sc = -subnode.search<VERBOSE, false>(-beta.plyDown(), -alpha.plyDown(), depthType(-1), depth + 1, principalVariation, str, allowStoreTT).plyUp();
					for (depthType d = 0; d < depthRemaining; d++)
					{
						if constexpr (searchAspiration)
						{
							bool bExact{ false };
							bool bLow{ true };
							bool bHigh{ true };
							scoreType lowAspiration{ sc };
							scoreType highAspiration{ sc };
							for (size_t i = 0; i < evaluatorType::countAspirationWindows(); i++)
							{
								lowAspiration = scoreType::max(alpha, bLow ? createAspiration(scoreType::min(sc, lowAspiration), -evaluatorType::aspirationWindowSize(i)) : lowAspiration);
								highAspiration = scoreType::min(beta, bHigh ? createAspiration(scoreType::max(sc, highAspiration), evaluatorType::aspirationWindowSize(i)) : highAspiration);
								if (lowAspiration.isLosing())
									lowAspiration = scoreType::minimum();
								if (highAspiration.isWinning())
									highAspiration = scoreType::maximum();
								if (d < depthRemaining - 1)
									sc = -subnode.search<VERBOSE, false>(-highAspiration.plyDown(), -lowAspiration.plyDown(), d, depth + 1, principalVariation, str, allowStoreTT).plyUp();
								else
									sc = -subnode.search<VERBOSE, LONGPV>(-highAspiration.plyDown(), -lowAspiration.plyDown(), d, depth + 1, principalVariation, str, allowStoreTT).plyUp();
								if ((sc > lowAspiration) && (sc < highAspiration))
								{
									bExact = true;
									break;
								}
								if (sc <= alpha)
								{
									bExact = true;
									break;
								}
								if (sc >= beta)
								{
									bExact = true;
									break;
								}
								if (sc <= lowAspiration)
									bLow = true;
								else
									bLow = false;
								if (sc >= highAspiration)
									bHigh = true;
								else
									bHigh = false;
							}
							if (!bExact)
							{
								if (d < depthRemaining - 1)
									sc = -subnode.search<VERBOSE, false>(-beta.plyDown(), -alpha.plyDown(), d, depth + 1, principalVariation, str, allowStoreTT).plyUp();
								else
									sc = -subnode.search<VERBOSE, LONGPV>(-beta.plyDown(), -alpha.plyDown(), d, depth + 1, principalVariation, str, allowStoreTT).plyUp();
							}
						}
						else
						{
							if (d < depthRemaining - 1)
								sc = -subnode.search<VERBOSE, false>(-beta.plyDown(), -alpha.plyDown(), d, depth + 1, principalVariation, str, allowStoreTT).plyUp();
							else
								sc = -subnode.search<VERBOSE, LONGPV>(-beta.plyDown(), -alpha.plyDown(), d, depth + 1, principalVariation, str, allowStoreTT).plyUp();
						}
					}
				}
				else
					sc = -subnode.search<VERBOSE, LONGPV>(-beta.plyDown(), -alpha.plyDown(), depthType(-1), depth + 1, principalVariation, str, allowStoreTT).plyUp();
				return sc;
			}
			else
			{
				node subnode(*this, move);
				return -subnode.search<VERBOSE, LONGPV>(-beta.plyDown(), -alpha.plyDown(), depthRemaining - depthType(1), depth + 1, principalVariation, str, allowStoreTT).plyUp();
			}
		}
		template<bool VERBOSE>
		constexpr scoreType zwsearchMove(const movebitsType move, const scoreType alpha, const depthType depthRemaining, const size_t depth, const uint_t<countPlayers, false> nullMoveHistory, std::ostream& str, bool& allowStoreTT) const noexcept
		{
			node subnode(*this, move);
			return -subnode.zwsearch<VERBOSE>(-alpha.plyDown(), depthRemaining - depthType(1), depth + 1, noNullMove(nullMoveHistory), str, allowStoreTT).plyUp();
		}
		template<bool VERBOSE, bool LONGPV, bool SCOUT>
		constexpr bool searchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const depthType depthRemaining, const size_t depth, variationType& principalVariation, std::ostream& str, const bool fromStack, bool& allowStoreTT) const noexcept
		{
			if constexpr (VERBOSE)
			{
				str << std::endl;
				for (depthType d = 0; d < depth; d++)
					str << " ";
				str << std::setw(6) << std::left << generatorType::moveToString(m_Stack, move, depth);
			}
			m_Heuristics.beginMove(m_Stack, move, false, depth);
			variationType subVariation;
			if constexpr (SCOUT)
			{
				bool bEnded{ false };
				scoreType sc{ scoreType::zero() };
				bool allowStoreTTsubnode{ true };
				if constexpr (searchScout)
				{
					sc = this->zwsearchMove<VERBOSE>(move, alpha, depthRemaining, depth, m_EmptyNullMoveHistory, str, allowStoreTTsubnode);
					if (sc > alpha && sc < beta)
					{
						sc = this->searchMove<VERBOSE, LONGPV>(move, alpha, beta, depthRemaining, depth, subVariation, str, allowStoreTTsubnode);
						if (sc > alpha)
						{
							alpha = sc;
							allowStoreTT &= allowStoreTTsubnode;
							if constexpr (searchTranspositionTable)
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
							bEnded = true;
						}
					}
				}
				else
				{
					sc = this->searchMove<VERBOSE, LONGPV>(move, alpha, beta, depthRemaining, depth, subVariation, str, allowStoreTTsubnode);
					if (sc > alpha && sc < beta)
					{
						if (sc > alpha)
						{
							alpha = sc;
							allowStoreTT &= allowStoreTTsubnode;
							if constexpr (searchTranspositionTable)
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
							bEnded = true;
						}
					}
				}
				if constexpr (VERBOSE)
				{
					str << "  " << sc;
				}
				if (sc > best)
				{
					allowStoreTT &= allowStoreTTsubnode;
					best = sc;
					if (sc >= beta)
					{
						if constexpr (VERBOSE)
						{
							str << " REFUTED" << std::endl;
						}
						if constexpr (failSoft)
						{
							if constexpr (searchTranspositionTable)
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							m_Heuristics.endMoveRefuted(m_Stack, move, false, depth, best, fromStack);
							m_Heuristics.endNodeCut(m_Stack);
							return true;
						}
						else
						{
							if constexpr (searchTranspositionTable)
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, beta, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							m_Heuristics.endMoveRefuted(m_Stack, move, false, depth, beta, fromStack);
							m_Heuristics.endNodeCut(m_Stack);
							return true;
						}
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED" << std::endl;
					}
					principalVariation.combine(move, subVariation);
					bestmove = move;
				}
				if (!bEnded)
					m_Heuristics.endMoveSilent(m_Stack, move, false, depth);
				else
					m_Heuristics.endMoveAccepted(m_Stack, move, false, depth, alpha, fromStack);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
			else
			{
				bool allowStoreTTsubnode{ true };
				const scoreType sc{ this->searchMove<VERBOSE,LONGPV>(move, alpha, beta, depthRemaining, depth, subVariation, str, allowStoreTTsubnode) };
				if constexpr (VERBOSE)
				{
					for (depthType d = 0; d < depth; d++)
						str << " ";
					str << std::setw(6) << std::left << "->";
				}
				best = sc;
				if constexpr (VERBOSE)
				{
					str << "  " << best;
				}
				if (best > alpha)
				{
					allowStoreTT &= allowStoreTTsubnode;
					if (best >= beta)
					{
						if constexpr (VERBOSE)
						{
							str << " REFUTED" << std::endl;
						}
						m_Heuristics.endNodeCut(m_Stack);
						if constexpr (failSoft)
						{
							if constexpr (searchTranspositionTable)
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							m_Heuristics.endMoveRefuted(m_Stack, move, false, depth, best, fromStack);
							return true;
						}
						else
						{
							if constexpr (searchTranspositionTable)
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, beta, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							m_Heuristics.endMoveRefuted(m_Stack, move, false, depth, beta, fromStack);
							return true;
						}
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED" << std::endl;
					}
					principalVariation.combine(move, subVariation);
					alpha = best;
					bestmove = move;
					if constexpr (searchTranspositionTable)
						if (allowStoreTT)
							m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
					m_Heuristics.endMoveAccepted(m_Stack, move, false, depth, best, fromStack);
				}
				else
					m_Heuristics.endMoveSilent(m_Stack, move, false, depth);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
		}
		template<bool VERBOSE, bool SCOUT>
		constexpr bool zwsearchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const depthType depthRemaining, const size_t depth, const uint_t<countPlayers, false> nullMoveHistory, std::ostream& str, const bool fromStack, bool& allowStoreTT) const noexcept
		{
			if constexpr (VERBOSE)
			{
				for (depthType d = 0; d < depth; d++)
					str << " ";
				str << std::setw(6) << generatorType::moveToString(m_Stack, move, depth);
			}
			m_Heuristics.beginMove(m_Stack, move, false, depth);
			if constexpr (SCOUT)
			{
				bool allowStoreTTsubnode{ true };
				bool bEnded{ false };
				const scoreType sc{ zwsearchMove<VERBOSE>(move, alpha, depthRemaining, depth, noNullMove(nullMoveHistory), str, allowStoreTTsubnode) };
				if constexpr (VERBOSE)
				{
					str << "  " << sc;
				}
				if (sc > best)
				{
					best = sc;
					allowStoreTT &= allowStoreTTsubnode;
					if (sc >= beta)
					{
						if constexpr (VERBOSE)
						{
							str << " REFUTED" << std::endl;
						}
						if (failSoft)
						{
							if constexpr (searchTranspositionTable)
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							m_Heuristics.endMoveRefuted(m_Stack, move, false, depth, best, fromStack);
							m_Heuristics.endNodeCut(m_Stack);
							return true;
						}
						else
						{
							if constexpr (searchTranspositionTable)
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, beta, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							m_Heuristics.endMoveRefuted(m_Stack, move, false, depth, beta, fromStack);
							m_Heuristics.endNodeCut(m_Stack);
							return true;
						}
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED" << std::endl;
					}
					bestmove = move;
				}
				if (!bEnded)
					m_Heuristics.endMoveSilent(m_Stack, move, false, depth);
				else
					m_Heuristics.endMoveAccepted(m_Stack, move, false, depth, sc, fromStack);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
			else
			{
				bool allowStoreTTsubnode{ true };
				const scoreType sc{ zwsearchMove<VERBOSE>(move, alpha, depthRemaining, depth, noNullMove(nullMoveHistory), str, allowStoreTTsubnode) };
				best = sc;
				if constexpr (VERBOSE)
				{
					str << "  " << best;
				}
				if (best >= beta)
				{
					allowStoreTT &= allowStoreTTsubnode;
					if constexpr (VERBOSE)
					{
						str << " REFUTED" << std::endl;
					}
					if constexpr (failSoft)
					{
						if constexpr (searchTranspositionTable)
							if (allowStoreTT)
								m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						m_Heuristics.endMoveRefuted(m_Stack, move, false, depth, best, fromStack);
						m_Heuristics.endNodeCut(m_Stack);
						return true;
					}
					else
					{
						if constexpr (searchTranspositionTable)
							if (allowStoreTT)
								m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, beta, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						m_Heuristics.endMoveRefuted(m_Stack, move, false, depth, best, fromStack);
						m_Heuristics.endNodeCut(m_Stack);
						return true;
					}
				}
				else
					m_Heuristics.endMoveSilent(m_Stack, move, false, depth);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
		}
		template<bool VERBOSE, bool USE_TT, bool SCOUT>
		constexpr bool qsearchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const size_t depth, variationType& principalVariation, std::ostream& str, const bool fromStack, bool& allowStoreTT) const noexcept
		{
			if constexpr (VERBOSE)
			{
				str << std::endl;
				for (depthType d = 0; d < depth; d++)
					str << " ";
				str << std::setw(6) << generatorType::moveToString(m_Stack, move, depth);
			}
			m_Heuristics.beginMove(m_Stack, move, true, depth);
			variationType subVariation;
			if constexpr (SCOUT)
			{
				bool allowStoreTTsubnode{ true };
				bool bEnded{ false };
				scoreType sc{ scoreType::zero() };
				{
					node subnode(*this, move);
					sc = -subnode.eval<VERBOSE, USE_TT>(-beta.plyDown(), -alpha.plyDown(), depth + 1, subVariation, str, allowStoreTTsubnode).plyUp();
				}
				if (sc > alpha && sc < beta)
				{
					if (sc > alpha)
					{
						alpha = sc;
						allowStoreTT &= allowStoreTTsubnode;
						if constexpr (USE_TT)
							if (allowStoreTT)
								m_Heuristics.transpositionTable().store(m_Stack, -1, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
						bEnded = true;
					}
				}
				if constexpr (VERBOSE)
				{
					str << "  " << sc;
				}
				if (sc > best)
				{
					allowStoreTT &= allowStoreTTsubnode;
					best = sc;
					if (sc >= beta)
					{
						if constexpr (VERBOSE)
						{
							str << " REFUTED" << std::endl;
						}
						if constexpr (failSoft)
						{
							if constexpr (USE_TT)
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							m_Heuristics.endMoveRefuted(m_Stack, move, true, depth, best, fromStack);
							m_Heuristics.endNodeCut(m_Stack);
							return true;
						}
						else
						{
							if constexpr (USE_TT)
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, -1, beta, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							m_Heuristics.endMoveRefuted(m_Stack, move, true, depth, beta, fromStack);
							m_Heuristics.endNodeCut(m_Stack);
							return true;
						}
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED" << std::endl;
					}
					principalVariation.combine(move, subVariation);
					bestmove = move;
				}
				if (!bEnded)
					m_Heuristics.endMoveSilent(m_Stack, move, false, depth);
				else
					m_Heuristics.endMoveAccepted(m_Stack, move, false, depth, alpha, fromStack);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
			else
			{
				bool allowStoreTTsubnode{ true };
				{
					node subnode(*this, move);
					const scoreType sc{ -subnode.eval<VERBOSE,USE_TT>(-beta.plyDown(), -alpha.plyDown(), depth + 1, subVariation, str, allowStoreTTsubnode).plyUp() };
					best = sc;
				}
				if constexpr (VERBOSE)
				{
					str << "  " << best;
				}
				if (best > alpha)
				{
					allowStoreTT &= allowStoreTTsubnode;
					if (best >= beta)
					{
						if constexpr (VERBOSE)
						{
							str << " REFUTED" << std::endl;
						}
						if constexpr (failSoft)
						{
							if constexpr (USE_TT)
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							m_Heuristics.endMoveRefuted(m_Stack, move, true, depth, best, fromStack);
							m_Heuristics.endNodeCut(m_Stack);
							return true;
						}
						else
						{
							if constexpr (USE_TT)
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, -1, beta, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							m_Heuristics.endMoveRefuted(m_Stack, move, true, depth, beta, fromStack);
							m_Heuristics.endNodeCut(m_Stack);
							return true;
						}
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED" << std::endl;
					}
					principalVariation.combine(move, subVariation);
					bestmove = move;
					alpha = best;
					if constexpr (USE_TT)
						if (allowStoreTT)
							m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
					m_Heuristics.endMoveAccepted(m_Stack, move, true, depth, best, fromStack);
				}
				else
					m_Heuristics.endMoveSilent(m_Stack, move, true, depth);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
		}
		template<bool VERBOSE, bool USE_TT, bool SCOUT>
		constexpr bool qzwsearchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const size_t depth, std::ostream& str, const bool fromStack, bool& allowStoreTT) const noexcept
		{
			if constexpr (VERBOSE)
			{
				for (depthType d = 0; d < depth; d++)
					str << " ";
				str << std::setw(6) << generatorType::moveToString(m_Stack, move, depth);
			}
			m_Heuristics.beginMove(m_Stack, move, true, depth);
			if constexpr (SCOUT)
			{
				bool allowStoreTTsubnode{ true };
				scoreType sc{ scoreType::zero() };
				{
					node subnode(*this, move);
					sc = -subnode.zweval<VERBOSE, USE_TT>(-alpha.plyDown(), depth + 1, str, allowStoreTTsubnode).plyUp();
				}
				if constexpr (VERBOSE)
				{
					str << "  " << sc;
				}
				if (sc >= beta)
				{
					if constexpr (VERBOSE)
					{
						str << " REFUTED" << std::endl;
					}
					allowStoreTT &= allowStoreTTsubnode;
					best = sc;
					if constexpr (failSoft)
					{
						if constexpr (USE_TT)
							if (allowStoreTT)
								m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						m_Heuristics.endMoveRefuted(m_Stack, move, true, depth, best, fromStack);
						m_Heuristics.endNodeCut(m_Stack);
						return true;
					}
					else
					{
						if constexpr (USE_TT)
							if (allowStoreTT)
								m_Heuristics.transpositionTable().store(m_Stack, -1, beta, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						m_Heuristics.endMoveRefuted(m_Stack, move, true, depth, beta, fromStack);
						m_Heuristics.endNodeCut(m_Stack);
						return true;
					}
				}
				m_Heuristics.endMoveSilent(m_Stack, move, false, depth);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
			else
			{
				bool allowStoreTTsubnode{ true };
				{
					node subnode(*this, move);
					const scoreType sc{ -subnode.zweval<VERBOSE,USE_TT>(-alpha.plyDown(), depth + 1, str, allowStoreTTsubnode).plyUp() };
					best = sc;
				}
				if constexpr (VERBOSE)
				{
					str << "  " << best;
				}
				if (best >= beta)
				{
					if constexpr (VERBOSE)
					{
						str << " REFUTED" << std::endl;
					}
					allowStoreTT &= allowStoreTTsubnode;
					if constexpr (failSoft)
					{
						if constexpr (USE_TT)
							if (allowStoreTT)
								m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						m_Heuristics.endMoveRefuted(m_Stack, move, true, depth, best, fromStack);
						m_Heuristics.endNodeCut(m_Stack);
						return true;
					}
					else
					{
						if constexpr (USE_TT)
							if (allowStoreTT)
								m_Heuristics.transpositionTable().store(m_Stack, -1, beta, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						m_Heuristics.endMoveRefuted(m_Stack, move, true, depth, beta, fromStack);
						m_Heuristics.endNodeCut(m_Stack);
						return true;
					}
				}
				else
					m_Heuristics.endMoveSilent(m_Stack, move, true, depth);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
		}
		constexpr static uint_t<countPlayers, false> noNullMove(const uint_t<countPlayers, false> nullMoveHistory) noexcept
		{
			return nullMoveHistory << 1;
		}
		constexpr static uint_t<countPlayers, false> doNullMove(uint_t<countPlayers, false> nullMoveHistory) noexcept
		{
			nullMoveHistory <<= 1;
			nullMoveHistory[0] = true;
			return nullMoveHistory;
		}
		constexpr static bool checkNullMove(const uint_t<countPlayers, false> nullMoveHistory) noexcept
		{
			return !nullMoveHistory[countPlayers - 1];
		}
		constexpr static inline uint_t<countPlayers, false> m_EmptyNullMoveHistory{ uint_t<countPlayers, false>(0) };
	public:
		constexpr static depthType nullMoveReduction(const size_t depthRemaining) noexcept
		{
			return nodeType::nullMoveReduction_Implementation(depthRemaining);
		}
		constexpr static bool nullMoveAllowed(const stackType& stack) noexcept
		{
			return nodeType::nullMoveAllowed_Implementation(stack);
		}
		constexpr const stackType& stack() const noexcept
		{
			return m_Stack;
		}
		template<bool VERBOSE, bool USE_TT>
		scoreType eval(scoreType alpha, scoreType beta, const size_t depth, variationType& principalVariation, std::ostream& str, bool& allowStoreTT) noexcept
		{
			if (!m_IsRunning)
			{
				allowStoreTT = false;
				return scoreType::zero();
			}
			m_Heuristics.beginNode(m_Stack);
			scoreType early{ scoreType::zero() };
			if (earlyScore<true>(early, allowStoreTT))
			{
				m_Heuristics.endNodeEarly(m_Stack);
				return early;
			}
			movebitsType bestmove;
			bool hasLegalMove{ false };
			movebitsType move;
			scoreType best{ scoreType::minimum() };
			const playerType movingPlayer{ m_Stack.movingPlayer() };
			const scoreType stand_pat{ evaluatorType::evaluate(alpha, beta, m_Stack) };
			if constexpr (VERBOSE)
			{
				str << "  " << stand_pat;
			}
			if constexpr (failSoft)
				best = scoreType::max(stand_pat, best);
			else
				best = scoreType::max(scoreType::min(stand_pat, beta), best);
			if (best > alpha)
			{
				if (best >= beta)
				{
					m_Heuristics.endNodeLeaf(m_Stack);
					if constexpr (failSoft)
					{
						if constexpr (USE_TT)
							m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), best, transpositiontable<descriptorSearch>::flags_lower, movebitsType(0));
						if constexpr (VERBOSE)
						{
							str << std::endl;
							for (depthType d = 0; d < depth; d++)
								str << " ";
							str << std::setw(6) << "<ev>";
							str << "  " << best;
							str << " LEAF" << std::endl;
						}
						return best;
					}
					else
					{
						if constexpr (USE_TT)
							m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), beta, transpositiontable<descriptorSearch>::flags_lower, movebitsType(0));
						if constexpr (VERBOSE)
						{
							str << std::endl;
							for (depthType d = 0; d < depth; d++)
								str << " ";
							str << std::setw(6) << "<ev>";
							str << "  " << beta;
							str << " LEAF" << std::endl;
						}
						return beta;
					}
				}
				if constexpr (VERBOSE)
				{
					str << std::endl;
					for (depthType d = 0; d < depth; d++)
						str << " ";
					str << std::setw(6) << "<ev>";
					str << "  " << best;
					str << " ACCEPTED" << std::endl;
				}
				alpha = best;
				if constexpr (USE_TT)
					m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
			}
			bool fromStack;
			allowStoreTT = true;
			if ((!hasLegalMove) && nextTacticalMove(depth, move, fromStack))
			{
				hasLegalMove = true;
				if (this->qsearchSubNode<VERBOSE, false, false>(move, alpha, beta, best, bestmove, depth, principalVariation, str, fromStack, allowStoreTT))
				{
					this->resetMoveGen();
					return best;
				}
			}
			if (!hasLegalMove)
			{
				allowStoreTT = true;
				m_Heuristics.endNodeLate(m_Stack);
				hasLegalMove = m_Stack.hasLegalMove(depth, m_Heuristics.feedback());
				if (hasLegalMove)
				{
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
					this->resetMoveGen();
					return best;
				}
				else
				{
					const scoreType late{ lateScore() };
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), late, transpositiontable<descriptorSearch>::flags_exact, movebitsType(0));
					this->resetMoveGen();
					return late;
				}
			}
			while (nextTacticalMove(depth, move, fromStack))
			{
				if (this->qsearchSubNode<VERBOSE, false, true>(move, alpha, beta, best, bestmove, depth, principalVariation, str, fromStack, allowStoreTT))
				{
					this->resetMoveGen();
					return best;
				}
			}
			m_Heuristics.endNodeLate(m_Stack);
			return alpha;
		}
		template<bool VERBOSE, bool USE_TT>
		scoreType zweval(scoreType beta, const size_t depth, std::ostream& str, bool& allowStoreTT) noexcept
		{
			if (!m_IsRunning)
			{
				allowStoreTT = false;
				return scoreType::zero();
			}
			m_Heuristics.beginNode(m_Stack);
			scoreType alpha{ beta.zeroWindow() };
			scoreType early{ scoreType::zero() };
			if (earlyScore<true>(early, allowStoreTT))
			{
				m_Heuristics.endNodeEarly(m_Stack);
				return early;
			}
			movebitsType bestmove;
			bool hasLegalMove{ false };
			movebitsType move;
			scoreType best{ scoreType::minimum() };
			if constexpr (USE_TT)
			{
				scoreType ttScore{ scoreType::zero() };
				movebitsType ttMove;
				const std::uint8_t lookUp{ m_Heuristics.transpositionTable().probe(m_Stack, depthType(-1), alpha, beta, ttScore, ttMove) };
				if (lookUp != transpositiontable<descriptorSearch>::flags_unused)
				{
					if (lookUp & transpositiontable<descriptorSearch>::flags_move)
					{
						hasLegalMove = true;
						bestmove = ttMove;
					}
					if (lookUp & transpositiontable<descriptorSearch>::flags_return)
					{
						m_Heuristics.endNodeTT(m_Stack);
						return ttScore;
					}
					else
						best = ttScore;
				}
			}
			const playerType movingPlayer{ m_Stack.movingPlayer() };
			const scoreType stand_pat{ evaluatorType::evaluate(alpha, beta, m_Stack) };
			if constexpr (failSoft)
				best = scoreType::max(stand_pat, best);
			else
				best = scoreType::max(scoreType::min(stand_pat, beta), best);
			if constexpr (VERBOSE)
			{
				str << "  " << stand_pat;
			}
			if (best > alpha)
			{
				if (best >= beta)
				{
					if constexpr (VERBOSE)
					{
						str << " LEAF" << std::endl;
					}
					m_Heuristics.endNodeLeaf(m_Stack);
					if constexpr (failSoft)
					{
						if constexpr (USE_TT)
							m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), best, transpositiontable<descriptorSearch>::flags_lower, movebitsType(0));
						return best;
					}
					else
					{
						if constexpr (USE_TT)
							m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), beta, transpositiontable<descriptorSearch>::flags_lower, movebitsType(0));
						return beta;
					}
				}
				if constexpr (VERBOSE)
				{
					str << " ACCEPTED" << std::endl;
				}
				alpha = best;
				if constexpr (USE_TT)
					m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
			}
			bool fromStack;
			allowStoreTT = true;
			if ((!hasLegalMove) && nextTacticalMove(depth, move, fromStack))
			{
				hasLegalMove = true;
				if (this->qzwsearchSubNode<VERBOSE, false, false>(move, alpha, beta, best, bestmove, depth, str, fromStack, allowStoreTT))
				{
					this->resetMoveGen();
					return best;
				}
			}
			if (!hasLegalMove)
			{
				allowStoreTT = true;
				m_Heuristics.endNodeLate(m_Stack);
				hasLegalMove = m_Stack.hasLegalMove(depth, m_Heuristics.feedback());
				if (hasLegalMove)
				{
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
					this->resetMoveGen();
					return best;
				}
				else
				{
					const scoreType late{ lateScore() };
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), late, transpositiontable<descriptorSearch>::flags_exact, movebitsType(0));
					this->resetMoveGen();
					return late;
				}
			}
			while (nextTacticalMove(depth, move, fromStack))
			{
				if (this->qzwsearchSubNode<VERBOSE, false, true>(move, alpha, beta, best, bestmove, depth, str, fromStack, allowStoreTT))
				{
					this->resetMoveGen();
					return best;
				}
			}
			m_Heuristics.endNodeLate(m_Stack);
			this->resetMoveGen();
			return alpha;
		}
		template<bool VERBOSE>
		scoreType zwsearch(scoreType beta, const depthType depthRemaining, const size_t depth, const uint_t<countPlayers, false> nullMoveHistory, std::ostream& str, bool& allowStoreTT) noexcept
		{
			if (!m_IsRunning)
			{
				allowStoreTT = false;
				return scoreType::zero();
			}
			scoreType alpha{ beta.zeroWindow() };
			if (depthRemaining >= depthType(0))
			{
				m_Heuristics.beginNode(m_Stack);
				scoreType early{ scoreType::zero() };
				if (earlyScore<false>(early, allowStoreTT))
				{
					m_Heuristics.endNodeEarly(m_Stack);
					return early;
				}
				bool hasLegalMove{ false };
				movebitsType move;
				scoreType best{ scoreType::zero() };
				movebitsType bestmove;
				if constexpr (searchTranspositionTable)
				{
					scoreType ttScore{ scoreType::zero() };
					movebitsType ttMove;
					const std::uint8_t lookUp{ m_Heuristics.transpositionTable().probe(m_Stack, depthRemaining, alpha, beta, ttScore, ttMove) };
					if (lookUp != transpositiontable<descriptorSearch>::flags_unused)
					{
						if (lookUp & transpositiontable<descriptorSearch>::flags_move)
						{
							hasLegalMove = true;
							bestmove = ttMove;
						}
						if (lookUp & transpositiontable<descriptorSearch>::flags_return)
						{
							m_Heuristics.endNodeTT(m_Stack);
							return ttScore;
						}
						else
							best = ttScore;
					}
				}
				allowStoreTT = true;
				if constexpr (pruneNullmove)
				{
					if (checkNullMove(nullMoveHistory) && nullMoveAllowed(m_Stack))
					{
						bool allowStoreTTsubnode;
						scoreType nmsc{ scoreType::zero() };
						const depthType remainingNullMoveDepth{ static_cast<depthType>(depthRemaining - nullMoveReduction(depthRemaining) - 1) };
						{
							node subnode(*this, generatorType::nullMove());
							nmsc = -subnode.zwsearch<VERBOSE>((scoreType::atom() - beta).plyDown(), remainingNullMoveDepth, depth + 1, doNullMove(nullMoveHistory), str, allowStoreTTsubnode).plyUp();
						}
						if (nmsc >= (beta))
						{
							allowStoreTT &= allowStoreTTsubnode;
							if constexpr (searchTranspositionTable)
								if (allowStoreTTsubnode)
									m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, beta, transpositiontable<descriptorSearch>::flags_lower, movebitsType(0));
							m_Heuristics.endNodeNull(m_Stack);
							return beta;
						}
					}
				}
				bool fromStack;
				const playerType movingPlayer{ m_Stack.movingPlayer() };
				if ((!hasLegalMove) && nextMove(depthRemaining, depth, move, fromStack))
				{
					hasLegalMove = true;
					if (this->zwsearchSubNode<VERBOSE, false>(move, alpha, beta, best, bestmove, depthRemaining, depth, noNullMove(nullMoveHistory), str, fromStack, allowStoreTT))
					{
						this->resetMoveGen();
						return best;
					}
				}
				if (!hasLegalMove)
				{
					allowStoreTT = true;
					m_Heuristics.endNodeLate(m_Stack);
					const scoreType late{ lateScore() };
					if constexpr (searchTranspositionTable)
						m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, late, transpositiontable<descriptorSearch>::flags_exact, movebitsType(0));
					this->resetMoveGen();
					return late;
				}
				while (nextMove(depthRemaining, depth, move, fromStack))
				{
					bool allowStoreTTsubnode;
					if (this->zwsearchSubNode<VERBOSE, true>(move, alpha, beta, best, bestmove, depthRemaining, depth, noNullMove(nullMoveHistory), str, fromStack, allowStoreTT))
					{
						this->resetMoveGen();
						return best;
					}
				}
				m_Heuristics.endNodeLate(m_Stack);
				this->resetMoveGen();
				return alpha;
			}
			else
			{
				return this->template zweval<VERBOSE, searchTranspositionTable>(beta, depth, str, allowStoreTT);
			}
		}
		template<bool VERBOSE, bool LONGPV>
		scoreType search(scoreType alpha, scoreType beta, const depthType depthRemaining, const size_t depth, variationType& principalVariation, std::ostream& str, bool& allowStoreTT) noexcept
		{
			if (!m_IsRunning)
			{
				allowStoreTT = false;
				return scoreType::zero();
			}
			if (depthRemaining >= depthType(0))
			{
				m_Heuristics.beginNode(m_Stack);
				scoreType early{ scoreType::zero() };
				if (earlyScore<false>(early, allowStoreTT))
				{
					m_Heuristics.endNodeEarly(m_Stack);
					return early;
				}
				bool hasLegalMove{ false };
				movebitsType move;
				scoreType best{ scoreType::zero() };
				movebitsType bestmove;
				bool fromStack;
				const playerType movingPlayer{ m_Stack.movingPlayer() };
				allowStoreTT = true;
				if ((!hasLegalMove) && nextMove(depthRemaining, depth, move, fromStack))
				{
					hasLegalMove = true;
					if (this->searchSubNode<VERBOSE, LONGPV, false>(move, alpha, beta, best, bestmove, depthRemaining, depth, principalVariation, str, fromStack, allowStoreTT))
					{
						this->resetMoveGen();
						return best;
					}
				}
				if (!hasLegalMove)
				{
					allowStoreTT = true;
					m_Heuristics.endNodeLate(m_Stack);
					const scoreType late{ lateScore() };
					if constexpr (searchTranspositionTable)
						m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, late, transpositiontable<descriptorSearch>::flags_exact, movebitsType(0));
					this->resetMoveGen();
					return late;
				}
				while (nextMove(depthRemaining, depth, move, fromStack))
				{
					if (this->searchSubNode<VERBOSE, LONGPV, true>(move, alpha, beta, best, bestmove, depthRemaining, depth, principalVariation, str, fromStack, allowStoreTT))
					{
						this->resetMoveGen();
						return best;
					}
				}
				m_Heuristics.endNodeLate(m_Stack);
				this->resetMoveGen();
				return alpha;
			}
			else
			{
				return this->template eval<VERBOSE, searchTranspositionTable>(alpha, beta, depth, principalVariation, str, allowStoreTT);
			}
		}
		node() = delete;
		constexpr node(const node&) = default;
		constexpr node(node&&) = default;
		constexpr node& operator=(const node&) = default;
		constexpr node(const stackType& stack, std::atomic_bool& isRunning, heuristicsType& heuristics) noexcept :
			m_Stack{ stack },
			m_IsRunning{ isRunning },
			m_Heuristics{ heuristics },
			m_MovesTT{ movelistType() },
			m_MovesKiller{ movelistType() },
			m_TacticalMovesTT{ movelistType() },
			m_TacticalMovesKiller{ movelistType() },
			m_TacticalMoveGeneratorStage{ -1 },
			m_MoveGeneratorStage{ -1 },
			m_Move{ 0 },
			m_TacticalMove{ 0 },
			m_NeedsSorting{ false },
			m_NeedsTacticalSorting{ false }
		{
			if constexpr (searchTranspositionTable)
				m_Heuristics.transpositionTable().prefetch(m_Stack);
		}
		constexpr node(const node& parent, const movebitsType moveBits) noexcept :
			m_Stack(parent.m_Stack, moveBits),
			m_IsRunning{ parent.m_IsRunning },
			m_Heuristics{ parent.m_Heuristics },
			m_MovesTT{ movelistType() },
			m_MovesKiller{ movelistType() },
			m_TacticalMovesTT{ movelistType() },
			m_TacticalMovesKiller{ movelistType() },
			m_TacticalMoveGeneratorStage{ -1 },
			m_MoveGeneratorStage{ -1 },
			m_Move{ 0 },
			m_TacticalMove{ 0 },
			m_NeedsSorting{ false },
			m_NeedsTacticalSorting{ false }
		{
			if constexpr (searchTranspositionTable)
				m_Heuristics.transpositionTable().prefetch(m_Stack);
		}
		~node() noexcept = default;
	};
}