namespace pygmalion
{
	//#define PYGMALION_SELECTIONSORT

	enum class movegenPhase
	{
		normal,
		criticalEvasion,
		critical,
		QSPhase1,
		QSPhase1_CriticalEvasion,
		QSPhase2,
		QSPhase2_CriticalEvasion,
		QSPhase3,
		QSPhase3_CriticalEvasion
	};

	template<typename DESCRIPTOR_DYNAMICS, typename INSTANCE >
	class generator :
		public DESCRIPTOR_DYNAMICS
	{
	public:
		using generatorType = INSTANCE;
		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include "include_dynamics.h"
		class movegenFeedback
		{
		private:
			class feedback
			{
			private:
				std::array<std::array<std::uint64_t, generatorType::countMaxMovegenPasses()>, generatorType::countTotalMovegenStages()> m_MoveCounters;
				std::array<std::array<passType, generatorType::countMaxMovegenPasses()>, generatorType::countTotalMovegenStages()> m_Indices;
				std::array<std::array<heuristicScore, generatorType::countMaxMovegenPasses()>, generatorType::countTotalMovegenStages()> m_ScoreCounters;
				void sortIndicesStage(const stageType stage, const movegenFeedback& mf, const size_t depth) noexcept
				{
					std::array <scoreType, generatorType::countMaxMovegenPasses()> scores;
					for (size_t pass = 0; pass < generatorType::countMovegenPasses(stage); pass++)
					{
						const passType idx{ index(stage,pass) };
						scores[pass] = mf.scoreRaw(stage, idx, depth);
					}
					sort<passType, scoreType>::sortValues(m_Indices[static_cast<size_t>(stage)].data(), scores.data(), generatorType::countMovegenPasses(stage));
				}
				void resetStage(const stageType stage) noexcept
				{
					constexpr const heuristicScore zero{ heuristicScore::zero() };
					for (size_t i = 0; i < generatorType::countMaxMovegenPasses(); i++)
					{
						m_MoveCounters[stage][i] = 0;
						m_ScoreCounters[stage][i] = zero;
						m_Indices[stage][i] = i;
					}
				}
			public:
				void sortIndices(const movegenFeedback& mf, const size_t depth) noexcept
				{
					for (size_t stage = 0; stage < generatorType::countTotalMovegenStages(); stage++)
						sortIndicesStage(stage, mf, depth);
				}
				PYGMALION_INLINE passType index(const stageType stage, const passType pass) const noexcept
				{
					return m_Indices[stage][pass];
				}
				feedback() noexcept
				{
					reset();
				}
				scoreType scoreRaw(const stageType stage, const passType pass) const noexcept
				{
					if (m_MoveCounters[static_cast<size_t>(stage)][static_cast<size_t>(pass)] == 0)
					{
						constexpr const scoreType minimum{ scoreType::minimum() };
						return minimum;
					}
					const heuristicScore score{ m_ScoreCounters[static_cast<size_t>(stage)][static_cast<size_t>(pass)] };
					return static_cast<scoreType>(score / m_MoveCounters[static_cast<size_t>(stage)][static_cast<size_t>(pass)]);
				}
				PYGMALION_INLINE const std::uint64_t& counterRaw(const stageType stage, const passType pass) const noexcept
				{
					return m_MoveCounters[stage][pass];
				}
				PYGMALION_INLINE void incrementMoveRaw(const stageType stage, const passType pass, const scoreType score, const scoreType eval) noexcept
				{
					if (score.isOpen())
					{
						m_ScoreCounters[stage][pass] += static_cast<heuristicScore>(score - eval);
						m_MoveCounters[stage][pass]++;
					}
				}
				void reset() noexcept
				{
					for (size_t stage = 0; stage < generatorType::countTotalMovegenStages(); stage++)
						resetStage(static_cast<stageType>(stage));
				}
			};
			mutable std::vector<feedback> m_Feedback;
		public:
			movegenFeedback() noexcept :
				m_Feedback{ std::vector<feedback>(0) }
			{

			}
			void sortPasses(const size_t depth) noexcept
			{
				for (size_t i = depth; i < m_Feedback.size(); i++)
					m_Feedback[i].sortIndices(*this, i);
				//	m_Feedback[depth].sortIndices(*this, depth);
			}
			PYGMALION_INLINE  const std::uint64_t& counterRaw(const stageType stage, const passType pass, const size_t depth) const noexcept
			{
				return m_Feedback[depth].counterRaw(stage, pass);
			}
			PYGMALION_INLINE  scoreType scoreRaw(const stageType stage, const passType pass, const size_t depth) const noexcept
			{
				constexpr const scoreType minimum{ scoreType::minimum() };
				const scoreType scoreFrontier{ m_Feedback[depth].scoreRaw(stage, pass) };
				if (scoreFrontier > minimum)
				{
					if (depth >= 2)
					{
						const scoreType scorePreFrontier{ m_Feedback[depth - 2].scoreRaw(stage, pass) };
						if (scorePreFrontier > minimum)
						{
							return (scorePreFrontier + scoreFrontier) / 2;
						}
						else
							return scoreFrontier;
					}
					else
						return scoreFrontier;
				}
				else
					return minimum;
			}
			void cutMoveRaw(const stageType stage, const passType pass, const size_t depth, const scoreType score, const scoreType eval) noexcept
			{
				m_Feedback[depth].incrementMoveRaw(stage, pass, score, eval);
			}
			void allMoveRaw(const stageType stage, const passType pass, const size_t depth, const scoreType score, const scoreType eval) noexcept
			{
				m_Feedback[depth].incrementMoveRaw(stage, pass, score, eval);
			}
			void reset() noexcept
			{
				m_Feedback.clear();
			}
			PYGMALION_INLINE  passType index(const stageType stage, const passType pass, const size_t depth) const noexcept
			{
				return m_Feedback[depth].index(stage, pass);
			}
			void expandToDepth(const size_t depth) const noexcept
			{
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
			}
		};
		class context :
			public DESCRIPTOR_DYNAMICS
		{
		public:
			using generatorType = INSTANCE;
			using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include "include_dynamics.h"
		private:
			stagelistType m_NormalStages;
			scorelistType m_NormalScores;
			movelistType m_NormalMoves;
			passlistType m_NormalPasses;
			stagelistType m_CriticalStages;
			scorelistType m_CriticalScores;
			movelistType m_CriticalMoves;
			passlistType m_CriticalPasses;
			stagelistType m_QSPhase1Stages;
			scorelistType m_QSPhase1Scores;
			movelistType m_QSPhase1Moves;
			passlistType m_QSPhase1Passes;
			stagelistType m_QSPhase2Stages;
			scorelistType m_QSPhase2Scores;
			movelistType m_QSPhase2Moves;
			passlistType m_QSPhase2Passes;
			stagelistType m_QSPhase3Stages;
			scorelistType m_QSPhase3Scores;
			movelistType m_QSPhase3Moves;
			passlistType m_QSPhase3Passes;
		public:
			context() noexcept
			{

			}
			~context() noexcept = default;
			PYGMALION_INLINE stagelistType& normalStages() noexcept
			{
				return m_NormalStages;
			}
			PYGMALION_INLINE scorelistType& normalScores() noexcept
			{
				return m_NormalScores;
			}
			PYGMALION_INLINE movelistType& normalMoves() noexcept
			{
				return m_NormalMoves;
			}
			PYGMALION_INLINE passlistType& normalPasses() noexcept
			{
				return m_NormalPasses;
			}
			PYGMALION_INLINE stagelistType& criticalStages() noexcept
			{
				return m_CriticalStages;
			}
			PYGMALION_INLINE scorelistType& criticalScores() noexcept
			{
				return m_CriticalScores;
			}
			PYGMALION_INLINE movelistType& criticalMoves() noexcept
			{
				return m_CriticalMoves;
			}
			PYGMALION_INLINE passlistType& criticalPasses() noexcept
			{
				return m_CriticalPasses;
			}
			PYGMALION_INLINE scorelistType& qsPhase1Scores() noexcept
			{
				return m_QSPhase1Scores;
			}
			PYGMALION_INLINE movelistType& qsPhase1Moves() noexcept
			{
				return m_QSPhase1Moves;
			}
			PYGMALION_INLINE stagelistType& qsPhase1Stages() noexcept
			{
				return m_QSPhase1Stages;
			}
			PYGMALION_INLINE passlistType& qsPhase1Passes() noexcept
			{
				return m_QSPhase1Passes;
			}
			PYGMALION_INLINE scorelistType& qsPhase2Scores() noexcept
			{
				return m_QSPhase2Scores;
			}
			PYGMALION_INLINE movelistType& qsPhase2Moves() noexcept
			{
				return m_QSPhase2Moves;
			}
			PYGMALION_INLINE stagelistType& qsPhase2Stages() noexcept
			{
				return m_QSPhase2Stages;
			}
			PYGMALION_INLINE passlistType& qsPhase2Passes() noexcept
			{
				return m_QSPhase1Passes;
			}
			PYGMALION_INLINE scorelistType& qsPhase3Scores() noexcept
			{
				return m_QSPhase3Scores;
			}
			PYGMALION_INLINE movelistType& qsPhase3Moves() noexcept
			{
				return m_QSPhase3Moves;
			}
			PYGMALION_INLINE stagelistType& qsPhase3Stages() noexcept
			{
				return m_QSPhase3Stages;
			}
			PYGMALION_INLINE passlistType& qsPhase3Passes() noexcept
			{
				return m_QSPhase3Passes;
			}
			void clearMovegenLists() noexcept
			{
				m_NormalStages.clear();
				m_NormalScores.clear();
				m_NormalMoves.clear();
				m_NormalPasses.clear();
				m_CriticalStages.clear();
				m_CriticalScores.clear();
				m_CriticalMoves.clear();
				m_CriticalPasses.clear();
				m_QSPhase1Stages.clear();
				m_QSPhase1Scores.clear();
				m_QSPhase1Moves.clear();
				m_QSPhase1Passes.clear();
				m_QSPhase2Stages.clear();
				m_QSPhase2Scores.clear();
				m_QSPhase2Moves.clear();
				m_QSPhase2Passes.clear();
				m_QSPhase3Stages.clear();
				m_QSPhase3Scores.clear();
				m_QSPhase3Moves.clear();
				m_QSPhase3Passes.clear();
			}
		};
		template<size_t PLAYER>
		class stack :
			public DESCRIPTOR_DYNAMICS
		{
		public:
			using generatorType = INSTANCE;
			using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include "include_dynamics.h"
			using contextType = typename generatorType::contextType;
		private:
			constexpr static inline const playerType m_MovingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr static inline const playerType m_NextPlayer{ m_MovingPlayer.next() };
		public:
			using parentType = stack< static_cast<size_t>(m_MovingPlayer.previous())>;
			friend stack< static_cast<size_t>(m_MovingPlayer.next())>;
		private:
			const parentType* m_pParent;
			contextType* m_pContext;
			boardType& m_Position;
			historyType& m_History;
			movedataType m_MoveData;
			mutable scoreType m_LastNormalScore;
			mutable stageType m_LastNormalStage;
			mutable stageType m_CurrentNormalStage;
			mutable passType m_CurrentNormalPass;
			mutable passType m_LastNormalPass;
			mutable indexType m_CurrentNormalMove;

			mutable scoreType m_LastQSPhase1Score;
			mutable stageType m_LastQSPhase1Stage;
			mutable stageType m_CurrentQSPhase1Stage;
			mutable passType m_CurrentQSPhase1Pass;
			mutable passType m_LastQSPhase1Pass;
			mutable indexType m_CurrentQSPhase1Move;
			mutable scoreType m_LastQSPhase2Score;
			mutable stageType m_LastQSPhase2Stage;
			mutable stageType m_CurrentQSPhase2Stage;
			mutable passType m_CurrentQSPhase2Pass;
			mutable passType m_LastQSPhase2Pass;
			mutable indexType m_CurrentQSPhase2Move;
			mutable scoreType m_LastQSPhase3Score;
			mutable stageType m_LastQSPhase3Stage;
			mutable stageType m_CurrentQSPhase3Stage;
			mutable passType m_CurrentQSPhase3Pass;
			mutable passType m_LastQSPhase3Pass;
			mutable indexType m_CurrentQSPhase3Move;

			mutable scoreType m_LastCriticalScore;
			mutable stageType m_LastCriticalStage;
			mutable stageType m_CurrentCriticalStage;
			mutable passType m_CurrentCriticalPass;
			mutable passType m_LastCriticalPass;
			mutable indexType m_CurrentCriticalMove;
			mutable indexType m_CurrentLegalMove;
			mutable bool m_HasLegalMove;
			mutable bool m_HasLegalMoveValid;
			mutable bool m_IsPositionCriticalValid{ false };
			mutable bool m_IsPositionCritical{ false };
			const bool m_IsNullmove;
			const hashType m_Hash;
			constexpr static inline const size_t countNormalStages{ generatorType::countMovegenStages(movegenPhase::normal) };
			constexpr static inline const std::array<stageType, countNormalStages> m_NormalStages
			{
				arrayhelper::generate< countNormalStages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::normal, index); })
			};
			constexpr static inline const std::array<size_t, countNormalStages> countNormalPasses
			{
				arrayhelper::generate< countNormalStages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::normal, index)); })
			};
			constexpr static inline const size_t countQSPhase1Stages{ generatorType::countMovegenStages(movegenPhase::QSPhase1) };
			constexpr static inline const std::array<stageType, countQSPhase1Stages> m_QSPhase1Stages
			{
				arrayhelper::generate< countQSPhase1Stages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::QSPhase1, index); })
			};
			constexpr static inline const std::array<size_t, countQSPhase1Stages> countQSPhase1Passes
			{
				arrayhelper::generate< countQSPhase1Stages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::QSPhase1, index)); })
			};
			constexpr static inline const size_t countQSPhase1CriticalEvasionStages{ generatorType::countMovegenStages(movegenPhase::QSPhase1_CriticalEvasion) };
			constexpr static inline const std::array<stageType, countQSPhase1CriticalEvasionStages> m_QSPhase1CriticalEvasionStages
			{
				arrayhelper::generate< countQSPhase1CriticalEvasionStages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::QSPhase1_CriticalEvasion, index); })
			};
			constexpr static inline const std::array<size_t, countQSPhase1CriticalEvasionStages> countQSPhase1CriticalEvasionPasses
			{
				arrayhelper::generate< countQSPhase1CriticalEvasionStages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::QSPhase1_CriticalEvasion, index)); })
			};
			constexpr static inline const size_t countQSPhase2Stages{ generatorType::countMovegenStages(movegenPhase::QSPhase2) };
			constexpr static inline const std::array<stageType, countQSPhase2Stages> m_QSPhase2Stages
			{
				arrayhelper::generate< countQSPhase2Stages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::QSPhase2, index); })
			};
			constexpr static inline const std::array<size_t, countQSPhase2Stages> countQSPhase2Passes
			{
				arrayhelper::generate< countQSPhase2Stages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::QSPhase2, index)); })
			};
			constexpr static inline const size_t countQSPhase2CriticalEvasionStages{ generatorType::countMovegenStages(movegenPhase::QSPhase2_CriticalEvasion) };
			constexpr static inline const std::array<stageType, countQSPhase2CriticalEvasionStages> m_QSPhase2CriticalEvasionStages
			{
				arrayhelper::generate< countQSPhase2CriticalEvasionStages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::QSPhase2_CriticalEvasion, index); })
			};
			constexpr static inline const std::array<size_t, countQSPhase2CriticalEvasionStages> countQSPhase2CriticalEvasionPasses
			{
				arrayhelper::generate< countQSPhase2CriticalEvasionStages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::QSPhase2_CriticalEvasion, index)); })
			};
			constexpr static inline const size_t countQSPhase3Stages{ generatorType::countMovegenStages(movegenPhase::QSPhase3) };
			constexpr static inline const std::array<stageType, countQSPhase3Stages> m_QSPhase3Stages
			{
				arrayhelper::generate< countQSPhase3Stages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::QSPhase3, index); })
			};
			constexpr static inline const std::array<size_t, countQSPhase3Stages> countQSPhase3Passes
			{
				arrayhelper::generate< countQSPhase3Stages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::QSPhase3, index)); })
			};
			constexpr static inline const size_t countQSPhase3CriticalEvasionStages{ generatorType::countMovegenStages(movegenPhase::QSPhase3_CriticalEvasion) };
			constexpr static inline const std::array<stageType, countQSPhase3CriticalEvasionStages> m_QSPhase3CriticalEvasionStages
			{
				arrayhelper::generate< countQSPhase3CriticalEvasionStages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::QSPhase3_CriticalEvasion, index); })
			};
			constexpr static inline const std::array<size_t, countQSPhase3CriticalEvasionStages> countQSPhase3CriticalEvasionPasses
			{
				arrayhelper::generate< countQSPhase3CriticalEvasionStages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::QSPhase3_CriticalEvasion, index)); })
			};
			constexpr static inline const size_t countCriticalEvasionStages{ generatorType::countMovegenStages(movegenPhase::criticalEvasion) };
			constexpr static inline const std::array<stageType, countCriticalEvasionStages> m_CriticalEvasionStages
			{
				arrayhelper::generate< countCriticalEvasionStages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::criticalEvasion, index); })
			};
			constexpr static inline const std::array<size_t, countCriticalEvasionStages> countCriticalEvasionPasses
			{
				arrayhelper::generate< countCriticalEvasionStages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::criticalEvasion, index)); })
			};
			constexpr static inline const size_t countCriticalStages{ generatorType::countMovegenStages(movegenPhase::critical) };
			constexpr static inline const std::array<stageType, countCriticalStages> m_CriticalStages
			{
				arrayhelper::generate< countCriticalStages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::critical, index); })
			};
			constexpr static inline const std::array<size_t, countCriticalStages> countCriticalPasses
			{
				arrayhelper::generate< countCriticalStages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::critical, index)); })
			};
			bool computeHasLegalMove(const size_t depth, movegenFeedback& feedback) const
			{
				while (m_CurrentLegalMove >= m_pContext->normalMoves().length())
				{
					if (isPositionCritical())
					{
						if (m_CurrentNormalStage < countCriticalEvasionStages)
						{
							if (m_CurrentNormalPass < countCriticalEvasionPasses[m_CurrentNormalStage])
							{
								const auto index{ feedback.index(m_CriticalEvasionStages[m_CurrentNormalStage], m_CurrentNormalPass, depth) };
								generatorType::generateMoves(m_CriticalEvasionStages[m_CurrentNormalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), index);
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalPasses().add(index);
									m_pContext->normalStages().add(m_CriticalEvasionStages[m_CurrentNormalStage]);
								}
								++m_CurrentNormalPass;
							}
							else
							{
								++m_CurrentNormalStage;
								m_CurrentNormalPass = 0;
							}
						}
						else
							return false;
					}
					else
					{
						if (m_CurrentNormalStage < countNormalStages)
						{
							if (m_CurrentNormalPass < countNormalPasses[m_CurrentNormalStage])
							{
								const auto index{ feedback.index(m_NormalStages[m_CurrentNormalStage], m_CurrentNormalPass, depth) };
								generatorType::generateMoves(m_NormalStages[m_CurrentNormalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), index);
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalPasses().add(index);
									m_pContext->normalStages().add(m_NormalStages[m_CurrentNormalStage]);
								}
								++m_CurrentNormalPass;
							}
							else
							{
								++m_CurrentNormalStage;
								m_CurrentNormalPass = 0;
							}
						}
						else
							return false;
					}
				}
				while (m_CurrentLegalMove < m_pContext->normalMoves().length())
				{
					if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves()[m_CurrentLegalMove]))
					{
						++m_CurrentLegalMove;
						return true;
					}
					++m_CurrentLegalMove;
				}
				return computeHasLegalMove(depth, feedback);
			}
			template<typename LAMBDA, bool EXPECT_CUTOFF>
			bool computeHasLegalMove(const size_t depth, movegenFeedback& feedback, const LAMBDA& lambda) const
			{
				while (m_CurrentLegalMove >= m_pContext->normalMoves().length())
				{
					if (isPositionCritical())
					{
						if (m_CurrentNormalStage < countCriticalEvasionStages)
						{
							if (m_CurrentNormalPass < countCriticalEvasionPasses[m_CurrentNormalStage])
							{
								const auto index{ feedback.index(m_CriticalEvasionStages[m_CurrentNormalStage], m_CurrentNormalPass, depth) };
								generatorType::generateMoves(m_CriticalEvasionStages[m_CurrentNormalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), index);
								const auto start{ m_pContext->normalPasses().length() };
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalScores().add(lambda(m_pContext->normalMoves()[m_pContext->normalPasses().length()]));
									m_pContext->normalPasses().add(index);
									m_pContext->normalStages().add(m_CriticalEvasionStages[m_CurrentNormalStage]);
								}
								++m_CurrentNormalPass;
								if constexpr (!EXPECT_CUTOFF)
									sort<movebitsType, scoreType>::sortValues(m_pContext->normalMoves().ptr() + start, m_pContext->normalScores().ptr() + start, m_pContext->normalMoves().length() - start);
							}
							else
							{
								++m_CurrentNormalStage;
								m_CurrentNormalPass = 0;
							}
						}
						else
							return false;
					}
					else
					{
						if (m_CurrentNormalStage < countNormalStages)
						{
							if (m_CurrentNormalPass < countNormalPasses[m_CurrentNormalStage])
							{
								const auto index{ feedback.index(m_NormalStages[m_CurrentNormalStage], m_CurrentNormalPass, depth) };
								generatorType::generateMoves(m_NormalStages[m_CurrentNormalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), index);
								const auto start{ m_pContext->normalPasses().length() };
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalScores().add(lambda(m_pContext->normalMoves()[m_pContext->normalPasses().length()]));
									m_pContext->normalPasses().add(index);
									m_pContext->normalStages().add(m_NormalStages[m_CurrentNormalStage]);
								}
								++m_CurrentNormalPass;
								if constexpr (!EXPECT_CUTOFF)
									sort<movebitsType, scoreType>::sortValues(m_pContext->normalMoves().ptr() + start, m_pContext->normalScores().ptr() + start, m_pContext->normalMoves().length() - start);
							}
							else
							{
								++m_CurrentNormalStage;
								m_CurrentNormalPass = 0;
							}
						}
						else
							return false;
					}
				}
				while (m_CurrentLegalMove < m_pContext->normalMoves().length())
				{
					if constexpr (EXPECT_CUTOFF)
					{
						const indexType start{ std::max(m_CurrentNormalMove,m_CurrentLegalMove) };
						if (start < m_pContext->normalMoves().length())
						{
							constexpr scoreType minimum{ scoreType::minimum() };
							scoreType best{ minimum };
							indexType bestIdx{ start };
							for (indexType i = start; i < m_pContext->normalMoves().length(); i++)
							{
								if (m_pContext->normalScores()[i] > best)
								{
									best = m_pContext->normalScores()[i];
									bestIdx = i;
								}
							}
							if (start != bestIdx)
							{
								m_pContext->normalMoves().swap(start, bestIdx);
								m_pContext->normalStages().swap(start, bestIdx);
								m_pContext->normalScores().swap(start, bestIdx);
								m_pContext->normalPasses().swap(start, bestIdx);
							}
						}
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves()[m_CurrentLegalMove]))
						{
							++m_CurrentLegalMove;
							return true;
						}
						++m_CurrentLegalMove;
					}
					else
					{
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves()[m_CurrentLegalMove]))
						{
							++m_CurrentLegalMove;
							return true;
						}
						++m_CurrentLegalMove;
					}
				}
				return this->template computeHasLegalMove<LAMBDA, EXPECT_CUTOFF>(depth, feedback, lambda);
			}
		public:
			PYGMALION_INLINE passType lastNormalPass() const noexcept
			{
				return m_LastNormalPass;
			}
			PYGMALION_INLINE stageType lastNormalStage() const noexcept
			{
				return m_LastNormalStage;
			}
			PYGMALION_INLINE scoreType lastNormalScore() const noexcept
			{
				return m_LastNormalScore;
			}
			PYGMALION_INLINE scoreType lastTacticalScore() const noexcept
			{
				return m_LastTacticalScore;
			}
			PYGMALION_INLINE scoreType lastTacticalCriticalScore() const noexcept
			{
				return m_LastTacticalCriticalScore;
			}
			PYGMALION_INLINE scoreType lastCriticalScore() const noexcept
			{
				return m_LastCriticalScore;
			}
			constexpr size_t normalStagesCount() const noexcept
			{
				return countNormalStages;
			}
			constexpr size_t normalPassesCount(const stageType stage) const noexcept
			{
				return countNormalPasses[stage];
			}
			PYGMALION_INLINE stageType normalStage(const size_t stageIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countNormalStages);
				return m_NormalStages[stageIndex];
			}
			PYGMALION_INLINE passType normalPass(movegenFeedback& feedback, const size_t stageIndex, const size_t passIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countNormalStages);
				return feedback.index(m_NormalStages[stageIndex], passIndex, m_History.length());
			}
			constexpr size_t countStages_QSPhase1() const noexcept
			{
				return countQSPhase1Stages;
			}
			constexpr size_t countPasses_QSPhase1(const stageType stage) const noexcept
			{
				return countQSPhase1Passes[stage];
			}
			PYGMALION_INLINE stageType stageQSPhase1(const size_t stageIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countQSPhase1Stages);
				return m_QSPhase1Stages[stageIndex];
			}
			PYGMALION_INLINE passType passQSPhase1(movegenFeedback& feedback, const size_t stageIndex, const size_t passIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countQSPhase1Stages);
				return feedback.index(m_QSPhase1Stages[stageIndex], passIndex, m_History.length());
			}
			constexpr size_t countStages_QSPhase2() const noexcept
			{
				return countQSPhase2Stages;
			}
			constexpr size_t countPasses_QSPhase2(const stageType stage) const noexcept
			{
				return countQSPhase2Passes[stage];
			}
			PYGMALION_INLINE stageType stageQSPhase2(const size_t stageIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countQSPhase2Stages);
				return m_QSPhase2Stages[stageIndex];
			}
			PYGMALION_INLINE passType passQSPhase2(movegenFeedback& feedback, const size_t stageIndex, const size_t passIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countQSPhase2Stages);
				return feedback.index(m_QSPhase2Stages[stageIndex], passIndex, m_History.length());
			}
			constexpr size_t countStages_QSPhase3() const noexcept
			{
				return countQSPhase3Stages;
			}
			constexpr size_t countPasses_QSPhase3(const stageType stage) const noexcept
			{
				return countQSPhase3Passes[stage];
			}
			PYGMALION_INLINE stageType stageQSPhase3(const size_t stageIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countQSPhase3Stages);
				return m_QSPhase3Stages[stageIndex];
			}
			PYGMALION_INLINE passType passQSPhase3(movegenFeedback& feedback, const size_t stageIndex, const size_t passIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countQSPhase3Stages);
				return feedback.index(m_QSPhase3Stages[stageIndex], passIndex, m_History.length());
			}
			constexpr size_t criticalStagesCount() const noexcept
			{
				return countCriticalStages;
			}
			constexpr size_t criticalPassesCount(const stageType stage) const noexcept
			{
				return countCriticalPasses[stage];
			}
			PYGMALION_INLINE stageType criticalStage(const size_t stageIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countCriticalStages);
				return m_CriticalStages[stageIndex];
			}
			PYGMALION_INLINE passType criticalPass(movegenFeedback& feedback, const size_t stageIndex, const size_t passIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countCriticalStages);
				return feedback.index(m_CriticalStages[stageIndex], passIndex, m_History.length());
			}
			constexpr bool isPositionCritical() const noexcept
			{
				if (!m_IsPositionCriticalValid)
				{
					m_IsPositionCritical = generatorType::isPositionCritical(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this));
					m_IsPositionCriticalValid = true;
				}
				return m_IsPositionCritical;
			}
			PYGMALION_INLINE void normalAllMove(movegenFeedback& feedback, const size_t depth, const scoreType score, const scoreType eval) const noexcept
			{
				feedback.allMoveRaw(m_LastNormalStage, m_LastNormalPass, depth, generatorType::template makeSubjective<PLAYER>(score), generatorType::template makeSubjective<PLAYER>(eval));
			}
			PYGMALION_INLINE void normalCutMove(movegenFeedback& feedback, const size_t depth, const scoreType score, const scoreType eval) const noexcept
			{
				feedback.cutMoveRaw(m_LastNormalStage, m_LastNormalPass, depth, generatorType::template makeSubjective<PLAYER>(score), generatorType::template makeSubjective<PLAYER>(eval));
			}
			PYGMALION_INLINE void qsPhase1AllMove(movegenFeedback& feedback, const size_t depth, const scoreType score, const scoreType eval) const noexcept
			{
				feedback.allMoveRaw(m_LastQSPhase1Stage, m_LastQSPhase1Pass, depth, generatorType::template makeSubjective<PLAYER>(score), generatorType::template makeSubjective<PLAYER>(eval));
			}
			PYGMALION_INLINE void qsPhase1CutMove(movegenFeedback& feedback, const size_t depth, const scoreType score, const scoreType eval) const noexcept
			{
				feedback.cutMoveRaw(m_LastQSPhase1Stage, m_LastQSPhase1Pass, depth, generatorType::template makeSubjective<PLAYER>(score), generatorType::template makeSubjective<PLAYER>(eval));
			}
			PYGMALION_INLINE void qsPhase2AllMove(movegenFeedback& feedback, const size_t depth, const scoreType score, const scoreType eval) const noexcept
			{
				feedback.allMoveRaw(m_LastQSPhase2Stage, m_LastQSPhase2Pass, depth, generatorType::template makeSubjective<PLAYER>(score), generatorType::template makeSubjective<PLAYER>(eval));
			}
			PYGMALION_INLINE void qsPhase2CutMove(movegenFeedback& feedback, const size_t depth, const scoreType score, const scoreType eval) const noexcept
			{
				feedback.cutMoveRaw(m_LastQSPhase2Stage, m_LastQSPhase2Pass, depth, generatorType::template makeSubjective<PLAYER>(score), generatorType::template makeSubjective<PLAYER>(eval));
			}
			PYGMALION_INLINE void qsPhase3AllMove(movegenFeedback& feedback, const size_t depth, const scoreType score, const scoreType eval) const noexcept
			{
				feedback.allMoveRaw(m_LastQSPhase3Stage, m_LastQSPhase3Pass, depth, generatorType::template makeSubjective<PLAYER>(score), generatorType::template makeSubjective<PLAYER>(eval));
			}
			PYGMALION_INLINE void qsPhase3CutMove(movegenFeedback& feedback, const size_t depth, const scoreType score, const scoreType eval) const noexcept
			{
				feedback.cutMoveRaw(m_LastQSPhase3Stage, m_LastQSPhase3Pass, depth, generatorType::template makeSubjective<PLAYER>(score), generatorType::template makeSubjective<PLAYER>(eval));
			}
			PYGMALION_INLINE void criticalAllMove(movegenFeedback& feedback, const size_t depth, const scoreType score, const scoreType eval) const noexcept
			{
				feedback.allMoveRaw(m_LastCriticalStage, m_LastCriticalPass, depth, generatorType::template makeSubjective<PLAYER>(score), generatorType::template makeSubjective<PLAYER>(eval));
			}
			PYGMALION_INLINE void criticalCutMove(movegenFeedback& feedback, const size_t depth, const scoreType score, const scoreType eval) const noexcept
			{
				feedback.cutMoveRaw(m_LastCriticalStage, m_LastCriticalPass, depth, generatorType::template makeSubjective<PLAYER>(score), generatorType::template makeSubjective<PLAYER>(eval));
			}
			bool hasLegalMove(const size_t depth, movegenFeedback& feedback) const
			{
				if (!m_HasLegalMoveValid)
				{
					m_HasLegalMove = computeHasLegalMove(depth, feedback);
					m_HasLegalMoveValid = true;
				}
				return m_HasLegalMove;
			}
			template<typename LAMBDA, bool EXPECT_CUTOFF>
			bool hasLegalMove(const size_t depth, movegenFeedback& feedback, const LAMBDA& lambda) const
			{
				if (!m_HasLegalMoveValid)
				{
					m_HasLegalMove = this->computeHasLegalMove<LAMBDA, EXPECT_CUTOFF>(depth, feedback, lambda);
					m_HasLegalMoveValid = true;
				}
				return m_HasLegalMove;
			}
			bool isMoveLegal(const movebitsType moveBits) const noexcept
			{
				return generatorType::isMoveLegal(*static_cast<const typename generatorType::stackType*>(this), moveBits);
			}
			bool nextMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback) const noexcept
			{
				if (m_CurrentNormalMove >= m_pContext->normalMoves().length())
				{
					if (isPositionCritical())
					{
						if (m_CurrentNormalStage < countCriticalEvasionStages)
						{
							if (m_CurrentNormalPass < countCriticalEvasionPasses[m_CurrentNormalStage])
							{
								const auto index{ feedback.index(m_CriticalEvasionStages[m_CurrentNormalStage], m_CurrentNormalPass, depth) };
								generatorType::generateMoves(m_CriticalEvasionStages[m_CurrentNormalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), index);
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalPasses().add(index);
									m_pContext->normalStages().add(m_CriticalEvasionStages[m_CurrentNormalStage]);
								}
								++m_CurrentNormalPass;
							}
							else
							{
								++m_CurrentNormalStage;
								m_CurrentNormalPass = 0;
							}
						}
						else
							return false;
					}
					else
					{
						if (m_CurrentNormalStage < countNormalStages)
						{
							if (m_CurrentNormalPass < countNormalPasses[m_CurrentNormalStage])
							{
								const auto index{ feedback.index(m_NormalStages[m_CurrentNormalStage], m_CurrentNormalPass, depth) };
								generatorType::generateMoves(m_NormalStages[m_CurrentNormalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), index);
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalPasses().add(index);
									m_pContext->normalStages().add(m_NormalStages[m_CurrentNormalStage]);
								}
								++m_CurrentNormalPass;
							}
							else
							{
								++m_CurrentNormalStage;
								m_CurrentNormalPass = 0;
							}
						}
						else
							return false;
					}
				}
				constexpr const scoreType minimum{ scoreType::minimum() };
				while (m_CurrentNormalMove < m_pContext->normalMoves().length())
				{
					moveBits = m_pContext->normalMoves()[m_CurrentNormalMove];
					if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
					{
						m_LastNormalPass = m_pContext->normalPasses()[m_CurrentNormalMove];
						m_LastNormalStage = m_pContext->normalStages()[m_CurrentNormalMove];
						m_LastNormalScore = minimum;
						++m_CurrentNormalMove;
						return true;
					}
					++m_CurrentNormalMove;
				}
				return nextMove(moveBits, depth, feedback);
			}
			template<typename LAMBDA, bool EXPECT_CUTOFF>
			bool nextMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback, const LAMBDA& lambda) const noexcept
			{
				while (m_CurrentNormalMove >= m_pContext->normalMoves().length())
				{
					if (isPositionCritical())
					{
						if (m_CurrentNormalStage < countCriticalEvasionStages)
						{
							if (m_CurrentNormalPass < countCriticalEvasionPasses[m_CurrentNormalStage])
							{
								const auto index{ feedback.index(m_CriticalEvasionStages[m_CurrentNormalStage], m_CurrentNormalPass, depth) };
								generatorType::generateMoves(m_CriticalEvasionStages[m_CurrentNormalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), index);
								const auto start{ m_pContext->normalPasses().length() };
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalScores().add(lambda(m_pContext->normalMoves()[m_pContext->normalPasses().length()]));
									m_pContext->normalPasses().add(index);
									m_pContext->normalStages().add(m_CriticalEvasionStages[m_CurrentNormalStage]);
								}
								++m_CurrentNormalPass;
								if constexpr (!EXPECT_CUTOFF)
									sort<movebitsType, scoreType>::sortValues(m_pContext->normalMoves().ptr() + start, m_pContext->normalScores().ptr() + start, m_pContext->normalMoves().length() - start);
							}
							else
							{
								++m_CurrentNormalStage;
								m_CurrentNormalPass = 0;
							}
						}
						else
							return false;
					}
					else
					{
						if (m_CurrentNormalStage < countNormalStages)
						{
							if (m_CurrentNormalPass < countNormalPasses[m_CurrentNormalStage])
							{
								const auto index{ feedback.index(m_NormalStages[m_CurrentNormalStage], m_CurrentNormalPass, depth) };
								generatorType::generateMoves(m_NormalStages[m_CurrentNormalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), index);
								const auto start{ m_pContext->normalPasses().length() };
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalScores().add(lambda(m_pContext->normalMoves()[m_pContext->normalPasses().length()]));
									m_pContext->normalPasses().add(index);
									m_pContext->normalStages().add(m_NormalStages[m_CurrentNormalStage]);
								}
								++m_CurrentNormalPass;
								if constexpr (!EXPECT_CUTOFF)
									sort<movebitsType, scoreType>::sortValues(m_pContext->normalMoves().ptr() + start, m_pContext->normalScores().ptr() + start, m_pContext->normalMoves().length() - start);
							}
							else
							{
								++m_CurrentNormalStage;
								m_CurrentNormalPass = 0;
							}
						}
						else
							return false;
					}
				}
				while (m_CurrentNormalMove < m_pContext->normalMoves().length())
				{
					if constexpr (!EXPECT_CUTOFF)
					{
						const indexType start{ std::max(m_CurrentNormalMove,m_CurrentLegalMove) };
						if (start < m_pContext->normalMoves().length())
						{
							constexpr scoreType minimum{ scoreType::minimum() };
							scoreType best{ minimum };
							indexType bestIdx{ start };
							for (indexType i = start; i < m_pContext->normalMoves().length(); i++)
							{
								if (m_pContext->normalScores()[i] > best)
								{
									best = m_pContext->normalScores()[i];
									bestIdx = i;
								}
							}
							if (start != bestIdx)
							{
								m_pContext->normalMoves().swap(start, bestIdx);
								m_pContext->normalStages().swap(start, bestIdx);
								m_pContext->normalScores().swap(start, bestIdx);
								m_pContext->normalPasses().swap(start, bestIdx);
							}
						}
						moveBits = m_pContext->normalMoves()[m_CurrentNormalMove];
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
						{
							m_LastNormalPass = m_pContext->normalPasses()[m_CurrentNormalMove];
							m_LastNormalStage = m_pContext->normalStages()[m_CurrentNormalMove];
							m_LastNormalScore = m_pContext->normalScores()[m_CurrentNormalMove];
							++m_CurrentNormalMove;
							return true;
						}
						++m_CurrentNormalMove;
					}
					else
					{
						moveBits = m_pContext->normalMoves()[m_CurrentNormalMove];
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
						{
							m_LastNormalPass = m_pContext->normalPasses()[m_CurrentNormalMove];
							m_LastNormalStage = m_pContext->normalStages()[m_CurrentNormalMove];
							m_LastNormalScore = m_pContext->normalScores()[m_CurrentNormalMove];
							++m_CurrentNormalMove;
							return true;
						}
						++m_CurrentNormalMove;
					}
				}
				return this->template nextMove<LAMBDA, EXPECT_CUTOFF>(moveBits, depth, feedback, lambda);
			}
			bool nextQSPhase1Move(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback) const noexcept
			{
				while (m_CurrentQSPhase1Move >= m_pContext->qsPhase1Moves().length())
				{
					if (isPositionCritical())
					{
						if (m_CurrentQSPhase1Stage < countQSPhase1CriticalEvasionStages)
						{
							if (m_CurrentQSPhase1Pass < countQSPhase1CriticalEvasionPasses[m_CurrentQSPhase1Stage])
							{
								const auto index{ feedback.index(m_QSPhase1CriticalEvasionStages[m_CurrentQSPhase1Stage], m_CurrentQSPhase1Pass, depth) };
								generatorType::generateMoves(m_QSPhase1CriticalEvasionStages[m_CurrentQSPhase1Stage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->qsPhase1Moves(), index);
								while (m_pContext->qsPhase1Passes().length() < m_pContext->qsPhase1Moves().length())
								{
									m_pContext->qsPhase1Passes().add(index);
									m_pContext->qsPhase1Stages().add(m_QSPhase1CriticalEvasionStages[m_CurrentQSPhase1Stage]);
								}
								++m_CurrentQSPhase1Pass;
							}
							else
							{
								++m_CurrentQSPhase1Stage;
								m_CurrentQSPhase1Pass = 0;
							}
						}
						else
							return false;
					}
					else
					{
						if (m_CurrentQSPhase1Stage < countQSPhase1Stages)
						{
							if (m_CurrentQSPhase1Pass < countQSPhase1Passes[m_CurrentQSPhase1Stage])
							{
								const auto index{ feedback.index(m_QSPhase1Stages[m_CurrentQSPhase1Stage], m_CurrentQSPhase1Pass, depth) };
								generatorType::generateMoves(m_QSPhase1Stages[m_CurrentQSPhase1Stage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->qsPhase1Moves(), index);
								while (m_pContext->qsPhase1Passes().length() < m_pContext->qsPhase1Moves().length())
								{
									m_pContext->qsPhase1Passes().add(index);
									m_pContext->qsPhase1Stages().add(m_QSPhase1Stages[m_CurrentQSPhase1Stage]);
								}
								++m_CurrentQSPhase1Pass;
							}
							else
							{
								++m_CurrentQSPhase1Stage;
								m_CurrentQSPhase1Pass = 0;
							}
						}
						else
							return false;
					}
				}
				constexpr const scoreType minimum{ scoreType::minimum() };
				while (m_CurrentQSPhase1Move < m_pContext->qsPhase1Moves().length())
				{
					moveBits = m_pContext->qsPhase1Moves()[m_CurrentQSPhase1Move];
					if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
					{
						m_LastQSPhase1Pass = m_pContext->qsPhase1Passes()[m_CurrentQSPhase1Move];
						m_LastQSPhase1Stage = m_pContext->qsPhase1Stages()[m_CurrentQSPhase1Move];
						m_LastQSPhase1Score = minimum;
						++m_CurrentQSPhase1Move;
						return true;
					}
					++m_CurrentQSPhase1Move;
				}
				return nextQSPhase1Move(moveBits, depth, feedback);
			}
			template<typename LAMBDA, bool EXPECT_CUTOFF>
			bool nextQSPhase1Move(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback, const LAMBDA& lambda) const noexcept
			{
				while (m_CurrentQSPhase1Move >= m_pContext->qsPhase1Moves().length())
				{
					if (isPositionCritical())
					{
						if (m_CurrentQSPhase1Stage < countQSPhase1CriticalEvasionStages)
						{
							if (m_CurrentQSPhase1Pass < countQSPhase1CriticalEvasionPasses[m_CurrentQSPhase1Stage])
							{
								const auto index{ feedback.index(m_QSPhase1CriticalEvasionStages[m_CurrentQSPhase1Stage], m_CurrentQSPhase1Pass, depth) };
								generatorType::generateMoves(m_QSPhase1CriticalEvasionStages[m_CurrentQSPhase1Stage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->qsPhase1Moves(), index);
								const auto start{ m_pContext->qsPhase1Passes().length() };
								while (m_pContext->qsPhase1Passes().length() < m_pContext->qsPhase1Moves().length())
								{
									m_pContext->qsPhase1Scores().add(lambda(m_pContext->qsPhase1Moves()[m_pContext->qsPhase1Passes().length()]));
									m_pContext->qsPhase1Passes().add(index);
									m_pContext->qsPhase1Stages().add(m_QSPhase1CriticalEvasionStages[m_CurrentQSPhase1Stage]);
								}
								++m_CurrentQSPhase1Pass;
								if constexpr (!EXPECT_CUTOFF)
									sort<movebitsType, scoreType>::sortValues(m_pContext->qsPhase1Moves().ptr() + start, m_pContext->qsPhase1Scores().ptr() + start, m_pContext->qsPhase1Moves().length() - start);
							}
							else
							{
								++m_CurrentQSPhase1Stage;
								m_CurrentQSPhase1Pass = 0;
							}
						}
						else
							return false;
					}
					else
					{
						if (m_CurrentQSPhase1Stage < countQSPhase1Stages)
						{
							if (m_CurrentQSPhase1Pass < countQSPhase1Passes[m_CurrentQSPhase1Stage])
							{
								const auto index{ feedback.index(m_QSPhase1Stages[m_CurrentQSPhase1Stage], m_CurrentQSPhase1Pass, depth) };
								generatorType::generateMoves(m_QSPhase1Stages[m_CurrentQSPhase1Stage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->qsPhase1Moves(), index);
								const auto start{ m_pContext->qsPhase1Passes().length() };
								while (m_pContext->qsPhase1Passes().length() < m_pContext->qsPhase1Moves().length())
								{
									m_pContext->qsPhase1Scores().add(lambda(m_pContext->qsPhase1Moves()[m_pContext->qsPhase1Passes().length()]));
									m_pContext->qsPhase1Passes().add(index);
									m_pContext->qsPhase1Stages().add(m_QSPhase1Stages[m_CurrentQSPhase1Stage]);
								}
								++m_CurrentQSPhase1Pass;
								if constexpr (!EXPECT_CUTOFF)
									sort<movebitsType, scoreType>::sortValues(m_pContext->qsPhase1Moves().ptr() + start, m_pContext->qsPhase1Scores().ptr() + start, m_pContext->qsPhase1Moves().length() - start);
							}
							else
							{
								++m_CurrentQSPhase1Stage;
								m_CurrentQSPhase1Pass = 0;
							}
						}
						else
							return false;
					}
				}
				while (m_CurrentQSPhase1Move < m_pContext->qsPhase1Moves().length())
				{
					if constexpr (EXPECT_CUTOFF)
					{
						constexpr scoreType minimum{ scoreType::minimum() };
						scoreType best{ minimum };
						indexType bestIdx{ m_CurrentQSPhase1Move };
						for (indexType i = m_CurrentQSPhase1Move; i < m_pContext->qsPhase1Moves().length(); i++)
						{
							if (m_pContext->qsPhase1Scores()[i] > best)
							{
								best = m_pContext->qsPhase1Scores()[i];
								bestIdx = i;
							}
						}
						if (bestIdx != m_CurrentQSPhase1Move)
						{
							m_pContext->qsPhase1Moves().swap(m_CurrentQSPhase1Move, bestIdx);
							m_pContext->qsPhase1Stages().swap(m_CurrentQSPhase1Move, bestIdx);
							m_pContext->qsPhase1Scores().swap(m_CurrentQSPhase1Move, bestIdx);
							m_pContext->qsPhase1Passes().swap(m_CurrentQSPhase1Move, bestIdx);
						}
						moveBits = m_pContext->qsPhase1Moves()[m_CurrentQSPhase1Move];
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
						{
							m_LastQSPhase1Pass = m_pContext->qsPhase1Passes()[m_CurrentQSPhase1Move];
							m_LastQSPhase1Stage = m_pContext->qsPhase1Stages()[m_CurrentQSPhase1Move];
							m_LastQSPhase1Score = m_pContext->qsPhase1Scores()[m_CurrentQSPhase1Move];
							++m_CurrentQSPhase1Move;
							return true;
						}
						++m_CurrentQSPhase1Move;
					}
					else
					{
						moveBits = m_pContext->qsPhase1Moves()[m_CurrentQSPhase1Move];
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
						{
							m_LastQSPhase1Pass = m_pContext->qsPhase1Passes()[m_CurrentQSPhase1Move];
							m_LastQSPhase1Stage = m_pContext->qsPhase1Stages()[m_CurrentQSPhase1Move];
							m_LastQSPhase1Score = m_pContext->qsPhase1Scores()[m_CurrentQSPhase1Move];
							++m_CurrentQSPhase1Move;
							return true;
						}
						++m_CurrentQSPhase1Move;
					}
				}
				return this->template nextQSPhase1Move<LAMBDA, EXPECT_CUTOFF>(moveBits, depth, feedback, lambda);
			}
			bool nextQSPhase2Move(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback) const noexcept
			{
				while (m_CurrentQSPhase2Move >= m_pContext->qsPhase2Moves().length())
				{
					if (isPositionCritical())
					{
						if (m_CurrentQSPhase2Stage < countQSPhase2CriticalEvasionStages)
						{
							if (m_CurrentQSPhase2Pass < countQSPhase2CriticalEvasionPasses[m_CurrentQSPhase2Stage])
							{
								const auto index{ feedback.index(m_QSPhase2CriticalEvasionStages[m_CurrentQSPhase2Stage], m_CurrentQSPhase2Pass, depth) };
								generatorType::generateMoves(m_QSPhase2CriticalEvasionStages[m_CurrentQSPhase2Stage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->qsPhase2Moves(), index);
								while (m_pContext->qsPhase2Passes().length() < m_pContext->qsPhase2Moves().length())
								{
									m_pContext->qsPhase2Passes().add(index);
									m_pContext->qsPhase2Stages().add(m_QSPhase2CriticalEvasionStages[m_CurrentQSPhase2Stage]);
								}
								++m_CurrentQSPhase2Pass;
							}
							else
							{
								++m_CurrentQSPhase2Stage;
								m_CurrentQSPhase2Pass = 0;
							}
						}
						else
							return false;
					}
					else
					{
						if (m_CurrentQSPhase2Stage < countQSPhase2Stages)
						{
							if (m_CurrentQSPhase2Pass < countQSPhase2Passes[m_CurrentQSPhase2Stage])
							{
								const auto index{ feedback.index(m_QSPhase2Stages[m_CurrentQSPhase2Stage], m_CurrentQSPhase2Pass, depth) };
								generatorType::generateMoves(m_QSPhase2Stages[m_CurrentQSPhase2Stage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->qsPhase2Moves(), index);
								while (m_pContext->qsPhase2Passes().length() < m_pContext->qsPhase2Moves().length())
								{
									m_pContext->qsPhase2Passes().add(index);
									m_pContext->qsPhase2Stages().add(m_QSPhase2Stages[m_CurrentQSPhase2Stage]);
								}
								++m_CurrentQSPhase2Pass;
							}
							else
							{
								++m_CurrentQSPhase2Stage;
								m_CurrentQSPhase2Pass = 0;
							}
						}
						else
							return false;
					}
				}
				constexpr const scoreType minimum{ scoreType::minimum() };
				while (m_CurrentQSPhase2Move < m_pContext->qsPhase2Moves().length())
				{
					moveBits = m_pContext->qsPhase2Moves()[m_CurrentQSPhase2Move];
					if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
					{
						m_LastQSPhase2Pass = m_pContext->qsPhase2Passes()[m_CurrentQSPhase2Move];
						m_LastQSPhase2Stage = m_pContext->qsPhase2Stages()[m_CurrentQSPhase2Move];
						m_LastQSPhase2Score = minimum;
						++m_CurrentQSPhase2Move;
						return true;
					}
					++m_CurrentQSPhase2Move;
				}
				return nextQSPhase2Move(moveBits, depth, feedback);
			}
			template<typename LAMBDA, bool EXPECT_CUTOFF>
			bool nextQSPhase2Move(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback, const LAMBDA& lambda) const noexcept
			{
				while (m_CurrentQSPhase2Move >= m_pContext->qsPhase2Moves().length())
				{
					if (isPositionCritical())
					{
						if (m_CurrentQSPhase2Stage < countQSPhase2CriticalEvasionStages)
						{
							if (m_CurrentQSPhase2Pass < countQSPhase2CriticalEvasionPasses[m_CurrentQSPhase2Stage])
							{
								const auto index{ feedback.index(m_QSPhase2CriticalEvasionStages[m_CurrentQSPhase2Stage], m_CurrentQSPhase2Pass, depth) };
								generatorType::generateMoves(m_QSPhase2CriticalEvasionStages[m_CurrentQSPhase2Stage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->qsPhase2Moves(), index);
								const auto start{ m_pContext->qsPhase2Passes().length() };
								while (m_pContext->qsPhase2Passes().length() < m_pContext->qsPhase2Moves().length())
								{
									m_pContext->qsPhase2Scores().add(lambda(m_pContext->qsPhase2Moves()[m_pContext->qsPhase2Passes().length()]));
									m_pContext->qsPhase2Passes().add(index);
									m_pContext->qsPhase2Stages().add(m_QSPhase2CriticalEvasionStages[m_CurrentQSPhase2Stage]);
								}
								++m_CurrentQSPhase2Pass;
								if constexpr (!EXPECT_CUTOFF)
									sort<movebitsType, scoreType>::sortValues(m_pContext->qsPhase2Moves().ptr() + start, m_pContext->qsPhase2Scores().ptr() + start, m_pContext->qsPhase2Moves().length() - start);
							}
							else
							{
								++m_CurrentQSPhase2Stage;
								m_CurrentQSPhase2Pass = 0;
							}
						}
						else
							return false;
					}
					else
					{
						if (m_CurrentQSPhase2Stage < countQSPhase2Stages)
						{
							if (m_CurrentQSPhase2Pass < countQSPhase2Passes[m_CurrentQSPhase2Stage])
							{
								const auto index{ feedback.index(m_QSPhase2Stages[m_CurrentQSPhase2Stage], m_CurrentQSPhase2Pass, depth) };
								generatorType::generateMoves(m_QSPhase2Stages[m_CurrentQSPhase2Stage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->qsPhase2Moves(), index);
								const auto start{ m_pContext->qsPhase2Passes().length() };
								while (m_pContext->qsPhase2Passes().length() < m_pContext->qsPhase2Moves().length())
								{
									m_pContext->qsPhase2Scores().add(lambda(m_pContext->qsPhase2Moves()[m_pContext->qsPhase2Passes().length()]));
									m_pContext->qsPhase2Passes().add(index);
									m_pContext->qsPhase2Stages().add(m_QSPhase2Stages[m_CurrentQSPhase2Stage]);
								}
								++m_CurrentQSPhase2Pass;
								if constexpr (!EXPECT_CUTOFF)
									sort<movebitsType, scoreType>::sortValues(m_pContext->qsPhase2Moves().ptr() + start, m_pContext->qsPhase2Scores().ptr() + start, m_pContext->qsPhase2Moves().length() - start);
							}
							else
							{
								++m_CurrentQSPhase2Stage;
								m_CurrentQSPhase2Pass = 0;
							}
						}
						else
							return false;
					}
				}
				while (m_CurrentQSPhase2Move < m_pContext->qsPhase2Moves().length())
				{
					if constexpr (EXPECT_CUTOFF)
					{
						constexpr scoreType minimum{ scoreType::minimum() };
						scoreType best{ minimum };
						indexType bestIdx{ m_CurrentQSPhase2Move };
						for (indexType i = m_CurrentQSPhase2Move; i < m_pContext->qsPhase2Moves().length(); i++)
						{
							if (m_pContext->qsPhase2Scores()[i] > best)
							{
								best = m_pContext->qsPhase2Scores()[i];
								bestIdx = i;
							}
						}
						if (bestIdx != m_CurrentQSPhase2Move)
						{
							m_pContext->qsPhase2Moves().swap(m_CurrentQSPhase2Move, bestIdx);
							m_pContext->qsPhase2Stages().swap(m_CurrentQSPhase2Move, bestIdx);
							m_pContext->qsPhase2Scores().swap(m_CurrentQSPhase2Move, bestIdx);
							m_pContext->qsPhase2Passes().swap(m_CurrentQSPhase2Move, bestIdx);
						}
						moveBits = m_pContext->qsPhase2Moves()[m_CurrentQSPhase2Move];
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
						{
							m_LastQSPhase2Pass = m_pContext->qsPhase2Passes()[m_CurrentQSPhase2Move];
							m_LastQSPhase2Stage = m_pContext->qsPhase2Stages()[m_CurrentQSPhase2Move];
							m_LastQSPhase2Score = m_pContext->qsPhase2Scores()[m_CurrentQSPhase2Move];
							++m_CurrentQSPhase2Move;
							return true;
						}
						++m_CurrentQSPhase2Move;
					}
					else
					{
						moveBits = m_pContext->qsPhase2Moves()[m_CurrentQSPhase2Move];
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
						{
							m_LastQSPhase2Pass = m_pContext->qsPhase2Passes()[m_CurrentQSPhase2Move];
							m_LastQSPhase2Stage = m_pContext->qsPhase2Stages()[m_CurrentQSPhase2Move];
							m_LastQSPhase2Score = m_pContext->qsPhase2Scores()[m_CurrentQSPhase2Move];
							++m_CurrentQSPhase2Move;
							return true;
						}
						++m_CurrentQSPhase2Move;
					}
				}
				return this->template nextQSPhase2Move<LAMBDA, EXPECT_CUTOFF>(moveBits, depth, feedback, lambda);
			}
			bool nextQSPhase3Move(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback) const noexcept
			{
				while (m_CurrentQSPhase3Move >= m_pContext->qsPhase3Moves().length())
				{
					if (isPositionCritical())
					{
						if (m_CurrentQSPhase3Stage < countQSPhase3CriticalEvasionStages)
						{
							if (m_CurrentQSPhase3Pass < countQSPhase3CriticalEvasionPasses[m_CurrentQSPhase3Stage])
							{
								const auto index{ feedback.index(m_QSPhase3CriticalEvasionStages[m_CurrentQSPhase3Stage], m_CurrentQSPhase3Pass, depth) };
								generatorType::generateMoves(m_QSPhase3CriticalEvasionStages[m_CurrentQSPhase3Stage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->qsPhase3Moves(), index);
								while (m_pContext->qsPhase3Passes().length() < m_pContext->qsPhase3Moves().length())
								{
									m_pContext->qsPhase3Passes().add(index);
									m_pContext->qsPhase3Stages().add(m_QSPhase3CriticalEvasionStages[m_CurrentQSPhase3Stage]);
								}
								++m_CurrentQSPhase3Pass;
							}
							else
							{
								++m_CurrentQSPhase3Stage;
								m_CurrentQSPhase3Pass = 0;
							}
						}
						else
							return false;
					}
					else
					{
						if (m_CurrentQSPhase3Stage < countQSPhase3Stages)
						{
							if (m_CurrentQSPhase3Pass < countQSPhase3Passes[m_CurrentQSPhase3Stage])
							{
								const auto index{ feedback.index(m_QSPhase3Stages[m_CurrentQSPhase3Stage], m_CurrentQSPhase3Pass, depth) };
								generatorType::generateMoves(m_QSPhase3Stages[m_CurrentQSPhase3Stage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->qsPhase3Moves(), index);
								while (m_pContext->qsPhase3Passes().length() < m_pContext->qsPhase3Moves().length())
								{
									m_pContext->qsPhase3Passes().add(index);
									m_pContext->qsPhase3Stages().add(m_QSPhase3Stages[m_CurrentQSPhase3Stage]);
								}
								++m_CurrentQSPhase3Pass;
							}
							else
							{
								++m_CurrentQSPhase3Stage;
								m_CurrentQSPhase3Pass = 0;
							}
						}
						else
							return false;
					}
				}
				constexpr const scoreType minimum{ scoreType::minimum() };
				while (m_CurrentQSPhase3Move < m_pContext->qsPhase3Moves().length())
				{
					moveBits = m_pContext->qsPhase3Moves()[m_CurrentQSPhase3Move];
					if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
					{
						m_LastQSPhase3Pass = m_pContext->qsPhase3Passes()[m_CurrentQSPhase3Move];
						m_LastQSPhase3Stage = m_pContext->qsPhase3Stages()[m_CurrentQSPhase3Move];
						m_LastQSPhase3Score = minimum;
						++m_CurrentQSPhase3Move;
						return true;
					}
					++m_CurrentQSPhase3Move;
				}
				return nextQSPhase3Move(moveBits, depth, feedback);
			}
			template<typename LAMBDA, bool EXPECT_CUTOFF>
			bool nextQSPhase3Move(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback, const LAMBDA& lambda) const noexcept
			{
				while (m_CurrentQSPhase3Move >= m_pContext->qsPhase3Moves().length())
				{
					if (isPositionCritical())
					{
						if (m_CurrentQSPhase3Stage < countQSPhase3CriticalEvasionStages)
						{
							if (m_CurrentQSPhase3Pass < countQSPhase3CriticalEvasionPasses[m_CurrentQSPhase3Stage])
							{
								const auto index{ feedback.index(m_QSPhase3CriticalEvasionStages[m_CurrentQSPhase3Stage], m_CurrentQSPhase3Pass, depth) };
								generatorType::generateMoves(m_QSPhase3CriticalEvasionStages[m_CurrentQSPhase3Stage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->qsPhase3Moves(), index);
								const auto start{ m_pContext->qsPhase3Passes().length() };
								while (m_pContext->qsPhase3Passes().length() < m_pContext->qsPhase3Moves().length())
								{
									m_pContext->qsPhase3Scores().add(lambda(m_pContext->qsPhase3Moves()[m_pContext->qsPhase3Passes().length()]));
									m_pContext->qsPhase3Passes().add(index);
									m_pContext->qsPhase3Stages().add(m_QSPhase3CriticalEvasionStages[m_CurrentQSPhase3Stage]);
								}
								++m_CurrentQSPhase3Pass;
								if constexpr (!EXPECT_CUTOFF)
									sort<movebitsType, scoreType>::sortValues(m_pContext->qsPhase3Moves().ptr() + start, m_pContext->qsPhase3Scores().ptr() + start, m_pContext->qsPhase3Moves().length() - start);
							}
							else
							{
								++m_CurrentQSPhase3Stage;
								m_CurrentQSPhase3Pass = 0;
							}
						}
						else
							return false;
					}
					else
					{
						if (m_CurrentQSPhase3Stage < countQSPhase3Stages)
						{
							if (m_CurrentQSPhase3Pass < countQSPhase3Passes[m_CurrentQSPhase3Stage])
							{
								const auto index{ feedback.index(m_QSPhase3Stages[m_CurrentQSPhase3Stage], m_CurrentQSPhase3Pass, depth) };
								generatorType::generateMoves(m_QSPhase3Stages[m_CurrentQSPhase3Stage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->qsPhase3Moves(), index);
								const auto start{ m_pContext->qsPhase3Passes().length() };
								while (m_pContext->qsPhase3Passes().length() < m_pContext->qsPhase3Moves().length())
								{
									m_pContext->qsPhase3Scores().add(lambda(m_pContext->qsPhase3Moves()[m_pContext->qsPhase3Passes().length()]));
									m_pContext->qsPhase3Passes().add(index);
									m_pContext->qsPhase3Stages().add(m_QSPhase3Stages[m_CurrentQSPhase3Stage]);
								}
								++m_CurrentQSPhase3Pass;
								if constexpr (!EXPECT_CUTOFF)
									sort<movebitsType, scoreType>::sortValues(m_pContext->qsPhase3Moves().ptr() + start, m_pContext->qsPhase3Scores().ptr() + start, m_pContext->qsPhase3Moves().length() - start);
							}
							else
							{
								++m_CurrentQSPhase3Stage;
								m_CurrentQSPhase3Pass = 0;
							}
						}
						else
							return false;
					}
				}
				while (m_CurrentQSPhase3Move < m_pContext->qsPhase3Moves().length())
				{
					if constexpr (EXPECT_CUTOFF)
					{
						constexpr scoreType minimum{ scoreType::minimum() };
						scoreType best{ minimum };
						indexType bestIdx{ m_CurrentQSPhase3Move };
						for (indexType i = m_CurrentQSPhase3Move; i < m_pContext->qsPhase3Moves().length(); i++)
						{
							if (m_pContext->qsPhase3Scores()[i] > best)
							{
								best = m_pContext->qsPhase3Scores()[i];
								bestIdx = i;
							}
						}
						if (bestIdx != m_CurrentQSPhase3Move)
						{
							m_pContext->qsPhase3Moves().swap(m_CurrentQSPhase3Move, bestIdx);
							m_pContext->qsPhase3Stages().swap(m_CurrentQSPhase3Move, bestIdx);
							m_pContext->qsPhase3Scores().swap(m_CurrentQSPhase3Move, bestIdx);
							m_pContext->qsPhase3Passes().swap(m_CurrentQSPhase3Move, bestIdx);
						}
						moveBits = m_pContext->qsPhase3Moves()[m_CurrentQSPhase3Move];
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
						{
							m_LastQSPhase3Pass = m_pContext->qsPhase3Passes()[m_CurrentQSPhase3Move];
							m_LastQSPhase3Stage = m_pContext->qsPhase3Stages()[m_CurrentQSPhase3Move];
							m_LastQSPhase3Score = m_pContext->qsPhase3Scores()[m_CurrentQSPhase3Move];
							++m_CurrentQSPhase3Move;
							return true;
						}
						++m_CurrentQSPhase3Move;
					}
					else
					{
						moveBits = m_pContext->qsPhase3Moves()[m_CurrentQSPhase3Move];
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
						{
							m_LastQSPhase3Pass = m_pContext->qsPhase3Passes()[m_CurrentQSPhase3Move];
							m_LastQSPhase3Stage = m_pContext->qsPhase3Stages()[m_CurrentQSPhase3Move];
							m_LastQSPhase3Score = m_pContext->qsPhase3Scores()[m_CurrentQSPhase3Move];
							++m_CurrentQSPhase3Move;
							return true;
						}
						++m_CurrentQSPhase3Move;
					}
				}
				return this->template nextQSPhase3Move<LAMBDA, EXPECT_CUTOFF>(moveBits, depth, feedback, lambda);
			}
			bool nextCriticalMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback) const noexcept
			{
				while (m_CurrentCriticalMove >= m_pContext->criticalMoves().length())
				{
					if (m_CurrentCriticalStage < countCriticalStages)
					{
						if (m_CurrentCriticalPass < countCriticalPasses[static_cast<size_t>(m_CriticalStages[static_cast<size_t>(m_CurrentCriticalStage)])])
						{
							const auto index{ feedback.index(m_CriticalStages[static_cast<size_t>(m_CurrentCriticalStage)], m_CurrentCriticalPass, depth) };
							generatorType::generateMoves(m_CriticalStages[static_cast<size_t>(m_CurrentCriticalStage)], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->criticalMoves(), index);
							while (m_pContext->criticalPasses().length() < m_pContext->criticalMoves().length())
							{
								m_pContext->criticalPasses().add(index);
								m_pContext->criticalStages().add(m_CriticalStages[static_cast<size_t>(m_CurrentCriticalStage)]);
							}
							++m_CurrentCriticalPass;
						}
						else
						{
							++m_CurrentCriticalStage;
							m_CurrentCriticalPass = 0;
						}
					}
					else
						return false;
				}
				constexpr const scoreType minimum{ scoreType::minimum() };
				while (m_CurrentCriticalMove < m_pContext->criticalMoves().length())
				{
					moveBits = m_pContext->criticalMoves()[m_CurrentCriticalMove];
					if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
					{
						m_LastCriticalPass = m_pContext->criticalPasses()[m_CurrentCriticalMove];
						m_LastCriticalStage = m_pContext->criticalStages()[m_CurrentCriticalMove];
						m_LastCriticalScore = minimum;
						++m_CurrentCriticalMove;
						return true;
					}
					++m_CurrentCriticalMove;
				}
				return nextCriticalMove(moveBits, depth, feedback);
			}
			template<typename LAMBDA, bool EXPECT_CUTOFF>
			bool nextCriticalMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback, const LAMBDA& lambda) const noexcept
			{
				while (m_CurrentCriticalMove >= m_pContext->criticalMoves().length())
				{
					if (m_CurrentCriticalStage < countCriticalStages)
					{
						if (m_CurrentCriticalPass < countCriticalPasses[m_CurrentCriticalStage])
						{
							const auto index{ feedback.index(m_CriticalStages[m_CurrentCriticalStage], m_CurrentCriticalPass, depth) };
							generatorType::generateMoves(m_CriticalStages[m_CurrentCriticalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->criticalMoves(), index);
							const auto start{ m_pContext->criticalPasses().length() };
							while (m_pContext->criticalPasses().length() < m_pContext->criticalMoves().length())
							{
								m_pContext->criticalScores().add(lambda(m_pContext->criticalMoves()[m_pContext->criticalPasses().length()]));
								m_pContext->criticalPasses().add(index);
								m_pContext->criticalStages().add(m_CriticalStages[m_CurrentCriticalStage]);
							}
							++m_CurrentCriticalPass;
							if constexpr (!EXPECT_CUTOFF)
								sort<movebitsType, scoreType>::sortValues(m_pContext->criticalMoves().ptr() + start, m_pContext->criticalScores().ptr() + start, m_pContext->criticalMoves().length() - start);
						}
						else
						{
							++m_CurrentCriticalStage;
							m_CurrentCriticalPass = 0;
						}
					}
					else
						return false;
				}
				while (m_CurrentCriticalMove < m_pContext->criticalMoves().length())
				{
					if constexpr (EXPECT_CUTOFF)
					{
						constexpr scoreType minimum{ scoreType::minimum() };
						scoreType best{ minimum };
						indexType bestIdx{ m_CurrentCriticalMove };
						for (indexType i = m_CurrentCriticalMove; i < m_pContext->criticalMoves().length(); i++)
						{
							if (m_pContext->criticalScores()[i] > best)
							{
								best = m_pContext->criticalScores()[i];
								bestIdx = i;
							}
						}
						if (m_CurrentCriticalMove != bestIdx)
						{
							m_pContext->criticalMoves().swap(m_CurrentCriticalMove, bestIdx);
							m_pContext->criticalStages().swap(m_CurrentCriticalMove, bestIdx);
							m_pContext->criticalScores().swap(m_CurrentCriticalMove, bestIdx);
							m_pContext->criticalPasses().swap(m_CurrentCriticalMove, bestIdx);
						}
						moveBits = m_pContext->criticalMoves()[m_CurrentCriticalMove];
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
						{
							m_LastCriticalPass = m_pContext->criticalPasses()[m_CurrentCriticalMove];
							m_LastCriticalStage = m_pContext->criticalStages()[m_CurrentCriticalMove];
							m_LastCriticalScore = m_pContext->criticalScores()[m_CurrentCriticalMove];
							++m_CurrentCriticalMove;
							return true;
						}
						++m_CurrentCriticalMove;
					}
					else
					{
						moveBits = m_pContext->criticalMoves()[m_CurrentCriticalMove];
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
						{
							m_LastCriticalPass = m_pContext->criticalPasses()[m_CurrentCriticalMove];
							m_LastCriticalStage = m_pContext->criticalStages()[m_CurrentCriticalMove];
							m_LastCriticalScore = m_pContext->criticalScores()[m_CurrentCriticalMove];
							++m_CurrentCriticalMove;
							return true;
						}
						++m_CurrentCriticalMove;
					}
				}
				return this->template nextCriticalMove<LAMBDA, EXPECT_CUTOFF>(moveBits, depth, feedback, lambda);
			}
			contextType& context() noexcept
			{
				return *m_pContext;
			}
			PYGMALION_INLINE stack(const parentType& parent, const movebitsType moveBits) noexcept :
				m_pContext{ parent.m_pContext + 1 },
				m_pParent{ &parent },
				m_Position{ parent.m_Position },
				m_History{ parent.m_History },
				m_HasLegalMove{ false },
				m_HasLegalMoveValid{ false },
				m_CurrentLegalMove{ 0 },
				m_CurrentNormalPass{ 0 },
				m_CurrentNormalMove{ 0 },
				m_CurrentNormalStage{ 0 },
				m_CurrentQSPhase1Pass{ 0 },
				m_CurrentQSPhase1Move{ 0 },
				m_CurrentQSPhase1Stage{ 0 },
				m_CurrentQSPhase2Pass{ 0 },
				m_CurrentQSPhase2Move{ 0 },
				m_CurrentQSPhase2Stage{ 0 },
				m_CurrentQSPhase3Pass{ 0 },
				m_CurrentQSPhase3Move{ 0 },
				m_CurrentQSPhase3Stage{ 0 },
				m_CurrentCriticalPass{ 0 },
				m_CurrentCriticalMove{ 0 },
				m_CurrentCriticalStage{ 0 },
				m_IsNullmove{ false },
				m_Hash{ m_Position.hash() }
			{
				motorType::move().doMove(m_Position, moveBits, m_MoveData);
				m_pContext->clearMovegenLists();
			}
			PYGMALION_INLINE stack(boardType& position, historyType& history, contextType* pContext) noexcept :
				m_pContext{ pContext },
				m_pParent{ nullptr },
				m_Position{ position },
				m_History{ history },
				m_HasLegalMove{ false },
				m_HasLegalMoveValid{ false },
				m_CurrentLegalMove{ 0 },
				m_CurrentNormalPass{ 0 },
				m_CurrentNormalMove{ 0 },
				m_CurrentNormalStage{ 0 },
				m_CurrentQSPhase1Pass{ 0 },
				m_CurrentQSPhase1Move{ 0 },
				m_CurrentQSPhase1Stage{ 0 },
				m_CurrentQSPhase2Pass{ 0 },
				m_CurrentQSPhase2Move{ 0 },
				m_CurrentQSPhase2Stage{ 0 },
				m_CurrentQSPhase3Pass{ 0 },
				m_CurrentQSPhase3Move{ 0 },
				m_CurrentQSPhase3Stage{ 0 },
				m_CurrentCriticalPass{ 0 },
				m_CurrentCriticalMove{ 0 },
				m_CurrentCriticalStage{ 0 },
				m_IsNullmove{ true },
				m_Hash{ m_Position.hash() }
			{
				m_pContext->clearMovegenLists();
				PYGMALION_ASSERT(position.movingPlayer() == m_MovingPlayer);
			}
			PYGMALION_INLINE contextType* getContext() const noexcept
			{
				return m_pContext;
			}
			PYGMALION_INLINE const boardType& position() const noexcept
			{
				return m_Position;
			}
			PYGMALION_INLINE playerType movingPlayer() const noexcept
			{
				return m_MovingPlayer;
			}
			PYGMALION_INLINE playerType nextPlayer() const noexcept
			{
				return m_NextPlayer;
			}
			PYGMALION_INLINE playerType previousPlayer() const noexcept
			{
				return m_MoveData.movingPlayer();
			}
			PYGMALION_INLINE ~stack() noexcept
			{
				if (!m_IsNullmove)
					motorType::move().undoMove(m_Position, m_MoveData);
			}
			std::string moveToSAN(const movebitsType moveBits, const size_t depth) const noexcept
			{
				return generatorType::moveToSAN(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits);
			}
			bool parseSAN(const std::string& san, movebitsType& mv, size_t& count) const noexcept
			{
				return generatorType::parseSAN(san, *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), mv, count);
			}
			bool occurs(const boardType& position, const int times, const int start, const int frequency) const noexcept
			{
				if (m_pParent != nullptr)
				{
					if (start == 0)
					{
						if (m_Hash == position.hash())
						{
							if (times == 1)
								return true;
							else
								return m_pParent->occurs(position, times - 1, frequency - 1, frequency);
						}
						else
							return m_pParent->occurs(position, times, frequency - 1, frequency);
					}
					else
						return m_pParent->occurs(position, times, start - 1, frequency);
				}
				else
				{
					return m_History.occurs(position, times, start, frequency);
				}
			}
		};
	private:
		template<typename COMMAND>
		static std::shared_ptr<pygmalion::intrinsics::command> createCommand() noexcept
		{
			auto delCmd = [](pygmalion::intrinsics::command* pCmd)
			{
				delete static_cast<COMMAND*>(pCmd);
			};
			std::shared_ptr<pygmalion::intrinsics::command> pCommand(static_cast<pygmalion::intrinsics::command*>(new COMMAND()), delCmd);
			return pCommand;
		}
	protected:
		template<typename COMMAND>
		static void addCommand(std::deque<std::shared_ptr<pygmalion::intrinsics::command>>& list) noexcept
		{
			std::shared_ptr<pygmalion::intrinsics::command> pCommand{ createCommand<COMMAND>() };
			list.emplace_back(std::move(pCommand));
		}
	public:
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commands() noexcept
		{
			return generatorType::commandsImplementation();
		}
		template<typename stackType>
		static bool parseSAN(const std::string& san, const stackType& stack, movebitsType& mv, size_t& count) noexcept
		{
			return generatorType::parseSAN_Implementation(san, stack, mv, count);
		}
		template<typename stackType>
		static std::string moveToSAN(const stackType& stack, const movebitsType moveBits) noexcept
		{
			return generatorType::moveToSAN_Implementation(stack, moveBits);
		}
		static std::string passToString(const stageType stage, const passType pass) noexcept
		{
			return generatorType::passToString_Implementation(stage, pass);
		}
		static std::string tacticalPassToString(const passType tacticalPass) noexcept
		{
			return generatorType::tacticalPassToString_Implementation(tacticalPass);
		}
		static std::string tacticalCriticalEvasionPassToString(const passType tacticalCriticalEvasionPass) noexcept
		{
			return generatorType::tacticalCriticalEvasionPassToString_Implementation(tacticalCriticalEvasionPass);
		}
		static std::string criticalPassToString(const passType criticalPass) noexcept
		{
			return generatorType::criticalPassToString_Implementation(criticalPass);
		}
		static std::string criticalEvasionPassToString(const passType criticalEvasionPass) noexcept
		{
			return generatorType::criticalPassToString_Implementation(criticalEvasionPass);
		}
		static std::string quietCriticalPassToString(const passType quietCriticalPass) noexcept
		{
			return generatorType::quietCriticalPassToString_Implementation(quietCriticalPass);
		}
		template<typename stackType>
		constexpr static void generateMoves(const stageType stage, const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			generatorType::generateMoves_Implementation(stage, stack, moves, currentPass);
		}
		template<typename stackType>
		static bool isMoveLegal(const stackType& stack, const movebitsType moveBits) noexcept
		{
			return generatorType::isMoveLegal_Implementation(stack, moveBits);
		}
		template<typename stackType>
		static bool isGeneratedMoveLegal(const stackType& stack, const movebitsType moveBits) noexcept
		{
			return generatorType::isGeneratedMoveLegal_Implementation(stack, moveBits);
		}
		template<size_t PLAYER, typename stackType>
		static std::uintmax_t perft(const stackType& stack, const size_t depthRemaining, const size_t depth, std::uintmax_t& nodes, movegenFeedback& feedback) noexcept
		{
			if (depthRemaining <= 0)
				return 1;
			else
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				movebitsType mb;
				std::uintmax_t count{ 0 };
				while (stack.nextMove(mb, depth, feedback))
				{
					nodes++;
					using subStackType = typename generatorType::template stackType<static_cast<size_t>(player.next())>;
					subStackType subStack{ subStackType(stack, mb) };
					count += generator::perft<static_cast<size_t>(player.next()), subStackType>(subStack, depthRemaining - 1, depth + 1, nodes, feedback);
				}
				return count;
			}
		}
		template<typename stackType>
		static bool isMoveTactical(const stackType& stack, const movebitsType mv) noexcept
		{
			return generatorType::isMoveTactical_Implementation(stack, mv);
		}
		template<typename stackType>
		static bool isPositionCritical(const stackType& stack) noexcept
		{
			return generatorType::isPositionCritical_Implementation(stack);
		}
		constexpr static size_t countMoveBucketTypes() noexcept
		{
			return generatorType::countMoveBucketTypes_Implementation();
		}
		constexpr static size_t countMoveBuckets(const size_t bucketType) noexcept
		{
			return generatorType::countMoveBuckets_Implementation(bucketType);
		}
		static size_t moveBucket(const size_t bucketType, const boardType& position, const movebitsType mv) noexcept
		{
			return generatorType::moveBucket_Implementation(bucketType, position, mv);
		}
		constexpr static bool hasNullMove() noexcept
		{
			return generatorType::hasNullMove_Implementation();
		}
		constexpr static movebitsType nullMove() noexcept
		{
			return generatorType::nullMove_Implementation();
		}
		template<size_t PLAYER, typename stackType>
		static bool isMoveCritical(const stackType& stack, const movebitsType moveBits) noexcept
		{
			return generatorType::template isMoveCritical_Implementation<PLAYER>(stack, moveBits);
		}
		static void dumpSquares(const squaresType& squares) noexcept
		{
			std::cerr << squares;
			std::cerr << std::endl;
			if (squares)
			{
				std::cerr << "squares:";
				for (const auto sq : squares)
				{
					std::cerr << " " << boardType::squareToString(sq);
				}
				std::cerr << std::endl;
			}
			else
				std::cerr << "(no squares)" << std::endl;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType makeSubjective(const scoreType score) noexcept
		{
			return generatorType::template makeSubjective_Implementation<PLAYER>(score);
		}
		constexpr static size_t countMovegenStages(const movegenPhase phase) noexcept
		{
			return generatorType::countMovegenStages_Implementation(phase);
		}
		constexpr static size_t countMaxMovegenStages() noexcept
		{
			size_t n{ countMovegenStages(movegenPhase::normal) };
			n = std::max(n, countMovegenStages(movegenPhase::QSPhase1));
			n = std::max(n, countMovegenStages(movegenPhase::QSPhase2));
			n = std::max(n, countMovegenStages(movegenPhase::QSPhase3));
			n = std::max(n, countMovegenStages(movegenPhase::QSPhase1_CriticalEvasion));
			n = std::max(n, countMovegenStages(movegenPhase::QSPhase2_CriticalEvasion));
			n = std::max(n, countMovegenStages(movegenPhase::QSPhase3_CriticalEvasion));
			n = std::max(n, countMovegenStages(movegenPhase::criticalEvasion));
			n = std::max(n, countMovegenStages(movegenPhase::critical));
			return n;
		}
		constexpr static size_t countTotalMovegenStages() noexcept
		{
			return generatorType::countTotalMovegenStages_Implementation();
		}
		constexpr static size_t countMovegenPasses(const size_t stage) noexcept
		{
			return generatorType::countMovegenPasses_Implementation(stage);
		}
		constexpr static size_t countMaxMovegenPasses(const movegenPhase phase) noexcept
		{
			size_t n{ 0 };
			for (size_t stage = 0; stage < generatorType::countTotalMovegenStages(); stage++)
				n = std::max(n, countMovegenPasses(stage));
			return n;
		}
		constexpr static size_t countMaxMovegenPasses() noexcept
		{
			size_t n{ 0 };
			n = std::max(n, countMaxMovegenPasses(movegenPhase::normal));
			n = std::max(n, countMaxMovegenPasses(movegenPhase::QSPhase1));
			n = std::max(n, countMaxMovegenPasses(movegenPhase::QSPhase2));
			n = std::max(n, countMaxMovegenPasses(movegenPhase::QSPhase3));
			n = std::max(n, countMaxMovegenPasses(movegenPhase::QSPhase1_CriticalEvasion));
			n = std::max(n, countMaxMovegenPasses(movegenPhase::QSPhase2_CriticalEvasion));
			n = std::max(n, countMaxMovegenPasses(movegenPhase::QSPhase3_CriticalEvasion));
			n = std::max(n, countMaxMovegenPasses(movegenPhase::criticalEvasion));
			n = std::max(n, countMaxMovegenPasses(movegenPhase::critical));
			return n;
		}
		constexpr static size_t movegenStage(const movegenPhase phase, const size_t stageIndex) noexcept
		{
			return generatorType::movegenStage_Implementation(phase, stageIndex);
		}
	};
}