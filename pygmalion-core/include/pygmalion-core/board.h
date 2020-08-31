namespace pygmalion
{
	template<typename DESCRIPTOR_BOARD>
	class board :
		public base_board<DESCRIPTOR_BOARD>
	{
	public:
		using descriptorBoard = DESCRIPTOR_BOARD;
#include "include_board.h"
	private:
		std::array<squaresType, countPieces> m_PieceOccupancy;
		std::array<squaresType, countPlayers> m_PlayerOccupancy;
		playerType m_MovingPlayer;
		flagsType m_Flags;
	protected:
		constexpr void setFlag(const flagType flag) noexcept
		{
			m_Flags[flag] = true;
		}
		constexpr void setFlags(const flagsType flags) noexcept
		{
			m_Flags = flags;
		}
		constexpr const flagsType getFlags() const noexcept
		{
			return m_Flags;
		}
		constexpr void clearFlag(const flagType flag) noexcept
		{
			m_Flags[flag] = false;
		}
		constexpr bool checkFlag(const flagType flag) const noexcept
		{
			return m_Flags[flag];
		}
		constexpr void clearFlags(const int first, const int count) noexcept
		{
			const flagsType mask{ static_cast<flagsType>(~(((flagsType(1) << count) - 1) << first)) };
			m_Flags &= mask;
		}
	public:
		constexpr void setMovingPlayer(const playerType movingPlayer) noexcept
		{
			assert(movingPlayer.isValid());
			m_MovingPlayer = movingPlayer;
		}
		constexpr playerType movingPlayer() const noexcept
		{
			return m_MovingPlayer;
		}
		constexpr playerType& movingPlayer() noexcept
		{
			return m_MovingPlayer;
		}
		constexpr const squaresType& pieceOccupancy(const pieceType pc) const noexcept
		{
			assert(pc.isValid());
			return m_PieceOccupancy[pc];
		}
		constexpr squaresType& pieceOccupancy(const pieceType pc) noexcept
		{
			assert(pc.isValid());
			return m_PieceOccupancy[pc];
		}
		constexpr const squaresType& playerOccupancy(const playerType p) const noexcept
		{
			assert(p.isValid());
			return m_PlayerOccupancy[p];
		}
		constexpr squaresType& playerOccupancy(const playerType p) noexcept
		{
			assert(p.isValid());
			return m_PlayerOccupancy[p];
		}
		constexpr const flagsType& flags() const noexcept
		{
			return m_Flags;
		}
		constexpr flagsType& flags() noexcept
		{
			return m_Flags;
		}
		constexpr squaresType totalOccupancy() const noexcept
		{
			constexpr const bool preferPlayers{ countPlayers < countPieces };
			squaresType value(0);
			if (preferPlayers)
			{
				for (const auto p : playerType::range)
				{
					value |= m_PlayerOccupancy[p];
				}
			}
			else
			{
				for (const auto pc : pieceType::range)
				{
					value |= m_PieceOccupancy[pc];
				}
			}
			return value;
		}
		constexpr bool isOccupied(const squareType sq) const noexcept
		{
			assert(sq.isValid());
			return totalOccupancy()[sq];
		}
		constexpr bool isOccupied(const squareType sq, const playerType p) const noexcept
		{
			assert(sq.isValid());
			assert(p.isValid());
			return playerOccupancy(p)[sq];
		}
		constexpr void addPiece(const pieceType pc, const squareType sq, const playerType p) noexcept
		{
			assert(p.isValid());
			assert(pc.isValid());
			assert(sq.isValid());
#if !defined(NDEBUG)
			assert(!m_PlayerOccupancy[p][sq]);
			assert(!m_PieceOccupancy[pc][sq]);
#endif
			m_PlayerOccupancy[p] += sq;
			m_PieceOccupancy[pc] += sq;
		}
		constexpr void removePiece(const pieceType pc, const squareType sq, const playerType p) noexcept
		{
			assert(p.isValid());
			assert(pc.isValid());
			assert(sq.isValid());
#if !defined(NDEBUG)
			assert(m_PlayerOccupancy[p][sq]);
			assert(m_PieceOccupancy[pc][sq]);
#endif
			m_PlayerOccupancy[p] -= sq;
			m_PieceOccupancy[pc] -= sq;
		}
		constexpr pieceType getPiece(const squareType sq) const noexcept
		{
			assert(sq.isValid());
			assert(totalOccupancy()[sq]);
			pieceType pc{ 0 };
			for (const auto i : pieceType::range)
				pc = pc | m_PieceOccupancy[i][sq] * i;
			return pc;
		}
		constexpr void clear() noexcept
		{
			for (const auto p : playerType::range)
				m_PlayerOccupancy[p] = squaresType::none();
			for (const auto pc : pieceType::range)
				m_PieceOccupancy[pc] = squaresType::none();
			m_Flags = 0;
			m_MovingPlayer = 0;
		}
		constexpr board() noexcept :
			m_PieceOccupancy{ },
			m_PlayerOccupancy{ },
			m_MovingPlayer{ 0 },
			m_Flags{ 0 }
		{
			clear();
		}
		constexpr board(board&&) noexcept = default;
		constexpr board(const board&) noexcept = default;
		constexpr board& operator=(board&&) noexcept = default;
		constexpr board& operator=(const board&) noexcept = default;
		~board() noexcept = default;
	};
}