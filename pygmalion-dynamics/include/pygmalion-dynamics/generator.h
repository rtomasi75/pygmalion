namespace pygmalion
{
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
				std::array<std::array<std::uint64_t, maxCountPasses>, countMovegenStages> m_MoveCounters;
				std::array<std::array<scoreType, maxCountPasses>, countMovegenStages> m_ScoreCounters;
				std::array<std::array<passType, maxCountPasses>, countMovegenStages> m_Indices;
				constexpr static bool USE_SCORE{ true };
				constexpr void sortIndicesStage(const stageType stage) noexcept
				{
					if constexpr (!USE_SCORE)
						sort<passType, std::uint64_t>::sortValues(m_Indices[stage].data(), m_MoveCounters[static_cast<size_t>(stage)].data(), countMovegenPasses[static_cast<size_t>(stage)]);
					else
					{
						std::array <scoreType, maxCountPasses> scores;
						for (size_t pass = 0; pass < countMovegenPasses[static_cast<size_t>(stage)]; pass++)
						{
							scores[pass] = score(stage, static_cast<passType>(pass));
						}
						sort<passType, scoreType>::sortValues(m_Indices[static_cast<size_t>(stage)].data(), scores.data(), countMovegenPasses[static_cast<size_t>(stage)]);
					}
				}
				constexpr void resetStage(const stageType stage) noexcept
				{
					constexpr const scoreType zero{ scoreType::zero() };
					for (size_t i = 0; i < countMovegenPasses[static_cast<size_t>(stage)]; i++)
					{
						m_MoveCounters[static_cast<size_t>(stage)][i] = 0;
						m_ScoreCounters[static_cast<size_t>(stage)][i] = zero;
						m_Indices[static_cast<size_t>(stage)][i] = i;
					}
				}
			public:
				constexpr void sortIndices() noexcept
				{
					for (size_t stage = 0; stage < countMovegenStages; stage++)
						sortIndicesStage(static_cast<stageType>(stage));
				}
				constexpr passType index(const stageType stage, const passType pass) const noexcept
				{
					PYGMALION_ASSERT(stage < countMovegenStages);
					PYGMALION_ASSERT(pass < countMovegenPasses[static_cast<size_t>(stage)]);
					return m_Indices[static_cast<size_t>(stage)][static_cast<size_t>(pass)];
				}
				constexpr passType moveIndex(const stageType stage, const passType pass) const noexcept
				{
					PYGMALION_ASSERT(stage < countMovegenStages);
					PYGMALION_ASSERT(pass < countMovegenPasses[static_cast<size_t>(stage)]);
					if constexpr (!USE_SCORE)
						return pass;
					else
						return m_Indices[static_cast<size_t>(stage)][static_cast<size_t>(pass)];
				}
				constexpr passType scoreIndex(const stageType stage, const passType pass) const noexcept
				{
					PYGMALION_ASSERT(stage < countMovegenStages);
					PYGMALION_ASSERT(pass < countMovegenPasses[static_cast<size_t>(stage)]);
					return m_Indices[static_cast<size_t>(stage)][static_cast<size_t>(pass)];
				}
				constexpr feedback() noexcept
				{
					reset();
				}
				constexpr scoreType score(const stageType stage, const passType pass) const noexcept
				{
					PYGMALION_ASSERT(stage < countMovegenStages);
					PYGMALION_ASSERT(pass < countMovegenPasses[static_cast<size_t>(stage)]);
					const passType indexMove{ moveIndex(stage, pass) };
					const passType indexScore{ scoreIndex(stage, pass) };
					if (m_MoveCounters[static_cast<size_t>(stage)][static_cast<size_t>(indexMove)] == 0)
					{
						constexpr const scoreType minimum{ scoreType::minimum() };
						return minimum;
					}
					if (m_ScoreCounters[static_cast<size_t>(stage)][static_cast<size_t>(indexScore)].isOpen())
						return m_ScoreCounters[static_cast<size_t>(stage)][static_cast<size_t>(indexScore)] / static_cast<typename scoreType::valueType>(m_MoveCounters[static_cast<size_t>(stage)][static_cast<size_t>(indexMove)]);
					else
						return m_ScoreCounters[static_cast<size_t>(stage)][static_cast<size_t>(indexScore)];
				}
				constexpr const std::uint64_t& counter(const stageType stage, const passType pass) const noexcept
				{
					PYGMALION_ASSERT(stage < countMovegenStages);
					PYGMALION_ASSERT(pass < countMovegenPasses[static_cast<size_t>(stage)]);
					return m_MoveCounters[static_cast<size_t>(stage)][static_cast<size_t>(moveIndex(stage, pass))];
				}
				constexpr void incrementMove(const stageType stage, const passType pass, const scoreType score) noexcept
				{
					PYGMALION_ASSERT(stage < countMovegenStages);
					PYGMALION_ASSERT(pass < countMovegenPasses[static_cast<size_t>(stage)]);
					const passType indexMove{ moveIndex(stage, pass) };
					const passType indexScore{ scoreIndex(stage, pass) };
					if (score.isOpen())
					{
						if (m_ScoreCounters[static_cast<size_t>(stage)][static_cast<size_t>(indexScore)].isOpen())
							m_ScoreCounters[static_cast<size_t>(stage)][static_cast<size_t>(indexScore)] += score;
						else
							m_ScoreCounters[static_cast<size_t>(stage)][static_cast<size_t>(indexScore)] = scoreType::max(score, m_ScoreCounters[static_cast<size_t>(stage)][static_cast<size_t>(indexScore)]);
					}
					else
						m_ScoreCounters[static_cast<size_t>(stage)][static_cast<size_t>(indexScore)] = scoreType::max(score, m_ScoreCounters[static_cast<size_t>(stage)][static_cast<size_t>(indexScore)]);
					m_MoveCounters[static_cast<size_t>(stage)][static_cast<size_t>(indexMove)]++;
				}
				constexpr void reset() noexcept
				{
					for (size_t stage = 0; stage < countMovegenStages; stage++)
						resetStage(static_cast<stageType>(stage));
				}
			};
			mutable std::vector<feedback> m_Feedback;
		public:
			constexpr movegenFeedback() noexcept :
				m_Feedback{ std::vector<feedback>(0) }
			{

			}
			constexpr void sortIndices(const size_t from_depth) noexcept
			{
				for (size_t d = from_depth; d < m_Feedback.size(); d++)
				{
					m_Feedback[d].sortIndices();
				}
			}
			constexpr const std::uint64_t& counter(const stageType stage, const passType pass, const size_t depth) const noexcept
			{
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].counter(stage, pass);
			}
			constexpr scoreType score(const stageType stage, const passType pass, const size_t depth) const noexcept
			{
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				if (depth >= 2)
					return (m_Feedback[depth - 2].score(stage, pass) + (3 * m_Feedback[depth].score(stage, pass))) / 4;
				else
					return m_Feedback[depth].score(stage, pass);
			}
			constexpr void cutMove(const stageType stage, const passType pass, const size_t depth, const scoreType& score) noexcept
			{
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementMove(stage, pass, score);
			}
			constexpr void allMove(const stageType stage, const passType pass, const size_t depth, const scoreType score) noexcept
			{
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementMove(stage, pass, score);
			}
			constexpr void reset() noexcept
			{
				m_Feedback.clear();
			}
			constexpr passType index(const stageType stage, const passType pass, const size_t depth) const noexcept
			{
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].index(stage, pass);
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
			stagelistType& normalStages() noexcept
			{
				return m_NormalStages;
			}
			scorelistType& normalScores() noexcept
			{
				return m_NormalScores;
			}
			movelistType& normalMoves() noexcept
			{
				return m_NormalMoves;
			}
			passlistType& normalPasses() noexcept
			{
				return m_NormalPasses;
			}
			scorelistType& tacticalScores() noexcept
			{
				return m_TacticalScores;
			}
			movelistType& tacticalMoves() noexcept
			{
				return m_TacticalMoves;
			}
			stagelistType& tacticalStages() noexcept
			{
				return m_TacticalStages;
			}
			passlistType& tacticalPasses() noexcept
			{
				return m_TacticalPasses;
			}
			stagelistType& criticalStages() noexcept
			{
				return m_CriticalStages;
			}
			scorelistType& criticalScores() noexcept
			{
				return m_CriticalScores;
			}
			movelistType& criticalMoves() noexcept
			{
				return m_CriticalMoves;
			}
			passlistType& criticalPasses() noexcept
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
			const movedataType m_MoveData;
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
			constexpr static inline const std::array<size_t, 4> m_NormalStages
			{
				movegenStage_WinningMoves,
				movegenStage_QuietMoves,
				movegenStage_EqualMoves,
				movegenStage_LosingMoves
			};
			constexpr static inline const size_t countNormalStages{ 4 };
			constexpr static inline const std::array<size_t, 3> m_TacticalStages
			{
				movegenStage_WinningMoves,
				movegenStage_EqualMoves,
				movegenStage_LosingMoves
			};
			constexpr static inline const size_t countTacticalStages{ 3 };
			constexpr static inline const std::array<size_t, 1> m_CriticalEvasionStages
			{
				movegenStage_CriticalEvasionMoves
			};
			constexpr static inline const size_t countCriticalEvasionStages{ 1 };
			constexpr static inline const std::array<size_t, 1> m_CriticalEvasionTacticalStages
			{
				movegenStage_TacticalCriticalEvasionMoves
			};
			constexpr static inline const size_t countCriticalEvasionTacticalStages{ 1 };
			constexpr static inline const std::array<size_t, 4> m_CriticalStages
			{
				movegenStage_CriticalMoves
			};
			constexpr static inline const size_t countCriticalStages{ 1 };
			bool computeHasLegalMove(const size_t depth, movegenFeedback& feedback) const
			{
				while (m_CurrentLegalMove >= m_pContext->normalMoves().length())
				{
					if (m_CurrentNormalStage < countNormalStages)
					{
						if (m_CurrentNormalPass < countMovegenPasses[static_cast<size_t>(m_NormalStages[static_cast<size_t>(m_CurrentNormalStage)])])
						{
							generatorType::generateMoves(m_NormalStages[static_cast<size_t>(m_CurrentNormalStage)], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), feedback.index(m_NormalStages[static_cast<size_t>(m_CurrentNormalStage)], m_CurrentNormalPass, depth));
							while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
							{
								m_pContext->normalPasses().add(m_CurrentNormalPass);
								m_pContext->normalStages().add(m_NormalStages[static_cast<size_t>(m_CurrentNormalStage)]);
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
		public:
			constexpr size_t normalStagesCount() const noexcept
			{
				return countNormalStages;
			}
			constexpr size_t normalPassesCount(const stageType stage) const noexcept
			{
				PYGMALION_ASSERT(stage < countNormalStages);
				return countMovegenPasses[static_cast<size_t>(m_NormalStages[static_cast<size_t>(stage)])];
			}
			constexpr stageType normalStage(const size_t stageIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countNormalStages);
				return m_NormalStages[stageIndex];
			}
			constexpr passType normalPass(movegenFeedback& feedback, const size_t stageIndex, const size_t passIndex) const noexcept
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
				PYGMALION_ASSERT(stage < countTacticalStages);
				return countMovegenPasses[static_cast<size_t>(m_TacticalStages[static_cast<size_t>(stage)])];
			}
			constexpr stageType tacticalStage(const size_t stageIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countTacticalStages);
				return m_TacticalStages[stageIndex];
			}
			constexpr passType tacticalPass(movegenFeedback& feedback, const size_t stageIndex, const size_t passIndex) const noexcept
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
				PYGMALION_ASSERT(stage < countCriticalStages);
				return countMovegenPasses[static_cast<size_t>(m_CriticalStages[static_cast<size_t>(stage)])];
			}
			constexpr stageType criticalStage(const size_t stageIndex) const noexcept
			{
				PYGMALION_ASSERT(stageIndex < countCriticalStages);
				return m_CriticalStages[stageIndex];
			}
			constexpr passType criticalPass(movegenFeedback& feedback, const size_t stageIndex, const size_t passIndex) const noexcept
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
			constexpr void normalAllMove(movegenFeedback& feedback, const size_t depth, const scoreType score) const noexcept
			{
				feedback.allMove(m_LastNormalStage, m_LastNormalPass, depth, score);
			}
			constexpr void normalCutMove(movegenFeedback& feedback, const size_t depth, const scoreType score) const noexcept
			{
				feedback.cutMove(m_LastNormalStage, m_LastNormalPass, depth, score);
			}
			constexpr void tacticalAllMove(movegenFeedback& feedback, const size_t depth, const scoreType score) const noexcept
			{
				feedback.allMove(m_LastTacticalStage, m_LastTacticalPass, depth, score);
			}
			constexpr void tacticalCutMove(movegenFeedback& feedback, const size_t depth, const scoreType score) const noexcept
			{
				feedback.cutMove(m_LastTacticalStage, m_LastTacticalPass, depth, score);
			}
			constexpr void criticalAllMove(movegenFeedback& feedback, const size_t depth, const scoreType score) const noexcept
			{
				feedback.allMove(m_LastCriticalStage, m_LastCriticalPass, depth, score);
			}
			constexpr void criticalCutMove(movegenFeedback& feedback, const size_t depth, const scoreType score) const noexcept
			{
				feedback.cutMove(m_LastCriticalStage, m_LastCriticalPass, depth, score);
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
			signatureType signature() const noexcept
			{
				return this->position().signature();
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
							if (m_CurrentNormalPass < countMovegenPasses[static_cast<size_t>(m_CriticalEvasionStages[static_cast<size_t>(m_CurrentNormalStage)])])
							{
								generatorType::generateMoves(m_CriticalEvasionStages[static_cast<size_t>(m_CurrentNormalStage)], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), feedback.index(m_CriticalEvasionStages[static_cast<size_t>(m_CurrentNormalStage)], m_CurrentNormalPass, depth));
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalPasses().add(m_CurrentNormalPass);
									m_pContext->normalStages().add(m_CriticalEvasionStages[static_cast<size_t>(m_CurrentNormalStage)]);
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
							if (m_CurrentNormalPass < countMovegenPasses[static_cast<size_t>(m_NormalStages[static_cast<size_t>(m_CurrentNormalStage)])])
							{
								generatorType::generateMoves(m_NormalStages[static_cast<size_t>(m_CurrentNormalStage)], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), feedback.index(m_NormalStages[static_cast<size_t>(m_CurrentNormalStage)], m_CurrentNormalPass, depth));
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalPasses().add(m_CurrentNormalPass);
									m_pContext->normalStages().add(m_NormalStages[static_cast<size_t>(m_CurrentNormalStage)]);
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
							if (m_CurrentNormalPass < countMovegenPasses[static_cast<size_t>(m_CriticalEvasionStages[static_cast<size_t>(m_CurrentNormalStage)])])
							{
								generatorType::generateMoves(m_CriticalEvasionStages[static_cast<size_t>(m_CurrentNormalStage)], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), feedback.index(m_CriticalEvasionStages[static_cast<size_t>(m_CurrentNormalStage)], m_CurrentNormalPass, depth));
								const auto start{ m_pContext->normalPasses().length() };
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalScores().add(lambda(m_pContext->normalMoves()[m_pContext->normalPasses().length()]));
									m_pContext->normalPasses().add(m_CurrentNormalPass);
									m_pContext->normalStages().add(m_CriticalEvasionStages[static_cast<size_t>(m_CurrentNormalStage)]);
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
							if (m_CurrentNormalPass < countMovegenPasses[static_cast<size_t>(m_NormalStages[static_cast<size_t>(m_CurrentNormalStage)])])
							{
								generatorType::generateMoves(m_NormalStages[static_cast<size_t>(m_CurrentNormalStage)], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->normalMoves(), feedback.index(m_NormalStages[static_cast<size_t>(m_CurrentNormalStage)], m_CurrentNormalPass, depth));
								const auto start{ m_pContext->normalPasses().length() };
								while (m_pContext->normalPasses().length() < m_pContext->normalMoves().length())
								{
									m_pContext->normalScores().add(lambda(m_pContext->normalMoves()[m_pContext->normalPasses().length()]));
									m_pContext->normalPasses().add(m_CurrentNormalPass);
									m_pContext->normalStages().add(m_NormalStages[static_cast<size_t>(m_CurrentNormalStage)]);
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
							if (m_CurrentTacticalPass < countMovegenPasses[static_cast<size_t>(m_CriticalEvasionTacticalStages[static_cast<size_t>(m_CurrentTacticalStage)])])
							{
								generatorType::generateMoves(m_CriticalEvasionTacticalStages[static_cast<size_t>(m_CurrentTacticalStage)], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->tacticalMoves(), feedback.index(m_CriticalEvasionTacticalStages[static_cast<size_t>(m_CurrentTacticalStage)], m_CurrentTacticalPass, depth));
								while (m_pContext->tacticalPasses().length() < m_pContext->tacticalMoves().length())
								{
									m_pContext->tacticalPasses().add(m_CurrentTacticalPass);
									m_pContext->tacticalStages().add(m_CriticalEvasionTacticalStages[static_cast<size_t>(m_CurrentTacticalStage)]);
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
							if (m_CurrentTacticalPass < countMovegenPasses[static_cast<size_t>(m_TacticalStages[static_cast<size_t>(m_CurrentTacticalStage)])])
							{
								generatorType::generateMoves(m_TacticalStages[static_cast<size_t>(m_CurrentTacticalStage)], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->tacticalMoves(), feedback.index(m_TacticalStages[static_cast<size_t>(m_CurrentTacticalStage)], m_CurrentTacticalPass, depth));
								while (m_pContext->tacticalPasses().length() < m_pContext->tacticalMoves().length())
								{
									m_pContext->tacticalPasses().add(m_CurrentTacticalPass);
									m_pContext->tacticalStages().add(m_TacticalStages[static_cast<size_t>(m_CurrentTacticalStage)]);
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
							if (m_CurrentTacticalPass < countMovegenPasses[static_cast<size_t>(m_CriticalEvasionTacticalStages[static_cast<size_t>(m_CurrentTacticalStage)])])
							{
								generatorType::generateMoves(m_CriticalEvasionTacticalStages[static_cast<size_t>(m_CurrentTacticalStage)], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->tacticalMoves(), feedback.index(m_CriticalEvasionTacticalStages[static_cast<size_t>(m_CurrentTacticalStage)], m_CurrentTacticalPass, depth));
								const auto start{ m_pContext->tacticalPasses().length() };
								while (m_pContext->tacticalPasses().length() < m_pContext->tacticalMoves().length())
								{
									m_pContext->tacticalScores().add(lambda(m_pContext->tacticalMoves()[m_pContext->tacticalPasses().length()]));
									m_pContext->tacticalPasses().add(m_CurrentTacticalPass);
									m_pContext->tacticalStages().add(m_CriticalEvasionTacticalStages[static_cast<size_t>(m_CurrentTacticalStage)]);
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
							if (m_CurrentTacticalPass < countMovegenPasses[static_cast<size_t>(m_TacticalStages[static_cast<size_t>(m_CurrentTacticalStage)])])
							{
								generatorType::generateMoves(m_TacticalStages[static_cast<size_t>(m_CurrentTacticalStage)], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->tacticalMoves(), feedback.index(m_TacticalStages[static_cast<size_t>(m_CurrentTacticalStage)], m_CurrentTacticalPass, depth));
								const auto start{ m_pContext->tacticalPasses().length() };
								while (m_pContext->tacticalPasses().length() < m_pContext->tacticalMoves().length())
								{
									m_pContext->tacticalScores().add(lambda(m_pContext->tacticalMoves()[m_pContext->tacticalPasses().length()]));
									m_pContext->tacticalPasses().add(m_CurrentTacticalPass);
									m_pContext->tacticalStages().add(m_TacticalStages[static_cast<size_t>(m_CurrentTacticalStage)]);
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
						if (m_CurrentCriticalPass < countMovegenPasses[static_cast<size_t>(m_CriticalStages[static_cast<size_t>(m_CurrentCriticalStage)])])
						{
							generatorType::generateMoves(m_CriticalStages[static_cast<size_t>(m_CurrentCriticalStage)], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->criticalMoves(), feedback.index(m_CriticalStages[static_cast<size_t>(m_CurrentCriticalStage)], m_CurrentCriticalPass, depth));
							while (m_pContext->criticalPasses().length() < m_pContext->criticalMoves().length())
							{
								m_pContext->criticalPasses().add(m_CurrentCriticalPass);
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
						if (m_CurrentCriticalPass < countMovegenPasses[static_cast<size_t>(m_CriticalStages[static_cast<size_t>(m_CurrentCriticalStage)])])
						{
							generatorType::generateMoves(m_CriticalStages[static_cast<size_t>(m_CurrentCriticalStage)], *static_cast<const typename generatorType::template stackType<PLAYER>*>(this), m_pContext->criticalMoves(), feedback.index(m_CriticalStages[static_cast<size_t>(m_CurrentCriticalStage)], m_CurrentCriticalPass, depth));
							const auto start{ m_pContext->criticalPasses().length() };
							while (m_pContext->criticalPasses().length() < m_pContext->criticalMoves().length())
							{
								m_pContext->criticalScores().add(lambda(m_pContext->criticalMoves()[m_pContext->criticalPasses().length()]));
								m_pContext->criticalPasses().add(m_CurrentCriticalPass);
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
				return nextCriticalMove(moveBits, depth, feedback, lambda);
			}
			stack(const parentType& parent, const movebitsType moveBits) noexcept :
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
				m_LastNormalPass{ 0 },
				m_LastNormalStage{ 0 },
				m_CurrentTacticalPass{ 0 },
				m_CurrentTacticalMove{ 0 },
				m_CurrentTacticalStage{ 0 },
				m_LastTacticalPass{ 0 },
				m_LastTacticalStage{ 0 },
				m_CurrentCriticalPass{ 0 },
				m_CurrentCriticalMove{ 0 },
				m_CurrentCriticalStage{ 0 },
				m_LastCriticalPass{ 0 },
				m_LastCriticalStage{ 0 },
				m_MoveData(motorType::move().doMove(m_Position, moveBits)),
				m_IsNullmove{ false },
				m_Hash{ m_Position.hash() }
			{
				m_pContext->clearMovegenLists();
			}
			stack(boardType& position, historyType& history, contextType* pContext) noexcept :
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
				m_LastNormalPass{ 0 },
				m_LastNormalStage{ 0 },
				m_CurrentTacticalPass{ 0 },
				m_CurrentTacticalMove{ 0 },
				m_CurrentTacticalStage{ 0 },
				m_LastTacticalPass{ 0 },
				m_LastTacticalStage{ 0 },
				m_CurrentCriticalPass{ 0 },
				m_CurrentCriticalMove{ 0 },
				m_CurrentCriticalStage{ 0 },
				m_LastCriticalPass{ 0 },
				m_LastCriticalStage{ 0 },
				m_MoveData(),
				m_IsNullmove{ true },
				m_Hash{ m_Position.hash() }
			{
				m_pContext->clearMovegenLists();
				PYGMALION_ASSERT(position.movingPlayer() == m_MovingPlayer);
			}
			constexpr contextType* getContext() const noexcept
			{
				return m_pContext;
			}
			constexpr const boardType& position() const noexcept
			{
				return m_Position;
			}
			playerType movingPlayer() const noexcept
			{
				return m_MovingPlayer;
			}
			playerType nextPlayer() const noexcept
			{
				return m_NextPlayer;
			}
			playerType previousPlayer() const noexcept
			{
				return m_MoveData.movingPlayer();
			}
			~stack() noexcept
			{
				if (!m_IsNullmove)
					motorType::move().undoMove(m_Position, m_MoveData);
			}
			std::string moveToString(const movebitsType moveBits, const size_t depth) const
			{
				return generatorType::moveToString(*static_cast<const typename generatorType::template stackType<PLAYER>*>(this), moveBits, depth);
			}
			constexpr bool occurs(const boardType& position, const int times, const int start, const int frequency) const noexcept
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
		constexpr static bool isMoveTactical(const stackType& stack, const movebitsType mv) noexcept
		{
			return generatorType::isMoveTactical_Implementation(stack, mv);
		}
		template<typename stackType>
		constexpr static bool isPositionCritical(const stackType& stack) noexcept
		{
			return generatorType::isPositionCritical_Implementation(stack);
		}
		constexpr static size_t countMoveBuckets() noexcept
		{
			return generatorType::countMoveBuckets_Implementation();
		}
		constexpr static size_t moveBucket(const boardType& position, const movebitsType mv) noexcept
		{
			return generatorType::moveBucket_Implementation(position, mv);
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
		constexpr static bool isMoveCritical(const stackType& stack, const movebitsType moveBits) noexcept
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
	};
}