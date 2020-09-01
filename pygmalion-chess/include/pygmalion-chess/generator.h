namespace pygmalion::chess
{
	class generator :
		public pygmalion::generator<descriptor_generator, generator>
	{
	private:
		static const inline generatorTables<descriptor_generator> m_MovegenTable;
	public:


		class stack :
			public pygmalion::generator<descriptor_generator, generator>::stack
		{
		private:
			mutable std::array<squareType, countPlayers> m_KingSquare{ make_array_n<countPlayers,squareType>(squareType::invalid) };
			mutable std::array<squaresType, countPlayers> m_SquaresAttackedByPlayer{ make_array_n<countPlayers,squaresType>(squaresType::none()) };
			mutable std::array<bool, countPlayers> m_IsKingSquareValid{ make_array_n<countPlayers,bool>(false) };
			mutable std::array<bool, countPlayers> m_SquaresAttackedByPlayerValid{ make_array_n<countPlayers,bool>(false) };
		public:
			squareType kingSquare(const playerType player) const noexcept
			{
				if (!m_IsKingSquareValid[player])
				{
					m_KingSquare[player] = position().kingSquare(player);
					m_IsKingSquareValid[player] = true;
				}
				return m_KingSquare[player];
			}
			squaresType squaresAttackedByPlayer(const playerType player) const
			{
				if (!m_SquaresAttackedByPlayerValid[player])
				{
					m_SquaresAttackedByPlayer[player] = generatorType::squaresAttackedByPlayer(*this, player);
					m_SquaresAttackedByPlayerValid[player] = true;
				}
			}
			stack(const stack& parent, const moveType mv) noexcept :
				pygmalion::generator<descriptor_generator, generator>::stack(parent, mv)
			{
			}
			stack(boardType& position, const playerType oldPlayer) noexcept :
				pygmalion::generator<descriptor_generator, generator>::stack(position, oldPlayer)
			{
			}
			~stack() noexcept
			{
			}
		};

		using stackType = stack;
	private:
		constexpr static squaresType fillAttackRay_Up(const squaresType attackers, const squaresType notBlockers) noexcept
		{
			squaresType attacks{ squaresType::up(attackers) };
			attacks |= squaresType::up(attacks & notBlockers);
			attacks |= squaresType::up(attacks & notBlockers);
			attacks |= squaresType::up(attacks & notBlockers);
			attacks |= squaresType::up(attacks & notBlockers);
			attacks |= squaresType::up(attacks & notBlockers);
			attacks |= squaresType::up(attacks & notBlockers);
			return attacks;
		}
		constexpr static squaresType fillAttackRay_Down(const squaresType attackers, const squaresType notBlockers) noexcept
		{
			squaresType attacks{ squaresType::down(attackers) };
			attacks |= squaresType::down(attacks & notBlockers);
			attacks |= squaresType::down(attacks & notBlockers);
			attacks |= squaresType::down(attacks & notBlockers);
			attacks |= squaresType::down(attacks & notBlockers);
			attacks |= squaresType::down(attacks & notBlockers);
			attacks |= squaresType::down(attacks & notBlockers);
			return attacks;
		}
		constexpr static squaresType fillAttackRay_Right(const squaresType attackers, const squaresType notBlockers) noexcept
		{
			squaresType attacks{ squaresType::right(attackers) };
			attacks |= squaresType::right(attacks & notBlockers);
			attacks |= squaresType::right(attacks & notBlockers);
			attacks |= squaresType::right(attacks & notBlockers);
			attacks |= squaresType::right(attacks & notBlockers);
			attacks |= squaresType::right(attacks & notBlockers);
			attacks |= squaresType::right(attacks & notBlockers);
			return attacks;
		}
		constexpr static squaresType fillAttackRay_Left(const squaresType attackers, const squaresType notBlockers) noexcept
		{
			squaresType attacks{ squaresType::left(attackers) };
			attacks |= squaresType::left(attacks & notBlockers);
			attacks |= squaresType::left(attacks & notBlockers);
			attacks |= squaresType::left(attacks & notBlockers);
			attacks |= squaresType::left(attacks & notBlockers);
			attacks |= squaresType::left(attacks & notBlockers);
			attacks |= squaresType::left(attacks & notBlockers);
			return attacks;
		}
		constexpr static squaresType fillAttackRay_UpLeft(const squaresType attackers, const squaresType notBlockers) noexcept
		{
			squaresType attacks{ squaresType::upLeft(attackers) };
			attacks |= squaresType::upLeft(attacks & notBlockers);
			attacks |= squaresType::upLeft(attacks & notBlockers);
			attacks |= squaresType::upLeft(attacks & notBlockers);
			attacks |= squaresType::upLeft(attacks & notBlockers);
			attacks |= squaresType::upLeft(attacks & notBlockers);
			attacks |= squaresType::upLeft(attacks & notBlockers);
			return attacks;
		}
		static squaresType fillAttackRay_UpRight(const squaresType attackers, const squaresType notBlockers) noexcept
		{
			squaresType attacks{ squaresType::upRight(attackers) };
			attacks |= squaresType::upRight(attacks & notBlockers);
			attacks |= squaresType::upRight(attacks & notBlockers);
			attacks |= squaresType::upRight(attacks & notBlockers);
			attacks |= squaresType::upRight(attacks & notBlockers);
			attacks |= squaresType::upRight(attacks & notBlockers);
			attacks |= squaresType::upRight(attacks & notBlockers);
			return attacks;
		}
		static squaresType fillAttackRay_DownLeft(const squaresType attackers, const squaresType notBlockers) noexcept
		{
			squaresType attacks{ squaresType::downLeft(attackers) };
			attacks |= squaresType::downLeft(attacks & notBlockers);
			attacks |= squaresType::downLeft(attacks & notBlockers);
			attacks |= squaresType::downLeft(attacks & notBlockers);
			attacks |= squaresType::downLeft(attacks & notBlockers);
			attacks |= squaresType::downLeft(attacks & notBlockers);
			attacks |= squaresType::downLeft(attacks & notBlockers);
			return attacks;
		}
		static squaresType fillAttackRay_DownRight(const squaresType attackers, const squaresType notBlockers) noexcept
		{
			squaresType attacks{ squaresType::downRight(attackers) };
			attacks |= squaresType::downRight(attacks & notBlockers);
			attacks |= squaresType::downRight(attacks & notBlockers);
			attacks |= squaresType::downRight(attacks & notBlockers);
			attacks |= squaresType::downRight(attacks & notBlockers);
			attacks |= squaresType::downRight(attacks & notBlockers);
			attacks |= squaresType::downRight(attacks & notBlockers);
			return attacks;
		}
		static squaresType squaresAttackedByPlayer(const stackType& stack, const playerType attackingPlayer) noexcept
		{
			assert(attackingPlayer.isValid());
			const boardType& position{ stack.position() };
			const squaresType attackerOccupancy{ position.playerOccupancy(attackingPlayer) };
			const squaresType knights{ position.pieceOccupancy(knight) & attackerOccupancy };
			squaresType attacked{ squaresType::upUpLeft(knights) | squaresType::upUpRight(knights) | squaresType::downDownLeft(knights) | squaresType::downDownRight(knights) | squaresType::upLeftLeft(knights) | squaresType::upRightRight(knights) | squaresType::downLeftLeft(knights) | squaresType::downRightRight(knights) };
			attacked |= m_MovegenTable.kingMoveMap(stack.kingSquare(attackingPlayer));
			const squaresType queens{ position.pieceOccupancy(queen) };
			const squaresType slidersHV{ (position.pieceOccupancy(rook) | queens) & attackerOccupancy };
			const squaresType slidersDiag{ (position.pieceOccupancy(bishop) | queens) & attackerOccupancy };
			const squaresType notBlockers = ~position.totalOccupancy();
			attacked |= fillAttackRay_Up(slidersHV, notBlockers) | fillAttackRay_Down(slidersHV, notBlockers) | fillAttackRay_Right(slidersHV, notBlockers) | fillAttackRay_Left(slidersHV, notBlockers);
			attacked |= fillAttackRay_UpLeft(slidersDiag, notBlockers) | fillAttackRay_UpRight(slidersDiag, notBlockers) | fillAttackRay_DownLeft(slidersDiag, notBlockers) | fillAttackRay_DownRight(slidersDiag, notBlockers);
			const squaresType pawns{ position.pieceOccupancy(pawn) & attackerOccupancy };
			attacked |= (attackingPlayer == whitePlayer) ? (squaresType::upLeft(pawns) | squaresType::upRight(pawns)) : (squaresType::downLeft(pawns) | squaresType::downRight(pawns));
			return attacked;
		}
	public:
		static void movesFromSquare(const stackType& stack, const squareType square, squaresType& moves, squaresType& captures) noexcept
		{
			const boardType& position{ stack.position() };
			moves = squaresType::none();
			captures = squaresType::none();
			const squaresType totalOccupancy{ position.totalOccupancy() };
			if (!totalOccupancy[square])
				return;
			const pieceType piece{ position.getPiece(square) };
			const playerType movingPlayer{ position.movingPlayer() };
			const playerType otherPlayer{ movingPlayer.next() };
			const squaresType captureTargets{ position.playerOccupancy(otherPlayer) };
			switch (piece)
			{
			default:
				assert(0);
				break;
			case rook:
				m_MovegenTable.sliderMoveMaps(false, square, totalOccupancy, captureTargets, moves, captures);
				break;
			case bishop:
				m_MovegenTable.sliderMoveMaps(true, square, totalOccupancy, captureTargets, moves, captures);
				break;
			case queen:
				m_MovegenTable.sliderMoveMaps(false, square, totalOccupancy, captureTargets, moves, captures);
				m_MovegenTable.sliderMoveMaps(true, square, totalOccupancy, captureTargets, moves, captures);
				break;
			case knight:
			{
				const squaresType atts{ m_MovegenTable.knightMoveMap(square) };
				moves = atts & ~totalOccupancy;
				captures = atts & captureTargets;
				break;
			}
			case pawn:
				moves = m_MovegenTable.pawnMoveMap(square, movingPlayer) - totalOccupancy;
				captures = m_MovegenTable.pawnCaptureMap(square, movingPlayer) & captureTargets;
				if (movingPlayer == whitePlayer)
				{
					const rankType rank{ square.rank() };
					if (rank == rank2)
					{
						moves |= squaresType::up(moves) - totalOccupancy;
					}
					else if (rank == rank5)
					{
						const fileType file{ square.file() };
						if ((file != fileA) && position.checkEnPassantFile(file - 1))
							captures += (rank + 1) & (file - 1);
						else if ((file != fileH) && position.checkEnPassantFile(file + 1))
							captures += (rank + 1) & (file + 1);
					}
				}
				else
				{
					const rankType rank{ square.rank() };
					if (rank == rank7)
					{
						moves |= squaresType::down(moves) & ~totalOccupancy;
					}
					else if (rank == rank4)
					{
						const fileType file{ square.file() };
						if ((file != fileA) && position.checkEnPassantFile(file - 1))
							captures += (rank - 1) & (file - 1);
						else if ((file != fileH) && position.checkEnPassantFile(file + 1))
							captures += (rank - 1) & (file + 1);
					}
				}
				break;
			case king:
			{
				const squaresType forbidden{ stack.squaresAttackedByPlayer(otherPlayer) };
				const squaresType atts2{ m_MovegenTable.kingMoveMap(square) };
				moves = atts2 & ~totalOccupancy;
				captures = atts2 & captureTargets;
				if ((movingPlayer == whitePlayer) && (square == squareE1))
				{
					if (position.checkCastleRightKingsideWhite() && (!(kingsideCastleInterestWhite & totalOccupancy)) && (!(forbidden & kingsideCastleWalkWhite)))
						moves += squareG1;
					if (position.checkCastleRightQueensideWhite() && (!(queensideCastleInterestWhite & totalOccupancy)) && (!(forbidden & queensideCastleWalkWhite)))
						moves += squareC1;
				}
				else if ((movingPlayer == blackPlayer) && (square == squareE8))
				{
					if (position.checkCastleRightKingsideBlack() && (!(kingsideCastleInterestBlack & totalOccupancy)) && (!(forbidden & kingsideCastleWalkBlack)))
						moves += squareG8;
					if (position.checkCastleRightQueensideBlack() && (!(queensideCastleInterestBlack & totalOccupancy)) && (!(forbidden & queensideCastleWalkBlack)))
						moves += squareC8;
				}
			}
			break;
			}
		}

		static std::string name_Implementation() noexcept
		{
			return "chess";
		}
		static bool isMoveLegal_Implementation(const stackType& stack, const moveType& move) noexcept
		{
			const playerType movingPlayer{ stack.movingPlayer() };
			const playerType otherPlayer{ movingPlayer.next() };
			const squareType to{ move.square(square_to) };

			// are we illegally capturing the other king?
			const squareType otherking{ stack.kingSquare(otherPlayer) };
			if (mechanicsType::isCapture(move) && (otherking == to))
				return false;

			// No. Let's see where our king lives after the move as been made then...
			const squareType from{ move.square(square_from) };
			const squareType kingsquareOld{ stack.kingSquare(movingPlayer) };
			const squareType kingsquare{ (from == kingsquareOld) ? to : kingsquareOld };

			// Does he live on a square that is guarded by the other king?
			const squaresType attackedByOtherKing{ m_MovegenTable.kingMoveMap(otherking) };
			if (attackedByOtherKing[kingsquare])
				return false;

			// We need the enemy occupancy bitboard as it would be after the move...
			const squaresType otherOccupancy{ stack.position().playerOccupancy(otherPlayer) };
			const squaresType otherDelta{ mechanicsType::isCapture(move) ? (mechanicsType::isCaptureEnPassant(move) ? squareType::fromRankFile(from.rank(), to.file()) : to) : squaresType::none() };
			const squaresType occOther{ otherOccupancy ^ otherDelta };

			// Does he live on a square that is guarded by an enemy knight?
			const squaresType otherKnights{ ((stack.position().pieceOccupancy(knight) & otherOccupancy) ^ otherDelta) & occOther };
			const squaresType attackedByOtherKnights{ squaresType::upUpLeft(otherKnights) | squaresType::upUpRight(otherKnights) | squaresType::downDownLeft(otherKnights) | squaresType::downDownRight(otherKnights) | squaresType::upLeftLeft(otherKnights) | squaresType::downLeftLeft(otherKnights) | squaresType::upRightRight(otherKnights) | squaresType::downRightRight(otherKnights) };
			if (attackedByOtherKnights[kingsquare])
				return false;

			// Does he live on a square that is guarded by an enemy pawn?
			const squaresType otherPawns{ ((stack.position().pieceOccupancy(pawn) & otherOccupancy) ^ otherDelta) & occOther };
			const squaresType attackedByOtherPawns{ (otherPlayer == whitePlayer) ? (squaresType::upLeft(otherPawns) | squaresType::upRight(otherPawns)) : (squaresType::downLeft(otherPawns) | squaresType::downRight(otherPawns)) };
			if (attackedByOtherPawns[kingsquare])
				return false;

			// We need the total occupancy bitboard as it would be after the move...
			const squaresType movingOccupancy{ stack.position().playerOccupancy(movingPlayer) };
			const squaresType moveMask{ from ^ to };
			const squaresType movingDelta{ mechanicsType::isCastleQueenside(move) ? (mechanicsType::isCastleKingside(move) ? (moveMask ^ squareType::fromRankFile(from.rank(), to.file() - 1) ^ squareType::fromRankFile(from.rank(),fileH)) : (moveMask ^ squareType::fromRankFile(from.rank(),to.file() + 1) ^ squareType::fromRankFile(from.rank(),fileA))) : moveMask };
			const squaresType occMoving{ movingOccupancy ^ movingDelta };
			const squaresType occTotal{ occOther | occMoving };

			// Is he attacked horizontally by sliding pieces?
			const squaresType queens{ stack.position().pieceOccupancy(queen) };
			const squaresType otherSlidersHV = occOther & (stack.position().pieceOccupancy(rook) | queens);
			if (m_MovegenTable.sliderAttacks(false, kingsquare, occTotal, otherSlidersHV))
				return false;

			// Is he attacked diagonally by sliding pieces?
			const squaresType otherSlidersDiag = occOther & (stack.position().pieceOccupancy(bishop) | queens);
			if (m_MovegenTable.sliderAttacks(true, kingsquare, occTotal, otherSlidersDiag))
				return false;

			// The move seems legal
			return true;
		}


		static bool generateMoves_Implementation(const stackType& stack, movelistType& moves, int& currentPass) noexcept
		{
		}
		static bool generateTacticalMoves_Implementation(const stackType& stack, movelistType& moves, int& currentPass) noexcept
		{
		}
	};

}