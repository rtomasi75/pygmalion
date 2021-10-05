namespace pygmalion
{
	template<typename DESCRIPTION_SEARCH, typename INSTANCE>
	class gametree
	{
	public:
		using gametreeType = INSTANCE;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"	
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		template<size_t PLAYER, typename INSTANCE2>
		class node :
			public DESCRIPTION_SEARCH
		{
		public:
			using instanceType = INSTANCE2;
			using descriptorSearch = DESCRIPTION_SEARCH;
#include "include_search.h"	
			using stackType = typename generatorType::template stackType<PLAYER>;
			constexpr static inline const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			friend node< static_cast<size_t>(movingPlayer.next()), typename gametreeType::template nodeType< static_cast<size_t>(movingPlayer.next()) > >;
			using parentType = node< static_cast<size_t>(movingPlayer.previous()), typename gametreeType::template nodeType< static_cast<size_t>(movingPlayer.previous()) >>;
			using childType = node< static_cast<size_t>(movingPlayer.next()), typename gametreeType::template nodeType< static_cast<size_t>(movingPlayer.next()) > >;
		private:
			stackType m_Stack;
			heuristicsType& m_Heuristics;
			const int m_DistanceFromRoot;
			movelistType m_Moves;
			movelistType m_CriticalMoves;
			movelistType m_TacticalMoves;
			killermovesType m_MovesKiller;
			killermovesType m_TacticalMovesKiller;
			ttmovesType m_MovesTT;
			ttmovesType m_TacticalMovesTT;
			int m_MoveGeneratorStage;
			int m_TacticalMoveGeneratorStage;
			bool m_NeedsSorting;
			bool m_NeedsTacticalSorting;
			bool m_FutilityPruningAllowed;
			std::atomic_bool& m_IsRunning;
			scoreType m_EvalAlpha;
			scoreType m_EvalBeta;
			scoreType m_Eval;
			scoreType m_FutileGap;
			indexType m_MoveTT;
			indexType m_MoveKiller;
			indexType m_TacticalMoveTT;
			indexType m_TacticalMoveKiller;
			indexType m_Move;
			indexType m_CriticalMove;
			indexType m_TacticalMove;
			size_t m_Depth;
			scoreType lateScore() const noexcept
			{
				const gamestateType lateState{ evaluatorType::lateResult(m_Stack) };
				PYGMALION_ASSERT(!gamestateType::isOpen(lateState));
				if (gamestateType::isDraw(lateState))
				{
					constexpr const scoreType zero{ scoreType::zero() };
					return zero;
				}
				else
				{
					constexpr const scoreType win{ scoreType::win() };
					constexpr const scoreType loss{ scoreType::loss() };
					return gamestateType::isWin(lateState, movingPlayer) ? win : loss;
				}
			}
			template<bool LAZY>
			bool earlyScore(scoreType& score, bool& allowStoreTT) const noexcept
			{
				const gamestateType earlyState{ evaluatorType::template earlyResult<PLAYER, LAZY>(m_Stack,allowStoreTT) };
				if (!gamestateType::isOpen(earlyState))
				{
					if (gamestateType::isDraw(earlyState))
					{
						constexpr const scoreType zero{ scoreType::zero() };
						score = zero;
						return true;
					}
					else
					{
						constexpr const scoreType win{ scoreType::win() };
						constexpr const scoreType loss{ scoreType::loss() };
						score = gamestateType::isWin(earlyState, movingPlayer) ? win : loss;
						return true;
					}
				}
				return false;
			}
			constexpr void resetMoveGen()
			{
				m_Move = 0;
				m_CriticalMove = 0;
				m_TacticalMove = 0;
				m_MoveGeneratorStage = -1;
				m_TacticalMoveGeneratorStage = -1;
				m_NeedsSorting = true;
				m_NeedsTacticalSorting = true;
			}
			template<bool PRUNED>
			constexpr bool nextMove(const depthType depthRemaining, movebitsType& movebits, bool& fromStack) noexcept
			{
				fromStack = false;
				if (m_MoveGeneratorStage < 0)
				{
					m_MoveGeneratorStage = 0;
					m_MovesTT.clear();
					m_Heuristics.transpositionTable().probeMoves(m_Stack, depthRemaining, m_MovesTT);
					m_MoveTT = 0;
				}
				if (m_MoveGeneratorStage == 0)
				{
					while (m_MoveTT < m_MovesTT.length())
					{
						movebits = m_MovesTT[m_MoveTT];
						++m_MoveTT;
						if constexpr (PRUNED)
						{
							if (generatorType::template isMoveCritical<PLAYER>(m_Stack, movebits))
								return true;
						}
						else
							return true;
					}
					m_MoveGeneratorStage = 1;
					m_MovesKiller.clear();
					m_Heuristics.killers(m_Stack, m_Depth, m_MovesKiller);
					m_MoveKiller = 0;
				}
				if (m_MoveGeneratorStage == 1)
				{
					while (m_MoveKiller < m_MovesKiller.length())
					{
						movebits = m_MovesKiller[m_MoveKiller];
						++m_MoveKiller;
						if constexpr (PRUNED)
						{
							if (generatorType::template isMoveCritical<PLAYER>(m_Stack, movebits))
							{
								const bool bDouble{ m_MovesTT.contains(movebits) };
								if (!bDouble)
								{
									return true;
								}
							}
						}
						else
						{
							const bool bDouble{ m_MovesTT.contains(movebits) };
							if (!bDouble)
							{
								return true;
							}
						}
					}
					m_MoveGeneratorStage = 2;
					m_TacticalMovesKiller.clear();
					m_Heuristics.tacticalKillers(m_Stack, m_Depth, m_TacticalMovesKiller);
					m_TacticalMoveKiller = 0;
				}
				if (m_MoveGeneratorStage == 2)
				{
					while (m_TacticalMoveKiller < m_TacticalMovesKiller.length())
					{
						movebits = m_TacticalMovesKiller[m_TacticalMoveKiller];
						++m_TacticalMoveKiller;
						if constexpr (PRUNED)
						{
							if (generatorType::template isMoveCritical<PLAYER>(m_Stack, movebits))
							{
								const bool bDouble{ m_MovesTT.contains(movebits) };
								if (!bDouble)
								{
									return true;
								}
							}
						}
						else
						{
							const bool bDouble{ m_MovesTT.contains(movebits) };
							if (!bDouble)
							{
								return true;
							}
						}
					}
					m_MoveGeneratorStage = 3;
				}
				if constexpr (heuristicMoves)
				{
					if (m_NeedsSorting)
					{
						if constexpr (PRUNED)
							m_Heuristics.sortMoves(m_Stack, m_Moves, m_Move, m_Depth);
						else
							m_Heuristics.sortMoves(m_Stack, m_CriticalMoves, m_Move, m_Depth);
						m_NeedsSorting = false;
					}
				}
				if constexpr (PRUNED)
				{
					while (m_CriticalMove < m_CriticalMoves.length())
					{
						movebits = m_CriticalMoves[m_CriticalMove];
						const bool bDouble{ m_MovesTT.contains(movebits) || m_MovesKiller.contains(movebits) };
						++m_CriticalMove;
						if (!bDouble)
						{
							return true;
						}
					}
				}
				else
				{
					while (m_Move < m_Moves.length())
					{
						movebits = m_Moves[m_Move];
						const bool bDouble{ m_MovesTT.contains(movebits) || m_MovesKiller.contains(movebits) };
						++m_Move;
						if (!bDouble)
						{
							return true;
						}
					}
				}
				movebitsType testBits{ movebitsType(0) };
				if constexpr (PRUNED)
				{
					if constexpr (heuristicMoves)
					{
						while (m_Stack.nextCriticalMove(testBits, m_Depth, m_Heuristics.feedback(), [this](const movebitsType& bits) { return this->m_Heuristics.moveScore(m_Stack, bits, m_Depth); }))
						{
							const bool bDouble{ m_MovesTT.contains(testBits) || m_MovesKiller.contains(testBits) };
							if (!bDouble)
							{
								fromStack = true;
								movebits = testBits;
								m_CriticalMoves.add(movebits);
								++m_CriticalMove;
								return true;
							}
						}
					}
					else
					{
						while (m_Stack.nextCriticalMove(testBits, m_Depth, m_Heuristics.feedback()))
						{
							const bool bDouble{ m_MovesTT.contains(testBits) || m_MovesKiller.contains(testBits) };
							if (!bDouble)
							{
								fromStack = true;
								movebits = testBits;
								m_CriticalMoves.add(movebits);
								++m_CriticalMove;
								return true;
							}
						}
					}
				}
				else
				{
					if constexpr (heuristicMoves)
					{
						while (m_Stack.nextMove(testBits, m_Depth, m_Heuristics.feedback(), [this](const movebitsType& bits) { return this->m_Heuristics.moveScore(m_Stack, bits, m_Depth); }))
						{
							const bool bDouble{ m_MovesTT.contains(testBits) || m_MovesKiller.contains(testBits) };
							if (!bDouble)
							{
								fromStack = true;
								movebits = testBits;
								m_Moves.add(movebits);
								++m_Move;
								return true;
							}
						}
					}
					else
					{
						while (m_Stack.nextMove(testBits, m_Depth, m_Heuristics.feedback()))
						{
							const bool bDouble{ m_MovesTT.contains(testBits) || m_MovesKiller.contains(testBits) };
							if (!bDouble)
							{
								fromStack = true;
								movebits = testBits;
								m_Moves.add(movebits);
								++m_Move;
								return true;
							}
						}
					}
				}
				return false;
			}
			constexpr bool nextTacticalMove(movebitsType& movebits, bool& fromStack) noexcept
			{
				fromStack = false;
				if (m_TacticalMoveGeneratorStage < 0)
				{
					m_TacticalMoveGeneratorStage = 0;
					m_TacticalMovesTT.clear();
					m_Heuristics.transpositionTable().probeTacticalMoves(m_Stack, m_TacticalMovesTT);
					m_TacticalMoveTT = 0;
				}
				if (m_TacticalMoveGeneratorStage == 0)
				{
					while (m_TacticalMoveTT < m_TacticalMovesTT.length())
					{
						movebits = m_TacticalMovesTT[m_TacticalMoveTT];
						++m_TacticalMoveTT;
						return true;
					}
					m_TacticalMoveGeneratorStage = 1;
					m_TacticalMovesKiller.clear();
					m_Heuristics.tacticalKillers(m_Stack, m_Depth, m_TacticalMovesKiller);
					m_TacticalMoveKiller = 0;
				}
				if (m_TacticalMoveGeneratorStage == 1)
				{
					while (m_TacticalMoveKiller < m_TacticalMovesKiller.length())
					{
						movebits = m_TacticalMovesKiller[m_TacticalMoveKiller];
						const bool bDouble{ m_TacticalMovesTT.contains(movebits) };
						++m_TacticalMoveKiller;
						if (!bDouble)
							return true;
					}
					m_TacticalMoveGeneratorStage = 2;
				}
				if constexpr (heuristicMoves)
				{
					if (m_NeedsTacticalSorting)
					{
						m_Heuristics.sortTacticalMoves(m_Stack, m_TacticalMoves, m_TacticalMove, m_Depth);
						m_NeedsTacticalSorting = false;
					}
				}
				while (m_TacticalMove < m_TacticalMoves.length())
				{
					movebits = m_TacticalMoves[m_TacticalMove];
					const bool bDouble{ m_TacticalMovesTT.contains(movebits) || m_TacticalMovesKiller.contains(movebits) };
					++m_TacticalMove;
					if (!bDouble)
					{
						return true;
					}
				}
				movebitsType testBits{ movebitsType(0) };
/*				if constexpr (heuristicMoves)
				{
					while (m_Stack.nextTacticalMove(testBits, m_Depth, m_Heuristics.feedback(), [this](const movebitsType& bits) { return this->m_Heuristics.tacticalMoveScore(m_Stack, bits, m_Depth); }))
					{
						const bool bDouble{ m_TacticalMovesTT.contains(testBits) || m_TacticalMovesKiller.contains(testBits) };
						if (!bDouble)
						{
							fromStack = true;
							movebits = testBits;
							m_TacticalMoves.add(testBits);
							++m_TacticalMove;
							return true;
						}
					}
				}
				else*/
				{
					while (m_Stack.nextTacticalMove(testBits, m_Depth, m_Heuristics.feedback()))
					{
						const bool bDouble{ m_TacticalMovesTT.contains(testBits) || m_TacticalMovesKiller.contains(testBits) };
						if (!bDouble)
						{
							fromStack = true;
							movebits = testBits;
							m_TacticalMoves.add(testBits);
							++m_TacticalMove;
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
			template<bool VERBOSE>
			constexpr scoreType searchMove(const movebitsType move, const scoreType alpha, const scoreType beta, const depthType depthRemaining, variationType& principalVariation, std::ostream& str, bool& allowStoreTT) const noexcept
			{
				if constexpr (searchIterativeDeepening)
				{
					scoreType sc;
					childType subnode(childType(*static_cast<const instanceType*>(this), move));
					if (depthRemaining >= 0)
					{
						sc = -subnode.template search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), depthType(-1), principalVariation, str, allowStoreTT).plyUp();
						for (depthType d = 0; d < depthRemaining; ++d)
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
									sc = -subnode.template search<VERBOSE>(-highAspiration.plyDown(), -lowAspiration.plyDown(), d, principalVariation, str, allowStoreTT).plyUp();
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
									sc = -subnode.template search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), d, principalVariation, str, allowStoreTT).plyUp();
								}
							}
							else
							{
								sc = -subnode.template search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), d, principalVariation, str, allowStoreTT).plyUp();
							}
						}
					}
					else
						sc = -subnode.template search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), depthType(-1), principalVariation, str, allowStoreTT).plyUp();
					return sc;
				}
				else
				{
					childType subnode(childType(*static_cast<const instanceType*>(this), move));
					return -subnode.template search<VERBOSE>(-beta.plyDown(), -alpha.plyDown(), depthRemaining - depthType(1), principalVariation, str, allowStoreTT).plyUp();
				}
			}
			template<bool VERBOSE>
			constexpr scoreType zwsearchMove(const movebitsType move, const scoreType alpha, const depthType& depthRemaining, const uint_t<countPlayers, false> nullMoveHistory, std::ostream& str, bool& allowStoreTT) const noexcept
			{
				childType subnode{ childType(*this, move) };
				return -subnode.template zwsearch<VERBOSE>(-alpha.plyDown(), depthRemaining - depthType(1), nullMoveHistory, str, allowStoreTT).plyUp();
			}
			template<bool VERBOSE, bool SCOUT>
			constexpr bool searchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const depthType depthRemaining, variationType& principalVariation, std::ostream& str, const bool fromStack, bool& allowStoreTT)  noexcept
			{
				m_Heuristics.beginMove(m_Stack, move, false, m_Depth);
				variationType subVariation;
				if constexpr (SCOUT)
				{
					if constexpr (pruneFutility)
					{
						if (m_FutilityPruningAllowed && this->canPruneMove(move) && this->canFutilityPruneMove(move))
						{
							m_Heuristics.template endMoveFutile<PLAYER>(m_Stack, move, false, m_Depth);
							return false;
						}
					}
					bool bEnded{ false };
					scoreType sc;
					bool allowStoreTTsubnode{ true };
					const scoreType oldAlpha{ alpha };
					if constexpr (searchScout)
					{
						sc = this->zwsearchMove<VERBOSE>(move, alpha, depthRemaining, m_EmptyNullMoveHistory, str, allowStoreTTsubnode);
						if (sc > alpha && sc < beta)
						{
							sc = this->searchMove<VERBOSE>(move, alpha, beta, depthRemaining, subVariation, str, allowStoreTTsubnode);
							if (sc > alpha)
							{
								alpha = sc;
								allowStoreTT &= allowStoreTTsubnode;
								if constexpr (searchTranspositionTable)
								{
									if (allowStoreTT)
										m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
								}
								bEnded = true;
							}
						}
					}
					else
					{
						sc = this->searchMove<VERBOSE>(move, alpha, beta, depthRemaining, subVariation, str, allowStoreTTsubnode);
						if (sc > alpha && sc < beta)
						{
							alpha = sc;
							allowStoreTT &= allowStoreTTsubnode;
							if constexpr (searchTranspositionTable)
							{
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
							}
							bEnded = true;
						}
					}
					if (sc > best)
					{
						allowStoreTT &= allowStoreTTsubnode;
						best = sc;
						if (sc >= beta)
						{
							if constexpr (searchTranspositionTable)
							{
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							}
							m_Heuristics.template endMoveRefuted<PLAYER, false>(m_Stack, move, false, m_Depth, best, evaluate(oldAlpha, best), fromStack);
							m_Heuristics.endNodeCut(m_Stack);
							return true;
						}
						principalVariation.combine(move, subVariation);
						bestmove = move;
					}
					if (!bEnded)
						m_Heuristics.template endMoveSilent<PLAYER>(m_Stack, move, false, m_Depth);
					else
						m_Heuristics.template endMoveAccepted<PLAYER, false>(m_Stack, move, false, m_Depth, alpha, evaluate(oldAlpha, best), fromStack);
					return false;
				}
				else
				{
					bool allowStoreTTsubnode{ true };
					const scoreType sc{ this->searchMove<VERBOSE>(move, alpha, beta, depthRemaining, subVariation, str, allowStoreTTsubnode) };
					best = sc;
					if (best > alpha)
					{
						allowStoreTT &= allowStoreTTsubnode;
						if (best >= beta)
						{
							m_Heuristics.endNodeCut(m_Stack);
							if constexpr (searchTranspositionTable)
							{
								if (allowStoreTT)
									m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							}
							m_Heuristics.template endMoveRefuted<PLAYER, false>(m_Stack, move, false, m_Depth, best, evaluate(alpha, best), fromStack);
							return true;
						}
						principalVariation.combine(move, subVariation);
						bestmove = move;
						if constexpr (searchTranspositionTable)
						{
							if (allowStoreTT)
								m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
						}
						m_Heuristics.template endMoveAccepted<PLAYER, false>(m_Stack, move, false, m_Depth, best, evaluate(alpha, best), fromStack);
						alpha = best;
					}
					else
						m_Heuristics.template endMoveSilent<PLAYER>(m_Stack, move, false, m_Depth);
					return false;
				}
			}
			template<bool VERBOSE, bool PRUNED>
			constexpr bool zwsearchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const depthType depthRemaining, const uint_t<countPlayers, false> nullMoveHistory, std::ostream& str, const bool fromStack, bool& allowStoreTT) noexcept
			{
				m_Heuristics.beginMove(m_Stack, move, false, m_Depth);
				if constexpr (!PRUNED)
				{
					if constexpr (pruneFutility)
					{
						if (m_FutilityPruningAllowed && this->canPruneMove(move) && this->canFutilityPruneMove(move))
						{
							m_Heuristics.template endMoveFutile<PLAYER>(m_Stack, move, false, m_Depth);
							return false;
						}
					}
				}
				bool allowStoreTTsubnode{ true };
				const scoreType sc{ this->zwsearchMove<VERBOSE>(move, alpha, depthRemaining, nullMoveHistory, str, allowStoreTTsubnode) };
				if (sc > best)
				{
					allowStoreTT &= allowStoreTTsubnode;
					best = sc;
					if (sc >= beta)
					{
						if constexpr (searchTranspositionTable)
						{
							if (allowStoreTT)
								m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						}
						m_Heuristics.template endMoveRefuted<PLAYER, PRUNED>(m_Stack, move, false, m_Depth, best, evaluate(alpha, best), fromStack);
						m_Heuristics.endNodeCut(m_Stack);
						return true;
					}
					bestmove = move;
				}
				m_Heuristics.template endMoveSilent<PLAYER>(m_Stack, move, false, m_Depth);
				return false;
			}
			template<bool VERBOSE, bool USE_TT>
			constexpr bool qsearchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, variationType& principalVariation, std::ostream& str, const bool fromStack, bool& allowStoreTT) noexcept
			{
				m_Heuristics.template beginMove<PLAYER>(m_Stack, move, true, m_Depth);
				variationType subVariation;
				bool allowStoreTTsubnode{ true };
				bool bEnded{ false };
				scoreType sc;
				{
					childType subnode(childType(*static_cast<const instanceType*>(this), move));
					sc = -subnode.template eval<VERBOSE, USE_TT>(-beta.plyDown(), -alpha.plyDown(), subVariation, str, allowStoreTTsubnode).plyUp();
				}
				const scoreType oldAlpha{ alpha };
				if (sc > alpha && sc < beta)
				{
					alpha = sc;
					allowStoreTT &= allowStoreTTsubnode;
					if constexpr (USE_TT)
					{
						if (allowStoreTT)
							m_Heuristics.transpositionTable().store(m_Stack, -1, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
					}
					bEnded = true;
				}
				if (sc > best)
				{
					allowStoreTT &= allowStoreTTsubnode;
					best = sc;
					if (sc >= beta)
					{
						if constexpr (USE_TT)
						{
							if (allowStoreTT)
								m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						}
						m_Heuristics.template endMoveRefuted<PLAYER, false>(m_Stack, move, true, m_Depth, best, evaluate(oldAlpha, best), fromStack);
						m_Heuristics.template endNodeCut<PLAYER>(m_Stack);
						return true;
					}
					principalVariation.combine(move, subVariation);
					bestmove = move;
				}
				if (!bEnded)
					m_Heuristics.template endMoveSilent<PLAYER>(m_Stack, move, false, m_Depth);
				else
					m_Heuristics.template endMoveAccepted<PLAYER, false>(m_Stack, move, false, m_Depth, alpha, evaluate(oldAlpha, best), fromStack);
				return false;
			}
			template<bool VERBOSE, bool USE_TT>
			constexpr bool qzwsearchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, std::ostream& str, const bool fromStack, bool& allowStoreTT) noexcept
			{
				m_Heuristics.beginMove(m_Stack, move, true, m_Depth);
				bool allowStoreTTsubnode{ true };
				scoreType sc;
				{
					childType subnode(childType(*static_cast<const instanceType*>(this), move));
					sc = -subnode.template zweval<VERBOSE, USE_TT>(-alpha.plyDown(), str, allowStoreTTsubnode).plyUp();
				}
				if (sc >= beta)
				{
					allowStoreTT &= allowStoreTTsubnode;
					best = sc;
					if constexpr (USE_TT)
					{
						if (allowStoreTT)
							m_Heuristics.transpositionTable().store(m_Stack, -1, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
					}
					m_Heuristics.template endMoveRefuted<PLAYER, false>(m_Stack, move, true, m_Depth, best, evaluate(alpha, best), fromStack);
					m_Heuristics.template endNodeCut<PLAYER>(m_Stack);
					return true;
				}
				m_Heuristics.template endMoveSilent<PLAYER>(m_Stack, move, false, m_Depth);
				return false;
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
			constexpr void printIndentation(std::ostream& str) const noexcept
			{
				for (int i = 0; i < m_DistanceFromRoot; i++)
					str << "    ";
			}
			constexpr scoreType evaluate(const scoreType alpha, const scoreType beta) noexcept
			{
				if ((alpha < m_EvalAlpha) || (beta > m_EvalBeta))
				{
					m_Eval = evaluatorType::evaluate(alpha, beta, m_Stack);
					m_EvalAlpha = alpha;
					m_EvalBeta = beta;
				}
				return m_Eval;
			}
			constexpr scoreType futileGap() const noexcept
			{
				return m_FutileGap;
			}
			constexpr scoreType moveFutilityValue(const movebitsType& move) const noexcept
			{
				return static_cast<const instanceType*>(this)->moveFutilityValue_Implementation(move);
			}
			constexpr bool canPruneMove(const movebitsType& move) const noexcept
			{
				return !generatorType::template isMoveCritical<PLAYER>(this->stack(), move);
			}
			constexpr bool canFutilityPruneMove(const movebitsType move) const noexcept
			{
				return moveFutilityValue(move) < this->futileGap();
			}
			constexpr static bool futilityPruningEnabled(const size_t depthRemaining) noexcept
			{
				return instanceType::futilityPruningEnabled_Implementation(depthRemaining);
			}
			constexpr static scoreType futilityMargin(const size_t depthRemaining, const stackType& stack) noexcept
			{
				return instanceType::futilityMargin_Implementation(depthRemaining, stack);
			}
			constexpr static scoreType futilityGlobalMargin(const size_t depthRemaining, const stackType& stack) noexcept
			{
				return instanceType::futilityGlobalMargin_Implementation(depthRemaining, stack);
			}
			constexpr bool pruningAllowed(const scoreType alpha, const scoreType beta) const noexcept
			{
				return alpha.isOpen() && beta.isOpen() && !this->stack().isPositionCritical();
			}
			constexpr static depthType nullMoveReduction(const size_t depthRemaining) noexcept
			{
				return instanceType::nullMoveReduction_Implementation(depthRemaining);
			}
			constexpr bool nullMoveAllowed() const noexcept
			{
				return static_cast<const instanceType*>(this)->nullMoveAllowed_Implementation();
			}
			template<bool VERBOSE, bool USE_TT>
			scoreType eval(scoreType alpha, scoreType beta, variationType& principalVariation, std::ostream& str, bool& allowStoreTT) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				if (!m_IsRunning)
				{
					allowStoreTT = false;
					return zero;
				}
				m_Heuristics.beginNode(m_Stack);
				scoreType early{ zero };
				if (earlyScore<false>(early, allowStoreTT))
				{
					m_Heuristics.endNodeEarly(m_Stack);
					return early;
				}
				movebitsType bestmove;
				bool hasLegalMove{ false };
				movebitsType move;
				const scoreType stand_pat{ evaluate(alpha, beta) };
				scoreType best{ stand_pat };
				if (best > alpha)
				{
					if (best >= beta)
					{
						m_Heuristics.endNodeLeaf(m_Stack);
						if constexpr (USE_TT)
							m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), best, transpositiontable<descriptorSearch>::flags_lower, movebitsType(0));
						return best;
					}
					alpha = best;
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
				}
				bool fromStack;
				allowStoreTT = true;
				if ((!hasLegalMove) && nextTacticalMove(move, fromStack))
				{
					hasLegalMove = true;
					if (this->qsearchSubNode<VERBOSE, USE_TT>(move, alpha, beta, best, bestmove, principalVariation, str, fromStack, allowStoreTT))
					{
						this->resetMoveGen();
						return best;
					}
				}
				if (!hasLegalMove)
				{
					allowStoreTT = true;
					m_Heuristics.endNodeLate(m_Stack);
					hasLegalMove = m_Stack.hasLegalMove(m_Depth, m_Heuristics.feedback());
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
				while (nextTacticalMove(move, fromStack))
				{
					if (this->qsearchSubNode<VERBOSE, USE_TT>(move, alpha, beta, best, bestmove, principalVariation, str, fromStack, allowStoreTT))
					{
						this->resetMoveGen();
						return best;
					}
				}
				m_Heuristics.endNodeLate(m_Stack);
				return alpha;
			}
			template<bool VERBOSE, bool USE_TT>
			scoreType zweval(scoreType beta, std::ostream& str, bool& allowStoreTT) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				if (!m_IsRunning)
				{
					allowStoreTT = false;
					return zero;
				}
				m_Heuristics.beginNode(m_Stack);
				scoreType alpha{ beta.zeroWindow() };
				scoreType early{ zero };
				if (earlyScore<true>(early, allowStoreTT))
				{
					m_Heuristics.endNodeEarly(m_Stack);
					return early;
				}
				movebitsType bestmove;
				bool hasLegalMove{ false };
				movebitsType move;
				constexpr const scoreType minimum{ scoreType::minimum() };
				scoreType best{ minimum };
				if constexpr (USE_TT)
				{
					scoreType ttScore;
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
				const scoreType stand_pat{ evaluate(alpha, beta) };
				best = scoreType::max(stand_pat, best);
				if (best > alpha)
				{
					if (best >= beta)
					{
						m_Heuristics.endNodeLeaf(m_Stack);
						if constexpr (USE_TT)
							m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), best, transpositiontable<descriptorSearch>::flags_lower, movebitsType(0));
						return best;
					}
					alpha = best;
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, depthType(-1), best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
				}
				bool fromStack;
				allowStoreTT = true;
				if ((!hasLegalMove) && nextTacticalMove(move, fromStack))
				{
					hasLegalMove = true;
					if (this->qzwsearchSubNode<VERBOSE, USE_TT>(move, alpha, beta, best, bestmove, str, fromStack, allowStoreTT))
					{
						this->resetMoveGen();
						return best;
					}
				}
				if (!hasLegalMove)
				{
					allowStoreTT = true;
					m_Heuristics.endNodeLate(m_Stack);
					hasLegalMove = m_Stack.hasLegalMove(m_Depth, m_Heuristics.feedback());
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
				while (nextTacticalMove(move, fromStack))
				{
					if (this->qzwsearchSubNode<VERBOSE, USE_TT>(move, alpha, beta, best, bestmove, str, fromStack, allowStoreTT))
					{
						this->resetMoveGen();
						return best;
					}
				}
				m_Heuristics.endNodeLate(m_Stack);
				this->resetMoveGen();
				return alpha;
			}
			template<bool VERBOSE, bool PRUNED>
			scoreType zwsearchLoop(bool& hasLegalMove, const depthType depthRemaining, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const uint_t<countPlayers, false> nullMoveHistory, std::ostream& str, bool& allowStoreTT) noexcept
			{
				movebitsType move;
				bool fromStack;
				if ((!hasLegalMove) && this->template nextMove<PRUNED>(depthRemaining, move, fromStack))
				{
					hasLegalMove = true;
					if (this->zwsearchSubNode<VERBOSE, PRUNED>(move, alpha, beta, best, bestmove, depthRemaining, noNullMove(nullMoveHistory), str, fromStack, allowStoreTT))
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
				while (this->template nextMove<PRUNED>(depthRemaining, move, fromStack))
				{
					bool allowStoreTTsubnode;
					if (this->zwsearchSubNode<VERBOSE, PRUNED>(move, alpha, beta, best, bestmove, depthRemaining, noNullMove(nullMoveHistory), str, fromStack, allowStoreTT))
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
			scoreType searchLoop(const depthType depthRemaining, scoreType& alpha, scoreType& beta, variationType& principalVariation, std::ostream& str, bool& allowStoreTT) noexcept
			{
				bool hasLegalMove{ false };
				movebitsType move;
				constexpr const scoreType minimum{ scoreType::minimum() };
				scoreType best{ minimum };
				movebitsType bestmove;
				bool fromStack;
				allowStoreTT = true;
				if ((!hasLegalMove) && this->template nextMove<false>(depthRemaining, move, fromStack))
				{
					hasLegalMove = true;
					if (this->searchSubNode<VERBOSE, false>(move, alpha, beta, best, bestmove, depthRemaining, principalVariation, str, fromStack, allowStoreTT))
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
				while (this->template nextMove<false>(depthRemaining, move, fromStack))
				{
					if (this->searchSubNode<VERBOSE, true>(move, alpha, beta, best, bestmove, depthRemaining, principalVariation, str, fromStack, allowStoreTT))
					{
						this->resetMoveGen();
						return best;
					}
				}
				m_Heuristics.endNodeLate(m_Stack);
				this->resetMoveGen();
				return alpha;
			}
		public:
			template<bool VERBOSE>
			scoreType zwsearch(scoreType beta, const depthType depthRemaining, const uint_t<countPlayers, false> nullMoveHistory, std::ostream& str, bool& allowStoreTT) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				if (!m_IsRunning)
				{
					allowStoreTT = false;
					return zero;
				}
				scoreType alpha{ beta.zeroWindow() };
				if (depthRemaining >= depthType(0))
				{
					m_Heuristics.beginNode(m_Stack);
					scoreType early{ zero };
					if (earlyScore<true>(early, allowStoreTT))
					{
						m_Heuristics.endNodeEarly(m_Stack);
						return early;
					}
					bool hasLegalMove{ false };
					bool allowNMP{ true };
					constexpr const scoreType minimum{ scoreType::minimum() };
					scoreType best{ minimum };
					movebitsType bestmove;
					if constexpr (searchTranspositionTable)
					{
						scoreType ttScore;
						movebitsType ttMove;
						const std::uint8_t lookUp{ m_Heuristics.transpositionTable().probe(m_Stack, depthRemaining, alpha, beta, ttScore, ttMove) };
						if ((lookUp & transpositiontable<descriptorSearch>::flags_hit) != transpositiontable<descriptorSearch>::flags_unused)
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
							{
								best = ttScore;
							}
						}
						else if ((lookUp & transpositiontable<descriptorSearch>::flags_noNMP) != transpositiontable<descriptorSearch>::flags_unused)
						{
							allowNMP = false;
						}
					}
					allowStoreTT = true;
					bool bPruned{ false };
					if constexpr (pruneNullmove || pruneFutility)
					{
						if (this->pruningAllowed(alpha, beta))
						{
							if constexpr (pruneNullmove)
							{
								if (allowNMP && checkNullMove(nullMoveHistory) && this->nullMoveAllowed())
								{
									bool allowStoreTTsubnode;
									constexpr const scoreType zero{ scoreType::zero() };
									scoreType nmsc{ zero };
									const depthType remainingNullMoveDepth{ static_cast<depthType>(depthRemaining - nullMoveReduction(depthRemaining) - 1) };
									{
										childType subnode(childType(*static_cast<const instanceType*>(this), generatorType::nullMove()));
										constexpr const scoreType atom{ scoreType::atom() };
										nmsc = -subnode.template zwsearch<VERBOSE>((atom - beta).plyDown(), remainingNullMoveDepth, doNullMove(nullMoveHistory), str, allowStoreTTsubnode).plyUp();
									}
									if (nmsc >= beta)
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
							if constexpr (pruneFutility)
							{
								if (instanceType::futilityPruningEnabled(depthRemaining))
								{
									const scoreType futileGlobalScore{ alpha - instanceType::futilityGlobalMargin(depthRemaining, m_Stack) };
									constexpr const scoreType maximum{ scoreType::maximum() };
									const scoreType eval{ evaluate(futileGlobalScore, maximum) };
									m_FutileGap = alpha - eval - instanceType::futilityMargin(depthRemaining, m_Stack);
									m_FutilityPruningAllowed = m_FutileGap >= zero;
									bPruned |= futileGlobalScore >= eval;
								}
							}
						}
					}
					if (bPruned)
						return this->template zwsearchLoop<VERBOSE, true>(hasLegalMove, depthRemaining, alpha, beta, best, bestmove, nullMoveHistory, str, allowStoreTT);
					else
						return this->template zwsearchLoop<VERBOSE, false>(hasLegalMove, depthRemaining, alpha, beta, best, bestmove, nullMoveHistory, str, allowStoreTT);
				}
				else
				{
					return this->template zweval<VERBOSE, searchTranspositionTable>(beta, str, allowStoreTT);
				}
			}
			template<bool VERBOSE>
			scoreType search(scoreType alpha, scoreType beta, const depthType depthRemaining, variationType& principalVariation, std::ostream& str, bool& allowStoreTT) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				if (!m_IsRunning)
				{
					allowStoreTT = false;
					return zero;
				}
				if (depthRemaining >= depthType(0))
				{
					m_Heuristics.beginNode(m_Stack);
					scoreType early{ zero };
					if (earlyScore<false>(early, allowStoreTT))
					{
						m_Heuristics.endNodeEarly(m_Stack);
						return early;
					}
					if constexpr (pruneNullmove || pruneFutility)
					{
						if (this->pruningAllowed(alpha, beta))
						{
							if constexpr (pruneFutility)
							{
								if (instanceType::futilityPruningEnabled(depthRemaining))
								{
									const scoreType futileGlobalScore{ alpha - instanceType::futilityGlobalMargin(depthRemaining, m_Stack) };
									constexpr const scoreType maximum{ scoreType::maximum() };
									const scoreType eval{ evaluate(futileGlobalScore, maximum) };
									m_FutileGap = alpha - eval - instanceType::futilityMargin(depthRemaining, m_Stack);
									m_FutilityPruningAllowed = m_FutileGap >= zero;
								}
							}
						}
					}
					return this->template searchLoop<VERBOSE>(depthRemaining, alpha, beta, principalVariation, str, allowStoreTT);
				}
				else
				{
					return this->template eval<VERBOSE, searchTranspositionTable>(alpha, beta, principalVariation, str, allowStoreTT);
				}
			}
			node() = delete;
			constexpr node(const node&) = default;
			constexpr node(node&&) = default;
			constexpr node& operator=(const node&) = default;
			node(const stackType& stack, std::atomic_bool& isRunning, heuristicsType& heuristics, const size_t depth) noexcept :
				m_Stack{ stack },
				m_IsRunning{ isRunning },
				m_Heuristics{ heuristics },
				m_MovesTT{ ttmovesType() },
				m_MovesKiller{ killermovesType() },
				m_TacticalMovesTT{ ttmovesType() },
				m_TacticalMovesKiller{ killermovesType() },
				m_Moves{ movelistType() },
				m_CriticalMoves{ movelistType() },
				m_TacticalMoves{ movelistType() },
				m_TacticalMoveGeneratorStage{ -1 },
				m_MoveGeneratorStage{ -1 },
				m_Move{ 0 },
				m_CriticalMove{ 0 },
				m_TacticalMove{ 0 },
				m_NeedsSorting{ false },
				m_NeedsTacticalSorting{ false },
				m_FutilityPruningAllowed{ false },
				m_DistanceFromRoot{ 0 },
				m_Depth{ depth }
			{
				PYGMALION_ASSERT(stack.position().movingPlayer() == movingPlayer);
				if constexpr (searchTranspositionTable)
					m_Heuristics.transpositionTable().prefetch(m_Stack);
				constexpr const scoreType minimum{ scoreType::minimum() };
				constexpr const scoreType maximum{ scoreType::maximum() };
				constexpr const scoreType zero{ scoreType::zero() };
				m_EvalAlpha = maximum;
				m_EvalBeta = minimum;
				m_Eval = zero;
				m_FutileGap = zero;
			}
			node(const parentType& parent, const movebitsType moveBits) noexcept :
				m_Stack(parent.m_Stack, moveBits),
				m_IsRunning{ parent.m_IsRunning },
				m_Heuristics{ parent.m_Heuristics },
				m_MovesTT{ ttmovesType() },
				m_MovesKiller{ killermovesType() },
				m_TacticalMovesTT{ ttmovesType() },
				m_TacticalMovesKiller{ killermovesType() },
				m_Moves{ movelistType() },
				m_CriticalMoves{ movelistType() },
				m_TacticalMoves{ movelistType() },
				m_TacticalMoveGeneratorStage{ -1 },
				m_MoveGeneratorStage{ -1 },
				m_Move{ 0 },
				m_CriticalMove{ 0 },
				m_TacticalMove{ 0 },
				m_NeedsSorting{ false },
				m_NeedsTacticalSorting{ false },
				m_FutilityPruningAllowed{ false },
				m_DistanceFromRoot{ parent.m_DistanceFromRoot + 1 },
				m_Depth{ parent.m_Depth + 1 }
			{
				if constexpr (searchTranspositionTable)
					m_Heuristics.transpositionTable().prefetch(m_Stack);
				constexpr const scoreType minimum{ scoreType::minimum() };
				constexpr const scoreType maximum{ scoreType::maximum() };
				constexpr const scoreType zero{ scoreType::zero() };
				m_EvalAlpha = maximum;
				m_EvalBeta = minimum;
				m_Eval = zero;
				m_FutileGap = zero;
			}
			~node() noexcept = default;
			template<bool VERBOSE>
			scoreType searchRoot(const depthType depthRemaining, variationType& principalVariation, std::ostream& str) noexcept
			{
				bool allowStoreTT;
				constexpr const scoreType minimum{ scoreType::minimum() };
				constexpr const scoreType maximum{ scoreType::maximum() };
				return this->template search<VERBOSE>(minimum, maximum, depthRemaining, principalVariation, str, allowStoreTT);
			}
			constexpr const stackType& stack() const noexcept
			{
				return m_Stack;
			}
		};
	};
}