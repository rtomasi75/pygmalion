namespace pygmalion::tictactoe
{
	class board : public pygmalion::board<3, 3, 1, 2, 0, 8, 9, pygmalion::tictactoe::board>
	{
	private:
		constexpr static std::array<hashValue, 1 << countFlags> m_FlagHash
		{
			hashValue(0x0000000000000000),
			hashValue(0xF8D626AAAF278509)
		};
		constexpr static std::array<std::array<std::array<hashValue, 9>, 1>, 2> m_PieceHash
		{
			hashValue(0x56436C9FE1A1AA8D),
			hashValue(0xEFAC4B70633B8F81),
			hashValue(0xBB215798D45DF7AF),
			hashValue(0x45F20042F24F1768),
			hashValue(0x930F80F4E8EB7462),
			hashValue(0xFF6712FFCFD75EA1),
			hashValue(0xAE623FD67468AA70),
			hashValue(0xDD2C5BC84BC8D8FC),
			hashValue(0x7EED120D54CF2DD9),
			hashValue(0x7F9B6AF1EBF78BAF),
			hashValue(0x58627E1A149BBA21),
			hashValue(0x2CD16E2ABD791E33),
			hashValue(0xD363EFF5F0977996),
			hashValue(0x0CE2A38C344A6EED),
			hashValue(0x1A804AADB9CFA741),
			hashValue(0x907F30421D78C5DE),
			hashValue(0x501F65EDB3034D07),
			hashValue(0x37624AE5A48FA6E9)
		};
	public:
		constexpr board() noexcept :
			pygmalion::board<3, 3, 1, 2, 0, 8, 9, pygmalion::tictactoe::board>()
		{
		}
		constexpr board(const board&) noexcept = default;
		constexpr board(board&&) noexcept = default;
		~board() = default;
		constexpr board& operator=(const board&) = default;
		constexpr board& operator=(board&&) = default;
		constexpr static hashValue pieceHash_Implementation(const player p, const piece pc, const square sq)
		{
			return m_PieceHash[p][pc][sq];
		}
		constexpr static hashValue flagsHash_Implementation(const flags f)
		{
			return m_FlagHash[f];
		}
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
			constexpr move& operator=(const move&) noexcept = default;
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
		class boardStack : public stack<movedata, move, boardStack>
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
	};

}