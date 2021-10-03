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
		gamestateType m_Arbitration;
		flagsType m_Flags;
		hashType m_Hash;
		cumulationType m_Cumulation;
		signatureType m_Signature;
		static const inline std::array<hashType, countPlayers* countPieces* countSquares> m_HashTable{ arrayhelper::generate< countPlayers* countPieces* countSquares ,hashType>([](const size_t index) {return hashType::random(); }) };
		constexpr static size_t requiredUnsignedBits(const size_t number) noexcept
		{
			size_t n = 1;
			size_t k = 0;
			while (number > n)
			{
				n *= 2;
				k++;
			}
			return k;
		}
	protected:
		constexpr static const hashType& playerHash(const playerType player) noexcept
		{
			return playerType::hash(player);
		}
		constexpr static const hashType& flagHash(const flagType flag) noexcept
		{
			return flagType::hash(flag);
		}
		constexpr static hashType pieceHash(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			//	return pieceType::hash(piece) ^ squareType::hash(square) ^ playerType::hash(player);
			return m_HashTable[static_cast<size_t>(player) * countSquares * countPieces + static_cast<size_t>(piece) * countSquares + static_cast<size_t>(square)];
		}
		void onClear() noexcept
		{
			m_Hash = playerHash(m_MovingPlayer);
			static_cast<boardType*>(this)->onClear_Implementation();
		}
		void onAddedPiece(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			m_Hash ^= pieceHash(piece, square, player);
			static_cast<boardType*>(this)->onAddedPiece_Implementation(piece, square, player);
		}
		void onSetMovingPlayer(const playerType player) noexcept
		{
			m_Hash ^= playerHash(m_MovingPlayer);
			static_cast<boardType*>(this)->onSetMovingPlayer_Implementation(player);
		}
		void onRemovedPiece(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			m_Hash ^= pieceHash(piece, square, player);
			static_cast<boardType*>(this)->onRemovedPiece_Implementation(piece, square, player);
		}
		void onSetFlag(const flagType& flag) noexcept
		{
			m_Hash ^= flagHash(flag);
			static_cast<boardType*>(this)->onSetFlag_Implementation(flag);
		}
		void onClearedFlag(const flagType& flag) noexcept
		{
			m_Hash ^= flagHash(flag);
			static_cast<boardType*>(this)->onClearedFlag_Implementation(flag);
		}
		void onInitialize() noexcept
		{
			static_cast<boardType*>(this)->onInitialize_Implementation();
		}
		constexpr static bool enableRange(const size_t first, const size_t last) noexcept
		{
			return (first <= last) && (last < countFlags);
		}
	public:
		const signatureType& signature() const noexcept
		{
			return m_Signature;
		}
		constexpr gamestateType arbitration() const noexcept
		{
			return m_Arbitration;
		}
		constexpr gamestateType& arbitration() noexcept
		{
			return m_Arbitration;
		}
		constexpr bool operator==(const boardType& other) const noexcept
		{
			if (m_Hash != other.m_Hash)
				return false;
			for (const auto pc : pieceType::range)
			{
				if (m_PieceOccupancy[pc] != other.m_PieceOccupancy[pc])
					return false;
			}
			for (const auto pl : playerType::range)
			{
				if (m_PlayerOccupancy[pl] != other.m_PlayerOccupancy[pl])
					return false;
			}
			if (m_Flags != other.m_Flags)
				return false;
			return true;
		}
		constexpr const hashType hash() const noexcept
		{
			return m_Hash;
		}
		constexpr cumulationType& cumulation() noexcept
		{
			return m_Cumulation;
		}
		constexpr const cumulationType& cumulation() const noexcept
		{
			return m_Cumulation;
		}
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
		static std::string cumulationToString(const cumulationType& cumulation)
		{
			return boardType::cumulationToString_Implementation(cumulation);
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
			std::string temp{ text };
			if (parseFile(temp, f))
			{
				rankType r;
				if (parseRank(temp, r))
				{
					square = f & r;
					text = temp;
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
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<board::enableRange(FIRST, LAST)>::type>
		constexpr void clearFlagRange() noexcept
		{
			for (const auto f : m_Flags.template extractRange<FIRST, LAST>())
			{
				onClearedFlag(f);
			}
			m_Flags.template clearRange<FIRST, LAST>();
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<board::enableRange(FIRST, LAST)>::type>
		constexpr void setFlagRange() noexcept
		{
			for (const auto f : ~m_Flags.template extractRange<FIRST, LAST>())
			{
				onSetFlag(f);
			}
			m_Flags.template setRange<FIRST, LAST>();
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<board::enableRange(FIRST, LAST)>::type>
		constexpr uint_t<1 + LAST - FIRST, false> extractFlagRange() const noexcept
		{
			return m_Flags.template extractRange<FIRST, LAST>();
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<board::enableRange(FIRST, LAST)>::type>
		constexpr void storeFlagRange(const uint_t<1 + LAST - FIRST, false>& flags) noexcept
		{
			flagsType oldFlags{ m_Flags };
			m_Flags.template storeRange<FIRST, LAST>(flags);
			for (const auto f : oldFlags ^ m_Flags)
			{
				if (m_Flags[f])
					onSetFlag(f);
				else
					onClearedFlag(f);
			}
		}
		constexpr const flagsType flags() const noexcept
		{
			return m_Flags;
		}
		constexpr void setMovingPlayer(const playerType movingPlayer) noexcept
		{
			PYGMALION_ASSERT(movingPlayer.isValid());
			m_Hash ^= playerHash(m_MovingPlayer);
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
			PYGMALION_ASSERT(pc.isValid());
			return m_PieceOccupancy[pc];
		}
		constexpr squaresType& pieceOccupancy(const pieceType pc) noexcept
		{
			PYGMALION_ASSERT(pc.isValid());
			return m_PieceOccupancy[pc];
		}
		constexpr const squaresType& playerOccupancy(const playerType p) const noexcept
		{
			PYGMALION_ASSERT(p.isValid());
			return m_PlayerOccupancy[p];
		}
		constexpr squaresType& playerOccupancy(const playerType p) noexcept
		{
			PYGMALION_ASSERT(p.isValid());
			return m_PlayerOccupancy[p];
		}
		constexpr squaresType totalOccupancy() const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType value{ none };
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
			PYGMALION_ASSERT(sq.isValid());
			return totalOccupancy()[sq];
		}
		constexpr bool isOccupied(const squareType sq, const playerType p) const noexcept
		{
			PYGMALION_ASSERT(sq.isValid());
			PYGMALION_ASSERT(p.isValid());
			return playerOccupancy(p)[sq];
		}
		constexpr void addPiece(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			PYGMALION_ASSERT(player.isValid());
			PYGMALION_ASSERT(piece.isValid());
			PYGMALION_ASSERT(square.isValid());
#if !defined(NDEBUG)
			PYGMALION_ASSERT(!m_PlayerOccupancy[player][square]);
			PYGMALION_ASSERT(!m_PieceOccupancy[piece][square]);
#endif
			m_PlayerOccupancy[player] |= square;
			m_PieceOccupancy[piece] |= square;
			m_Signature.addPiece(piece, player);
			onAddedPiece(piece, square, player);
		}
		constexpr void removePiece(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			PYGMALION_ASSERT(player.isValid());
			PYGMALION_ASSERT(piece.isValid());
			PYGMALION_ASSERT(square.isValid());
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_PlayerOccupancy[player][square]);
			PYGMALION_ASSERT(m_PieceOccupancy[piece][square]);
#endif
			m_PlayerOccupancy[player] -= square;
			m_PieceOccupancy[piece] -= square;
			m_Signature.removePiece(piece, player);
			onRemovedPiece(piece, square, player);
		}
		constexpr pieceType getPiece(const squareType sq) const noexcept
		{
			PYGMALION_ASSERT(sq.isValid());
			PYGMALION_ASSERT(totalOccupancy()[sq]);
			for (const auto pc : pieceType::range)
			{
				if (m_PieceOccupancy[pc][sq])
					return pc;
			}
			PYGMALION_ASSERT(false);
			return pieceType::invalid;
		}
		constexpr playerType getPlayer(const squareType sq) const noexcept
		{
			PYGMALION_ASSERT(sq.isValid());
			PYGMALION_ASSERT(totalOccupancy()[sq]);
			for (const auto p : playerType::range)
			{
				if (m_PlayerOccupancy[p][sq])
					return p;
			}
			PYGMALION_ASSERT(false);
			return playerType::invalid;
		}
		constexpr void clear() noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			for (const auto p : playerType::range)
				m_PlayerOccupancy[p] = none;
			for (const auto pc : pieceType::range)
				m_PieceOccupancy[pc] = none;
			m_Flags.clear();
			m_MovingPlayer = 0;
			m_Arbitration = gamestateType::open();
			m_Signature.clear();
			onClear();
		}
		constexpr board() noexcept :
			m_PieceOccupancy{ },
			m_PlayerOccupancy{ },
			m_MovingPlayer{ 0 },
			m_Flags{ flagsType(0) },
			m_Arbitration{ gamestateType::open() }
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
		str << "Hash: ";
		str << position.hash();
		str << std::endl;
		str << "Cumulation: ";
		str << boardType::cumulationToString(position.cumulation());
		str << std::endl;
		str << "Player " << boardType::playerToString(position.movingPlayer()) << " is on the move." << std::endl;
		return str;
	}
}