namespace pygmalion::tictactoe
{
	class board : public pygmalion::board<3, 3, 1, 2, 0, 16, 9, pygmalion::tictactoe::board>
	{
	private:
		static const hash<hashLength, countSquares* countPieces* countPlayers> m_PieceHash;
		static const hash<hashLength, countFlags> m_FlagHash;
	public:
		constexpr board() noexcept :
			pygmalion::board<3, 3, 1, 2, 0, 16, 9, pygmalion::tictactoe::board>()
		{
		}
		constexpr board(const board&) noexcept = default;
		constexpr board(board&&) noexcept = default;
		~board() = default;
		constexpr board& operator=(const board&) = default;
		constexpr board& operator=(board&&) = default;
		class move : public moveBase<false, true, requiredUnsignedBits(countSquares), 1, 0>
		{
		private:
		public:
			constexpr square to() const noexcept
			{
				return square2();
			}
			constexpr move(const square to) noexcept :
				moveBase<false, true, requiredUnsignedBits(countSquares), 1, 0>(0, to, 0, 0)
			{

			}
			constexpr move() noexcept :
				moveBase<false, true, requiredUnsignedBits(countSquares), 1, 0>()
			{

			}
			constexpr move(const move&) noexcept = default;
			constexpr move(move&&) noexcept = default;
			constexpr move& operator=(const move& other) noexcept = default;
			constexpr move& operator=(move&&) noexcept = default;
			~move() noexcept = default;
		};
		using moveType = move;
		class movedata : public movedataBase
		{
		private:
			hashValue m_OldHash;
			square m_TargetSquare;
		public:
			constexpr movedata(board& position, const player oldPlayer) noexcept :
				movedataBase(position, oldPlayer),
				m_OldHash{ position.getHash() },
				m_TargetSquare{ square::invalid }
			{

			}
			constexpr movedata(board& position, const move& mv) noexcept :
				movedataBase(position),
				m_OldHash{ position.getHash() },
				m_TargetSquare{ mv.to() }
			{
			}
			~movedata() noexcept = default;
			constexpr auto oldHash() const noexcept
			{
				return m_OldHash;
			}
			constexpr square targetSquare() const noexcept
			{
				return m_TargetSquare;
			}
		};
		class boardStack : public stack<movedata, boardStack>
		{
		public:
			bool isMoveLegal_Implementation(const moveType& move) const noexcept;
			bool generateMoves_Implementation(movelistType& moves, int& currentPass) const noexcept;
			bool generateTacticalMoves_Implementation(movelistType& moves, int& currentPass) const noexcept;
			boardStack(const boardStack& parent, const move mv) noexcept;
			boardStack(instanceType& position, const player oldPlayer) noexcept;
			~boardStack() noexcept = default;
		};
		using stackType = boardStack;
		constexpr static void makeMove_Implementation(instanceType& position, const movedata& md) noexcept
		{
			position.addPiece(0, md.targetSquare(), md.movingPlayer());
			position.setHash(md.oldHash() ^ pieceHash(md.movingPlayer(), 0, md.targetSquare()) ^ flagsHash(flagsFromPlayer(md.movingPlayer())));
			position.setMovingPlayer(md.movingPlayer().next());
		}
		constexpr static void unmakeMove_Implementation(instanceType& position, const movedata& md) noexcept
		{
			position.removePiece(0, md.targetSquare(), md.movingPlayer());
			position.setMovingPlayer(md.movingPlayer());
			position.setHash(md.oldHash());
		}
		constexpr static hashValue pieceHash_Implementation(const player p, const piece pc, const square sq)
		{
			assert(p.isValid());
			assert(pc.isValid());
			assert(sq.isValid());
			return m_PieceHash[(p * piece::countValues + pc) * square::countValues + sq];
		}
		constexpr static hashValue flagHash_Implementation(flags f)
		{
			assert(f >= 0);
			assert(f < (size_t(1) << countFlags));
			const bitfield<hashLength> fl(f);
			hashValue h{ 0 };
			for (const auto bit : fl)
				h |= m_FlagHash[bit];
			return h;
		}
	};

}