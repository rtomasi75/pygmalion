namespace pygmalion::chess
{

	class movegen : public pygmalion::movegen<board, descriptor_board, descriptor_movegen, pygmalion::chess::movedata, pygmalion::chess::stack, movegen>
	{
	private:
		static movegenTables m_Tables;
		using bitsType = typename boardType::bitsType;
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
		static movegenTables& tables() noexcept
		{
			return m_Tables;
		}
		static bitsType attackedSquares(const boardType& position, const playerType attackingPlayer) noexcept
		{
			assert(attackingPlayer.isValid());
			const bitsType attackerOccupancy{ position.playerOccupancy(attackingPlayer) };
			const bitsType knights{ position.pieceOccupancy(knight) & attackerOccupancy };
			bitsType attacked{ boardType::upUpLeft(knights) | boardType::upUpRight(knights) | boardType::downDownLeft(knights) | boardType::downDownRight(knights) | boardType::upLeftLeft(knights) | boardType::upRightRight(knights) | boardType::downLeftLeft(knights) | boardType::downRightRight(knights) };
			attacked |= m_Tables.kingMoveMap(position_kingSquare(position, attackingPlayer));
			const bitsType queens{ position.pieceOccupancy(queen) };
			const bitsType slidersHV{ (position.pieceOccupancy(rook) | queens) & attackerOccupancy };
			const bitsType slidersDiag{ (position.pieceOccupancy(bishop) | queens) & attackerOccupancy };
			const bitsType notBlockers = ~position.totalOccupancy();
			attacked |= fillAttackRay_Up(slidersHV, notBlockers) | fillAttackRay_Down(slidersHV, notBlockers) | fillAttackRay_Right(slidersHV, notBlockers) | fillAttackRay_Left(slidersHV, notBlockers);
			attacked |= fillAttackRay_UpLeft(slidersDiag, notBlockers) | fillAttackRay_UpRight(slidersDiag, notBlockers) | fillAttackRay_DownLeft(slidersDiag, notBlockers) | fillAttackRay_DownRight(slidersDiag, notBlockers);
			const bitsType pawns{ position.pieceOccupancy(pawn) & attackerOccupancy };
			attacked |= (attackingPlayer == whitePlayer) ? (boardType::upLeft(pawns) | boardType::upRight(pawns)) : (boardType::downLeft(pawns) | boardType::downRight(pawns));
			return attacked;
		}
		static bool isSquareAttackedByPlayer(const boardType& position, const squareType square, const playerType attackingPlayer) noexcept
		{
			const bitsType playerPieces{ position.playerOccupancy(attackingPlayer) };
			const bitsType attackingKnights{ m_Tables.knightMoveMap(square) & position.pieceOccupancy(knight) & playerPieces };
			if (attackingKnights)
				return true;
			const bitsType attackingKings{ m_Tables.kingMoveMap(square) & position.pieceOccupancy(king) & playerPieces };
			if (attackingKings)
				return true;
			const bitsType pawns{ position.pieceOccupancy(pawn) & playerPieces };
			const bitsType attackedByPawn{ attackingPlayer == whitePlayer ? boardType::upLeft(pawns) | boardType::upRight(pawns) : boardType::downLeft(pawns) | boardType::downRight(pawns) };
			if (attackedByPawn[square])
				return true;
			const bitsType totalOccupancy{ position.totalOccupancy() };
			const bitsType slidersHV{ position.pieceOccupancy(queen) | position.pieceOccupancy(rook) };
			if (m_Tables.sliderAttacks(false, square, totalOccupancy, slidersHV) & playerPieces)
				return true;
			const bitsType slidersDiag{ position.pieceOccupancy(queen) | position.pieceOccupancy(bishop) };
			if (m_Tables.sliderAttacks(true, square, totalOccupancy, slidersDiag) & playerPieces)
				return true;
			return false;
		}
		static bitsType attackers(const boardType& position, const squareType square) noexcept
		{
			assert(square.isValid());
			bitsType attackers{ bitsType::empty() };
			attackers |= m_Tables.knightMoveMap(square) & position.pieceOccupancy(knight);
			attackers |= m_Tables.kingMoveMap(square) & position.pieceOccupancy(king);
			const bitsType whitepawns{ position.pieceOccupancy(pawn) & position.playerOccupancy(whitePlayer) };
			const bitsType blackpawns{ position.pieceOccupancy(pawn) & position.playerOccupancy(blackPlayer) };
			const bitsType piecemap{ bitsType::setMask(square) };
			attackers |= (board::downLeft(piecemap) | board::downRight(piecemap)) & whitepawns;
			attackers |= (board::upLeft(piecemap) | board::upRight(piecemap)) & blackpawns;
			const bitsType xraysHV{ position.pieceOccupancy(queen) | position.pieceOccupancy(rook) };
			const bitsType xraysDiag{ position.pieceOccupancy(queen) | position.pieceOccupancy(bishop) };
			const bitsType totalOCC{ position.totalOccupancy() };
			attackers |= m_Tables.sliderAttacks(false, square, totalOCC, xraysHV);
			attackers |= m_Tables.sliderAttacks(true, square, totalOCC, xraysDiag);
			return attackers;
		}
		static bitsType attackers(const boardType& position, const squareType square, const playerType attacker) noexcept
		{
			assert(square.isValid());
			bitsType attackers{ bitsType::empty() };
			attackers |= m_Tables.knightMoveMap(square) & position.pieceOccupancy(knight);
			attackers |= m_Tables.kingMoveMap(square) & position.pieceOccupancy(king);
			const bitsType pawns{ position.pieceOccupancy(pawn) & position.playerOccupancy(attacker) };
			const bitsType piecemap{ bitsType::setMask(square) };
			attackers |= (attacker == whitePlayer ? (board::downLeft(piecemap) | board::downRight(piecemap)) : (board::upLeft(piecemap) | board::upRight(piecemap))) & pawns;
			const bitsType xraysHV{ position.pieceOccupancy(queen) | position.pieceOccupancy(rook) };
			const bitsType xraysDiag{ position.pieceOccupancy(queen) | position.pieceOccupancy(bishop) };
			const bitsType totalOCC{ position.totalOccupancy() };
			attackers |= m_Tables.sliderAttacks(false, square, totalOCC, xraysHV);
			attackers |= m_Tables.sliderAttacks(true, square, totalOCC, xraysDiag);
			return attackers & position.playerOccupancy(attacker);
		}
		static bool position_isCheck(const boardType& position) noexcept
		{
			return isSquareAttackedByPlayer(position, position_kingSquare(position, position.movingPlayer()), position.movingPlayer().next());
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
				moves.add(move_quiet(from, to));
			const bitsType captureMap{ knightMap & position.playerOccupancy(otherPlayer) };
			for (const auto to : captureMap)
				moves.add(move_capture(from, to));
		}
		static void knightCaptures(const boardType& position, const squareType from, const playerType otherPlayer, movelistType& moves) noexcept
		{
			assert(otherPlayer.isValid());
			assert(from.isValid());
			const bitsType knightMap{ m_Tables.knightMoveMap(from) };
			const bitsType captureMap{ knightMap & position.playerOccupancy(otherPlayer) };
			for (const auto to : captureMap)
				moves.add(move_capture(from, to));
		}
		static void castles(const boardType& position, const squareType from, const playerType movingPlayer, const playerType otherPlayer, const bitsType forbidden, movelistType& moves) noexcept
		{
			assert(movingPlayer.isValid());
			assert(otherPlayer.isValid());
			assert(from.isValid());
			const bitsType totalOccupancy{ position.totalOccupancy() };
			if ((movingPlayer == whitePlayer) && (from == squareE1))
			{
				if (position_checkCastlerightKingsideWhite(position) && (!(kingsideCastleInterestWhite & totalOccupancy)) && (!(forbidden & kingsideCastleWalkWhite)))
					moves.add(move_castleKingsideWhite());
				if (position_checkCastlerightQueensideWhite(position) && (!(queensideCastleInterestWhite & totalOccupancy)) && (!(forbidden & queensideCastleWalkWhite)))
					moves.add(move_castleQueensideWhite());
			}
			else if ((movingPlayer == blackPlayer) && (from == squareE8))
			{
				if (position_checkCastlerightKingsideBlack(position) && (!(kingsideCastleInterestBlack & totalOccupancy)) && (!(forbidden & kingsideCastleWalkBlack)))
					moves.add(move_castleKingsideBlack());
				if (position_checkCastlerightQueensideBlack(position) && (!(queensideCastleInterestBlack & totalOccupancy)) && (!(forbidden & queensideCastleWalkBlack)))
					moves.add(move_castleQueensideBlack());
			}
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
				moves.add(move_quiet(from, to));
			const bitsType captureMap{ (kingMap & position.playerOccupancy(otherPlayer)) & allowed };
			for (const auto to : captureMap)
				moves.add(move_capture(from, to));
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
				moves.add(move_capture(from, to));
		}
		static void doublePushes(const boardType& position, const squareType from, const playerType movingPlayer, const playerType otherPlayer, movelistType& moves) noexcept
		{
			assert(movingPlayer.isValid());
			assert(from.isValid());
			const rankType fromRank{ from.rank() };
			if (movingPlayer == whitePlayer)
			{
				if (fromRank == rank2)
				{
					const bitsType freeSquares{ ~position.totalOccupancy() };
					const bitsType moveMap{ m_Tables.pawnMoveMap(from,movingPlayer) & freeSquares };
					const bitsType doublePushMap{ boardType::up(moveMap) & freeSquares };
					for (const auto to : doublePushMap)
						moves.add(move_doublePush(from, to));
				}
			}
			else
			{
				if (fromRank == rank7)
				{
					const bitsType freeSquares{ ~position.totalOccupancy() };
					const bitsType moveMap{ m_Tables.pawnMoveMap(from,movingPlayer) & freeSquares };
					const bitsType doublePushMap{ boardType::down(moveMap) & freeSquares };
					for (const auto to : doublePushMap)
						moves.add(move_doublePush(from, to));
				}
			}
		}
		static void promotions(const boardType& position, const squareType from, const playerType movingPlayer, const playerType otherPlayer, movelistType& moves) noexcept
		{
			assert(movingPlayer.isValid());
			assert(from.isValid());
			const rankType fromRank{ from.rank() };
			if (movingPlayer == whitePlayer)
			{
				if (fromRank == rank7)
				{
					const bitsType freeSquares{ ~position.totalOccupancy() };
					const bitsType moveMap{ m_Tables.pawnMoveMap(from,movingPlayer) & freeSquares };
					for (const auto to : moveMap)
					{
						moves.add(move_promotion(from, to, queen));
						moves.add(move_promotion(from, to, knight));
						moves.add(move_promotion(from, to, rook));
						moves.add(move_promotion(from, to, bishop));
					}
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
					{
						moves.add(move_capturePromotion(from, to, queen));
						moves.add(move_capturePromotion(from, to, knight));
						moves.add(move_capturePromotion(from, to, rook));
						moves.add(move_capturePromotion(from, to, bishop));
					}
				}
			}
			else
			{
				if (fromRank == rank2)
				{
					const bitsType freeSquares{ ~position.totalOccupancy() };
					const bitsType moveMap{ m_Tables.pawnMoveMap(from,movingPlayer) & freeSquares };
					for (const auto to : moveMap)
					{
						moves.add(move_promotion(from, to, queen));
						moves.add(move_promotion(from, to, knight));
						moves.add(move_promotion(from, to, rook));
						moves.add(move_promotion(from, to, bishop));
					}
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
					{
						moves.add(move_capturePromotion(from, to, queen));
						moves.add(move_capturePromotion(from, to, knight));
						moves.add(move_capturePromotion(from, to, rook));
						moves.add(move_capturePromotion(from, to, bishop));
					}
				}
			}
		}
		static void promotionCaptures(const boardType& position, const squareType from, const playerType movingPlayer, const playerType otherPlayer, movelistType& moves) noexcept
		{
			assert(movingPlayer.isValid());
			assert(from.isValid());
			const rankType fromRank{ from.rank() };
			if (movingPlayer == whitePlayer)
			{
				if (fromRank == rank7)
				{
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
					{
						moves.add(move_capturePromotion(from, to, queen));
						moves.add(move_capturePromotion(from, to, knight));
						moves.add(move_capturePromotion(from, to, rook));
						moves.add(move_capturePromotion(from, to, bishop));
					}
				}
			}
			else
			{
				if (fromRank == rank2)
				{
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
					{
						moves.add(move_capturePromotion(from, to, queen));
						moves.add(move_capturePromotion(from, to, knight));
						moves.add(move_capturePromotion(from, to, rook));
						moves.add(move_capturePromotion(from, to, bishop));
					}
				}
			}
		}
		static void pawnMoves(const boardType& position, const squareType from, const playerType movingPlayer, const playerType otherPlayer, movelistType& moves) noexcept
		{
			assert(movingPlayer.isValid());
			assert(from.isValid());
			const rankType fromRank{ from.rank() };
			if (movingPlayer == whitePlayer)
			{
				if (fromRank != rank7)
				{
					const bitsType freeSquares{ ~position.totalOccupancy() };
					const bitsType moveMap{ m_Tables.pawnMoveMap(from,movingPlayer) & freeSquares };
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : moveMap)
						moves.add(move_quiet(from, to));
					for (const auto to : captureMap)
						moves.add(move_capture(from, to));
				}
			}
			else
			{
				if (fromRank != rank2)
				{
					const bitsType freeSquares{ ~position.totalOccupancy() };
					const bitsType moveMap{ m_Tables.pawnMoveMap(from,movingPlayer) & freeSquares };
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : moveMap)
						moves.add(move_quiet(from, to));
					for (const auto to : captureMap)
						moves.add(move_capture(from, to));
				}
			}
		}
		static void enPassantCaptures(const boardType& position, const squareType from, const playerType movingPlayer, const playerType otherPlayer, movelistType& moves) noexcept
		{
			assert(movingPlayer.isValid());
			assert(from.isValid());
			const rankType fromRank{ from.rank() };
			if (movingPlayer == whitePlayer)
			{
				if (fromRank == rank5)
				{
					const fileType fromFile{ from.file() };
					if ((fromFile != fileA) && position_checkEnPassantFlag(position, fromFile - 1))
						moves.add(move_captureEnPassant(from, squareType::fromRankFile(fromRank + 1, fromFile - 1)));
					if ((fromFile != fileH) && position_checkEnPassantFlag(position, fromFile + 1))
						moves.add(move_captureEnPassant(from, squareType::fromRankFile(fromRank + 1, fromFile + 1)));
				}
			}
			else
			{
				if (fromRank == rank4)
				{
					const fileType fromFile{ from.file() };
					if ((fromFile != fileA) && position_checkEnPassantFlag(position, fromFile - 1))
						moves.add(move_captureEnPassant(from, squareType::fromRankFile(fromRank - 1, fromFile - 1)));
					if ((fromFile != fileH) && position_checkEnPassantFlag(position, fromFile + 1))
						moves.add(move_captureEnPassant(from, squareType::fromRankFile(fromRank - 1, fromFile + 1)));
				}
			}
		}
		static void pawnCaptures(const boardType& position, const squareType from, const playerType movingPlayer, const playerType otherPlayer, movelistType& moves) noexcept
		{
			assert(movingPlayer.isValid());
			assert(from.isValid());
			const rankType fromRank{ from.rank() };
			if (movingPlayer == whitePlayer)
			{
				if (fromRank != rank7)
				{
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
						moves.add(move_capture(from, to));
				}
			}
			else
			{
				if (fromRank != rank2)
				{
					const bitsType captureMap{ m_Tables.pawnCaptureMap(from,movingPlayer) & position.playerOccupancy(otherPlayer) };
					for (const auto to : captureMap)
						moves.add(move_capture(from, to));
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
				moves.add(move_quiet(from, to));
			const bitsType captureMap{ attackMask & position.playerOccupancy(otherPlayer) };
			for (const auto to : captureMap)
				moves.add(move_capture(from, to));
		}
		static void sliderCaptures(const boardType& position, const squareType from, const playerType otherPlayer, const bool diagonal, movelistType& moves) noexcept
		{
			assert(otherPlayer.isValid());
			assert(from.isValid());
			const bitsType totalOccupancy{ position.totalOccupancy() };
			const bitsType attackMask{ m_Tables.sliderAttackMask(diagonal,from,totalOccupancy) };
			const bitsType captureMap{ attackMask & position.playerOccupancy(otherPlayer) };
			for (const auto to : captureMap)
				moves.add(move_capture(from, to));
		}
		static void moveMaps(const boardType& position, const squareType square, bitsType& moves, bitsType& captures) noexcept
		{
			moves = bitsType::empty();
			captures = bitsType::empty();
			const bitsType totalOccupancy{ position.totalOccupancy() };
			if (!totalOccupancy[square])
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
			case rook:
				m_Tables.sliderMoveMaps(false, square, totalOccupancy, captureTargets, moves, captures);
				break;
			case bishop:
				m_Tables.sliderMoveMaps(true, square, totalOccupancy, captureTargets, moves, captures);
				break;
			case queen:
				m_Tables.sliderMoveMaps(false, square, totalOccupancy, captureTargets, moves, captures);
				m_Tables.sliderMoveMaps(true, square, totalOccupancy, captureTargets, moves, captures);
				break;
			case knight:
			{
				const bitsType atts{ m_Tables.knightMoveMap(square) };
				moves = atts & ~totalOccupancy;
				captures = atts & captureTargets;
				break;
			}
			case pawn:
				moves = m_Tables.pawnMoveMap(square, movingPlayer) & ~totalOccupancy;
				captures = m_Tables.pawnCaptureMap(square, movingPlayer) & captureTargets;
				if (movingPlayer == whitePlayer)
				{
					const rankType rank{ square.rank() };
					if (rank == rank2)
					{
						moves |= boardType::up(moves) & ~totalOccupancy;
					}
					else if (rank == rank5)
					{
						const fileType file{ square.file() };
						if ((file != fileA) && position_checkEnPassantFlag(position, file - 1))
							captures.setBit(squareType::fromRankFile(rank + 1, file - 1));
						else if ((file != fileH) && position_checkEnPassantFlag(position, file + 1))
							captures.setBit(squareType::fromRankFile(rank + 1, file + 1));
					}
				}
				else
				{
					const rankType rank{ square.rank() };
					if (rank == rank7)
					{
						moves |= boardType::down(moves) & ~totalOccupancy;
					}
					else if (rank == rank4)
					{
						const fileType file{ square.file() };
						if ((file != fileA) && position_checkEnPassantFlag(position, file - 1))
							captures.setBit(squareType::fromRankFile(rank - 1, file - 1));
						else if ((file != fileH) && position_checkEnPassantFlag(position, file + 1))
							captures.setBit(squareType::fromRankFile(rank - 1, file + 1));
					}
				}
				break;
			case king:
			{
				const bitsType forbidden{ attackedSquares(position,otherPlayer) };
				const bitsType atts2{ m_Tables.kingMoveMap(square) };
				moves = atts2 & ~totalOccupancy;
				captures = atts2 & captureTargets;
				if ((movingPlayer == whitePlayer) && (square == squareE1))
				{
					if (position_checkCastlerightKingsideWhite(position) && (!(kingsideCastleInterestWhite & totalOccupancy)) && (!(forbidden & kingsideCastleWalkWhite)))
						moves.setBit(squareG1);
					if (position_checkCastlerightQueensideWhite(position) && (!(queensideCastleInterestWhite & totalOccupancy)) && (!(forbidden & queensideCastleWalkWhite)))
						moves.setBit(squareC1);
				}
				else if ((movingPlayer == blackPlayer) && (square == squareE8))
				{
					if (position_checkCastlerightKingsideBlack(position) && (!(kingsideCastleInterestBlack & totalOccupancy)) && (!(forbidden & kingsideCastleWalkBlack)))
						moves.setBit(squareG8);
					if (position_checkCastlerightQueensideBlack(position) && (!(queensideCastleInterestBlack & totalOccupancy)) && (!(forbidden & queensideCastleWalkBlack)))
						moves.setBit(squareC8);
				}
			}
			break;
			}
		}

		static std::string name_Implementation() noexcept
		{
			return "Chess ver. 1.0";
		}
		static gamestateType earlyResult_Implementation(const stackType& stack) noexcept
		{
			if (stack.position().getDistanceToDraw() <= 0)
				return boardType::draw();
			if ((stack.position().pieceOccupancy(pawn) | stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen)) == bitsType::empty())
			{
				if ((stack.position().pieceOccupancy(knight) == bitsType::empty()) && (stack.position().pieceOccupancy(bishop).populationCount() <= 1))
					return boardType::draw();
				if ((stack.position().pieceOccupancy(bishop) == bitsType::empty()) && (stack.position().pieceOccupancy(knight).populationCount() <= 1))
					return boardType::draw();
				if (stack.position().pieceOccupancy(bishop) == bitsType::empty())
				{
					if (((stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(blackPlayer)) == bitsType::empty()) && ((stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(whitePlayer)).populationCount() <= 2))
						return boardType::draw();
					if (((stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(whitePlayer)) == bitsType::empty()) && ((stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(blackPlayer)).populationCount() <= 2))
						return boardType::draw();
				}
			}
			return boardType::open();
		}
		static gamestateType lateResult_Implementation(const stackType& stack) noexcept
		{
			return stack.isCheck() ? boardType::draw() : boardType::loss(stack.movingPlayer());
		}
		static bool isMoveLegal_Implementation(const stackType& stack, const moveType& move) noexcept
		{
			const boardType& position{ stack.position() };
			const playerType movingPlayer{ position.movingPlayer() };
			const playerType otherPlayer{ movingPlayer.next() };
			const squareType to{ move_to(move) };

			// are we illegally capturing the other king?
			const bool isCapture{ move_isCapture(move) };
			const squareType otherking{ position_kingSquare(position,otherPlayer) };
			if (isCapture && (otherking == to))
				return false;

			// No. Let's see where our king lives after the move as been made then...
			const squareType from{ move_from(move) };
			const squareType kingsquareOld{ position_kingSquare(position,movingPlayer) };
			const squareType kingsquare{ (from == kingsquareOld) ? to : kingsquareOld };

			// Does he live on a square that is guarded by the other king?
			const bitsType attackedByOtherKing{ m_Tables.kingMoveMap(otherking) };
			if (attackedByOtherKing[kingsquare])
				return false;

			// We need the enemy occupancy bitboard as it would be after the move...
			const bitsType otherOccupancy{ position.playerOccupancy(otherPlayer) };
			const bitsType otherDelta{ isCapture ? (move_isCaptureEnPassant(move) ? bitsType::setMask(squareType::fromRankFile(from.rank(), to.file())) : bitsType::setMask(to)) : bitsType::empty() };
			const bitsType occOther{ otherOccupancy ^ otherDelta };

			// Does he live on a square that is guarded by an enemy knight?
			const bitsType otherKnights{ ((position.pieceOccupancy(knight) & otherOccupancy) ^ otherDelta) & occOther };
			const bitsType attackedByOtherKnights{ boardType::upUpLeft(otherKnights) | boardType::upUpRight(otherKnights) | boardType::downDownLeft(otherKnights) | boardType::downDownRight(otherKnights) | boardType::upLeftLeft(otherKnights) | boardType::downLeftLeft(otherKnights) | boardType::upRightRight(otherKnights) | boardType::downRightRight(otherKnights) };
			if (attackedByOtherKnights[kingsquare])
				return false;

			// Does he live on a square that is guarded by an enemy pawn?
			const bitsType otherPawns{ ((position.pieceOccupancy(pawn) & otherOccupancy) ^ otherDelta) & occOther };
			const bitsType attackedByOtherPawns{ (otherPlayer == whitePlayer) ? (boardType::upLeft(otherPawns) | boardType::upRight(otherPawns)) : (boardType::downLeft(otherPawns) | boardType::downRight(otherPawns)) };
			if (attackedByOtherPawns[kingsquare])
				return false;

			// We need the total occupancy bitboard as it would be after the move...
			const bitsType movingOccupancy{ position.playerOccupancy(movingPlayer) };
			const bitsType moveMask{ bitsType::setMask(from) ^ bitsType::setMask(to) };
			const bitsType movingDelta{ move_isCastleQueenside(move) ? (move_isCastleKingside(move) ? (moveMask ^ bitsType::setMask(squareType::fromRankFile(from.rank(), to.file() - 1)) ^ bitsType::setMask(squareType::fromRankFile(from.rank(),fileH))) : (moveMask ^ bitsType::setMask(squareType::fromRankFile(from.rank(),to.file() + 1)) ^ bitsType::setMask(squareType::fromRankFile(from.rank(),fileA)))) : moveMask };
			const bitsType occMoving{ movingOccupancy ^ movingDelta };
			const bitsType occTotal{ occOther | occMoving };

			// Is he attacked horizontally by sliding pieces?
			const bitsType queens{ position.pieceOccupancy(queen) };
			const bitsType otherSlidersHV = occOther & (position.pieceOccupancy(rook) | queens);
			if (m_Tables.sliderAttacks(false, kingsquare, occTotal, otherSlidersHV))
				return false;

			// Is he attacked diagonally by sliding pieces?
			const bitsType otherSlidersDiag = occOther & (position.pieceOccupancy(bishop) | queens);
			if (m_Tables.sliderAttacks(true, kingsquare, occTotal, otherSlidersDiag))
				return false;

			// The move seems legal
			return true;
		}
		static bool generateMoves_Implementation(const stackType& stack, movelistType& moves, int& currentPass) noexcept
		{
			const boardType& position{ stack.position() };
			const playerType movingPlayer{ stack.movingPlayer() };
			const playerType otherPlayer{ stack.nextPlayer() };
			const bitsType movingOccupancy{ position.playerOccupancy(movingPlayer) };
			switch (currentPass)
			{
			default:
				return false;
			case 0:
				for (const auto from : (position.pieceOccupancy(pawn)& movingOccupancy))
					doublePushes(position, from, movingPlayer, otherPlayer, moves);
				currentPass++;
				return true;
			case 1:
				for (const auto from : (position.pieceOccupancy(pawn)& movingOccupancy))
					pawnMoves(position, from, movingPlayer, otherPlayer, moves);
				currentPass++;
				return true;
			case 2:
				for (const auto from : (position.pieceOccupancy(pawn)& movingOccupancy))
					enPassantCaptures(position, from, movingPlayer, otherPlayer, moves);
				currentPass++;
				return true;
			case 3:
				for (const auto from : (position.pieceOccupancy(knight)& movingOccupancy))
					knightMoves(position, from, otherPlayer, moves);
				currentPass++;
				return true;
			case 4:
				for (const auto from : ((position.pieceOccupancy(bishop) | position.pieceOccupancy(queen))& movingOccupancy))
					sliderMoves(position, from, otherPlayer, true, moves);
				currentPass++;
				return true;
			case 5:
				for (const auto from : ((position.pieceOccupancy(rook) | position.pieceOccupancy(queen))& movingOccupancy))
					sliderMoves(position, from, otherPlayer, false, moves);
				currentPass++;
				return true;
			case 6:
				for (const auto from : (position.pieceOccupancy(king)& movingOccupancy))
					kingMoves(position, from, movingPlayer, otherPlayer, stack.attackedSquares(otherPlayer), moves);
				currentPass++;
			case 7:
				for (const auto from : (position.pieceOccupancy(king)& movingOccupancy))
					castles(position, from, movingPlayer, otherPlayer, stack.attackedSquares(otherPlayer), moves);
				currentPass++;
				return true;
			}
		}
		static bool generateTacticalMoves_Implementation(const stackType& stack, movelistType& moves, int& currentPass) noexcept
		{
			const boardType& position{ stack.position() };
			const playerType movingPlayer{ stack.movingPlayer() };
			const playerType otherPlayer{ stack.nextPlayer() };
			const bitsType movingOccupancy{ position.playerOccupancy(movingPlayer) };
			switch (currentPass)
			{
			default:
				return false;
			case 0:
				for (const auto from : (position.pieceOccupancy(pawn)& movingOccupancy))
					pawnCaptures(position, from, movingPlayer, otherPlayer, moves);
				currentPass++;
				return true;
			case 1:
				for (const auto from : (position.pieceOccupancy(pawn)& movingOccupancy))
					enPassantCaptures(position, from, movingPlayer, otherPlayer, moves);
				currentPass++;
				return true;
			case 2:
				for (const auto from : (position.pieceOccupancy(knight)& movingOccupancy))
					knightCaptures(position, from, otherPlayer, moves);
				currentPass++;
				return true;
			case 3:
				for (const auto from : ((position.pieceOccupancy(bishop) | position.pieceOccupancy(queen))& movingOccupancy))
					sliderCaptures(position, from, otherPlayer, true, moves);
				currentPass++;
				return true;
			case 4:
				for (const auto from : ((position.pieceOccupancy(rook) | position.pieceOccupancy(queen))& movingOccupancy))
					sliderCaptures(position, from, otherPlayer, false, moves);
				currentPass++;
				return true;
			case 5:
				for (const auto from : (position.pieceOccupancy(king)& movingOccupancy))
					kingCaptures(position, from, movingPlayer, otherPlayer, stack.attackedSquares(otherPlayer), moves);
				currentPass++;
				return true;
			}
		}
		static void initializePosition_Implementation(boardType& position) noexcept;
		static void makeMove_Implementation(boardType& position, const movedata& md) noexcept;
		static void unmakeMove_Implementation(boardType& position, const movedata& md) noexcept;

	};
}