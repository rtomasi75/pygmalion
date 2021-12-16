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
		hashType m_Hash;
		hashType m_StructureHash;
		size_t m_MoveCount;
		size_t m_ReversiblePlyCount;
		objectiveType m_Material;
		squaresType m_EnPassantSquares;
		squareType m_EnPassantVictim;
		flagsType m_Flags;
		playerpiecesType m_PlayerPieces;
		gamestateType m_Arbitration;
		playerType m_MovingPlayer;
		constexpr static inline std::array<hashType, countPlayers> m_MovingPlayerHash
		{
			arrayhelper::generate<countPlayers,hashType>([](const size_t playerIndex) { return hashType(boardInfo.movingPlayerHash[playerIndex]); })
		};
		constexpr static inline std::array<hashType, countSquares> m_EnPassantHash
		{
			arrayhelper::generate<countSquares,hashType>([](const size_t squareIndex) { return hashType(boardInfo.enPassantHash[squareIndex]); })
		};
		constexpr static inline std::array<hashType, 1 << flagType::countValues> m_FlagsHash
		{
			arrayhelper::generate<1 << flagType::countValues,hashType>([](const size_t index)
				{
					return boardInfo.flagHash[index];
				})
		};
		constexpr static inline std::array<std::array<std::array<hashType, countSquares>, countPieces>, countPlayers> m_PlayerPieceSquareHash
		{
			arrayhelper::generate<countPlayers, std::array<std::array<hashType, countSquares>, countPieces>>([](const size_t player) { return arrayhelper::generate<countPieces, std::array<hashType, countSquares>>([player](const size_t piece) {return arrayhelper::generate<countSquares, hashType>([player, piece](const size_t square) {return boardInfo.playerPieceSquareHash[player][piece][square]; }); }); })
		};
	protected:
		PYGMALION_INLINE static const hashType playerHash(const playerType player) noexcept
		{
			return m_MovingPlayerHash[player];
		}
		PYGMALION_INLINE static const hashType flagsHash(const flagsType flags) noexcept
		{
			return m_FlagsHash[flags.toIndex()];
		}
		PYGMALION_INLINE static const hashType pieceHash(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			return m_PlayerPieceSquareHash[player][piece][square];
		}
		PYGMALION_INLINE static const hashType enPassantHash(const squareType square) noexcept
		{
			return m_EnPassantHash[square];
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
		hashType theoreticalHash() const noexcept
		{
			constexpr const flagsType noFlags{ flagsType::none() };
			hashType hash{ hashType(0) };
			hash ^= playerHash(m_MovingPlayer);
			hash ^= flagsHash(m_Flags);
			for (const auto pl : playerType::range)
			{
				for (const auto pc : pieceType::range)
				{
					for (const auto sq : playerOccupancy(pl)& pieceOccupancy(pc))
						hash ^= pieceHash(pc, sq, pl);
				}
			}
			for (const auto sq : enPassantTargets())
				hash ^= enPassantHash(sq);
			return hash;
		}
		PYGMALION_INLINE bool operator==(const boardType& other) const noexcept
		{
			for (const auto pl : playerType::range)
			{
				if (playerOccupancy(pl) != other.playerOccupancy(pl))
					return false;
			}
			for (const auto pc : pieceType::range)
			{
				if (pieceOccupancy(pc) != other.pieceOccupancy(pc))
					return false;
			}
			if (this->flags() != other.flags())
				return false;
			if (this->enPassantTargets() != other.enPassantTargets())
				return false;
			if (this->enPassantVictim() != other.enPassantVictim())
				return false;
			if (this->getReversiblePlyCount() != other.getReversiblePlyCount())
				return false;
			if (this->getMoveCount() != other.getMoveCount())
				return false;
			if (this->movingPlayer() != other.movingPlayer())
				return false;
			if (this->hash() != other.hash())
				return false;
			if (this->material() != other.material())
				return false;
			if (this->playerpieces() != other.playerpieces())
				return false;
			if (this->arbitration() != other.arbitration())
				return false;
			return true;
		}
		PYGMALION_INLINE bool operator!=(const boardType& other) const noexcept
		{
			for (const auto pl : playerType::range)
			{
				if (playerOccupancy(pl) != other.playerOccupancy(pl))
					return true;
			}
			for (const auto pc : pieceType::range)
			{
				if (pieceOccupancy(pl) != other.pieceOccupancy(pl))
					return true;
			}
			if (this->flags() != other.flags())
				return true;
			if (this->enPassantSquares() != other.enPassantSquares())
				return true;
			if (this->getReversiblePlyCount() != other.getReversiblePlayCount())
				return true;
			if (this->getMoveCount() != other.getMoveCount())
				return true;
			if (this->movingPlayer() != other.movingPlayer())
				return true;
			if (this->cumulation() != other.cumulation())
				return true;
			if (this->hash() != other.hash())
				return true;
			if (this->material() != other.material())
				return true;
			if (this->playerpieces() != other.playerpieces())
				return true;
			if (this->arbitration() != other.arbitration())
				return true;
			return false;
		}
		PYGMALION_INLINE const squaresType& enPassantTargets() const noexcept
		{
			return m_EnPassantSquares;
		}
		PYGMALION_INLINE const squareType& enPassantVictim() const noexcept
		{
			return m_EnPassantVictim;
		}
		PYGMALION_INLINE bool checkEnPassantTarget(const squareType sq) const noexcept
		{
			return m_EnPassantSquares[sq];
		}
		PYGMALION_INLINE bool checkEnPassantVictim(const squareType sq) const noexcept
		{
			return m_EnPassantVictim == sq;
		}
		PYGMALION_INLINE void clearEnPassant() noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			for (const auto sq : m_EnPassantSquares)
				m_Hash ^= enPassantHash(sq);
			m_EnPassantSquares.clear();
			m_EnPassantVictim = squareType::invalid;
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		PYGMALION_INLINE void setEnPassant(const squaresType targets, const squareType victim) noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			for (const auto sq : m_EnPassantSquares)
				m_Hash ^= enPassantHash(sq);
			m_EnPassantSquares = targets;
			m_EnPassantVictim = victim;
			for (const auto sq : m_EnPassantSquares)
				m_Hash ^= enPassantHash(sq);
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		PYGMALION_INLINE const playerpiecesType& playerpieces() const noexcept
		{
			return m_PlayerPieces;
		}
		PYGMALION_INLINE const piecesType& pieces(const playerType pl) const noexcept
		{
			return playerpieces().pieces(pl);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE const piecesType& pieces() const noexcept
		{
			return playerpieces().template pieces<PLAYER>();
		}
		PYGMALION_INLINE piecesType opponentPieces(const playerType pl) const noexcept
		{
			constexpr const piecesType none{ piecesType::none() };
			piecesType opponents{ none };
			const size_t playerIndex{ static_cast<size_t>(pl) };
			size_t i;
			for (i = 0; i < playerIndex; i++)
				opponents |= playerpieces().pieces(i);
			for (i++; i < countPlayers; i++)
				opponents |= playerpieces().pieces(i);
			return opponents;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE piecesType opponentPieces() const noexcept
		{
			constexpr const piecesType none{ piecesType::none() };
			piecesType opponents{ none };
			constexpr const size_t playerIndex{ PLAYER };
			size_t i;
			for (i = 0; i < playerIndex; i++)
				opponents |= playerpieces().pieces(i);
			for (i++; i < countPlayers; i++)
				opponents |= playerpieces().pieces(i);
			return opponents;
		}
		constexpr static size_t countParameters{ materialTableType::countParameters };
		PYGMALION_INLINE objectiveType material() const noexcept
		{
			return m_Material;
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
		PYGMALION_INLINE const hashType& hash() const noexcept
		{
			return m_Hash;
		}
		PYGMALION_INLINE const hashType& structureHash() const noexcept
		{
			return m_StructureHash;
		}
		PYGMALION_INLINE void setFlag(const flagType flag) noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			const flagsType oldFlags{ m_Flags };
			m_Flags.setElement(flag);
			m_Hash ^= flagsHash(oldFlags);
			m_Hash ^= flagsHash(m_Flags);
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		PYGMALION_INLINE void toggleFlag(const flagType flag) noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			const flagsType oldFlags{ m_Flags };
			m_Flags ^= flag;
			m_Hash ^= flagsHash(oldFlags);
			m_Hash ^= flagsHash(m_Flags);
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		PYGMALION_INLINE void clearFlag(const flagType flag) noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			const flagsType oldFlags{ m_Flags };
			m_Flags.clearElement(flag);
			m_Hash ^= flagsHash(oldFlags);
			m_Hash ^= flagsHash(m_Flags);
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		PYGMALION_INLINE bool testFlag(const flagType flag) const noexcept
		{
			return m_Flags[flag];
		}
		PYGMALION_INLINE void setFlags(const flagsType flags) noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			const flagsType oldFlags{ m_Flags };
			m_Flags |= flags;
			m_Hash ^= flagsHash(oldFlags);
			m_Hash ^= flagsHash(m_Flags);
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		PYGMALION_INLINE void clearFlags(const flagsType flags) noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			const flagsType oldFlags{ m_Flags };
			m_Flags &= ~flags;
			m_Hash ^= flagsHash(oldFlags);
			m_Hash ^= flagsHash(m_Flags);
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<board::enableRange(FIRST, LAST)>::type>
		PYGMALION_INLINE void clearFlagRange() noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			const flagsType oldFlags{ m_Flags };
			m_Flags.template clearRange<FIRST, LAST>();
			m_Hash ^= flagsHash(oldFlags);
			m_Hash ^= flagsHash(m_Flags);
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<board::enableRange(FIRST, LAST)>::type>
		PYGMALION_INLINE void setFlagRange() noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			const flagsType oldFlags{ m_Flags };
			m_Flags.template setRange<FIRST, LAST>();
			m_Hash ^= flagsHash(oldFlags);
			m_Hash ^= flagsHash(m_Flags);
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<board::enableRange(FIRST, LAST)>::type>
		uint_t<1 + LAST - FIRST, false> extractFlagRange() const noexcept
		{
			return m_Flags.template extractRange<FIRST, LAST>();
		}
		template<size_t FIRST, size_t LAST, typename = typename std::enable_if<board::enableRange(FIRST, LAST)>::type>
		PYGMALION_INLINE void storeFlagRange(const uint_t<1 + LAST - FIRST, false> flags) noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			const flagsType oldFlags{ m_Flags };
			m_Flags.template storeRange<FIRST, LAST>(flags);
			m_Hash ^= flagsHash(oldFlags);
			m_Hash ^= flagsHash(m_Flags);
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		PYGMALION_INLINE void checkFlags(const flagsType flags) noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			const flagsType oldFlags{ m_Flags };
			m_Flags = flags;
			m_Hash ^= flagsHash(oldFlags);
			m_Hash ^= flagsHash(m_Flags);
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		PYGMALION_INLINE const flagsType& flags() const noexcept
		{
			return m_Flags;
		}
		PYGMALION_INLINE void setMovingPlayer(const playerType movingPlayer) noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			const playerType oldPlayer{ m_MovingPlayer };
			m_MovingPlayer = movingPlayer;
			m_Hash ^= playerHash(m_MovingPlayer) ^ playerHash(oldPlayer);
			m_StructureHash ^= playerHash(m_MovingPlayer) ^ playerHash(oldPlayer);
			PYGMALION_ASSERT(theoreticalHash() == hash());
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
		PYGMALION_INLINE squaresType pieceOccupancy(const piecesType pcs) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType occupied{ none };
			for (const auto pc : pcs)
				occupied |= m_PieceOccupancy[pc];
			return occupied;
		}
		PYGMALION_INLINE const squaresType& playerOccupancy(const playerType pl) const noexcept
		{
			PYGMALION_ASSERT(pl.isValid());
			return m_PlayerOccupancy[pl];
		}
		PYGMALION_INLINE squaresType playerOccupancy(const playersType pls) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType occupied{ none };
			for (const auto pl : pls)
				occupied |= m_PlayerOccupancy[pl];
			return occupied;
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
			PYGMALION_ASSERT(theoreticalHash() == hash());
			PYGMALION_ASSERT(player.isValid());
			PYGMALION_ASSERT(piece.isValid());
			PYGMALION_ASSERT(square.isValid());
#if !defined(NDEBUG)
			for (const auto pl : playerType::range)
				PYGMALION_ASSERT(!m_PlayerOccupancy[pl][square]);
			for (const auto pc : pieceType::range)
				PYGMALION_ASSERT(!m_PieceOccupancy[pc][square]);
#endif
			m_PlayerOccupancy[player] |= square;
			m_PieceOccupancy[piece] |= square;
			m_Hash ^= pieceHash(piece, square, player);
			if (piece.isStructural())
				m_StructureHash ^= pieceHash(piece, square, player);
			m_Material += materialTable.material(player, piece, square);
			m_PlayerPieces.pieces(player) |= piece;
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		PYGMALION_INLINE void removePiece(const pieceType piece, const squareType square, const playerType player, const materialTableType& materialTable) noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
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
			if (piece.isStructural())
				m_StructureHash ^= pieceHash(piece, square, player);
			m_Material -= materialTable.material(player, piece, square);
			const squaresType occ{ m_PlayerOccupancy[player] & m_PieceOccupancy[piece] };
			m_PlayerPieces.pieces(player).checkElement(piece, m_PlayerOccupancy[player] & m_PieceOccupancy[piece]);
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		PYGMALION_INLINE void movePiece(const pieceType piece, const squareType from, const squareType to, const playerType player, const materialTableType& materialTable) noexcept
		{
			PYGMALION_ASSERT(theoreticalHash() == hash());
			PYGMALION_ASSERT(player.isValid());
			PYGMALION_ASSERT(piece.isValid());
			PYGMALION_ASSERT(from.isValid());
			PYGMALION_ASSERT(to.isValid());
#if !defined(NDEBUG)
			PYGMALION_ASSERT(m_PlayerOccupancy[player][from]);
			PYGMALION_ASSERT(m_PieceOccupancy[piece][from]);
			for (const auto pl : playerType::range)
				PYGMALION_ASSERT(!m_PlayerOccupancy[pl][to]);
			for (const auto pc : pieceType::range)
				PYGMALION_ASSERT(!m_PieceOccupancy[pc][to]);
#endif
			m_PlayerOccupancy[player] -= from;
			m_PieceOccupancy[piece] -= from;
			m_PlayerOccupancy[player] |= to;
			m_PieceOccupancy[piece] |= to;
			m_Hash ^= pieceHash(piece, from, player);
			m_Hash ^= pieceHash(piece, to, player);
			if (piece.isStructural())
			{
				m_StructureHash ^= pieceHash(piece, from, player);
				m_StructureHash ^= pieceHash(piece, to, player);
			}
			m_Material -= materialTable.material(player, piece, from);
			m_Material += materialTable.material(player, piece, to);
			PYGMALION_ASSERT(theoreticalHash() == hash());
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
			m_Hash = playerHash(m_MovingPlayer) ^ flagsHash(m_Flags);
			m_StructureHash = playerHash(m_MovingPlayer);
			m_MoveCount = 0;
			m_ReversiblePlyCount = 0;
			constexpr const objectiveType zero{ objectiveType::zero() };
			m_Material = zero;
			m_PlayerPieces.clear();
			PYGMALION_ASSERT(theoreticalHash() == hash());
		}
		board() noexcept :
			m_PieceOccupancy{ },
			m_PlayerOccupancy{ },
			m_MovingPlayer{ 0 },
			m_Flags{ flagsType::none() },
			m_Arbitration{ gamestateType::open() }
		{
			clear();
		}
		void initialize(const materialTableType& materialTable) noexcept
		{
			clear();
			setMovingPlayer(static_cast<playerType>(boardInfo.initialPlayerIndex()));
			size_t victimSquareIndex;
			list<size_t, countSquares> targetSquareIndices;
			if (boardInfo.initialEnPassant(victimSquareIndex, targetSquareIndices))
			{
				const squareType victim{ static_cast<squareType>(victimSquareIndex) };
				squaresType targets{ squaresType::none() };
				for (size_t i = 0; i < targetSquareIndices.length(); i++)
					targets |= static_cast<squareType>(targetSquareIndices[i]);
				setEnPassant(targets, victim);
			}
			else
				clearEnPassant();
			for (const auto sq : squareType::range)
			{
				size_t playerpieceIndex;
				if (boardInfo.initialPlayerPieceOnSquare(static_cast<size_t>(sq), playerpieceIndex))
				{
					const playerpieceType ppc{ static_cast<playerpieceType>(playerpieceIndex) };
					addPiece(ppc.piece(), sq, ppc.player(), materialTable);
				}
			}
			for (const auto f : flagType::range)
			{
				if (boardInfo.initialFlag(static_cast<size_t>(f)))
					setFlag(f);
			}
			PYGMALION_ASSERT(theoreticalHash() == hash());
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
						fen << (piece & side).toShortString();
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
			fen << movingPlayer().toShortString() << " ";
			fen << flags().toString() << " ";
			if (enPassantTargets())
			{
				for (const auto sq : enPassantTargets())
					fen << sq.toShortString();
				bool bNeedsVictim{ true };
				if constexpr (countPlayers == 2)
				{
					if (enPassantTargets().count() == 1)
					{
						const squareType epSquare{ enPassantTargets().first() };
						if (movingPlayer() == playerType(0))
						{
							if (epSquare.rank() == rankType(5) && enPassantVictim().rank() == rankType(4) && epSquare.file() == enPassantVictim().file())
								bNeedsVictim = false;
						}
						else
						{
							if (epSquare.rank() == rankType(2) && enPassantVictim().rank() == rankType(3) && epSquare.file() == enPassantVictim().file())
								bNeedsVictim = false;
						}
					}
				}
				if (bNeedsVictim)
					fen << ":" << enPassantVictim().toShortString();
				fen << " ";
			}
			else
				fen << "- ";
			fen << parser::fromInt(getReversiblePlyCount()) << " ";
			fen << parser::fromInt(getMoveCount() / 2);
			return fen.str();
		}
		bool setFen(const std::string& fen, const materialTableType& materialTable) noexcept
		{
			clear();
			size_t pos{ 0 };
			typename fileType::baseType file{ 0 };
			typename rankType::baseType rank{ static_cast<typename rankType::baseType>(countRanks - 1) };
			bool bParse{ true };
			size_t count{ 0 };
			playerpieceType ppc;
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
					if (playerpieceType::parse(fen.substr(pos, fen.length() - pos), count, ppc))
					{
						addPiece(ppc.piece(), fileType(file) & rankType(rank), ppc.player(), materialTable);
						file++;
					}
					else
					{
						clear();
						return false;
					}
					pos += count;
					count = 0;
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
			playerType player;
			if (!playerType::parse(fen.substr(pos, fen.length() - pos), count, player))
			{
				clear();
				return false;
			}
			pos += count;
			count = 0;
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
			flagsType flags{ flagsType::none() };
			if (!flagsType::parse(fen.substr(pos, fen.length() - pos), count, flags))
			{
				clear();
				return false;
			}
			checkFlags(flags);
			pos += count;
			count = 0;
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
			if (fen[pos] == '-')
			{
				m_EnPassantSquares = squaresType::none();
				pos++;
			}
			else
			{
				bool bAtLeastOne{ false };
				squareType epSquare;
				squaresType epSquares{ squaresType::none() };
				while (squareType::parse(fen.substr(pos, fen.length() - pos), count, epSquare))
				{
					epSquares |= epSquare;
					bAtLeastOne = true;
					pos += count;
					count = 0;
				}
				if (!bAtLeastOne)
				{
					clear();
					return false;
				}
				bool bNeedsVictim{ true };
				if constexpr (countPlayers == 2)
				{
					if (epSquares.count() == 1)
					{
						const squareType epSquare2{ epSquares.first() };
						if (movingPlayer() == playerType(0))
						{
							if (epSquare2.rank() == rankType(5))
								bNeedsVictim = false;
						}
						else
						{
							if (epSquare2.rank() == rankType(2))
								bNeedsVictim = false;
						}
					}
				}
				squareType victim{ squareType::invalid };
				if (fen.length() > pos)
				{
					if (fen[pos] == ':')
					{
						pos++;
						if (fen.length() > pos)
						{
							if (squareType::parse(fen.substr(pos, fen.length() - pos), count, victim))
							{
								pos += count;
								count = 0;
							}
							else
							{
								clear();
								return false;
							}
						}
						else
						{
							clear();
							return false;
						}
					}
				}
				if (bNeedsVictim)
				{
					if (!victim.isValid())
					{
						clear();
						return false;
					}
				}
				else
				{
					if (!victim.isValid())
					{
						if ((epSquare.rank() == rankType(5)) && (movingPlayer() == playerType(0)))
							victim = rankType(4) & epSquare.file();
						else if ((epSquare.rank() == rankType(2)) && (movingPlayer() == playerType(1)))
							victim = rankType(3) & epSquare.file();
						else
						{
							clear();
							return false;
						}
					}
				}
				setEnPassant(epSquares, victim);
			}
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
		PYGMALION_INLINE squareType royalSquare(const playerType player, const royalpieceType rp) const noexcept
		{
			return (pieceOccupancy(static_cast<pieceType>(rp)) & playerOccupancy(player)).first();
		}
	};

	template<typename DESCRIPTOR_STATE, typename INSTANCE>
	std::ostream& operator<<(std::ostream& str, const board<DESCRIPTOR_STATE, INSTANCE>& position) noexcept
	{
		using boardType = board<DESCRIPTOR_STATE, INSTANCE>;
		using descriptorState = DESCRIPTOR_STATE;
#include "include_state.h"
		for (const auto r : rankType::range)
		{
			const rankType rank{ -r };
			str << rank.toShortString();
			str << "|";
			for (const auto file : fileType::range)
			{
				const squareType square{ rank & file };
				if (position.totalOccupancy()[square])
				{
					if (position.playerOccupancy(descriptorState::whitePlayer)[square] && position.playerOccupancy(descriptorState::blackPlayer)[square])
						str << "!";
					else
					{
						bool hasPiece{ false };
						for (const auto pc : pieceType::range)
						{
							if (position.pieceOccupancy(pc)[square])
							{
								hasPiece = true;
								break;
							}
						}
						if (hasPiece)
						{
							const pieceType piece{ position.getPiece(square) };
							const playerType player{ position.getPlayer(square) };
							str << (piece & player).toShortString();
						}
						else
							str << "@";
					}
				}
				else
				{
					bool hasPiece{ false };
					for (const auto pc : pieceType::range)
					{
						if (position.pieceOccupancy(pc)[square])
						{
							hasPiece = true;
							break;
						}
					}
					if (hasPiece)
						str << "?";
					else
					{
						if (position.checkEnPassantTarget(square))
							str << "#";
						else
							str << ".";
					}
				}
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
			str << file.toShortString();
		}
		str << std::endl;
		str << std::endl;
		str << "Flags:    " << position.flags().toString() << std::endl;
		str << "Pieces:   " << position.pieces(descriptorState::whitePlayer).toString(descriptorState::whitePlayer) << ":" << position.pieces(descriptorState::blackPlayer).toString(descriptorState::blackPlayer) << std::endl;
		str << "Material: " << position.material().makeSubjective(position.movingPlayer()) << std::endl;
		str << std::endl;
		str << "Total Hash:     " << std::setw(8) << std::hex << static_cast<std::uint64_t>(position.hash()) << std::dec << std::endl;
		str << "Structure Hash: " << std::setw(8) << std::hex << static_cast<std::uint64_t>(position.structureHash()) << std::dec << std::endl;
		str << std::endl;
		str << "FEN: " << position.getFen() << std::endl;
		str << std::endl;
		str << "EnPassant victim:  " << (position.enPassantVictim().isValid() ? position.enPassantVictim().toShortString() : std::string("none")) << std::endl;
		str << "EnPassant targets:";
		if (position.enPassantTargets())
		{
			for (const auto ep : position.enPassantTargets())
			{
				str << " " << ep.toShortString();
			}
		}
		else
		{
			str << " none";
		}
		str << std::endl;
		str << std::endl;
		str << "Half-move clock: " << static_cast<std::uint64_t>(position.getReversiblePlyCount()) << std::endl;
		str << "Moves played:    " << static_cast<std::uint64_t>(position.getMoveCount()) << std::endl;
		str << std::endl;
		str << "Moving player: " << position.movingPlayer().toLongString() << std::endl;
		return str;
	}
}