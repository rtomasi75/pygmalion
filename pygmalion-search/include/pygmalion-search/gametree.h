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
			using dataType = typename evaluatorType::dataType;
		private:
			stackType m_Stack;
			dataType m_Data;
			heuristicsType& m_Heuristics;
			const std::vector<scoreType>& m_Parameters;
			const int m_DistanceFromRoot;
			movelistType m_Moves;
			movelistType m_CriticalMoves;
			movelistType m_TacticalMoves;
			quietKillermovesType m_QuietMovesKiller;
			tacticalKillermovesType m_TacticalMovesKiller;
			ttmovesType m_MovesTT;
			ttmovesType m_TacticalMovesTT;
			int m_MoveGeneratorStage;
			int m_TacticalMoveGeneratorStage;
			bool m_NeedsSorting;
			bool m_FutilityPruningAllowed;
			bool m_DeltaPruningAllowed;
			bool m_IsTTMove;
			bool m_IsKiller;
			bool m_IsTacticalKiller;
			signal& m_Terminate;
			scoreType m_EvalAlpha;
			scoreType m_EvalBeta;
			scoreType m_Eval;
			scoreType m_FutileGap;
			scoreType m_DeltaGap;
			indexType m_MoveTT;
			indexType m_TacticalMoveTT;
			indexType m_QuietMoveKiller;
			indexType m_TacticalMoveKiller;
			indexType m_Move;
			indexType m_CriticalMove;
			indexType m_TacticalMove;
			size_t m_Depth;
			nodecounterType m_MoveNodecount;
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
			template<int QSPHASE>
			PYGMALION_INLINE void beginMove(const movebitsType moveBits) noexcept
			{
				m_MoveNodecount = m_Heuristics.template beginMove<PLAYER, QSPHASE>(m_Stack, moveBits, m_Depth);
			}
			template<bool PRUNED, int QSPHASE>
			PYGMALION_INLINE void endMoveAccepted(const movebitsType moveBits, const depthType depthRemaining) noexcept
			{
				const nodecounterType count{ m_Heuristics.template endMoveAccepted<PLAYER, PRUNED, QSPHASE>(m_MoveNodecount, m_Stack, moveBits, m_Depth, depthRemaining) };
			}
			template<bool PRUNED, int QSPHASE>
			PYGMALION_INLINE void endMoveRefuted(const movebitsType moveBits, const depthType depthRemaining) noexcept
			{
				const nodecounterType count{ m_Heuristics.template endMoveRefuted<PLAYER, PRUNED, QSPHASE>(m_MoveNodecount, m_Stack, moveBits, m_Depth, depthRemaining) };
			}
			template<bool PRUNED, int QSPHASE>
			PYGMALION_INLINE void endMoveSilent(const movebitsType moveBits, const depthType depthRemaining) noexcept
			{
				m_Heuristics.template endMoveSilent<PLAYER, QSPHASE>(m_MoveNodecount, m_Stack, moveBits, m_Depth, depthRemaining);
			}
			template<bool PRUNED, int QSPHASE>
			PYGMALION_INLINE void endMoveFutile(const movebitsType moveBits) noexcept
			{
				m_Heuristics.template endMoveFutile<PLAYER, QSPHASE>(m_Stack, moveBits, m_Depth);
			}
			template<bool PRUNED, int QSPHASE>
			PYGMALION_INLINE void endMoveDelta(const movebitsType moveBits) noexcept
			{
				m_Heuristics.template endMoveDelta<PLAYER, QSPHASE>(m_Stack, moveBits, m_Depth);
			}
			template<bool LAZY>
			PYGMALION_INLINE bool earlyScore(scoreType& score, bool& allowStoreTT) const noexcept
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
			PYGMALION_INLINE static scoreType createAspiration(const scoreType sc, const scoreType window) noexcept
			{
				if (sc.isOpen())
					return sc + window;
				else
					return sc;
			}
			template<bool ANALYZE>
			PYGMALION_INLINE scoreType searchMove(const movebitsType move, const scoreType alpha, const scoreType beta, const depthType depthRemaining, variationType& principalVariation, bool& allowStoreTT, indexType* pCurrentMove) noexcept
			{
				if constexpr (searchIterativeDeepening && !(ANALYZE))
				{
					scoreType sc;
					childType subnode(childType(*static_cast<const instanceType*>(this), move));
					if (depthRemaining >= 0)
					{
						if constexpr (searchAspiration)
						{
							constexpr const scoreType minimum{ scoreType::minimum() };
							constexpr const scoreType maximum{ scoreType::maximum() };
							sc = evaluate(alpha, beta);
							scoreType lowAspiration{ sc };
							scoreType highAspiration{ sc };
							PYGMALION_TUNABLE const scoreType initialAspirationWindow{ evaluatorType::initialAspirationWindowSize() };
							constexpr const scoreType atom{ scoreType::atom() };
							scoreType delta{ initialAspirationWindow };
							for (depthType d = -1; d < depthRemaining; ++d)
							{
								bool bExact{ false };
								bool bLow{ true };
								bool bHigh{ true };
								constexpr const size_t countWindows{ evaluatorType::countAspirationWindows() };
								for (size_t i = 0; i < countWindows; i++)
								{
									const scoreType oldScore{ sc };
									const scoreType oldLow{ lowAspiration };
									const scoreType oldHigh{ highAspiration };
									if (sc.isOpen())
									{
										lowAspiration = scoreType::min(bLow ? (lowAspiration - delta) : (oldHigh - atom), alpha);
										highAspiration = scoreType::max(bHigh ? (highAspiration + delta) : (oldLow + atom), beta);
									}
									else
									{
										if (sc.isWinning())
										{
											lowAspiration = scoreType::min(oldHigh - atom, alpha);
											highAspiration = scoreType::max(maximum, beta);
										}
										else
										{
											lowAspiration = scoreType::min(minimum, alpha);
											highAspiration = scoreType::max(oldLow + atom, beta);
										}
									}
									if (lowAspiration.isLosing())
										lowAspiration = minimum;
									if (highAspiration.isWinning())
										highAspiration = maximum;
									sc = -subnode.search(-highAspiration.plyDown(), -lowAspiration.plyDown(), d, principalVariation, allowStoreTT).plyUp();
									if ((sc > lowAspiration) && (sc < highAspiration))
									{
										bExact = true;
										break;
									}
									if ((sc <= alpha) || (sc >= beta))
									{
										bExact = true;
										break;
									}
									if (sc <= lowAspiration)
									{
										delta = 2 * (oldScore - sc + atom);
										bLow = true;
									}
									else
										bLow = false;
									if (sc >= highAspiration)
									{
										delta = 2 * (sc - oldScore + atom);
										bHigh = true;
									}
									else
										bHigh = false;
								}
								if (!bExact)
								{
									sc = -subnode.search(-beta.plyDown(), -alpha.plyDown(), d, principalVariation, allowStoreTT).plyUp();
								}
							}
							return sc;
						}
						else
						{
							for (depthType d = -1; d < depthRemaining; ++d)
							{
								sc = -subnode.search(-beta.plyDown(), -alpha.plyDown(), d, principalVariation, allowStoreTT).plyUp();
							}
						}
					}
					else
						sc = -subnode.search(-beta.plyDown(), -alpha.plyDown(), depthType(-1), principalVariation, allowStoreTT).plyUp();
					if constexpr (ANALYZE)
						(*pCurrentMove)++;
					return sc;
				}
				else
				{
					childType subnode(childType(*static_cast<const instanceType*>(this), move));
					if constexpr (ANALYZE)
						(*pCurrentMove)++;
					return -subnode.search(-beta.plyDown(), -alpha.plyDown(), depthRemaining - depthType(1), principalVariation, allowStoreTT).plyUp();
				}
			}
			PYGMALION_INLINE scoreType zwsearchMove(const movebitsType move, const scoreType alpha, const depthType& depthRemaining, const uint_t<countPlayers, false> nullMoveHistory, bool& allowStoreTT, const knuthType expectedNodeType) const noexcept
			{
				childType subnode{ childType(*this, move) };
				return -subnode.zwsearch(-alpha.plyDown(), depthRemaining - depthType(1), nullMoveHistory, allowStoreTT, expectedNodeType).plyUp();
			}
			template<bool SCOUT, bool ANALYZE>
			PYGMALION_INLINE bool searchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const depthType depthRemaining, variationType& principalVariation, bool& allowStoreTT, indexType* pCurrentMove)  noexcept
			{
				this->template beginMove<-1>(move);
				variationType subVariation;
				bool bCanPrune{ true };
				if constexpr (pruneFutility || lateMoveReductions)
					bCanPrune = this->canPruneMove(move);
				if constexpr (SCOUT)
				{
					if constexpr (pruneFutility)
					{
						if (m_FutilityPruningAllowed && bCanPrune && this->canFutilityPruneMove(move))
						{
							this->template endMoveFutile<false, -1>(move);
							return false;
						}
					}
					bool bEnded{ false };
					scoreType sc;
					bool allowStoreTTsubnode{ true };
					if constexpr (searchScout && !ANALYZE)
					{
						const bool bIsLateMove{ !(m_IsKiller || m_IsTacticalKiller || m_IsTTMove) };
						if (bIsLateMove)
						{
							if constexpr (lateMoveReductions)
							{
								const bool bAllowLMR{ bCanPrune && (depthRemaining >= lateMoveReductionMinDepth) && !(m_Stack.isPositionCritical() || generatorType::isMoveTactical(m_Stack,move)) };
								if (bAllowLMR)
									sc = this->zwsearchMove(move, alpha, depthRemaining - lateMoveReductionPlies, m_EmptyNullMoveHistory, allowStoreTTsubnode, CUTnode);
								else
									sc = this->zwsearchMove(move, alpha, depthRemaining, m_EmptyNullMoveHistory, allowStoreTTsubnode, CUTnode);
							}
							else
								sc = this->zwsearchMove(move, alpha, depthRemaining, m_EmptyNullMoveHistory, allowStoreTTsubnode, CUTnode);
							if (sc > alpha && sc < beta)
								sc = this->template searchMove<false>(move, alpha, beta, depthRemaining, subVariation, allowStoreTTsubnode, nullptr);
						}
						else
							sc = this->template searchMove<false>(move, alpha, beta, depthRemaining, subVariation, allowStoreTTsubnode, nullptr);
						if (sc > best)
						{
							allowStoreTT &= allowStoreTTsubnode;
							best = sc;
							if (sc > alpha)
							{
								if (sc >= beta)
								{
									if constexpr (searchTranspositionTable)
									{
										if (allowStoreTT)
											m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
									}
									this->template endMoveRefuted<false, -1>(move, depthRemaining);
									m_Heuristics.endNodeCut(m_Stack);
									return true;
								}
								allowStoreTT &= allowStoreTTsubnode;
								if constexpr (searchTranspositionTable)
								{
									if (allowStoreTT)
										m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
								}
								this->template endMoveAccepted<false, -1>(move, depthRemaining);
								alpha = sc;
							}
							else
								this->template endMoveSilent<false, -1>(move, depthRemaining);
							principalVariation.combine(move, subVariation);
							bestmove = move;
						}
						else
							this->template endMoveSilent<false, -1>(move, depthRemaining);
					}
					else
					{
						sc = this->template searchMove<ANALYZE>(move, alpha, beta, depthRemaining, subVariation, allowStoreTTsubnode, pCurrentMove);
						if (sc > best)
						{
							allowStoreTT &= allowStoreTTsubnode;
							best = sc;
							if (sc > alpha)
							{
								if (sc >= beta)
								{
									if constexpr (searchTranspositionTable)
									{
										if (allowStoreTT)
											m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
									}
									this->template endMoveRefuted<false, -1>(move, depthRemaining);
									m_Heuristics.endNodeCut(m_Stack);
									return true;
								}
								allowStoreTT &= allowStoreTTsubnode;
								if constexpr (searchTranspositionTable)
								{
									if (allowStoreTT)
										m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
								}
								this->template endMoveAccepted<false, -1>(move, depthRemaining);
								alpha = sc;
							}
							else
								this->template endMoveSilent<false, -1>(move, depthRemaining);
							principalVariation.combine(move, subVariation);
							bestmove = move;
						}
						else
							this->template endMoveSilent<false, -1>(move, depthRemaining);
					}
					return false;
				}
				else
				{
					bool allowStoreTTsubnode{ true };
					const scoreType sc{ this->template searchMove<ANALYZE>(move, alpha, beta, depthRemaining, subVariation, allowStoreTTsubnode, pCurrentMove) };
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
							this->template endMoveRefuted<false, -1>(move, depthRemaining);
							return true;
						}
						principalVariation.combine(move, subVariation);
						bestmove = move;
						if constexpr (searchTranspositionTable)
						{
							if (allowStoreTT)
								m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, best, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
						}
						this->template endMoveAccepted<false, -1>(move, depthRemaining);
						alpha = best;
					}
					else
						this->template endMoveSilent<false, -1>(move, depthRemaining);
					return false;
				}
			}
			template<bool PRUNED>
			PYGMALION_INLINE bool zwsearchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const depthType depthRemaining, const uint_t<countPlayers, false> nullMoveHistory, bool& allowStoreTT, const knuthType expectedNodeType) noexcept
			{
				this->template beginMove<-1>(move);
				bool bCanPrune{ true };
				if constexpr (((!PRUNED) && pruneFutility) || lateMoveReductions)
					bCanPrune = this->canPruneMove(move);
				if constexpr (!PRUNED)
				{
					if constexpr (pruneFutility)
					{
						if (m_FutilityPruningAllowed && bCanPrune && this->canFutilityPruneMove(move))
						{
							this->template endMoveFutile<PRUNED, -1>(move);
							return false;
						}
					}
				}
				bool allowStoreTTsubnode{ true };
				const bool bIsLateMove{ !(m_IsKiller || m_IsTacticalKiller || m_IsTTMove || !generatorType::isMoveTactical(m_Stack,move)) };
				scoreType sc;
				if constexpr (lateMoveReductions)
				{
					if (bIsLateMove)
					{
						const bool bAllowLMR{ bCanPrune && (depthRemaining >= lateMoveReductionMinDepth) && !(m_Stack.isPositionCritical() || generatorType::isMoveTactical(m_Stack,move)) };
						if (bAllowLMR)
						{
							sc = this->zwsearchMove(move, alpha, depthRemaining - lateMoveReductionPlies, nullMoveHistory, allowStoreTTsubnode, bIsLateMove ? ALLnode : expectedNodeType);
							if (sc > alpha)
								sc = this->zwsearchMove(move, alpha, depthRemaining, nullMoveHistory, allowStoreTTsubnode, bIsLateMove ? ALLnode : expectedNodeType);
						}
						else
							sc = this->zwsearchMove(move, alpha, depthRemaining, nullMoveHistory, allowStoreTTsubnode, bIsLateMove ? ALLnode : expectedNodeType);
					}
					else
						sc = this->zwsearchMove(move, alpha, depthRemaining, nullMoveHistory, allowStoreTTsubnode, bIsLateMove ? ALLnode : expectedNodeType);
				}
				else
					sc = this->zwsearchMove(move, alpha, depthRemaining, nullMoveHistory, allowStoreTTsubnode, bIsLateMove ? ALLnode : expectedNodeType);
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
						this->template endMoveRefuted<PRUNED, -1>(move, depthRemaining);
						m_Heuristics.endNodeCut(m_Stack);
						return true;
					}
					bestmove = move;
				}
				this->template endMoveSilent<PRUNED, -1>(move, depthRemaining);
				return false;
			}
			template<int QSDEPTH, bool USE_TT>
			PYGMALION_INLINE bool qsearchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, variationType& principalVariation, bool& allowStoreTT) noexcept
			{
				constexpr const int QSPHASE{ (QSDEPTH < (countQsPhase1Plies + countQsPhase2Plies)) ? ((QSDEPTH < countQsPhase1Plies) ? 0 : 1) : 2 };
				this->template beginMove<QSPHASE>(move);
				if constexpr (pruneDelta)
				{
					if (m_DeltaPruningAllowed && this->canPruneMove(move) && this->canDeltaPruneMove(move))
					{
						this->template endMoveDelta<false, QSPHASE>(move);
						return false;
					}
				}
				variationType subVariation;
				bool allowStoreTTsubnode{ true };
				bool bEnded{ false };
				scoreType sc;
				if constexpr (QSDEPTH >= (countQsPhase1Plies + countQsPhase2Plies + countQsPhase3Plies))
				{
					sc = evaluate(alpha, beta) + evaluatorType::template staticExchangeScore<PLAYER>(m_Stack.position(), move, m_Stack.materialTable()).template makeSubjective<PLAYER>();
					allowStoreTTsubnode = false;
				}
				else
				{
					childType subnode(childType(*static_cast<const instanceType*>(this), move));
					sc = -subnode.template eval<QSDEPTH + 1, USE_TT>(-beta.plyDown(), -alpha.plyDown(), subVariation, allowStoreTTsubnode).plyUp();
				}
				const scoreType oldAlpha{ alpha };
				constexpr const depthType ttDraft{ node::template qsearchDraft<QSDEPTH>() };
				if (sc > alpha && sc < beta)
				{
					alpha = sc;
					allowStoreTT &= allowStoreTTsubnode;
					if constexpr (USE_TT)
					{
						if (allowStoreTT)
						{
							m_Heuristics.transpositionTable().store(m_Stack, ttDraft, sc, transpositiontable<descriptorSearch>::flags_upper | transpositiontable<descriptorSearch>::flags_move, move);
						}
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
							{
								m_Heuristics.transpositionTable().store(m_Stack, ttDraft, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
							}
						}
						this->template endMoveRefuted<false, QSPHASE>(move, ttDraft);
						m_Heuristics.template endNodeCut<PLAYER>(m_Stack);
						return true;
					}
					principalVariation.combine(move, subVariation);
					bestmove = move;
				}
				if (!bEnded)
					this->template endMoveSilent<false, QSPHASE>(move, ttDraft);
				else
					this->template endMoveAccepted<false, QSPHASE>(move, ttDraft);
				return false;
			}
			template<int QSDEPTH, bool USE_TT>
			PYGMALION_INLINE bool qzwsearchSubNode(const movebitsType move, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, bool& allowStoreTT, const knuthType expectedNodeType) noexcept
			{
				constexpr const int QSPHASE{ (QSDEPTH < (countQsPhase1Plies + countQsPhase2Plies)) ? ((QSDEPTH < countQsPhase1Plies) ? 0 : 1) : 2 };
				this->template beginMove<QSPHASE>(move);
				if constexpr (pruneDelta)
				{
					if (m_DeltaPruningAllowed && this->canPruneMove(move) && this->canDeltaPruneMove(move))
					{
						this->template endMoveDelta<false, QSPHASE>(move);
						return false;
					}
				}
				bool allowStoreTTsubnode{ true };
				scoreType sc;
				if constexpr (QSDEPTH >= (countQsPhase1Plies + countQsPhase2Plies + countQsPhase3Plies))
				{
					sc = evaluate(alpha, beta) + evaluatorType::template staticExchangeScore<PLAYER>(m_Stack.position(), move, m_Stack.materialTable()).template makeSubjective<PLAYER>();
					allowStoreTTsubnode = false;
				}
				else
				{
					childType subnode(childType(*static_cast<const instanceType*>(this), move));
					sc = -subnode.template zweval<QSDEPTH + 1, USE_TT>(-alpha.plyDown(), allowStoreTTsubnode, expectedNodeType).plyUp();
				}
				constexpr const depthType ttDraft{ node::template qsearchDraft<QSDEPTH>() };
				if (sc >= beta)
				{
					allowStoreTT &= allowStoreTTsubnode;
					best = sc;
					if constexpr (USE_TT)
					{
						if (allowStoreTT)
						{
							m_Heuristics.transpositionTable().store(m_Stack, ttDraft, best, transpositiontable<descriptorSearch>::flags_lower | transpositiontable<descriptorSearch>::flags_move, move);
						}
					}
					this->template endMoveRefuted<false, QSPHASE>(move, ttDraft);
					m_Heuristics.template endNodeCut<PLAYER>(m_Stack);
					return true;
				}
				this->template endMoveSilent<false, QSPHASE>(move, ttDraft);
				return false;
			}
			PYGMALION_INLINE static uint_t<countPlayers, false> noNullMove(const uint_t<countPlayers, false> nullMoveHistory) noexcept
			{
				return nullMoveHistory << 1;
			}
			PYGMALION_INLINE static uint_t<countPlayers, false> doNullMove(uint_t<countPlayers, false> nullMoveHistory) noexcept
			{
				nullMoveHistory <<= 1;
				nullMoveHistory[0] = true;
				return nullMoveHistory;
			}
			PYGMALION_INLINE static bool checkNullMove(const uint_t<countPlayers, false> nullMoveHistory) noexcept
			{
				return !nullMoveHistory[countPlayers - 1];
			}
			constexpr static inline uint_t<countPlayers, false> m_EmptyNullMoveHistory{ uint_t<countPlayers, false>(0) };
			PYGMALION_INLINE scoreType futileGap() const noexcept
			{
				return m_FutileGap;
			}
			PYGMALION_INLINE scoreType deltaGap() const noexcept
			{
				return m_DeltaGap;
			}
			PYGMALION_INLINE scoreType moveFutilityValue(const movebitsType& move) const noexcept
			{
				return static_cast<const instanceType*>(this)->moveFutilityValue_Implementation(move);
			}
			PYGMALION_INLINE scoreType moveDeltaValue(const movebitsType& move) const noexcept
			{
				return static_cast<const instanceType*>(this)->moveDeltaValue_Implementation(move);
			}
			PYGMALION_INLINE bool canPruneMove(const movebitsType& move) const noexcept
			{
				return !generatorType::template isMoveCritical<PLAYER>(this->stack(), move);
			}
			PYGMALION_INLINE bool canDeltaPruneMove(const movebitsType move) const noexcept
			{
				return moveDeltaValue(move) < this->deltaGap();
			}
			PYGMALION_INLINE bool canFutilityPruneMove(const movebitsType move) const noexcept
			{
				return moveFutilityValue(move) < this->futileGap();
			}
			PYGMALION_INLINE static bool futilityPruningEnabled(const size_t depthRemaining) noexcept
			{
				return instanceType::futilityPruningEnabled_Implementation(depthRemaining);
			}
			PYGMALION_INLINE scoreType futilityMargin(const size_t depthRemaining, const stackType& stack) const noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				constexpr const squaresType none{ squaresType::none() };
				const scoreType positionalMargin{ stack.delta().maxQuietChange(stackType::MovingPlayer,stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) };
				playerType player{ stackType::NextPlayer };
				scoreType margin{ positionalMargin };
				size_t d{ 0 };
				while (depthRemaining > d)
				{
					const piecemaskType playerPieces{ stack.position().pieceMask(player) };
					const piecemaskType opponentPieces{ stack.position().opponentPieceMask(player) };
					const scoreType quietMargin{ stack.delta().maxQuietChange(stackType::MovingPlayer,player,playerPieces) };
					const scoreType captureMargin{ stack.delta().maxCaptureChange(stackType::MovingPlayer,player,playerPieces,opponentPieces) };
					const squaresType promotionOrigins{ none };
					bool bPromotionPossible{ false };
					for (const auto promoPiece : (generatorType::promotionPieces(player)& stack.position().pieceMask(player)))
					{
						if (stack.position().pieceOccupancy(promoPiece) & stack.position().playerOccupancy(player) & generatorType::promotionOrigins(player, promoPiece))
						{
							bPromotionPossible = true;
							break;
						}
					}
					const scoreType plyMargin{ scoreType::max(quietMargin, captureMargin) };
					scoreType promoMargin;
					if (bPromotionPossible)
					{
						const scoreType promotionMargin{ stack.delta().maxPromotionChange(stackType::MovingPlayer,player,playerPieces) };
						const scoreType promoCaptureMargin{ stack.delta().maxPromoCaptureChange(stackType::MovingPlayer,player,playerPieces,opponentPieces) };
						promoMargin = scoreType::max(promotionMargin, promoCaptureMargin);
					}
					else
						promoMargin = zero;
					margin += scoreType::max(promoMargin, plyMargin);
					d++;
					player++;
				}
				return margin;
			}
			PYGMALION_INLINE scoreType deltaMargin(const stackType& stack) const noexcept
			{
				return static_cast<const instanceType*>(this)->deltaMargin_Implementation(stack);
			}
			PYGMALION_INLINE scoreType futilityGlobalMargin(const size_t depthRemaining, const stackType& stack) const noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				constexpr const squaresType none{ squaresType::none() };
				playerType player{ stackType::MovingPlayer };
				scoreType margin{ zero };
				size_t d{ 0 };
				while (depthRemaining >= d)
				{
					const piecemaskType playerPieces{ stack.position().pieceMask(player) };
					const piecemaskType opponentPieces{ stack.position().opponentPieceMask(player) };
					const scoreType quietMargin{ stack.delta().maxQuietChange(stackType::MovingPlayer,player,playerPieces) };
					const scoreType captureMargin{ stack.delta().maxCaptureChange(stackType::MovingPlayer,player,playerPieces,opponentPieces) };
					const squaresType promotionOrigins{ none };
					bool bPromotionPossible{ false };
					for (const auto promoPiece : (generatorType::promotionPieces(player)& stack.position().pieceMask(player)))
					{
						if (stack.position().pieceOccupancy(promoPiece) & stack.position().playerOccupancy(player) & generatorType::promotionOrigins(player, promoPiece))
						{
							bPromotionPossible = true;
							break;
						}
					}
					const scoreType plyMargin{ scoreType::max(quietMargin, captureMargin) };
					scoreType promoMargin;
					if (bPromotionPossible)
					{
						const scoreType promotionMargin{ stack.delta().maxPromotionChange(stackType::MovingPlayer,player,playerPieces) };
						const scoreType promoCaptureMargin{ stack.delta().maxPromoCaptureChange(stackType::MovingPlayer,player,playerPieces,opponentPieces) };
						promoMargin = scoreType::max(promotionMargin, promoCaptureMargin);
					}
					else
						promoMargin = zero;
					margin += scoreType::max(promoMargin, plyMargin);
					d++;
					player++;
				}
				return margin;
			}
			PYGMALION_INLINE scoreType deltaGlobalMargin(const stackType& stack) const noexcept
			{
				return static_cast<const instanceType*>(this)->deltaGlobalMargin_Implementation(stack);
			}
			PYGMALION_INLINE bool pruningAllowed(const scoreType alpha, const scoreType beta) const noexcept
			{
				return alpha.isOpen() && beta.isOpen() && !this->stack().isPositionCritical();
			}
			PYGMALION_INLINE static depthType nullMoveReduction(const size_t depthRemaining) noexcept
			{
				return instanceType::nullMoveReduction_Implementation(depthRemaining);
			}
			PYGMALION_INLINE bool nullMoveAllowed() const noexcept
			{
				return static_cast<const instanceType*>(this)->nullMoveAllowed_Implementation();
			}
			template<int QSDEPTH>
			constexpr static depthType qsearchDraft() noexcept
			{
				return static_cast<depthType>(-(QSDEPTH + 1));
				/*			if constexpr (QSDEPTH < countQsPhase1Plies)
								return static_cast<depthType>(-1);
							else if constexpr (QSDEPTH < countQsPhase2Plies)
								return static_cast<depthType>(-2);
							else if constexpr (QSDEPTH < countQsPhase3Plies)
								return static_cast<depthType>(-3);
							else
								return static_cast<depthType>(-4);*/
			}
			template<int QSDEPTH, bool USE_TT>
			scoreType eval(scoreType alpha, scoreType beta, variationType& principalVariation, bool& allowStoreTT) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				bool bTerminate{ false };
				m_Terminate.doIfHigh(
					[&bTerminate]()
					{
						bTerminate = true;
					}
				);
				if (bTerminate)
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
				scoreType best = stand_pat;
				constexpr const depthType ttDraft{ node::template qsearchDraft<QSDEPTH>() };
				if (best > alpha)
				{
					if (best >= beta)
					{
						m_Heuristics.endNodeLeaf(m_Stack);
						if constexpr (USE_TT)
						{
							m_Heuristics.transpositionTable().store(m_Stack, ttDraft, best, transpositiontable<descriptorSearch>::flags_lower, movebitsType(0));
						}
						return best;
					}
					alpha = best;
					if constexpr (USE_TT)
					{
						m_Heuristics.transpositionTable().store(m_Stack, ttDraft, best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
					}
				}
				bool fromStack;
				allowStoreTT = true;
				bool bPruned{ false };
				if constexpr (pruneDelta)
				{
					if (this->pruningAllowed(alpha, beta))
					{
						const scoreType deltaGlobalScore{ alpha - instanceType::deltaGlobalMargin(m_Stack) };
						constexpr const scoreType maximum{ scoreType::maximum() };
						const scoreType eval{ evaluate(deltaGlobalScore, maximum) };
						m_DeltaGap = alpha - eval - instanceType::deltaMargin(m_Stack);
						m_DeltaPruningAllowed = m_DeltaGap >= zero;
						bPruned |= deltaGlobalScore >= eval;
					}
				}
				return this->template evalLoop<QSDEPTH, USE_TT>(alpha, beta, best, principalVariation, allowStoreTT);
			}
			template<int QSDEPTH, bool USE_TT>
			PYGMALION_INLINE scoreType evalLoop(scoreType& alpha, scoreType& beta, scoreType& best, variationType& principalVariation, bool& allowStoreTT) noexcept
			{
				constexpr const int QSPHASE{ (QSDEPTH < (countQsPhase1Plies + countQsPhase2Plies)) ? ((QSDEPTH < countQsPhase1Plies) ? 0 : 1) : 2 };
				movebitsType bestmove;
				bool hasLegalMove{ false };
				movebitsType move;
				bool fromStack;
				allowStoreTT = true;
				constexpr const scoreType zero{ scoreType::zero() };
				constexpr const depthType ttDraft{ node::template qsearchDraft<QSDEPTH>() };
				if ((!hasLegalMove) && this->template nextTacticalMove<QSPHASE, false>(ttDraft, move))
				{
					hasLegalMove = true;
					if (this->template qsearchSubNode<QSDEPTH, USE_TT>(move, alpha, beta, best, bestmove, principalVariation, allowStoreTT))
					{
						this->template resetMoveGen<false, true>();
						return best;
					}
				}
				if (!hasLegalMove)
				{
					allowStoreTT = true;
					m_Heuristics.endNodeLate(m_Stack);
					if constexpr (staticMoveScores)
					{
						const auto lambda{ [this](const movebitsType& bits) { return this->m_Heuristics.staticMoveScore(m_Stack, bits, m_Depth); } };
						hasLegalMove = m_Stack.template hasLegalMove<decltype(lambda), false>(lambda);
					}
					else
						hasLegalMove = m_Stack.hasLegalMove();
					if (hasLegalMove)
					{
						if constexpr (USE_TT)
						{
							m_Heuristics.transpositionTable().store(m_Stack, ttDraft, best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
						}
						this->template resetMoveGen<false, true>();
						return best;
					}
					else
					{
						const scoreType late{ lateScore() };
						if constexpr (USE_TT)
						{
							m_Heuristics.transpositionTable().store(m_Stack, ttDraft, late, transpositiontable<descriptorSearch>::flags_exact, movebitsType(0));
						}
						this->template resetMoveGen<false, true>();
						return late;
					}
				}
				while (this->template nextTacticalMove<QSPHASE, false>(ttDraft, move))
				{
					if (this->template qsearchSubNode<QSDEPTH, USE_TT>(move, alpha, beta, best, bestmove, principalVariation, allowStoreTT))
					{
						this->template resetMoveGen<false, true>();
						return best;
					}
				}
				this->template resetMoveGen<false, true>();
				m_Heuristics.endNodeLate(m_Stack);
				return alpha;
			}
			template<int QSDEPTH, bool USE_TT>
			scoreType zweval(scoreType beta, bool& allowStoreTT, const knuthType expectedNodeType) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				bool bTerminate{ false };
				m_Terminate.doIfHigh(
					[&bTerminate]()
					{
						bTerminate = true;
					}
				);
				if (bTerminate)
				{
					allowStoreTT = false;
					return zero;
				}
				scoreType alpha{ beta.zeroWindow() };
				if ((m_DistanceFromRoot + 1) >= countSearchPlies)
					return evaluate(alpha, beta);
				m_Heuristics.beginNode(m_Stack);
				scoreType early{ zero };
				if (earlyScore<true>(early, allowStoreTT))
				{
					m_Heuristics.endNodeEarly(m_Stack);
					return early;
				}
				constexpr const depthType ttDraft{ node::template qsearchDraft<QSDEPTH>() };
				movebitsType bestmove;
				bool hasLegalMove{ false };
				movebitsType move;
				constexpr const scoreType minimum{ scoreType::minimum() };
				scoreType best{ minimum };
				if constexpr (USE_TT)
				{
					scoreType ttScore;
					movebitsType ttMove;
					const std::uint8_t lookUp{ m_Heuristics.transpositionTable().probe(m_Stack, ttDraft, alpha, beta, ttScore, ttMove) };
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
							m_Heuristics.transpositionTable().store(m_Stack, ttDraft, best, transpositiontable<descriptorSearch>::flags_lower, movebitsType(0));
						return best;
					}
					alpha = best;
					if constexpr (USE_TT)
						m_Heuristics.transpositionTable().store(m_Stack, ttDraft, best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
				}
				bool fromStack;
				allowStoreTT = true;
				bool bPruned{ false };
				if constexpr (pruneDelta)
				{
					if (this->pruningAllowed(alpha, beta))
					{
						const scoreType deltaGlobalScore{ alpha - instanceType::deltaGlobalMargin(m_Stack) };
						constexpr const scoreType maximum{ scoreType::maximum() };
						const scoreType eval{ evaluate(deltaGlobalScore, maximum) };
						m_DeltaGap = alpha - eval - instanceType::deltaMargin(m_Stack);
						m_DeltaPruningAllowed = m_DeltaGap >= zero;
						bPruned |= deltaGlobalScore >= eval;
					}
				}
				return this->template zwevalLoop<QSDEPTH, USE_TT>(alpha, beta, best, allowStoreTT, expectedNodeType);
			}
			template<int QSDEPTH, bool USE_TT>
			PYGMALION_INLINE scoreType zwevalLoop(scoreType& alpha, scoreType& beta, scoreType& best, bool& allowStoreTT, const knuthType expectedNodeType) noexcept
			{
				constexpr const int QSPHASE{ (QSDEPTH < (countQsPhase1Plies + countQsPhase2Plies)) ? ((QSDEPTH < countQsPhase1Plies) ? 0 : 1) : 2 };
				movebitsType bestmove;
				bool hasLegalMove{ false };
				movebitsType move;
				allowStoreTT = true;
				constexpr const scoreType zero{ scoreType::zero() };
				constexpr const depthType ttDraft{ node::template qsearchDraft<QSDEPTH>() };
				if (expectedNodeType == CUTnode)
				{
					if ((!hasLegalMove) && this->template nextTacticalMove<QSPHASE, true>(ttDraft, move))
					{
						hasLegalMove = true;
						if (this->qzwsearchSubNode<QSDEPTH, USE_TT>(move, alpha, beta, best, bestmove, allowStoreTT, -expectedNodeType))
						{
							this->template resetMoveGen<false, true>();
							return best;
						}
					}
				}
				else
				{
					if ((!hasLegalMove) && this->template nextTacticalMove<QSPHASE, false>(ttDraft, move))
					{
						hasLegalMove = true;
						if (this->qzwsearchSubNode<QSDEPTH, USE_TT>(move, alpha, beta, best, bestmove, allowStoreTT, -expectedNodeType))
						{
							this->template resetMoveGen<false, true>();
							return best;
						}
					}
				}
				if (!hasLegalMove)
				{
					allowStoreTT = true;
					m_Heuristics.endNodeLate(m_Stack);
					if constexpr (staticMoveScores)
					{
						const auto lambda{ [this](const movebitsType& bits) { return this->m_Heuristics.staticMoveScore(m_Stack, bits, m_Depth); } };
						if (expectedNodeType == CUTnode)
							hasLegalMove = m_Stack.template hasLegalMove<decltype(lambda), true>(lambda);
						else
							hasLegalMove = m_Stack.template hasLegalMove<decltype(lambda), false>(lambda);
					}
					else
						hasLegalMove = m_Stack.hasLegalMove(m_Depth, m_Heuristics.feedback());
					if (hasLegalMove)
					{
						if constexpr (USE_TT)
						{
							m_Heuristics.transpositionTable().store(m_Stack, ttDraft, best, transpositiontable<descriptorSearch>::flags_upper, movebitsType(0));
						}
						this->template resetMoveGen<false, true>();
						return best;
					}
					else
					{
						const scoreType late{ lateScore() };
						if constexpr (USE_TT)
						{
							m_Heuristics.transpositionTable().store(m_Stack, ttDraft, late, transpositiontable<descriptorSearch>::flags_exact, movebitsType(0));
						}
						this->template resetMoveGen<false, true>();
						return late;
					}
				}
				if (expectedNodeType == CUTnode)
				{
					while (this->template nextTacticalMove<QSPHASE, true>(ttDraft, move))
					{
						if (this->qzwsearchSubNode<QSDEPTH, USE_TT>(move, alpha, beta, best, bestmove, allowStoreTT, -expectedNodeType))
						{
							this->template resetMoveGen<false, true>();
							return best;
						}
					}
				}
				else
				{
					while (this->template nextTacticalMove<QSPHASE, false>(ttDraft, move))
					{
						if (this->qzwsearchSubNode<QSDEPTH, USE_TT>(move, alpha, beta, best, bestmove, allowStoreTT, -expectedNodeType))
						{
							this->template resetMoveGen<false, true>();
							return best;
						}
					}
				}
				m_Heuristics.endNodeLate(m_Stack);
				this->template resetMoveGen<false, true>();
				return alpha;
			}
			template<bool PRUNED>
			PYGMALION_INLINE scoreType zwsearchLoop(bool& hasLegalMove, const depthType depthRemaining, scoreType& alpha, scoreType& beta, scoreType& best, movebitsType& bestmove, const uint_t<countPlayers, false> nullMoveHistory, bool& allowStoreTT, const knuthType expectedNodeType) noexcept
			{
				movebitsType move;
				bool fromStack;
				if (expectedNodeType == CUTnode)
				{
					if ((!hasLegalMove) && this->template nextMove<PRUNED, true>(depthRemaining, move))
					{
						hasLegalMove = true;
						if (this->zwsearchSubNode<PRUNED>(move, alpha, beta, best, bestmove, depthRemaining, noNullMove(nullMoveHistory), allowStoreTT, CUTnode))
						{
							this->template resetMoveGen<PRUNED, false>();
							return best;
						}
					}
				}
				else
				{
					if ((!hasLegalMove) && this->template nextMove<PRUNED, false>(depthRemaining, move))
					{
						hasLegalMove = true;
						if (this->zwsearchSubNode<PRUNED>(move, alpha, beta, best, bestmove, depthRemaining, noNullMove(nullMoveHistory), allowStoreTT, -expectedNodeType))
						{
							this->template resetMoveGen<PRUNED, false>();
							return best;
						}
					}
				}
				if (!hasLegalMove)
				{
					allowStoreTT = true;
					m_Heuristics.endNodeLate(m_Stack);
					const scoreType late{ lateScore() };
					if constexpr (searchTranspositionTable)
						m_Heuristics.transpositionTable().store(m_Stack, depthRemaining, late, transpositiontable<descriptorSearch>::flags_exact, movebitsType(0));
					this->template resetMoveGen<PRUNED, false>();
					return late;
				}
				if (expectedNodeType == CUTnode)
				{
					while (this->template nextMove<PRUNED, true>(depthRemaining, move))
					{
						bool allowStoreTTsubnode;
						if (this->zwsearchSubNode<PRUNED>(move, alpha, beta, best, bestmove, depthRemaining, noNullMove(nullMoveHistory), allowStoreTT, CUTnode))
						{
							this->template resetMoveGen<PRUNED, false>();
							return best;
						}
					}
				}
				else
				{
					while (this->template nextMove<PRUNED, false>(depthRemaining, move))
					{
						bool allowStoreTTsubnode;
						if (this->zwsearchSubNode<PRUNED>(move, alpha, beta, best, bestmove, depthRemaining, noNullMove(nullMoveHistory), allowStoreTT, CUTnode))
						{
							this->template resetMoveGen<PRUNED, false>();
							return best;
						}
					}
				}
				m_Heuristics.endNodeLate(m_Stack);
				this->template resetMoveGen<PRUNED, false>();
				return alpha;
			}
			template<bool ANALYZE>
			PYGMALION_INLINE scoreType searchLoop(const depthType depthRemaining, scoreType& alpha, scoreType& beta, variationType& principalVariation, bool& allowStoreTT, indexType* pCurrentMove) noexcept
			{
				bool hasLegalMove{ false };
				movebitsType move;
				constexpr const scoreType minimum{ scoreType::minimum() };
				scoreType best{ minimum };
				movebitsType bestmove;
				allowStoreTT = true;
				if ((!hasLegalMove) && this->template nextMove<false, false>(depthRemaining, move))
				{
					hasLegalMove = true;
					if (this->searchSubNode<false, ANALYZE>(move, alpha, beta, best, bestmove, depthRemaining, principalVariation, allowStoreTT, pCurrentMove))
					{
						this->template resetMoveGen<false, false>();
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
					this->template resetMoveGen<false, false>();
					return late;
				}
				while (this->template nextMove<false, false>(depthRemaining, move))
				{
					if (this->searchSubNode<true, ANALYZE>(move, alpha, beta, best, bestmove, depthRemaining, principalVariation, allowStoreTT, pCurrentMove))
					{
						this->template resetMoveGen<false, false>();
						return best;
					}
				}
				m_Heuristics.endNodeLate(m_Stack);
				this->template resetMoveGen<false, false>();
				return alpha;
			}
		public:
			PYGMALION_INLINE scoreType evaluate(const scoreType alpha, const scoreType beta) noexcept
			{
				if ((alpha < m_EvalAlpha) || (beta > m_EvalBeta))
				{
					m_Eval = evaluatorType::evaluate(alpha, beta, m_Stack, m_Data, m_Parameters);
					m_EvalAlpha = alpha;
					m_EvalBeta = beta;
				}
				return m_Eval;
			}
			template<bool PRUNED, bool TACTICAL >
			PYGMALION_INLINE void resetMoveGen()
			{
				if constexpr (TACTICAL)
				{
					m_TacticalMove = 0;
					m_TacticalMoveGeneratorStage = -1;
				}
				else
				{
					if constexpr (PRUNED)
						m_CriticalMove = 0;
					else
						m_Move = 0;
					m_MoveGeneratorStage = -1;
				}
			}
			scoreType zwsearch(scoreType beta, const depthType depthRemaining, const uint_t<countPlayers, false> nullMoveHistory, bool& allowStoreTT, const knuthType expectedNodeType) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				bool bTerminate{ false };
				m_Terminate.doIfHigh(
					[&bTerminate]()
					{
						bTerminate = true;
					}
				);
				if (bTerminate)
				{
					allowStoreTT = false;
					return zero;
				}
				scoreType alpha{ beta.zeroWindow() };
				if ((depthRemaining >= depthType(0)) && ((m_DistanceFromRoot + 1) < countSearchPlies))
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
										constexpr const movebitsType nullMove{ generatorType::nullMove() };
										childType subnode(childType(*static_cast<const instanceType*>(this), nullMove));
										constexpr const scoreType atom{ scoreType::atom() };
										nmsc = -subnode.zwsearch((atom - beta).plyDown(), remainingNullMoveDepth, doNullMove(nullMoveHistory), allowStoreTTsubnode, CUTnode).plyUp();
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
									const scoreType futileGlobalScore{ alpha - static_cast<const instanceType*>(this)->futilityGlobalMargin(depthRemaining, m_Stack) };
									constexpr const scoreType maximum{ scoreType::maximum() };
									const scoreType eval{ evaluate(futileGlobalScore, maximum) };
									m_FutileGap = alpha - eval - static_cast<const instanceType*>(this)->futilityMargin(depthRemaining, m_Stack);
									m_FutilityPruningAllowed = m_FutileGap >= zero;
									bPruned |= futileGlobalScore >= eval;
								}
							}
						}
					}
					if (bPruned)
						return this->template zwsearchLoop<true>(hasLegalMove, depthRemaining, alpha, beta, best, bestmove, nullMoveHistory, allowStoreTT, expectedNodeType);
					else
						return this->template zwsearchLoop<false>(hasLegalMove, depthRemaining, alpha, beta, best, bestmove, nullMoveHistory, allowStoreTT, expectedNodeType);
				}
				else
				{
					return this->template zweval<0, searchTranspositionTable>(beta, allowStoreTT, expectedNodeType);
				}
			}
			scoreType analyze(scoreType alpha, scoreType beta, const depthType depthRemaining, variationType& principalVariation, bool& allowStoreTT, indexType& currentMove) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				bool bTerminate{ false };
				m_Terminate.doIfHigh(
					[&bTerminate]()
					{
						bTerminate = true;
					}
				);
				if (bTerminate)
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
					return this->template searchLoop<true>(depthRemaining, alpha, beta, principalVariation, allowStoreTT, &currentMove);
				}
				else
				{
					return this->template eval<searchTranspositionTable>(alpha, beta, principalVariation, allowStoreTT, 0);
				}
			}
			scoreType search(scoreType alpha, scoreType beta, const depthType depthRemaining, variationType& principalVariation, bool& allowStoreTT) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				bool bTerminate{ false };
				m_Terminate.doIfHigh(
					[&bTerminate]()
					{
						bTerminate = true;
					}
				);
				if (bTerminate)
				{
					allowStoreTT = false;
					return zero;
				}
				if ((depthRemaining >= depthType(0)) && ((m_DistanceFromRoot + 1 + countQsPhase1Plies + countQsPhase2Plies + countQsPhase3Plies) < countSearchPlies))
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
									const scoreType futileGlobalScore{ alpha - static_cast<instanceType*>(this)->futilityGlobalMargin(depthRemaining, m_Stack) };
									constexpr const scoreType maximum{ scoreType::maximum() };
									const scoreType eval{ evaluate(futileGlobalScore, maximum) };
									m_FutileGap = alpha - eval - static_cast<instanceType*>(this)->futilityMargin(depthRemaining, m_Stack);
									m_FutilityPruningAllowed = m_FutileGap >= zero;
								}
							}
						}
					}
					return this->template searchLoop<false>(depthRemaining, alpha, beta, principalVariation, allowStoreTT, nullptr);
				}
				else
				{
					return this->template eval<0, searchTranspositionTable>(alpha, beta, principalVariation, allowStoreTT);
				}
			}
			node() = delete;
			PYGMALION_INLINE node(const stackType& stack, signal& terminate, heuristicsType& heuristics, const size_t depth, const std::vector<scoreType>& parameters) noexcept :
				m_Parameters{ parameters },
				m_Stack{ stack },
				m_Terminate{ terminate },
				m_Heuristics{ heuristics },
				m_MovesTT{ ttmovesType() },
				m_QuietMovesKiller{ quietKillermovesType() },
				m_TacticalMovesKiller{ tacticalKillermovesType() },
				m_TacticalMovesTT{ ttmovesType() },
				m_Moves{ movelistType() },
				m_TacticalMoves{ movelistType() },
				m_TacticalMoveGeneratorStage{ -1 },
				m_MoveGeneratorStage{ -1 },
				m_Move{ 0 },
				m_CriticalMove{ 0 },
				m_TacticalMove{ 0 },
				m_NeedsSorting{ false },
				m_FutilityPruningAllowed{ false },
				m_DeltaPruningAllowed{ false },
				m_DistanceFromRoot{ 0 },
				m_Depth{ depth }
			{
				PYGMALION_ASSERT(stack.position().movingPlayer() == movingPlayer);
				m_Heuristics.expandToDepth(m_Depth + countSearchPlies);
				if constexpr (searchTranspositionTable)
					m_Heuristics.transpositionTable().prefetch(m_Stack);
				m_Stack.context().clearMovegenLists();
				constexpr const scoreType minimum{ scoreType::minimum() };
				constexpr const scoreType maximum{ scoreType::maximum() };
				constexpr const scoreType zero{ scoreType::zero() };
				m_EvalAlpha = maximum;
				m_EvalBeta = minimum;
				m_Eval = zero;
				m_FutileGap = zero;
				m_DeltaGap = zero;
				evaluatorType::createData(m_Data);
			}
			PYGMALION_INLINE node(const parentType& parent, const movebitsType moveBits) noexcept :
				m_Parameters{ parent.m_Parameters },
				m_Stack(parent.m_Stack, moveBits),
				m_Terminate{ parent.m_Terminate },
				m_Heuristics{ parent.m_Heuristics },
				m_MovesTT{ ttmovesType() },
				m_QuietMovesKiller{ quietKillermovesType() },
				m_TacticalMovesKiller{ tacticalKillermovesType() },
				m_TacticalMovesTT{ ttmovesType() },
				m_Moves{ movelistType() },
				m_TacticalMoves{ movelistType() },
				m_TacticalMoveGeneratorStage{ -1 },
				m_MoveGeneratorStage{ -1 },
				m_Move{ 0 },
				m_CriticalMove{ 0 },
				m_TacticalMove{ 0 },
				m_NeedsSorting{ false },
				m_FutilityPruningAllowed{ false },
				m_DeltaPruningAllowed{ false },
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
				m_DeltaGap = zero;
				evaluatorType::createData(m_Data);
			}
			bool lastMoveFromTT() const noexcept
			{
				return m_IsTTMove;
			}
			bool lastMoveIsKiller() const noexcept
			{
				return m_IsKiller;
			}
			bool lastMoveIsTacticalKiller() const noexcept
			{
				return m_IsTacticalKiller;
			}
			PYGMALION_INLINE ~node() noexcept = default;
			template<bool ANALYZE>
			scoreType searchRoot(const depthType depthRemaining, variationType& principalVariation, const scoreType scoreFromPreviousDepth, indexType& currentMove, indexType& countMoves) noexcept
			{
				bool allowStoreTT;
				constexpr const scoreType minimum{ scoreType::minimum() };
				constexpr const scoreType maximum{ scoreType::maximum() };
				if constexpr (ANALYZE)
				{
					currentMove = 0;
					countMoves = 0;
					bool fromStack;
					movebitsType move;
					while (nextMove<false>(depthRemaining, move, fromStack))
						countMoves++;
					resetMoveGen();
					return this->analyze(minimum, maximum, depthRemaining, principalVariation, allowStoreTT, currentMove);
				}
				else
				{
					if constexpr (searchAspiration)
					{
						scoreType sc{ scoreFromPreviousDepth };
						scoreType lowAspiration{ sc };
						scoreType highAspiration{ sc };
						PYGMALION_TUNABLE const scoreType initialAspirationWindow{ evaluatorType::initialAspirationWindowSize() };
						constexpr const scoreType atom{ scoreType::atom() };
						scoreType delta{ initialAspirationWindow };
						bool bExact{ false };
						bool bLow{ true };
						bool bHigh{ true };
						constexpr const size_t countWindows{ evaluatorType::countAspirationWindows() };
						for (size_t i = 0; i < countWindows; i++)
						{
							const scoreType oldScore{ sc };
							const scoreType oldLow{ lowAspiration };
							const scoreType oldHigh{ highAspiration };
							if (sc.isOpen())
							{
								lowAspiration = bLow ? (lowAspiration - delta) : (oldHigh - atom);
								highAspiration = bHigh ? (highAspiration + delta) : (oldLow + atom);
							}
							else
							{
								if (sc.isWinning())
								{
									lowAspiration = oldHigh - atom;
									highAspiration = maximum;
								}
								else
								{
									lowAspiration = minimum;
									highAspiration = oldLow + atom;
								}
							}
							if (lowAspiration.isLosing())
								lowAspiration = minimum;
							if (highAspiration.isWinning())
								highAspiration = maximum;
							sc = this->search(lowAspiration, highAspiration, depthRemaining, principalVariation, allowStoreTT);
							if ((sc > lowAspiration) && (sc < highAspiration))
							{
								bExact = true;
								break;
							}
							if (sc <= lowAspiration)
							{
								delta = 2 * (oldScore - sc + atom);
								bLow = true;
							}
							else
								bLow = false;
							if (sc >= highAspiration)
							{
								delta = 2 * (sc - oldScore + atom);
								bHigh = true;
							}
							else
								bHigh = false;
						}
						if (!bExact)
						{
							sc = this->search(minimum, maximum, depthRemaining, principalVariation, allowStoreTT);
						}
						return sc;
					}
					else
						return this->search(minimum, maximum, depthRemaining, principalVariation, allowStoreTT);
				}
			}
			PYGMALION_INLINE const stackType& stack() const noexcept
			{
				return m_Stack;
			}
			template<bool PRUNED, bool EXPECT_CUTOFF>
			bool nextMove(const depthType depthRemaining, movebitsType& movebits) noexcept
			{
				if (m_MoveGeneratorStage < 0)
				{
					m_MoveGeneratorStage = 0;
					m_MovesTT.clear();
					m_Heuristics.transpositionTable().probeMoves(m_Stack, depthRemaining, m_MovesTT);
					m_MoveTT = 0;
				}
				if (m_MoveGeneratorStage == 0)
				{
					constexpr const scoreType maximum{ scoreType::maximum() };
					m_IsTTMove = true;
					while (m_MoveTT < m_MovesTT.length())
					{
						movebits = m_MovesTT[m_MoveTT];
						++m_MoveTT;
						if constexpr (PRUNED)
						{
							if (generatorType::template isMoveCritical<PLAYER>(m_Stack, movebits))
							{
								return true;
							}
						}
						else
						{
							return true;
						}
					}
					m_IsTTMove = false;
					m_MoveGeneratorStage = 1;
					m_TacticalMovesKiller.clear();
					m_Heuristics.template tacticalKillers<PLAYER, 0>(m_Stack, m_Depth, m_TacticalMovesKiller);
					m_TacticalMoveKiller = 0;
				}
				if (m_MoveGeneratorStage == 1)
				{
					constexpr const scoreType win{ scoreType::win() };
					m_IsTacticalKiller = true;
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
					m_IsTacticalKiller = false;
					m_MoveGeneratorStage = 2;
					m_QuietMovesKiller.clear();
					m_Heuristics.quietKillers(m_Stack, m_Depth, m_QuietMovesKiller);
					m_QuietMoveKiller = 0;
				}
				if (m_MoveGeneratorStage == 2)
				{
					m_IsKiller = true;
					while (m_QuietMoveKiller < m_QuietMovesKiller.length())
					{
						movebits = m_QuietMovesKiller[m_QuietMoveKiller];
						++m_QuietMoveKiller;
						if constexpr (PRUNED)
						{
							if (generatorType::template isMoveCritical<PLAYER>(m_Stack, movebits))
							{
								const bool bDouble{ m_MovesTT.contains(movebits) || m_TacticalMovesKiller.contains(movebits) };
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
					m_IsKiller = false;
					m_MoveGeneratorStage = 3;
				}
				if constexpr (PRUNED)
				{
					while (m_CriticalMove < m_CriticalMoves.length())
					{
						movebits = m_CriticalMoves[m_CriticalMove];
						const bool bDouble{ m_MovesTT.contains(movebits) || m_QuietMovesKiller.contains(movebits) || m_TacticalMovesKiller.contains(movebits) };
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
						const bool bDouble{ m_MovesTT.contains(movebits) || m_QuietMovesKiller.contains(movebits) || m_TacticalMovesKiller.contains(movebits) };
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
					if constexpr (staticMoveScores)
					{
						const auto lambda{ [this](const movebitsType& bits) { return this->m_Heuristics.staticMoveScore(m_Stack, bits, m_Depth); } };
						while (m_Stack.template nextCriticalMove<decltype(lambda), EXPECT_CUTOFF && allowSelectionSort>(testBits, lambda))
						{
							const bool bDouble{ m_MovesTT.contains(testBits) || m_QuietMovesKiller.contains(testBits) || m_TacticalMovesKiller.contains(testBits) };
							m_CriticalMoves.add(testBits);
							++m_CriticalMove;
							if (!bDouble)
							{
								movebits = testBits;
								return true;
							}
						}
					}
					else
					{
						while (m_Stack.nextCriticalMove(testBits))
						{
							const bool bDouble{ m_MovesTT.contains(testBits) || m_QuietMovesKiller.contains(testBits) || m_TacticalMovesKiller.contains(testBits) };
							m_CriticalMoves.add(testBits);
							++m_CriticalMove;
							if (!bDouble)
							{
								movebits = testBits;
								return true;
							}
						}
					}
				}
				else
				{
					if constexpr (staticMoveScores)
					{
						const auto lambda{ [this](const movebitsType& bits) { return this->m_Heuristics.staticMoveScore(m_Stack, bits, m_Depth); } };
						while (m_Stack.template nextMove<decltype(lambda), EXPECT_CUTOFF && allowSelectionSort>(testBits, lambda))
						{
							const bool bDouble{ m_MovesTT.contains(testBits) || m_QuietMovesKiller.contains(testBits) || m_TacticalMovesKiller.contains(testBits) };
							m_Moves.add(testBits);
							++m_Move;
							if (!bDouble)
							{
								movebits = testBits;
								return true;
							}
						}
					}
					else
					{
						while (m_Stack.nextMove(testBits))
						{
							const bool bDouble{ m_MovesTT.contains(testBits) || m_QuietMovesKiller.contains(testBits) || m_TacticalMovesKiller.contains(testBits) };
							m_Moves.add(testBits);
							++m_Move;
							if (!bDouble)
							{
								movebits = testBits;
								return true;
							}
						}
					}
				}
				return false;
			}
			template<int QSPHASE, bool EXPECT_CUTOFF>
			bool nextTacticalMove(const depthType depthRemaining, movebitsType& movebits) noexcept
			{
				if (m_TacticalMoveGeneratorStage < 0)
				{
					m_TacticalMoveGeneratorStage = 0;
					m_TacticalMovesTT.clear();
					if constexpr (QSPHASE == 0)
						m_Heuristics.transpositionTable().probeQSPhase1Moves(m_Stack, depthRemaining, m_TacticalMovesTT);
					else if constexpr (QSPHASE == 1)
						m_Heuristics.transpositionTable().probeQSPhase2Moves(m_Stack, depthRemaining, m_TacticalMovesTT);
					else
						m_Heuristics.transpositionTable().probeQSPhase3Moves(m_Stack, depthRemaining, m_TacticalMovesTT);
					m_TacticalMoveTT = 0;
				}
				if (m_TacticalMoveGeneratorStage == 0)
				{
					m_IsTTMove = true;
					while (m_TacticalMoveTT < m_TacticalMovesTT.length())
					{
						movebits = m_TacticalMovesTT[m_TacticalMoveTT];
						++m_TacticalMoveTT;
						return true;
					}
					m_IsTTMove = false;
					m_TacticalMoveGeneratorStage = 1;
					m_TacticalMovesKiller.clear();
					m_Heuristics.template tacticalKillers<PLAYER, QSPHASE>(m_Stack, m_Depth, m_TacticalMovesKiller);
					m_TacticalMoveKiller = 0;
				}
				if (m_TacticalMoveGeneratorStage == 1)
				{
					m_IsTacticalKiller = true;
					while (m_TacticalMoveKiller < m_TacticalMovesKiller.length())
					{
						movebits = m_TacticalMovesKiller[m_TacticalMoveKiller];
						const bool bDouble{ m_TacticalMovesTT.contains(movebits) };
						++m_TacticalMoveKiller;
						if (!bDouble)
							return true;
					}
					m_IsTacticalKiller = false;
					m_TacticalMoveGeneratorStage = 2;
				}
				while (m_TacticalMove < m_TacticalMoves.length())
				{
					movebits = m_TacticalMoves[m_TacticalMove];
					++m_TacticalMove;
					const bool bDouble{ m_TacticalMovesTT.contains(movebits) || m_TacticalMovesKiller.contains(movebits) };
					if (!bDouble)
					{
						return true;
					}
				}
				movebitsType testBits{ movebitsType(0) };
				if constexpr (staticMoveScores)
				{
					const auto lambda{ [this](const movebitsType& bits) { return this->m_Heuristics.staticMoveScore(m_Stack, bits, m_Depth); } };
					if constexpr (QSPHASE == 0)
					{
						while (m_Stack.template nextQSPhase1Move<decltype(lambda), EXPECT_CUTOFF && allowSelectionSort>(testBits, lambda))
						{
							movebits = testBits;
							m_TacticalMoves.add(testBits);
							++m_TacticalMove;
							const bool bDouble{ m_MovesTT.contains(movebits) || m_TacticalMovesKiller.contains(movebits) };
							if (!bDouble)
							{
								return true;
							}
						}
					}
					else if constexpr (QSPHASE == 1)
					{
						while (m_Stack.template nextQSPhase2Move<decltype(lambda), EXPECT_CUTOFF && allowSelectionSort>(testBits, lambda))
						{
							movebits = testBits;
							m_TacticalMoves.add(testBits);
							++m_TacticalMove;
							const bool bDouble{ m_MovesTT.contains(movebits) || m_TacticalMovesKiller.contains(movebits) };
							if (!bDouble)
							{
								return true;
							}
						}
					}
					else
					{
						while (m_Stack.template nextQSPhase3Move<decltype(lambda), EXPECT_CUTOFF && allowSelectionSort>(testBits, lambda))
						{
							movebits = testBits;
							m_TacticalMoves.add(testBits);
							++m_TacticalMove;
							const bool bDouble{ m_TacticalMovesTT.contains(testBits) || m_TacticalMovesKiller.contains(testBits) };
							if (!bDouble)
							{
								return true;
							}
						}
					}
				}
				else
				{
					if constexpr (QSPHASE == 0)
					{
						while (m_Stack.nextQSPhase1Move(testBits, m_Depth, m_Heuristics.feedback()))
						{
							movebits = testBits;
							m_TacticalMoves.add(testBits);
							++m_TacticalMove;
							const bool bDouble{ m_MovesTT.contains(movebits) || m_TacticalMovesKiller.contains(movebits) };
							if (!bDouble)
							{
								return true;
							}
						}
					}
					else if constexpr (QSPHASE == 1)
					{
						while (m_Stack.nextQSPhase2Move(testBits, m_Depth, m_Heuristics.feedback()))
						{
							movebits = testBits;
							m_TacticalMoves.add(testBits);
							++m_TacticalMove;
							const bool bDouble{ m_TacticalMovesTT.contains(testBits) || m_TacticalMovesKiller.contains(testBits) };
							if (!bDouble)
							{
								return true;
							}
						}
					}
					else
					{
						while (m_Stack.nextQSPhase3Move(testBits, m_Depth, m_Heuristics.feedback()))
						{
							movebits = testBits;
							m_TacticalMoves.add(testBits);
							++m_TacticalMove;
							const bool bDouble{ m_TacticalMovesTT.contains(testBits) || m_TacticalMovesKiller.contains(testBits) };
							if (!bDouble)
							{
								return true;
							}
						}
					}
				}
				return false;
			}
		};
	};
}