namespace pygmalion::chess
{

	class board : public pygmalion::board<8, 8, 6, 2, 12, 64, 255, pygmalion::chess::board>
	{
	public:
	private:
		constexpr static uint8_t DrawingDistance{ 100 };
		static const hash<hashLength, countSquares* countPieces* countPlayers> m_PieceHash;
		static const hash<hashLength, countFlags> m_FlagHash;
		hashValue m_PawnstructureHash;
		score m_Material;
		square m_KingSquare[player::countValues];
		uint8_t m_DistanceToDraw;
	public:
		constexpr auto getDistanceToDraw() const noexcept
		{
			return m_DistanceToDraw;
		}
		constexpr void setDistanceToDraw(const uint8_t distance) noexcept
		{
			m_DistanceToDraw = distance;
		}
		constexpr auto getPawnstructureHash() const noexcept
		{
			return m_PawnstructureHash;
		}
		constexpr void setPawnstructureHash(const hashValue hash) noexcept
		{
			m_PawnstructureHash = hash;
		}
		constexpr score getMaterial() const noexcept
		{
			return m_Material;
		}
		constexpr void setMaterial(const score material) noexcept
		{
			m_Material = material;
		}
		constexpr static piece knight{ 0x0 };
		constexpr static piece bishop{ 0x1 };
		constexpr static piece rook{ 0x2 };
		constexpr static piece queen{ 0x3 };
		constexpr static piece pawn{ 0x4 };
		constexpr static piece king{ 0x5 };
		constexpr board(const board&) noexcept = default;
		constexpr board(board&&) noexcept = default;
		~board() = default;
		board& operator=(const board&) = default;
		board& operator=(board&&) = default;
		constexpr static player whitePlayer{ 0 };
		constexpr static player blackPlayer{ 1 };
		constexpr static flags castlerightQueensideWhite{ flagBit(countIntrinsicFlags) };
		constexpr static flags castlerightQueensideBlack{ flagBit(countIntrinsicFlags + 1) };
		constexpr static flags castlerightKingsideWhite{ flagBit(countIntrinsicFlags + 2) };
		constexpr static flags castlerightKingsideBlack{ flagBit(countIntrinsicFlags + 3) };
		constexpr static flags castlerightMask{ castlerightQueensideWhite | castlerightQueensideBlack | castlerightKingsideWhite | castlerightKingsideBlack };
		constexpr static flags castlerightQueenside(const player p) noexcept
		{
			assert(p.isValid());
			return (size_t(1) << countIntrinsicFlags) << (p * 2);
		}
		constexpr static flags castlerightKingside(const player p) noexcept
		{
			assert(p.isValid());
			return (size_t(1) << (countIntrinsicFlags + 1)) << (p * 2);
		}
		constexpr static flags enPassantFlagsMask{ ((flags(1) << 9) - 1) << (countIntrinsicFlags + 4) };
		constexpr static flags enPassantFlags(const file f) noexcept
		{
			assert(f.isValid());
			return flagBit(countIntrinsicFlags + 4 + f);
		}
		constexpr static rank rank1{ 0 };
		constexpr static rank rank2{ 1 };
		constexpr static rank rank3{ 2 };
		constexpr static rank rank4{ 3 };
		constexpr static rank rank5{ 4 };
		constexpr static rank rank6{ 5 };
		constexpr static rank rank7{ 6 };
		constexpr static rank rank8{ 7 };
		constexpr static file fileA{ 0 };
		constexpr static file fileB{ 1 };
		constexpr static file fileC{ 2 };
		constexpr static file fileD{ 3 };
		constexpr static file fileE{ 4 };
		constexpr static file fileF{ 5 };
		constexpr static file fileG{ 6 };
		constexpr static file fileH{ 7 };
		constexpr static square squareA1{ fromRankFile(rank1,fileA) };
		constexpr static square squareA2{ fromRankFile(rank2,fileA) };
		constexpr static square squareA3{ fromRankFile(rank3,fileA) };
		constexpr static square squareA4{ fromRankFile(rank4,fileA) };
		constexpr static square squareA5{ fromRankFile(rank5,fileA) };
		constexpr static square squareA6{ fromRankFile(rank6,fileA) };
		constexpr static square squareA7{ fromRankFile(rank7,fileA) };
		constexpr static square squareA8{ fromRankFile(rank8,fileA) };
		constexpr static square squareB1{ fromRankFile(rank1,fileB) };
		constexpr static square squareB2{ fromRankFile(rank2,fileB) };
		constexpr static square squareB3{ fromRankFile(rank3,fileB) };
		constexpr static square squareB4{ fromRankFile(rank4,fileB) };
		constexpr static square squareB5{ fromRankFile(rank5,fileB) };
		constexpr static square squareB6{ fromRankFile(rank6,fileB) };
		constexpr static square squareB7{ fromRankFile(rank7,fileB) };
		constexpr static square squareB8{ fromRankFile(rank8,fileB) };
		constexpr static square squareC1{ fromRankFile(rank1,fileC) };
		constexpr static square squareC2{ fromRankFile(rank2,fileC) };
		constexpr static square squareC3{ fromRankFile(rank3,fileC) };
		constexpr static square squareC4{ fromRankFile(rank4,fileC) };
		constexpr static square squareC5{ fromRankFile(rank5,fileC) };
		constexpr static square squareC6{ fromRankFile(rank6,fileC) };
		constexpr static square squareC7{ fromRankFile(rank7,fileC) };
		constexpr static square squareC8{ fromRankFile(rank8,fileC) };
		constexpr static square squareD1{ fromRankFile(rank1,fileD) };
		constexpr static square squareD2{ fromRankFile(rank2,fileD) };
		constexpr static square squareD3{ fromRankFile(rank3,fileD) };
		constexpr static square squareD4{ fromRankFile(rank4,fileD) };
		constexpr static square squareD5{ fromRankFile(rank5,fileD) };
		constexpr static square squareD6{ fromRankFile(rank6,fileD) };
		constexpr static square squareD7{ fromRankFile(rank7,fileD) };
		constexpr static square squareD8{ fromRankFile(rank8,fileD) };
		constexpr static square squareE1{ fromRankFile(rank1,fileE) };
		constexpr static square squareE2{ fromRankFile(rank2,fileE) };
		constexpr static square squareE3{ fromRankFile(rank3,fileE) };
		constexpr static square squareE4{ fromRankFile(rank4,fileE) };
		constexpr static square squareE5{ fromRankFile(rank5,fileE) };
		constexpr static square squareE6{ fromRankFile(rank6,fileE) };
		constexpr static square squareE7{ fromRankFile(rank7,fileE) };
		constexpr static square squareE8{ fromRankFile(rank8,fileE) };
		constexpr static square squareF1{ fromRankFile(rank1,fileF) };
		constexpr static square squareF2{ fromRankFile(rank2,fileF) };
		constexpr static square squareF3{ fromRankFile(rank3,fileF) };
		constexpr static square squareF4{ fromRankFile(rank4,fileF) };
		constexpr static square squareF5{ fromRankFile(rank5,fileF) };
		constexpr static square squareF6{ fromRankFile(rank6,fileF) };
		constexpr static square squareF7{ fromRankFile(rank7,fileF) };
		constexpr static square squareF8{ fromRankFile(rank8,fileF) };
		constexpr static square squareG1{ fromRankFile(rank1,fileG) };
		constexpr static square squareG2{ fromRankFile(rank2,fileG) };
		constexpr static square squareG3{ fromRankFile(rank3,fileG) };
		constexpr static square squareG4{ fromRankFile(rank4,fileG) };
		constexpr static square squareG5{ fromRankFile(rank5,fileG) };
		constexpr static square squareG6{ fromRankFile(rank6,fileG) };
		constexpr static square squareG7{ fromRankFile(rank7,fileG) };
		constexpr static square squareG8{ fromRankFile(rank8,fileG) };
		constexpr static square squareH1{ fromRankFile(rank1,fileH) };
		constexpr static square squareH2{ fromRankFile(rank2,fileH) };
		constexpr static square squareH3{ fromRankFile(rank3,fileH) };
		constexpr static square squareH4{ fromRankFile(rank4,fileH) };
		constexpr static square squareH5{ fromRankFile(rank5,fileH) };
		constexpr static square squareH6{ fromRankFile(rank6,fileH) };
		constexpr static square squareH7{ fromRankFile(rank7,fileH) };
		constexpr static square squareH8{ fromRankFile(rank8,fileH) };
		board() noexcept;
		constexpr static bitsType notFileH{ 0x7f7f7f7f7f7f7f7f };
		constexpr static bitsType notFileA{ 0xfefefefefefefefe };
		constexpr static bitsType notRank1{ 0xffffffffffffff00 };
		constexpr static bitsType notRank8{ 0x00ffffffffffffff };
		constexpr static bitsType right(const bitsType bits) noexcept
		{
			return (bits & notFileH) << 1;
		}
		constexpr static bitsType rightFast(const bitsType bits) noexcept
		{
			return bits << 1;
		}
		constexpr static bitsType left(const bitsType bits) noexcept
		{
			return (bits & notFileA) >> 1;
		}
		constexpr static bitsType left_lazy(const bitsType bits) noexcept
		{
			return bits >> 1;
		}
		constexpr static bitsType down(const bitsType bits) noexcept
		{
			return bits >> 8;
		}
		constexpr static bitsType up(const bitsType bits) noexcept
		{
			return bits << 8;
		}
		constexpr static bitsType downRight(const bitsType bits) noexcept
		{
			return (bits & notFileH) >> 7;
		}
		constexpr static bitsType downRight_lazy(const bitsType bits) noexcept
		{
			return bits >> 7;
		}
		constexpr static bitsType upRight(const bitsType bits) noexcept
		{
			return (bits & notFileH) << 9;
		}
		constexpr static bitsType upRight_lazy(const bitsType bits) noexcept
		{
			return bits << 9;
		}
		constexpr static bitsType downLeft(const bitsType bits) noexcept
		{
			return (bits & notFileA) >> 9;
		}
		constexpr static bitsType downLeft_lazy(const bitsType bits) noexcept
		{
			return bits >> 9;
		}
		constexpr static bitsType upLeft(const bitsType bits) noexcept
		{
			return (bits & notFileA) << 7;
		}
		constexpr static bitsType upLeft_lazy(const bitsType bits) noexcept
		{
			return bits << 7;
		}
		constexpr static bitsType upUpLeft(const bitsType bits) noexcept
		{
			return up(upLeft(bits));
		}
		constexpr static bitsType upUpRight(const bitsType bits) noexcept
		{
			return up(upRight(bits));
		}
		constexpr static bitsType downDownLeft(const bitsType bits) noexcept
		{
			return down(downLeft(bits));
		}
		constexpr static bitsType downDownRight(const bitsType bits) noexcept
		{
			return down(downRight(bits));
		}
		constexpr static bitsType upLeftLeft(const bitsType bits) noexcept
		{
			return upLeft(left(bits));
		}
		constexpr static bitsType downLeftLeft(const bitsType bits) noexcept
		{
			return downLeft(left(bits));
		}
		constexpr static bitsType upRightRight(const bitsType bits) noexcept
		{
			return upRight(right(bits));
		}
		constexpr static bitsType downRightRight(const bitsType bits) noexcept
		{
			return downRight(right(bits));
		}
		constexpr square kingSquare(const player side) const noexcept
		{
			return m_KingSquare[side];
		}
		constexpr static bitsType queensideCastleInterestWhite{ bitsType::setMask(squareD1) | bitsType::setMask(squareC1) | bitsType::setMask(squareB1) };
		constexpr static bitsType queensideCastleInterestBlack{ bitsType::setMask(squareD8) | bitsType::setMask(squareC8) | bitsType::setMask(squareB8) };
		constexpr static bitsType kingsideCastleInterestWhite{ bitsType::setMask(squareF1) | bitsType::setMask(squareG1) };
		constexpr static bitsType kingsideCastleInterestBlack{ bitsType::setMask(squareF8) | bitsType::setMask(squareG8) };
		constexpr static bitsType queensideCastleWalkWhite{ bitsType::setMask(squareE1) | bitsType::setMask(squareD1) | bitsType::setMask(squareC1) };
		constexpr static bitsType queensideCastleWalkBlack{ bitsType::setMask(squareE8) | bitsType::setMask(squareD8) | bitsType::setMask(squareC8) };
		constexpr static bitsType kingsideCastleWalkWhite{ bitsType::setMask(squareE1) | bitsType::setMask(squareF1) | bitsType::setMask(squareG1) };
		constexpr static bitsType kingsideCastleWalkBlack{ bitsType::setMask(squareE8) | bitsType::setMask(squareF8) | bitsType::setMask(squareG8) };
		class move : public moveBase<true, true, requiredUnsignedBits(countSquares), 4, 2>
		{
		private:
			constexpr move(const squareType from, const squareType to, const channelType channel, const dataType data) noexcept :
				moveBase<true, true, requiredUnsignedBits(countSquares), 4, 2>(from, to, channel, data)
			{

			}
		public:
			constexpr move() noexcept :
				moveBase<true, true, requiredUnsignedBits(countSquares), 4, 2>()
			{

			}
			constexpr static move quiet(const square from, const square to) noexcept
			{
				return move(from, to, 0b00, 0b00);
			}
			constexpr static move doublePush(const square from, const square to) noexcept
			{
				return move(from, to, 0b00, 0b01);
			}
			constexpr static move capture(const square from, const square to) noexcept
			{
				return move(from, to, 0b01, 0b00);
			}
			constexpr static move captureEnPassant(const square from, const square to) noexcept
			{
				return move(from, to, 0b01, 0b01);
			}
			constexpr static move castleKingside(const  player p) noexcept
			{
				return (p == whitePlayer) ? move(squareE1, squareG1, 0b00, 0b11) : move(squareE8, squareG8, 0b00, 0b11);
			}
			constexpr static move castleQueenside(const  player p) noexcept
			{
				return (p == whitePlayer) ? move(squareE1, squareC1, 0b00, 0b10) : move(squareE8, 0b00, squareC8, 0b10);
			}
			constexpr static move promotion(const square from, const square to, const piece promoted) noexcept
			{
				assert(promoted.isValid());
				return move(from, to, 0b10, promoted);
			}
			constexpr static move promotionCapture(const square from, const square to, const piece promoted) noexcept
			{
				assert(promoted.isValid());
				return move(from, to, 0b11, promoted);
			}
			constexpr square from() const noexcept
			{
				return square1();
			}
			constexpr square to() const noexcept
			{
				return square2();
			}
			constexpr move(const move&) noexcept = default;
			constexpr move(move&&) noexcept = default;
			constexpr move& operator=(const move&) noexcept = default;
			constexpr move& operator=(move&&) noexcept = default;
			~move() noexcept = default;
			constexpr bool isEnPassant() const noexcept
			{
				return (channel() == 0b01) && (data() == 0b01);
			}
			constexpr bool isCastleQueenside() const noexcept
			{
				return (channel() == 0b00) && (data() == 0b10);
			}
			constexpr bool isCastleKingside() const noexcept
			{
				return (channel() == 0b00) && (data() == 0b11);
			}
			constexpr bool isPromotion() const noexcept
			{
				return channel() == 0b10;
			}
			constexpr bool isCapture() const noexcept
			{
				return (channel() == 0b11) || (channel() == 0b01);
			}
			constexpr bool isPromotionCapture() const noexcept
			{
				return channel() == 0b11;
			}
			constexpr bool isCastle() const noexcept
			{
				return isCastleQueenside() || isCastleKingside();
			}
			constexpr bool isDoublePush() const noexcept
			{
				return (channel() == 0b00) && (data() == 0b01);
			}
			constexpr board::piece get_PromotionPiece() const noexcept
			{
				assert(isPromotion() || isPromotionCapture());
				return data();
			}
		};
		using moveType = move;
		class movedata : public movedataBase
		{
		private:
			hashValue m_OldHash;
			hashValue m_OldPawnstructureHash;
			score m_OldMaterial;
			flags m_OldFlags;
			uint8_t m_OldDistanceToDraw;
			bool m_IsCapture;
			bool m_IsPromotion;
			bool m_IsDoublePush;
			bool m_IsCastling;
			square m_FromSquare;
			square m_ToSquare;
			player m_OtherPlayer;
			piece m_MovingPiece;
			piece m_TargetPiece;
			square m_CaptureSquare;
			piece m_CapturedPiece;
			square m_RookFrom;
			square m_RookTo;
			square m_WhiteKing;
			square m_BlackKing;
		public:
			constexpr auto oldHash() const noexcept
			{
				return m_OldHash;
			}
			constexpr auto oldPawnstructureHash() const noexcept
			{
				return m_OldPawnstructureHash;
			}
			constexpr auto oldMaterial() const noexcept
			{
				return m_OldMaterial;
			}
			constexpr auto oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			constexpr auto oldDistanceToDraw() const noexcept
			{
				return m_OldDistanceToDraw;
			}
			constexpr auto isCapture() const noexcept
			{
				return m_IsCapture;
			}
			constexpr auto isPromotion() const noexcept
			{
				return m_IsPromotion;
			}
			constexpr auto isDoublePush() const noexcept
			{
				return m_IsDoublePush;
			}
			constexpr auto isCastling() const noexcept
			{
				return m_IsCastling;
			}
			constexpr auto fromSquare() const noexcept
			{
				return m_FromSquare;
			}
			constexpr auto toSquare() const noexcept
			{
				return m_ToSquare;
			}
			constexpr auto otherPlayer() const noexcept
			{
				return m_OtherPlayer;
			}
			constexpr auto movingPiece() const noexcept
			{
				return m_MovingPiece;
			}
			constexpr auto targetPiece() const noexcept
			{
				return m_TargetPiece;
			}
			constexpr auto captureSquare() const noexcept
			{
				return m_CaptureSquare;
			}
			constexpr auto capturedPiece() const noexcept
			{
				return m_CapturedPiece;
			}
			constexpr auto rookFrom() const noexcept
			{
				return m_RookFrom;
			}
			constexpr auto rookTo() const noexcept
			{
				return m_RookTo;
			}
			constexpr auto whiteKing() const noexcept
			{
				return m_WhiteKing;
			}
			constexpr auto blackKing() const noexcept
			{
				return m_BlackKing;
			}
			movedata(const board& position, const player oldPlayer) noexcept;
			movedata(const board& position, const move& mv) noexcept;
			~movedata() noexcept = default;
		};
		static void makeMove_Implementation(board& position, const movedata& md) noexcept;
		static void unmakeMove_Implementation(board& position, const movedata& md) noexcept;
		class boardStack : public stack<movedata, boardStack>
		{
		private:
			mutable bitsType m_AttackedSquares[player::countValues];
			player m_OtherPlayer;
			mutable bool m_AttackedSquaresValid[player::countValues];
			mutable bool m_IsCheck;
			mutable bool m_IsCheckValid;
			void computeAttackSquares(const player p) const noexcept;
			void computeIsCheck() const noexcept;
		public:
			bool isMoveLegal_Implementation(const moveType& move) const noexcept;
			bool generateMoves_Implementation(movelistType& moves, int& currentPass) const noexcept;
			bool generateTacticalMoves_Implementation(movelistType& moves, int& currentPass) const noexcept;
			boardStack(const boardStack& parent, const moveType mv) noexcept;
			boardStack(instanceType& position, const player oldPlayer) noexcept;
			~boardStack() noexcept = default;
			constexpr player otherPlayer() const noexcept
			{
				return m_OtherPlayer;
			}
			bool isCheck() const noexcept
			{
				if (!m_IsCheckValid)
					computeIsCheck();
				return m_IsCheck;
			}
			bitsType attackedSquares(const player p) const noexcept
			{
				if (!m_AttackedSquaresValid[p])
					computeAttackSquares(p);
				return m_AttackedSquares[p];
			}
		};
		using stackType = boardStack;
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