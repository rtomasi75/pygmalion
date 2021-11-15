namespace pygmalion::chess
{
	class evaluator :
		public pygmalion::evaluator<descriptor_evaluation, evaluator
		//		, evaluationstage_pawnstructure
		//		, evaluationstage_attacks
		//		, evaluationstage_mobility
		//		, evaluationstage_control
		//		, evaluationstage_kingsafety
		>
	{
	public:
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType computeMaterial_Implementation(const typename generatorType::template stackType<PLAYER>& stack) noexcept
		{
			const scoreType mat{ static_cast<scoreType>(stack.position().material()) };
			const bool invert{ stack.movingPlayer() == blackPlayer };
			return invert ? -mat : mat;
		}
		PYGMALION_INLINE PYGMALION_TUNABLE static scoreType initialAspirationWindowSize() noexcept
		{
			PYGMALION_TUNABLE const scoreType delta{ rootDelta() / 8 };
			return delta;
		}
		PYGMALION_INLINE constexpr static size_t countAspirationWindows_Implementation() noexcept
		{
			return 128;
		}
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commandsImplementation() noexcept;
		template<size_t PLAYER, bool LAZY>
		static gamestateType earlyResult_Implementation(const generatorType::template stackType<PLAYER>& stack, bool& allowStoreTT) noexcept
		{
			if constexpr (!LAZY)
			{
				if (stack.position().cumulation().reversiblePlies() >= 100)
				{
					allowStoreTT = false;
					return gamestateType::draw();
				}
			}
			if (stack.position().playerOccupancy(whitePlayer) == squaresType(stack.kingSquare(whitePlayer)))
			{
				if (stack.position().playerOccupancy(blackPlayer) == squaresType(stack.kingSquare(blackPlayer)))
					return gamestateType::draw();
				if (!(stack.position().playerOccupancy(blackPlayer) & (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen) | stack.position().pieceOccupancy(pawn))))
				{
					if (!(stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(bishop)))
					{
						if ((stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(knight)).count() == 1)
						{
							allowStoreTT = true;
							return gamestateType::draw();
						}
					}
					if (!(stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(knight)))
					{
						if ((stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(bishop)).count() == 1)
						{
							allowStoreTT = true;
							return gamestateType::draw();
						}
					}
				}
			}
			else if (stack.position().playerOccupancy(blackPlayer) == squaresType(stack.kingSquare(blackPlayer)))
			{
				if (!(stack.position().playerOccupancy(whitePlayer) & (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen) | stack.position().pieceOccupancy(pawn))))
				{
					if (!(stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)))
					{
						if ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(knight)).count() == 1)
						{
							allowStoreTT = true;
							return gamestateType::draw();
						}
					}
					if (!(stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(knight)))
					{
						if ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)).count() == 1)
						{
							allowStoreTT = true;
							return gamestateType::draw();
						}
					}
				}
			}
			else if (!(stack.position().pieceOccupancy(queen) | stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(knight) | stack.position().pieceOccupancy(pawn)))
			{
				if (((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)).count() == 1) && ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)).count() == 1))
				{
					const squareType whiteBishop{ *(stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)).begin() };
					const squareType blackBishop{ *(stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(bishop)).begin() };
					if (whiteBishop.isDark() == blackBishop.isDark())
					{
						allowStoreTT = true;
						return gamestateType::draw();
					}
				}
			}
			if constexpr (!LAZY)
			{
				if (stack.occurs(stack.position(), 2, 4, 4))
				{
					allowStoreTT = false;
					return gamestateType::draw();
				}
			}
			return gamestateType::open();
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static gamestateType lateResult_Implementation(const typename generatorType::template stackType<PLAYER>& stack) noexcept
		{
			if (stack.isPositionCritical())
				return gamestateType::loss(stack.position().movingPlayer());
			else
				return gamestateType::draw();
		}
		PYGMALION_INLINE static squareType leastValuablePiece(const boardType& position, const squaresType mask, const playerType side) noexcept
		{
			const squaresType occ{ position.playerOccupancy(side) & mask };
			squareType best{ squareType::invalid };
			materialScore lowest{ materialScore::maximum() };
			for (const auto sq : occ)
			{
				const pieceType pc{ position.getPiece(sq) };
				const materialScore value{ boardType::materialValueRelative(pc,sq,side) };
				if (value < lowest)
				{
					best = sq;
					lowest = value;
				}
			}
			return best;
		}
		PYGMALION_INLINE static materialScore staticExchange(const movebitsType move, const boardType& position) noexcept
		{
			constexpr const materialScore zero{ materialScore::zero() };
			const squareType to{ motorType::move().toSquare(position, move) };
			const squareType from{ motorType::move().fromSquare(position, move) };
			pieceType attackingPiece{ position.getPiece(from) };
			playerType movingSide{ position.getPlayer(from) };
			playerType defendingSide{ movingSide.next() };
			PYGMALION_ASSERT(attackingPiece.isValid());
			materialScore gain[32];
			pieceType promotedPiece{ attackingPiece };
			if (motorType::move().isPromotion(move))
				promotedPiece = motorType::move().promotedPiece(move);
			gain[0] = boardType::materialValueRelative(promotedPiece, to, movingSide) - boardType::materialValueRelative(attackingPiece, from, movingSide);
			if (motorType::move().isCapture(move))
			{
				const squareType captureSquare{ motorType::move().captureSquare(position, move) };
				const pieceType capPiece = position.getPiece(captureSquare);
				gain[0] += boardType::materialValueRelative(capPiece, captureSquare, defendingSide);
			}
			squaresType mayXrayHV{ position.pieceOccupancy(queen) | position.pieceOccupancy(rook) };
			squaresType mayXrayDiag{ position.pieceOccupancy(queen) | position.pieceOccupancy(bishop) };
			int d{ 0 };
			squaresType occBB{ position.totalOccupancy() };
			squaresType attackBB{ generatorType::attackers(position,to) };
			squaresType fromBB{ squaresType(from) };
			gain[1] = zero;
			while (d < 30)
			{
				movingSide = defendingSide;
				defendingSide = movingSide.next();
				d++;
				attackBB &= ~fromBB;
				occBB &= ~fromBB;
				mayXrayHV &= ~fromBB;
				mayXrayDiag &= ~fromBB;
				attackBB |= generatorType::attacksXrayHV(to, occBB, mayXrayHV);
				attackBB |= generatorType::attacksXrayDiag(to, occBB, mayXrayDiag);
				const squareType leastSquare{ leastValuablePiece(position, attackBB, movingSide) };
				if (leastSquare.isValid())
				{
					if (promotedPiece == king)
					{
						d--;
						break;
					}
					const squareType attackersquare{ leastSquare };
					const pieceType capturedPiece{ promotedPiece };
					promotedPiece = position.getPiece(attackersquare);
					gain[d] = boardType::materialValueRelative(promotedPiece, to, movingSide) - boardType::materialValueRelative(promotedPiece, attackersquare, movingSide) + boardType::materialValueRelative(capturedPiece, to, defendingSide) - gain[d - 1];
					fromBB = squaresType(attackersquare);
				}
				else
					break;
			}
			if (d > 0)
			{
				while (--d)
					gain[d - 1] = -materialScore::max(-gain[d - 1], gain[d]);
			}
			return gain[0];
		}
		PYGMALION_INLINE static scoreType staticTacticalMoveScore_Implementation(const boardType& position, const movebitsType move) noexcept
		{
			return static_cast<scoreType>(staticExchange(move, position));
		}
		constexpr static size_t countParameters_Implementation() noexcept
		{
			return 4;
		}
