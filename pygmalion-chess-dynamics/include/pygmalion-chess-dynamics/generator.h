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
		constexpr static const inline movegen_pawn_promotion_black movegenPawnPromotionBlack{ movegen_pawn_promotion_black() };
		constexpr static const inline movegen_pawn_promotion_white movegenPawnPromotionWhite{ movegen_pawn_promotion_white() };
		constexpr static const inline movegen_pawn_promocapture_black movegenPawnPromoCaptureBlack{ movegen_pawn_promocapture_black() };
		constexpr static const inline movegen_pawn_promocapture_white movegenPawnPromoCaptureWhite{ movegen_pawn_promocapture_white() };
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
			mutable std::array<squaresType, countPlayers> m_SquaresAttackedByPlayer{ arrayhelper::make<countPlayers,squaresType>(squaresType::none()) };
			mutable std::array<squaresType, countPlayers> m_SquaresTargetedByPlayer{ arrayhelper::make<countPlayers,squaresType>(squaresType::none()) };
			mutable std::array<squaresType, countPlayers> m_ControlledByPlayer{ arrayhelper::make<countPlayers,squaresType>(squaresType::none()) };
			mutable std::array<squareType, countPlayers> m_KingSquare{ arrayhelper::make<countPlayers,squareType>(squareType::invalid) };
			mutable std::array<bool, countPlayers> m_IsKingSquareValid{ arrayhelper::make<countPlayers,bool>(false) };
			mutable std::array<bool, countPlayers> m_SquaresAttackedByPlayerValid{ arrayhelper::make<countPlayers,bool>(false) };
			mutable std::array<bool, countPlayers> m_SquaresTargetedByPlayerValid{ arrayhelper::make<countPlayers,bool>(false) };
			mutable bool m_IsCheckValid{ false };
			mutable bool m_IsCheck{ false };
			mutable bool m_IsControlValid{ false };
		public:
			void control(squaresType& white, squaresType& black) const;
			squareType kingSquare(const playerType player) const noexcept;
			squaresType squaresTargetedByPlayer(const playerType player) const;
			squaresType squaresAttackedByPlayer(const playerType player) const;
			bool isCheck() const noexcept;
			stack(const stack& parent, const movebitsType& movebits) noexcept;
			stack(boardType& position, historyType& history, const playerType oldPlayer) noexcept;
			~stack() noexcept;
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
		constexpr static squaresType pawnAttacks(const squareType sq, const playerType p, const squaresType& allowed) noexcept
		{
			if (p == whitePlayer)
				return movegenPawnCaptureWhite.attacks(sq, allowed);
			else
				return movegenPawnCaptureBlack.attacks(sq, allowed);
		}
		constexpr static squaresType pawnAttacks(const squaresType squares, const playerType p, const squaresType& allowed) noexcept
		{
			if (p == whitePlayer)
				return movegenPawnCaptureWhite.attacks(squares, allowed);
			else
				return movegenPawnCaptureBlack.attacks(squares, allowed);
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
			return static_cast<squaresType>(static_cast<rankType>(1));
		}
		constexpr static const squaresType pawnPromotionFromSquaresWhite() noexcept
		{
			return static_cast<squaresType>(static_cast<rankType>(countRanks - 2));
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
			for (rankType rank = 1; rank < (countRanks - 2); rank++)
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
		static void control(const generatorType::stackType& stack, squaresType& white, squaresType& black) noexcept;
		static squaresType attackers(const boardType& position, const squareType square) noexcept;
		static squaresType attackers(const boardType& position, const squareType square, const playerType attacker) noexcept;
		static bool isAttacked(const boardType& position, const squareType square, const playerType attacker) noexcept;
		static squaresType squaresAttackedByPlayer(const stackType& stack, const playerType attackingPlayer) noexcept;
		static squaresType squaresTargetedByPlayer(const stackType& stack, const playerType attackingPlayer) noexcept;
		static void generateKingMoves(const stackType& stack, movelistType& moves) noexcept;
		static void generateKingCaptures(const stackType& stack, movelistType& moves) noexcept;
		static void generateCastles(const stackType& stack, movelistType& moves) noexcept;
		static void generatePawnEnPassant(const stackType& stack, movelistType& moves) noexcept;
		constexpr static void generateKnightMoves(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : stack.position().pieceOccupancy(knight)& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : knightTargets(from, ~stack.position().totalOccupancy()))
					moves.add(motorType::move().createQuiet(from, to));
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
					const squaresType temp{ allowedPawns.up() };
					const squaresType leftCaptures{ temp.left() };
					const squaresType rightCaptures{ temp.right() };
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
					const squaresType temp{ allowedPawns.down() };
					const squaresType leftCaptures{ temp.left() };
					const squaresType rightCaptures{ temp.right() };
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
					const squaresType temp{ allowedPawns.up() };
					const squaresType leftCaptures{ temp.left() };
					const squaresType rightCaptures{ temp.right() };
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
					const squaresType temp{ allowedPawns.down() };
					const squaresType leftCaptures{ temp.left() };
					const squaresType rightCaptures{ temp.right() };
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
	public:
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commandsImplementation() noexcept;
		static bool isMoveLegal_Implementation(const stackType& stack, const movebitsType& moveBits) noexcept;
		static bool generateMoves_Implementation(const stackType& stack, movelistType& moves, size_t& currentPass) noexcept;
		static bool generateTacticalMoves_Implementation(const stackType& stack, movelistType& moves, size_t& currentPass) noexcept;
		static void movesFromSquare(const stackType& stack, const squareType square, squaresType& moves, squaresType& captures) noexcept;
		static std::string moveToString_Implementation(const stackType& stack, const movebitsType mv) noexcept;
		};
		}