namespace pygmalion::chess
{
	class movegen : public pygmalion::movegen<pygmalion::chess::board, 255, false, pygmalion::chess::board::movedata, pygmalion::chess::movegen>
	{
	private:
		static movegenTables m_Tables;
		static bitsType fillAttackRay_Up(const bitsType attackers, const bitsType notBlockers) noexcept
		{
			bitsType attacks{ boardType::up(attackers) };
			attacks |= boardType::up(attacks & notBlockers);
			attacks |= boardType::up(attacks & notBlockers);
			attacks |= boardType::up(attacks & notBlockers);
			attacks |= boardType::up(attacks & notBlockers);
			attacks |= boardType::up(attacks & notBlockers);
			attacks |= boardType::up(attacks & notBlockers);
			return attacks;
		}
		static bitsType fillAttackRay_Down(const bitsType attackers, const bitsType notBlockers) noexcept
		{
			bitsType attacks{ boardType::down(attackers) };
			attacks |= boardType::down(attacks & notBlockers);
			attacks |= boardType::down(attacks & notBlockers);
			attacks |= boardType::down(attacks & notBlockers);
			attacks |= boardType::down(attacks & notBlockers);
			attacks |= boardType::down(attacks & notBlockers);
			attacks |= boardType::down(attacks & notBlockers);
			return attacks;
		}
		static bitsType fillAttackRay_Right(const bitsType attackers, const bitsType notBlockers) noexcept
		{
			bitsType attacks{ boardType::right(attackers) };
			attacks |= boardType::right(attacks & notBlockers);
			attacks |= boardType::right(attacks & notBlockers);
			attacks |= boardType::right(attacks & notBlockers);
			attacks |= boardType::right(attacks & notBlockers);
			attacks |= boardType::right(attacks & notBlockers);
			attacks |= boardType::right(attacks & notBlockers);
			return attacks;
		}
		static bitsType fillAttackRay_Left(const bitsType attackers, const bitsType notBlockers) noexcept
		{
			bitsType attacks{ boardType::left(attackers) };
			attacks |= boardType::left(attacks & notBlockers);
			attacks |= boardType::left(attacks & notBlockers);
			attacks |= boardType::left(attacks & notBlockers);
			attacks |= boardType::left(attacks & notBlockers);
			attacks |= boardType::left(attacks & notBlockers);
			attacks |= boardType::left(attacks & notBlockers);
			return attacks;
		}
		static bitsType fillAttackRay_UpLeft(const bitsType attackers, const bitsType notBlockers) noexcept
		{
			bitsType attacks{ boardType::upLeft(attackers) };
			attacks |= boardType::upLeft(attacks & notBlockers);
			attacks |= boardType::upLeft(attacks & notBlockers);
			attacks |= boardType::upLeft(attacks & notBlockers);
			attacks |= boardType::upLeft(attacks & notBlockers);
			attacks |= boardType::upLeft(attacks & notBlockers);
			attacks |= boardType::upLeft(attacks & notBlockers);
			return attacks;
		}
		static bitsType fillAttackRay_UpRight(const bitsType attackers, const bitsType notBlockers) noexcept
		{
			bitsType attacks{ boardType::upRight(attackers) };
			attacks |= boardType::upRight(attacks & notBlockers);
			attacks |= boardType::upRight(attacks & notBlockers);
			attacks |= boardType::upRight(attacks & notBlockers);
			attacks |= boardType::upRight(attacks & notBlockers);
			attacks |= boardType::upRight(attacks & notBlockers);
			attacks |= boardType::upRight(attacks & notBlockers);
			return attacks;
		}
		static bitsType fillAttackRay_DownLeft(const bitsType attackers, const bitsType notBlockers) noexcept
		{
			bitsType attacks{ boardType::downLeft(attackers) };
			attacks |= boardType::downLeft(attacks & notBlockers);
			attacks |= boardType::downLeft(attacks & notBlockers);
			attacks |= boardType::downLeft(attacks & notBlockers);
			attacks |= boardType::downLeft(attacks & notBlockers);
			attacks |= boardType::downLeft(attacks & notBlockers);
			attacks |= boardType::downLeft(attacks & notBlockers);
			return attacks;
		}
		static bitsType fillAttackRay_DownRight(const bitsType attackers, const bitsType notBlockers) noexcept
		{
			bitsType attacks{ boardType::downRight(attackers) };
			attacks |= boardType::downRight(attacks & notBlockers);
			attacks |= boardType::downRight(attacks & notBlockers);
			attacks |= boardType::downRight(attacks & notBlockers);
			attacks |= boardType::downRight(attacks & notBlockers);
			attacks |= boardType::downRight(attacks & notBlockers);
			attacks |= boardType::downRight(attacks & notBlockers);
			return attacks;
		}
	public:
		using rankType = typename boardType::rank;
		using fileType = typename boardType::file;
		static movegenTables& tables() noexcept
		{
			return m_Tables;
		}
		static std::string name_Implementation() noexcept
		{
			return "Chess ver. 1.0";
		}
		constexpr static gamestateType earlyResult_Implementation(const stackType& stack) noexcept
		{
			return boardType::open();
		}
		static gamestateType lateResult_Implementation(const stackType& stack) noexcept
		{
			return stack.isCheck() ? boardType::draw() : boardType::loss(stack.movingPlayer());
		}
		static bitsType attackedSquares(const boardType& position, const playerType attackingPlayer) noexcept
		{
			assert(attackingPlayer.isValid());
			const bitsType attackerOccupancy{ position.playerOccupancy(attackingPlayer) };
			const bitsType knights{ position.pieceOccupancy(boardType::knight) & attackerOccupancy };
			bitsType attacked{ boardType::upUpLeft(knights) | boardType::upUpRight(knights) | boardType::downDownLeft(knights) | boardType::downDownRight(knights) | boardType::upLeftLeft(knights) | boardType::upRightRight(knights) | boardType::downLeftLeft(knights) | boardType::downRightRight(knights) };
			attacked |= m_Tables.kingMoveMap(position.kingSquare(attackingPlayer));
			const bitsType queens{ position.pieceOccupancy(boardType::queen) };
			const bitsType slidersHV{ (position.pieceOccupancy(boardType::rook) | queens) & attackerOccupancy };
			const bitsType slidersDiag{ (position.pieceOccupancy(boardType::bishop) | queens) & attackerOccupancy };
			const bitsType notBlockers = ~position.totalOccupancy();
			attacked |= fillAttackRay_Up(slidersHV, notBlockers) | fillAttackRay_Down(slidersHV, notBlockers) | fillAttackRay_Right(slidersHV, notBlockers) | fillAttackRay_Left(slidersHV, notBlockers);
			attacked |= fillAttackRay_UpLeft(slidersDiag, notBlockers) | fillAttackRay_UpRight(slidersDiag, notBlockers) | fillAttackRay_DownLeft(slidersDiag, notBlockers) | fillAttackRay_DownRight(slidersDiag, notBlockers);
			const bitsType pawns{ position.pieceOccupancy(boardType::pawn) & attackerOccupancy };
			attacked |= (attackingPlayer == boardType::whitePlayer) ? (boardType::upLeft(pawns) | boardType::upRight(pawns)) : (boardType::downLeft(pawns) | boardType::downRight(pawns));
			return attacked;
		}
		static bool isSquareAttackedByPlayer(const boardType& position, const squareType square, const playerType attackingPlayer) noexcept
		{
			const bitsType playerPieces{ position.playerOccupancy(attackingPlayer) };
			const bitsType attackingKnights{ m_Tables.knightMoveMap(square) & position.pieceOccupancy(boardType::knight) & playerPieces };
			if (attackingKnights)
				return true;
			const bitsType attackingKings{ m_Tables.kingMoveMap(square) & position.pieceOccupancy(boardType::king) & playerPieces };
			if (attackingKings)
				return true;
			const bitsType pawns{ position.pieceOccupancy(boardType::pawn) & playerPieces };
			const bitsType attackedByPawn{ attackingPlayer == boardType::whitePlayer ? boardType::upLeft(pawns) | boardType::upRight(pawns) : boardType::downLeft(pawns) | boardType::downRight(pawns) };
			if (attackedByPawn.checkBit(square))
				return true;
			const bitsType totalOccupancy{ position.totalOccupancy() };
			const bitsType slidersHV{ position.pieceOccupancy(boardType::queen) | position.pieceOccupancy(boardType::rook) };
			if (m_Tables.sliderAttacks(false, square, totalOccupancy, slidersHV) & playerPieces)
				return true;
			const bitsType slidersDiag{ position.pieceOccupancy(boardType::queen) | position.pieceOccupancy(boardType::bishop) };
			if (m_Tables.sliderAttacks(true, square, totalOccupancy, slidersDiag) & playerPieces)
				return true;
			return false;
		}
		static bitsType attackers(const boardType& position, const squareType square) noexcept
		{
			assert(square.isValid());
			bitsType attackers{ bitsType::empty() };
			attackers |= m_Tables.knightMoveMap(square) & position.pieceOccupancy(boardType::knight);
			attackers |= m_Tables.kingMoveMap(square) & position.pieceOccupancy(boardType::king);
			const bitsType whitepawns{ position.pieceOccupancy(boardType::pawn) & position.playerOccupancy(boardType::whitePlayer) };
			const bitsType blackpawns{ position.pieceOccupancy(boardType::pawn) & position.playerOccupancy(boardType::blackPlayer) };
			const bitsType piecemap{ bitsType::setMask(square) };
			attackers |= (board::downLeft(piecemap) | board::downRight(piecemap)) & whitepawns;
			attackers |= (board::upLeft(piecemap) | board::upRight(piecemap)) & blackpawns;
			const bitsType xraysHV{ position.pieceOccupancy(boardType::queen) | position.pieceOccupancy(boardType::rook) };
			const bitsType xraysDiag{ position.pieceOccupancy(boardType::queen) | position.pieceOccupancy(boardType::bishop) };
			const bitsType totalOCC{ position.totalOccupancy() };
			attackers |= m_Tables.sliderAttacks(false, square, totalOCC, xraysHV);
			attackers |= m_Tables.sliderAttacks(true, square, totalOCC, xraysDiag);
			return attackers;
		}
		static bitsType attackers(const boardType& position, const squareType square, const playerType attacker) noexcept
		{
			assert(square.isValid());
			bitsType attackers{ bitsType::empty() };
			attackers |= m_Tables.knightMoveMap(square) & position.pieceOccupancy(boardType::knight);
			attackers |= m_Tables.kingMoveMap(square) & position.pieceOccupancy(boardType::king);
			const bitsType pawns{ position.pieceOccupancy(boardType::pawn) & position.playerOccupancy(attacker) };
			const bitsType piecemap{ bitsType::setMask(square) };
			attackers |= (attacker == boardType::whitePlayer ? (board::downLeft(piecemap) | board::downRight(piecemap)) : (board::upLeft(piecemap) | board::upRight(piecemap))) & pawns;
			const bitsType xraysHV{ position.pieceOccupancy(boardType::queen) | position.pieceOccupancy(boardType::rook) };
			const bitsType xraysDiag{ position.pieceOccupancy(boardType::queen) | position.pieceOccupancy(boardType::bishop) };
			const bitsType totalOCC{ position.totalOccupancy() };
			attackers |= m_Tables.sliderAttacks(false, square, totalOCC, xraysHV);
			attackers |= m_Tables.sliderAttacks(true, square, totalOCC, xraysDiag);
			return attackers & position.playerOccupancy(attacker);
		}
		static bool isMoveLegal_Implementation(const stackType& stack, const moveType& move) noexcept
		{
			const boardType& position{ stack.position() };
			const playerType movingPlayer{ position.movingPlayer() };
			const playerType otherPlayer{ movingPlayer.next() };
			const squareType to{ move.to() };

			// are we illegally capturing the other king?
			const bool isCapture{ move.isCapture() };
			const squareType otherking{ position.kingSquare(otherPlayer) };
			if (isCapture && (otherking == to))
				return false;

			// No. Let's see where our king lives after the move as been made then...
			const squareType from{ move.from() };
			const squareType kingsquareOld{ position.kingSquare(movingPlayer) };
			const squareType kingsquare{ (from == kingsquareOld) ? to : kingsquareOld };

			// Does he live on a square that is guarded by the other king?
			const bitsType attacks_otherKing{ m_Tables.kingMoveMap(otherking) };
			if (attacks_otherKing.checkBit(kingsquare))
				return false;

			// We need the enemy occupancy bitboard as it would be after the move...
			const bitsType otherOccupancy{ position.playerOccupancy(otherPlayer) };
			const bitsType otherDelta{ isCapture ? (move.isEnPassant() ? bitsType::setMask(boardType::fromRankFile(boardType::rankOfSquare(from), boardType::fileOfSquare(to))) : bitsType::setMask(to)) : bitsType::empty() };
			const bitsType occOther{ otherOccupancy ^ otherDelta };

			// Does he live on a square that is guarded by an enemy knight?
			const bitsType otherKnights{ ((position.pieceOccupancy(boardType::knight) & otherOccupancy) ^ otherDelta) & occOther };
			const bitsType attacks_otherKnights{ boardType::upUpLeft(otherKnights) | boardType::upUpRight(otherKnights) | boardType::downDownLeft(otherKnights) | boardType::downDownRight(otherKnights) | boardType::upLeftLeft(otherKnights) | boardType::downLeftLeft(otherKnights) | boardType::upRightRight(otherKnights) | boardType::downRightRight(otherKnights) };
			if (attacks_otherKnights.checkBit(kingsquare))
				return false;

			// Does he live on a square that is guarded by an enemy pawn?
			const bitsType otherPawns{ ((position.pieceOccupancy(boardType::pawn) & otherOccupancy) ^ otherDelta) & occOther };
			const bitsType attacks_otherPawns{ (otherPlayer == boardType::whitePlayer) ? (boardType::upLeft(otherPawns) | boardType::upRight(otherPawns)) : (boardType::downLeft(otherPawns) | boardType::downRight(otherPawns)) };
			if (attacks_otherPawns.checkBit(kingsquare))
				return false;

			// We need the total occupancy bitboard as it would be after the move...
			const bitsType movingOccupancy{ position.playerOccupancy(movingPlayer) };
			const bitsType moveMask{ bitsType::setMask(from) ^ bitsType::setMask(to) };
			const bitsType movingDelta{ move.isCastle() ? (move.isCastleKingside() ? (moveMask ^ bitsType::setMask(boardType::fromRankFile(boardType::rankOfSquare(from), boardType::fileOfSquare(to) - 1)) ^ bitsType::setMask(boardType::fromRankFile(boardType::rankOfSquare(from),boardType::fileH))) : (moveMask ^ bitsType::setMask(boardType::fromRankFile(boardType::rankOfSquare(from), boardType::fileOfSquare(to) + 1)) ^ bitsType::setMask(boardType::fromRankFile(boardType::rankOfSquare(from),boardType::fileA)))) : moveMask };
			const bitsType occMoving{ movingOccupancy ^ movingDelta };
			const bitsType occTotal{ occOther | occMoving };

			// Is he attacked horizontally by sliding pieces?
			const bitsType queens{ position.pieceOccupancy(boardType::queen) };
			const bitsType otherSlidersHV = occOther & (position.pieceOccupancy(boardType::rook) | queens);
			if (m_Tables.sliderAttacks(false, kingsquare, occTotal, otherSlidersHV))
				return false;

			// Is he attacked diagonally by sliding pieces?
			const bitsType otherSlidersDiag = occOther & (position.pieceOccupancy(boardType::bishop) | queens);
			if (m_Tables.sliderAttacks(true, kingsquare, occTotal, otherSlidersDiag))
				return false;

			// The move seems legal
			return true;
		}
		static bitsType pawnMoveMap_untabled(const playerType side, const squareType square, const bool bCapture) noexcept;
		static bitsType knightMoveMap_untabled(const squareType square) noexcept;
		static bitsType kingMoveMap_untabled(const squareType square) noexcept;
		static bitsType sliderAttacks_untabled(const squareType square, const bitsType blockers, const bool bDiag) noexcept;
		static void sliderMoveMaps_untabled(const bool bDiag, const squareType square, const bitsType occupy, const bitsType capturetargets, bitsType& moves, bitsType& caps) noexcept;
		static void knightMoves(const boardType& position, const squareType from, const playerType otherPlayer, movelistType& moves) noexcept
		{
			assert(otherPlayer.isValid());
			assert(from.isValid());
			const bitsType knightMap{ m_Tables.knightMoveMap(from) };
			const bitsType moveMap{ knightMap & ~position.totalOccupancy() };
			for (const auto to : moveMap)
				moves.add(moveType::quiet(from, to));
			const bitsType captureMap{ knightMap & position.playerOccupancy(otherPlayer) };
			for (const auto to : captureMap)
				moves.add(moveType::capture(from, to));
		}
		static void knightCaptures(const boardType& position, const squareType from, const playerType otherPlayer, movelistType& moves) noexcept
		{
			assert(otherPlayer.isValid());
			assert(from.isValid());
			const bitsType knightMap{ m_Tables.knightMoveMap(from) };
			const bitsType captureMap{ knightMap & position.playerOccupancy(otherPlayer) };
			for (const auto to : captureMap)
				moves.add(moveType::capture(from, to));
		}
		static void kingMoves(const boardType& position, const squareType from, const playerType movingPlayer, const playerType otherPlayer, const bitsType forbidden, movelistType& moves) noexcept
		{
			assert(movingPlayer.isValid());
			assert(otherPlayer.isValid());
			assert(from.isValid());
			const bitsType kingMap{ m_Tables.kingMoveMap(from) };
			const bitsType totalOccupancy{ position.totalOccupancy() };
			const bitsType allowed{ ~forbidden };
			const bitsType moveMap{ (kingMap & ~totalOccupancy) & allowed };
			for (const auto to : moveMap)
				moves.add(moveType::quiet(from, to));
			const bitsType captureMap{ (kingMap & position.playerOccupancy(otherPlayer)) & allowed };
			for (const auto to : captureMap)
				moves.add(moveType::capture(from, to));
			if ((movingPlayer == boardType::whitePlayer) && (from == boardType::squareE1))
			{
				const typename boardType::flags flags{ position.getFlags() };
				if ((flags & boardType::castlerightKingsideWhite) && (!(boardType::kingsideCastleInterestWhite & totalOccupancy)) && (!(forbidden & boardType::kingsideCastleWalkWhite)))
					moves.add(moveType::castleKingside(boardType::whitePlayer));
				if ((flags & boardType::castlerightQueensideWhite) && (!(boardType::queensideCastleInterestWhite & totalOccupancy)) && (!(forbidden & boardType::queensideCastleWalkWhite)))
					moves.add(moveType::castleQueenside(boardType::whitePlayer));
			}
			else if ((movingPlayer == boardType::blackPlayer) && (from == boardType::squareE8))
			{
				const typename boardType::flags flags{ position.getFlags() };
				if ((flags & boardType::castlerightKingsideBlack) && (!(boardType::kingsideCastleInterestBlack & totalOccupancy)) && (!(forbidden & boardType::kingsideCastleWalkBlack)))
					moves.add(moveType::castleKingside(boardType::blackPlayer));
				if ((flags & boardType::castlerightQueensideBlack) && (!(boardType::queensideCastleInterestBlack & totalOccupancy)) && (!(forbidden & boardType::queensideCastleWalkBlack)))
					moves.add(moveType::castleQueenside(boardType::blackPlayer));
			}
		}
		static void kingCaptures(const boardType& position, const squareType from, const playerType movingPlayer, const playerType otherPlayer, const bitsType forbidden, movelistType& moves) noexcept
		{
			assert(movingPlayer.isValid());
			assert(otherPlayer.isValid());
			assert(from.isValid());
			const bitsType kingMap{ m_Tables.kingMoveMap(from) };
			const bitsType totalOccupancy{ position.totalOccupancy() };
			const bitsType allowed{ ~forbidden };
			const bitsType captureMap{ (kingMap & position.playerOccupancy(otherPlayer)) & allowed };
			for (const auto to : captureMap)
				moves.add(moveType::capture(from, to));
		}
		static void pawnMoves(const boardType& position, const squareType from, const playerType movingPlayer, const playerType otherPlayer, movelistType& moves) noexcept
		{
			assert(movingPlayer.isValid());
			assert(from.isValid());
			const bitsType freeSquares{ ~position.totalOccupancy() };
			const bitsType moveMap{ m_Tables.pawnMoveMap(from,movingPlayer) & freeSquares };
			const rankType fromRank{ boardType::rankOfSquare(from) };
			if (movingPlayer == boardType::whitePlayer)
			{
				if (fromRank == boardType::rank7)
				{
					for (const auto to : moveMap)
					{
						moves.add(moveType::promotion(from, to, board::queen));
						moves.add(moveType::promotion(from, to, board::knight));
						moves.add(moveType::promotion(from, to, board::rook));
						moves.add(moveType::promotion(from, to, board::bishop));
					}
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
					{
						moves.add(moveType::promotionCapture(from, to, board::queen));
						moves.add(moveType::promotionCapture(from, to, board::knight));
						moves.add(moveType::promotionCapture(from, to, board::rook));
						moves.add(moveType::promotionCapture(from, to, board::bishop));
					}
				}
				else
				{
					if (fromRank == boardType::rank2)
					{
						const squareType doublePushTo{ boardType::fromRankFile(boardType::rank4,boardType::fileOfSquare(from)) };
						const squareType doublePushOver{ boardType::fromRankFile(boardType::rank3,boardType::fileOfSquare(from)) };
						if (freeSquares.checkBit(doublePushTo) && freeSquares.checkBit(doublePushOver))
							moves.add(moveType::doublePush(from, doublePushTo));
					}
					else if (fromRank == boardType::rank5)
					{
						const fileType fromFile{ boardType::fileOfSquare(from) };
						const flagsType flags{ position.getFlags() };
						if ((fromFile != boardType::fileA) && (flags & boardType::enPassantFlags(fromFile - 1)))
							moves.add(moveType::captureEnPassant(from, boardType::fromRankFile(fromRank + 1, fromFile - 1)));
						if ((fromFile != boardType::fileH) && (flags & boardType::enPassantFlags(fromFile + 1)))
							moves.add(moveType::captureEnPassant(from, boardType::fromRankFile(fromRank + 1, fromFile + 1)));
					}
					for (const auto to : moveMap)
						moves.add(moveType::quiet(from, to));
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
						moves.add(moveType::capture(from, to));
				}
			}
			else
			{
				if (fromRank == boardType::rank2)
				{
					for (const auto to : moveMap)
					{
						moves.add(moveType::promotion(from, to, board::queen));
						moves.add(moveType::promotion(from, to, board::knight));
						moves.add(moveType::promotion(from, to, board::rook));
						moves.add(moveType::promotion(from, to, board::bishop));
					}
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
					{
						moves.add(moveType::promotionCapture(from, to, board::queen));
						moves.add(moveType::promotionCapture(from, to, board::knight));
						moves.add(moveType::promotionCapture(from, to, board::rook));
						moves.add(moveType::promotionCapture(from, to, board::bishop));
					}
				}
				else
				{
					if (fromRank == boardType::rank7)
					{
						const squareType doublePushTo{ boardType::fromRankFile(boardType::rank5,boardType::fileOfSquare(from)) };
						const squareType doublePushOver{ boardType::fromRankFile(boardType::rank6,boardType::fileOfSquare(from)) };
						if (freeSquares.checkBit(doublePushTo) && freeSquares.checkBit(doublePushOver))
							moves.add(moveType::doublePush(from, doublePushTo));
					}
					else if (fromRank == boardType::rank4)
					{
						const fileType fromFile{ boardType::fileOfSquare(from) };
						const flagsType flags{ position.getFlags() };
						if ((fromFile != boardType::fileA) && (flags & boardType::enPassantFlags(fromFile - 1)))
							moves.add(moveType::captureEnPassant(from, boardType::fromRankFile(fromRank - 1, fromFile - 1)));
						if ((fromFile != boardType::fileH) && (flags & boardType::enPassantFlags(fromFile + 1)))
							moves.add(moveType::captureEnPassant(from, boardType::fromRankFile(fromRank - 1, fromFile + 1)));
					}
					for (const auto to : moveMap)
						moves.add(moveType::quiet(from, to));
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
						moves.add(moveType::capture(from, to));
				}
			}
		}
		static void pawnCaptures(const boardType& position, const squareType from, const playerType movingPlayer, const playerType otherPlayer, movelistType& moves) noexcept
		{
			assert(movingPlayer.isValid());
			assert(from.isValid());
			const bitsType freeSquares{ ~position.totalOccupancy() };
			const rankType fromRank{ boardType::rankOfSquare(from) };
			if (movingPlayer == boardType::whitePlayer)
			{
				if (fromRank == boardType::rank7)
				{
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
					{
						moves.add(moveType::promotionCapture(from, to, board::queen));
						moves.add(moveType::promotionCapture(from, to, board::knight));
						moves.add(moveType::promotionCapture(from, to, board::rook));
						moves.add(moveType::promotionCapture(from, to, board::bishop));
					}
				}
				else
				{
					if (fromRank == boardType::rank5)
					{
						const fileType fromFile{ boardType::fileOfSquare(from) };
						const flagsType flags{ position.getFlags() };
						if ((fromFile != boardType::fileA) && (flags & boardType::enPassantFlags(fromFile - 1)))
							moves.add(moveType::captureEnPassant(from, boardType::fromRankFile(fromRank + 1, fromFile - 1)));
						if ((fromFile != boardType::fileH) && (flags & boardType::enPassantFlags(fromFile + 1)))
							moves.add(moveType::captureEnPassant(from, boardType::fromRankFile(fromRank + 1, fromFile + 1)));
					}
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
						moves.add(moveType::capture(from, to));
				}
			}
			else
			{
				if (fromRank == boardType::rank2)
				{
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
					{
						moves.add(moveType::promotionCapture(from, to, board::queen));
						moves.add(moveType::promotionCapture(from, to, board::knight));
						moves.add(moveType::promotionCapture(from, to, board::rook));
						moves.add(moveType::promotionCapture(from, to, board::bishop));
					}
				}
				else
				{
					if (fromRank == boardType::rank4)
					{
						const fileType fromFile{ boardType::fileOfSquare(from) };
						const flagsType flags{ position.getFlags() };
						if ((fromFile != boardType::fileA) && (flags & boardType::enPassantFlags(fromFile - 1)))
							moves.add(moveType::captureEnPassant(from, boardType::fromRankFile(fromRank - 1, fromFile - 1)));
						if ((fromFile != boardType::fileH) && (flags & boardType::enPassantFlags(fromFile + 1)))
							moves.add(moveType::captureEnPassant(from, boardType::fromRankFile(fromRank - 1, fromFile + 1)));
					}
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
						moves.add(moveType::capture(from, to));
				}
			}
		}
		static void sliderMoves(const boardType& position, const squareType from, const playerType otherPlayer, const bool diagonal, movelistType& moves) noexcept
		{
			assert(otherPlayer.isValid());
			assert(from.isValid());
			const bitsType totalOccupancy{ position.totalOccupancy() };
			const bitsType attackMask{ m_Tables.sliderAttackMask(diagonal,from,totalOccupancy) };
			const bitsType moveMap{ attackMask & ~totalOccupancy };
			for (const auto to : moveMap)
				moves.add(moveType::quiet(from, to));
			const bitsType captureMap{ attackMask & position.playerOccupancy(otherPlayer) };
			for (const auto to : captureMap)
				moves.add(moveType::capture(from, to));
		}
		static void sliderCaptures(const boardType& position, const squareType from, const playerType otherPlayer, const bool diagonal, movelistType& moves) noexcept
		{
			assert(otherPlayer.isValid());
			assert(from.isValid());
			const bitsType totalOccupancy{ position.totalOccupancy() };
			const bitsType attackMask{ m_Tables.sliderAttackMask(diagonal,from,totalOccupancy) };
			const bitsType captureMap{ attackMask & position.playerOccupancy(otherPlayer) };
			for (const auto to : captureMap)
				moves.add(moveType::capture(from, to));
		}
		static bool generateMoves_Implementation(const stackType& stack, movelistType& moves, int& currentPass) noexcept
		{
			const boardType& position{ stack.position() };
			const playerType movingPlayer{ stack.movingPlayer() };
			const playerType otherPlayer{ stack.otherPlayer() };
			const bitsType movingOccupancy{ position.playerOccupancy(movingPlayer) };
			switch (currentPass)
			{
			default:
				return false;
			case 0:
				for (const auto from : (position.pieceOccupancy(boardType::knight)& movingOccupancy))
					knightMoves(position, from, otherPlayer, moves);
				currentPass++;
				return true;
			case 1:
				for (const auto from : (position.pieceOccupancy(boardType::pawn)& movingOccupancy))
					pawnMoves(position, from, movingPlayer, otherPlayer, moves);
				currentPass++;
				return true;
			case 2:
				for (const auto from : ((position.pieceOccupancy(boardType::bishop) | position.pieceOccupancy(boardType::queen))& movingOccupancy))
					sliderMoves(position, from, otherPlayer, true, moves);
				currentPass++;
				return true;
			case 3:
				for (const auto from : ((position.pieceOccupancy(boardType::rook) | position.pieceOccupancy(boardType::queen))& movingOccupancy))
					sliderMoves(position, from, otherPlayer, false, moves);
				currentPass++;
				return true;
			case 4:
				for (const auto from : (position.pieceOccupancy(boardType::king)& movingOccupancy))
					kingMoves(position, from, movingPlayer, otherPlayer, stack.attackedSquares(otherPlayer), moves);
				currentPass++;
				return true;
			}
		}
		static bool generateTacticalMoves_Implementation(const stackType& stack, movelistType& moves, int& currentPass) noexcept
		{
			const boardType& position{ stack.position() };
			const playerType movingPlayer{ stack.movingPlayer() };
			const playerType otherPlayer{ stack.otherPlayer() };
			const bitsType movingOccupancy{ position.playerOccupancy(movingPlayer) };
			switch (currentPass)
			{
			default:
				return false;
			case 0:
				for (const auto from : (position.pieceOccupancy(boardType::knight)& movingOccupancy))
					knightCaptures(position, from, otherPlayer, moves);
				currentPass++;
				return true;
			case 1:
				for (const auto from : (position.pieceOccupancy(boardType::pawn)& movingOccupancy))
					pawnCaptures(position, from, movingPlayer, otherPlayer, moves);
				currentPass++;
				return true;
			case 2:
				for (const auto from : ((position.pieceOccupancy(boardType::bishop) | position.pieceOccupancy(boardType::queen))& movingOccupancy))
					sliderCaptures(position, from, otherPlayer, true, moves);
				currentPass++;
				return true;
			case 3:
				for (const auto from : ((position.pieceOccupancy(boardType::rook) | position.pieceOccupancy(boardType::queen))& movingOccupancy))
					sliderCaptures(position, from, otherPlayer, false, moves);
				currentPass++;
				return true;
			case 4:
				for (const auto from : (position.pieceOccupancy(boardType::king)& movingOccupancy))
					kingCaptures(position, from, movingPlayer, otherPlayer, stack.attackedSquares(otherPlayer), moves);
				currentPass++;
				return true;
			}
		}
		static void moveMaps(const boardType& position, const squareType square, bitsType& moves, bitsType& captures) noexcept
		{
			moves = bitsType::empty();
			captures = bitsType::empty();
			const bitsType totalOccupancy{ position.totalOccupancy() };
			if (!totalOccupancy.checkBit(square))
				return;
			const pieceType piece{ position.getPiece(square) };
			const playerType movingPlayer{ position.movingPlayer() };
			const playerType otherPlayer{ movingPlayer.next() };
			const bitsType captureTargets{ position.playerOccupancy(otherPlayer) };
			switch (piece)
			{
			default:
				assert(0);
				break;
			case boardType::rook:
				m_Tables.sliderMoveMaps(false, square, totalOccupancy, captureTargets, moves, captures);
				break;
			case boardType::bishop:
				m_Tables.sliderMoveMaps(true, square, totalOccupancy, captureTargets, moves, captures);
				break;
			case boardType::queen:
				m_Tables.sliderMoveMaps(false, square, totalOccupancy, captureTargets, moves, captures);
				m_Tables.sliderMoveMaps(true, square, totalOccupancy, captureTargets, moves, captures);
				break;
			case boardType::knight:
			{
				const bitsType atts{ m_Tables.knightMoveMap(square) };
				moves = atts & ~totalOccupancy;
				captures = atts & captureTargets;
				break;
			}
			case boardType::pawn:
				moves = m_Tables.pawnMoveMap(square, movingPlayer) & ~totalOccupancy;
				captures = m_Tables.pawnCaptureMap(square, movingPlayer) & captureTargets;
				if (movingPlayer == boardType::whitePlayer)
				{
					const rankType rank{ boardType::rankOfSquare(square) };
					if (rank == boardType::rank2)
					{
						moves |= boardType::up(moves) & ~totalOccupancy;
					}
					else if (rank == boardType::rank5)
					{
						const fileType file{ boardType::fileOfSquare(square) };
						const flagsType flags{ position.getFlags() };
						if ((file != boardType::fileA) && (flags & boardType::enPassantFlags(file - 1)))
							captures.setBit(boardType::fromRankFile(rank + 1, file - 1));
						else if ((file != boardType::fileH) && (flags & boardType::enPassantFlags(file + 1)))
							captures.setBit(boardType::fromRankFile(rank + 1, file + 1));
					}
				}
				else
				{
					const rankType rank{ boardType::rankOfSquare(square) };
					if (rank == boardType::rank2)
					{
						moves |= boardType::up(moves) & ~totalOccupancy;
					}
					else if (rank == boardType::rank4)
					{
						const fileType file{ boardType::fileOfSquare(square) };
						const flagsType flags{ position.getFlags() };
						if ((file != boardType::fileA) && (flags & boardType::enPassantFlags(file - 1)))
							captures.setBit(boardType::fromRankFile(rank - 1, file - 1));
						else if ((file != boardType::fileH) && (flags & boardType::enPassantFlags(file + 1)))
							captures.setBit(boardType::fromRankFile(rank - 1, file + 1));
					}
				}
				break;
			case boardType::king:
			{
				const bitsType forbidden{ attackedSquares(position,otherPlayer) };
				const bitsType atts2{ m_Tables.kingMoveMap(square) };
				moves = atts2 & ~totalOccupancy;
				captures = atts2 & captureTargets;
				if ((movingPlayer == boardType::whitePlayer) && (square == boardType::squareE1))
				{
					const typename boardType::flags flags{ position.getFlags() };
					if ((flags & boardType::castlerightKingsideWhite) && (!(boardType::kingsideCastleInterestWhite & totalOccupancy)) && (!(forbidden & boardType::kingsideCastleWalkWhite)))
						moves.setBit(boardType::squareG1);
					if ((flags & boardType::castlerightQueensideWhite) && (!(boardType::queensideCastleInterestWhite & totalOccupancy)) && (!(forbidden & boardType::queensideCastleWalkWhite)))
						moves.setBit(boardType::squareC1);
				}
				else if ((movingPlayer == boardType::blackPlayer) && (square == boardType::squareE8))
				{
					const typename boardType::flags flags{ position.getFlags() };
					if ((flags & boardType::castlerightKingsideBlack) && (!(boardType::kingsideCastleInterestBlack & totalOccupancy)) && (!(forbidden & boardType::kingsideCastleWalkBlack)))
						moves.setBit(boardType::squareG8);
					if ((flags & boardType::castlerightQueensideBlack) && (!(boardType::queensideCastleInterestBlack & totalOccupancy)) && (!(forbidden & boardType::queensideCastleWalkBlack)))
						moves.setBit(boardType::squareC8);
				}
			}
			break;
			}
		}
	};
}