#if defined(PYGMALION_TUNE)
		static parameter getParameter_Implementation(const size_t index) noexcept
		{
			switch (index)
			{
			case 0: // knight
				return parameter(boardType::getMaterial(knight, whitePlayer), 2.0, 4.0, 0.001, "material_knight");
			case 1: // bishop
				return parameter(boardType::getMaterial(bishop, whitePlayer), 2.0, 4.0, 0.001, "material_bishop");
			case 2: // rook
				return parameter(boardType::getMaterial(rook, whitePlayer), 4.5, 7.0, 0.001, "material_rook");
			case 3: // queen
				return parameter(boardType::getMaterial(queen, whitePlayer), 7.5, 12.0, 0.001, "material_queen");
			default:
				PYGMALION_ASSERT(false);
				return parameter(0.0, 0.0, 0.0, 0.0, "???");
			}
		}
		static void setParameter_Implementation(const size_t index, double value) noexcept
		{
			switch (index)
			{
			case 0: // knight
				boardType::setMaterial(knight, value);
				break;
			case 1: // bishop
				boardType::setMaterial(bishop, value);
				break;
			case 2: // rook
				boardType::setMaterial(rook, value);
				break;
			case 3: // queen
				boardType::setMaterial(queen, value);
				break;
			default:
				PYGMALION_ASSERT(false);
				break;
			}
		}
#endif
	};
}