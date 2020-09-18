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
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "generic board, " << countFiles << "x" << countRanks << " square" << (countSquares != 1 ? "s" : "") << ", " << countPlayers << " player" << (countPlayers != 1 ? "s" : "") << ", " << countFlags << " flag" << (countFlags != 1 ? "s" : "");
			return sstr.str();
		}
		static std::string name() noexcept
		{
			return boardType::name_Implementation();
		}
		static std::string fileToString(const fileType file) noexcept
		{
			return boardType::fileToString_Implementation(file);
		}
		static bool parseFile(std::string& text, fileType& file) noexcept
		{
			return boardType::parseFile_Implementation(text, file);
		}
		static std::string flagToString(const flagType flag) noexcept
		{
			return boardType::flagToString_Implementation(flag);
		}
		static bool parseFlag(std::string& text, flagType& flag) noexcept
		{
			return boardType::parseFlag_Implementation(text, flag);
		}
		static std::string rankToString(const rankType rank) noexcept
		{
			return boardType::rankToString_Implementation(rank);
		}
		static bool parseRank(std::string& text, rankType& rank) noexcept
		{
			return boardType::parseRank_Implementation(text, rank);
		}
		static std::string playerToString(const playerType player) noexcept
		{
			return boardType::playerToString_Implementation(player);
		}
		static bool parsePlayer(std::string& text, playerType& player) noexcept
		{
			return boardType::parsePlayer_Implementation(text, player);
		}
		static std::string pieceToString(const pieceType piece, const playerType player) noexcept
		{
			return boardType::pieceToString_Implementation(piece, player);
		}
		static bool parsePiece(std::string& text, pieceType& piece, playerType& player) noexcept
		{
			return boardType::parsePiece_Implementation(text, piece, player);
		}
		static std::string squareToString(const squareType square) noexcept
		{
			return fileToString(square.file()) + rankToString(square.rank());
		}
		static bool parseSquare(std::string& text, squareType& square) noexcept
		{
			fileType f;
			if (parseFile(text, f))
			{
				rankType r;
				if (parseRank(text, r))
				{
					square = f & r;
					return true;
				}
			}
			return false;
		}
		constexpr void setFlag(const flagType flag) noexcept
		{
			if (!m_Flags[flag])
			{
				m_Flags.set(flag);
				onSetFlag(flag);
			}
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
			if (m_Flags[flag])
			{
				m_Flags.clear(flag);
				onClearedFlag(flag);
			}
		}
		constexpr bool checkFlag(const flagType flag) const noexcept
		{
			return m_Flags[flag];
		}
		constexpr void setFlags(const flagsType flags) noexcept
		{
			for (const auto f : flags & ~m_Flags)
			{
				m_Flags.set(f);
				onSetFlag(f);
			}
		}
		constexpr void clearFlags(const flagsType flags) noexcept
		{
			for (const auto f : flags & m_Flags)
			{
				m_Flags.clear(f);
				onClearedFlag(f);
			}
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
			m_Flags{ flagsType(0) }
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

	template<typename DESCRIPTOR_STATE, typename INSTANCE>
	std::ostream& operator<<(std::ostream& str, const board<DESCRIPTOR_STATE, INSTANCE>& position) noexcept
	{
		using boardType = INSTANCE;
		using descriptorState = DESCRIPTOR_STATE;
#include "include_state.h"
		for (const auto r : rankType::range)
		{
			const rankType rank{ -r };
			str << boardType::rankToString(rank) << "|";
			for (const auto file : fileType::range)
			{
				const squareType square{ rank & file };
				if (position.totalOccupancy()[square])
				{
					const pieceType piece{ position.getPiece(square) };
					const playerType player{ position.getPlayer(square) };
					str << boardType::pieceToString(piece, player);
				}
				else
					str << ".";
			}
			str << std::endl;
		}
		str << "-+";
		for (const auto file : fileType::range)
		{
			str << "-";
		}
		str << std::endl;
		str << " |";
		for (const auto file : fileType::range)
		{
			str << boardType::fileToString(file);
		}
		str << std::endl;
		if constexpr (countFlags > 0)
		{
			str << std::endl;
			str << "Flags: ";
			for (const auto flag : flagType::range)
			{
				if (position.checkFlag(flag))
					str << boardType::flagToString(flag);
				else
					str << "_";
			}
			str << std::endl;
		}
		str << std::endl;
		str << "Player " << boardType::playerToString(position.movingPlayer()) << " is on the move." << std::endl;
		return str;
	}
}