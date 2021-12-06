namespace pygmalion
{
	template<typename DESCRIPTOR_STATE, typename INSTANCE>
	class board :
		public DESCRIPTOR_STATE
	{
	public:
		using boardType = INSTANCE;
		using descriptorState = DESCRIPTOR_STATE;
		using materialTableType = state::materialTables<descriptorState, boardType>;
#include "include_state.h"
	private:
		std::array<squaresType, countPieces> m_PieceOccupancy;
		std::array<squaresType, countPlayers> m_PlayerOccupancy;
		cumulationType m_Cumulation;
		hashType m_Hash;
		size_t m_MoveCount;
		size_t m_ReversiblePlyCount;
		scoreType m_Material;
		flagsType m_Flags;
		std::array<piecemaskType, countPlayers> m_PieceMask;
		gamestateType m_Arbitration;
		playerType m_MovingPlayer;
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
		PYGMALION_INLINE static const hashType& playerHash(const playerType player) noexcept
		{
			if constexpr (hasCustomHashing)
				return boardType::customPlayerHash(player);
			else
				return playerType::hash(player);
		}
		PYGMALION_INLINE static const hashType& flagsHash(const flagsType flags) noexcept
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
		PYGMALION_INLINE static const hashType& pieceHash(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			if constexpr (hasCustomHashing)
				return boardType::customPieceHash(piece, square, player);
			else
				return m_PlayerPieceSquareHash[player][piece][square];
		}
		PYGMALION_INLINE void onClear() noexcept
		{
			static_cast<boardType*>(this)->onClear_Implementation();
		}
		PYGMALION_INLINE void onAddedPiece(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			static_cast<boardType*>(this)->onAddedPiece_Implementation(piece, square, player);
		}
		PYGMALION_INLINE void onSetMovingPlayer(const playerType player) noexcept
		{
			static_cast<boardType*>(this)->onSetMovingPlayer_Implementation(player);
		}
		PYGMALION_INLINE void onRemovedPiece(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			static_cast<boardType*>(this)->onRemovedPiece_Implementation(piece, square, player);
		}
		PYGMALION_INLINE void onMovedPiece(const pieceType piece, const squareType from, const squareType to, const playerType player) noexcept
		{
			static_cast<boardType*>(this)->onMovedPiece_Implementation(piece, from, to, player);
		}
		PYGMALION_INLINE void onSetFlag(const flagType& flag) noexcept
		{
			static_cast<boardType*>(this)->onSetFlag_Implementation(flag);
		}
		PYGMALION_INLINE void onClearedFlag(const flagType& flag) noexcept
		{
			static_cast<boardType*>(this)->onClearedFlag_Implementation(flag);
		}
		PYGMALION_INLINE void onInitialize(const materialTableType& materialTable) noexcept
		{
			static_cast<boardType*>(this)->onInitialize_Implementation(materialTable);
		}
		constexpr static bool enableRange(const size_t first, const size_t last) noexcept
		{
			return (first <= last) && (last < countFlags);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType makeSubjectivePacked(const playerType pl, const scoreType score) noexcept
		{
			if constexpr (PLAYER >= countPlayers)
			{
				PYGMALION_ASSERT(false);
				return scoreType::zero();
			}
			else
			{
				constexpr const playerType PL{ static_cast<playerType>(PLAYER) };
				if (pl == PL)
					return boardType::template makeSubjective<PLAYER>(score);
				else
					return makeSubjectivePacked<PLAYER + 1>(pl, score);
			}
			return boardType::template makeSubjective_Implementation<PLAYER>(score);
		}
	public:
		PYGMALION_INLINE piecemaskType pieceMask(const playerType pl) const noexcept
		{
			return m_PieceMask[pl];
		}
		constexpr static size_t countParameters{ materialTableType::countParameters };
		PYGMALION_INLINE scoreType materialAbsolute() const noexcept
		{
			return m_Material;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType makeSubjective(const scoreType score) noexcept
		{
			return boardType::template makeSubjective_Implementation<PLAYER>(score);
		}
		PYGMALION_INLINE static scoreType makeSubjective(const playerType pl, const scoreType score) noexcept
		{
			return makeSubjectivePacked<0>(pl, score);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE scoreType materialRelative() const noexcept
		{
			return this->template makeSubjective<PLAYER>(m_Material);
		}
		PYGMALION_INLINE scoreType materialRelative(const playerType pl) const noexcept
		{
			return makeSubjective(pl, m_Material);
		}
		PYGMALION_INLINE size_t getMoveCount() const noexcept
		{
			return m_MoveCount;
		}
		PYGMALION_INLINE size_t getReversiblePlyCount() const noexcept
		{
			return m_ReversiblePlyCount;
		}
		PYGMALION_INLINE void resetReversiblePlyCount() noexcept
		{
			m_ReversiblePlyCount = 0;
		}
		PYGMALION_INLINE void doReversiblePly() noexcept
		{
			m_ReversiblePlyCount++;
		}
		PYGMALION_INLINE void undoReversiblePly() noexcept
		{
			m_ReversiblePlyCount--;
		}
		PYGMALION_INLINE void doMove() noexcept
		{
			m_MoveCount++;
		}
		PYGMALION_INLINE void undoMove() noexcept
		{
			m_MoveCount--;
		}
		PYGMALION_INLINE void setReversiblePlyCount(const size_t count) noexcept
		{
			m_ReversiblePlyCount = count;
		}
		PYGMALION_INLINE void setMoveCount(const size_t count) noexcept
		{
			m_MoveCount = count;
		}
		PYGMALION_INLINE gamestateType arbitration() const noexcept
		{
			return m_Arbitration;
		}
		PYGMALION_INLINE gamestateType& arbitration() noexcept
		{
			return m_Arbitration;
		}
		PYGMALION_INLINE bool operator==(const boardType& other) const noexcept
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
		PYGMALION_INLINE const hashType& hash() const noexcept
		{
			return m_Hash;
		}
		PYGMALION_INLINE cumulationType& cumulation() noexcept
		{
			return m_Cumulation;
		}
		PYGMALION_INLINE const cumulationType& cumulation() const noexcept
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
		static bool parseFile(const std::string& text, fileType& file, size_t& count) noexcept
		{
			return boardType::parseFile_Implementation(text, file, count);
		}
		static std::string flagToString(const flagType flag) noexcept
		{
			return boardType::flagToString_Implementation(flag);
		}
		static bool parseFlag(const std::string& text, flagType& flag, size_t& count) noexcept
		{
			return boardType::parseFlag_Implementation(text, flag, count);
		}
		static std::string rankToString(const rankType rank) noexcept
		{
			return boardType::rankToString_Implementation(rank);
		}
		static bool parseRank(const std::string& text, rankType& rank, size_t& count) noexcept
		{
			return boardType::parseRank_Implementation(text, rank, count);
		}
		static std::string playerToString(const playerType player) noexcept
		{
			return boardType::playerToString_Implementation(player);
		}
		static bool parsePlayer(const std::string& text, playerType& player, size_t& count) noexcept
		{
			return boardType::parsePlayer_Implementation(text, player, count);
		}
		static std::string pieceToString(const pieceType piece, const playerType player) noexcept
		{
			return boardType::pieceToString_Implementation(piece, player);
		}
		static bool parsePiece(const std::string& text, pieceType& piece, playerType& player, size_t& count) noexcept
		{
			return boardType::parsePiece_Implementation(text, piece, player, count);
		}
		static std::string squareToString(const squareType square) noexcept
		{
			return fileToString(square.file()) + rankToString(square.rank());
		}
		static bool parseSquare(const std::string& text, squareType& square, size_t& count) noexcept
		{
			fileType f;
			std::string temp{ text };
			size_t cnt{ 0 };
			if (parseFile(temp, f, cnt))
			{
				temp = temp.substr(cnt, temp.length() - cnt);
				rankType r;
				if (parseRank(temp, r, cnt))
				{
					count += cnt;
					square = f & r;
					return true;
				}
			}
			return false;
		}
		static std::string flagsToString(const flagsType flags, const playerType movingPlayer) noexcept
		{
			return boardType::flagsToString_Implementation(flags, movingPlayer);
		}
		static bool parseFlags(const std::string& text, flagsType& flags, size_t& count) noexcept
		{
			return boardType::parseFlags_Implementation(text, flags, count);
		}
		PYGMALION_INLINE void setFlag(const flagType flag) noexcept
		{
			if (!m_Flags[flag])
			{
				const flagsType oldFlags{ m_Flags };
				m_Flags.set(flag);
				onSetFlag(flag);
				m_Hash ^= flagsHash(oldFlags) ^ flagsHash(m_Flags);
			}
		}
		PYGMALION_INLINE void toggleFlag(const flagType flag) noexcept
		{
			const flagsType oldFlags{ m_Flags };
			m_Flags.toggle(flag);
			if (m_Flags[flag])
				onSetFlag(flag);
			else
				onClearedFlag(flag);
			m_Hash ^= flagsHash(oldFlags) ^ flagsHash(m_Flags);
		}
		PYGMALION_INLINE void clearFlag(const flagType flag) noexcept
		{
			if (m_Flags[flag])
			{
				const flagsType oldFlags{ m_Flags };
				m_Flags.clear(flag);
				onClearedFlag(flag);
				m_Hash ^= flagsHash(oldFlags) ^ flagsHash(m_Flags);
			}
		}
		PYGMALION_INLINE bool checkFlag(const flagType flag) const noexcept
		{
			return m_Flags[flag];
		}
		PYGMALION_INLINE void setFlags(const flagsType flags) noexcept
		{
			const flagsType oldFlags{ m_Flags };
			for (const auto f : flags & ~m_Flags)
			{
				m_Flags.set(f);
				onSetFlag(f);
			}
			m_Hash ^= flagsHash(oldFlags) ^ flagsHash(m_Flags);
		}
		PYGMALION_INLINE void clearFlags(const flagsType flags) noexcept
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
		PYGMALION_INLINE void clearFlagRange() noexcept
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
		PYGMALION_INLINE void setFlagRange() noexcept
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
		PYGMALION_INLINE void storeFlagRange(const uint_t<1 + LAST - FIRST, false>& flags) noexcept
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
		PYGMALION_INLINE void setMovingPlayer(const playerType movingPlayer) noexcept
		{
			const playerType oldPlayer{ m_MovingPlayer };
			m_MovingPlayer = movingPlayer;
			onSetMovingPlayer(m_MovingPlayer);
			m_Hash ^= playerHash(m_MovingPlayer) ^ playerHash(oldPlayer);
		}
		PYGMALION_INLINE playerType movingPlayer() const noexcept
		{
			return m_MovingPlayer;
		}
		PYGMALION_INLINE const squaresType& pieceOccupancy(const pieceType pc) const noexcept
		{
			PYGMALION_ASSERT(pc.isValid());
			return m_PieceOccupancy[pc];
		}
		PYGMALION_INLINE const squaresType& playerOccupancy(const playerType p) const noexcept
		{
			PYGMALION_ASSERT(p.isValid());
			return m_PlayerOccupancy[p];
		}
		PYGMALION_INLINE squaresType totalOccupancy() const noexcept
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
		PYGMALION_INLINE bool isOccupied(const squareType sq) const noexcept
		{
			PYGMALION_ASSERT(sq.isValid());
			return totalOccupancy()[sq];
		}
		PYGMALION_INLINE bool isOccupied(const squareType sq, const playerType p) const noexcept
		{
			PYGMALION_ASSERT(sq.isValid());
			PYGMALION_ASSERT(p.isValid());
			return playerOccupancy(p)[sq];
		}
		PYGMALION_INLINE void addPiece(const pieceType piece, const squareType square, const playerType player, const materialTableType& materialTable) noexcept
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
			m_Material += materialTable.materialAbsolute(player, piece, square);
			m_PieceMask[player].setPiece(piece);
			onAddedPiece(piece, square, player);
		}
		PYGMALION_INLINE void removePiece(const pieceType piece, const squareType square, const playerType player, const materialTableType& materialTable) noexcept
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
			m_Material -= materialTable.materialAbsolute(player, piece, square);
			const squaresType occ{ m_PlayerOccupancy[player] & m_PieceOccupancy[piece] };
			m_PieceMask[player].setPiece(piece, m_PlayerOccupancy[player] & m_PieceOccupancy[piece]);
			onRemovedPiece(piece, square, player);
		}
		PYGMALION_INLINE void movePiece(const pieceType piece, const squareType from, const squareType to, const playerType player, const materialTableType& materialTable) noexcept
		{
			PYGMALION_ASSERT(player.isValid());
			PYGMALION_ASSERT(piece.isValid());
			PYGMALION_ASSERT(from.isValid());
			PYGMALION_ASSERT(to.isValid());
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_PlayerOccupancy[player][from]);
			PYGMALION_ASSERT(m_PieceOccupancy[piece][from]);
			PYGMALION_ASSERT(!m_PlayerOccupancy[player][to]);
			PYGMALION_ASSERT(!m_PieceOccupancy[piece][to]);
#endif
			m_PlayerOccupancy[player] -= from;
			m_PieceOccupancy[piece] -= from;
			m_PlayerOccupancy[player] |= to;
			m_PieceOccupancy[piece] |= to;
			m_Hash ^= pieceHash(piece, from, player);
			m_Hash ^= pieceHash(piece, to, player);
			m_Material -= materialTable.materialAbsolute(player, piece, from);
			m_Material += materialTable.materialAbsolute(player, piece, to);
			onMovedPiece(piece, from, to, player);
		}
		PYGMALION_INLINE pieceType getPiece(const squareType sq) const noexcept
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
		PYGMALION_INLINE playerType getPlayer(const squareType sq) const noexcept
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
		PYGMALION_INLINE void clear() noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			for (const auto pl : playerType::range)
				m_PlayerOccupancy[pl] = none;
			for (const auto pc : pieceType::range)
				m_PieceOccupancy[pc] = none;
			m_Flags.clear();
			m_MovingPlayer = 0;
			m_Arbitration = gamestateType::open();
			onClear();
			m_Hash = playerHash(m_MovingPlayer) ^ flagsHash(m_Flags);
			m_MoveCount = 0;
			m_ReversiblePlyCount = 0;
			constexpr const scoreType zero{ scoreType::zero() };
			m_Material = zero;
			for (const auto pl : playerType::range)
				m_PieceMask[pl].clear();
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
		void initialize(const materialTableType& materialTable) noexcept
		{
			clear();
			onInitialize(materialTable);
		}
		board(board&&) noexcept = default;
		board(const board&) noexcept = default;
		board& operator=(board&&) noexcept = default;
		board& operator=(const board&) noexcept = default;
		~board() noexcept = default;
		std::string getFen() const noexcept
		{
			std::stringstream fen;
			for (typename rankType::baseType rank = countRanks - 1; rank >= 0; rank--)
			{
				size_t l{ 0 };
				for (typename fileType::baseType file = 0; file < countFiles; file++)
				{
					const squareType square{ fileType(file) & rankType(rank) };
					if (totalOccupancy()[square])
					{
						if (l != 0)
						{
							fen << parser::fromInt(l);
						}
						l = 0;
						const playerType side{ getPlayer(square) };
						const pieceType piece{ getPiece(square) };
						fen << boardType::pieceToString(piece, side);
					}
					else
						l++;
				}
				if (l != 0)
					fen << parser::fromInt(l);
				if (rank != 0)
					fen << "/";
			}
			fen << " ";
			fen << board::playerToString(movingPlayer()) << " ";
			fen << board::flagsToString(flags(), movingPlayer()) << " ";
			fen << parser::fromInt(getReversiblePlyCount()) << " ";
			fen << parser::fromInt(getMoveCount() / 2);
			return fen.str();
		}
		static std::string pieceMaskToString(const piecemaskType& piecemask, const playerType pl) noexcept
		{
			std::stringstream str;
			const std::string nullString{ "_" };
			for (const auto pc : pieceType::range)
			{
				if (piecemask.getPiece(pc))
				{
					const std::string pcString{ boardType::pieceToString(pc,pl) };
					str << pcString;
				}
				else
				{
					str << nullString;
				}
			}
			return str.str();
		}
		bool setFen(const std::string& fen, const materialTableType& materialTable) noexcept
		{
			clear();
			size_t pos{ 0 };
			typename fileType::baseType file{ 0 };
			typename rankType::baseType rank{ static_cast<typename rankType::baseType>(countRanks - 1) };
			bool bParse{ true };
			size_t count{ 0 };
			pieceType piece;
			playerType player;
			while (bParse)
			{
				if (fen.length() <= pos)
				{
					clear();
					return false;
				}
				switch (fen[pos])
				{
				default:
					count = 0;
					if (board::parsePiece(fen.substr(pos, fen.length() - pos), piece, player, count))
					{
						addPiece(piece, fileType(file) & rankType(rank), player, materialTable);
						file++;
					}
					else
					{
						clear();
						return false;
					}
					pos += count;
					break;
				case ' ':
					bParse = false;
					pos++;
					break;
				case '1':
					file++;
					pos++;
					break;
				case '2':
					file += 2;
					pos++;
					break;
				case '3':
					file += 3;
					pos++;
					break;
				case '4':
					file += 4;
					pos++;
					break;
				case '5':
					file += 5;
					pos++;
					break;
				case '6':
					file += 6;
					pos++;
					break;
				case '7':
					file += 7;
					pos++;
					break;
				case '8':
					pos++;
					break;
				case '/':
					file = 0;
					rank--;
					pos++;
					break;
				}
				if (file < 0)
					break;
			}
			if (fen.length() <= pos)
			{
				clear();
				return false;
			}
			count = 0;
			if (!board::parsePlayer(fen.substr(pos, fen.length() - pos), player, count))
			{
				clear();
				return false;
			}
			pos += count;
			setMovingPlayer(player);
			if (fen.length() <= pos)
			{
				clear();
				return false;
			}
			if (fen[pos] != ' ')
			{
				clear();
				return false;
			}
			pos++;
			if (fen.length() <= pos)
			{
				clear();
				return false;
			}
			count = 0;
			if (!board::parseFlags(fen.substr(pos, fen.length() - pos), m_Flags, count))
			{
				clear();
				return false;
			}
			pos += count;
			if (fen[pos] != ' ')
			{
				clear();
				return false;
			}
			pos++;
			std::string revCountStr = "";
			std::string remainder;
			parser::parseToken(parser::trimString(fen.substr(pos, fen.length() - pos)), revCountStr, remainder);
			if (revCountStr != "")
				setReversiblePlyCount(static_cast<size_t>(parser::parseInt(revCountStr)));
			else
			{
				clear();
				return false;
			}
			std::string mvCountStr = "";
			std::string remainder2;
			parser::parseToken(remainder, mvCountStr, remainder2);
			if (mvCountStr != "")
				setMoveCount(static_cast<size_t>(2 * parser::parseInt(mvCountStr)) + (static_cast<size_t>(player) == (countPlayers - 1)));
			else
			{
				clear();
				return false;
			}
			return true;
		}
		PYGMALION_INLINE static scoreType defaultLazyMaterial(const pieceType pc) noexcept
		{
			return boardType::defaultLazyMaterial_Implementation(pc);
		}
		PYGMALION_INLINE static scoreType defaultMaterial(const playerType pl, const pieceType pc, const squareType sq) noexcept
		{
			return boardType::defaultMaterial_Implementation(pl, pc, sq);
		}
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