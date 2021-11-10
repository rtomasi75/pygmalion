namespace pygmalion
{
	enum class movegenPhase
	{
		normal,
		tactical,
		criticalEvasion,
		tacticalCrtiticalEvasion,
		critical
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
			stagelistType m_TacticalStages;
			stagelistType m_CriticalStages;
			scorelistType m_NormalScores;
			scorelistType m_TacticalScores;
			scorelistType m_CriticalScores;
			movelistType m_NormalMoves;
			movelistType m_TacticalMoves;
			movelistType m_CriticalMoves;
			passlistType m_NormalPasses;
			passlistType m_TacticalPasses;
			passlistType m_CriticalPasses;
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
			PYGMALION_INLINE scorelistType& tacticalScores() noexcept
			{
				return m_TacticalScores;
			}
			PYGMALION_INLINE movelistType& tacticalMoves() noexcept
			{
				return m_TacticalMoves;
			}
			PYGMALION_INLINE stagelistType& tacticalStages() noexcept
			{
				return m_TacticalStages;
			}
			PYGMALION_INLINE passlistType& tacticalPasses() noexcept
			{
				return m_TacticalPasses;
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
			void clearMovegenLists() noexcept
			{
				m_NormalStages.clear();
				m_NormalScores.clear();
				m_NormalMoves.clear();
				m_NormalPasses.clear();
				m_TacticalStages.clear();
				m_TacticalScores.clear();
				m_TacticalMoves.clear();
				m_TacticalPasses.clear();
				m_CriticalStages.clear();
				m_CriticalScores.clear();
				m_CriticalMoves.clear();
				m_CriticalPasses.clear();
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
			mutable stageType m_LastNormalStage;
			mutable stageType m_CurrentNormalStage;
			mutable stageType m_LastTacticalStage;
			mutable stageType m_CurrentTacticalStage;
			mutable stageType m_LastCriticalStage;
			mutable stageType m_CurrentCriticalStage;
			mutable passType m_CurrentNormalPass;
			mutable passType m_LastNormalPass;
			mutable passType m_CurrentTacticalPass;
			mutable passType m_LastTacticalPass;
			mutable passType m_CurrentCriticalPass;
			mutable passType m_LastCriticalPass;
			mutable indexType m_CurrentNormalMove;
			mutable indexType m_CurrentTacticalMove;
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
			constexpr static inline const size_t countTacticalStages{ generatorType::countMovegenStages(movegenPhase::tactical) };
			constexpr static inline const std::array<stageType, countTacticalStages> m_TacticalStages
			{
				arrayhelper::generate< countTacticalStages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::tactical, index); })
			};
			constexpr static inline const size_t countCriticalEvasionStages{ generatorType::countMovegenStages(movegenPhase::criticalEvasion) };
			constexpr static inline const std::array<stageType, countCriticalEvasionStages> m_CriticalEvasionStages
			{
				arrayhelper::generate< countCriticalEvasionStages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::criticalEvasion, index); })
			};
			constexpr static inline const size_t countCriticalEvasionTacticalStages{ generatorType::countMovegenStages(movegenPhase::tacticalCrtiticalEvasion) };
			constexpr static inline const std::array<stageType, countCriticalEvasionTacticalStages> m_CriticalEvasionTacticalStages
			{
				arrayhelper::generate< countCriticalEvasionTacticalStages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::tacticalCrtiticalEvasion, index); })
			};
			constexpr static inline const size_t countCriticalStages{ generatorType::countMovegenStages(movegenPhase::critical) };
			constexpr static inline const std::array<stageType, countCriticalStages> m_CriticalStages
			{
				arrayhelper::generate< countCriticalStages, stageType>([](const size_t index) {return generatorType::movegenStage(movegenPhase::critical, index); })
			};
			constexpr static inline const std::array<size_t, countNormalStages> countNormalPasses
			{
				arrayhelper::generate< countNormalStages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::normal, index)); })
			};
			constexpr static inline const std::array<size_t, countTacticalStages> countTacticalPasses
			{
				arrayhelper::generate< countTacticalStages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::tactical, index)); })
			};
			constexpr static inline const std::array<size_t, countCriticalEvasionStages> countCriticalEvasionPasses
			{
				arrayhelper::generate< countCriticalEvasionStages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::criticalEvasion, index)); })
			};
			constexpr static inline const std::array<size_t, countCriticalEvasionTacticalStages> countCriticalEvasionTacticalPasses
			{
				arrayhelper::generate< countCriticalEvasionTacticalStages, stageType>([](const size_t index) {return generatorType::countMovegenPasses(generatorType::movegenStage(movegenPhase::tacticalCrtiticalEvasion, index)); })
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
			template<typename LAMBDA>
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
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalScores().add(lambda(m_pContext->normalMoves()[m_pContext->normalPasses().length()]));
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
									m_pContext->normalScores().add(lambda(m_pContext->normalMoves()[m_pContext->normalPasses().length()]));
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
				return computeHasLegalMove(depth, feedback, lambda);
			}
		public:
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
			constexpr size_t tacticalStagesCount() const noexcept
			{
				return countTacticalStages;
			}
			constexpr size_t tacticalPassesCount(const stageType stage) const noexcept
			{
				return countTacticalPasses[stage];
			}
			PYGMALION_INLINE stageType tacticalStage(const size_t stageIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countTacticalStages);
				return m_TacticalStages[stageIndex];
			}
			PYGMALION_INLINE passType tacticalPass(movegenFeedback& feedback, const size_t stageIndex, const size_t passIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countTacticalStages);
				return feedback.index(m_TacticalStages[stageIndex], passIndex, m_History.length());
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
			PYGMALION_INLINE void tacticalAllMove(movegenFeedback& feedback, const size_t depth, const scoreType score, const scoreType eval) const noexcept
			{
				feedback.allMoveRaw(m_LastTacticalStage, m_LastTacticalPass, depth, generatorType::template makeSubjective<PLAYER>(score), generatorType::template makeSubjective<PLAYER>(eval));
			}
			PYGMALION_INLINE void tacticalCutMove(movegenFeedback& feedback, const size_t depth, const scoreType score, const scoreType eval) const noexcept
			{
				feedback.cutMoveRaw(m_LastTacticalStage, m_LastTacticalPass, depth, generatorType::template makeSubjective<PLAYER>(score), generatorType::template makeSubjective<PLAYER>(eval));
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
			template<typename LAMBDA>
			bool hasLegalMove(const size_t depth, movegenFeedback& feedback, const LAMBDA& lambda) const
			{
				if (!m_HasLegalMoveValid)
				{
					m_HasLegalMove = computeHasLegalMove(depth, feedback, lambda);
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
				while (m_CurrentNormalMove < m_pContext->normalMoves().length())
				{
					moveBits = m_pContext->normalMoves()[m_CurrentNormalMove];
					if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
					{
						m_LastNormalPass = m_pContext->normalPasses()[m_CurrentNormalMove];
						m_LastNormalStage = m_pContext->normalStages()[m_CurrentNormalMove];
						++m_CurrentNormalMove;
						return true;
					}
					++m_CurrentNormalMove;
				}
				return nextMove(moveBits, depth, feedback);
			}
			template<typename LAMBDA>
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
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalScores().add(lambda(m_pContext->normalMoves()[m_pContext->normalPasses().length()]));
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
									m_pContext->normalScores().add(lambda(m_pContext->normalMoves()[m_pContext->normalPasses().length()]));
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
				while (m_CurrentNormalMove < m_pContext->normalMoves().length())
				{
					moveBits = m_pContext->normalMoves()[m_CurrentNormalMove];
					if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
					{
						m_LastNormalPass = m_pContext->normalPasses()[m_CurrentNormalMove];
						m_LastNormalStage = m_pContext->normalStages()[m_CurrentNormalMove];
						++m_CurrentNormalMove;
						return true;
					}
					++m_CurrentNormalMove;
				}
				return nextMove(moveBits, depth, feedback, lambda);
			}
			bool nextTacticalMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback) const noexcept
			{
				while (m_CurrentTacticalMove >= m_pContext->tacticalMoves().length())
				{
					if (isPositionCritical())
					{
						if (m_CurrentTacticalStage < countCriticalEvasionTacticalStages)
						{
							if (m_CurrentTacticalPass < countCriticalEvasionTacticalPasses[m_CurrentTacticalStage])
							{
								const auto index{ feedback.index(m_CriticalEvasionTacticalStages[m_CurrentTacticalStage], m_CurrentTacticalPass, depth) };
								generatorType::generateMoves(m_CriticalEvasionTacticalStages[m_CurrentTacticalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->tacticalMoves(), index);
								while (m_pContext->tacticalPasses().length() < m_pContext->tacticalMoves().length())
								{
									m_pContext->tacticalPasses().add(index);
									m_pContext->tacticalStages().add(m_CriticalEvasionTacticalStages[m_CurrentTacticalStage]);
								}
								++m_CurrentTacticalPass;
							}
							else
							{
								++m_CurrentTacticalStage;
								m_CurrentTacticalPass = 0;
							}
						}
						else
							return false;
					}
					else
					{
						if (m_CurrentTacticalStage < countTacticalStages)
						{
							if (m_CurrentTacticalPass < countTacticalPasses[m_CurrentTacticalStage])
							{
								const auto index{ feedback.index(m_TacticalStages[m_CurrentTacticalStage], m_CurrentTacticalPass, depth) };
								generatorType::generateMoves(m_TacticalStages[m_CurrentTacticalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->tacticalMoves(), index);
								while (m_pContext->tacticalPasses().length() < m_pContext->tacticalMoves().length())
								{
									m_pContext->tacticalPasses().add(index);
									m_pContext->tacticalStages().add(m_TacticalStages[m_CurrentTacticalStage]);
								}
								++m_CurrentTacticalPass;
							}
							else
							{
								++m_CurrentTacticalStage;
								m_CurrentTacticalPass = 0;
							}
						}
						else
							return false;
					}
				}
				while (m_CurrentTacticalMove < m_pContext->tacticalMoves().length())
				{
					moveBits = m_pContext->tacticalMoves()[m_CurrentTacticalMove];
					if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
					{
						m_LastTacticalPass = m_pContext->tacticalPasses()[m_CurrentTacticalMove];
						m_LastTacticalStage = m_pContext->tacticalStages()[m_CurrentTacticalMove];
						++m_CurrentTacticalMove;
						return true;
					}
					++m_CurrentTacticalMove;
				}
				return nextTacticalMove(moveBits, depth, feedback);
			}
			template<typename LAMBDA>
			bool nextTacticalMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback, const LAMBDA& lambda) const noexcept
			{
				while (m_CurrentTacticalMove >= m_pContext->tacticalMoves().length())
				{
					if (isPositionCritical())
					{
						if (m_CurrentTacticalStage < countCriticalEvasionTacticalStages)
						{
							if (m_CurrentTacticalPass < countCriticalEvasionTacticalPasses[m_CurrentTacticalStage])
							{
								const auto index{ feedback.index(m_CriticalEvasionTacticalStages[m_CurrentTacticalStage], m_CurrentTacticalPass, depth) };
								generatorType::generateMoves(m_CriticalEvasionTacticalStages[m_CurrentTacticalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->tacticalMoves(), index);
								while (m_pContext->tacticalPasses().length() < m_pContext->tacticalMoves().length())
								{
									m_pContext->tacticalScores().add(lambda(m_pContext->tacticalMoves()[m_pContext->tacticalPasses().length()]));
									m_pContext->tacticalPasses().add(index);
									m_pContext->tacticalStages().add(m_CriticalEvasionTacticalStages[m_CurrentTacticalStage]);
								}
								++m_CurrentTacticalPass;
							}
							else
							{
								++m_CurrentTacticalStage;
								m_CurrentTacticalPass = 0;
							}
						}
						else
							return false;
					}
					else
					{
						if (m_CurrentTacticalStage < countTacticalStages)
						{
							if (m_CurrentTacticalPass < countTacticalPasses[m_CurrentTacticalStage])
							{
								const auto index{ feedback.index(m_TacticalStages[m_CurrentTacticalStage], m_CurrentTacticalPass, depth) };
								generatorType::generateMoves(m_TacticalStages[m_CurrentTacticalStage], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->tacticalMoves(), index);
								while (m_pContext->tacticalPasses().length() < m_pContext->tacticalMoves().length())
								{
									m_pContext->tacticalScores().add(lambda(m_pContext->tacticalMoves()[m_pContext->tacticalPasses().length()]));
									m_pContext->tacticalPasses().add(index);
									m_pContext->tacticalStages().add(m_TacticalStages[m_CurrentTacticalStage]);
								}
								++m_CurrentTacticalPass;
							}
							else
							{
								++m_CurrentTacticalStage;
								m_CurrentTacticalPass = 0;
							}
						}
						else
							return false;
					}
				}
				while (m_CurrentTacticalMove < m_pContext->tacticalMoves().length())
				{
					moveBits = m_pContext->tacticalMoves()[m_CurrentTacticalMove];
					if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
					{
						m_LastTacticalPass = m_pContext->tacticalPasses()[m_CurrentTacticalMove];
						m_LastTacticalStage = m_pContext->tacticalStages()[m_CurrentTacticalMove];
						++m_CurrentTacticalMove;
						return true;
					}
					++m_CurrentTacticalMove;
				}
				return nextTacticalMove(moveBits, depth, feedback, lambda);
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
				while (m_CurrentCriticalMove < m_pContext->criticalMoves().length())
				{
					moveBits = m_pContext->criticalMoves()[m_CurrentCriticalMove];
					if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
					{
						m_LastCriticalPass = m_pContext->criticalPasses()[m_CurrentCriticalMove];
						m_LastCriticalStage = m_pContext->criticalStages()[m_CurrentCriticalMove];
						++m_CurrentCriticalMove;
						return true;
					}
					++m_CurrentCriticalMove;
				}
				return nextCriticalMove(moveBits, depth, feedback);
			}
			template<typename LAMBDA>
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
					moveBits = m_pContext->criticalMoves()[m_CurrentCriticalMove];
					if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits))
					{
						m_LastCriticalPass = m_pContext->criticalPasses()[m_CurrentCriticalMove];
						m_LastCriticalStage = m_pContext->criticalStages()[m_CurrentCriticalMove];
						++m_CurrentCriticalMove;
						return true;
					}
					++m_CurrentCriticalMove;
				}
				return nextCriticalMove(moveBits, depth, feedback, lambda);
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
				m_CurrentTacticalPass{ 0 },
				m_CurrentTacticalMove{ 0 },
				m_CurrentTacticalStage{ 0 },
				m_LastTacticalPass{ 0 },
				m_LastTacticalStage{ 0 },
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
				m_CurrentTacticalPass{ 0 },
				m_CurrentTacticalMove{ 0 },
				m_CurrentTacticalStage{ 0 },
				m_LastTacticalPass{ 0 },
				m_LastTacticalStage{ 0 },
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
			std::string moveToString(const movebitsType moveBits, const size_t depth) const
			{
				return generatorType::moveToString(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits, depth);
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
		static std::string moveToString(const stackType& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
			return generatorType::moveToString_Implementation(stack, moveBits, depth);
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
			n = std::max(n, countMovegenStages(movegenPhase::tactical));
			n = std::max(n, countMovegenStages(movegenPhase::criticalEvasion));
			n = std::max(n, countMovegenStages(movegenPhase::tacticalCrtiticalEvasion));
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
			n = std::max(n, countMaxMovegenPasses(movegenPhase::tactical));
			n = std::max(n, countMaxMovegenPasses(movegenPhase::criticalEvasion));
			n = std::max(n, countMaxMovegenPasses(movegenPhase::tacticalCrtiticalEvasion));
			n = std::max(n, countMaxMovegenPasses(movegenPhase::critical));
			return n;
		}
		constexpr static size_t movegenStage(const movegenPhase phase, const size_t stageIndex) noexcept
		{
			return generatorType::movegenStage_Implementation(phase, stageIndex);
		}
	};
}