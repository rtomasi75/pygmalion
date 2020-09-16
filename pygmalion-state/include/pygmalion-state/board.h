namespace pygmalion
{
	template<typename DESCRIPTOR_STATE, typename INSTANCE>
	class board :
		public DESCRIPTOR_STATE
	{
	public:
		using boardType = INSTANCE;
		using descriptorState = DESCRIPTOR_STATE;
#include "include_state.h"
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
		void onSetMovingPlayer(const playerType player) noexcept
		{
			reinterpret_cast<boardType*>(this)->onSetMovingPlayer_Implementation(player);
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
		void onInitialize() noexcept
		{
			reinterpret_cast<boardType*>(this)->onInitialize_Implementation();
		}
	public:
		static std::string fileToString(const fileType file) noexcept
		{
			return boardType::fileToString_Implementation(file);
		}
		static bool parseFile(const std::string& text, fileType& file, size_t& len) noexcept
		{
			return boardType::parseFile_Implementation(text, file, len);
		}
		static std::string flagToString(const flagType flag) noexcept
		{
			return boardType::flagToString_Implementation(flag);
		}
		static bool parseFlag(const std::string& text, flagType& flag, size_t& len) noexcept
		{
			return boardType::parseFlag_Implementation(text, flag, len);
		}
		static std::string rankToString(const rankType rank) noexcept
		{
			return boardType::rankToString_Implementation(rank);
		}
		static bool parseRank(const std::string& text, rankType& rank, size_t& len) noexcept
		{
			return boardType::parseRank_Implementation(text, rank, len);
		}
		static std::string playerToString(const playerType player) noexcept
		{
			return boardType::playerToString_Implementation(player);
		}
		static bool parsePlayer(const std::string& text, playerType& player, size_t& len) noexcept
		{
			return boardType::parsePlayer_Implementation(text, player, len);
		}
		static std::string pieceToString(const pieceType piece, const playerType player) noexcept
		{
			return boardType::pieceToString_Implementation(piece, player);
		}
		static std::string pieceToString(const pieceType piece) noexcept
		{
			return boardType::pieceToString_Implementation(piece);
		}
		static bool parsePiece(const std::string& text, pieceType& piece, size_t& len) noexcept
		{
			return boardType::parsePiece_Implementation(text, piece, len);
		}
		static std::string squareToString(const squareType square) noexcept
		{
			return fileToString(square.file()) + rankToString(square.rank());
		}
		static bool parseSquare(const std::string& text, squareType& square, size_t& len) noexcept
		{
			size_t ln{ 0 };
			fileType f;
			if (parseFile(text, f, ln))
			{
				rankType r;
				if (parseRank(text.substr(1, text.length() - 1), r, ln))
				{
					len += ln;
					square = f & r;
					return true;
				}
			}
			return false;
		}
		constexpr void setFlag(const flagType flag) noexcept
		{
			m_Flags.set(flag);
			onSetFlag(flag);
		}
		constexpr void toggleFlag(const flagType flag) noexcept
		{
			m_Flags.toggle(flag);
			if (m_Flags[flag])
				onSetFlag(flag);
			else
				onClearedFlag(flag);
		}
		constexpr void clearFlag(const flagType flag) noexcept
		{
			m_Flags.clear(flag);
			onClearedFlag(flag);
		}
		constexpr bool checkFlag(const flagType flag) const noexcept
		{
			return m_Flags[flag];
		}
		constexpr void setFlags(const flagsType flags) noexcept
		{
			for (const auto flag : m_Flags)
				onClearedFlag(flag);
			m_Flags = flags;
			for (const auto flag : flags)
				onSetFlag(flag);
		}
		constexpr const flagsType flags() const noexcept
		{
			return m_Flags;
		}
		constexpr void setMovingPlayer(const playerType movingPlayer) noexcept
		{
			assert(movingPlayer.isValid());
			m_MovingPlayer = movingPlayer;
			onSetMovingPlayer(m_MovingPlayer);
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
		constexpr flagsType& flags() noexcept
		{
			return m_Flags;
		}
		constexpr squaresType totalOccupancy() const noexcept
		{
			squaresType value{ squaresType::none() };
			if constexpr (countPlayers < countPieces)
			{
				for (const auto p : playerType::range)
					value |= m_PlayerOccupancy[p];
			}
			else
			{
				for (const auto pc : pieceType::range)
					value |= m_PieceOccupancy[pc];
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
			m_PlayerOccupancy[player] |= square;
			m_PieceOccupancy[piece] |= square;
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
		constexpr playerType getPlayer(const squareType sq) const noexcept
		{
			assert(sq.isValid());
			assert(totalOccupancy()[sq]);
			playerType p{ 0 };
			for (const auto i : playerType::range)
				p = p | m_PlayerOccupancy[i][sq] * i;
			return p;
		}
		constexpr void clear() noexcept
		{
			for (const auto p : playerType::range)
				m_PlayerOccupancy[p] = squaresType::none();
			for (const auto pc : pieceType::range)
				m_PieceOccupancy[pc] = squaresType::none();
			m_Flags.clear();
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
		constexpr void initialize() noexcept
		{
			clear();
			onInitialize();
		}
		constexpr board(board&&) noexcept = default;
		constexpr board(const board&) noexcept = default;
		constexpr board& operator=(board&&) noexcept = default;
		constexpr board& operator=(const board&) noexcept = default;
		~board() noexcept = default;
	};
}