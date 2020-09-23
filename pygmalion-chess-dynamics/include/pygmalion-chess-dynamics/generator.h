namespace pygmalion::chess
{
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
		using stackType = typename pygmalion::generator<descriptor_dynamics, generator>::stack;
		constexpr static squaresType knightTargets(const squareType sq, const squaresType& allowed) noexcept
		{
			return movegenKnight.targets(sq, allowed);
		}
		constexpr static squaresType knightAttacks(const squareType sq, const squaresType& allowed) noexcept
		{
			return movegenKnight.attacks(sq, allowed);
		}
		constexpr static squaresType pawnPushTargets(const squareType sq, const playerType p, const squaresType& allowed) noexcept
		{
			return (p == whitePlayer) ? movegenPawnPushWhite.targets(sq, allowed) : movegenPawnPushBlack.targets(sq, allowed);
		}
		constexpr static squaresType pawnCaptureTargets(const squareType sq, const playerType p, const squaresType& allowed) noexcept
		{
			return (p == whitePlayer) ? movegenPawnCaptureWhite.attacks(sq, allowed) : movegenPawnCaptureBlack.attacks(sq, allowed);
		}
		constexpr static squaresType pawnDoublePushTargets(const squareType sq, const playerType p, const squaresType& allowed) noexcept
		{
			return (p == whitePlayer) ? movegenPawnDoublePushWhite.targets(sq, allowed) : movegenPawnDoublePushBlack.targets(sq, allowed);
		}
	private:
		constexpr static void generateKnightMoves(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : stack.position().pieceOccupancy(knight)& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : knightTargets(from, ~stack.position().totalOccupancy()))
					moves.add(motorType::move().createQuiet(from, to));
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
		}
		constexpr static void generatePawnCaptures(const stackType& stack, movelistType& moves) noexcept
		{
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
		}
		constexpr static void generatePawnDoublePushes(const stackType& stack, movelistType& moves) noexcept
		{
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
		}
		constexpr static void generatePawnEnPassant(const stackType& stack, movelistType& moves) noexcept
		{
			const uint_t<8, false> epFlags{ stack.position().flags().extractRange<4,11>() };
			size_t bit{ 0 };
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
		static bool isMoveLegal_Implementation(const stackType& stack, const movebitsType& mv) noexcept
		{
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
			}
			return false;
		}

	};
}