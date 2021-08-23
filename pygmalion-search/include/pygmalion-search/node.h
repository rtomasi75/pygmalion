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
		constexpr static bool inline ZWS{ true };
		constexpr static bool inline TT{ true };
		stackType m_Stack;
		heuristicsType& m_Heuristics;
		std::atomic_bool& m_IsRunning;
		movelistType m_MovesTT;
		movelistType m_TacticalMovesTT;
		int m_MoveGeneratorStage;
		int m_TacticalMoveGeneratorStage;
		indexType m_MoveTT;
		indexType m_TacticalMoveTT;
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
	protected:
		constexpr bool nextMove(movebitsType& movebits) noexcept
		{
			if (m_MoveGeneratorStage < 0)
			{
				m_MoveGeneratorStage = 0;
				m_Heuristics.transpositionTable().probeMoves(m_Stack, m_MovesTT);
				m_MoveTT = 0;
			}
			if (m_MoveGeneratorStage == 0)
			{
				if (m_MoveTT < m_MovesTT.length())
				{
					movebits = m_MovesTT[m_MoveTT];
					m_MoveTT++;
					return true;
				}
				else
				{
					m_MoveGeneratorStage = 1;
				}
			}
			movebitsType testBits{ movebitsType(0) };
			while (m_Stack.nextMove(testBits))
			{
				bool bDouble{ false };
				for (indexType i = 0; i < m_MovesTT.length(); i++)
				{
					if (m_MovesTT[i] == testBits)
					{
						bDouble = true;
						break;
					}
				}
				if (!bDouble)
				{
					movebits = testBits;
					return true;
				}
			}
			return false;
		}
		constexpr bool nextTacticalMove(movebitsType& movebits) noexcept
		{
			if (m_TacticalMoveGeneratorStage < 0)
			{
				m_TacticalMoveGeneratorStage = 0;
				m_Heuristics.transpositionTable().probeTacticalMoves(m_Stack, m_TacticalMovesTT);
				m_TacticalMoveTT = 0;
			}
			if (m_TacticalMoveGeneratorStage == 0)
			{
				if (m_TacticalMoveTT < m_TacticalMovesTT.length())
				{
					movebits = m_TacticalMovesTT[m_TacticalMoveTT];
					m_TacticalMoveTT++;
					return true;
				}
				else
				{
					m_TacticalMoveGeneratorStage = 1;
				}
			}
			movebitsType testBits{ movebitsType(0) };
			while (m_Stack.nextTacticalMove(testBits))
			{
				bool bDouble{ false };
				for (indexType i = 0; i < m_TacticalMovesTT.length(); i++)
				{
					if (m_TacticalMovesTT[i] == testBits)
					{
						bDouble = true;
						break;
					}
				}
				if (!bDouble)
				{
					movebits = testBits;
					return true;
				}
			}
			return false;
		}
		template<bool VERBOSE, bool SCOUT>
		constexpr bool searchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const depthType depthRemaining, const depthType depth, variationType& principalVariation, std::ostream& str) const noexcept
		{
			if constexpr (VERBOSE)
			{
				for (depthType d = 0; d < depth; d++)
					str << "      ";
				str << generatorType::moveToString(m_Stack, move);
			}
			m_Heuristics.beginMove(m_Stack.position(), move);
			variationType subVariation;
			if constexpr (SCOUT)
			{
				scoreType sc{ scoreType::zero() };
				if constexpr (ZWS)
				{
					{
						node zwsubnode(*this, move);
						sc = -zwsubnode.zwsearch<VERBOSE>(-alpha.plyDown(), depthRemaining - 1, depth + 1, str).plyUp();
					}
					if (sc > alpha && sc < beta)
					{
						{
							node subnode(*this, move);
							sc = -subnode.search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), depthRemaining - 1, depth + 1, subVariation, str).plyUp();
						}
						if (sc > alpha)
						{
							alpha = sc;
						}
					}
				}
				else
				{
					{
						node subnode(*this, move);
						sc = -subnode.search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), depthRemaining - 1, depth + 1, subVariation, str).plyUp();
					}
					if (sc > alpha && sc < beta)
					{
						if (sc > alpha)
						{
							alpha = sc;
							if constexpr (TT)
								m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
						}
					}
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
						m_Heuristics.endMoveRefuted(m_Stack.position(), move);
						m_Heuristics.endNodeCut(m_Stack.position());
						best = sc;
						if constexpr (TT)
							m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						return true;
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED";
					}
					best = sc;
					m_Heuristics.endMoveAccepted(m_Stack.position(), move);
					principalVariation.combine(move, subVariation);
					bestmove = move;
				}
				else
					m_Heuristics.endMoveSilent(m_Stack.position(), move);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
			else
			{
				{
					node subnode(*this, move);
					const scoreType sc{ -subnode.search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), depthRemaining - 1, depth + 1, subVariation, str).plyUp() };
					best = sc;
				}
				if constexpr (VERBOSE)
				{
					str << "  " << best;
				}
				if (best > alpha)
				{
					if (best >= beta)
					{
						if constexpr (VERBOSE)
						{
							str << " REFUTED" << std::endl;
						}
						m_Heuristics.endMoveRefuted(m_Stack.position(), move);
						m_Heuristics.endNodeCut(m_Stack.position());
						if constexpr (TT)
							m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						return true;
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED";
					}
					principalVariation.combine(move, subVariation);
					m_Heuristics.endMoveAccepted(m_Stack.position(), move);
					alpha = best;
					bestmove = move;
					if constexpr (TT)
						m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
				}
				else
					m_Heuristics.endMoveSilent(m_Stack.position(), move);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
		}
		template<bool VERBOSE, bool SCOUT>
		constexpr bool zwsearchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const depthType depthRemaining, const depthType depth, std::ostream& str) const noexcept
		{
			if constexpr (VERBOSE)
			{
				for (depthType d = 0; d < depth; d++)
					str << "      ";
				str << generatorType::moveToString(m_Stack, move);
			}
			m_Heuristics.beginMove(m_Stack.position(), move);
			if constexpr (SCOUT)
			{
				scoreType sc{ scoreType::zero() };
				{
					node subnode(*this, move);
					sc = -subnode.zwsearch<VERBOSE>(-alpha.plyDown(), depthRemaining - 1, depth + 1, str).plyUp();
				}
				if (sc > alpha && sc < beta)
				{
					if (sc > alpha)
					{
						alpha = sc;
						if constexpr (TT)
							m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
					}
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
						m_Heuristics.endMoveRefuted(m_Stack.position(), move);
						m_Heuristics.endNodeCut(m_Stack.position());
						best = sc;
						if constexpr (TT)
							m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						return true;
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED";
					}
					best = sc;
					m_Heuristics.endMoveAccepted(m_Stack.position(), move);
					bestmove = move;
				}
				else
					m_Heuristics.endMoveSilent(m_Stack.position(), move);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
			else
			{
				{
					node subnode(*this, move);
					const scoreType sc{ -subnode.zwsearch<VERBOSE>(-alpha.plyDown(), depthRemaining - 1, depth + 1, str).plyUp() };
					best = sc;
				}
				if constexpr (VERBOSE)
				{
					str << "  " << best;
				}
				if (best > alpha)
				{
					if (best >= beta)
					{
						if constexpr (VERBOSE)
						{
							str << " REFUTED" << std::endl;
						}
						m_Heuristics.endMoveRefuted(m_Stack.position(), move);
						m_Heuristics.endNodeCut(m_Stack.position());
						if constexpr (TT)
							m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						return true;
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED";
					}
					m_Heuristics.endMoveAccepted(m_Stack.position(), move);
					alpha = best;
					bestmove = move;
					if constexpr (TT)
						m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
				}
				else
					m_Heuristics.endMoveSilent(m_Stack.position(), move);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
		}
		template<bool VERBOSE, bool USE_TT, bool SCOUT>
		constexpr bool qsearchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const depthType depth, variationType& principalVariation, std::ostream& str) const noexcept
		{
			if constexpr (VERBOSE)
			{
				for (depthType d = 0; d < depth; d++)
					str << "      ";
				str << generatorType::moveToString(m_Stack, move);
			}
			m_Heuristics.beginMove(m_Stack.position(), move);
			variationType subVariation;
			if constexpr (SCOUT)
			{
				scoreType sc{ scoreType::zero() };
				{
					node subnode(*this, move);
					sc = -subnode.eval<VERBOSE, false>(-beta.plyDown(), -alpha.plyDown(), depth + 1, subVariation, str).plyUp();
				}
				if (sc > alpha && sc < beta)
				{
					if (sc > alpha)
					{
						alpha = sc;
						if constexpr (USE_TT)
							m_Heuristics.transpositionTable().store(m_Stack, -1, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
					}
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
						m_Heuristics.endMoveRefuted(m_Stack.position(), move);
						m_Heuristics.endNodeCut(m_Stack.position());
						best = sc;
						if constexpr (USE_TT)
							m_Heuristics.transpositionTable().store(m_Stack, -1, beta, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						return true;
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED";
					}
					best = sc;
					m_Heuristics.endMoveAccepted(m_Stack.position(), move);
					principalVariation.combine(move, subVariation);
					bestmove = move;
				}
				else
					m_Heuristics.endMoveSilent(m_Stack.position(), move);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
			else
			{
				{
					node subnode(*this, move);
					const scoreType sc{ -subnode.eval<VERBOSE,false>(-beta.plyDown(), -alpha.plyDown(), depth + 1, subVariation, str).plyUp() };
					best = sc;
				}
				if constexpr (VERBOSE)
				{
					str << "  " << best;
				}
				if (best > alpha)
				{
					if (best >= beta)
					{
						if constexpr (VERBOSE)
						{
							str << " REFUTED" << std::endl;
						}
						m_Heuristics.endMoveRefuted(m_Stack.position(), move);
						m_Heuristics.endNodeCut(m_Stack.position());
						if constexpr (USE_TT)
							m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						return true;
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED";
					}
					principalVariation.combine(move, subVariation);
					m_Heuristics.endMoveAccepted(m_Stack.position(), move);
					alpha = best;
					bestmove = move;
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
				}
				else
					m_Heuristics.endMoveSilent(m_Stack.position(), move);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
		}
		template<bool VERBOSE, bool USE_TT, bool SCOUT>
		constexpr bool qzwsearchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const depthType depth, std::ostream& str) const noexcept
		{
			if constexpr (VERBOSE)
			{
				for (depthType d = 0; d < depth; d++)
					str << "      ";
				str << generatorType::moveToString(m_Stack, move);
			}
			m_Heuristics.beginMove(m_Stack.position(), move);
			if constexpr (SCOUT)
			{
				scoreType sc{ scoreType::zero() };
				{
					node subnode(*this, move);
					sc = -subnode.zweval<VERBOSE, false>(-alpha.plyDown(), depth + 1, str).plyUp();
				}
				if (sc > alpha && sc < beta)
				{
					if (sc > alpha)
					{
						alpha = sc;
						if constexpr (USE_TT)
							m_Heuristics.transpositionTable().store(m_Stack, -1, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
					}
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
						m_Heuristics.endMoveRefuted(m_Stack.position(), move);
						m_Heuristics.endNodeCut(m_Stack.position());
						best = sc;
						if constexpr (USE_TT)
							m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						return true;
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED";
					}
					best = sc;
					m_Heuristics.endMoveAccepted(m_Stack.position(), move);
					bestmove = move;
				}
				else
					m_Heuristics.endMoveSilent(m_Stack.position(), move);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
			else
			{
				{
					node subnode(*this, move);
					const scoreType sc{ -subnode.zweval<VERBOSE,false>(-alpha.plyDown(), depth + 1, str).plyUp() };
					best = sc;
				}
				if constexpr (VERBOSE)
				{
					str << "  " << best;
				}
				if (best > alpha)
				{
					if (best >= beta)
					{
						if constexpr (VERBOSE)
						{
							str << " REFUTED" << std::endl;
						}
						m_Heuristics.endMoveRefuted(m_Stack.position(), move);
						m_Heuristics.endNodeCut(m_Stack.position());
						if constexpr (USE_TT)
							m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						return true;
					}
					if constexpr (VERBOSE)
					{
						str << " ACCEPTED";
					}
					m_Heuristics.endMoveAccepted(m_Stack.position(), move);
					alpha = best;
					bestmove = move;
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
				}
				else
					m_Heuristics.endMoveSilent(m_Stack.position(), move);
				if constexpr (VERBOSE)
				{
					str << std::endl;
				}
				return false;
			}
		}
	public:
		constexpr const stackType& stack() const noexcept
		{
			return m_Stack;
		}
		template<bool VERBOSE, bool USE_TT>
		scoreType eval(scoreType alpha, scoreType beta, const depthType depth, variationType& principalVariation, std::ostream& str) noexcept
		{
			if (!m_IsRunning)
				return scoreType::zero();
			m_Heuristics.beginNode(m_Stack.position());
			scoreType early{ scoreType::zero() };
			if (earlyScore(early))
			{
				m_Heuristics.endNodeEarly(m_Stack.position());
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
				const std::uint8_t lookUp{ m_Heuristics.transpositionTable().probe(m_Stack, -1, alpha, beta, ttScore, ttMove) };
				if (lookUp != transpositiontable<descriptorSearch>::flags_unused)
				{
					if (lookUp & transpositiontable<descriptorSearch>::flags_move)
					{
						principalVariation = variationType(ttMove);
						hasLegalMove = true;
						bestmove = ttMove;
					}
					else
						principalVariation.clear();
					if (lookUp & transpositiontable<descriptorSearch>::flags_return)
						return ttScore;
					else
						best = ttScore;
				}
			}
			const playerType movingPlayer{ m_Stack.movingPlayer() };
			const scoreType stand_pat{ evaluatorType::evaluate(alpha, beta, m_Stack) };
			best = scoreType::max(stand_pat, best);
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
						str << " LEAF";
					}
					m_Heuristics.endNodeLeaf(m_Stack.position());
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_lower, movebitsType(0));
					return best;
				}
				if constexpr (VERBOSE)
				{
					str << " ACCEPTED";
				}
				alpha = best;
				if constexpr (USE_TT)
					m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
			}
			if ((!hasLegalMove) && nextTacticalMove(move))
			{
				hasLegalMove = true;
				if (this->qsearchSubNode<VERBOSE, false, false>(move, alpha, beta, best, bestmove, depth, principalVariation, str))
					return best;
			}
			if (!hasLegalMove)
			{
				m_Heuristics.endNodeLate(m_Stack.position());
				hasLegalMove = m_Stack.hasLegalMove();
				if (hasLegalMove)
				{
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
					return best;
				}
				else
				{
					const scoreType late{ lateScore() };
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, -1, late, transpositiontable<descriptorSearch>::flags_exact, movebitsType(0));
					return late;
				}
			}
			while (nextTacticalMove(move))
			{
				if (this->qsearchSubNode<VERBOSE, false, true>(move, alpha, beta, best, bestmove, depth, principalVariation, str))
					return best;
			}
			m_Heuristics.endNodeLate(m_Stack.position());
			return alpha;
		}
		template<bool VERBOSE>
		scoreType search(scoreType alpha, scoreType beta, const depthType depthRemaining, const depthType depth, variationType& principalVariation, std::ostream& str) noexcept
		{
			if (!m_IsRunning)
				return scoreType::zero();
			if ((depthRemaining >= 0) && (depth < countSearchPlies))
			{
				m_Heuristics.beginNode(m_Stack.position());
				scoreType early{ scoreType::zero() };
				if (earlyScore(early))
				{
					m_Heuristics.endNodeEarly(m_Stack.position());
					return early;
				}
				bool hasLegalMove{ false };
				movebitsType move;
				scoreType best{ scoreType::zero() };
				movebitsType bestmove;
				if constexpr (TT)
				{
					scoreType ttScore{ scoreType::zero() };
					movebitsType ttMove;
					const std::uint8_t lookUp{ m_Heuristics.transpositionTable().probe(m_Stack, depthRemaining, alpha, beta, ttScore, ttMove) };
					if (lookUp != transpositiontable<descriptorSearch>::flags_unused)
					{
						if (lookUp & transpositiontable<descriptorSearch>::flags_move)
						{
							principalVariation = variationType(ttMove);
							hasLegalMove = true;
							bestmove = ttMove;
						}
						else
							principalVariation.clear();
						if (lookUp & transpositiontable<descriptorSearch>::flags_return)
							return ttScore;
						else
							best = ttScore;
					}
				}
				const playerType movingPlayer{ m_Stack.movingPlayer() };
				if ((!hasLegalMove) && nextMove(move))
				{
					hasLegalMove = true;
					if (this->searchSubNode<VERBOSE, false>(move, alpha, beta, best, bestmove, depthRemaining, depth, principalVariation, str))
						return best;
				}
				if (!hasLegalMove)
				{
					m_Heuristics.endNodeLate(m_Stack.position());
					const scoreType late{ lateScore() };
					if constexpr (TT)
						m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, late, transpositiontable<descriptorSearch>::flags_exact, movebitsType(0));
					return late;
				}
				while (nextMove(move))
				{
					if (this->searchSubNode<VERBOSE, true>(move, alpha, beta, best, bestmove, depthRemaining, depth, principalVariation, str))
						return best;
				}
				m_Heuristics.endNodeLate(m_Stack.position());
				return alpha;
			}
			else
			{
				const scoreType exact{ this->template eval<VERBOSE, TT>(alpha, beta, depth, principalVariation, str) };
				return exact;
			}
		}
		template<bool VERBOSE, bool USE_TT>
		scoreType zweval(scoreType beta, const depthType depth, std::ostream& str) noexcept
		{
			if (!m_IsRunning)
				return scoreType::zero();
			scoreType alpha{ beta.zeroWindow() };
			m_Heuristics.beginNode(m_Stack.position());
			scoreType early{ scoreType::zero() };
			if (earlyScore(early))
			{
				m_Heuristics.endNodeEarly(m_Stack.position());
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
				const std::uint8_t lookUp{ m_Heuristics.transpositionTable().probe(m_Stack, -1, alpha, beta, ttScore, ttMove) };
				if (lookUp != transpositiontable<descriptorSearch>::flags_unused)
				{
					if (lookUp & transpositiontable<descriptorSearch>::flags_move)
					{
						hasLegalMove = true;
						bestmove = ttMove;
					}
					if (lookUp & transpositiontable<descriptorSearch>::flags_return)
						return ttScore;
					else
						best = ttScore;
				}
			}
			const playerType movingPlayer{ m_Stack.movingPlayer() };
			const scoreType stand_pat{ evaluatorType::evaluate(alpha, beta, m_Stack) };
			best = scoreType::max(stand_pat, best);
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
						str << " LEAF";
					}
					m_Heuristics.endNodeLeaf(m_Stack.position());
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_lower, movebitsType(0));
					return best;
				}
				if constexpr (VERBOSE)
				{
					str << " ACCEPTED";
				}
				alpha = best;
				if constexpr (USE_TT)
					m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
			}
			if ((!hasLegalMove) && nextTacticalMove(move))
			{
				hasLegalMove = true;
				if (this->qzwsearchSubNode<VERBOSE, false, false>(move, alpha, beta, best, bestmove, depth, str))
					return best;
			}
			if (!hasLegalMove)
			{
				m_Heuristics.endNodeLate(m_Stack.position());
				hasLegalMove = m_Stack.hasLegalMove();
				if (hasLegalMove)
				{
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
					return best;
				}
				else
				{
					const scoreType late{ lateScore() };
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, -1, late, transpositiontable<descriptorSearch>::flags_exact, movebitsType(0));
					return late;
				}
			}
			while (nextTacticalMove(move))
			{
				if (this->qzwsearchSubNode<VERBOSE, false, true>(move, alpha, beta, best, bestmove, depth, str))
					return best;
			}
			m_Heuristics.endNodeLate(m_Stack.position());
			return alpha;
		}
		template<bool VERBOSE>
		scoreType zwsearch(scoreType beta, const depthType depthRemaining, const depthType depth, std::ostream& str) noexcept
		{
			if (!m_IsRunning)
				return scoreType::zero();
			scoreType alpha{ beta.zeroWindow() };
			if ((depthRemaining >= 0) && (depth < countSearchPlies))
			{
				m_Heuristics.beginNode(m_Stack.position());
				scoreType early{ scoreType::zero() };
				if (earlyScore(early))
				{
					m_Heuristics.endNodeEarly(m_Stack.position());
					return early;
				}
				bool hasLegalMove{ false };
				movebitsType move;
				scoreType best{ scoreType::zero() };
				movebitsType bestmove;
				if constexpr (TT)
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
							return ttScore;
						else
							best = ttScore;
					}
				}
				const playerType movingPlayer{ m_Stack.movingPlayer() };
				if ((!hasLegalMove) && nextMove(move))
				{
					hasLegalMove = true;
					if (this->zwsearchSubNode<VERBOSE, false>(move, alpha, beta, best, bestmove, depthRemaining, depth, str))
						return best;
				}
				if (!hasLegalMove)
				{
					m_Heuristics.endNodeLate(m_Stack.position());
					const scoreType late{ lateScore() };
					if constexpr (TT)
						m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, late, transpositiontable<descriptorSearch>::flags_exact, movebitsType(0));
					return late;
				}
				while (nextMove(move))
				{
					if (this->zwsearchSubNode<VERBOSE, true>(move, alpha, beta, best, bestmove, depthRemaining, depth, str))
						return best;
				}
				m_Heuristics.endNodeLate(m_Stack.position());
				return alpha;
			}
			else
			{
				const scoreType exact{ this->template zweval<VERBOSE, TT>(beta, depth, str) };
				return exact;
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
			m_TacticalMovesTT{ movelistType() },
			m_TacticalMoveGeneratorStage{ -1 },
			m_MoveGeneratorStage{ -1 }
		{

		}
		constexpr node(const node& parent, const movebitsType moveBits) noexcept :
			m_Stack(parent.m_Stack, moveBits),
			m_IsRunning{ parent.m_IsRunning },
			m_Heuristics{ parent.m_Heuristics },
			m_MovesTT{ movelistType() },
			m_TacticalMovesTT{ movelistType() },
			m_TacticalMoveGeneratorStage{ -1 },
			m_MoveGeneratorStage{ -1 }
		{
		}
		~node() noexcept = default;
	};
}