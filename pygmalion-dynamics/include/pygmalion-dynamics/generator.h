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
				std::array <std::uint64_t, countTacticalPasses> m_TacticalMoveCounter;
				std::array <scoreType, countTacticalPasses> m_TacticalScoreCounter;
				std::array <passType, countPasses> m_Index;
				std::array <passType, countTacticalPasses> m_TacticalIndex;
				constexpr static bool USE_SCORE{ false };
			public:
				constexpr void sortIndices() noexcept
				{
					if constexpr (!USE_SCORE)
					{
						sort<passType, std::uint64_t>::sortValues(m_Index.data(), m_MoveCounter.data(), countPasses);
						sort<passType, std::uint64_t>::sortValues(m_TacticalIndex.data(), m_TacticalMoveCounter.data(), countTacticalPasses);
					}
					else
					{
						sort<passType, scoreType>::sortValues(m_Index.data(), m_ScoreCounter.data(), countPasses);
						sort<passType, scoreType>::sortValues(m_TacticalIndex.data(), m_TacticalScoreCounter.data(), countTacticalPasses);
					}
				}
				constexpr passType index(const passType pass) const noexcept
				{
					assert(pass < countPasses);
					return m_Index[static_cast<size_t>(pass)];
				}
				constexpr passType tacticalIndex(const passType pass) const noexcept
				{
					assert(pass < countTacticalPasses);
					return m_TacticalIndex[static_cast<size_t>(pass)];
				}
				constexpr feedback() noexcept :
					m_MoveCounter{ arrayhelper::make<countPasses,std::uint64_t>(0) },
					m_TacticalMoveCounter{ arrayhelper::make<countTacticalPasses, std::uint64_t>(0) },
					m_ScoreCounter{ arrayhelper::make<countPasses,scoreType>(scoreType::zero()) },
					m_TacticalScoreCounter{ arrayhelper::make<countTacticalPasses, scoreType>(scoreType::zero()) },
					m_Index{ arrayhelper::generate<countPasses,passType>([](const size_t index) {return index; }) },
					m_TacticalIndex{ arrayhelper::generate<countTacticalPasses,passType>([](const size_t index) {return index; }) }
				{

				}
				constexpr scoreType score(const passType pass) const noexcept
				{
					if constexpr (USE_SCORE)
					{
						const size_t indexMove{ static_cast<size_t>(index(pass)) };
						const size_t indexScore{ static_cast<size_t>(pass) };
						if (m_MoveCounter[indexMove] == 0)
							return scoreType::zero();
						if (m_ScoreCounter[indexScore].isOpen())
							return m_ScoreCounter[indexScore] / static_cast<typename scoreType::valueType>(m_MoveCounter[indexMove]);
						else
							return m_ScoreCounter[indexScore];
					}
					else
					{
						const size_t indexMove{ static_cast<size_t>(pass) };
						const size_t indexScore{ static_cast<size_t>(index(pass)) };
						if (m_MoveCounter[indexMove] == 0)
							return scoreType::zero();
						if (m_ScoreCounter[indexScore].isOpen())
							return m_ScoreCounter[indexScore] / static_cast<typename scoreType::valueType>(m_MoveCounter[indexMove]);
						else
							return m_ScoreCounter[indexScore];
					}
				}
				constexpr scoreType tacticalScore(const passType pass) const noexcept
				{
					if constexpr (USE_SCORE)
					{
						const size_t indexMove{ static_cast<size_t>(tacticalIndex(pass)) };
						const size_t indexScore{ static_cast<size_t>(pass) };
						if (m_TacticalMoveCounter[indexMove] == 0)
							return scoreType::zero();
						if (m_TacticalScoreCounter[indexScore].isOpen())
							return m_TacticalScoreCounter[indexScore] / static_cast<typename scoreType::valueType>(m_TacticalMoveCounter[indexMove]);
						else
							return m_TacticalScoreCounter[indexScore];
					}
					else
					{
						const size_t indexMove{ static_cast<size_t>(pass) };
						const size_t indexScore{ static_cast<size_t>(tacticalIndex(pass)) };
						if (m_TacticalMoveCounter[indexMove] == 0)
							return scoreType::zero();
						if (m_TacticalScoreCounter[indexScore].isOpen())
							return m_TacticalScoreCounter[indexScore] / static_cast<typename scoreType::valueType>(m_TacticalMoveCounter[indexMove]);
						else
							return m_TacticalScoreCounter[indexScore];
					}
				}
				constexpr const std::uint64_t& counter(const passType pass) const noexcept
				{
					if constexpr (USE_SCORE)
						return m_MoveCounter[static_cast<size_t>(index(pass))];
					else
						return m_MoveCounter[static_cast<size_t>(pass)];
				}
				constexpr const std::uint64_t& tacticalCounter(const passType pass) const noexcept
				{
					if constexpr (USE_SCORE)
						return m_TacticalMoveCounter[static_cast<size_t>(tacticalIndex(pass))];
					else
						return m_TacticalMoveCounter[static_cast<size_t>(pass)];
				}
				constexpr void incrementMove(const passType pass, const scoreType score) noexcept
				{
					if constexpr (USE_SCORE)
					{
						const size_t indexMove{ static_cast<size_t>(index(pass)) };
						const size_t indexScore{ static_cast<size_t>(pass) };
						if (score.isOpen())
						{
							if (m_ScoreCounter[indexScore].isOpen())
								m_ScoreCounter[indexScore] += score;
							else
								m_ScoreCounter[indexScore] = scoreType::max(score, m_ScoreCounter[indexScore]);
						}
						else
							m_ScoreCounter[static_cast<size_t>(index(pass))] = scoreType::max(score, m_ScoreCounter[indexScore]);
						m_MoveCounter[indexMove]++;
					}
					else
					{
						const size_t indexMove{ static_cast<size_t>(pass) };
						const size_t indexScore{ static_cast<size_t>(index(pass)) };
						if (score.isOpen())
						{
							if (m_ScoreCounter[indexScore].isOpen())
								m_ScoreCounter[indexScore] += score;
							else
								m_ScoreCounter[indexScore] = scoreType::max(score, m_ScoreCounter[indexScore]);
						}
						else
							m_ScoreCounter[static_cast<size_t>(index(pass))] = scoreType::max(score, m_ScoreCounter[indexScore]);
						m_MoveCounter[indexMove]++;
					}
				}
				constexpr void incrementTacticalMove(const passType pass, const scoreType score) noexcept
				{
					if constexpr (USE_SCORE)
					{
						const size_t indexMove{ static_cast<size_t>(tacticalIndex(pass)) };
						const size_t indexScore{ static_cast<size_t>(pass) };
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
					else
					{
						const size_t indexMove{ static_cast<size_t>(pass) };
						const size_t indexScore{ static_cast<size_t>(tacticalIndex(pass)) };
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
				}
				constexpr void reset() noexcept
				{
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
			constexpr const std::uint64_t& counter(const passType pass, const size_t depth) const noexcept
			{
				assert(pass < countPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].counter(pass);
			}
			constexpr scoreType score(const passType pass, const size_t depth) const noexcept
			{
				assert(pass < countPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].score(pass);
			}
			constexpr const std::uint64_t& tacticalCounter(const passType pass, const size_t depth) const noexcept
			{
				assert(pass < countTacticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(std::move(feedback()));
				}
				return m_Feedback[depth].tacticalCounter(pass);
			}
			constexpr scoreType tacticalScore(const passType pass, const size_t depth) const noexcept
			{
				assert(pass < countTacticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].tacticalScore(pass);
			}
			constexpr void cutMove(const passType pass, const size_t depth, const scoreType score) noexcept
			{
				assert(pass < countPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementMove(pass, score);
			}
			constexpr void allMove(const passType pass, const size_t depth, const scoreType score) noexcept
			{
				assert(pass < countPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementMove(pass, score);
			}
			constexpr void tacticalCutMove(const passType tacticalPass, const size_t depth, const scoreType score) noexcept
			{
				assert(tacticalPass < countTacticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementTacticalMove(tacticalPass, score);
			}
			constexpr void tacticalAllMove(const passType tacticalPass, const size_t depth, const scoreType score) noexcept
			{
				assert(tacticalPass < countTacticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				m_Feedback[depth].incrementTacticalMove(tacticalPass, score);
			}
			constexpr void reset() noexcept
			{
				m_Feedback.clear();
			}
			constexpr passType index(const passType pass, const size_t depth) const noexcept
			{
				assert(pass < countPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].index(pass);
			}
			constexpr passType tacticalIndex(const passType pass, const size_t depth) const noexcept
			{
				assert(pass < countTacticalPasses);
				while (m_Feedback.size() <= depth)
				{
					m_Feedback.emplace_back(feedback());
				}
				return m_Feedback[depth].tacticalIndex(pass);
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
			mutable passlistType m_Passes;
			mutable movelistType m_TacticalMoves;
			mutable passlistType m_TacticalPasses;
			boardType& m_Position;
			historyType& m_History;
			const movedataType m_MoveData;
			mutable passType m_CurrentPass;
			mutable passType m_LastPass;
			mutable passType m_CurrentTacticalPass;
			mutable passType m_LastTacticalPass;
			mutable indexType m_CurrentMove;
			mutable indexType m_CurrentTacticalMove;
			mutable indexType m_CurrentLegalMove;
			mutable signatureType m_Signature;
			const playerType m_MovingPlayer;
			const playerType m_NextPlayer;
			mutable bool m_HasLegalMove;
			mutable bool m_HasLegalMoveValid;
			mutable bool m_SignatureValid;
			const bool m_IsNullmove;
			bool computeHasLegalMove(const size_t depth, movegenFeedback& feedback) const
			{
				bool allMovesGenerated{ false };
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
						m_CurrentPass++;
					}
					while (m_CurrentLegalMove < m_Moves.length())
					{
						if (generatorType::isMoveLegal(*static_cast<const typename generatorType::stackType*>(this), m_Moves[m_CurrentLegalMove]))
							return true;
						m_CurrentLegalMove++;
					}
				}
				return false;
			}
		public:
			constexpr void allMove(movegenFeedback& feedback, const size_t depth, const scoreType score) const noexcept
			{
				feedback.allMove(m_LastPass, depth, score);
			}
			constexpr void tacticalAllMove(movegenFeedback& feedback, const size_t depth, const scoreType score) const noexcept
			{
				feedback.tacticalAllMove(m_LastTacticalPass, depth, score);
			}
			constexpr void cutMove(movegenFeedback& feedback, const size_t depth, const scoreType score) const noexcept
			{
				feedback.cutMove(m_LastPass, depth, score);
			}
			constexpr void tacticalCutMove(movegenFeedback& feedback, const size_t depth, const scoreType score) const noexcept
			{
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
				return generatorType::isMoveLegal(*reinterpret_cast<const typename generatorType::stackType*>(this), moveBits);
			}
			bool nextMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback) const noexcept
			{
				bool allMovesGenerated{ false };
				while (!allMovesGenerated)
				{
					if (m_CurrentMove >= m_Moves.length())
					{
						if (m_CurrentPass >= countPasses)
						{
							allMovesGenerated = true;
							return false;
						}
						generatorType::generateMoves(*reinterpret_cast<const typename generatorType::stackType*>(this), m_Moves, feedback.index(m_CurrentPass, depth));
						while (m_Passes.length() < m_Moves.length())
							m_Passes.add(m_CurrentPass);
						m_CurrentPass++;
					}
					while (m_CurrentMove < m_Moves.length())
					{
						moveBits = m_Moves[m_CurrentMove];
						m_CurrentMove++;
						if (generatorType::isMoveLegal(*reinterpret_cast<const typename generatorType::stackType*>(this), moveBits))
						{
							m_LastPass = m_Passes[m_CurrentMove - 1];
							return true;
						}
					}
				}
				return false;
			}
			bool nextTacticalMove(movebitsType& moveBits, const size_t depth, movegenFeedback& feedback) const noexcept
			{
				bool allMovesGenerated{ false };
				while (!allMovesGenerated)
				{
					if (m_CurrentTacticalMove >= m_TacticalMoves.length())
					{
						if (m_CurrentTacticalPass >= countTacticalPasses)
						{
							allMovesGenerated = true;
							return false;
						}
						generatorType::generateTacticalMoves(*reinterpret_cast<const typename generatorType::stackType*>(this), m_TacticalMoves, feedback.tacticalIndex(m_CurrentTacticalPass, depth));
						while (m_TacticalPasses.length() < m_TacticalMoves.length())
							m_TacticalPasses.add(m_CurrentTacticalPass);
						m_CurrentTacticalPass++;
					}
					while (m_CurrentTacticalMove < m_TacticalMoves.length())
					{
						moveBits = m_TacticalMoves[m_CurrentTacticalMove];
						m_CurrentTacticalMove++;
						if (generatorType::isMoveLegal(*reinterpret_cast<const typename generatorType::stackType*>(this), moveBits))
						{
							m_LastTacticalPass = m_TacticalPasses[m_CurrentTacticalMove - 1];
							return true;
						}
					}
				}
				return false;
			}
			stack(const stack& parent, const movebitsType moveBits) noexcept :
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
				m_CurrentLegalMove{ 0 },
				m_MoveData(motorType::move().doMove(m_Position, moveBits)),
				m_MovingPlayer{ m_Position.movingPlayer() },
				m_NextPlayer{ m_MovingPlayer.next() },
				m_IsNullmove{ false },
				m_LastPass{ 0 },
				m_LastTacticalPass{ 0 }
			{
			}
			stack(boardType& position, historyType& history, const playerType oldPlayer) noexcept :
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
				m_CurrentLegalMove{ 0 },
				m_MoveData(),
				m_MovingPlayer{ m_Position.movingPlayer() },
				m_NextPlayer{ m_MovingPlayer.next() },
				m_IsNullmove{ true },
				m_LastPass{ 0 },
				m_LastTacticalPass{ 0 }
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
			std::string moveToString(const movebitsType moveBits, const size_t depth) const
			{
				return generatorType::moveToString(*static_cast<const typename generatorType::stackType*>(this), moveBits, depth);
			}
			constexpr bool occurs(const boardType& position, const int times, const int start = 3, const int frequency = 4) const noexcept
			{
				int n{ 0 };
				if (m_pParent != nullptr)
				{
					if (start == 0)
					{
						if (m_Position == position)
						{
							if (times == 1)
								return true;
							else
								return m_pParent->occurs(position, times - 1, frequency, frequency);
						}
						else
							return m_pParent->occurs(position, times, start - 1, frequency);
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
		static std::string passToString(const passType pass) noexcept
		{
			return generatorType::passToString_Implementation(pass);
		}
		static std::string tacticalPassToString(const passType tacticalPass) noexcept
		{
			return generatorType::tacticalPassToString_Implementation(tacticalPass);
		}
		template<typename stackType>
		static void generateMoves(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			generatorType::generateMoves_Implementation(stack, moves, currentPass);
		}
		template<typename stackType>
		static void generateTacticalMoves(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			generatorType::generateTacticalMoves_Implementation(stack, moves, currentPass);
		}
		template<typename stackType>
		static bool isMoveLegal(const stackType& stack, const movebitsType& moveBits) noexcept
		{
			return generatorType::isMoveLegal_Implementation(stack, moveBits);
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
	};
}