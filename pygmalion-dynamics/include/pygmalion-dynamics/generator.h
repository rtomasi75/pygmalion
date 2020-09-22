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
			mutable movelistType m_Moves;
			mutable movelistType m_TacticalMoves;
			boardType& m_Position;
			const movedataType m_MoveData;
			mutable size_t m_CurrentPass;
			mutable size_t m_CurrentTacticalPass;
			mutable indexType m_CurrentMove;
			mutable indexType m_CurrentTacticalMove;
			mutable indexType m_CurrentLegalMove;
			const playerType m_MovingPlayer;
			const playerType m_NextPlayer;
			mutable bool m_HasLegalMove;
			mutable bool m_HasLegalMoveValid;
			const bool m_IsNullmove;
			bool computeHasLegalMove() const
			{
				bool allMovesGenerated{ false };
				while (!allMovesGenerated)
				{
					if (m_CurrentLegalMove >= m_Moves.length())
					{
						if (!generatorType::generateMoves(*this, m_Moves, m_CurrentPass))
						{
							allMovesGenerated = true;
							return false;
						}
					}
					while (m_CurrentLegalMove < m_Moves.length())
					{
						if (generatorType::isMoveLegal(*this, m_Moves[m_CurrentLegalMove]))
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
			bool isMoveLegal(const movebitsType& moveBits) const noexcept
			{
				return generatorType::isMoveLegal(*this, moveBits);
			}
			bool nextMove(movebitsType& moveBits) const noexcept
			{
				bool allMovesGenerated{ false };
				while (!allMovesGenerated)
				{
					if (m_CurrentMove >= m_Moves.length())
					{
						if (!generatorType::generateMoves(*this, m_Moves, m_CurrentPass))
						{
							allMovesGenerated = true;
							return false;
						}
					}
					while (m_CurrentMove < m_Moves.length())
					{
						moveBits = m_Moves[m_CurrentMove];
						m_CurrentMove++;
						if (generatorType::isMoveLegal(*this, moveBits))
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
						if (!generatorType::generateTacticalMoves(*this, m_TacticalMoves, m_CurrentTacticalPass))
						{
							allMovesGenerated = true;
							return false;
						}
					}
					while (m_CurrentTacticalMove < m_TacticalMoves.length())
					{
						moveBits = m_TacticalMoves[m_CurrentTacticalMove];
						m_CurrentTacticalMove++;
						if (generatorType::isMoveLegal(*this, moveBits))
							return true;
					}
				}
				return false;
			}
			stack(const stack& parent, const movebitsType moveBits) noexcept :
				m_Position{ parent.m_Position },
				m_Moves(),
				m_HasLegalMove{ false },
				m_HasLegalMoveValid{ false },
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
			stack(boardType& position, const playerType oldPlayer) noexcept :
				m_Position{ position },
				m_Moves(),
				m_HasLegalMove{ false },
				m_HasLegalMoveValid{ false },
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
			const boardType& position() const noexcept
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
		};

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

	};
}