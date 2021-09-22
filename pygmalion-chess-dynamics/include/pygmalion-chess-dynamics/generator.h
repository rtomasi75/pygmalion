namespace pygmalion::chess
{
	//#define FASTPAWNS

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
			mutable bool m_IsControlValid{ false };
		public:
			void control(squaresType& white, squaresType& black) const;
			squareType kingSquare(const playerType player) const noexcept
			{
				if (!m_IsKingSquareValid[player])
				{
					m_KingSquare[player] = position().kingSquare(player);
					m_IsKingSquareValid[player] = true;
				}
				return m_KingSquare[player];
			}
			squaresType squaresTargetedByPlayer(const playerType player) const
			{
				if (!m_SquaresTargetedByPlayerValid[player])
				{
					m_SquaresTargetedByPlayer[player] = generatorType::squaresTargetedByPlayer(*this, player);
					m_SquaresTargetedByPlayerValid[player] = true;
				}
				return m_SquaresTargetedByPlayer[player];
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
			stack(boardType& position, historyType& history, const playerType oldPlayer) noexcept :
				pygmalion::generator<descriptor_dynamics, generator>::stack(position, history, oldPlayer)
			{
			}
			~stack() noexcept = default;
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
		constexpr static const movebitsType m_NullMove{ motorType::move().createNull() };
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
		static void control(const generatorType::stackType& stack, squaresType& white, squaresType& black) noexcept
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
		static bool isAttacked(const boardType& position, const squareType square, const playerType attacker) noexcept
		{
			assert(square.isValid());
			const squaresType allowed{ ~position.totalOccupancy() };
			if (knightAttacks(square, allowed) & position.pieceOccupancy(knight) & position.playerOccupancy(attacker))
				return true;
			if (kingAttacks(square, allowed) & position.pieceOccupancy(king) & position.playerOccupancy(attacker))
				return true;
			const squaresType piecemap{ squaresType(square) };
			if (attacker == whitePlayer)
			{
				const squaresType pawns{ position.pieceOccupancy(pawn) & position.playerOccupancy(whitePlayer) };
				const squaresType temppawns{ pawns.up() };
				const squaresType pawnAttacks{ temppawns.left() | temppawns.right() };
				if (pawnAttacks & piecemap)
					return true;
			}
			else
			{
				const squaresType pawns{ position.pieceOccupancy(pawn) & position.playerOccupancy(blackPlayer) };
				const squaresType temppawns{ pawns.down() };
				const squaresType pawnAttacks{ temppawns.left() | temppawns.right() };
				if (pawnAttacks & piecemap)
					return true;
			}
			const squaresType slidersDiag{ (position.pieceOccupancy(queen) | position.pieceOccupancy(bishop)) & position.playerOccupancy(attacker) };
			if (sliderAttacksDiag(square, allowed) & slidersDiag)
				return true;
			const squaresType slidersHV{ (position.pieceOccupancy(queen) | position.pieceOccupancy(rook)) & position.playerOccupancy(attacker) };
			if (sliderAttacksHV(square, allowed) & slidersHV)
				return true;
			return false;
		}
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
			if (attackingPlayer == whitePlayer)
				attacked |= pawns.upLeft() | pawns.upRight();
			else
				attacked |= pawns.downLeft() | pawns.downRight();
			return attacked;
		}
		static squaresType squaresTargetedByPlayer(const stackType& stack, const playerType attackingPlayer) noexcept
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
		static void generateKingMoves(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType forbidden{ stack.squaresAttackedByPlayer(stack.nextPlayer()) };
			const squaresType allowed{ ~forbidden };
			const squareType from{ stack.kingSquare(stack.movingPlayer()) };
			const squaresType destinations{ allowed & kingTargets(from, ~stack.position().totalOccupancy()) };
			for (const squareType to : destinations)
				moves.add(motorType::move().createQuiet(from, to));
		}
		static void generateKingCaptures(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType forbidden{ stack.squaresAttackedByPlayer(stack.nextPlayer()) };
			const squaresType allowed{ ~forbidden };
			const squareType from{ stack.kingSquare(stack.movingPlayer()) };
			const squaresType destinations{ allowed & kingAttacks(from, ~stack.position().totalOccupancy()) & stack.position().playerOccupancy(stack.nextPlayer()) };
			for (const squareType to : destinations)
				moves.add(motorType::move().createCapture(from, to));
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
		typedef void moveGenFunction(const stackType& stack, movelistType& moves);
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
		constexpr static void generatePawnPushesWhite(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType whitePawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
			for (const squareType to : movegenPawnPushWhite.targets(whitePawns, ~stack.position().totalOccupancy()))
				moves.add(motorType::move().createQuiet(to.down(), to));
		}
		constexpr static void generatePawnPushesBlack(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType blackPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
			for (const squareType to : movegenPawnPushBlack.targets(blackPawns, ~stack.position().totalOccupancy()))
				moves.add(motorType::move().createQuiet(to.up(), to));
		}
		constexpr static inline moveGenFunction* m_PawnPushes[]{ &generatePawnPushesWhite, &generatePawnPushesBlack };
		constexpr static void generatePawnPushes(const stackType& stack, movelistType& moves) noexcept
		{
			(*(m_PawnPushes[stack.position().movingPlayer()]))(stack, moves);
		}
		constexpr static void generatePawnPromotionsWhite(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType whitePawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
			for (const squareType to : movegenPawnPromotionWhite.targets(whitePawns, ~stack.position().totalOccupancy()))
			{
				const squareType from{ to.down() };
				moves.add(motorType::move().createPromotionQueen(from, to));
				moves.add(motorType::move().createPromotionKnight(from, to));
				moves.add(motorType::move().createPromotionRook(from, to));
				moves.add(motorType::move().createPromotionBishop(from, to));
			}
		}
		constexpr static void generatePawnPromotionsBlack(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType blackPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
			for (const squareType to : movegenPawnPromotionBlack.targets(blackPawns, ~stack.position().totalOccupancy()))
			{
				const squareType from{ to.up() };
				moves.add(motorType::move().createPromotionQueen(from, to));
				moves.add(motorType::move().createPromotionKnight(from, to));
				moves.add(motorType::move().createPromotionRook(from, to));
				moves.add(motorType::move().createPromotionBishop(from, to));
			}
		}
		constexpr static inline moveGenFunction* m_PawnPromotions[]{ &generatePawnPromotionsWhite, &generatePawnPromotionsBlack };
		constexpr static void generatePawnPromotions(const stackType& stack, movelistType& moves) noexcept
		{
			(*(m_PawnPromotions[stack.position().movingPlayer()]))(stack, moves);
		}
		constexpr static void generatePawnCapturesWhite(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType whitePawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
			for (const squareType to : movegenPawnCaptureWhite.attacks(whitePawns, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(blackPlayer))
			{
				if (to.file() > fileA)
				{
					const squareType fromLeft{ to.downLeft() };
					if (whitePawns[fromLeft])
						moves.add(motorType::move().createCapture(fromLeft, to));
				}
				if (to.file() < fileH)
				{
					const squareType fromRight{ to.downRight() };
					if (whitePawns[fromRight])
						moves.add(motorType::move().createCapture(fromRight, to));
				}
			}
		}
		constexpr static void generatePawnCapturesBlack(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType blackPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
			for (const squareType to : movegenPawnCaptureBlack.attacks(blackPawns, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(whitePlayer))
			{
				if (to.file() > fileA)
				{
					const squareType fromLeft{ to.upLeft() };
					if (blackPawns[fromLeft])
						moves.add(motorType::move().createCapture(fromLeft, to));
				}
				if (to.file() < fileH)
				{
					const squareType fromRight{ to.upRight() };
					if (blackPawns[fromRight])
						moves.add(motorType::move().createCapture(fromRight, to));
				}
			}
		}
		constexpr static inline moveGenFunction* m_PawnCaptures[]{ &generatePawnCapturesWhite, &generatePawnCapturesBlack };
		constexpr static void generatePawnCaptures(const stackType& stack, movelistType& moves) noexcept
		{
			(*(m_PawnCaptures[stack.position().movingPlayer()]))(stack, moves);
		}
		constexpr static void generatePawnPromoCapturesWhite(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType whitePawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
			for (const squareType to : movegenPawnPromoCaptureWhite.attacks(whitePawns, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(blackPlayer))
			{
				if (to.file() > fileA)
				{
					const squareType fromLeft{ to.downLeft() };
					if (whitePawns[fromLeft])
					{
						moves.add(motorType::move().createPromoCaptureQueen(fromLeft, to));
						moves.add(motorType::move().createPromoCaptureKnight(fromLeft, to));
						moves.add(motorType::move().createPromoCaptureRook(fromLeft, to));
						moves.add(motorType::move().createPromoCaptureBishop(fromLeft, to));
					}
				}
				if (to.file() < fileH)
				{
					const squareType fromRight{ to.downRight() };
					if (whitePawns[fromRight])
					{
						moves.add(motorType::move().createPromoCaptureQueen(fromRight, to));
						moves.add(motorType::move().createPromoCaptureKnight(fromRight, to));
						moves.add(motorType::move().createPromoCaptureRook(fromRight, to));
						moves.add(motorType::move().createPromoCaptureBishop(fromRight, to));
					}
				}
			}
		}
		constexpr static void generatePawnPromoCapturesBlack(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType blackPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
			for (const squareType to : movegenPawnPromoCaptureBlack.attacks(blackPawns, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(whitePlayer))
			{
				if (to.file() > fileA)
				{
					const squareType fromLeft{ to.upLeft() };
					if (blackPawns[fromLeft])
					{
						moves.add(motorType::move().createPromoCaptureQueen(fromLeft, to));
						moves.add(motorType::move().createPromoCaptureKnight(fromLeft, to));
						moves.add(motorType::move().createPromoCaptureRook(fromLeft, to));
						moves.add(motorType::move().createPromoCaptureBishop(fromLeft, to));
					}
				}
				if (to.file() < fileH)
				{
					const squareType fromRight{ to.upRight() };
					if (blackPawns[fromRight])
					{
						moves.add(motorType::move().createPromoCaptureQueen(fromRight, to));
						moves.add(motorType::move().createPromoCaptureKnight(fromRight, to));
						moves.add(motorType::move().createPromoCaptureRook(fromRight, to));
						moves.add(motorType::move().createPromoCaptureBishop(fromRight, to));
					}
				}
			}
		}
		constexpr static inline moveGenFunction* m_PawnPromoCaptures[]{ &generatePawnPromoCapturesWhite, &generatePawnPromoCapturesBlack };
		constexpr static void generatePawnPromoCaptures(const stackType& stack, movelistType& moves) noexcept
		{
			(*(m_PawnPromoCaptures[stack.position().movingPlayer()]))(stack, moves);
		}
		constexpr static void generatePawnDoublePushesWhite(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType whitePawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
			for (const squareType to : movegenPawnDoublePushWhite.targets(whitePawns, ~stack.position().totalOccupancy()))
				moves.add(motorType::move().createDoublePush(to.file()));
		}
		constexpr static void generatePawnDoublePushesBlack(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType blackPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
			for (const squareType to : movegenPawnDoublePushBlack.targets(blackPawns, ~stack.position().totalOccupancy()))
				moves.add(motorType::move().createDoublePush(to.file()));
		}
		constexpr static inline moveGenFunction* m_PawnDoublePushes[]{ &generatePawnDoublePushesWhite, &generatePawnDoublePushesBlack };
		constexpr static void generatePawnDoublePushes(const stackType& stack, movelistType& moves) noexcept
		{
			(*(m_PawnDoublePushes[stack.position().movingPlayer()]))(stack, moves);
		}
		constexpr static inline moveGenFunction* m_Moves[]
		{
			&generateKnightMoves,
			&generatePawnPushes,
			&generatePawnDoublePushes,
			&generateKnightCaptures,
			&generatePawnCaptures,
			&generatePawnEnPassant,
			&generateSliderMovesHV,
			&generateSliderMovesDiag,
			&generateSliderCapturesHV,
			&generateSliderCapturesDiag,
			&generateKingMoves,
			&generateKingCaptures,
			&generateCastles,
			&generatePawnPromotions,
			&generatePawnPromoCaptures
		};
		constexpr static inline moveGenFunction* m_TacticalMoves[]
		{
			&generateKnightCaptures,
			&generatePawnCaptures,
			&generatePawnEnPassant,
			&generateSliderCapturesHV,
			&generateSliderCapturesDiag,
			&generateKingCaptures,
			&generatePawnPromoCaptures
		};
	public:
		static squaresType attackers(const boardType& position, const squareType square) noexcept
		{
			assert(square.isValid());
			squaresType attackers{ squaresType::none() };
			const squaresType allowed{ ~position.totalOccupancy() };
			attackers |= knightAttacks(square, allowed) & position.pieceOccupancy(knight);
			attackers |= kingAttacks(square, allowed) & position.pieceOccupancy(king);
			const squaresType whitepawns{ position.pieceOccupancy(pawn) & position.playerOccupancy(whitePlayer) };
			const squaresType blackpawns{ position.pieceOccupancy(pawn) & position.playerOccupancy(blackPlayer) };
			const squaresType piecemap{ squaresType(square) };
			const squaresType temppiecemap1{ piecemap.up() };
			const squaresType temppiecemap2{ piecemap.down() };
			attackers |= (temppiecemap1.left() | temppiecemap1.right()) & blackpawns;
			attackers |= (temppiecemap2.left() | temppiecemap2.right()) & whitepawns;
			const squaresType slidersHV{ position.pieceOccupancy(queen) | position.pieceOccupancy(rook) };
			const squaresType slidersDiag{ position.pieceOccupancy(queen) | position.pieceOccupancy(bishop) };
			attackers |= sliderAttacksHV(square, allowed) & slidersHV;
			attackers |= sliderAttacksDiag(square, allowed) & slidersDiag;
			return attackers;
		}
		static squaresType attackers(const boardType& position, const squareType square, const playerType attacker) noexcept
		{
			assert(square.isValid());
			squaresType attackers{ squaresType::none() };
			const squaresType allowed{ ~position.totalOccupancy() };
			attackers |= knightAttacks(square, allowed) & position.pieceOccupancy(knight);
			attackers |= kingAttacks(square, allowed) & position.pieceOccupancy(king);
			const squaresType pawns{ position.pieceOccupancy(pawn) };
			const squaresType piecemap{ squaresType(square) };
			if (attacker == whitePlayer)
			{
				const squaresType temppiecemap{ piecemap.down() };
				attackers |= (temppiecemap.left() | temppiecemap.right()) & pawns;
			}
			else
			{
				const squaresType temppiecemap{ piecemap.up() };
				attackers |= (temppiecemap.left() | temppiecemap.right()) & pawns;
			}
			const squaresType slidersHV{ (position.pieceOccupancy(queen) | position.pieceOccupancy(rook)) };
			const squaresType slidersDiag{ (position.pieceOccupancy(queen) | position.pieceOccupancy(bishop)) };
			attackers |= sliderAttacksHV(square, allowed) & slidersHV;
			attackers |= sliderAttacksDiag(square, allowed) & slidersDiag;
			return attackers & position.playerOccupancy(attacker);
		}
		constexpr static size_t countMoveBuckets_Implementation() noexcept
		{
			if constexpr (usePieceType)
				return countSquares * countPieces;
			else
				return countSquares * countSquares;
		}
		constexpr static size_t moveBucket_Implementation(const boardType& position, const movebitsType& mv) noexcept
		{
			const squareType to{ motorType::move().toSquare(position, mv) };
			const squareType from{ motorType::move().fromSquare(position,mv) };
			if constexpr (usePieceType)
			{
				const pieceType pc{ position.getPiece(from) };
				return static_cast<size_t>(pc) * countSquares + static_cast<size_t>(to);
			}
			else
			{
				return static_cast<size_t>(from) * countSquares + static_cast<size_t>(to);
			}
		}
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commandsImplementation() noexcept;
		static bool isMoveLegal_Implementation(const stackType& stack, const movebitsType& moveBits) noexcept
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
		static bool isMoveTactical_Implementation(const stackType& stack, const movebitsType& moveBits) noexcept
		{
			return motorType::move().isCapture(moveBits);
		}
		static bool isGeneratedMoveLegal_Implementation(const stackType& stack, const movebitsType& moveBits) noexcept
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
			if (isKingMove || stack.isPositionCritical())
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
		constexpr static void generateMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			(*(m_Moves[static_cast<size_t>(currentPass)]))(stack, moves);
		}
		constexpr static void generateTacticalMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			(*(m_TacticalMoves[static_cast<size_t>(currentPass)]))(stack, moves);
		}
		static void movesFromSquare(const stackType& stack, const squareType square, squaresType& moves, squaresType& captures, const size_t depth) noexcept
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
		static std::string moveToString_Implementation(const stackType& stack, const movebitsType mv, const size_t depth) noexcept;
		static std::string passToString_Implementation(const passType pass) noexcept;
		static std::string tacticalPassToString_Implementation(const passType tacticalPass) noexcept;
		static squaresType attacksXrayDiag(const squareType square, const squaresType& occ, const squaresType& xrays) noexcept
		{
			assert(square.isValid());
			const squaresType attmask{ movegenSlidersDiag.attacks(square, ~occ) };
			return attmask & xrays;
		}
		static squaresType attacksXrayHV(const squareType square, const squaresType& occ, const squaresType& xrays) noexcept
		{
			assert(square.isValid());
			const squaresType attmask{ movegenSlidersHV.attacks(square, ~occ) };
			return attmask & xrays;
		}
		constexpr static bool hasNullMove_Implementation() noexcept
		{
			return true;
		}
		constexpr static movebitsType nullMove_Implementation() noexcept
		{
			return m_NullMove;
		}
		static bool isMoveCritical_Implementation(const stackType& stack, const movebitsType& moveBits) noexcept
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
		static bool isPositionCritical_Implementation(const stackType& stack) noexcept
		{
			return generatorType::isAttacked(stack.position(), stack.kingSquare(stack.movingPlayer()), stack.nextPlayer());
		}
	};
}