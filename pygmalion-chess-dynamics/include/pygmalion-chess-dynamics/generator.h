namespace pygmalion::chess
{
#define FASTPAWNS

	class generator :
		public pygmalion::generator<descriptor_dynamics, generator>
	{
	public:
		constexpr static const inline movegen_knight movegenKnight{ movegen_knight() };
		constexpr static const inline movegen_pawn_push_white movegenPawnPushWhite{ movegen_pawn_push_white() };
		constexpr static const inline movegen_pawn_push_black movegenPawnPushBlack{ movegen_pawn_push_black() };
		constexpr static const inline movegen_pawn_capture_white movegenPawnCaptureWhite{ movegen_pawn_capture_white() };
		constexpr static const inline movegen_pawn_capture_black movegenPawnCaptureBlack{ movegen_pawn_capture_black() };
		constexpr static const inline movegen_pawn_doublepush_white movegenPawnDoublePushWhite{ movegen_pawn_doublepush_white() };
		constexpr static const inline movegen_pawn_doublepush_black movegenPawnDoublePushBlack{ movegen_pawn_doublepush_black() };
		constexpr static const inline movegen_sliders_hv movegenSlidersHV{ movegen_sliders_hv() };
		constexpr static const inline movegen_sliders_diag movegenSlidersDiag{ movegen_sliders_diag() };
		constexpr static const inline movegen_king movegenKing{ movegen_king() };

		class stack :
			public pygmalion::generator<descriptor_dynamics, generator>::stack
		{
		private:
			mutable std::array<squareType, countPlayers> m_KingSquare{ arrayhelper::make<countPlayers,squareType>(squareType::invalid) };
			mutable std::array<squaresType, countPlayers> m_SquaresAttackedByPlayer{ arrayhelper::make<countPlayers,squaresType>(squaresType::none()) };
			mutable std::array<bool, countPlayers> m_IsKingSquareValid{ arrayhelper::make<countPlayers,bool>(false) };
			mutable std::array<bool, countPlayers> m_SquaresAttackedByPlayerValid{ arrayhelper::make<countPlayers,bool>(false) };
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
				return m_SquaresAttackedByPlayer[player];
			}
			stack(const stack& parent, const movebitsType& movebits) noexcept :
				pygmalion::generator<descriptor_dynamics, generator>::stack(parent, movebits)
			{
			}
			stack(boardType& position, const playerType oldPlayer) noexcept :
				pygmalion::generator<descriptor_dynamics, generator>::stack(position, oldPlayer)
			{
			}
			~stack() noexcept
			{
			}
		};
		using stackType = stack;
		constexpr static squaresType sliderTargetsHV(const squareType sq, const squaresType& allowed) noexcept
		{
			return movegenSlidersHV.targets(sq, allowed);
		}
		constexpr static squaresType sliderTargetsDiag(const squareType sq, const squaresType& allowed) noexcept
		{
			return movegenSlidersDiag.targets(sq, allowed);
		}
		constexpr static squaresType sliderTargetsHV(const squaresType squares, const squaresType& allowed) noexcept
		{
			return movegenSlidersHV.targets(squares, allowed);
		}
		constexpr static squaresType sliderTargetsDiag(const squaresType squares, const squaresType& allowed) noexcept
		{
			return movegenSlidersDiag.targets(squares, allowed);
		}
		constexpr static squaresType sliderAttacksHV(const squareType sq, const squaresType& allowed) noexcept
		{
			return movegenSlidersHV.attacks(sq, allowed);
		}
		constexpr static squaresType sliderAttacksDiag(const squareType sq, const squaresType& allowed) noexcept
		{
			return movegenSlidersDiag.attacks(sq, allowed);
		}
		constexpr static squaresType sliderAttacksHV(const squaresType squares, const squaresType& allowed) noexcept
		{
			return movegenSlidersHV.attacks(squares, allowed);
		}
		constexpr static squaresType sliderAttacksDiag(const squaresType squares, const squaresType& allowed) noexcept
		{
			return movegenSlidersDiag.attacks(squares, allowed);
		}
		constexpr static squaresType knightTargets(const squareType sq, const squaresType& allowed) noexcept
		{
			return movegenKnight.targets(sq, allowed);
		}
		constexpr static squaresType knightTargets(const squaresType squares, const squaresType& allowed) noexcept
		{
			return movegenKnight.targets(squares, allowed);
		}
		constexpr static squaresType knightAttacks(const squareType sq, const squaresType& allowed) noexcept
		{
			return movegenKnight.attacks(sq, allowed);
		}
		constexpr static squaresType knightAttacks(const squaresType squares, const squaresType& allowed) noexcept
		{
			return movegenKnight.attacks(squares, allowed);
		}
		constexpr static squaresType kingTargets(const squaresType squares, const squaresType& allowed) noexcept
		{
			return movegenKing.targets(squares, allowed);
		}
		constexpr static squaresType kingTargets(const squareType sq, const squaresType& allowed) noexcept
		{
			return movegenKing.targets(sq, allowed);
		}
		constexpr static squaresType kingAttacks(const squaresType squares, const squaresType& allowed) noexcept
		{
			return movegenKing.attacks(squares, allowed);
		}
		constexpr static squaresType kingAttacks(const squareType sq, const squaresType& allowed) noexcept
		{
			return movegenKing.attacks(sq, allowed);
		}
	private:
		constexpr static const squaresType pawnPromotionFromSquaresBlack() noexcept
		{
			return static_cast<squaresType>(static_cast<squareType>(1));
		}
		constexpr static const squaresType pawnPromotionFromSquaresWhite() noexcept
		{
			return static_cast<squaresType>(static_cast<squareType>(countRanks - 2));
		}
		constexpr static const squaresType pawnFromSquaresBlack() noexcept
		{
			squaresType squares{ squaresType::none() };
			for (rankType rank = 2; rank < (countRanks - 1); rank++)
				squares |= static_cast<squaresType>(rank);
			return squares;
		}
		constexpr static const squaresType pawnFromSquaresWhite() noexcept
		{
			squaresType squares{ squaresType::none() };
			for (rankType rank = 1; rank < (countRanks - 3); rank++)
				squares |= static_cast<squaresType>(rank);
			return squares;
		}
		constexpr static const squaresType pawnDoublePushFromSquaresBlack() noexcept
		{
			squaresType squares{ squaresType::none() };
			squares |= static_cast<squaresType>(static_cast<rankType>(countRanks - 2));
			return squares;
		}
		constexpr static const squaresType pawnDoublePushFromSquaresWhite() noexcept
		{
			squaresType squares{ squaresType::none() };
			squares |= static_cast<squaresType>(static_cast<rankType>(1));
			return squares;
		}
	public:
		constexpr static squaresType pawnPushTargets(const squareType sq, const playerType p, const squaresType& allowed) noexcept
		{
			return (p == whitePlayer) ? movegenPawnPushWhite.targets(sq, allowed) : movegenPawnPushBlack.targets(sq, allowed);
		}
		constexpr static squaresType pawnCaptureTargets(const squareType sq, const playerType p, const squaresType& allowed) noexcept
		{
			return (p == whitePlayer) ? movegenPawnCaptureWhite.attacks(sq, allowed) : movegenPawnCaptureBlack.attacks(sq, allowed);
		}
		constexpr static squaresType pawnCaptureTargets(const squaresType squares, const playerType p, const squaresType& allowed) noexcept
		{
			return (p == whitePlayer) ? movegenPawnCaptureWhite.attacks(squares, allowed) : movegenPawnCaptureBlack.attacks(squares, allowed);
		}
		constexpr static squaresType pawnDoublePushTargets(const squareType sq, const playerType p, const squaresType& allowed) noexcept
		{
			return (p == whitePlayer) ? movegenPawnDoublePushWhite.targets(sq, allowed) : movegenPawnDoublePushBlack.targets(sq, allowed);
		}
		friend class stack;
	private:
		static squaresType squaresAttackedByPlayer(const stackType& stack, const playerType attackingPlayer) noexcept
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
			attacked |= pawnCaptureTargets(pawns, attackingPlayer, notBlockers);
			return attacked;
		}
		constexpr static void generateKnightMoves(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : stack.position().pieceOccupancy(knight)& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : knightTargets(from, ~stack.position().totalOccupancy()))
					moves.add(motorType::move().createQuiet(from, to));
			}
		}
		static void generateKingMoves(const stackType& stack, movelistType& moves) noexcept
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
		static void generateKingCaptures(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType forbidden{ stack.squaresAttackedByPlayer(stack.nextPlayer()) };
			const squaresType allowed{ ~forbidden };
			for (const squareType from : stack.position().pieceOccupancy(king)& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : allowed & kingAttacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(stack.nextPlayer()))
					moves.add(motorType::move().createCapture(from, to));
			}
		}
		constexpr static void generateSliderMovesHV(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen))& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : sliderTargetsHV(from, ~stack.position().totalOccupancy()))
					moves.add(motorType::move().createQuiet(from, to));
			}
		}
		constexpr static void generateSliderMovesDiag(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : (stack.position().pieceOccupancy(bishop) | stack.position().pieceOccupancy(queen))& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : sliderTargetsDiag(from, ~stack.position().totalOccupancy()))
					moves.add(motorType::move().createQuiet(from, to));
			}
		}
		constexpr static void generateSliderCapturesHV(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen))& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : sliderAttacksHV(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(stack.nextPlayer()))
					moves.add(motorType::move().createCapture(from, to));
			}
		}
		constexpr static void generateSliderCapturesDiag(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : (stack.position().pieceOccupancy(bishop) | stack.position().pieceOccupancy(queen))& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : sliderAttacksDiag(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(stack.nextPlayer()))
					moves.add(motorType::move().createCapture(from, to));
			}
		}
		constexpr static void generateKnightCaptures(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : stack.position().pieceOccupancy(knight)& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : knightAttacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(stack.nextPlayer()))
					moves.add(motorType::move().createCapture(from, to));
			}
		}
		constexpr static void generatePawnPushes(const stackType& stack, movelistType& moves) noexcept
		{
#if defined(FASTPAWNS)
			const squaresType allowed{ ~stack.position().totalOccupancy() };
			if (stack.position().movingPlayer() == whitePlayer)
			{
				constexpr const squaresType fromSquares{ pawnFromSquaresWhite() };
				const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				const squaresType allowedPawns{ pawns & fromSquares };
				if (allowedPawns)
				{
					const squaresType pushedPawns{ allowedPawns.up() };
					const squaresType allowedPushes{ pushedPawns & allowed };
					for (const auto sq : allowedPushes)
						moves.add(motorType::move().createQuiet(sq.down(), sq));
				}
			}
			else
			{
				constexpr const squaresType fromSquares{ pawnFromSquaresBlack() };
				const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
				const squaresType allowedPawns{ pawns & fromSquares };
				if (allowedPawns)
				{
					const squaresType pushedPawns{ allowedPawns.down() };
					const squaresType allowedPushes{ pushedPawns & allowed };
					for (const auto sq : allowedPushes)
						moves.add(motorType::move().createQuiet(sq.up(), sq));
				}
			}
#else
			if (stack.position().movingPlayer() == whitePlayer)
			{
				for (const squareType from : stack.position().pieceOccupancy(pawn)& stack.position().playerOccupancy(whitePlayer))
				{
					for (const squareType to : movegenPawnPushWhite.targets(from, ~stack.position().totalOccupancy()))
						moves.add(motorType::move().createQuiet(from, to));
				}
			}
			else
			{
				for (const squareType from : stack.position().pieceOccupancy(pawn)& stack.position().playerOccupancy(blackPlayer))
				{
					for (const squareType to : movegenPawnPushBlack.targets(from, ~stack.position().totalOccupancy()))
						moves.add(motorType::move().createQuiet(from, to));
				}
			}
#endif
		}
		constexpr static void generatePawnPromotions(const stackType& stack, movelistType& moves) noexcept
		{
#if defined(FASTPAWNS)
			const squaresType allowed{ ~stack.position().totalOccupancy() };
			if (stack.position().movingPlayer() == whitePlayer)
			{
				constexpr const squaresType fromSquares{ pawnPromotionFromSquaresWhite() };
				const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				const squaresType allowedPawns{ pawns & fromSquares };
				if (allowedPawns)
				{
					const squaresType pushedPawns{ allowedPawns.up() };
					const squaresType allowedPushes{ pushedPawns & allowed };
					for (const auto sq : allowedPushes)
					{
						const squareType sq1{ sq.down() };
						moves.add(motorType::move().createPromotionQueen(sq1, sq));
						moves.add(motorType::move().createPromotionKnight(sq1, sq));
						moves.add(motorType::move().createPromotionRook(sq1, sq));
						moves.add(motorType::move().createPromotionBishop(sq1, sq));
					}
				}
			}
			else
			{
				constexpr const squaresType fromSquares{ pawnPromotionFromSquaresBlack() };
				const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
				const squaresType allowedPawns{ pawns & fromSquares };
				if (allowedPawns)
				{
					const squaresType pushedPawns{ allowedPawns.down() };
					const squaresType allowedPushes{ pushedPawns & allowed };
					for (const auto sq : allowedPushes)
					{
						const squareType sq1{ sq.up() };
						moves.add(motorType::move().createPromotionQueen(sq1, sq));
						moves.add(motorType::move().createPromotionKnight(sq1, sq));
						moves.add(motorType::move().createPromotionRook(sq1, sq));
						moves.add(motorType::move().createPromotionBishop(sq1, sq));
					}
				}
			}
#else
			if (stack.position().movingPlayer() == whitePlayer)
			{
				for (const squareType from : stack.position().pieceOccupancy(pawn)& stack.position().playerOccupancy(whitePlayer))
				{
					for (const squareType to : movegenPawnPromotionWhite.targets(from, ~stack.position().totalOccupancy()))
					{
						moves.add(motorType::move().createPromotionQueen(from, to));
						moves.add(motorType::move().createPromotionKnight(from, to));
						moves.add(motorType::move().createPromotionRook(from, to));
						moves.add(motorType::move().createPromotionBishop(from, to));
					}
				}
			}
			else
			{
				for (const squareType from : stack.position().pieceOccupancy(pawn)& stack.position().playerOccupancy(blackPlayer))
				{
					for (const squareType to : movegenPawnPromotionBlack.targets(from, ~stack.position().totalOccupancy()))
					{
						moves.add(motorType::move().createPromotionQueen(from, to));
						moves.add(motorType::move().createPromotionKnight(from, to));
						moves.add(motorType::move().createPromotionRook(from, to));
						moves.add(motorType::move().createPromotionBishop(from, to));
					}
				}
			}
#endif
		}
		constexpr static void generatePawnCaptures(const stackType& stack, movelistType& moves) noexcept
		{
#if defined(FASTPAWNS)
			if (stack.position().movingPlayer() == whitePlayer)
			{
				const squaresType allowed{ stack.position().playerOccupancy(blackPlayer) };
				constexpr const squaresType fromSquares{ pawnFromSquaresWhite() };
				const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				const squaresType allowedPawns{ pawns & fromSquares };
				if (allowedPawns)
				{
					const squaresType leftCaptures{ allowedPawns.upLeft() };
					const squaresType rightCaptures{ allowedPawns.upRight() };
					const squaresType allowedLeftCaptures{ leftCaptures & allowed };
					const squaresType allowedRightCaptures{ rightCaptures & allowed };
					for (const auto sq : allowedLeftCaptures)
						moves.add(motorType::move().createCapture(sq.downRight(), sq));
					for (const auto sq : allowedRightCaptures)
						moves.add(motorType::move().createCapture(sq.downLeft(), sq));
				}
			}
			else
			{
				const squaresType allowed{ stack.position().playerOccupancy(whitePlayer) };
				constexpr const squaresType fromSquares{ pawnFromSquaresBlack() };
				const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
				const squaresType allowedPawns{ pawns & fromSquares };
				if (allowedPawns)
				{
					const squaresType leftCaptures{ allowedPawns.downLeft() };
					const squaresType rightCaptures{ allowedPawns.downRight() };
					const squaresType allowedLeftCaptures{ leftCaptures & allowed };
					const squaresType allowedRightCaptures{ rightCaptures & allowed };
					for (const auto sq : allowedLeftCaptures)
						moves.add(motorType::move().createCapture(sq.upRight(), sq));
					for (const auto sq : allowedRightCaptures)
						moves.add(motorType::move().createCapture(sq.upLeft(), sq));
				}
			}
#else
			if (stack.position().movingPlayer() == whitePlayer)
			{
				for (const squareType from : stack.position().pieceOccupancy(pawn)& stack.position().playerOccupancy(whitePlayer))
				{
					for (const squareType to : movegenPawnCaptureWhite.attacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(blackPlayer))
						moves.add(motorType::move().createCapture(from, to));
				}
			}
			else
			{
				for (const squareType from : stack.position().pieceOccupancy(pawn)& stack.position().playerOccupancy(blackPlayer))
				{
					for (const squareType to : movegenPawnCaptureBlack.attacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(whitePlayer))
						moves.add(motorType::move().createCapture(from, to));
				}
			}
#endif
		}
		constexpr static void generatePawnPromoCaptures(const stackType& stack, movelistType& moves) noexcept
		{
#if defined(FASTPAWNS)
			if (stack.position().movingPlayer() == whitePlayer)
			{
				const squaresType allowed{ stack.position().playerOccupancy(blackPlayer) };
				constexpr const squaresType fromSquares{ pawnPromotionFromSquaresWhite() };
				const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				const squaresType allowedPawns{ pawns & fromSquares };
				if (allowedPawns)
				{
					const squaresType leftCaptures{ allowedPawns.upLeft() };
					const squaresType rightCaptures{ allowedPawns.upRight() };
					const squaresType allowedLeftCaptures{ leftCaptures & allowed };
					const squaresType allowedRightCaptures{ rightCaptures & allowed };
					for (const auto sq : allowedLeftCaptures)
					{
						const squareType sq1{ sq.downRight() };
						moves.add(motorType::move().createPromoCaptureQueen(sq1, sq));
						moves.add(motorType::move().createPromoCaptureKnight(sq1, sq));
						moves.add(motorType::move().createPromoCaptureRook(sq1, sq));
						moves.add(motorType::move().createPromoCaptureBishop(sq1, sq));
					}
					for (const auto sq : allowedRightCaptures)
					{
						const squareType sq1{ sq.downLeft() };
						moves.add(motorType::move().createPromoCaptureQueen(sq1, sq));
						moves.add(motorType::move().createPromoCaptureKnight(sq1, sq));
						moves.add(motorType::move().createPromoCaptureRook(sq1, sq));
						moves.add(motorType::move().createPromoCaptureBishop(sq1, sq));
					}
				}
			}
			else
			{
				const squaresType allowed{ stack.position().playerOccupancy(whitePlayer) };
				constexpr const squaresType fromSquares{ pawnPromotionFromSquaresBlack() };
				const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
				const squaresType allowedPawns{ pawns & fromSquares };
				if (allowedPawns)
				{
					const squaresType leftCaptures{ allowedPawns.downLeft() };
					const squaresType rightCaptures{ allowedPawns.downRight() };
					const squaresType allowedLeftCaptures{ leftCaptures & allowed };
					const squaresType allowedRightCaptures{ rightCaptures & allowed };
					for (const auto sq : allowedLeftCaptures)
					{
						const squareType sq1{ sq.upRight() };
						moves.add(motorType::move().createPromoCaptureQueen(sq1, sq));
						moves.add(motorType::move().createPromoCaptureKnight(sq1, sq));
						moves.add(motorType::move().createPromoCaptureRook(sq1, sq));
						moves.add(motorType::move().createPromoCaptureBishop(sq1, sq));
					}
					for (const auto sq : allowedRightCaptures)
					{
						const squareType sq1{ sq.upLeft() };
						moves.add(motorType::move().createPromoCaptureQueen(sq1, sq));
						moves.add(motorType::move().createPromoCaptureKnight(sq1, sq));
						moves.add(motorType::move().createPromoCaptureRook(sq1, sq));
						moves.add(motorType::move().createPromoCaptureBishop(sq1, sq));
					}
				}
			}
#else
			if (stack.position().movingPlayer() == whitePlayer)
			{
				for (const squareType from : stack.position().pieceOccupancy(pawn)& stack.position().playerOccupancy(whitePlayer))
				{
					for (const squareType to : movegenPawnPromoCaptureWhite.attacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(blackPlayer))
					{
						moves.add(motorType::move().createPromoCaptureQueen(from, to));
						moves.add(motorType::move().createPromoCaptureKnight(from, to));
						moves.add(motorType::move().createPromoCaptureRook(from, to));
						moves.add(motorType::move().createPromoCaptureBishop(from, to));
					}
				}
			}
			else
			{
				for (const squareType from : stack.position().pieceOccupancy(pawn)& stack.position().playerOccupancy(blackPlayer))
				{
					for (const squareType to : movegenPawnPromoCaptureBlack.attacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(whitePlayer))
					{
						moves.add(motorType::move().createPromoCaptureQueen(from, to));
						moves.add(motorType::move().createPromoCaptureKnight(from, to));
						moves.add(motorType::move().createPromoCaptureRook(from, to));
						moves.add(motorType::move().createPromoCaptureBishop(from, to));
					}
				}
			}
#endif
		}
		constexpr static void generatePawnDoublePushes(const stackType& stack, movelistType& moves) noexcept
		{
#if defined(FASTPAWNS)
			const squaresType allowed{ ~stack.position().totalOccupancy() };
			if (stack.position().movingPlayer() == whitePlayer)
			{
				constexpr const squaresType fromSquares{ pawnDoublePushFromSquaresWhite() };
				const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				const squaresType allowedPawns{ pawns & fromSquares };
				if (allowedPawns)
				{
					const squaresType pushedPawns{ allowedPawns.up() };
					const squaresType allowedPushes{ pushedPawns & allowed };
					const squaresType doublePushedPawns{ allowedPushes.up() };
					const squaresType allowedDoublePushes{ doublePushedPawns & allowed };
					for (const auto sq : allowedDoublePushes)
						moves.add(motorType::move().createDoublePush(sq.file()));
				}
			}
			else
			{
				constexpr const squaresType fromSquares{ pawnDoublePushFromSquaresBlack() };
				const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
				const squaresType allowedPawns{ pawns & fromSquares };
				if (allowedPawns)
				{
					const squaresType pushedPawns{ allowedPawns.down() };
					const squaresType allowedPushes{ pushedPawns & allowed };
					const squaresType doublePushedPawns{ allowedPushes.down() };
					const squaresType allowedDoublePushes{ doublePushedPawns & allowed };
					for (const auto sq : allowedDoublePushes)
						moves.add(motorType::move().createDoublePush(sq.file()));
				}
			}
#else
			if (stack.position().movingPlayer() == whitePlayer)
			{
				for (const squareType from : stack.position().pieceOccupancy(pawn)& stack.position().playerOccupancy(whitePlayer))
				{
					for (const squareType to : movegenPawnDoublePushWhite.targets(from, ~stack.position().totalOccupancy()))
						moves.add(motorType::move().createDoublePush(from.file()));
				}
			}
			else
			{
				for (const squareType from : stack.position().pieceOccupancy(pawn)& stack.position().playerOccupancy(blackPlayer))
				{
					for (const squareType to : movegenPawnDoublePushBlack.targets(from, ~stack.position().totalOccupancy()))
						moves.add(motorType::move().createDoublePush(from.file()));
				}
			}
#endif
		}
		static void generateCastles(const stackType& stack, movelistType& moves) noexcept
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
		static void generatePawnEnPassant(const stackType& stack, movelistType& moves) noexcept
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
	public:
		static bool isMoveLegal_Implementation(const stackType& stack, const movebitsType& moveBits) noexcept
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
			const squareType kingsquare{ (from == kingsquareOld) ? to : kingsquareOld };

			// Does he live on a square that is guarded by the other king?
			const squaresType attackedByOtherKing{ movegenKing.attacks(otherking,squaresType::all()) };
			if (attackedByOtherKing[kingsquare])
				return false;

			// We need the enemy occupancy bitboard as it would be after the move...
			const squaresType otherOccupancy{ position.playerOccupancy(otherPlayer) };
			const squaresType otherDelta{ motorType::move().otherOccupancyDelta(position, moveBits) };
			const squaresType occOther{ otherOccupancy ^ otherDelta };

			// Does he live on a square that is guarded by an enemy knight?
			const squaresType otherKnights{ ((position.pieceOccupancy(knight) & otherOccupancy) ^ otherDelta) & occOther };
			const squaresType attackedByOtherKnights{ movegenKnight.attacks(otherKnights,squaresType::all()) };
			if (attackedByOtherKnights[kingsquare])
				return false;

			// Does he live on a square that is guarded by an enemy pawn?
			const squaresType otherPawns{ ((position.pieceOccupancy(pawn) & otherOccupancy) ^ otherDelta) & occOther };
			const squaresType attackedByOtherPawns{ (otherPlayer == whitePlayer) ? movegenPawnCaptureWhite.attacks(otherPawns,squaresType::all()) : movegenPawnCaptureBlack.attacks(otherPawns,squaresType::all()) };
			if (attackedByOtherPawns[kingsquare])
				return false;

			// We need the total occupancy bitboard as it would be after the move...
			const squaresType movingOccupancy{ position.playerOccupancy(movingPlayer) };
			const squaresType movingDelta{ motorType::move().ownOccupancyDelta(position, moveBits) };
			const squaresType occMoving{ movingOccupancy ^ movingDelta };
			const squaresType occTotal{ occOther | occMoving };

			// Is he attacked horizontally by sliding pieces?
			const squaresType queens{ position.pieceOccupancy(queen) };
			const squaresType otherSlidersHV = occOther & (position.pieceOccupancy(rook) | queens);
			if (movegenSlidersHV.attacks(otherSlidersHV, ~occTotal)[kingsquare])
				return false;

			// Is he attacked diagonally by sliding pieces?
			const squaresType otherSlidersDiag = occOther & (position.pieceOccupancy(bishop) | queens);
			if (movegenSlidersDiag.attacks(otherSlidersDiag, ~occTotal)[kingsquare])
				return false;

			// The move seems legal
			return true;
		}
		static bool generateMoves_Implementation(const stackType& stack, movelistType& moves, size_t& currentPass) noexcept
		{
			switch (currentPass)
			{
			default:
				return false;
			case 0:
				currentPass = 1;
				generateKnightMoves(stack, moves);
				return true;
			case 1:
				currentPass = 2;
				generatePawnPushes(stack, moves);
				return true;
			case 2:
				currentPass = 3;
				generatePawnDoublePushes(stack, moves);
				return true;
			case 3:
				currentPass = 4;
				generateKnightCaptures(stack, moves);
				return true;
			case 4:
				currentPass = 5;
				generatePawnCaptures(stack, moves);
				return true;
			case 5:
				currentPass = 6;
				generatePawnEnPassant(stack, moves);
				return true;
			case 6:
				currentPass = 7;
				generateSliderMovesHV(stack, moves);
				return true;
			case 7:
				currentPass = 8;
				generateSliderMovesDiag(stack, moves);
				return true;
			case 8:
				currentPass = 9;
				generateSliderCapturesHV(stack, moves);
				return true;
			case 9:
				currentPass = 10;
				generateSliderCapturesDiag(stack, moves);
				return true;
			case 10:
				currentPass = 11;
				generateKingMoves(stack, moves);
				return true;
			case 11:
				currentPass = 12;
				generateKingCaptures(stack, moves);
				return true;
			case 12:
				currentPass = 13;
				generateCastles(stack, moves);
				return true;
			case 13:
				currentPass = 14;
				generatePawnPromotions(stack, moves);
				return true;
			case 14:
				currentPass = 15;
				generatePawnPromoCaptures(stack, moves);
				return true;
			}
		}
		static bool generateTacticalMoves_Implementation(const stackType& stack, movelistType& moves, size_t& currentPass) noexcept
		{
			switch (currentPass)
			{
			default:
				return false;
			case 0:
				currentPass = 1;
				generateKnightCaptures(stack, moves);
				return true;
			case 1:
				currentPass = 2;
				generatePawnCaptures(stack, moves);
				return true;
			case 2:
				currentPass = 3;
				generatePawnEnPassant(stack, moves);
				return true;
			case 3:
				currentPass = 4;
				generateSliderCapturesHV(stack, moves);
				return true;
			case 4:
				currentPass = 5;
				generateSliderCapturesDiag(stack, moves);
				return true;
			case 5:
				currentPass = 6;
				generateKingCaptures(stack, moves);
				return true;
			case 6:
				currentPass = 7;
				generatePawnPromoCaptures(stack, moves);
				return true;
			}
			return false;
		}
	};
}