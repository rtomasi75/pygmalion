namespace pygmalion::chess
{
	class mechanics :
		public pygmalion::mechanics<descriptor_mechanics, mechanics>
	{
	public:
		static void setCastlerightQueensideBlack(boardType& position) noexcept
		{
			position.flags().setBit(castlerightQueensideBlack);
		}
		static void setCastlerightQueensideWhite(boardType& position) noexcept
		{
			position.flags().setBit(castlerightQueensideWhite);
		}
		static void setCastlerightKingsideBlack(boardType& position) noexcept
		{
			position.flags().setBit(castlerightKingsideBlack);
		}
		static void setCastlerightKingsideWhite(boardType& position) noexcept
		{
			position.flags().setBit(castlerightKingsideWhite);
		}
		static void clearCastlerightQueensideBlack(boardType& position) noexcept
		{
			position.flags().clearBit(castlerightQueensideBlack);
		}
		static void clearCastlerightQueensideWhite(boardType& position) noexcept
		{
			position.flags().clearBit(castlerightQueensideWhite);
		}
		static void clearCastlerightKingsideBlack(boardType& position) noexcept
		{
			position.flags().clearBit(castlerightKingsideBlack);
		}
		static void clearCastlerightKingsideWhite(boardType& position) noexcept
		{
			position.flags().clearBit(castlerightKingsideWhite);
		}
		constexpr static bool checkCastlerightQueensideBlack(const boardType& position) noexcept
		{
			return position.flags().getBit(castlerightQueensideBlack);
		}
		constexpr static bool checkCastlerightQueensideWhite(const boardType& position) noexcept
		{
			return position.flags().getBit(castlerightQueensideWhite);
		}
		constexpr static bool checkCastlerightKingsideBlack(const boardType& position) noexcept
		{
			return position.flags().getBit(castlerightKingsideBlack);
		}
		constexpr static bool checkCastlerightKingsideWhite(const boardType& position) noexcept
		{
			return position.flags().getBit(castlerightKingsideWhite);
		}
		constexpr static bool checkEnPassantFlag(const boardType& position, const fileType f) noexcept
		{
			assert(f.isValid());
			return position.flags().getBit(enPassantFlag(f));
		}
		static void setEnPassantFlag(boardType& position, const fileType f) noexcept
		{
			assert(f.isValid());
			position.flags().setBit(enPassantFlag(f));
		}
		static void clearEnPassantFlags(boardType& position) noexcept
		{
			for (const auto f : fileType::range)
				position.flags().clearBit(enPassantFlag(f));
		}
		static squareType kingSquare(const boardType& position, const playerType p) noexcept
		{
			const squaresType kingOccupancy{ position.pieceOccupancy(king) & position.playerOccupancy(p) };
			assert(kingOccupancy);
			return kingOccupancy.first();
		}
		static bool isCapture(const moveType move) noexcept
		{
			return move.flags().getBit(capture);
		}
		static bool isCaptureEnPassant(const moveType move) noexcept
		{
			return move.flags().getBit(captureEnPassant) && isCapture(move);
		}
		static bool isDoublePush(const moveType move) noexcept
		{
			return move.flags().getBit(doublePush) && !isCapture(move);
		}
		static bool isCastleKingside(const moveType move) noexcept
		{
			return move.flags().getBit(castle) && (move.square(square_to).file() == fileH);
		}
		static bool isCastleQueenside(const moveType move) noexcept
		{
			return move.flags().getBit(castle) && (move.square(square_to).file() == fileA);
		}
		static bool isCastle(const moveType move) noexcept
		{
			return move.flags().getBit(castle);
		}
		static bool isPromotion(const moveType move) noexcept
		{
			return move.flags().getBit(promotion);
		}
		constexpr static moveType quietMove(const squareType from, const squareType to) noexcept
		{
			return moveType({ from,to }, { 0 }, 0);
		}
		constexpr static moveType doublePushMove(const squareType from, const squareType to) noexcept
		{
			return moveType({ from,to }, { 0 }, moveflagsType::setMask(doublePush));
		}
		constexpr static moveType captureMove(const squareType from, const squareType to) noexcept
		{
			return moveType({ from,to }, { 0 }, moveflagsType::setMask(capture));
		}
		constexpr static moveType castleKingsideWhite() noexcept
		{
			return moveType({ squareE1,squareH1 }, { 0 }, moveflagsType::setMask(castle));
		}
		constexpr static moveType castleKingsideBlack() noexcept
		{
			return moveType({ squareE8,squareH8 }, { 0 }, moveflagsType::setMask(castle));
		}
		constexpr static moveType castleQueensideWhite() noexcept
		{
			return moveType({ squareE1,squareA1 }, { 0 }, moveflagsType::setMask(castle));
		}
		constexpr static moveType castleQueensideBlack() noexcept
		{
			return moveType({ squareE8,squareA8 }, { 0 }, moveflagsType::setMask(castle));
		}
		constexpr static moveType captureEnPassantMove(const squareType from, const squareType to) noexcept
		{
			return moveType({ from,to }, { 0 }, moveflagsType::setMask(captureEnPassant) | moveflagsType::setMask(capture));
		}
		constexpr static moveType capturePromotionMove(const squareType from, const squareType to, const pieceType pc) noexcept
		{
			return moveType({ from,to }, { pc }, moveflagsType::setMask(promotion) | moveflagsType::setMask(capture));
		}
		constexpr static moveType promotionMove(const squareType from, const squareType to, const pieceType pc) noexcept
		{
			return moveType({ from,to }, { pc }, moveflagsType::setMask(promotion));
		}
		constexpr static squareType fromSquare(const moveType move) noexcept
		{
			return move.square(square_to);
		}
		constexpr static squareType toSquare(const moveType move) noexcept
		{
			return move.square(square_from);
		}
		constexpr static pieceType promotionPiece(const moveType move) noexcept
		{
			return move.piece(piece_promotion);
		}
		class movedata : 
			public pygmalion::mechanics<descriptor_mechanics, mechanics>::movedata
		{
		private:
			score m_OldMaterial;
			uint8_t m_OldDistanceToDraw;
			bool m_IsCapture;
			bool m_IsEnPassant;
			bool m_IsPromotion;
			bool m_IsDoublePush;
			bool m_IsCastling;
			flagsType m_OldFlags;
			squareType m_FromSquare;
			squareType m_ToSquare;
			playerType m_OtherPlayer;
			pieceType m_MovingPiece;
			pieceType m_TargetPiece;
			squareType m_CaptureSquare;
			pieceType m_CapturedPiece;
			squareType m_RookFrom;
			squareType m_RookTo;
		public:
			movedata(const board& position, const playerType oldPlayer) noexcept :
				pygmalion::mechanics<descriptor_mechanics, mechanics>::movedata(position, oldPlayer),
				m_OldMaterial{ position.getMaterial() },
				m_OldDistanceToDraw{ position.getDistanceToDraw() },
				m_IsPromotion{ false },
				m_IsCapture{ false },
				m_IsEnPassant{ false },
				m_IsDoublePush{ false },
				m_IsCastling{ false },
				m_FromSquare{ squareType::invalid },
				m_ToSquare{ squareType::invalid },
				m_OtherPlayer{ squareType::invalid },
				m_MovingPiece{ pieceType::invalid },
				m_TargetPiece{ pieceType::invalid },
				m_CaptureSquare{ squareType::invalid },
				m_CapturedPiece{ pieceType::invalid },
				m_RookFrom{ squareType::invalid },
				m_RookTo{ squareType::invalid },
				m_OldFlags{ position.flags() }
			{

			}
			movedata(const board& position, const moveType& move) noexcept :
				pygmalion::mechanics<descriptor_mechanics, mechanics>::movedata(position, move),
				m_OldMaterial{ position.getMaterial() },
				m_OldDistanceToDraw{ position.getDistanceToDraw() },
				m_IsPromotion{ mechanics::isPromotion(move) },
				m_IsCapture{ mechanics::isCapture(move) },
				m_IsEnPassant{ mechanics::isCaptureEnPassant(move) },
				m_IsDoublePush{ mechanics::isDoublePush(move) },
				m_IsCastling{ mechanics::isCastle(move) },
				m_FromSquare{ move.square(square_from) },
				m_ToSquare{ move.square(square_to) },
				m_OtherPlayer{ movingPlayer().next() },
				m_MovingPiece{ position.getPiece(m_FromSquare) },
				m_TargetPiece{ m_IsPromotion ? mechanics::promotionPiece(move) : m_MovingPiece },
				m_CaptureSquare{ squareType::invalid },
				m_CapturedPiece{ pieceType::invalid },
				m_RookFrom{ squareType::invalid },
				m_RookTo{ squareType::invalid },
				m_OldFlags{ position.flags() }
			{
				if (m_IsCapture)
				{
					if (m_IsEnPassant)
					{
						m_CaptureSquare = squareType::fromRankFile(m_FromSquare.rank(), m_ToSquare.file());
						m_CapturedPiece = pawn;
					}
					else
					{
						m_CaptureSquare = m_ToSquare;
						m_CapturedPiece = position.getPiece(m_CaptureSquare);
					}
				}
				else if (m_IsCastling)
				{
					const bool bWhite{ movingPlayer() == whitePlayer };
					const bool bKingSide{ isCastleKingside(move) };
					m_RookFrom = bKingSide ? (bWhite ? squareH1 : squareH8) : (bWhite ? squareA1 : squareA8);
					m_RookTo = bKingSide ? (bWhite ? squareF1 : squareF8) : (bWhite ? squareD1 : squareD8);
				}
			}
			constexpr auto oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			constexpr auto oldMaterial() const noexcept
			{
				return m_OldMaterial;
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
			constexpr auto isEnPassant() const noexcept
			{
				return m_IsEnPassant;
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
			~movedata() noexcept = default;
		};
		using movedataType = movedata;
		static void initializePosition_Implementation(boardType& position) noexcept
		{
			position.clear();
			position.setMovingPlayer(whitePlayer);
			// pawns
			for (const auto f : fileType::range)
			{
				position.addPiece(pawn, squareType::fromRankFile(rank2, f), whitePlayer);
//				position.material() += evaluator::material(whitePlayer, pawn, squareType::fromRankFile(rank2, f));
				position.addPiece(pawn, squareType::fromRankFile(rank7, f), blackPlayer);
//				position.material() += evaluator::material(blackPlayer, pawn, squareType::fromRankFile(rank7, f));
			}
			clearEnPassantFlags(position);
			// kings
			position.addPiece(king, squareE1, whitePlayer);
	//		position.material() += evaluator::material(whitePlayer, king, squareE1);
			position.addPiece(king, squareE8, blackPlayer);
	//		position.material() += evaluator::material(blackPlayer, king, squareE8);
			// rooks
			position.addPiece(rook, squareA1, whitePlayer);
	//		position.material() += evaluator::material(whitePlayer, rook, squareA1);
			position.addPiece(rook, squareH1, whitePlayer);
	//		position.material() += evaluator::material(whitePlayer, rook, squareH1);
			position.addPiece(rook, squareA8, blackPlayer);
	//		position.material() += evaluator::material(blackPlayer, rook, squareA8);
			position.addPiece(rook, squareH8, blackPlayer);
	//		position.material() += evaluator::material(blackPlayer, rook, squareH8);
			setCastlerightQueensideBlack(position);
			setCastlerightQueensideWhite(position);
			setCastlerightKingsideBlack(position);
			setCastlerightKingsideWhite(position);
			// knights
	/*		position.addPiece(knight, squareB1, whitePlayer);
			position.material() += evaluator::material(whitePlayer, knight, squareB1);
			position.addPiece(knight, squareG1, whitePlayer);
			position.material() += evaluator::material(whitePlayer, knight, squareG1);
			position.addPiece(knight, squareB8, blackPlayer);
			position.material() += evaluator::material(blackPlayer, knight, squareB8);
			position.addPiece(knight, squareG8, blackPlayer);
			position.material() += evaluator::material(blackPlayer, knight, squareG8);
			// bishops
			position.addPiece(bishop, squareC1, whitePlayer);
			position.material() += evaluator::material(whitePlayer, bishop, squareC1);
			position.addPiece(bishop, squareF1, whitePlayer);
			position.material() += evaluator::material(whitePlayer, bishop, squareF1);
			position.addPiece(bishop, squareC8, blackPlayer);
			position.material() += evaluator::material(blackPlayer, bishop, squareC8);
			position.addPiece(bishop, squareF8, blackPlayer);
			position.material() += evaluator::material(blackPlayer, bishop, squareF8);
			// queens
			position.addPiece(queen, squareD1, whitePlayer);
			position.material() += evaluator::material(whitePlayer, queen, squareD1);
			position.addPiece(queen, squareD8, blackPlayer);
			position.material() += evaluator::material(blackPlayer, queen, squareD8);*/
		}
		static void makeMove_Implementation(boardType& position, const movedata& md) noexcept
		{
			score newMaterial{ md.oldMaterial() };
			if (md.isCapture())
			{
				position.removePiece(md.capturedPiece(), md.captureSquare(), md.otherPlayer());
				position.setDistanceToDraw(DrawingDistance);
//				newMaterial -= evaluator::material(md.otherPlayer(), md.capturedPiece(), md.captureSquare());
				switch (md.capturedPiece())
				{
				case rook:
					if (md.otherPlayer() == blackPlayer)
					{
						if (md.captureSquare() == squareA8)
							clearCastlerightQueensideBlack(position);
						else if (md.captureSquare() == squareH8)
							clearCastlerightKingsideBlack(position);
					}
					else
					{
						if (md.captureSquare() == squareA1)
							clearCastlerightQueensideWhite(position);
						else if (md.captureSquare() == squareH1)
							clearCastlerightKingsideWhite(position);
					}
					break;
				}
			}
			else
				position.setDistanceToDraw(position.getDistanceToDraw() - 1);
			switch (md.movingPiece())
			{
			case king:
				if (md.movingPlayer() == blackPlayer)
				{
					clearCastlerightKingsideBlack(position);
					clearCastlerightQueensideBlack(position);
				}
				else
				{
					clearCastlerightKingsideWhite(position);
					clearCastlerightQueensideWhite(position);
				}
			case rook:
				if (md.movingPlayer() == blackPlayer)
				{
					if (md.fromSquare() == squareA8)
						clearCastlerightQueensideBlack(position);
					else if (md.fromSquare() == squareH8)
						clearCastlerightKingsideBlack(position);
				}
				else
				{
					if (md.fromSquare() == squareA1)
						clearCastlerightQueensideWhite(position);
					else if (md.fromSquare() == squareH1)
						clearCastlerightKingsideWhite(position);
				}
				break;
			}
			position.removePiece(md.movingPiece(), md.fromSquare(), md.movingPlayer());
		//	newMaterial -= evaluator::material(md.movingPlayer(), md.movingPiece(), md.fromSquare());
			position.addPiece(md.targetPiece(), md.toSquare(), md.movingPlayer());
		//	newMaterial += evaluator::material(md.movingPlayer(), md.targetPiece(), md.toSquare());
			clearEnPassantFlags(position);
			if (md.isDoublePush())
				setEnPassantFlag(position, md.toSquare().file());
			else if (md.isCastling())
			{
				position.removePiece(rook, md.rookFrom(), md.movingPlayer());
			//	newMaterial -= evaluator::material(md.movingPlayer(), rook, md.rookFrom());
				position.addPiece(rook, md.rookTo(), md.movingPlayer());
			//	newMaterial += evaluator::material(md.movingPlayer(), rook, md.rookTo());
			}
			position.setMovingPlayer(md.otherPlayer());
			position.setMaterial(newMaterial);
		}
		static void unmakeMove_Implementation(boardType& position, const movedata& md) noexcept
		{
			if (md.isCastling())
			{
				position.removePiece(rook, md.rookTo(), md.movingPlayer());
				position.addPiece(rook, md.rookFrom(), md.movingPlayer());
			}
			position.removePiece(md.targetPiece(), md.toSquare(), md.movingPlayer());
			position.addPiece(md.movingPiece(), md.fromSquare(), md.movingPlayer());
			if (md.isCapture())
				position.addPiece(md.capturedPiece(), md.captureSquare(), md.otherPlayer());
			position.setMaterial(md.oldMaterial());
			position.setDistanceToDraw(md.oldDistanceToDraw());
			position.setMovingPlayer(md.movingPlayer());
			position.flags() = md.oldFlags();
		}
	};

}