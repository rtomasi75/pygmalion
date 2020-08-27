namespace pygmalion
{
	template<int COUNTRANKS, int COUNTFILES, int PIECECOUNT, int PLAYERCOUNT, int CUSTOMFLAGCOUNT, int HASHLENGTH, int COUNTMOVES, typename INSTANCE>
	class board
	{
	public:
		constexpr static const int maxMoveCount{ COUNTMOVES };
		constexpr static const int hashLength{ HASHLENGTH };
		constexpr static const int countRanks{ COUNTRANKS };
		constexpr static const int countFiles{ COUNTFILES };
		constexpr static const int countSquares{ countRanks * countFiles };
		constexpr static const int countPieces{ PIECECOUNT };
		constexpr static const int countPlayers{ PLAYERCOUNT };
		constexpr static const int countGamestateBits{ 1 + requiredUnsignedBits(countPlayers) };
		constexpr static const int countCustomFlags{ CUSTOMFLAGCOUNT };
		constexpr static const int countPlayerFlags{ requiredUnsignedBits(countPlayers) };
		constexpr static const int countIntrinsicFlags{ countPlayerFlags };
		constexpr static const int countFlags{ countCustomFlags + countPlayerFlags };
		using rank = enumeration<COUNTRANKS>;
		using file = enumeration<COUNTFILES>;
		using instanceType = INSTANCE;
		using hashValue = typename hashBase<hashLength>::hashValue;
		using bitsType = bitfield<countSquares>;
		using gamestate = enumeration<countGamestateBits>;
		using player = enumeration<countPlayers>;
		using square = enumeration<countSquares>;
		using piece = enumeration <countPieces>;
		using flags = typename int_traits<requiredBitBytes(countFlags)>::UTYPE;
		constexpr static square fromRankFile(const rank r, const file f) noexcept
		{
			assert(r.isValid());
			assert(f.isValid());
			return r * countFiles + f;
		}
		constexpr static rank rankOfSquare(const square sq) noexcept
		{
			assert(sq.isValid());
			return sq / countFiles;
		}
		constexpr static file fileOfSquare(const square sq) noexcept
		{
			assert(sq.isValid());
			return sq % countFiles;
		}
		constexpr static flags flagBit(const int bit) noexcept
		{
			return static_cast<flags>(flags(1) << bit);
		}
		const static hash<hashLength, player::countValues> m_PlayerHash;
		const static hash<hashLength, square::countValues> m_SquareHash;
		const static hash<hashLength, piece::countValues> m_PieceHash;
		const static hash<hashLength, countFlags> m_FlagHash;
	private:
		std::array<bitsType, countPieces> m_PieceOccupancy;
		std::array<bitsType, countPlayers> m_PlayerOccupancy;
		flags m_Flags;
		hashValue m_Hash;
	protected:
		constexpr static flags flagmask{ static_cast<flags>((flags(1) << countFlags) - 1) };
		constexpr static flags playermask{ static_cast<flags>(((flags(1) << countPlayerFlags) - 1)) };
		constexpr static flags playerstencil = ~playermask;
		constexpr static flags flagsFromPlayer(const player p) noexcept
		{
			assert(p.isValid());
			return p;
		}
		constexpr static player playerFromFlags(const flags f) noexcept
		{
			return f & playermask;
		}
	public:
		constexpr hashValue getHash() const noexcept
		{
			return m_Hash;
		}
		constexpr void setHash(const hashValue hash) noexcept
		{
			m_Hash = hash;
		}
		template<typename MOVEDATA>
		void makeMove(const MOVEDATA& movedata) noexcept
		{
			instanceType::makeMove_Implementation(*static_cast<instanceType*>(this), movedata);
		}
		template<typename MOVEDATA>
		void unmakeMove(const MOVEDATA& movedata) noexcept
		{
			instanceType::unmakeMove_Implementation(*static_cast<instanceType*>(this), movedata);
		}
		constexpr void setFlags(const flags newFlags) noexcept
		{
			m_Flags = newFlags;
		}
		constexpr auto getFlags() const noexcept
		{
			return m_Flags;
		}
		constexpr static hashValue pieceHash(const player p, const piece pc, const square sq)
		{
			assert(p.isValid());
			return instanceType::pieceHash_Implementation(p, pc, sq);
		}
		constexpr static hashValue flagsHash(flags f)
		{
			assert(f >= 0);
			assert(f < (size_t(1) << countFlags));
			return instanceType::flagHash_Implementation(f);
		}
		constexpr static auto open() noexcept
		{
			return static_cast<gamestate>(0);
		}
		constexpr static auto isOpen(const gamestate state) noexcept
		{
			return state == open();
		}
		constexpr static auto draw() noexcept
		{
			return static_cast<gamestate>(1);
		}
		constexpr static auto isDraw(const gamestate state) noexcept
		{
			return state == draw();
		}
		constexpr static auto loss(const player losingPlayer) noexcept
		{
			return static_cast<gamestate>(2 << (losingPlayer));
		}
		constexpr static auto isLoss(const gamestate state, const player p) noexcept
		{
			return state == loss(p);
		}
		constexpr static auto win(const player winningPlayer) noexcept
		{
			gamestate result{ 0 };
			for (const auto i : player::range)
			{
				if (i != winningPlayer)
					result |= loss(i);
			}
			return result;
		}
		constexpr static auto isWin(const gamestate state, const player p) noexcept
		{
			return state == win(p);
		}
		constexpr void setMovingPlayer(const player movingPlayer) noexcept
		{
			assert(movingPlayer.isValid());
			m_Flags &= playerstencil;
			m_Flags |= flagsFromPlayer(movingPlayer);
		}
		constexpr auto movingPlayer() const noexcept
		{
			return playerFromFlags(m_Flags);
		}
		constexpr auto pieceOccupancy(const piece pc) const noexcept
		{
			assert(pc.isValid());
			return m_PieceOccupancy[pc];
		}
		constexpr auto playerOccupancy(const player p) const noexcept
		{
			assert(p.isValid());
			return m_PlayerOccupancy[p];
		}
		constexpr bitsType totalOccupancy() const noexcept
		{
			constexpr const bool preferPlayers{ countPlayers < countPieces };
			bitsType value(0);
			if (preferPlayers)
			{
				for (const auto p : player::range)
				{
					value |= m_PlayerOccupancy[p];
				}
			}
			else
			{
				for (const auto pc : piece::range)
				{
					value |= m_PieceOccupancy[pc];
				}
			}
			return value;
		}
		constexpr bool isOccupied(const square sq) const noexcept
		{
			assert(sq.isValid());
			return totalOccupancy().checkBit(sq);
		}
		constexpr bool isOccupied(const square sq, const player p) const noexcept
		{
			assert(sq.isValid());
			assert(p.isValid());
			return playerOccupancy(p).checkBit(sq);
		}
		constexpr void addPiece(const piece pc, const square sq, const player p) noexcept
		{
			assert(p.isValid());
			assert(pc.isValid());
			assert(sq.isValid());
			for (const auto i : piece::range)
			{
				assert(!pieceOccupancy(i).checkBit(sq));
			}
			for (const auto i : player::range)
			{
				assert(!playerOccupancy(i).checkBit(sq));
			}
			m_PlayerOccupancy[p].setBit(sq);
			m_PieceOccupancy[pc].setBit(sq);
		}
		constexpr void removePiece(const piece pc, const square sq, const player p) noexcept
		{
			assert(p.isValid());
			assert(pc.isValid());
			assert(sq.isValid());
			assert(m_PieceOccupancy[pc].checkBit(sq));
			assert(m_PlayerOccupancy[p].checkBit(sq));
			m_PlayerOccupancy[p].clearBit(sq);
			m_PieceOccupancy[pc].clearBit(sq);
		}
		constexpr piece getPiece(const square sq) const noexcept
		{
			assert(sq.isValid());
			assert(totalOccupancy().checkBit(sq));
			piece pc{ 0 };
			for (const piece i : piece::range)
				pc = pc | m_PieceOccupancy[i].checkBit(sq) * i;
			return pc;
		}
		constexpr board() noexcept :
			m_PieceOccupancy{ },
			m_PlayerOccupancy{ },
			m_Flags{ 0 },
			m_Hash{ 0 }
		{

		}
		constexpr board(board&&) noexcept = default;
		constexpr board(const board&) noexcept = default;
		constexpr board& operator=(board&&) noexcept = default;
		constexpr board& operator=(const board&) noexcept = default;
		~board() noexcept = default;
		class movedataBase
		{
		public:
		private:
			player m_MovingPlayer;
			bool m_IsNullMove;
		public:
			constexpr movedataBase(const instanceType& position, const player movingPlayer) noexcept :
				m_MovingPlayer{ movingPlayer },
				m_IsNullMove{ true }
			{

			}
			constexpr movedataBase(const instanceType& position) noexcept :
				m_MovingPlayer{ position.movingPlayer() },
				m_IsNullMove{ false }
			{
			}
			~movedataBase() noexcept = default;
			constexpr player movingPlayer() const noexcept
			{
				return m_MovingPlayer;
			}
			constexpr bool isNullMove() const noexcept
			{
				return m_IsNullMove;
			}
		};
		template<typename MOVEDATA, typename STACK>
		class stack
		{
		public:
			using stackType = STACK;
			using movedataType = MOVEDATA;
			using moveType = typename instanceType::moveType;
			using movelistType = movelist<moveType, maxMoveCount>;
			using indexType = typename movelistType::counterType;
		private:
			mutable movelistType m_Moves;
			mutable movelistType m_TacticalMoves;
			instanceType& m_Position;
			const movedataType m_MoveData;
			player m_MovingPlayer;
			mutable int m_CurrentPass;
			mutable indexType m_CurrentMove;
			mutable int m_CurrentTacticalPass;
			mutable indexType m_CurrentTacticalMove;
			mutable indexType m_CurrentLegalMove;
			mutable bool m_HasLegalMove;
			mutable bool m_HasLegalMoveValid;
			void initialize() noexcept
			{
				if (!m_MoveData.isNullMove())
					m_Position.makeMove(m_MoveData);
			}
			void deinitialize() noexcept
			{
				if (!m_MoveData.isNullMove())
					m_Position.unmakeMove(m_MoveData);
			}
			bool computeHasLegalMove() const
			{
				bool allMovesGenerated{ false };
				while (!allMovesGenerated)
				{
					if (m_CurrentLegalMove >= m_Moves.length())
					{
						if (!generateMoves(m_Moves, m_CurrentPass))
						{
							allMovesGenerated = true;
							return false;
						}
					}
					while (m_CurrentLegalMove < m_Moves.length())
					{
						if (isMoveLegal(m_Moves[m_CurrentLegalMove]))
							return true;
						m_CurrentLegalMove++;
					}
				}
				return false;
			}
		protected:
			bool generateMoves(movelistType& moves, int& currentPass) const noexcept
			{
				return static_cast<const stackType*>(this)->generateMoves_Implementation(moves, currentPass);
			}
			bool generateTacticalMoves(movelistType& moves, int& currentPass) const noexcept
			{
				return static_cast<const stackType*>(this)->generateTacticalMoves_Implementation(moves, currentPass);
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
			bool isMoveLegal(const moveType& move) const noexcept
			{
				return static_cast<const stackType*>(this)->isMoveLegal_Implementation(move);
			}
			bool nextMove(moveType& move) const noexcept
			{
				bool allMovesGenerated{ false };
				while (!allMovesGenerated)
				{
					if (m_CurrentMove >= m_Moves.length())
					{
						if (!generateMoves(m_Moves, m_CurrentPass))
						{
							allMovesGenerated = true;
							return false;
						}
					}
					while (m_CurrentMove < m_Moves.length())
					{
						move = m_Moves[m_CurrentMove];
						m_CurrentMove++;
						if (isMoveLegal(move))
							return true;
					}
				}
				return false;
			}
			bool nextTacticalMove(moveType& move) const noexcept
			{
				bool allMovesGenerated{ false };
				while (!allMovesGenerated)
				{
					if (m_CurrentTacticalMove >= m_TacticalMoves.length())
					{
						if (!generateTacticalMoves(m_TacticalMoves, m_CurrentTacticalPass))
						{
							allMovesGenerated = true;
							return false;
						}
					}
					while (m_CurrentTacticalMove < m_TacticalMoves.length())
					{
						move = m_TacticalMoves[m_CurrentTacticalMove];
						m_CurrentTacticalMove++;
						if (isMoveLegal(move))
							return true;
					}
				}
				return false;
			}
			stack(const stack& parent, const moveType mv) noexcept :
				m_Position{ parent.m_Position },
				m_MoveData(m_Position, mv),
				m_Moves(),
				m_HasLegalMove{ false },
				m_HasLegalMoveValid{ false },
				m_CurrentPass{ 0 },
				m_CurrentMove{ 0 },
				m_CurrentTacticalPass{ 0 },
				m_CurrentTacticalMove{ 0 },
				m_CurrentLegalMove{ 0 }
			{
				initialize();
				m_MovingPlayer = m_Position.movingPlayer();
			}
			stack(instanceType& position, const player oldPlayer) noexcept :
				m_Position{ position },
				m_MoveData(m_Position, oldPlayer),
				m_Moves(),
				m_HasLegalMove{ false },
				m_HasLegalMoveValid{ false },
				m_CurrentPass{ 0 },
				m_CurrentMove{ 0 },
				m_CurrentTacticalPass{ 0 },
				m_CurrentTacticalMove{ 0 },
				m_CurrentLegalMove{ 0 }
			{
				initialize();
				m_MovingPlayer = m_Position.movingPlayer();
			}
			const instanceType& position() const noexcept
			{
				return m_Position;
			}
			player movingPlayer() const noexcept
			{
				return m_MovingPlayer;
			}
			~stack() noexcept
			{
				deinitialize();
			}
		};
	};
}