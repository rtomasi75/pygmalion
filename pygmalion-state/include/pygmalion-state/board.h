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
		static inline std::array<hashType, 1 << flagType::countValues> m_FlagsHash
		{
			arrayhelper::generate<1 << flagType::countValues,hashType>([](const size_t index)
				{
					const flagsType flags{flagsType(static_cast<uintmax_t>(index))};
					hashType hash{hashType(0)};
					for (size_t i = 0; i < flagType::countValues; i++)
					{
						if (flags[i])
							hash ^= flagType::hash(i);
					}
					return hash;
				})
		};
		static inline std::array<std::array<std::array<hashType, countSquares>, countPieces>, countPlayers> m_PlayerPieceSquareHash
		{
			arrayhelper::generate<countPlayers, std::array<std::array<hashType, countSquares>, countPieces>>([](const size_t player) { return arrayhelper::generate<countPieces, std::array<hashType, countSquares>>([player](const size_t piece) {return arrayhelper::generate<countSquares, hashType>([player, piece](const size_t square) {return pieceType::hash(static_cast<pieceType>(piece)) ^ squareType::hash(static_cast<squareType>(square)) ^ playerType::hash(static_cast<playerType>(player)); }); }); })
		};
	protected:
		static const hashType& playerHash(const playerType player) noexcept
		{
			if constexpr (hasCustomHashing)
				return boardType::customPlayerHash(player);
			else
				return playerType::hash(player);
		}
		static const hashType& flagsHash(const flagsType flags) noexcept
		{
			if constexpr (hasCustomHashing)
				return boardType::customFlagsHash(flags);
			else
			{
				const typename flagsType::bitsType bits{ flags.bits() };
				const size_t index{ static_cast<size_t>(static_cast<std::uintmax_t>(bits)) };
				return m_FlagsHash[index];
			}
		}
		static const hashType& pieceHash(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			if constexpr (hasCustomHashing)
				return boardType::customPieceHash(piece, square, player);
			else
				return m_PlayerPieceSquareHash[player][piece][square];
		}
		void onClear() noexcept
		{
			static_cast<boardType*>(this)->onClear_Implementation();
		}
		void onAddedPiece(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			static_cast<boardType*>(this)->onAddedPiece_Implementation(piece, square, player);
		}
		void onSetMovingPlayer(const playerType player) noexcept
		{
			static_cast<boardType*>(this)->onSetMovingPlayer_Implementation(player);
		}
		void onRemovedPiece(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			static_cast<boardType*>(this)->onRemovedPiece_Implementation(piece, square, player);
		}
		void onSetFlag(const flagType& flag) noexcept
		{
			static_cast<boardType*>(this)->onSetFlag_Implementation(flag);
		}
		void onClearedFlag(const flagType& flag) noexcept
		{
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
		gamestateType arbitration() const noexcept
		{
			return m_Arbitration;
		}
		gamestateType& arbitration() noexcept
		{
			return m_Arbitration;
		}
		bool operator==(const boardType& other) const noexcept
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
		const hashType hash() const noexcept
		{
			return m_Hash;
		}
		cumulationType& cumulation() noexcept
		{
			return m_Cumulation;
		}
		const cumulationType& cumulation() const noexcept
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
		void setFlag(const flagType flag) noexcept
		{
			if (!m_Flags[flag])
			{
				const flagsType oldFlags{ m_Flags };
				m_Flags.set(flag);
				onSetFlag(flag);
				m_Hash ^= flagsHash(oldFlags) ^ flagsHash(m_Flags);
			}
		}
		void toggleFlag(const flagType flag) noexcept
		{
			const flagsType oldFlags{ m_Flags };
			m_Flags.toggle(flag);
			if (m_Flags[flag])
				onSetFlag(flag);
			else
				onClearedFlag(flag);
			m_Hash ^= flagsHash(oldFlags) ^ flagsHash(m_Flags);
		}
		void clearFlag(const flagType flag) noexcept
		{
			if (m_Flags[flag])
			{
				const flagsType oldFlags{ m_Flags };
				m_Flags.clear(flag);
				onClearedFlag(flag);
				m_Hash ^= flagsHash(oldFlags) ^ flagsHash(m_Flags);
			}
		}
		bool checkFlag(const flagType flag) const noexcept
		{
			return m_Flags[flag];
		}
		void setFlags(const flagsType flags) noexcept
		{
			const flagsType oldFlags{ m_Flags };
			for (const auto f : flags & ~m_Flags)
			{
				m_Flags.set(f);
				onSetFlag(f);
			}
			m_Hash ^= flagsHash(oldFlags) ^ flagsHash(m_Flags);
		}
		void clearFlags(const flagsType flags) noexcept
		{
			const flagsType oldFlags{ m_Flags };
			for (const auto f : flags & m_Flags)
			{
				m_Flags.clear(f);
				onClearedFlag(f);
			}
			m_Hash ^= flagsHash(oldFlags) ^ flagsHash(m_Flags);
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<board::enableRange(FIRST, LAST)>::type>
		void clearFlagRange() noexcept
		{
			flagsType oldFlags{ m_Flags };
			for (const auto f : m_Flags.template extractRange<FIRST, LAST>())
			{
				onClearedFlag(f);
			}
			m_Flags.template clearRange<FIRST, LAST>();
			m_Hash ^= flagsHash(oldFlags) ^ flagsHash(m_Flags);
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<board::enableRange(FIRST, LAST)>::type>
		void setFlagRange() noexcept
		{
			flagsType oldFlags{ m_Flags };
			for (const auto f : ~m_Flags.template extractRange<FIRST, LAST>())
			{
				onSetFlag(f);
			}
			m_Flags.template setRange<FIRST, LAST>();
			m_Hash ^= flagsHash(oldFlags) ^ flagsHash(m_Flags);
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<board::enableRange(FIRST, LAST)>::type>
		uint_t<1 + LAST - FIRST, false> extractFlagRange() const noexcept
		{
			return m_Flags.template extractRange<FIRST, LAST>();
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<board::enableRange(FIRST, LAST)>::type>
		void storeFlagRange(const uint_t<1 + LAST - FIRST, false>& flags) noexcept
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
			m_Hash ^= flagsHash(oldFlags) ^ flagsHash(m_Flags);
		}
		const flagsType flags() const noexcept
		{
			return m_Flags;
		}
		void setMovingPlayer(const playerType movingPlayer) noexcept
		{
			const playerType oldPlayer{ m_MovingPlayer };
			m_MovingPlayer = movingPlayer;
			onSetMovingPlayer(m_MovingPlayer);
			m_Hash ^= playerHash(m_MovingPlayer) ^ playerHash(oldPlayer);
		}
		playerType movingPlayer() const noexcept
		{
			return m_MovingPlayer;
		}
		const squaresType& pieceOccupancy(const pieceType pc) const noexcept
		{
			PYGMALION_ASSERT(pc.isValid());
			return m_PieceOccupancy[pc];
		}
		const squaresType& playerOccupancy(const playerType p) const noexcept
		{
			PYGMALION_ASSERT(p.isValid());
			return m_PlayerOccupancy[p];
		}
		squaresType totalOccupancy() const noexcept
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
		bool isOccupied(const squareType sq) const noexcept
		{
			PYGMALION_ASSERT(sq.isValid());
			return totalOccupancy()[sq];
		}
		bool isOccupied(const squareType sq, const playerType p) const noexcept
		{
			PYGMALION_ASSERT(sq.isValid());
			PYGMALION_ASSERT(p.isValid());
			return playerOccupancy(p)[sq];
		}
		void addPiece(const pieceType piece, const squareType square, const playerType player) noexcept
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
			m_Hash ^= pieceHash(piece, square, player);
			onAddedPiece(piece, square, player);
		}
		void removePiece(const pieceType piece, const squareType square, const playerType player) noexcept
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
			m_Hash ^= pieceHash(piece, square, player);
			onRemovedPiece(piece, square, player);
		}
		pieceType getPiece(const squareType sq) const noexcept
		{
			PYGMALION_ASSERT(sq.isValid());
			PYGMALION_ASSERT(totalOccupancy()[sq]);
			if constexpr (countPieces < 8)
			{
				typename pieceType::baseType result{ typename pieceType::baseType(0) };
				for (const auto pc : pieceType::range)
				{
					const bool bHit{ m_PieceOccupancy[pc][sq] };
					result |= bHit * static_cast<typename pieceType::baseType>(pc);
				}
				return static_cast<pieceType>(result);
			}
			else
			{
				for (const auto pc : pieceType::range)
				{
					if (m_PieceOccupancy[pc][sq])
						return pc;
				}
				PYGMALION_ASSERT(false);
				return pieceType::invalid;
			}
		}
		playerType getPlayer(const squareType sq) const noexcept
		{
			PYGMALION_ASSERT(sq.isValid());
			PYGMALION_ASSERT(totalOccupancy()[sq]);
			if constexpr (countPlayers < 8)
			{
				typename playerType::baseType result{ typename playerType::baseType(0) };
				for (const auto p : playerType::range)
				{
					const bool bHit{ m_PlayerOccupancy[p][sq] };
					result |= bHit * static_cast<typename playerType::baseType>(p);
				}
				return static_cast<playerType>(result);
			}
			else
			{
				for (const auto p : playerType::range)
				{
					if (m_PlayerOccupancy[p][sq])
						return p;
				}
				PYGMALION_ASSERT(false);
				return playerType::invalid;
			}
		}
		void clear() noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			for (const auto p : playerType::range)
				m_PlayerOccupancy[p] = none;
			for (const auto pc : pieceType::range)
				m_PieceOccupancy[pc] = none;
			m_Flags.clear();
			m_MovingPlayer = 0;
			m_Arbitration = gamestateType::open();
			onClear();
			m_Hash = playerHash(m_MovingPlayer) ^ flagsHash(m_Flags);
		}
		board() noexcept :
			m_PieceOccupancy{ },
			m_PlayerOccupancy{ },
			m_MovingPlayer{ 0 },
			m_Flags{ flagsType(0) },
			m_Arbitration{ gamestateType::open() }
		{
			clear();
		}
		void initialize() noexcept
		{
			clear();
			onInitialize();
		}
		board(board&&) noexcept = default;
		board(const board&) noexcept = default;
		board& operator=(board&&) noexcept = default;
		board& operator=(const board&) noexcept = default;
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