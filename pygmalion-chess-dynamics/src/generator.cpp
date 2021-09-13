#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess
{
	std::deque<std::shared_ptr<pygmalion::intrinsics::command>> generator::commandsImplementation() noexcept
	{
		std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ std::deque<std::shared_ptr<pygmalion::intrinsics::command>>() };
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugMovegen>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugUntabled>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugMagics>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugAttacked>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugTargeted>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugCheck>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_perft>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_setFen>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_getFen>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_testMovegen>(list);
		return list;
	}

	void generator::control(const generatorType::stackType& stack, squaresType& white, squaresType& black) noexcept
	{
		const squaresType whitePawns{ stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(pawn) };
		const squaresType blackPawns{ stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(pawn) };
		const squaresType whiteRightAttacks{ whitePawns.upRight() };
		const squaresType whiteLeftAttacks{ whitePawns.upLeft() };
		const squaresType blackRightAttacks{ blackPawns.downRight() };
		const squaresType blackLeftAttacks{ blackPawns.downLeft() };
		const squaresType whiteSingleAttacks{ whiteLeftAttacks ^ whiteRightAttacks };
		const squaresType whiteDoubleAttacks{ whiteLeftAttacks & whiteRightAttacks };
		const squaresType blackSingleAttacks{ blackLeftAttacks ^ blackRightAttacks };
		const squaresType blackDoubleAttacks{ blackLeftAttacks & blackRightAttacks };
		squaresType open{ squaresType::all() };
		squaresType whiteControl{ squaresType::none() };
		squaresType blackControl{ squaresType::none() };
		const squaresType balancedDoubleAttacks{ whiteDoubleAttacks & blackDoubleAttacks };
		whiteControl |= open & whiteDoubleAttacks & ~balancedDoubleAttacks;
		blackControl |= open & blackDoubleAttacks & ~balancedDoubleAttacks;
		open &= ~(whiteControl | blackControl);
		const squaresType balancedSingleAttacks{ whiteSingleAttacks & blackSingleAttacks };
		whiteControl |= open & whiteSingleAttacks & ~balancedSingleAttacks;
		blackControl |= open & blackSingleAttacks & ~balancedSingleAttacks;
		open &= ~(whiteControl | blackControl);
		const squaresType whiteKnights{ stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(knight) };
		const squaresType blackKnights{ stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(knight) };
		const squaresType whiteBishops{ stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop) };
		const squaresType blackBishops{ stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(bishop) };
		std::uint8_t attacksWhite[64]
		{
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0
		};
		std::uint8_t attacksBlack[64]
		{
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0
		};
		squaresType touched{ squaresType::none() };
		for (squareType sq : whiteKnights)
		{
			const squaresType attacks{ generatorType::knightAttacks(sq,squaresType::all()) };
			for (squareType attack : attacks)
			{
				attacksWhite[attack]++;
				touched |= attack;
			}
		}
		for (squareType sq : blackKnights)
		{
			const squaresType attacks{ generatorType::knightAttacks(sq,squaresType::all()) };
			for (squareType attack : attacks)
			{
				attacksBlack[attack]++;
				touched |= attack;
			}
		}
		for (squareType sq : whiteBishops)
		{
			const squaresType attacks{ generatorType::sliderAttacksDiag(sq,~stack.position().totalOccupancy()) };
			for (squareType attack : attacks)
			{
				attacksWhite[attack]++;
				touched |= attack;
			}
		}
		for (squareType sq : blackBishops)
		{
			const squaresType attacks{ generatorType::sliderAttacksDiag(sq,~stack.position().totalOccupancy()) };
			for (squareType attack : attacks)
			{
				attacksBlack[attack]++;
				touched |= attack;
			}
		}
		for (squareType sq : (open& touched))
		{
			if (attacksWhite[sq] > attacksBlack[sq])
			{
				whiteControl |= sq;
				open -= sq;
			}
			else if (attacksBlack[sq] > attacksWhite[sq])
			{
				blackControl |= sq;
				open -= sq;
			}
		}
		std::uint8_t attacksWhite2[64]
		{
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0
		};
		std::uint8_t attacksBlack2[64]
		{
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0
		};
		const squaresType whiteRooks{ stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(rook) };
		const squaresType blackRooks{ stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(rook) };
		touched = squaresType::none();
		for (squareType sq : whiteRooks)
		{
			const squaresType attacks{ generatorType::sliderAttacksHV(sq,~stack.position().totalOccupancy()) };
			for (squareType attack : attacks)
			{
				attacksWhite2[attack]++;
				touched |= attack;
			}
		}
		for (squareType sq : blackRooks)
		{
			const squaresType attacks{ generatorType::sliderAttacksHV(sq,~stack.position().totalOccupancy()) };
			for (squareType attack : attacks)
			{
				attacksBlack2[attack]++;
				touched |= attack;
			}
		}
		for (squareType sq : (open& touched))
		{
			if (attacksWhite2[sq] > attacksBlack2[sq])
			{
				whiteControl |= sq;
				open -= sq;
			}
			else if (attacksBlack2[sq] > attacksWhite2[sq])
			{
				blackControl |= sq;
				open -= sq;
			}
		}
		std::uint8_t attacksWhite3[64]
		{
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0
		};
		std::uint8_t attacksBlack3[64]
		{
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0
		};
		const squaresType whiteQueens{ stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(queen) };
		const squaresType blackQueens{ stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(queen) };
		touched = squaresType::none();
		for (squareType sq : whiteQueens)
		{
			const squaresType attacks{ generatorType::sliderAttacksHV(sq,~stack.position().totalOccupancy()) | generatorType::sliderAttacksDiag(sq,~stack.position().totalOccupancy()) };
			for (squareType attack : attacks)
			{
				attacksWhite3[attack]++;
				touched |= attack;
			}
		}
		for (squareType sq : blackQueens)
		{
			const squaresType attacks{ generatorType::sliderAttacksHV(sq,~stack.position().totalOccupancy()) | generatorType::sliderAttacksDiag(sq,~stack.position().totalOccupancy()) };
			for (squareType attack : attacks)
			{
				attacksBlack3[attack]++;
				touched |= attack;
			}
		}
		for (squareType sq : (open& touched))
		{
			if (attacksWhite3[sq] > attacksBlack3[sq])
			{
				whiteControl |= sq;
				open -= sq;
			}
			else if (attacksBlack3[sq] > attacksWhite3[sq])
			{
				blackControl |= sq;
				open -= sq;
			}
		}
		const squaresType whiteKingAttacks{ generatorType::kingAttacks(stack.kingSquare(whitePlayer),squaresType::all()) };
		const squaresType blackKingAttacks{ generatorType::kingAttacks(stack.kingSquare(blackPlayer),squaresType::all()) };
		const squaresType balancedKingAttacks{ whiteKingAttacks & blackKingAttacks };
		whiteControl |= open & whiteKingAttacks & ~balancedKingAttacks;
		blackControl |= open & blackKingAttacks & ~balancedKingAttacks;
		white = whiteControl;
		black = blackControl;
	}

	generator::squaresType generator::attackers(const boardType& position, const squareType square) noexcept
	{
		assert(square.isValid());
		squaresType attackers{ squaresType::none() };
		const squaresType allowed{ ~position.totalOccupancy() };
		attackers |= knightAttacks(square, allowed) & position.pieceOccupancy(knight);
		attackers |= kingAttacks(square, allowed) & position.pieceOccupancy(king);
		const squaresType whitepawns{ position.pieceOccupancy(pawn) & position.playerOccupancy(whitePlayer) };
		const squaresType blackpawns{ position.pieceOccupancy(pawn) & position.playerOccupancy(blackPlayer) };
		const squaresType piecemap{ squaresType(square) };
		attackers |= (piecemap.upLeft() | piecemap.upRight()) & blackpawns;
		attackers |= (piecemap.downLeft() | piecemap.downRight()) & whitepawns;
		const squaresType slidersHV{ position.pieceOccupancy(queen) | position.pieceOccupancy(rook) };
		const squaresType slidersDiag{ position.pieceOccupancy(queen) | position.pieceOccupancy(bishop) };
		attackers |= sliderAttacksHV(square, allowed) & slidersHV;
		attackers |= sliderAttacksDiag(square, allowed) & slidersDiag;
		return attackers;
	}

	generator::squaresType generator::attackers(const boardType& position, const squareType square, const playerType attacker) noexcept
	{
		assert(square.isValid());
		squaresType attackers{ squaresType::none() };
		const squaresType allowed{ ~position.totalOccupancy() };
		attackers |= knightAttacks(square, allowed) & position.pieceOccupancy(knight);
		attackers |= kingAttacks(square, allowed) & position.pieceOccupancy(king);
		const squaresType pawns{ position.pieceOccupancy(pawn) };
		const squaresType piecemap{ squaresType(square) };
		attackers |= ((attacker == whitePlayer) ? (piecemap.downLeft() | piecemap.downRight()) : (piecemap.upLeft() | piecemap.upRight())) & pawns;
		const squaresType slidersHV{ (position.pieceOccupancy(queen) | position.pieceOccupancy(rook)) };
		const squaresType slidersDiag{ (position.pieceOccupancy(queen) | position.pieceOccupancy(bishop)) };
		attackers |= sliderAttacksHV(square, allowed) & slidersHV;
		attackers |= sliderAttacksDiag(square, allowed) & slidersDiag;
		return attackers & position.playerOccupancy(attacker);
	}

	bool generator::isAttacked(const boardType& position, const squareType square, const playerType attacker) noexcept
	{
		assert(square.isValid());
		const squaresType allowed{ ~position.totalOccupancy() };
		if (knightAttacks(square, allowed) & position.pieceOccupancy(knight) & position.playerOccupancy(attacker))
			return true;
		if (kingAttacks(square, allowed) & position.pieceOccupancy(king) & position.playerOccupancy(attacker))
			return true;
		const squaresType pawns{ position.pieceOccupancy(pawn) & position.playerOccupancy(attacker) };
		const squaresType piecemap{ squaresType(square) };
		const squaresType pawnAttacks{ (attacker == whitePlayer) ? (pawns.upLeft() | pawns.upRight()) : (pawns.downLeft() | pawns.downRight()) };
		if (pawnAttacks & piecemap)
			return true;
		const squaresType slidersDiag{ (position.pieceOccupancy(queen) | position.pieceOccupancy(bishop)) & position.playerOccupancy(attacker) };
		if (sliderAttacksDiag(square, allowed) & slidersDiag)
			return true;
		const squaresType slidersHV{ (position.pieceOccupancy(queen) | position.pieceOccupancy(rook)) & position.playerOccupancy(attacker) };
		if (sliderAttacksHV(square, allowed) & slidersHV)
			return true;
		return false;
	}

	generator::squaresType generator::squaresAttackedByPlayer(const stackType& stack, const playerType attackingPlayer) noexcept
	{
		assert(attackingPlayer.isValid());
		const boardType& position{ stack.position() };
		const squaresType totalOccupancy{ position.totalOccupancy() };
		const squaresType notBlockers = ~totalOccupancy;
		const squaresType attackerOccupancy{ position.playerOccupancy(attackingPlayer) };
		const squaresType knights{ position.pieceOccupancy(knight) & attackerOccupancy };
		squaresType attacked{ knightAttacks(knights, notBlockers) };
		attacked |= kingAttacks(stack.kingSquare(attackingPlayer), notBlockers);
		const squaresType queens{ position.pieceOccupancy(queen) };
		const squaresType slidersHV{ (position.pieceOccupancy(rook) | queens) & attackerOccupancy };
		const squaresType slidersDiag{ (position.pieceOccupancy(bishop) | queens) & attackerOccupancy };
		attacked |= sliderAttacksHV(slidersHV, notBlockers);
		attacked |= sliderAttacksDiag(slidersDiag, notBlockers);;
		const squaresType pawns{ position.pieceOccupancy(pawn) & attackerOccupancy };
		if (attackingPlayer == whitePlayer)
			attacked |= pawns.upLeft() | pawns.upRight();
		else
			attacked |= pawns.downLeft() | pawns.downRight();
		return attacked;
	}

	generator::squaresType generator::squaresTargetedByPlayer(const stackType& stack, const playerType attackingPlayer) noexcept
	{
		assert(attackingPlayer.isValid());
		const boardType& position{ stack.position() };
		const squaresType totalOccupancy{ position.totalOccupancy() };
		const squaresType notBlockers = ~totalOccupancy;
		const squaresType attackerOccupancy{ position.playerOccupancy(attackingPlayer) };
		const squaresType knights{ position.pieceOccupancy(knight) & attackerOccupancy };
		squaresType attacked{ knightTargets(knights, notBlockers) };
		attacked |= kingTargets(stack.kingSquare(attackingPlayer), notBlockers);
		const squaresType queens{ position.pieceOccupancy(queen) };
		const squaresType slidersHV{ (position.pieceOccupancy(rook) | queens) & attackerOccupancy };
		const squaresType slidersDiag{ (position.pieceOccupancy(bishop) | queens) & attackerOccupancy };
		attacked |= sliderTargetsHV(slidersHV, notBlockers);
		attacked |= sliderTargetsDiag(slidersDiag, notBlockers);;
		const squaresType pawns{ position.pieceOccupancy(pawn) & attackerOccupancy };
		if (attackingPlayer == whitePlayer)
			attacked |= pawns.upLeft() | pawns.upRight();
		else
			attacked |= pawns.downLeft() | pawns.downRight();
		return attacked;
	}

	void generator::generateKingMoves(const stackType& stack, movelistType& moves) noexcept
	{
		const squaresType forbidden{ stack.squaresAttackedByPlayer(stack.nextPlayer()) };
		const squaresType allowed{ ~forbidden };
		for (const squareType from : stack.position().pieceOccupancy(king)& stack.position().playerOccupancy(stack.position().movingPlayer()))
		{
			const squaresType destinations{ allowed & kingTargets(from, ~stack.position().totalOccupancy()) };
			for (const squareType to : destinations)
				moves.add(motorType::move().createQuiet(from, to));
		}
	}

	void generator::generateKingCaptures(const stackType& stack, movelistType& moves) noexcept
	{
		const squaresType forbidden{ stack.squaresAttackedByPlayer(stack.nextPlayer()) };
		const squaresType allowed{ ~forbidden };
		for (const squareType from : stack.position().pieceOccupancy(king)& stack.position().playerOccupancy(stack.position().movingPlayer()))
		{
			for (const squareType to : allowed & kingAttacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(stack.nextPlayer()))
				moves.add(motorType::move().createCapture(from, to));
		}
	}

	void generator::generateCastles(const stackType& stack, movelistType& moves) noexcept
	{
		if (stack.position().movingPlayer() == whitePlayer)
		{
			if (stack.position().checkCastleRightKingsideWhite())
			{
				if (!(stack.position().totalOccupancy() & kingsideCastleInterestWhite))
				{
					if (!(stack.squaresAttackedByPlayer(blackPlayer) & kingsideCastleWalkWhite))
						moves.add(motorType::move().createKingsideCastle());
				}
			}
			if (stack.position().checkCastleRightQueensideWhite())
			{
				if (!(stack.position().totalOccupancy() & queensideCastleInterestWhite))
				{
					if (!(stack.squaresAttackedByPlayer(blackPlayer) & queensideCastleWalkWhite))
						moves.add(motorType::move().createQueensideCastle());
				}
			}
		}
		else
		{
			if (stack.position().checkCastleRightKingsideBlack())
			{
				if (!(stack.position().totalOccupancy() & kingsideCastleInterestBlack))
				{
					if (!(stack.squaresAttackedByPlayer(whitePlayer) & kingsideCastleWalkBlack))
						moves.add(motorType::move().createKingsideCastle());
				}
			}
			if (stack.position().checkCastleRightQueensideBlack())
			{
				if (!(stack.position().totalOccupancy() & queensideCastleInterestBlack))
				{
					if (!(stack.squaresAttackedByPlayer(whitePlayer) & queensideCastleWalkBlack))
						moves.add(motorType::move().createQueensideCastle());
				}
			}
		}
	}

	void generator::generatePawnEnPassant(const stackType& stack, movelistType& moves) noexcept
	{
		const uint_t<8, false> epFlags{ stack.position().flags().extractRange<4,11>() };
		size_t bit;
		if (stack.position().movingPlayer() == whitePlayer)
		{
			if (epFlags.bitscanForward(bit))
			{
				const fileType epFile{ static_cast<typename fileType::baseType>(bit) };
				const squaresType leftFile{ static_cast<squaresType>(epFile).left() };
				const squaresType rightFile{ static_cast<squaresType>(epFile).right() };
				const squaresType rank{ static_cast<squaresType>(rank5) };
				const squaresType fromSquares = (leftFile | rightFile) & rank;
				const squareType toSquare{ epFile & rank6 };
				for (const squareType from : fromSquares & (stack.position().playerOccupancy(whitePlayer)& stack.position().pieceOccupancy(pawn)))
					moves.add(motorType::move().createEnPassant(from.file(), epFile));
			}
		}
		else
		{
			if (epFlags.bitscanForward(bit))
			{
				const fileType epFile{ static_cast<typename fileType::baseType>(bit) };
				const squaresType leftFile{ static_cast<squaresType>(epFile).left() };
				const squaresType rightFile{ static_cast<squaresType>(epFile).right() };
				const squaresType rank{ static_cast<squaresType>(rank4) };
				const squaresType fromSquares = (leftFile | rightFile) & rank;
				const squareType toSquare{ epFile & rank3 };
				for (const squareType from : fromSquares & (stack.position().playerOccupancy(blackPlayer)& stack.position().pieceOccupancy(pawn)))
					moves.add(motorType::move().createEnPassant(from.file(), epFile));
			}
		}
	}

	bool generator::isGeneratedMoveLegal_Implementation(const stackType& stack, const movebitsType& moveBits) noexcept
	{
		const boardType& position{ stack.position() };
		const playerType movingPlayer{ position.movingPlayer() };
		const playerType otherPlayer{ movingPlayer.next() };
		const squareType to{ motorType::move().toSquare(position, moveBits) };

		// are we illegally capturing the other king?
		const bool isCapture{ motorType::move().isCapture(moveBits) };
		const squareType otherking{ stack.kingSquare(otherPlayer) };
		if (isCapture && (otherking == to))
			return false;

		// No. Let's see where our king lives after the move as been made then...
		const squareType from{ motorType::move().fromSquare(position, moveBits) };
		const squareType kingsquareOld{ stack.kingSquare(movingPlayer) };
		const bool isKingMove{ from == kingsquareOld };
		const squareType kingsquare{ isKingMove ? to : kingsquareOld };

		// We need the enemy occupancy bitboard as it would be after the move...
		const squaresType otherOccupancy{ position.playerOccupancy(otherPlayer) };
		const squaresType otherDelta{ motorType::move().otherOccupancyDelta(position, moveBits) };
		const squaresType occOther{ otherOccupancy ^ otherDelta };

		// if we're moving the king, we need to do some extra work
		if (isKingMove || stack.isCheck())
		{
			// Does our king live on a square that is guarded by the other king?
			const squaresType attackedByOtherKing{ movegenKing.attacks(otherking,squaresType::all()) };
			if (attackedByOtherKing[kingsquare])
				return false;

			// Does he live on a square that is guarded by an enemy knight?
			const squaresType otherKnights{ ((position.pieceOccupancy(knight) & otherOccupancy) ^ otherDelta) & occOther };
			const squaresType attackedByOtherKnights{ movegenKnight.attacks(otherKnights,squaresType::all()) };
			if (attackedByOtherKnights[kingsquare])
				return false;

			// Does he live on a square that is guarded by an enemy pawn?
			const squaresType otherPawns{ ((position.pieceOccupancy(pawn) & otherOccupancy) ^ otherDelta) & occOther };
			if (otherPlayer == whitePlayer)
			{
				const squaresType pawnsTemp{ otherPawns.up() };
				const squaresType attackedByOtherPawns{ pawnsTemp.right() | pawnsTemp.left() };
				if (attackedByOtherPawns[kingsquare])
					return false;
			}
			else
			{
				const squaresType pawnsTemp{ otherPawns.down() };
				const squaresType attackedByOtherPawns{ pawnsTemp.right() | pawnsTemp.left() };
				if (attackedByOtherPawns[kingsquare])
					return false;
			}
		}

		// We need the total occupancy bitboard as it would be after the move...
		const squaresType movingOccupancy{ position.playerOccupancy(movingPlayer) };
		const squaresType movingDelta{ motorType::move().ownOccupancyDelta(position, moveBits) };
		const squaresType occMoving{ movingOccupancy ^ movingDelta };
		const squaresType occTotal{ occOther | occMoving };

		// Is he attacked horizontally by sliding pieces?
		const squaresType queens{ position.pieceOccupancy(queen) };
		const squaresType rooks{ position.pieceOccupancy(rook) };
		const squaresType otherSlidersHV = occOther & (rooks | queens);
		if (movegenSlidersHV.attacks(otherSlidersHV, ~occTotal)[kingsquare])
			return false;

		// Is he attacked diagonally by sliding pieces?
		const squaresType bishops{ position.pieceOccupancy(bishop) };
		const squaresType otherSlidersDiag = occOther & (bishops | queens);
		if (movegenSlidersDiag.attacks(otherSlidersDiag, ~occTotal)[kingsquare])
			return false;

		// The move seems legal
		return true;
	}

	bool generator::isMoveLegal_Implementation(const stackType& stack, const movebitsType& moveBits) noexcept
	{
		const boardType& position{ stack.position() };
		const playerType movingPlayer{ position.movingPlayer() };
		const playerType otherPlayer{ movingPlayer.next() };
		const squareType from{ motorType::move().fromSquare(position, moveBits) };
		const squareType to{ motorType::move().toSquare(position, moveBits) };
		if (!from.isValid())
			return false;
		if (!to.isValid())
			return false;

		if (motorType::move().isDoublePush(moveBits))
		{
			// are we moving a pawn?
			if (!position.pieceOccupancy(pawn)[from])
				return false;

			// is it our own pawn?
			if (!position.playerOccupancy(movingPlayer)[from])
				return false;

			// is our destination square empty?
			if (position.totalOccupancy()[to])
				return false;

			if (movingPlayer == whitePlayer)
			{
				// is the pawn elegible for a double push?
				if (!pawnDoublePushFromSquaresWhite()[from])
					return false;

				// is the destination rank correct?
				const fileType rankTo{ to.rank() };
				if (rankTo != rank4)
					return false;

				// is our way free?
				const fileType fileFrom{ from.file() };
				const squareType interestSquare{ fileFrom & rank3 };
				if (position.totalOccupancy()[interestSquare])
					return false;
			}

			else
			{
				// is the pawn elegible for a double push?
				if (!pawnDoublePushFromSquaresBlack()[from])
					return false;

				// is the destination rank correct?
				const fileType rankTo{ to.rank() };
				if (rankTo != rank5)
					return false;

				// is our way free?
				const fileType fileFrom{ from.file() };
				const squareType interestSquare{ fileFrom & rank6 };
				if (position.totalOccupancy()[interestSquare])
					return false;
			}
		}
		else if (motorType::move().isEnPassant(moveBits))
		{
			// are we moving a pawn?
			if (!position.pieceOccupancy(pawn)[from])
				return false;

			// is it our own pawn?
			if (!position.playerOccupancy(movingPlayer)[from])
				return false;

			// is our destination square empty?
			if (position.totalOccupancy()[to])
				return false;

			// do we have en Passant rights?
			const fileType epFile{ to.file() };
			if (!position.checkEnPassantFile(epFile))
				return false;
		}
		else if (motorType::move().isPromotion(moveBits))
		{
			// are we moving a pawn?
			if (!position.pieceOccupancy(pawn)[from])
				return false;

			// is it our own pawn?
			if (!position.playerOccupancy(movingPlayer)[from])
				return false;

			// is the pawn elegible for a promotion?
			const fileType rankFrom{ from.rank() };
			if (((movingPlayer == whitePlayer) ? rank7 : rank2) == rankFrom)
				return false;

			// is the destination rank correct?
			const fileType rankTo{ to.rank() };
			if (((movingPlayer == whitePlayer) ? rank8 : rank1) == rankTo)
				return false;

			// is it a promotion capture?
			if (motorType::move().isCapture(moveBits))
			{
				// is the capture square valid?
				const squareType captureSquare{ motorType::move().captureSquare(position,moveBits) };
				if (!captureSquare.isValid())
					return false;

				// is there a piece to capture?
				if (!position.playerOccupancy(otherPlayer)[captureSquare])
					return false;
			}
			else
			{
				// is our destination square empty?
				if (position.totalOccupancy()[to])
					return false;
			}
		}
		else if (motorType::move().isKingsideCastle(moveBits))
		{
			// do we have kingside castling rights?
			if (!position.checkCastleRightKingside(movingPlayer))
				return false;

			// are pieces obstructing the way?
			const squaresType castleInterest{ (movingPlayer == whitePlayer) ? kingsideCastleInterestWhite : kingsideCastleInterestBlack };
			if (position.totalOccupancy() & castleInterest)
				return false;

			// is the way for the king attacked?
			const squaresType castleWalk{ (movingPlayer == whitePlayer) ? kingsideCastleWalkWhite : kingsideCastleWalkBlack };
			if (stack.squaresAttackedByPlayer(otherPlayer) & castleWalk)
				return false;
		}
		else if (motorType::move().isQueensideCastle(moveBits))
		{
			// do we have kingside castling rights?
			if (!position.checkCastleRightQueenside(movingPlayer))
				return false;

			// are pieces obstructing the way?
			const squaresType castleInterest{ (movingPlayer == whitePlayer) ? queensideCastleInterestWhite : queensideCastleInterestBlack };
			if (position.totalOccupancy() & castleInterest)
				return false;

			// is the way for the king attacked?
			const squaresType castleWalk{ (movingPlayer == whitePlayer) ? queensideCastleWalkWhite : queensideCastleWalkBlack };
			if (stack.squaresAttackedByPlayer(otherPlayer) & castleWalk)
				return false;
		}
		else if (motorType::move().isCapture(moveBits))
		{
			// is there a piece to move?
			if (!position.playerOccupancy(movingPlayer)[from])
				return false;

			// is the capture square valid?
			const squareType captureSquare{ motorType::move().captureSquare(position,moveBits) };
			if (!captureSquare.isValid())
				return false;

			// is there a piece to capture?
			if (!position.playerOccupancy(otherPlayer)[captureSquare])
				return false;

			// what piece are we moving?
			const pieceType movingPiece{ position.getPiece(from) };

			// are we doing a legal capture?
			switch (movingPiece)
			{
			case pawn:
				if (!pawnCaptureTargets(from, movingPlayer, ~position.playerOccupancy(movingPlayer))[to])
					return false;
				break;
			case king:
				if (!kingTargets(from, ~position.playerOccupancy(movingPlayer))[to])
					return false;
				break;
			case knight:
				if (!knightTargets(from, ~position.playerOccupancy(movingPlayer))[to])
					return false;
				break;
			case rook:
				if (!(sliderAttacksHV(from, ~position.totalOccupancy()) & position.playerOccupancy(otherPlayer))[to])
					return false;
				break;
			case bishop:
				if (!(sliderAttacksDiag(from, ~position.totalOccupancy()) & position.playerOccupancy(otherPlayer))[to])
					return false;
				break;
			case queen:
				if (!((sliderAttacksHV(from, ~position.totalOccupancy()) | sliderAttacksDiag(from, ~position.totalOccupancy())) & position.playerOccupancy(otherPlayer))[to])
					return false;
				break;
			}
		}
		else
		{
			// is there a piece to move?
			if (!position.playerOccupancy(movingPlayer)[from])
				return false;

			// is our destination square empty?
			if (position.totalOccupancy()[to])
				return false;

			// what piece are we moving?
			const pieceType movingPiece{ position.getPiece(from) };

			// are we doing a legal move?
			switch (movingPiece)
			{
			case pawn:
				return false;
			case king:
				if (!kingTargets(from, ~position.playerOccupancy(movingPlayer))[to])
					return false;
				break;
			case knight:
				if (!knightTargets(from, ~position.playerOccupancy(movingPlayer))[to])
					return false;
				break;
			case rook:
				if (!(sliderAttacksHV(from, ~position.totalOccupancy()) & ~position.totalOccupancy())[to])
					return false;
				break;
			case bishop:
				if (!(sliderAttacksDiag(from, ~position.totalOccupancy()) & ~position.totalOccupancy())[to])
					return false;
				break;
			case queen:
				if (!((sliderAttacksHV(from, ~position.totalOccupancy()) | sliderAttacksDiag(from, ~position.totalOccupancy())) & ~position.totalOccupancy())[to])
					return false;
				break;
			}
		}
		return generatorType::isGeneratedMoveLegal(stack, moveBits);
	}

	bool generator::isGivingCheck(const stackType& stack, const movebitsType& moveBits) noexcept
	{
		const boardType& position{ stack.position() };
		const playerType movingPlayer{ position.movingPlayer() };
		const playerType otherPlayer{ movingPlayer.next() };
		const squareType to{ motorType::move().toSquare(position, moveBits) };

		// We need to know where the enemy king lives
		const squareType otherking{ stack.kingSquare(otherPlayer) };

		// We need our own occupancy bitboard as it would be after the move...
		const squaresType ownOccupancy{ position.playerOccupancy(movingPlayer) };
		const squaresType ownDelta{ motorType::move().ownOccupancyDelta(position, moveBits) };
		const squaresType occOwn{ ownOccupancy ^ ownDelta };

		// Does he live on a square that is attacked by one of our knights?
		const squaresType ownKnights{ ((position.pieceOccupancy(knight) & ownOccupancy) ^ ownDelta) & occOwn };
		const squaresType attackedByOwnKnights{ movegenKnight.attacks(ownKnights,squaresType::all()) };
		if (attackedByOwnKnights[otherking])
			return true;

		// Does he live on a square that is attacked by one of our pawns?
		const squaresType ownPawns{ ((position.pieceOccupancy(pawn) & ownOccupancy) ^ ownDelta) & occOwn };
		if (movingPlayer == whitePlayer)
		{
			const squaresType pawnsTemp{ ownPawns.up() };
			const squaresType attackedByOwnPawns{ pawnsTemp.right() | pawnsTemp.left() };
			if (attackedByOwnPawns[otherking])
				return true;
		}
		else
		{
			const squaresType pawnsTemp{ ownPawns.down() };
			const squaresType attackedByOwnPawns{ pawnsTemp.right() | pawnsTemp.left() };
			if (attackedByOwnPawns[otherking])
				return true;
		}

		// We need the total occupancy bitboard as it would be after the move...
		const squaresType otherOccupancy{ position.playerOccupancy(otherPlayer) };
		const squaresType otherDelta{ motorType::move().otherOccupancyDelta(position, moveBits) };
		const squaresType occOther{ otherOccupancy ^ otherDelta };
		const squaresType occTotal{ occOther | occOwn };

		// Is he attacked horizontally by sliding pieces?
		const squaresType queens{ (position.pieceOccupancy(queen) & otherOccupancy) ^ ownDelta };
		const squaresType rooks{ (position.pieceOccupancy(rook) & otherOccupancy) ^ ownDelta };
		const squaresType ownSlidersHV = occOwn & (rooks | queens);
		if (movegenSlidersHV.attacks(ownSlidersHV, ~occTotal)[otherking])
			return true;

		// Is he attacked diagonally by sliding pieces?
		const squaresType bishops{ (position.pieceOccupancy(bishop) & otherOccupancy) ^ ownDelta };
		const squaresType ownSlidersDiag = occOwn & (bishops | queens);
		if (movegenSlidersDiag.attacks(ownSlidersDiag, ~occTotal)[otherking])
			return true;

		// The move seems not to be giving check
		return false;
	}

	bool generator::isMoveTactical_Implementation(const stackType& stack, const movebitsType& moveBits) noexcept
	{
		return motorType::move().isCapture(moveBits);
	}

	void generator::generateMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
	{
		switch (static_cast<size_t>(currentPass))
		{
		default:
			assert(0);
			return;
		case 0:
			generateKnightMoves(stack, moves);
			break;
		case 1:
			generatePawnPushes(stack, moves);
			break;
		case 2:
			generatePawnDoublePushes(stack, moves);
			break;
		case 3:
			generateKnightCaptures(stack, moves);
			break;
		case 4:
			generatePawnCaptures(stack, moves);
			break;
		case 5:
			generatePawnEnPassant(stack, moves);
			break;
		case 6:
			generateSliderMovesHV(stack, moves);
			break;
		case 7:
			generateSliderMovesDiag(stack, moves);
			break;
		case 8:
			generateSliderCapturesHV(stack, moves);
			break;
		case 9:
			generateSliderCapturesDiag(stack, moves);
			break;
		case 10:
			generateKingMoves(stack, moves);
			break;
		case 11:
			generateKingCaptures(stack, moves);
			break;
		case 12:
			generateCastles(stack, moves);
			break;
		case 13:
			generatePawnPromotions(stack, moves);
			break;
		case 14:
			generatePawnPromoCaptures(stack, moves);
			break;
		}
	}

	void generator::generateTacticalMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
	{
		switch (static_cast<size_t>(currentPass))
		{
		default:
			assert(0);
			return;
		case 0:
			generateKnightCaptures(stack, moves);
			break;
		case 1:
			generatePawnCaptures(stack, moves);
			break;
		case 2:
			generatePawnEnPassant(stack, moves);
			break;
		case 3:
			generateSliderCapturesHV(stack, moves);
			break;
		case 4:
			generateSliderCapturesDiag(stack, moves);
			break;
		case 5:
			generateKingCaptures(stack, moves);
			break;
		case 6:
			generatePawnPromoCaptures(stack, moves);
			break;
		}
	}

	void generator::movesFromSquare(const stackType& stack, const squareType square, squaresType& moves, squaresType& captures, const size_t depth) noexcept
	{
		const boardType& position{ stack.position() };
		moves = squaresType::none();
		captures = squaresType::none();
		movelistType list;
		size_t pass{ 0 };
		for (size_t pass = 0; pass < countPasses; pass++)
			generateMoves(stack, list, pass);
		for (indexType i = 0; i < list.length(); i++)
		{
			const squareType fromSquare{ motorType::move().fromSquare(position, list[i]) };
			if (square == fromSquare)
			{
				const squareType toSquare{ motorType::move().toSquare(position,list[i]) };
				if (motorType::move().isCapture(list[i]))
				{
					captures |= toSquare;
				}
				else
				{
					moves |= toSquare;
				}
			}
		}
	}

	std::string generator::moveToString_Implementation(const stackType& stack, const movebitsType mv, const size_t depth) noexcept
	{
		const boardType& position{ stack.position() };
		const squareType from{ motorType::move().fromSquare(position,mv) };
		const squareType to{ motorType::move().toSquare(position,mv) };
		const pieceType piece{ position.getPiece(from) };
		const playerType side{ position.movingPlayer() };
		if (motorType::move().isKingsideCastle(mv))
			return "O-O";
		if (motorType::move().isQueensideCastle(mv))
			return "O-O-O";
		std::string ret = "";
		switch (piece)
		{
		default:
			assert(0);
			break;
		case pawn:
			break;
		case knight:
			ret += "N";
			break;
		case bishop:
			ret += "B";
			break;
		case rook:
			ret += "R";
			break;
		case queen:
			ret += "Q";
			break;
		case king:
			ret += "K";
			break;
		}
		int countamb{ 0 };
		for (const auto sq : squareType::range)
		{
			if ((position.pieceOccupancy(piece) & position.playerOccupancy(side))[sq])
			{
				squaresType captures{ squaresType::none() };
				squaresType moves{ squaresType::none() };
				generatorType::movesFromSquare(stack, sq, moves, captures, depth);
				if ((captures | moves)[to])
				{
					countamb++;
				}
			}
		}
		if (countamb > 1)
		{
			const auto file{ from.file() };
			countamb = 0;
			for (const auto sq : squareType::range)
			{
				if ((position.pieceOccupancy(piece) & position.playerOccupancy(side))[sq])
				{
					squaresType captures{ squaresType::none() };
					squaresType moves{ squaresType::none() };
					generatorType::movesFromSquare(stack, sq, moves, captures, depth);
					if ((captures | moves)[to])
					{
						if (sq.file() == file)
							countamb++;
					}
				}
			}
			if (countamb > 1)
			{
				const auto rank{ from.rank() };
				countamb = 0;
				for (const auto sq : squareType::range)
				{
					if ((position.pieceOccupancy(piece) & position.playerOccupancy(side))[sq])
					{
						squaresType captures{ squaresType::none() };
						squaresType moves{ squaresType::none() };
						generatorType::movesFromSquare(stack, sq, moves, captures, depth);
						if ((captures | moves)[to])
						{
							if (sq.rank() == rank)
								countamb++;
						}
					}
				}
				if (countamb > 1)
				{
					ret += boardType::squareToString(from);
				}
				else
				{
					switch (rank)
					{
					case 0:
						ret += "1";
						break;
					case 1:
						ret += "2";
						break;
					case 2:
						ret += "3";
						break;
					case 3:
						ret += "4";
						break;
					case 4:
						ret += "5";
						break;
					case 5:
						ret += "6";
						break;
					case 6:
						ret += "7";
						break;
					case 7:
						ret += "8";
						break;
					}
				}
			}
			else
			{
				switch (file)
				{
				case 0:
					ret += "a";
					break;
				case 1:
					ret += "b";
					break;
				case 2:
					ret += "c";
					break;
				case 3:
					ret += "d";
					break;
				case 4:
					ret += "e";
					break;
				case 5:
					ret += "f";
					break;
				case 6:
					ret += "g";
					break;
				case 7:
					ret += "h";
					break;
				}
			}
		}
		if (motorType::move().isCapture(mv))
			ret += "x";
		ret = ret + boardType::squareToString(to);
		if (motorType::move().isEnPassant(mv))
			ret += "ep";
		if (motorType::move().isPromotion(mv))
		{
			switch (motorType::move().promotedPiece(mv))
			{
			case knight:
				ret += "=N";
				break;
			case bishop:
				ret += "=B";
				break;
			case rook:
				ret += "=R";
				break;
			case queen:
				ret += "=Q";
				break;
			}
		}
		return ret;
	}

	void generator::stack::control(squaresType& white, squaresType& black) const
	{
		if (!m_IsControlValid)
		{
			generatorType::control(*static_cast<const stackType*>(this), m_ControlledByPlayer[whitePlayer], m_ControlledByPlayer[blackPlayer]);
			m_IsControlValid = true;
		}
		white = m_ControlledByPlayer[whitePlayer];
		black = m_ControlledByPlayer[blackPlayer];
	}

	generator::squareType generator::stack::kingSquare(const playerType player) const noexcept
	{
		if (!m_IsKingSquareValid[player])
		{
			m_KingSquare[player] = position().kingSquare(player);
			m_IsKingSquareValid[player] = true;
		}
		return m_KingSquare[player];
	}

	generator::squaresType generator::stack::squaresTargetedByPlayer(const playerType player) const
	{
		if (!m_SquaresTargetedByPlayerValid[player])
		{
			m_SquaresTargetedByPlayer[player] = generatorType::squaresTargetedByPlayer(*this, player);
			m_SquaresTargetedByPlayerValid[player] = true;
		}
		return m_SquaresTargetedByPlayer[player];
	}

	generator::squaresType generator::stack::squaresAttackedByPlayer(const playerType player) const
	{
		if (!m_SquaresAttackedByPlayerValid[player])
		{
			m_SquaresAttackedByPlayer[player] = generatorType::squaresAttackedByPlayer(*this, player);
			m_SquaresAttackedByPlayerValid[player] = true;
		}
		return m_SquaresAttackedByPlayer[player];
	}

	bool generator::stack::isCheck() const noexcept
	{
		if (!m_IsCheckValid)
		{
			m_IsCheck = generatorType::isAttacked(position(), kingSquare(movingPlayer()), nextPlayer());
			m_IsCheckValid = true;
		}
		return m_IsCheck;
	}

	generator::stack::stack(const stack& parent, const movebitsType& movebits) noexcept :
		pygmalion::generator<descriptor_dynamics, generator>::stack(parent, movebits)
	{
	}

	generator::stack::stack(boardType& position, historyType& history, const playerType oldPlayer) noexcept :
		pygmalion::generator<descriptor_dynamics, generator>::stack(position, history, oldPlayer)
	{
	}

	generator::stack::~stack() noexcept
	{
	}

	std::string generator::passToString_Implementation(const passType pass) noexcept
	{
		switch (static_cast<size_t>(pass))
		{
		default:
			assert(0);
			return "???";
		case 0:
			return "knight moves";
		case 1:
			return "pawn pushes";
		case 2:
			return "double pushes";
		case 3:
			return "knight captures";
		case 4:
			return "pawn captures";
		case 5:
			return "en Passant";
		case 6:
			return "slider moves h./v.";
		case 7:
			return "slider moves diag.";
		case 8:
			return "slider captures h./v.";
		case 9:
			return "slider captures diag.";
		case 10:
			return "king moves";
		case 11:
			return "king captures";
		case 12:
			return "castles";
		case 13:
			return "promotions";
		case 14:
			return "promotion captures";
		}
	}

	std::string generator::tacticalPassToString_Implementation(const passType tacticalPass) noexcept
	{
		switch (static_cast<size_t>(tacticalPass))
		{
		default:
			assert(0);
			return "???";
		case 0:
			return "knight captures";
		case 1:
			return "pawn captures";
		case 2:
			return "en Passant";
		case 3:
			return "slider captures h./v.";
		case 4:
			return "slider captures diag.";
		case 5:
			return "king captures";
		case 6:
			return "promotion captures";
		}
	}

}