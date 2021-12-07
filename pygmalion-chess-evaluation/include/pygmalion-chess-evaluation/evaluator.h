namespace pygmalion::chess
{
	class evaluator :
		public pygmalion::evaluator<descriptor_evaluation, evaluator
		//, evaluationstage_attacks
		//, evaluationstage_mobility
		//, evaluationstage_pawnstructure
		//, evaluationstage_control
		//, evaluationstage_kingsafety
		//		, evaluationstage_kingareasafety
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
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType differentiateMaterial_Implementation(const typename generatorType::template stackType<PLAYER>& stack, const size_t parameterIndex, const double parameterValue) noexcept
		{

		}
		PYGMALION_INLINE PYGMALION_TUNABLE static scoreType initialAspirationWindowSize() noexcept
		{
			constexpr const scoreType delta{ static_cast<scoreType>(0.25) };
			return delta;
		}
		PYGMALION_INLINE constexpr static size_t countAspirationWindows_Implementation() noexcept
		{
			return 4;
		}
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commandsImplementation() noexcept;
		template<size_t PLAYER, bool LAZY>
		static gamestateType earlyResult_Implementation(const generatorType::template stackType<PLAYER>& stack, bool& allowStoreTT) noexcept
		{
			if constexpr (!LAZY)
			{
				if (stack.position().getReversiblePlyCount() >= 100)
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
		template<size_t PLAYER>
		PYGMALION_INLINE static squareType leastValuablePiece(const boardType& position, const squaresType mask, const materialTableType& materialTable) noexcept
		{
			constexpr const playerType side{ static_cast<playerType>(PLAYER) };
			const squaresType occ{ position.playerOccupancy(side) & mask };
			squareType best{ squareType::invalid };
			scoreType lowest{ materialScore::maximum() };
			for (const auto sq : occ)
			{
				const pieceType pc{ position.getPiece(sq) };
				const scoreType value{ materialTable.material(side,pc,sq).template makeSubjective<PLAYER>() };
				if (value < lowest)
				{
					best = sq;
					lowest = value;
				}
			}
			return best;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static objectiveType staticExchange(const movebitsType move, const boardType& position, const materialTableType& materialTable) noexcept
		{
			playerType movingSide{ static_cast<playerType>(PLAYER) };
			playerType defendingSide{ movingSide.next() };
			constexpr const objectiveType zero{ objectiveType::zero() };
			const squareType to{ motorType::move().toSquare(position, move) };
			const squareType from{ motorType::move().fromSquare(position, move) };
			PYGMALION_ASSERT(movingSide == position.getPlayer(from));
			pieceType attackingPiece{ position.getPiece(from) };
			PYGMALION_ASSERT(attackingPiece.isValid());
			objectiveType gain[32];
			pieceType promotedPiece{ attackingPiece };
			if (motorType::move().isPromotion(move))
				promotedPiece = motorType::move().promotedPiece(move);
			gain[0] = materialTable.material(movingSide, promotedPiece, to) - materialTable.material(movingSide, attackingPiece, from);
			if (motorType::move().isCapture(move))
			{
				const squareType captureSquare{ motorType::move().captureSquare(position, move) };
				const pieceType capPiece = position.getPiece(captureSquare);
				gain[0] -= materialTable.material(defendingSide, capPiece, captureSquare);
			}
			squaresType mayXrayHV{ position.pieceOccupancy(queen) | position.pieceOccupancy(rook) };
			squaresType mayXrayDiag{ position.pieceOccupancy(queen) | position.pieceOccupancy(bishop) };
			int d{ 0 };
			squaresType occBB{ position.totalOccupancy() };
			squaresType attackBB{ generatorType::attackersBoth(position,to) };
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
				const squareType leastSquare{ evaluator::template leastValuablePiece<PLAYER>(position, attackBB, materialTable) };
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
					gain[d] = materialTable.material(movingSide, promotedPiece, to) - materialTable.material(movingSide, promotedPiece, attackersquare) - materialTable.material(defendingSide, capturedPiece, to) + gain[d - 1];
					fromBB = squaresType(attackersquare);
				}
				else
					break;
			}
			if (d > 0)
			{
				while (--d)
				{
					const scoreType scorePrev{ gain[d - 1].makeSubjective(movingSide) };
					const scoreType scoreNow{ gain[d].makeSubjective(movingSide) };
					if (scoreNow > scorePrev)
						gain[d - 1] = gain[d];
					movingSide = movingSide.previous();
				}
			}
			return gain[0];
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static objectiveType staticMoveScore_Implementation(const boardType& position, const movebitsType move, const materialTableType& materialTable) noexcept
		{
			constexpr const playerType movingSide{ static_cast<playerType>(PLAYER) };
			constexpr const playerType defendingSide{ movingSide.next() };
			const squareType to{ motorType::move().toSquare(position, move) };
			const squareType from{ motorType::move().fromSquare(position, move) };
			PYGMALION_ASSERT(movingSide == position.getPlayer(from));
			pieceType attackingPiece{ position.getPiece(from) };
			PYGMALION_ASSERT(attackingPiece.isValid());
			pieceType promotedPiece{ attackingPiece };
			if (motorType::move().isPromotion(move))
				promotedPiece = motorType::move().promotedPiece(move);
			objectiveType gain;
			gain = materialTable.material(movingSide, promotedPiece, to) - materialTable.material(movingSide, attackingPiece, from);
			if (motorType::move().isCapture(move))
			{
				const squareType captureSquare{ motorType::move().captureSquare(position, move) };
				const pieceType capPiece = position.getPiece(captureSquare);
				gain -= materialTable.material(defendingSide, capPiece, captureSquare);
			}
			return gain;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static objectiveType staticExchangeScore_Implementation(const boardType& position, const movebitsType move, const materialTableType& materialTable) noexcept
		{
			return static_cast<objectiveType>(evaluator::template staticExchange<PLAYER>(move, position, materialTable));
		}
	};
}