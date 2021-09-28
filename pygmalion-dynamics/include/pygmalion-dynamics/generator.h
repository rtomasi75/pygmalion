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
		using passType = uint_t<arrayhelper::requiredUnsignedBits(std::max(countPasses, countTacticalPasses) + 1), false>;
		using passlistType = list<passType, countMaxGeneratedMoves>;
		class movegenFeedback
		{
		private:
			class feedback
			{
			private:
				std::array <std::uint64_t, countPasses> m_MoveCounter;
				std::array <scoreType, countPasses> m_ScoreCounter;
				std::array <std::uint64_t, countCriticalEvasionPasses> m_CriticalEvasionMoveCounter;
				std::array <scoreType, countCriticalEvasionPasses> m_CriticalEvasionScoreCounter;
				std::array <std::uint64_t, countTacticalPasses> m_TacticalMoveCounter;
				std::array <scoreType, countTacticalPasses> m_TacticalScoreCounter;
				std::array <std::uint64_t, countTacticalCriticalEvasionPasses> m_TacticalCriticalEvasionMoveCounter;
				std::array <scoreType, countTacticalCriticalEvasionPasses> m_TacticalCriticalEvasionScoreCounter;
				std::array <std::uint64_t, countCriticalPasses> m_CriticalMoveCounter;
				std::array <scoreType, countCriticalPasses> m_CriticalScoreCounter;
				std::array <passType, countPasses> m_Index;
				std::array <passType, countCriticalEvasionPasses> m_CriticalEvasionIndex;
				std::array <passType, countTacticalPasses> m_TacticalIndex;
				std::array <passType, countTacticalCriticalEvasionPasses> m_TacticalCriticalEvasionIndex;
				std::array <passType, countCriticalPasses> m_CriticalIndex;
				constexpr static bool USE_SCORE{ true };
			public:
				constexpr void sortIndices() noexcept
				{
					if constexpr (!USE_SCORE)
					{
						sort<passType, std::uint64_t>::sortValues(m_Index.data(), m_MoveCounter.data(), countPasses);
						sort<passType, std::uint64_t>::sortValues(m_CriticalEvasionIndex.data(), m_CriticalEvasionMoveCounter.data(), countCriticalEvasionPasses);
						sort<passType, std::uint64_t>::sortValues(m_TacticalIndex.data(), m_TacticalMoveCounter.data(), countTacticalPasses);
						sort<passType, std::uint64_t>::sortValues(m_TacticalCriticalEvasionIndex.data(), m_TacticalCriticalEvasionMoveCounter.data(), countTacticalCriticalEvasionPasses);
						sort<passType, std::uint64_t>::sortValues(m_CriticalIndex.data(), m_CriticalMoveCounter.data(), countCriticalPasses);
					}
					else
					{
						std::array <scoreType, countPasses> scores{ arrayhelper::generate<countPasses,scoreType>([this](const size_t pass)
							{
								return this->score(pass);
							})
						};
						std::array <scoreType, countCriticalEvasionPasses> criticalEvasionScores{ arrayhelper::generate<countCriticalEvasionPasses,scoreType>([this](const size_t pass)
							{
								return this->criticalEvasionScore(pass);
							})
						};
						std::array <scoreType, countTacticalPasses> tacticalScores{ arrayhelper::generate<countTacticalPasses,scoreType>([this](const size_t pass)
							{
								return this->tacticalScore(pass);
							})
						};
						std::array <scoreType, countTacticalCriticalEvasionPasses> tacticalCriticalEvasionScores{ arrayhelper::generate<countTacticalCriticalEvasionPasses,scoreType>([this](const size_t pass)
							{
								return this->tacticalCriticalEvasionScore(pass);
							})
						};
						std::array <scoreType, countCriticalPasses> criticalScores{ arrayhelper::generate<countCriticalPasses,scoreType>([this](const size_t pass)
							{
								return this->criticalScore(pass);
							})
						};
						sort<passType, scoreType>::sortValues(m_Index.data(), scores.data(), countPasses);
						sort<passType, scoreType>::sortValues(m_CriticalEvasionIndex.data(), criticalEvasionScores.data(), countCriticalEvasionPasses);
						sort<passType, scoreType>::sortValues(m_TacticalIndex.data(), tacticalScores.data(), countTacticalPasses);
						sort<passType, scoreType>::sortValues(m_TacticalCriticalEvasionIndex.data(), tacticalCriticalEvasionScores.data(), countTacticalCriticalEvasionPasses);
						sort<passType, scoreType>::sortValues(m_CriticalIndex.data(), criticalScores.data(), countCriticalPasses);
					}
				}
				constexpr passType index(const passType& pass) const noexcept
				{
					assert(pass < countPasses);
					return m_Index[static_cast<size_t>(pass)];
				}
				constexpr passType criticalEvasionIndex(const passType& pass) const noexcept
				{
					assert(pass < countCriticalEvasionPasses);
					return m_CriticalEvasionIndex[static_cast<size_t>(pass)];
				}
				constexpr passType moveIndex(const passType& pass) const noexcept
				{
					assert(pass < countPasses);
					if constexpr (!USE_SCORE)
						return static_cast<size_t>(pass);
					else
						return m_Index[static_cast<size_t>(pass)];
				}
				constexpr passType moveCriticalEvasionIndex(const passType& pass) const noexcept
				{
					assert(pass < countCriticalEvasionPasses);
					if constexpr (!USE_SCORE)
						return static_cast<size_t>(pass);
					else
						return m_CriticalEvasionIndex[static_cast<size_t>(pass)];
				}
				constexpr passType scoreIndex(const passType& pass) const noexcept
				{
					assert(pass < countPasses);
					return m_Index[static_cast<size_t>(pass)];
				}
				constexpr passType criticalEvasionScoreIndex(const passType& pass) const noexcept
				{
					assert(pass < countCriticalEvasionPasses);
					return m_CriticalEvasionIndex[static_cast<size_t>(pass)];
				}
				constexpr passType tacticalIndex(const passType& pass) const noexcept
				{
					assert(pass < countTacticalPasses);
					return m_TacticalIndex[static_cast<size_t>(pass)];
				}
				constexpr passType tacticalCriticalEvasionIndex(const passType& pass) const noexcept
				{
					assert(pass < countTacticalCriticalEvasionPasses);
					return m_TacticalCriticalEvasionIndex[static_cast<size_t>(pass)];
				}
				constexpr passType tacticalMoveIndex(const passType& pass) const noexcept
				{
					assert(pass < countTacticalPasses);
					if constexpr (!USE_SCORE)
						return static_cast<size_t>(pass);
					else
						return m_TacticalIndex[static_cast<size_t>(pass)];
				}
				constexpr passType tacticalCriticalEvasionMoveIndex(const passType& pass) const noexcept
				{
					assert(pass < countTacticalCriticalEvasionPasses);
					if constexpr (!USE_SCORE)
						return static_cast<size_t>(pass);
					else
						return m_TacticalCriticalEvasionIndex[static_cast<size_t>(pass)];
				}
				constexpr passType tacticalCriticalEvasionScoreIndex(const passType& pass) const noexcept
				{
					assert(pass < countTacticalCriticalEvasionPasses);
					return m_TacticalCriticalEvasionIndex[static_cast<size_t>(pass)];
				}
				constexpr passType tacticalScoreIndex(const passType& pass) const noexcept
				{
					assert(pass < countTacticalPasses);
					return m_TacticalIndex[static_cast<size_t>(pass)];
				}
				constexpr passType criticalIndex(const passType& pass) const noexcept
				{
					assert(pass < countCriticalPasses);
					return m_CriticalIndex[static_cast<size_t>(pass)];
				}
				constexpr passType criticalMoveIndex(const passType& pass) const noexcept
				{
					assert(pass < countCriticalPasses);
					if constexpr (!USE_SCORE)
						return static_cast<size_t>(pass);
					else
						return m_CriticalIndex[static_cast<size_t>(pass)];
				}
				constexpr passType criticalEvasionMoveIndex(const passType& pass) const noexcept
				{
					assert(pass < countCriticalEvasionPasses);
					if constexpr (!USE_SCORE)
						return static_cast<size_t>(pass);
					else
						return m_CriticalEvasionIndex[static_cast<size_t>(pass)];
				}
				constexpr passType criticalScoreIndex(const passType& pass) const noexcept
				{
					assert(pass < countCriticalPasses);
					return m_CriticalIndex[static_cast<size_t>(pass)];
				}
				constexpr feedback() noexcept :
					m_MoveCounter{ arrayhelper::make<countPasses,std::uint64_t>(0) },
					m_CriticalEvasionMoveCounter{ arrayhelper::make<countCriticalEvasionPasses,std::uint64_t>(0) },
					m_TacticalMoveCounter{ arrayhelper::make<countTacticalPasses, std::uint64_t>(0) },
					m_TacticalCriticalEvasionMoveCounter{ arrayhelper::make<countTacticalCriticalEvasionPasses, std::uint64_t>(0) },
					m_CriticalMoveCounter{ arrayhelper::make<countCriticalPasses, std::uint64_t>(0) },
					m_ScoreCounter{ arrayhelper::make<countPasses,scoreType>(scoreType::zero()) },
					m_CriticalEvasionScoreCounter{ arrayhelper::make<countCriticalEvasionPasses,scoreType>(scoreType::zero()) },
					m_TacticalScoreCounter{ arrayhelper::make<countTacticalPasses, scoreType>(scoreType::zero()) },
					m_TacticalCriticalEvasionScoreCounter{ arrayhelper::make<countTacticalCriticalEvasionPasses, scoreType>(scoreType::zero()) },
					m_CriticalScoreCounter{ arrayhelper::make<countCriticalPasses, scoreType>(scoreType::zero()) },
					m_Index{ arrayhelper::generate<countPasses,passType>([](const size_t index) {return index; }) },
					m_CriticalEvasionIndex{ arrayhelper::generate<countCriticalEvasionPasses,passType>([](const size_t index) {return index; }) },
					m_TacticalIndex{ arrayhelper::generate<countTacticalPasses,passType>([](const size_t index) {return index; }) },
					m_TacticalCriticalEvasionIndex{ arrayhelper::generate<countTacticalCriticalEvasionPasses,passType>([](const size_t index) {return index; }) },
					m_CriticalIndex{ arrayhelper::generate<countCriticalPasses,passType>([](const size_t index) {return index; }) }
				{

				}
				constexpr scoreType score(const passType& pass) const noexcept
				{
					const size_t indexMove{ static_cast<size_t>(moveIndex(pass)) };
					const size_t indexScore{ static_cast<size_t>(scoreIndex(pass)) };
					if (m_MoveCounter[indexMove] == 0)
						return scoreType::minimum();
					if (m_ScoreCounter[indexScore].isOpen())
						return m_ScoreCounter[indexScore] / static_cast<typename scoreType::valueType>(m_MoveCounter[indexMove]);
					else
						return m_ScoreCounter[indexScore];
				}
				constexpr scoreType criticalEvasionScore(const passType& pass) const noexcept
				{
					const size_t indexMove{ static_cast<size_t>(criticalEvasionMoveIndex(pass)) };
					const size_t indexScore{ static_cast<size_t>(criticalEvasionScoreIndex(pass)) };
					if (m_CriticalEvasionMoveCounter[indexMove] == 0)
						return scoreType::minimum();
					if (m_CriticalEvasionScoreCounter[indexScore].isOpen())
						return m_CriticalEvasionScoreCounter[indexScore] / static_cast<typename scoreType::valueType>(m_CriticalEvasionMoveCounter[indexMove]);
					else
						return m_CriticalEvasionScoreCounter[indexScore];
				}
				constexpr scoreType tacticalScore(const passType& pass) const noexcept
				{
					const size_t indexMove{ static_cast<size_t>(tacticalMoveIndex(pass)) };
					const size_t indexScore{ static_cast<size_t>(tacticalScoreIndex(pass)) };
					if (m_TacticalMoveCounter[indexMove] == 0)
						return scoreType::minimum();
					if (m_TacticalScoreCounter[indexScore].isOpen())
						return m_TacticalScoreCounter[indexScore] / static_cast<typename scoreType::valueType>(m_TacticalMoveCounter[indexMove]);
					else
						return m_TacticalScoreCounter[indexScore];
				}
				constexpr scoreType tacticalCriticalEvasionScore(const passType& pass) const noexcept
				{
					const size_t indexMove{ static_cast<size_t>(tacticalCriticalEvasionMoveIndex(pass)) };
					const size_t indexScore{ static_cast<size_t>(tacticalCriticalEvasionScoreIndex(pass)) };
					if (m_TacticalCriticalEvasionMoveCounter[indexMove] == 0)
						return scoreType::minimum();
					if (m_TacticalCriticalEvasionScoreCounter[indexScore].isOpen())
						return m_TacticalCriticalEvasionScoreCounter[indexScore] / static_cast<typename scoreType::valueType>(m_TacticalCriticalEvasionMoveCounter[indexMove]);
					else
						return m_TacticalCriticalEvasionScoreCounter[indexScore];
				}
				constexpr scoreType criticalScore(const passType& pass) const noexcept
				{
					const size_t indexMove{ static_cast<size_t>(criticalMoveIndex(pass)) };
					const size_t indexScore{ static_cast<size_t>(criticalScoreIndex(pass)) };
					if (m_CriticalMoveCounter[indexMove] == 0)
						return scoreType::minimum();
					if (m_CriticalScoreCounter[indexScore].isOpen())
						return m_CriticalScoreCounter[indexScore] / static_cast<typename scoreType::valueType>(m_CriticalMoveCounter[indexMove]);
					else
						return m_CriticalScoreCounter[indexScore];
				}
				constexpr const std::uint64_t& counter(const passType& pass) const noexcept
				{
					return m_MoveCounter[static_cast<size_t>(moveIndex(pass))];
				}
				constexpr const std::uint64_t& criticalEvasionCounter(const passType& pass) const noexcept
				{
					return m_CriticalEvasionMoveCounter[static_cast<size_t>(criticalEvasionMoveIndex(pass))];
				}
				constexpr const std::uint64_t& tacticalCounter(const passType& pass) const noexcept
				{
					return m_TacticalMoveCounter[static_cast<size_t>(tacticalMoveIndex(pass))];
				}
				constexpr const std::uint64_t& tacticalCriticalEvasionCounter(const passType& pass) const noexcept
				{
					return m_TacticalCriticalEvasionMoveCounter[static_cast<size_t>(tacticalCriticalEvasionMoveIndex(pass))];
				}
				constexpr const std::uint64_t& criticalCounter(const passType& pass) const noexcept
				{
					return m_CriticalMoveCounter[static_cast<size_t>(criticalMoveIndex(pass))];
				}
				constexpr void incrementMove(const passType& pass, const scoreType& score) noexcept
				{
					const size_t indexMove{ static_cast<size_t>(moveIndex(pass)) };
					const size_t indexScore{ static_cast<size_t>(scoreIndex(pass)) };
					if (score.isOpen())
					{
						if (m_ScoreCounter[indexScore].isOpen())
							m_ScoreCounter[indexScore] += score;
						else
							m_ScoreCounter[indexScore] = scoreType::max(score, m_ScoreCounter[indexScore]);
					}
					else
						m_ScoreCounter[indexScore] = scoreType::max(score, m_ScoreCounter[indexScore]);
					m_MoveCounter[indexMove]++;
				}
				constexpr void incrementCriticalEvasionMove(const passType& pass, const scoreType& score) noexcept
				{
					const size_t indexMove{ static_cast<size_t>(criticalEvasionMoveIndex(pass)) };
					const size_t indexScore{ static_cast<size_t>(criticalEvasionScoreIndex(pass)) };
					if (score.isOpen())
					{
						if (m_CriticalEvasionScoreCounter[indexScore].isOpen())
							m_CriticalEvasionScoreCounter[indexScore] += score;
						else
							m_CriticalEvasionScoreCounter[indexScore] = scoreType::max(score, m_CriticalEvasionScoreCounter[indexScore]);
					}
					else
						m_CriticalEvasionScoreCounter[indexScore] = scoreType::max(score, m_CriticalEvasionScoreCounter[indexScore]);
					m_CriticalEvasionMoveCounter[indexMove]++;
				}
				constexpr void incrementTacticalMove(const passType& pass, const scoreType& score) noexcept
				{
					const size_t indexMove{ static_cast<size_t>(tacticalMoveIndex(pass)) };
					const size_t indexScore{ static_cast<size_t>(tacticalScoreIndex(pass)) };
					if (score.isOpen())
					{
						if (m_TacticalScoreCounter[indexScore].isOpen())
							m_TacticalScoreCounter[indexScore] += score;
						else
							m_TacticalScoreCounter[indexScore] = scoreType::max(score, m_TacticalScoreCounter[indexScore]);
					}
					else
						m_TacticalScoreCounter[indexScore] = scoreType::max(score, m_TacticalScoreCounter[indexScore]);
					m_TacticalMoveCounter[indexMove]++;
				}
				constexpr void incrementTacticalCriticalEvasionMove(const passType& pass, const scoreType& score) noexcept
				{
					const size_t indexMove{ static_cast<size_t>(tacticalCriticalEvasionMoveIndex(pass)) };
					const size_t indexScore{ static_cast<size_t>(tacticalCriticalEvasionScoreIndex(pass)) };
					if (score.isOpen())
					{
						if (m_TacticalCriticalEvasionScoreCounter[indexScore].isOpen())
							m_TacticalCriticalEvasionScoreCounter[indexScore] += score;
						else
							m_TacticalCriticalEvasionScoreCounter[indexScore] = scoreType::max(score, m_TacticalCriticalEvasionScoreCounter[indexScore]);
					}
					else
						m_TacticalCriticalEvasionScoreCounter[indexScore] = scoreType::max(score, m_TacticalCriticalEvasionScoreCounter[indexScore]);
					m_TacticalCriticalEvasionMoveCounter[indexMove]++;
				}
				constexpr void incrementCriticalMove(const passType& pass, const scoreType& score) noexcept
				{
					const size_t indexMove{ static_cast<size_t>(criticalMoveIndex(pass)) };
					const size_t indexScore{ static_cast<size_t>(criticalScoreIndex(pass)) };
					if (score.isOpen())
					{
						if (m_CriticalScoreCounter[indexScore].isOpen())
							m_CriticalScoreCounter[indexScore] += score;
						else
							m_CriticalScoreCounter[indexScore] = scoreType::max(score, m_CriticalScoreCounter[indexScore]);
					}
					else
						m_CriticalScoreCounter[indexScore] = scoreType::max(score, m_CriticalScoreCounter[indexScore]);
					m_CriticalMoveCounter[indexMove]++;
				}
				constexpr void reset() noexcept
				{
					for (size_t i = 0; i < generatorType::countCriticalEvasionPasses; i++)
					{
						m_CriticalEvasionMoveCounter[i] = 0;
						m_CriticalEvasionScoreCounter[i] = scoreType::zero();
						m_CriticalEvasionIndex[i] = i;
					}
					for (size_t i = 0; i < generatorType::countPasses; i++)
					{
						m_MoveCounter[i] = 0;
						m_ScoreCounter[i] = scoreType::zero();
						m_Index[i] = i;
					}
					for (size_t i = 0; i < generatorType::countTacticalPasses; i++)
					{
						m_TacticalMoveCounter[i] = 0;
						m_TacticalScoreCounter[i] = scoreType::zero();
						m_TacticalIndex[i] = i;
					}
					for (size_t i = 0; i < generatorType::countTacticalCriticalEvasionPasses; i++)
					{
						m_TacticalCriticalEvasionMoveCounter[i] = 0;
						m_TacticalCriticalEvasionScoreCounter[i] = scoreType::zero();
						m_TacticalCriticalEvasionIndex[i] = i;
					}
					for (size_t i = 0; i < generatorType::countCriticalPasses; i++)
					{
						m_CriticalMoveCounter[i] = 0;
						m_CriticalScoreCounter[i] = scoreType::zero();
						m_CriticalIndex[i] = i;
					}
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
			constexpr const std::uint64_t& counter(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].counter(pass);
			}
			constexpr const std::uint64_t& criticalEvasionCounter(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countCriticalEvasionPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].criticalEvasionCounter(pass);
			}
			constexpr scoreType score(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				if (depth >= 2)
					return (m_Feedback[depth - 2].score(pass) + (3 * m_Feedback[depth].score(pass))) / 4;
				else
					return m_Feedback[depth].score(pass);
			}
			constexpr scoreType criticalEvasionScore(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countCriticalEvasionPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				if (depth >= 2)
					return (m_Feedback[depth - 2].criticalEvasionScore(pass) + (3 * m_Feedback[depth].criticalEvasionScore(pass))) / 4;
				else
					return m_Feedback[depth].criticalEvasionScore(pass);
			}
			constexpr const std::uint64_t& tacticalCounter(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countTacticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(std::move(feedback()));
				}
				return m_Feedback[depth].tacticalCounter(pass);
			}
			constexpr const std::uint64_t& tacticalCriticalEvasionCounter(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countTacticalCriticalEvasionPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(std::move(feedback()));
				}
				return m_Feedback[depth].tacticalCriticalEvasionCounter(pass);
			}
			constexpr scoreType tacticalScore(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countTacticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].tacticalScore(pass);
			}
			constexpr scoreType tacticalCriticalEvasionScore(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countTacticalCriticalEvasionPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].tacticalCriticalEvasionScore(pass);
			}
			constexpr const std::uint64_t& criticalCounter(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countCriticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(std::move(feedback()));
				}
				return m_Feedback[depth].criticalCounter(pass);
			}
			constexpr scoreType criticalScore(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countCriticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].criticalScore(pass);
			}
			constexpr void cutMove(const passType& pass, const size_t depth, const scoreType& score) noexcept
			{
				assert(pass < countPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementMove(pass, score);
			}
			constexpr void criticalEvasionCutMove(const passType& pass, const size_t depth, const scoreType& score) noexcept
			{
				assert(pass < countCriticalEvasionPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementCriticalEvasionMove(pass, score);
			}
			constexpr void allMove(const passType& pass, const size_t depth, const scoreType& score) noexcept
			{
				assert(pass < countPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementMove(pass, score);
			}
			constexpr void criticalEvasionAllMove(const passType& pass, const size_t depth, const scoreType& score) noexcept
			{
				assert(pass < countPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementCriticalEvasionMove(pass, score);
			}
			constexpr void tacticalCutMove(const passType& tacticalPass, const size_t depth, const scoreType& score) noexcept
			{
				assert(tacticalPass < countTacticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementTacticalMove(tacticalPass, score);
			}
			constexpr void tacticalCriticalEvasionCutMove(const passType& tacticalCriticalEvasionPass, const size_t depth, const scoreType& score) noexcept
			{
				assert(tacticalCriticalEvasionPass < countTacticalCriticalEvasionPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementTacticalCriticalEvasionMove(tacticalCriticalEvasionPass, score);
			}
			constexpr void tacticalAllMove(const passType& tacticalPass, const size_t depth, const scoreType& score) noexcept
			{
				assert(tacticalPass < countTacticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementTacticalMove(tacticalPass, score);
			}
			constexpr void tacticalCriticalEvasionAllMove(const passType& tacticalCriticalEvasionPass, const size_t depth, const scoreType& score) noexcept
			{
				assert(tacticalCriticalEvasionPass < countTacticalCriticalEvasionPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementTacticalCriticalEvasionMove(tacticalCriticalEvasionPass, score);
			}
			constexpr void criticalCutMove(const passType& criticalPass, const size_t depth, const scoreType& score) noexcept
			{
				assert(criticalPass < countCriticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementCriticalMove(criticalPass, score);
			}
			constexpr void criticalAllMove(const passType& criticalPass, const size_t depth, const scoreType& score) noexcept
			{
				assert(criticalPass < countCriticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementCriticalMove(criticalPass, score);
			}
			constexpr void reset() noexcept
			{
				m_Feedback.clear();
			}
			constexpr passType index(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].index(pass);
			}
			constexpr passType criticalEvasionIndex(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countCriticalEvasionPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].criticalEvasionIndex(pass);
			}
			constexpr passType tacticalIndex(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countTacticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].tacticalIndex(pass);
			}
			constexpr passType tacticalCriticalEvasionIndex(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countTacticalCriticalEvasionPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].tacticalCriticalEvasionIndex(pass);
			}
			constexpr passType criticalIndex(const passType& pass, const size_t depth) const noexcept
			{
				assert(pass < countCriticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].criticalIndex(pass);
			}
		};
		class stack :
			public DESCRIPTOR_DYNAMICS
		{
		public:
			using generatorType = INSTANCE;
			using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include "include_dynamics.h"
		private:
			const stack* m_pParent;
			mutable movelistType m_Moves;
			mutable list<scoreType, countMaxGeneratedMoves> m_Scores;
			mutable passlistType m_Passes;
			mutable movelistType m_TacticalMoves;
			mutable list<scoreType, countMaxGeneratedMoves> m_TacticalScores;
			mutable passlistType m_TacticalPasses;
			mutable movelistType m_CriticalMoves;
			mutable list<scoreType, countMaxGeneratedMoves> m_CriticalScores;
			mutable passlistType m_CriticalPasses;
			boardType& m_Position;
			historyType& m_History;
			const movedataType m_MoveData;
			mutable passType m_CurrentPass;
			mutable passType m_LastPass;
			mutable passType m_CurrentTacticalPass;
			mutable passType m_LastTacticalPass;
			mutable passType m_CurrentCriticalPass;
			mutable passType m_LastCriticalPass;
			mutable indexType m_CurrentMove;
			mutable indexType m_CurrentTacticalMove;
			mutable indexType m_CurrentCriticalMove;
			mutable indexType m_CurrentLegalMove;
			mutable signatureType m_Signature;
			const playerType m_MovingPlayer;
			const playerType m_NextPlayer;
			mutable bool m_HasLegalMove;
			mutable bool m_HasLegalMoveValid;
			mutable bool m_SignatureValid;
			mutable bool m_IsPositionCriticalValid{ false };
			mutable bool m_IsPositionCritical{ false };
			const bool m_IsNullmove;
			const hashType m_Hash;
			bool computeHasLegalMove(const size_t depth, movegenFeedback& feedback) const
			{
				bool allMovesGenerated{ false };
				if (isPositionCritical())
				{
					while (!allMovesGenerated)
					{
						if (m_CurrentLegalMove >= m_Moves.length())
						{
							if (m_CurrentPass >= countCriticalEvasionPasses)
							{
								allMovesGenerated = true;
								return false;
							}
							generatorType::generateCriticalEvasionMoves(*static_cast<const typename generatorType::stackType*>(this), m_Moves, feedback.index(m_CurrentPass, depth));
							while (m_Passes.length() < m_Moves.length())
								m_Passes.add(m_CurrentPass);
							++m_CurrentPass;
						}
						while (m_CurrentLegalMove < m_Moves.length())
						{
							if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::stackType*>(this), m_Moves[m_CurrentLegalMove]))
								return true;
							++m_CurrentLegalMove;
						}
					}
				}
				else
				{
					while (!allMovesGenerated)
					{
						if (m_CurrentLegalMove >= m_Moves.length())
						{
							if (m_CurrentPass >= countPasses)
							{
								allMovesGenerated = true;
								return false;
							}
							generatorType::generateMoves(*static_cast<const typename generatorType::stackType*>(this), m_Moves, feedback.index(m_CurrentPass, depth));
							while (m_Passes.length() < m_Moves.length())
								m_Passes.add(m_CurrentPass);
							++m_CurrentPass;
						}
						while (m_CurrentLegalMove < m_Moves.length())
						{
							if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::stackType*>(this), m_Moves[m_CurrentLegalMove]))
								return true;
							++m_CurrentLegalMove;
						}
					}
				}
				return false;
			}
		public:
			constexpr bool isPositionCritical() const noexcept
			{
				if (!m_IsPositionCriticalValid)
				{
					m_IsPositionCritical = generatorType::isPositionCritical(*static_cast<const typename generatorType::stackType*>(this));
					m_IsPositionCriticalValid = true;
				}
				return m_IsPositionCritical;
			}
			constexpr void allMove(movegenFeedback& feedback, const size_t depth, const scoreType& score) const noexcept
			{
				if (isPositionCritical())
					feedback.criticalEvasionAllMove(m_LastPass, depth, score);
				else
					feedback.allMove(m_LastPass, depth, score);
			}
			constexpr void criticalAllMove(movegenFeedback& feedback, const size_t depth, const scoreType& score) const noexcept
			{
				feedback.criticalAllMove(m_LastPass, depth, score);
			}
			constexpr void tacticalAllMove(movegenFeedback& feedback, const size_t depth, const scoreType& score) const noexcept
			{
				if (isPositionCritical())
					feedback.tacticalCriticalEvasionAllMove(m_LastTacticalPass, depth, score);
				else
					feedback.tacticalAllMove(m_LastTacticalPass, depth, score);
			}
			constexpr void cutMove(movegenFeedback& feedback, const size_t depth, const scoreType& score) const noexcept
			{
				if (isPositionCritical())
					feedback.criticalEvasionCutMove(m_LastPass, depth, score);
				else
					feedback.cutMove(m_LastPass, depth, score);
			}
			constexpr void criticalCutMove(movegenFeedback& feedback, const size_t depth, const scoreType& score) const noexcept
			{
				feedback.criticalCutMove(m_LastPass, depth, score);
			}
			constexpr void tacticalCutMove(movegenFeedback& feedback, const size_t depth, const scoreType& score) const noexcept
			{
				if (isPositionCritical())
					feedback.tacticalCriticalEvasionCutMove(m_LastTacticalPass, depth, score);
				else
					feedback.tacticalCutMove(m_LastTacticalPass, depth, score);
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
			signatureType signature() const
			{
				if (!m_SignatureValid)
				{
					m_Signature = this->position().signature();
					m_SignatureValid = true;
				}
				return m_Signature;
			}
			bool isMoveLegal(const movebitsType& moveBits) const noexcept
			{
				return generatorType::isMoveLegal(*static_cast<const typename generatorType::stackType*>(this), moveBits);
			}
			bool nextMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback) const noexcept
			{
				bool allMovesGenerated{ false };
				if (isPositionCritical())
				{
					while (!allMovesGenerated)
					{
						if (m_CurrentMove >= m_Moves.length())
						{
							if (m_CurrentPass >= countCriticalEvasionPasses)
							{
								allMovesGenerated = true;
								return false;
							}
							generatorType::generateCriticalEvasionMoves(*static_cast<const typename generatorType::stackType*>(this), m_Moves, feedback.criticalEvasionIndex(m_CurrentPass, depth));
							while (m_Passes.length() < m_Moves.length())
								m_Passes.add(m_CurrentPass);
							++m_CurrentPass;
						}
						while (m_CurrentMove < m_Moves.length())
						{
							moveBits = m_Moves[m_CurrentMove];
							++m_CurrentMove;
							if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::stackType*>(this), moveBits))
							{
								m_LastPass = m_Passes[m_CurrentMove - 1];
								return true;
							}
						}
					}
				}
				else
				{
					while (!allMovesGenerated)
					{
						if (m_CurrentMove >= m_Moves.length())
						{
							if (m_CurrentPass >= countPasses)
							{
								allMovesGenerated = true;
								return false;
							}
							generatorType::generateMoves(*static_cast<const typename generatorType::stackType*>(this), m_Moves, feedback.index(m_CurrentPass, depth));
							while (m_Passes.length() < m_Moves.length())
								m_Passes.add(m_CurrentPass);
							++m_CurrentPass;
						}
						while (m_CurrentMove < m_Moves.length())
						{
							moveBits = m_Moves[m_CurrentMove];
							++m_CurrentMove;
							if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::stackType*>(this), moveBits))
							{
								m_LastPass = m_Passes[m_CurrentMove - 1];
								return true;
							}
						}
					}
				}
				return false;
			}
			template<typename LAMBDA>
			bool nextMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback, const LAMBDA& lambda) const noexcept
			{
				bool allMovesGenerated{ false };
				if (isPositionCritical())
				{
					while (!allMovesGenerated)
					{
						if (m_CurrentMove >= m_Moves.length())
						{
							if (m_CurrentPass >= countCriticalEvasionPasses)
							{
								allMovesGenerated = true;
								return false;
							}
							generatorType::generateCriticalEvasionMoves(*static_cast<const typename generatorType::stackType*>(this), m_Moves, feedback.criticalEvasionIndex(m_CurrentPass, depth));
							const auto start{ m_Passes.length() };
							while (m_Passes.length() < m_Moves.length())
							{
								m_Scores.add(lambda(m_Moves[m_Passes.length()]));
								m_Passes.add(m_CurrentPass);
							}
							sort<movebitsType, scoreType>::sortValues(m_Moves.ptr() + static_cast<size_t>(start), m_Scores.ptr() + static_cast<size_t>(start), static_cast<size_t>(m_Moves.length() - start));
							++m_CurrentPass;
						}
						while (m_CurrentMove < m_Moves.length())
						{
							moveBits = m_Moves[m_CurrentMove];
							++m_CurrentMove;
							if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::stackType*>(this), moveBits))
							{
								m_LastPass = m_Passes[m_CurrentMove - 1];
								return true;
							}
						}
					}
				}
				else
				{
					while (!allMovesGenerated)
					{
						if (m_CurrentMove >= m_Moves.length())
						{
							if (m_CurrentPass >= countPasses)
							{
								allMovesGenerated = true;
								return false;
							}
							generatorType::generateMoves(*static_cast<const typename generatorType::stackType*>(this), m_Moves, feedback.index(m_CurrentPass, depth));
							const auto start{ m_Passes.length() };
							while (m_Passes.length() < m_Moves.length())
							{
								m_Scores.add(lambda(m_Moves[m_Passes.length()]));
								m_Passes.add(m_CurrentPass);
							}
							sort<movebitsType, scoreType>::sortValues(m_Moves.ptr() + static_cast<size_t>(start), m_Scores.ptr() + static_cast<size_t>(start), static_cast<size_t>(m_Moves.length() - start));
							++m_CurrentPass;
						}
						while (m_CurrentMove < m_Moves.length())
						{
							moveBits = m_Moves[m_CurrentMove];
							++m_CurrentMove;
							if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::stackType*>(this), moveBits))
							{
								m_LastPass = m_Passes[m_CurrentMove - 1];
								return true;
							}
						}
					}
				}
				return false;
			}
			bool nextTacticalMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback) const noexcept
			{
				bool allMovesGenerated{ false };
				if (isPositionCritical())
				{
					while (!allMovesGenerated)
					{
						if (m_CurrentTacticalMove >= m_TacticalMoves.length())
						{
							if (m_CurrentTacticalPass >= countTacticalCriticalEvasionPasses)
							{
								allMovesGenerated = true;
								return false;
							}
							generatorType::generateTacticalCriticalEvasionMoves(*static_cast<const typename generatorType::stackType*>(this), m_TacticalMoves, feedback.tacticalCriticalEvasionIndex(m_CurrentTacticalPass, depth));
							const auto start{ m_TacticalPasses.length() };
							while (m_TacticalPasses.length() < m_TacticalMoves.length())
								m_TacticalPasses.add(m_CurrentTacticalPass);
							++m_CurrentTacticalPass;
						}
						while (m_CurrentTacticalMove < m_TacticalMoves.length())
						{
							moveBits = m_TacticalMoves[m_CurrentTacticalMove];
							++m_CurrentTacticalMove;
							if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::stackType*>(this), moveBits))
							{
								m_LastTacticalPass = m_TacticalPasses[m_CurrentTacticalMove - 1];
								return true;
							}
						}
					}
				}
				else
				{
					while (!allMovesGenerated)
					{
						if (m_CurrentTacticalMove >= m_TacticalMoves.length())
						{
							if (m_CurrentTacticalPass >= countTacticalPasses)
							{
								allMovesGenerated = true;
								return false;
							}
							generatorType::generateTacticalMoves(*static_cast<const typename generatorType::stackType*>(this), m_TacticalMoves, feedback.tacticalIndex(m_CurrentTacticalPass, depth));
							const auto start{ m_TacticalPasses.length() };
							while (m_TacticalPasses.length() < m_TacticalMoves.length())
								m_TacticalPasses.add(m_CurrentTacticalPass);
							++m_CurrentTacticalPass;
						}
						while (m_CurrentTacticalMove < m_TacticalMoves.length())
						{
							moveBits = m_TacticalMoves[m_CurrentTacticalMove];
							++m_CurrentTacticalMove;
							if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::stackType*>(this), moveBits))
							{
								m_LastTacticalPass = m_TacticalPasses[m_CurrentTacticalMove - 1];
								return true;
							}
						}
					}
				}
				return false;
			}
			template<typename LAMBDA>
			bool nextTacticalMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback, const LAMBDA& lambda) const noexcept
			{
				bool allMovesGenerated{ false };
				if (isPositionCritical())
				{
					while (!allMovesGenerated)
					{
						if (m_CurrentTacticalMove >= m_TacticalMoves.length())
						{
							if (m_CurrentTacticalPass >= countTacticalCriticalEvasionPasses)
							{
								allMovesGenerated = true;
								return false;
							}
							generatorType::generateTacticalCriticalEvasionMoves(*static_cast<const typename generatorType::stackType*>(this), m_TacticalMoves, feedback.tacticalCriticalEvasionIndex(m_CurrentTacticalPass, depth));
							const auto start{ m_TacticalPasses.length() };
							while (m_TacticalPasses.length() < m_TacticalMoves.length())
							{
								m_TacticalScores.add(lambda(m_TacticalMoves[m_TacticalPasses.length()]));
								m_TacticalPasses.add(m_CurrentTacticalPass);
							}
							sort<movebitsType, scoreType>::sortValues(m_TacticalMoves.ptr() + static_cast<size_t>(start), m_TacticalScores.ptr() + static_cast<size_t>(start), static_cast<size_t>(m_TacticalMoves.length() - start));
							++m_CurrentTacticalPass;
						}
						while (m_CurrentTacticalMove < m_TacticalMoves.length())
						{
							moveBits = m_TacticalMoves[m_CurrentTacticalMove];
							++m_CurrentTacticalMove;
							if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::stackType*>(this), moveBits))
							{
								m_LastTacticalPass = m_TacticalPasses[m_CurrentTacticalMove - 1];
								return true;
							}
						}
					}
				}
				else
				{
					while (!allMovesGenerated)
					{
						if (m_CurrentTacticalMove >= m_TacticalMoves.length())
						{
							if (m_CurrentTacticalPass >= countTacticalPasses)
							{
								allMovesGenerated = true;
								return false;
							}
							generatorType::generateTacticalMoves(*static_cast<const typename generatorType::stackType*>(this), m_TacticalMoves, feedback.tacticalIndex(m_CurrentTacticalPass, depth));
							const auto start{ m_TacticalPasses.length() };
							while (m_TacticalPasses.length() < m_TacticalMoves.length())
							{
								m_TacticalScores.add(lambda(m_TacticalMoves[m_TacticalPasses.length()]));
								m_TacticalPasses.add(m_CurrentTacticalPass);
							}
							sort<movebitsType, scoreType>::sortValues(m_TacticalMoves.ptr() + static_cast<size_t>(start), m_TacticalScores.ptr() + static_cast<size_t>(start), static_cast<size_t>(m_TacticalMoves.length() - start));
							++m_CurrentTacticalPass;
						}
						while (m_CurrentTacticalMove < m_TacticalMoves.length())
						{
							moveBits = m_TacticalMoves[m_CurrentTacticalMove];
							++m_CurrentTacticalMove;
							if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::stackType*>(this), moveBits))
							{
								m_LastTacticalPass = m_TacticalPasses[m_CurrentTacticalMove - 1];
								return true;
							}
						}
					}
				}
				return false;
			}
			bool nextCriticalMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback) const noexcept
			{
				bool allMovesGenerated{ false };
				while (!allMovesGenerated)
				{
					if (m_CurrentCriticalMove >= m_CriticalMoves.length())
					{
						if (m_CurrentCriticalPass >= countCriticalPasses)
						{
							allMovesGenerated = true;
							return false;
						}
						generatorType::generateCriticalMoves(*static_cast<const typename generatorType::stackType*>(this), m_CriticalMoves, feedback.criticalIndex(m_CurrentCriticalPass, depth));
						const auto start{ m_CriticalPasses.length() };
						while (m_CriticalPasses.length() < m_CriticalMoves.length())
							m_CriticalPasses.add(m_CurrentCriticalPass);
						++m_CurrentCriticalPass;
					}
					while (m_CurrentCriticalMove < m_CriticalMoves.length())
					{
						moveBits = m_CriticalMoves[m_CurrentCriticalMove];
						++m_CurrentCriticalMove;
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::stackType*>(this), moveBits))
						{
							m_LastCriticalPass = m_CriticalPasses[m_CurrentCriticalMove - 1];
							return true;
						}
					}
				}
				return false;
			}
			template<typename LAMBDA>
			bool nextCriticalMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback, const LAMBDA& lambda) const noexcept
			{
				bool allMovesGenerated{ false };
				while (!allMovesGenerated)
				{
					if (m_CurrentCriticalMove >= m_CriticalMoves.length())
					{
						if (m_CurrentCriticalPass >= countCriticalPasses)
						{
							allMovesGenerated = true;
							return false;
						}
						generatorType::generateCriticalMoves(*static_cast<const typename generatorType::stackType*>(this), m_CriticalMoves, feedback.criticalIndex(m_CurrentCriticalPass, depth));
						const auto start{ m_CriticalPasses.length() };
						while (m_CriticalPasses.length() < m_CriticalMoves.length())
						{
							m_CriticalScores.add(lambda(m_CriticalMoves[m_CriticalPasses.length()]));
							m_CriticalPasses.add(m_CurrentCriticalPass);
						}
						sort<movebitsType, scoreType>::sortValues(m_CriticalMoves.ptr() + static_cast<size_t>(start), m_CriticalScores.ptr() + static_cast<size_t>(start), static_cast<size_t>(m_CriticalMoves.length() - start));
						++m_CurrentCriticalPass;
					}
					while (m_CurrentCriticalMove < m_CriticalMoves.length())
					{
						moveBits = m_CriticalMoves[m_CurrentCriticalMove];
						++m_CurrentCriticalMove;
						if (generatorType::isGeneratedMoveLegal(*static_cast<const typename generatorType::stackType*>(this), moveBits))
						{
							m_LastCriticalPass = m_CriticalPasses[m_CurrentCriticalMove - 1];
							return true;
						}
					}
				}
				return false;
			}
			stack(const stack& parent, const movebitsType& moveBits) noexcept :
				m_pParent{ &parent },
				m_Position{ parent.m_Position },
				m_History{ parent.m_History },
				m_Moves(),
				m_HasLegalMove{ false },
				m_HasLegalMoveValid{ false },
				m_SignatureValid{ false },
				m_CurrentPass{ 0 },
				m_CurrentMove{ 0 },
				m_CurrentTacticalPass{ 0 },
				m_CurrentTacticalMove{ 0 },
				m_CurrentCriticalPass{ 0 },
				m_CurrentCriticalMove{ 0 },
				m_CurrentLegalMove{ 0 },
				m_MoveData(motorType::move().doMove(m_Position, moveBits)),
				m_MovingPlayer{ m_Position.movingPlayer() },
				m_NextPlayer{ m_MovingPlayer.next() },
				m_IsNullmove{ false },
				m_LastPass{ 0 },
				m_LastTacticalPass{ 0 },
				m_LastCriticalPass{ 0 },
				m_Hash{ m_Position.hash() }
			{
			}
			stack(boardType& position, historyType& history, const playerType& oldPlayer) noexcept :
				m_pParent{ nullptr },
				m_Position{ position },
				m_History{ history },
				m_Moves(),
				m_HasLegalMove{ false },
				m_HasLegalMoveValid{ false },
				m_SignatureValid{ false },
				m_CurrentPass{ 0 },
				m_CurrentMove{ 0 },
				m_CurrentTacticalPass{ 0 },
				m_CurrentTacticalMove{ 0 },
				m_CurrentCriticalPass{ 0 },
				m_CurrentCriticalMove{ 0 },
				m_CurrentLegalMove{ 0 },
				m_MoveData(),
				m_MovingPlayer{ m_Position.movingPlayer() },
				m_NextPlayer{ m_MovingPlayer.next() },
				m_IsNullmove{ true },
				m_LastPass{ 0 },
				m_LastTacticalPass{ 0 },
				m_LastCriticalPass{ 0 },
				m_Hash{ m_Position.hash() }
			{
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
			std::string moveToString(const movebitsType& moveBits, const size_t depth) const
			{
				return generatorType::moveToString(*static_cast<const typename generatorType::stackType*>(this), moveBits, depth);
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
		static std::string moveToString(const stackType& stack, const movebitsType& moveBits, const size_t depth) noexcept
		{
			return generatorType::moveToString_Implementation(stack, moveBits, depth);
		}
		static std::string passToString(const passType& pass) noexcept
		{
			return generatorType::passToString_Implementation(pass);
		}
		static std::string tacticalPassToString(const passType& tacticalPass) noexcept
		{
			return generatorType::tacticalPassToString_Implementation(tacticalPass);
		}
		static std::string tacticalCriticalEvasionPassToString(const passType& tacticalCriticalEvasionPass) noexcept
		{
			return generatorType::tacticalCriticalEvasionPassToString_Implementation(tacticalCriticalEvasionPass);
		}
		static std::string criticalPassToString(const passType& criticalPass) noexcept
		{
			return generatorType::criticalPassToString_Implementation(criticalPass);
		}
		static std::string criticalEvasionPassToString(const passType& criticalEvasionPass) noexcept
		{
			return generatorType::criticalPassToString_Implementation(criticalEvasionPass);
		}
		static std::string quietCriticalPassToString(const passType& quietCriticalPass) noexcept
		{
			return generatorType::quietCriticalPassToString_Implementation(quietCriticalPass);
		}
		template<typename stackType>
		constexpr static void generateMoves(const stackType& stack, movelistType& moves, const passType& currentPass) noexcept
		{
			generatorType::generateMoves_Implementation(stack, moves, currentPass);
		}
		template<typename stackType>
		constexpr static void generateCriticalMoves(const stackType& stack, movelistType& moves, const passType& currentPass) noexcept
		{
			generatorType::generateCriticalMoves_Implementation(stack, moves, currentPass);
		}
		template<typename stackType>
		constexpr static void generateTacticalCriticalEvasionMoves(const stackType& stack, movelistType& moves, const passType& currentPass) noexcept
		{
			generatorType::generateTacticalCriticalEvasionMoves_Implementation(stack, moves, currentPass);
		}
		template<typename stackType>
		constexpr static void generateCriticalEvasionMoves(const stackType& stack, movelistType& moves, const passType& currentPass) noexcept
		{
			generatorType::generateCriticalEvasionMoves_Implementation(stack, moves, currentPass);
		}
		template<typename stackType>
		constexpr static void generateQuietCriticalMoves(const stackType& stack, movelistType& moves, const passType& currentPass) noexcept
		{
			generatorType::generateQuietCriticalMoves_Implementation(stack, moves, currentPass);
		}
		template<typename stackType>
		constexpr static void generateTacticalMoves(const stackType& stack, movelistType& moves, const passType& currentPass) noexcept
		{
			generatorType::generateTacticalMoves_Implementation(stack, moves, currentPass);
		}
		template<typename stackType>
		static bool isMoveLegal(const stackType& stack, const movebitsType& moveBits) noexcept
		{
			return generatorType::isMoveLegal_Implementation(stack, moveBits);
		}
		template<typename stackType>
		static bool isGeneratedMoveLegal(const stackType& stack, const movebitsType& moveBits) noexcept
		{
			return generatorType::isGeneratedMoveLegal_Implementation(stack, moveBits);
		}
		template<typename stackType>
		static std::uintmax_t perft(const stackType& stack, const size_t depthRemaining, const size_t depth, std::uintmax_t& nodes, movegenFeedback& feedback) noexcept
		{
			if (depthRemaining <= 0)
				return 1;
			else
			{
				movebitsType mb;
				std::uintmax_t count{ 0 };
				while (stack.nextMove(mb, depth, feedback))
				{
					nodes++;
					stackType subStack(stack, mb);
					count += generator::perft(subStack, depthRemaining - 1, depth + 1, nodes, feedback);
				}
				return count;
			}
		}
		template<typename stackType>
		constexpr static bool isMoveTactical(const stackType& stack, const movebitsType& mv) noexcept
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
		constexpr static size_t moveBucket(const boardType& position, const movebitsType& mv) noexcept
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
		template<typename stackType>
		constexpr static bool isMoveCritical(const stackType& stack, const movebitsType& moveBits) noexcept
		{
			return generatorType::isMoveCritical_Implementation(stack, moveBits);
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