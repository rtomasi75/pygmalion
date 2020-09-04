namespace pygmalion
{
	template<typename DESCRIPTOR_BOARD, typename INSTANCE>
	class board :
		public DESCRIPTOR_BOARD
	{
	public:
		using boardType = INSTANCE;
		using descriptorBoard = DESCRIPTOR_BOARD;
#include "include_board.h"
	private:
		std::array<squaresType, countPieces> m_PieceOccupancy;
		std::array<squaresType, countPlayers> m_PlayerOccupancy;
		playerType m_MovingPlayer;
		flagsType m_Flags;
	protected:
		void onClear() noexcept
		{
			reinterpret_cast<boardType*>(this)->onClear_Implementation();
		}
		void onAddedPiece(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			reinterpret_cast<boardType*>(this)->onAddedPiece_Implementation(piece, square, player);
		}
		void onRemovedPiece(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			reinterpret_cast<boardType*>(this)->onRemovedPiece_Implementation(piece, square, player);
		}
		void onSetFlag(const flagType flag) noexcept
		{
			reinterpret_cast<boardType*>(this)->onSetFlag_Implementation(flag);
		}
		void onClearedFlag(const flagType flag) noexcept
		{
			reinterpret_cast<boardType*>(this)->onClearedFlag_Implementation(flag);
		}
		constexpr void setFlag(const flagType flag) noexcept
		{
			m_Flags.setBit(static_cast<typename flagType::baseType>(flag));
			onSetFlag(flag);
		}
		constexpr void clearFlag(const flagType flag) noexcept
		{
			m_Flags.clearBit(static_cast<typename flagType::baseType>(flag));
			onClearedFlag(flag);
		}
		constexpr bool checkFlag(const flagType flag) const noexcept
		{
			return m_Flags[static_cast<typename flagType::baseType>(flag)];
		}
		constexpr void setFlags(const flagsType flags) noexcept
		{
			for (const auto flag : m_Flags)
				onClearedFlag(flag);
			m_Flags = flags;
			for (const auto flag : flags)
				onSetFlag(flag);
		}
		constexpr const flagsType getFlags() const noexcept
		{
			return m_Flags;
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
			squaresType value{ squaresType::none() };
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
		constexpr void addPiece(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			assert(player.isValid());
			assert(piece.isValid());
			assert(square.isValid());
#if !defined(NDEBUG)
			assert(!m_PlayerOccupancy[player][square]);
			assert(!m_PieceOccupancy[piece][square]);
#endif
			m_PlayerOccupancy[player] += square;
			m_PieceOccupancy[piece] += square;
			onAddedPiece(piece, square, player);
		}
		constexpr void removePiece(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			assert(player.isValid());
			assert(piece.isValid());
			assert(square.isValid());
#if !defined(NDEBUG)
			assert(m_PlayerOccupancy[player][square]);
			assert(m_PieceOccupancy[piece][square]);
#endif
			m_PlayerOccupancy[player] -= square;
			m_PieceOccupancy[piece] -= square;
			onRemovedPiece(piece, square, player);
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
			onClear();
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