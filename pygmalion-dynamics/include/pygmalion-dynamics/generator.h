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
			mutable movelistType m_TacticalMoves;
			boardType& m_Position;
			historyType& m_History;
			const movedataType m_MoveData;
			mutable size_t m_CurrentPass;
			mutable size_t m_CurrentTacticalPass;
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
			bool computeHasLegalMove() const
			{
				bool allMovesGenerated{ false };
				while (!allMovesGenerated)
				{
					if (m_CurrentLegalMove >= m_Moves.length())
					{
						if (!generatorType::generateMoves(*static_cast<const typename generatorType::stackType*>(this), m_Moves, m_CurrentPass))
						{
							allMovesGenerated = true;
							return false;
						}
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
			bool hasLegalMove() const
			{
				if (!m_HasLegalMoveValid)
				{
					m_HasLegalMove = computeHasLegalMove();
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
			bool nextMove(movebitsType& moveBits) const noexcept
			{
				bool allMovesGenerated{ false };
				while (!allMovesGenerated)
				{
					if (m_CurrentMove >= m_Moves.length())
					{
						if (!generatorType::generateMoves(*reinterpret_cast<const typename generatorType::stackType*>(this), m_Moves, m_CurrentPass))
						{
							allMovesGenerated = true;
							return false;
						}
					}
					while (m_CurrentMove < m_Moves.length())
					{
						moveBits = m_Moves[m_CurrentMove];
						m_CurrentMove++;
						if (generatorType::isMoveLegal(*reinterpret_cast<const typename generatorType::stackType*>(this), moveBits))
							return true;
					}
				}
				return false;
			}
			bool nextTacticalMove(movebitsType& moveBits) const noexcept
			{
				bool allMovesGenerated{ false };
				while (!allMovesGenerated)
				{
					if (m_CurrentTacticalMove >= m_TacticalMoves.length())
					{
						if (!generatorType::generateTacticalMoves(*reinterpret_cast<const typename generatorType::stackType*>(this), m_TacticalMoves, m_CurrentTacticalPass))
						{
							allMovesGenerated = true;
							return false;
						}
					}
					while (m_CurrentTacticalMove < m_TacticalMoves.length())
					{
						moveBits = m_TacticalMoves[m_CurrentTacticalMove];
						m_CurrentTacticalMove++;
						if (generatorType::isMoveLegal(*reinterpret_cast<const typename generatorType::stackType*>(this), moveBits))
							return true;
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
				m_IsNullmove{ false }
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
				m_IsNullmove{ true }
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
			std::string moveToString(const movebitsType moveBits) const
			{
				return generatorType::moveToString(*static_cast<const typename generatorType::stackType*>(this), moveBits);
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
		static std::string moveToString(const stackType& stack, const movebitsType moveBits) noexcept
		{
			return generatorType::moveToString_Implementation(stack, moveBits);
		}
		template<typename stackType>
		static bool generateMoves(const stackType& stack, movelistType& moves, size_t& currentPass) noexcept
		{
			return generatorType::generateMoves_Implementation(stack, moves, currentPass);
		}
		template<typename stackType>
		static bool generateTacticalMoves(const stackType& stack, movelistType& moves, size_t& currentPass) noexcept
		{
			return generatorType::generateTacticalMoves_Implementation(stack, moves, currentPass);
		}
		template<typename stackType>
		static bool isMoveLegal(const stackType& stack, const movebitsType& moveBits) noexcept
		{
			return generatorType::isMoveLegal_Implementation(stack, moveBits);
		}
		template<typename stackType>
		static std::uintmax_t perft(const stackType& stack, const size_t depth, std::uintmax_t& nodes) noexcept
		{
			if (depth <= 0)
				return 1;
			else
			{
				movebitsType mb;
				std::uintmax_t count{ 0 };
				while (stack.nextMove(mb))
				{
					nodes++;
					stackType subStack(stack, mb);
					count += generator::perft(subStack, depth - 1, nodes);
				}
				return count;
			}
		}
	};
}