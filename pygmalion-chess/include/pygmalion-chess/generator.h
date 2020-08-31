namespace pygmalion::chess
{
	class generator :
		public pygmalion::generator<descriptor_generator, generator>
	{
	private:
		static const inline generatorTables<descriptor_generator> m_Tables;
	public:
		class stack :
			public pygmalion::generator<descriptor_generator, generator>::stack
		{
		private:
			mutable std::array<bool,countPlayers> m_IsKingSquareValid{ make_array_n<countPlayers,bool>(false) };
			mutable std::array<squareType, countPlayers> m_KingSquare{ make_array_n<countPlayers,squareType>(squareType::invalid) };
		public:
			constexpr squareType kingSquare(const playerType player) const noexcept
			{
				if (!m_IsKingSquareValid[player])
				{
					const bool ok{ (position().playerOccupancy(player) & position().pieceOccupancy(king)).firstSetBit(m_KingSquare[player]) };
					assert(ok);
					m_IsKingSquareValid[player] = true;
				}
				return m_KingSquare[player];
			}
			stack(const stack& parent, const moveType mv) noexcept :
				pygmalion::generator<descriptor_generator, generator>::stack(parent,mv)
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
		static const generatorTables<descriptor_generator>& tables() noexcept
		{
			return m_Tables;
		}

		static squaresType kingMoveMap(const squareType square)
		{
			return m_Tables.kingMoveMap(square);
		}

		static std::string name_Implementation() noexcept
		{
			return "chess ver. 1.0";
		}
		static bool isMoveLegal_Implementation(const stackType& stack, const moveType& move) noexcept
		{
			const playerType movingPlayer{ stack.movingPlayer() };
			const playerType otherPlayer{ movingPlayer.next() };
			const squareType to{ move.square(mechanicsType::square_to)};

			// are we illegally capturing the other king?
			const squareType otherking{ stack.kingSquare(otherPlayer) };
			if (mechanicsType::isCapture(move) && (otherking == to))
				return false;

			// No. Let's see where our king lives after the move as been made then...
			const squareType from{ move.square(mechanicsType::square_from) };
			const squareType kingsquareOld{ stack.kingSquare(movingPlayer) };
			const squareType kingsquare{ (from == kingsquareOld) ? to : kingsquareOld };

			// Does he live on a square that is guarded by the other king?
			const squaresType attackedByOtherKing{ kingMoveMap(otherking) };
			if (attackedByOtherKing[kingsquare])
				return false;

			// We need the enemy occupancy bitboard as it would be after the move...
			const squaresType otherOccupancy{ position.playerOccupancy(otherPlayer) };
			const squaresType otherDelta{ mechanicsType::isCapture ? (mechanicsType::isCaptureEnPassant(move) ? squaresType::setMask(squareType::fromRankFile(from.rank(), to.file())) : squaresType::setMask(to)) : squaresType::empty() };
			const squaresType occOther{ otherOccupancy ^ otherDelta };

			// Does he live on a square that is guarded by an enemy knight?
			const squaresType otherKnights{ ((position.pieceOccupancy(knight) & otherOccupancy) ^ otherDelta) & occOther };
			const squaresType attackedByOtherKnights{ boardType::upUpLeft(otherKnights) | boardType::upUpRight(otherKnights) | boardType::downDownLeft(otherKnights) | boardType::downDownRight(otherKnights) | boardType::upLeftLeft(otherKnights) | boardType::downLeftLeft(otherKnights) | boardType::upRightRight(otherKnights) | boardType::downRightRight(otherKnights) };
			if (attackedByOtherKnights[kingsquare])
				return false;

			// Does he live on a square that is guarded by an enemy pawn?
			const squaresType otherPawns{ ((position.pieceOccupancy(pawn) & otherOccupancy) ^ otherDelta) & occOther };
			const squaresType attackedByOtherPawns{ (otherPlayer == whitePlayer) ? (boardType::upLeft(otherPawns) | boardType::upRight(otherPawns)) : (boardType::downLeft(otherPawns) | boardType::downRight(otherPawns)) };
			if (attackedByOtherPawns[kingsquare])
				return false;

			// We need the total occupancy bitboard as it would be after the move...
			const squaresType movingOccupancy{ position.playerOccupancy(movingPlayer) };
			const squaresType moveMask{ squaresType::setMask(from) ^ squaresType::setMask(to) };
			const squaresType movingDelta{ mechanicsType::isCastleQueenside(move) ? (mechanicsType::isCastleKingside(move) ? (moveMask ^ squaresType::setMask(squareType::fromRankFile(from.rank(), to.file() - 1)) ^ squaresType::setMask(squareType::fromRankFile(from.rank(),fileH))) : (moveMask ^ squaresType::setMask(squareType::fromRankFile(from.rank(),to.file() + 1)) ^ squaresType::setMask(squareType::fromRankFile(from.rank(),fileA)))) : moveMask };
			const squaresType occMoving{ movingOccupancy ^ movingDelta };
			const squaresType occTotal{ occOther | occMoving };

			// Is he attacked horizontally by sliding pieces?
			const squaresType queens{ position.pieceOccupancy(queen) };
			const squaresType otherSlidersHV = occOther & (position.pieceOccupancy(rook) | queens);
			if (m_Tables.sliderAttacks(false, kingsquare, occTotal, otherSlidersHV))
				return false;

			// Is he attacked diagonally by sliding pieces?
			const squaresType otherSlidersDiag = occOther & (position.pieceOccupancy(bishop) | queens);
			if (m_Tables.sliderAttacks(true, kingsquare, occTotal, otherSlidersDiag))
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