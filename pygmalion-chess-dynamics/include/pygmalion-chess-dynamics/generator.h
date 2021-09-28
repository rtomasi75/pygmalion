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
	private:
		constexpr static inline const rays m_Rays{ rays() };
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
			if (p == whitePlayer)
				return movegenPawnPushWhite.targets(sq, allowed);
			else
				return movegenPawnPushBlack.targets(sq, allowed);
		}
		constexpr static squaresType pawnCaptureTargets(const squareType sq, const playerType p, const squaresType& allowed) noexcept
		{
			if (p == whitePlayer)
				return movegenPawnCaptureWhite.attacks(sq, allowed);
			else
				return movegenPawnCaptureBlack.attacks(sq, allowed);
		}
		constexpr static squaresType pawnCaptureTargets(const squaresType squares, const playerType p, const squaresType& allowed) noexcept
		{
			if (p == whitePlayer)
				return movegenPawnCaptureWhite.attacks(squares, allowed);
			else
				return movegenPawnCaptureBlack.attacks(squares, allowed);
		}
		constexpr static squaresType pawnDoublePushTargets(const squareType sq, const playerType p, const squaresType& allowed) noexcept
		{
			if (p == whitePlayer)
				return movegenPawnDoublePushWhite.targets(sq, allowed);
			else
				return movegenPawnDoublePushBlack.targets(sq, allowed);
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
				const squaresType attacks{ generatorType::movegenKnight.attacks(sq,squaresType::all()) };
				for (squareType attack : attacks)
				{
					attacksWhite[attack]++;
					touched |= attack;
				}
			}
			for (squareType sq : blackKnights)
			{
				const squaresType attacks{ generatorType::movegenKnight.attacks(sq,squaresType::all()) };
				for (squareType attack : attacks)
				{
					attacksBlack[attack]++;
					touched |= attack;
				}
			}
			for (squareType sq : whiteBishops)
			{
				const squaresType attacks{ generatorType::movegenSlidersDiag.attacks(sq,~stack.position().totalOccupancy()) };
				for (squareType attack : attacks)
				{
					attacksWhite[attack]++;
					touched |= attack;
				}
			}
			for (squareType sq : blackBishops)
			{
				const squaresType attacks{ generatorType::movegenSlidersDiag.attacks(sq,~stack.position().totalOccupancy()) };
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
				const squaresType attacks{ generatorType::movegenSlidersHV.attacks(sq,~stack.position().totalOccupancy()) };
				for (squareType attack : attacks)
				{
					attacksWhite2[attack]++;
					touched |= attack;
				}
			}
			for (squareType sq : blackRooks)
			{
				const squaresType attacks{ generatorType::movegenSlidersHV.attacks(sq,~stack.position().totalOccupancy()) };
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
				const squaresType attacks{ generatorType::movegenSlidersHV.attacks(sq,~stack.position().totalOccupancy()) | generatorType::movegenSlidersHV.attacks(sq,~stack.position().totalOccupancy()) };
				for (squareType attack : attacks)
				{
					attacksWhite3[attack]++;
					touched |= attack;
				}
			}
			for (squareType sq : blackQueens)
			{
				const squaresType attacks{ generatorType::movegenSlidersHV.attacks(sq,~stack.position().totalOccupancy()) | generatorType::movegenSlidersHV.attacks(sq,~stack.position().totalOccupancy()) };
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
			const squaresType whiteKingAttacks{ generatorType::movegenKing.attacks(stack.kingSquare(whitePlayer),squaresType::all()) };
			const squaresType blackKingAttacks{ generatorType::movegenKing.attacks(stack.kingSquare(blackPlayer),squaresType::all()) };
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
			if (movegenKnight.attacks(square, allowed) & position.pieceOccupancy(knight) & position.playerOccupancy(attacker))
				return true;
			if (movegenKing.attacks(square, allowed) & position.pieceOccupancy(king) & position.playerOccupancy(attacker))
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
			if (movegenSlidersDiag.attacks(square, allowed) & slidersDiag)
				return true;
			const squaresType slidersHV{ (position.pieceOccupancy(queen) | position.pieceOccupancy(rook)) & position.playerOccupancy(attacker) };
			if (movegenSlidersHV.attacks(square, allowed) & slidersHV)
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
			squaresType attacked{ movegenKnight.attacks(knights, notBlockers) };
			attacked |= movegenKing.attacks(stack.kingSquare(attackingPlayer), notBlockers);
			const squaresType queens{ position.pieceOccupancy(queen) };
			const squaresType slidersHV{ (position.pieceOccupancy(rook) | queens) & attackerOccupancy };
			const squaresType slidersDiag{ (position.pieceOccupancy(bishop) | queens) & attackerOccupancy };
			attacked |= movegenSlidersHV.attacks(slidersHV, notBlockers);
			attacked |= movegenSlidersDiag.attacks(slidersDiag, notBlockers);;
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
			squaresType attacked{ movegenKnight.targets(knights, notBlockers) };
			attacked |= movegenKing.targets(stack.kingSquare(attackingPlayer), notBlockers);
			const squaresType queens{ position.pieceOccupancy(queen) };
			const squaresType slidersHV{ (position.pieceOccupancy(rook) | queens) & attackerOccupancy };
			const squaresType slidersDiag{ (position.pieceOccupancy(bishop) | queens) & attackerOccupancy };
			attacked |= movegenSlidersHV.targets(slidersHV, notBlockers);
			attacked |= movegenSlidersDiag.targets(slidersDiag, notBlockers);;
			const squaresType pawns{ position.pieceOccupancy(pawn) & attackerOccupancy };
			if (attackingPlayer == whitePlayer)
				attacked |= pawns.upLeft() | pawns.upRight();
			else
				attacked |= pawns.downLeft() | pawns.downRight();
			return attacked;
		}
		static void generateKingMoves(const stackType& stack, movelistType& moves) noexcept
		{
			const squareType from{ stack.kingSquare(stack.movingPlayer()) };
			const squaresType destinations{ movegenKing.targets(from, ~stack.position().totalOccupancy()) };
			for (const squareType to : destinations)
				moves.add(motorType::move().createQuiet(from, to));
		}
		static void generateKingCaptures(const stackType& stack, movelistType& moves) noexcept
		{
			const squareType from{ stack.kingSquare(stack.movingPlayer()) };
			const squaresType destinations{ movegenKing.attacks(from, ~stack.position().totalOccupancy()) & stack.position().playerOccupancy(stack.nextPlayer()) };
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
						moves.add(motorType::move().createKingsideCastle());
				}
				if (stack.position().checkCastleRightQueensideWhite())
				{
					if (!(stack.position().totalOccupancy() & queensideCastleInterestWhite))
						moves.add(motorType::move().createQueensideCastle());
				}
			}
			else
			{
				if (stack.position().checkCastleRightKingsideBlack())
				{
					if (!(stack.position().totalOccupancy() & kingsideCastleInterestBlack))
						moves.add(motorType::move().createKingsideCastle());
				}
				if (stack.position().checkCastleRightQueensideBlack())
				{
					if (!(stack.position().totalOccupancy() & queensideCastleInterestBlack))
						moves.add(motorType::move().createQueensideCastle());
				}
			}
		}
		static void generatePawnEnPassant(const stackType& stack, movelistType& moves) noexcept
		{
			const uint_t<8, false> epFlags{ stack.position().flags().extractRange<4,11>() };
			if (epFlags)
			{
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
		}
		typedef void moveGenFunction(const stackType& stack, movelistType& moves);
		constexpr static void generateKnightMoves(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : stack.position().pieceOccupancy(knight)& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : movegenKnight.targets(from, ~stack.position().totalOccupancy()))
					moves.add(motorType::move().createQuiet(from, to));
			}
		}
		constexpr static void generateSliderMovesHV(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen))& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : movegenSlidersHV.targets(from, ~stack.position().totalOccupancy()))
					moves.add(motorType::move().createQuiet(from, to));
			}
		}
		constexpr static void generateSliderMovesDiag(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : (stack.position().pieceOccupancy(bishop) | stack.position().pieceOccupancy(queen))& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : movegenSlidersDiag.targets(from, ~stack.position().totalOccupancy()))
					moves.add(motorType::move().createQuiet(from, to));
			}
		}
		constexpr static void generateSliderCapturesHV(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen))& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : movegenSlidersHV.attacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(stack.nextPlayer()))
					moves.add(motorType::move().createCapture(from, to));
			}
		}
		constexpr static void generateSliderCapturesDiag(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : (stack.position().pieceOccupancy(bishop) | stack.position().pieceOccupancy(queen))& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : movegenSlidersDiag.attacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(stack.nextPlayer()))
					moves.add(motorType::move().createCapture(from, to));
			}
		}
		constexpr static void generateKnightCaptures(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : stack.position().pieceOccupancy(knight)& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : movegenKnight.attacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(stack.nextPlayer()))
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
		constexpr static void generatePawnPushes(const stackType& stack, movelistType& moves) noexcept
		{
			if (stack.position().movingPlayer() == whitePlayer)
				generatePawnPushesWhite(stack, moves);
			else
				generatePawnPushesBlack(stack, moves);
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
		constexpr static void generatePawnPromotions(const stackType& stack, movelistType& moves) noexcept
		{
			if (stack.position().movingPlayer() == whitePlayer)
				generatePawnPromotionsWhite(stack, moves);
			else
				generatePawnPromotionsBlack(stack, moves);
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
		constexpr static void generatePawnCaptures(const stackType& stack, movelistType& moves) noexcept
		{
			if (stack.position().movingPlayer() == whitePlayer)
				generatePawnCapturesWhite(stack, moves);
			else
				generatePawnCapturesBlack(stack, moves);
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
		constexpr static void generatePawnPromoCaptures(const stackType& stack, movelistType& moves) noexcept
		{
			if (stack.position().movingPlayer() == whitePlayer)
				generatePawnPromoCapturesWhite(stack, moves);
			else
				generatePawnPromoCapturesBlack(stack, moves);
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
		constexpr static void generatePawnDoublePushes(const stackType& stack, movelistType& moves) noexcept
		{
			if (stack.position().movingPlayer() == whitePlayer)
				generatePawnDoublePushesWhite(stack, moves);
			else
				generatePawnDoublePushesBlack(stack, moves);
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
		static void generateCriticalKnightMoves(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType ownKnights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.movingPlayer()) };
			const squareType otherKing{ stack.kingSquare(stack.nextPlayer()) };
			const squaresType criticalSquares{ movegenKnight.inverseAttacks(otherKing, squaresType::all()) };
			const squaresType criticalTargets{ criticalSquares & ~stack.position().totalOccupancy() };
			const squaresType criticalCaptures{ criticalSquares & stack.position().playerOccupancy(stack.nextPlayer()) };
			for (const auto to : criticalTargets)
			{
				const squaresType origins{ movegenKnight.inverseTargets(to,squaresType::all()) };
				const squaresType movers{ origins & ownKnights };
				for (const auto from : movers)
					moves.add(motorType::move().createQuiet(from, to));
			}
			for (const auto to : criticalCaptures)
			{
				const squaresType origins{ movegenKnight.inverseAttacks(to,squaresType::all()) };
				const squaresType movers{ origins & ownKnights };
				for (const auto from : movers)
					moves.add(motorType::move().createCapture(from, to));
			}
			if (stack.movingPlayer() == whitePlayer)
			{
				const squaresType criticalPromotionSquares{ criticalSquares & rank8 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType criticalPromoCaptures{ criticalPromotionSquares & stack.position().playerOccupancy(blackPlayer) };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionWhite.inverseTargets(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					for (const auto from : movers)
						moves.add(motorType::move().createPromotionKnight(from, to));
				}
				for (const auto to : criticalPromoCaptures)
				{
					const squaresType origins{ movegenPawnPromoCaptureWhite.inverseAttacks(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					for (const auto from : movers)
						moves.add(motorType::move().createPromoCaptureKnight(from, to));
				}
			}
			else
			{
				const squaresType criticalPromotionSquares{ criticalSquares & rank1 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType criticalPromoCaptures{ criticalPromotionSquares & stack.position().playerOccupancy(whitePlayer) };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionBlack.inverseTargets(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					for (const auto from : movers)
						moves.add(motorType::move().createPromotionKnight(from, to));
				}
				for (const auto to : criticalPromoCaptures)
				{
					const squaresType origins{ movegenPawnPromoCaptureWhite.inverseAttacks(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					for (const auto from : movers)
						moves.add(motorType::move().createPromoCaptureKnight(from, to));
				}
			}
		}
		static void generateCriticalPawnMovesWhite(const stackType& stack, movelistType& moves) noexcept
		{
			const squareType otherKing{ stack.kingSquare(blackPlayer) };
			const rankType otherKingRank{ otherKing.rank() };
			const squaresType unoccupied{ ~stack.position().totalOccupancy() };
			const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
			constexpr const squaresType notRank1{ ~rank1 };
			const squaresType tempSquare{ squaresType(otherKing).down() & notRank1 };
			const squaresType criticalSquares{ tempSquare.left() | tempSquare.right() };
			const squaresType criticalTargets{ criticalSquares & unoccupied };
			const squaresType criticalCaptures{ criticalSquares & stack.position().playerOccupancy(blackPlayer) };
			for (const auto to : criticalTargets)
			{
				const squaresType origins{ squaresType(to).down() & notRank1 };
				const squaresType movers{ origins & ownPawns };
				for (const auto from : movers)
					moves.add(motorType::move().createQuiet(from, to));
				const squaresType pushovers{ origins & unoccupied & rank3 };
				for (const auto pushover : pushovers)
				{
					const squaresType doublePushOrigins{ squaresType(pushover.down()) };
					const squaresType doublePushers{ doublePushOrigins & ownPawns };
					for (const auto from : doublePushers)
						moves.add(motorType::move().createDoublePush(to.file()));
				}
				const rankType toRank{ to.rank() };
				if (toRank == rank6)
				{
					const fileType toFile{ to.file() };
					if (stack.position().checkEnPassantFile(toFile))
					{
						if (toFile > fileA)
						{
							const fileType fromFile{ static_cast<fileType>(toFile - 1) };
							const squareType from{ fromFile & rank5 };
							if (ownPawns[from])
								moves.add(motorType::move().createEnPassant(fromFile, toFile));
						}
						if (toFile < fileH)
						{
							const fileType fromFile{ static_cast<fileType>(toFile + 1) };
							const squareType from{ fromFile & rank5 };
							if (ownPawns[from])
								moves.add(motorType::move().createEnPassant(fromFile, toFile));
						}
					}
				}
			}
			for (const auto to : criticalCaptures)
			{
				const squaresType tempOrigin{ squaresType(to).down() & notRank1 };
				const squaresType origins{ tempOrigin.left() | tempOrigin.right() };
				const squaresType movers{ origins & ownPawns };
				for (const auto from : movers)
					moves.add(motorType::move().createCapture(from, to));
			}
		}
		static void generateCriticalPawnMovesBlack(const stackType& stack, movelistType& moves) noexcept
		{
			const squareType otherKing{ stack.kingSquare(whitePlayer) };
			const rankType otherKingRank{ otherKing.rank() };
			const squaresType unoccupied{ ~stack.position().totalOccupancy() };
			const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
			constexpr const squaresType notRank8{ ~rank8 };
			const squaresType tempSquare{ squaresType(otherKing).up() & notRank8 };
			const squaresType criticalSquares{ tempSquare.left() | tempSquare.right() };
			const squaresType criticalTargets{ criticalSquares & unoccupied };
			const squaresType criticalCaptures{ criticalSquares & stack.position().playerOccupancy(whitePlayer) };
			for (const auto to : criticalTargets)
			{
				const squaresType origins{ squaresType(to).up() & notRank8 };
				const squaresType movers{ origins & ownPawns };
				for (const auto from : movers)
					moves.add(motorType::move().createQuiet(from, to));
				const squaresType pushovers{ origins & unoccupied & rank6 };
				for (const auto pushover : pushovers)
				{
					const squaresType doublePushOrigins{ squaresType(pushover.up()) };
					const squaresType doublePushers{ doublePushOrigins & ownPawns };
					for (const auto from : doublePushers)
						moves.add(motorType::move().createDoublePush(to.file()));
				}
				const rankType toRank{ to.rank() };
				if (toRank == rank3)
				{
					const fileType toFile{ to.file() };
					if (stack.position().checkEnPassantFile(toFile))
					{
						if (toFile > fileA)
						{
							const fileType fromFile{ static_cast<fileType>(toFile - 1) };
							const squareType from{ fromFile & rank4 };
							if (ownPawns[from])
								moves.add(motorType::move().createEnPassant(fromFile, toFile));
						}
						if (toFile < fileH)
						{
							const fileType fromFile{ static_cast<fileType>(toFile + 1) };
							const squareType from{ fromFile & rank4 };
							if (ownPawns[from])
								moves.add(motorType::move().createEnPassant(fromFile, toFile));
						}
					}
				}
			}
			for (const auto to : criticalCaptures)
			{
				const squaresType tempOrigin{ squaresType(to).up() & notRank8 };
				const squaresType origins{ tempOrigin.left() | tempOrigin.right() };
				const squaresType movers{ origins & ownPawns };
				for (const auto from : movers)
					moves.add(motorType::move().createCapture(from, to));
			}
		}
		static void generateCriticalPawnMoves(const stackType& stack, movelistType& moves) noexcept
		{
			if (stack.movingPlayer() == whitePlayer)
				generateCriticalPawnMovesWhite(stack, moves);
			else
				generateCriticalPawnMovesBlack(stack, moves);
		}
		static void generateCriticalSliderMovesHV(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType ownQueens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.movingPlayer()) };
			const squaresType ownRooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.movingPlayer()) };
			const squaresType ownSlidersHV{ ownQueens | ownRooks };
			const squareType otherKing{ stack.kingSquare(stack.nextPlayer()) };
			const squaresType occupied{ stack.position().totalOccupancy() };
			const squaresType unoccupied{ ~occupied };
			const squaresType criticalSquares{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied) };
			const squaresType criticalTargets{ criticalSquares & unoccupied };
			const squaresType criticalCaptures{ criticalSquares & stack.position().playerOccupancy(stack.nextPlayer()) };
			const squaresType discoveryCandidates{ criticalSquares & stack.position().playerOccupancy(stack.movingPlayer()) };
			for (const auto to : criticalTargets)
			{
				const squaresType origins{ movegenSlidersHV.inverseAttacks(to,unoccupied) };
				const squaresType movers{ origins & ownSlidersHV };
				for (const auto from : movers)
					moves.add(motorType::move().createQuiet(from, to));
				const squaresType origins2{ movegenSlidersDiag.inverseAttacks(to,unoccupied) };
				const squaresType movers2{ origins2 & ownQueens };
				for (const auto from : movers2)
					moves.add(motorType::move().createQuiet(from, to));
			}
			for (const auto to : criticalCaptures)
			{
				const squaresType origins{ movegenSlidersHV.inverseAttacks(to,unoccupied) };
				const squaresType movers{ origins & ownSlidersHV };
				for (const auto from : movers)
					moves.add(motorType::move().createCapture(from, to));
				const squaresType origins2{ movegenSlidersDiag.inverseAttacks(to,unoccupied) };
				const squaresType movers2{ origins2 & ownQueens };
				for (const auto from : movers2)
					moves.add(motorType::move().createCapture(from, to));
			}
			for (const auto from : discoveryCandidates)
			{
				const squaresType discovered{ unoccupied | from };
				const squaresType discoveredRays{ movegenSlidersHV.inverseAttacks(otherKing,discovered) };
				const squaresType discoveredAttacks{ discoveredRays & ownSlidersHV };
				if (discoveredAttacks != squaresType::none())
				{
					const pieceType discoveringPiece{ stack.position().getPiece(from) };
					const squareType discoveredSquare{ *discoveredAttacks.begin() };
					const squaresType allowedDestinations{ ~(movegenSlidersHV.attacks(from,discovered) & discoveredRays) };
					switch (discoveringPiece)
					{
					case king:
					{
						const squaresType discoveryTargets{ movegenKing.targets(from,squaresType::all()) & allowedDestinations };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						const squaresType discoveryCaptures{ discoveryTargets & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						for (const auto to : discoveryCaptures)
							moves.add(motorType::move().createCapture(from, to));
						break;
					}
					case knight:
					{
						const squaresType criticalSquares2{ movegenKnight.inverseAttacks(otherKing, squaresType::all()) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ movegenKnight.targets(from,squaresType::all()) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						const squaresType discoveryCaptures{ discoveryTargets & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						for (const auto to : discoveryCaptures)
							moves.add(motorType::move().createCapture(from, to));
						break;
					}
					case rook:
					{
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares };
						const squaresType discoveryTargets{ movegenSlidersHV.attacks(from,discovered) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						const squaresType discoveryCaptures{ discoveryTargets & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						for (const auto to : discoveryCaptures)
							moves.add(motorType::move().createCapture(from, to));
						break;
					}
					case bishop:
					{
						const squaresType criticalSquares2{ movegenSlidersDiag.inverseAttacks(otherKing, unoccupied) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ movegenSlidersDiag.attacks(from,discovered) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						const squaresType discoveryCaptures{ discoveryTargets & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						for (const auto to : discoveryCaptures)
							moves.add(motorType::move().createCapture(from, to));
						break;
					}
					case queen:
					{
						const squaresType criticalSquares2{ criticalSquares | movegenSlidersDiag.inverseAttacks(otherKing, unoccupied) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ (movegenSlidersHV.attacks(from,discovered) | movegenSlidersDiag.attacks(from,discovered)) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						const squaresType discoveryCaptures{ discoveryTargets & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						for (const auto to : discoveryCaptures)
							moves.add(motorType::move().createCapture(from, to));
						break;
					}
					case pawn:
					{
						if (stack.movingPlayer() == whitePlayer)
						{
							constexpr const squaresType notRank1{ ~rank1 };
							const squaresType tempSquare{ squaresType(otherKing).down() & notRank1 };
							const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
							const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
							const squaresType discoveryMoves{ movegenPawnPushWhite.targets(from,squaresType::all()) & allowedDestinations2 & unoccupied };
							const squaresType discoveryCaptures{ movegenPawnCaptureWhite.targets(from,squaresType::all()) & allowedDestinations2 & stack.position().playerOccupancy(stack.nextPlayer()) };
							const squaresType discoveryDoublePushes{ movegenPawnDoublePushWhite.targets(from,discovered) & allowedDestinations2 };
							for (const auto to : discoveryMoves)
								moves.add(motorType::move().createQuiet(from, to));
							for (const auto to : discoveryCaptures)
								moves.add(motorType::move().createCapture(from, to));
							const fileType fromFile{ from.file() };
							for (const auto to : discoveryDoublePushes)
								moves.add(motorType::move().createDoublePush(fromFile));
						}
						else
						{
							constexpr const squaresType notRank8{ ~rank8 };
							const squaresType tempSquare{ squaresType(otherKing).up() & notRank8 };
							const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
							const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
							const squaresType discoveryMoves{ movegenPawnPushBlack.targets(from,squaresType::all()) & allowedDestinations2 & unoccupied };
							const squaresType discoveryCaptures{ movegenPawnCaptureBlack.targets(from,squaresType::all()) & allowedDestinations2 & stack.position().playerOccupancy(stack.nextPlayer()) };
							const squaresType discoveryDoublePushes{ movegenPawnDoublePushBlack.targets(from,discovered) & allowedDestinations2 };
							for (const auto to : discoveryMoves)
								moves.add(motorType::move().createQuiet(from, to));
							for (const auto to : discoveryCaptures)
								moves.add(motorType::move().createCapture(from, to));
							const fileType fromFile{ from.file() };
							for (const auto to : discoveryDoublePushes)
								moves.add(motorType::move().createDoublePush(fromFile));
						}
						break;
					}
					}
				}
			}
			const uint_t<8, false> epFlags{ stack.position().flags().extractRange<4,11>() };
			if (epFlags)
			{
				size_t bit;
				if (stack.position().movingPlayer() == whitePlayer)
				{
					if (epFlags.bitscanForward(bit))
					{
						constexpr const squaresType notRank1{ ~rank1 };
						const squaresType tempSquare{ squaresType(otherKing).down() & notRank1 };
						const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
						const fileType epFile{ static_cast<typename fileType::baseType>(bit) };
						const squareType toSquare{ epFile & rank6 };
						const squaresType allowedDestinations2{ ~criticalSquares2 };
						const squaresType leftFile{ static_cast<squaresType>(epFile).left() };
						const squaresType rightFile{ static_cast<squaresType>(epFile).right() };
						const squaresType rank{ static_cast<squaresType>(rank5) };
						const squaresType fromSquares = (leftFile | rightFile) & rank;
						for (const squareType from : fromSquares & (stack.position().playerOccupancy(whitePlayer)& stack.position().pieceOccupancy(pawn)))
						{
							const movebitsType mv{ motorType::move().createEnPassant(from.file(), epFile) };
							const squareType to{ motorType::move().toSquare(stack.position(),mv) };
							if (allowedDestinations2[to])
							{
								const squaresType ownDelta{ motorType::move().ownOccupancyDelta(stack.position(),mv) };
								const squaresType otherDelta{ motorType::move().otherOccupancyDelta(stack.position(),mv) };
								const squaresType ownOcc{ ownDelta ^ stack.position().playerOccupancy(whitePlayer) };
								const squaresType otherOcc{ otherDelta ^ stack.position().playerOccupancy(blackPlayer) };
								const squaresType unoccupied2{ ~(ownOcc | otherOcc) };
								const squaresType criticalSquares3{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied2) };
								if ((criticalSquares3 & ownSlidersHV) != squaresType::none())
									moves.add(mv);
							}
						}
					}
				}
				else
				{
					if (epFlags.bitscanForward(bit))
					{
						constexpr const squaresType notRank8{ ~rank8 };
						const squaresType tempSquare{ squaresType(otherKing).up() & notRank8 };
						const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
						const fileType epFile{ static_cast<typename fileType::baseType>(bit) };
						const squareType toSquare{ epFile & rank3 };
						const squaresType allowedDestinations2{ ~criticalSquares2 };
						const squaresType leftFile{ static_cast<squaresType>(epFile).left() };
						const squaresType rightFile{ static_cast<squaresType>(epFile).right() };
						const squaresType rank{ static_cast<squaresType>(rank4) };
						const squaresType fromSquares = (leftFile | rightFile) & rank;
						for (const squareType from : fromSquares & (stack.position().playerOccupancy(blackPlayer)& stack.position().pieceOccupancy(pawn)))
						{
							const movebitsType mv{ motorType::move().createEnPassant(from.file(), epFile) };
							const squareType to{ motorType::move().toSquare(stack.position(),mv) };
							if (allowedDestinations2[to])
							{
								const squaresType ownDelta{ motorType::move().ownOccupancyDelta(stack.position(),mv) };
								const squaresType otherDelta{ motorType::move().otherOccupancyDelta(stack.position(),mv) };
								const squaresType ownOcc{ ownDelta ^ stack.position().playerOccupancy(blackPlayer) };
								const squaresType otherOcc{ otherDelta ^ stack.position().playerOccupancy(whitePlayer) };
								const squaresType unoccupied2{ ~(ownOcc | otherOcc) };
								const squaresType criticalSquares3{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied2) };
								if ((criticalSquares3 & ownSlidersHV) != squaresType::none())
									moves.add(mv);
							}
						}
					}
				}
			}
			if (stack.movingPlayer() == whitePlayer)
			{
				const squaresType criticalPromotionSquares{ rank8 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType criticalPromoCaptures{ criticalPromotionSquares & stack.position().playerOccupancy(blackPlayer) };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionWhite.inverseTargets(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					const squaresType toBB{ squaresType(to) };
					const squaresType promotedSliders{ ownSlidersHV ^ toBB };
					for (const auto from : movers)
					{
						const squaresType fromBB{ squaresType(from) };
						const squaresType newUnoccupied{ unoccupied ^ fromBB ^ toBB };
						const squaresType criticalSquares2{ movegenSlidersHV.inverseAttacks(otherKing, newUnoccupied) };
						if (criticalSquares2[to])
						{
							moves.add(motorType::move().createPromotionQueen(from, to));
							moves.add(motorType::move().createPromotionRook(from, to));
						}
					}
				}
				for (const auto to : criticalPromoCaptures)
				{
					const squaresType origins{ movegenPawnPromoCaptureWhite.inverseAttacks(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					const squaresType toBB{ squaresType(to) };
					const squaresType promotedSliders{ ownSlidersHV ^ toBB };
					for (const auto from : movers)
					{
						const squaresType fromBB{ squaresType(from) };
						const squaresType newUnoccupied{ unoccupied ^ fromBB };
						const squaresType criticalSquares2{ movegenSlidersHV.inverseAttacks(otherKing, newUnoccupied) };
						if (criticalSquares2[to])
						{
							moves.add(motorType::move().createPromoCaptureQueen(from, to));
							moves.add(motorType::move().createPromoCaptureRook(from, to));
						}
					}
				}
			}
			else
			{
				const squaresType criticalPromotionSquares{ rank1 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType criticalPromoCaptures{ criticalPromotionSquares & stack.position().playerOccupancy(whitePlayer) };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionBlack.inverseTargets(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					const squaresType toBB{ squaresType(to) };
					const squaresType promotedSliders{ ownSlidersHV ^ toBB };
					for (const auto from : movers)
					{
						const squaresType fromBB{ squaresType(from) };
						const squaresType newUnoccupied{ unoccupied ^ fromBB ^ toBB };
						const squaresType criticalSquares2{ movegenSlidersHV.inverseAttacks(otherKing, newUnoccupied) };
						if (criticalSquares2[to])
						{
							moves.add(motorType::move().createPromotionQueen(from, to));
							moves.add(motorType::move().createPromotionRook(from, to));
						}
					}
				}
				for (const auto to : criticalPromoCaptures)
				{
					const squaresType origins{ movegenPawnPromoCaptureWhite.inverseAttacks(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					const squaresType toBB{ squaresType(to) };
					const squaresType promotedSliders{ ownSlidersHV ^ toBB };
					for (const auto from : movers)
					{
						const squaresType fromBB{ squaresType(from) };
						const squaresType newUnoccupied{ unoccupied ^ fromBB };
						const squaresType criticalSquares2{ movegenSlidersHV.inverseAttacks(otherKing, newUnoccupied) };
						if (criticalSquares2[to])
						{
							moves.add(motorType::move().createPromoCaptureQueen(from, to));
							moves.add(motorType::move().createPromoCaptureRook(from, to));
						}
					}
				}
			}
			if (stack.position().movingPlayer() == whitePlayer)
			{
				if (stack.position().checkCastleRightKingsideWhite())
				{
					if (!(occupied & kingsideCastleInterestWhite))
					{
						const movebitsType mv{ motorType::move().createKingsideCastle() };
						const squaresType ownDelta{ motorType::move().ownOccupancyDelta(stack.position(),mv) };
						const squaresType otherDelta{ motorType::move().otherOccupancyDelta(stack.position(),mv) };
						const squaresType ownOcc{ ownDelta ^ stack.position().playerOccupancy(whitePlayer) };
						const squaresType otherOcc{ otherDelta ^ stack.position().playerOccupancy(blackPlayer) };
						const squaresType unoccupied2{ ~(ownOcc | otherOcc) };
						const squaresType criticalSquares3{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied2) };
						if (criticalSquares3[squareF1])
							moves.add(mv);
					}
				}
				if (stack.position().checkCastleRightQueensideWhite())
				{
					if (!(occupied & queensideCastleInterestWhite))
					{
						const movebitsType mv{ motorType::move().createQueensideCastle() };
						const squaresType ownDelta{ motorType::move().ownOccupancyDelta(stack.position(),mv) };
						const squaresType otherDelta{ motorType::move().otherOccupancyDelta(stack.position(),mv) };
						const squaresType ownOcc{ ownDelta ^ stack.position().playerOccupancy(whitePlayer) };
						const squaresType otherOcc{ otherDelta ^ stack.position().playerOccupancy(blackPlayer) };
						const squaresType unoccupied2{ ~(ownOcc | otherOcc) };
						const squaresType criticalSquares3{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied2) };
						if (criticalSquares3[squareD1])
							moves.add(mv);
					}
				}
			}
			else
			{
				if (stack.position().checkCastleRightKingsideBlack())
				{
					if (!(occupied & kingsideCastleInterestBlack))
					{
						const movebitsType mv{ motorType::move().createKingsideCastle() };
						const squaresType ownDelta{ motorType::move().ownOccupancyDelta(stack.position(),mv) };
						const squaresType otherDelta{ motorType::move().otherOccupancyDelta(stack.position(),mv) };
						const squaresType ownOcc{ ownDelta ^ stack.position().playerOccupancy(blackPlayer) };
						const squaresType otherOcc{ otherDelta ^ stack.position().playerOccupancy(whitePlayer) };
						const squaresType unoccupied2{ ~(ownOcc | otherOcc) };
						const squaresType criticalSquares3{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied2) };
						if (criticalSquares3[squareF8])
							moves.add(mv);
					}
				}
				if (stack.position().checkCastleRightQueensideBlack())
				{
					if (!(occupied & queensideCastleInterestBlack))
					{
						const movebitsType mv{ motorType::move().createQueensideCastle() };
						const squaresType ownDelta{ motorType::move().ownOccupancyDelta(stack.position(),mv) };
						const squaresType otherDelta{ motorType::move().otherOccupancyDelta(stack.position(),mv) };
						const squaresType ownOcc{ ownDelta ^ stack.position().playerOccupancy(blackPlayer) };
						const squaresType otherOcc{ otherDelta ^ stack.position().playerOccupancy(whitePlayer) };
						const squaresType unoccupied2{ ~(ownOcc | otherOcc) };
						const squaresType criticalSquares3{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied2) };
						if (criticalSquares3[squareD8])
							moves.add(mv);
					}
				}
			}
		}
		static void generateCriticalSliderMovesDiag(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType ownQueens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.movingPlayer()) };
			const squaresType ownBishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.movingPlayer()) };
			const squaresType ownSlidersDiag{ ownQueens | ownBishops };
			const squareType otherKing{ stack.kingSquare(stack.nextPlayer()) };
			const squaresType unoccupied{ ~stack.position().totalOccupancy() };
			const squaresType criticalSquares{ movegenSlidersDiag.inverseAttacks(otherKing, unoccupied) };
			const squaresType criticalTargets{ criticalSquares & unoccupied };
			const squaresType criticalCaptures{ criticalSquares & stack.position().playerOccupancy(stack.nextPlayer()) };
			const squaresType discoveryCandidates{ criticalSquares & stack.position().playerOccupancy(stack.movingPlayer()) };
			for (const auto to : criticalTargets)
			{
				const squaresType origins{ movegenSlidersDiag.inverseAttacks(to,unoccupied) };
				const squaresType movers{ origins & ownSlidersDiag };
				for (const auto from : movers)
					moves.add(motorType::move().createQuiet(from, to));
				const squaresType origins2{ movegenSlidersHV.inverseAttacks(to,unoccupied) };
				const squaresType movers2{ origins2 & ownQueens };
				for (const auto from : movers2)
					moves.add(motorType::move().createQuiet(from, to));
			}
			for (const auto to : criticalCaptures)
			{
				const squaresType origins{ movegenSlidersDiag.inverseAttacks(to,unoccupied) };
				const squaresType movers{ origins & ownSlidersDiag };
				for (const auto from : movers)
					moves.add(motorType::move().createCapture(from, to));
				const squaresType origins2{ movegenSlidersHV.inverseAttacks(to,unoccupied) };
				const squaresType movers2{ origins2 & ownQueens };
				for (const auto from : movers2)
					moves.add(motorType::move().createCapture(from, to));
			}
			for (const auto from : discoveryCandidates)
			{
				const squaresType discovered{ unoccupied | from };
				const squaresType discoveredRays{ movegenSlidersDiag.inverseAttacks(otherKing,discovered) };
				const squaresType discoveredAttacks{ discoveredRays & ownSlidersDiag };
				if (discoveredAttacks != squaresType::none())
				{
					const pieceType discoveringPiece{ stack.position().getPiece(from) };
					const squareType discoveredSquare{ *discoveredAttacks.begin() };
					const squaresType allowedDestinations{ ~(movegenSlidersDiag.attacks(from,discovered) & discoveredRays) };
					switch (discoveringPiece)
					{
					case king:
					{
						const squaresType discoveryTargets{ movegenKing.targets(from,squaresType::all()) & allowedDestinations };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						const squaresType discoveryCaptures{ discoveryTargets & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						for (const auto to : discoveryCaptures)
							moves.add(motorType::move().createCapture(from, to));
						break;
					}
					case knight:
					{
						const squaresType criticalSquares2{ movegenKnight.inverseAttacks(otherKing, squaresType::all()) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ movegenKnight.targets(from,squaresType::all()) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						const squaresType discoveryCaptures{ discoveryTargets & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						for (const auto to : discoveryCaptures)
							moves.add(motorType::move().createCapture(from, to));
						break;
					}
					case rook:
					{
						const squaresType criticalSquares2{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ movegenSlidersHV.attacks(from,discovered) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						const squaresType discoveryCaptures{ discoveryTargets & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						for (const auto to : discoveryCaptures)
							moves.add(motorType::move().createCapture(from, to));
						break;
					}
					case bishop:
					{
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares };
						const squaresType discoveryTargets{ movegenSlidersDiag.attacks(from,discovered) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						const squaresType discoveryCaptures{ discoveryTargets & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						for (const auto to : discoveryCaptures)
							moves.add(motorType::move().createCapture(from, to));
						break;
					}
					case queen:
					{
						const squaresType criticalSquares2{ criticalSquares | movegenSlidersHV.inverseAttacks(otherKing, unoccupied) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ (movegenSlidersHV.attacks(from,discovered) | movegenSlidersDiag.attacks(from,discovered)) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						const squaresType discoveryCaptures{ discoveryTargets & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						for (const auto to : discoveryCaptures)
							moves.add(motorType::move().createCapture(from, to));
						break;
					}
					case pawn:
					{
						if (stack.movingPlayer() == whitePlayer)
						{
							constexpr const squaresType notRank1{ ~rank1 };
							const squaresType tempSquare{ squaresType(otherKing).down() & notRank1 };
							const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
							const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
							const squaresType discoveryMoves{ movegenPawnPushWhite.targets(from,squaresType::all()) & allowedDestinations2 & unoccupied };
							const squaresType discoveryCaptures{ movegenPawnCaptureWhite.targets(from,squaresType::all()) & allowedDestinations2 & stack.position().playerOccupancy(stack.nextPlayer()) };
							const squaresType discoveryDoublePushes{ movegenPawnDoublePushWhite.targets(from,discovered) & allowedDestinations2 };
							for (const auto to : discoveryMoves)
								moves.add(motorType::move().createQuiet(from, to));
							for (const auto to : discoveryCaptures)
								moves.add(motorType::move().createCapture(from, to));
							const fileType fromFile{ from.file() };
							for (const auto to : discoveryDoublePushes)
								moves.add(motorType::move().createDoublePush(fromFile));
						}
						else
						{
							constexpr const squaresType notRank8{ ~rank8 };
							const squaresType tempSquare{ squaresType(otherKing).up() & notRank8 };
							const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
							const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
							const squaresType discoveryMoves{ movegenPawnPushBlack.targets(from,squaresType::all()) & allowedDestinations2 & unoccupied };
							const squaresType discoveryCaptures{ movegenPawnCaptureBlack.targets(from,squaresType::all()) & allowedDestinations2 & stack.position().playerOccupancy(stack.nextPlayer()) };
							const squaresType discoveryDoublePushes{ movegenPawnDoublePushBlack.targets(from,discovered) & allowedDestinations2 };
							for (const auto to : discoveryMoves)
								moves.add(motorType::move().createQuiet(from, to));
							for (const auto to : discoveryCaptures)
								moves.add(motorType::move().createCapture(from, to));
							const fileType fromFile{ from.file() };
							for (const auto to : discoveryDoublePushes)
								moves.add(motorType::move().createDoublePush(fromFile));
						}
						break;
					}
					}
				}
			}
			const uint_t<8, false> epFlags{ stack.position().flags().extractRange<4,11>() };
			if (epFlags)
			{
				size_t bit;
				if (stack.position().movingPlayer() == whitePlayer)
				{
					if (epFlags.bitscanForward(bit))
					{
						constexpr const squaresType notRank1{ ~rank1 };
						const squaresType tempSquare{ squaresType(otherKing).down() & notRank1 };
						const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
						const fileType epFile{ static_cast<typename fileType::baseType>(bit) };
						const squareType toSquare{ epFile & rank6 };
						const squaresType allowedDestinations2{ ~criticalSquares2 };
						const squaresType leftFile{ static_cast<squaresType>(epFile).left() };
						const squaresType rightFile{ static_cast<squaresType>(epFile).right() };
						const squaresType rank{ static_cast<squaresType>(rank5) };
						const squaresType fromSquares = (leftFile | rightFile) & rank;
						for (const squareType from : fromSquares & (stack.position().playerOccupancy(whitePlayer)& stack.position().pieceOccupancy(pawn)))
						{
							const movebitsType mv{ motorType::move().createEnPassant(from.file(), epFile) };
							const squareType to{ motorType::move().toSquare(stack.position(),mv) };
							if (allowedDestinations2[to])
							{
								const squaresType ownDelta{ motorType::move().ownOccupancyDelta(stack.position(),mv) };
								const squaresType otherDelta{ motorType::move().otherOccupancyDelta(stack.position(),mv) };
								const squaresType ownOcc{ ownDelta ^ stack.position().playerOccupancy(whitePlayer) };
								const squaresType otherOcc{ otherDelta ^ stack.position().playerOccupancy(blackPlayer) };
								const squaresType unoccupied2{ ~(ownOcc | otherOcc) };
								const squaresType criticalSquares3{ movegenSlidersDiag.inverseAttacks(otherKing, unoccupied2) };
								if ((criticalSquares3 & ownSlidersDiag) != squaresType::none())
									moves.add(mv);
							}
						}
					}
				}
				else
				{
					if (epFlags.bitscanForward(bit))
					{
						constexpr const squaresType notRank8{ ~rank8 };
						const squaresType tempSquare{ squaresType(otherKing).up() & notRank8 };
						const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
						const fileType epFile{ static_cast<typename fileType::baseType>(bit) };
						const squareType toSquare{ epFile & rank3 };
						const squaresType allowedDestinations2{ ~criticalSquares2 };
						const squaresType leftFile{ static_cast<squaresType>(epFile).left() };
						const squaresType rightFile{ static_cast<squaresType>(epFile).right() };
						const squaresType rank{ static_cast<squaresType>(rank4) };
						const squaresType fromSquares = (leftFile | rightFile) & rank;
						for (const squareType from : fromSquares & (stack.position().playerOccupancy(blackPlayer)& stack.position().pieceOccupancy(pawn)))
						{
							const movebitsType mv{ motorType::move().createEnPassant(from.file(), epFile) };
							const squareType to{ motorType::move().toSquare(stack.position(),mv) };
							if (allowedDestinations2[to])
							{
								const squaresType ownDelta{ motorType::move().ownOccupancyDelta(stack.position(),mv) };
								const squaresType otherDelta{ motorType::move().otherOccupancyDelta(stack.position(),mv) };
								const squaresType ownOcc{ ownDelta ^ stack.position().playerOccupancy(blackPlayer) };
								const squaresType otherOcc{ otherDelta ^ stack.position().playerOccupancy(whitePlayer) };
								const squaresType unoccupied2{ ~(ownOcc | otherOcc) };
								const squaresType criticalSquares3{ movegenSlidersDiag.inverseAttacks(otherKing, unoccupied2) };
								if ((criticalSquares3 & ownSlidersDiag) != squaresType::none())
									moves.add(mv);
							}
						}
					}
				}
			}
			if (stack.movingPlayer() == whitePlayer)
			{
				const squaresType criticalPromotionSquares{ rank8 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType criticalPromoCaptures{ criticalPromotionSquares & stack.position().playerOccupancy(blackPlayer) };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionWhite.inverseTargets(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					const squaresType toBB{ squaresType(to) };
					const squaresType promotedSliders{ ownSlidersDiag ^ toBB };
					for (const auto from : movers)
					{
						const squaresType fromBB{ squaresType(from) };
						const squaresType newUnoccupied{ unoccupied ^ fromBB ^ toBB };
						const squaresType criticalSquares2{ movegenSlidersDiag.inverseAttacks(otherKing, newUnoccupied) };
						if (criticalSquares2[to])
						{
							moves.add(motorType::move().createPromotionQueen(from, to));
							moves.add(motorType::move().createPromotionBishop(from, to));
						}
					}
				}
				for (const auto to : criticalPromoCaptures)
				{
					const squaresType origins{ movegenPawnPromoCaptureWhite.inverseAttacks(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					const squaresType toBB{ squaresType(to) };
					const squaresType promotedSliders{ ownSlidersDiag ^ toBB };
					for (const auto from : movers)
					{
						const squaresType fromBB{ squaresType(from) };
						const squaresType newUnoccupied{ unoccupied ^ fromBB  };
						const squaresType criticalSquares2{ movegenSlidersDiag.inverseAttacks(otherKing, newUnoccupied) };
						if (criticalSquares2[to])
						{
							moves.add(motorType::move().createPromoCaptureQueen(from, to));
							moves.add(motorType::move().createPromoCaptureBishop(from, to));
						}
					}
				}
			}
			else
			{
				const squaresType criticalPromotionSquares{ rank1 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType criticalPromoCaptures{ criticalPromotionSquares & stack.position().playerOccupancy(whitePlayer) };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionBlack.inverseTargets(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					const squaresType toBB{ squaresType(to) };
					const squaresType promotedSliders{ ownSlidersDiag ^ toBB };
					for (const auto from : movers)
					{
						const squaresType fromBB{ squaresType(from) };
						const squaresType newUnoccupied{ unoccupied ^ fromBB ^ toBB };
						const squaresType criticalSquares2{ movegenSlidersDiag.inverseAttacks(otherKing, newUnoccupied) };
						if (criticalSquares2[to])
						{
							moves.add(motorType::move().createPromotionQueen(from, to));
							moves.add(motorType::move().createPromotionBishop(from, to));
						}
					}
				}
				for (const auto to : criticalPromoCaptures)
				{
					const squaresType origins{ movegenPawnPromoCaptureWhite.inverseAttacks(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					const squaresType toBB{ squaresType(to) };
					const squaresType promotedSliders{ ownSlidersDiag ^ toBB };
					for (const auto from : movers)
					{
						const squaresType fromBB{ squaresType(from) };
						const squaresType newUnoccupied{ unoccupied ^ fromBB };
						const squaresType criticalSquares2{ movegenSlidersDiag.inverseAttacks(otherKing, newUnoccupied) };
						if (criticalSquares2[to])
						{
							moves.add(motorType::move().createPromoCaptureQueen(from, to));
							moves.add(motorType::move().createPromoCaptureBishop(from, to));
						}
					}
				}
			}
		}
		constexpr static inline moveGenFunction* m_CriticalMoves[]
		{
			&generateCriticalKnightMoves,
			&generateCriticalPawnMoves,
			&generateCriticalSliderMovesHV,
			&generateCriticalSliderMovesDiag
		};
		static void generateQuietCriticalKnightMoves(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType ownKnights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.movingPlayer()) };
			const squareType otherKing{ stack.kingSquare(stack.nextPlayer()) };
			const squaresType criticalSquares{ movegenKnight.inverseAttacks(otherKing, squaresType::all()) };
			const squaresType criticalTargets{ criticalSquares & ~stack.position().totalOccupancy() };
			for (const auto to : criticalTargets)
			{
				const squaresType origins{ movegenKnight.inverseTargets(to,squaresType::all()) };
				const squaresType movers{ origins & ownKnights };
				for (const auto from : movers)
					moves.add(motorType::move().createQuiet(from, to));
			}
			if (stack.movingPlayer() == whitePlayer)
			{
				const squaresType criticalPromotionSquares{ criticalSquares & rank8 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionWhite.inverseTargets(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					for (const auto from : movers)
						moves.add(motorType::move().createPromotionKnight(from, to));
				}
			}
			else
			{
				const squaresType criticalPromotionSquares{ criticalSquares & rank1 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionBlack.inverseTargets(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					for (const auto from : movers)
						moves.add(motorType::move().createPromotionKnight(from, to));
				}
			}
		}
		static void generateQuietCriticalPawnMovesWhite(const stackType& stack, movelistType& moves) noexcept
		{
			const squareType otherKing{ stack.kingSquare(blackPlayer) };
			const rankType otherKingRank{ otherKing.rank() };
			const squaresType unoccupied{ ~stack.position().totalOccupancy() };
			const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
			constexpr const squaresType notRank1{ ~rank1 };
			const squaresType tempSquare{ squaresType(otherKing).down() & notRank1 };
			const squaresType criticalSquares{ tempSquare.left() | tempSquare.right() };
			const squaresType criticalTargets{ criticalSquares & unoccupied };
			for (const auto to : criticalTargets)
			{
				const squaresType origins{ squaresType(to).down() & notRank1 };
				const squaresType movers{ origins & ownPawns };
				for (const auto from : movers)
					moves.add(motorType::move().createQuiet(from, to));
				const squaresType pushovers{ origins & unoccupied & rank3 };
				for (const auto pushover : pushovers)
				{
					const squaresType doublePushOrigins{ squaresType(pushover.down()) };
					const squaresType doublePushers{ doublePushOrigins & ownPawns };
					for (const auto from : doublePushers)
						moves.add(motorType::move().createDoublePush(to.file()));
				}
			}
		}
		static void generateQuietCriticalPawnMovesBlack(const stackType& stack, movelistType& moves) noexcept
		{
			const squareType otherKing{ stack.kingSquare(whitePlayer) };
			const rankType otherKingRank{ otherKing.rank() };
			const squaresType unoccupied{ ~stack.position().totalOccupancy() };
			const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
			constexpr const squaresType notRank8{ ~rank8 };
			const squaresType tempSquare{ squaresType(otherKing).up() & notRank8 };
			const squaresType criticalSquares{ tempSquare.left() | tempSquare.right() };
			const squaresType criticalTargets{ criticalSquares & unoccupied };
			for (const auto to : criticalTargets)
			{
				const squaresType origins{ squaresType(to).up() & notRank8 };
				const squaresType movers{ origins & ownPawns };
				for (const auto from : movers)
					moves.add(motorType::move().createQuiet(from, to));
				const squaresType pushovers{ origins & unoccupied & rank6 };
				for (const auto pushover : pushovers)
				{
					const squaresType doublePushOrigins{ squaresType(pushover.up()) };
					const squaresType doublePushers{ doublePushOrigins & ownPawns };
					for (const auto from : doublePushers)
						moves.add(motorType::move().createDoublePush(to.file()));
				}
			}
		}
		static void generateQuietCriticalPawnMoves(const stackType& stack, movelistType& moves) noexcept
		{
			if (stack.movingPlayer() == whitePlayer)
				generateQuietCriticalPawnMovesWhite(stack, moves);
			else
				generateQuietCriticalPawnMovesBlack(stack, moves);
		}
		static void generateQuietCriticalSliderMovesHV(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType ownQueens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.movingPlayer()) };
			const squaresType ownRooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.movingPlayer()) };
			const squaresType ownSlidersHV{ ownQueens | ownRooks };
			const squareType otherKing{ stack.kingSquare(stack.nextPlayer()) };
			const squaresType occupied{ stack.position().totalOccupancy() };
			const squaresType unoccupied{ ~occupied };
			const squaresType criticalSquares{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied) };
			const squaresType criticalTargets{ criticalSquares & unoccupied };
			const squaresType discoveryCandidates{ criticalSquares & stack.position().playerOccupancy(stack.movingPlayer()) };
			for (const auto to : criticalTargets)
			{
				const squaresType origins{ movegenSlidersHV.inverseAttacks(to,unoccupied) };
				const squaresType movers{ origins & ownSlidersHV };
				for (const auto from : movers)
					moves.add(motorType::move().createQuiet(from, to));
				const squaresType origins2{ movegenSlidersDiag.inverseAttacks(to,unoccupied) };
				const squaresType movers2{ origins2 & ownQueens };
				for (const auto from : movers2)
					moves.add(motorType::move().createQuiet(from, to));
			}
			for (const auto from : discoveryCandidates)
			{
				const squaresType discovered{ unoccupied | from };
				const squaresType discoveredRays{ movegenSlidersHV.inverseAttacks(otherKing,discovered) };
				const squaresType discoveredAttacks{ discoveredRays & ownSlidersHV };
				if (discoveredAttacks != squaresType::none())
				{
					const pieceType discoveringPiece{ stack.position().getPiece(from) };
					const squareType discoveredSquare{ *discoveredAttacks.begin() };
					const squaresType allowedDestinations{ ~(movegenSlidersHV.attacks(from,discovered) & discoveredRays) };
					switch (discoveringPiece)
					{
					case king:
					{
						const squaresType discoveryTargets{ movegenKing.targets(from,squaresType::all()) & allowedDestinations };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						break;
					}
					case knight:
					{
						const squaresType criticalSquares2{ movegenKnight.inverseAttacks(otherKing, squaresType::all()) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ movegenKnight.targets(from,squaresType::all()) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						break;
					}
					case rook:
					{
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares };
						const squaresType discoveryTargets{ movegenSlidersHV.attacks(from,discovered) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						break;
					}
					case bishop:
					{
						const squaresType criticalSquares2{ movegenSlidersDiag.inverseAttacks(otherKing, unoccupied) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ movegenSlidersDiag.attacks(from,discovered) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						break;
					}
					case queen:
					{
						const squaresType criticalSquares2{ criticalSquares | movegenSlidersDiag.inverseAttacks(otherKing, unoccupied) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ (movegenSlidersHV.attacks(from,discovered) | movegenSlidersDiag.attacks(from,discovered)) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						break;
					}
					case pawn:
					{
						if (stack.movingPlayer() == whitePlayer)
						{
							constexpr const squaresType notRank1{ ~rank1 };
							const squaresType tempSquare{ squaresType(otherKing).down() & notRank1 };
							const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
							const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
							const squaresType discoveryMoves{ movegenPawnPushWhite.targets(from,squaresType::all()) & allowedDestinations2 & unoccupied };
							const squaresType discoveryDoublePushes{ movegenPawnDoublePushWhite.targets(from,discovered) & allowedDestinations2 };
							for (const auto to : discoveryMoves)
								moves.add(motorType::move().createQuiet(from, to));
							const fileType fromFile{ from.file() };
							for (const auto to : discoveryDoublePushes)
								moves.add(motorType::move().createDoublePush(fromFile));
						}
						else
						{
							constexpr const squaresType notRank8{ ~rank8 };
							const squaresType tempSquare{ squaresType(otherKing).up() & notRank8 };
							const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
							const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
							const squaresType discoveryMoves{ movegenPawnPushBlack.targets(from,squaresType::all()) & allowedDestinations2 & unoccupied };
							const squaresType discoveryDoublePushes{ movegenPawnDoublePushBlack.targets(from,discovered) & allowedDestinations2 };
							for (const auto to : discoveryMoves)
								moves.add(motorType::move().createQuiet(from, to));
							const fileType fromFile{ from.file() };
							for (const auto to : discoveryDoublePushes)
								moves.add(motorType::move().createDoublePush(fromFile));
						}
						break;
					}
					}
				}
			}
			if (stack.movingPlayer() == whitePlayer)
			{
				const squaresType criticalPromotionSquares{ rank8 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionWhite.inverseTargets(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					const squaresType toBB{ squaresType(to) };
					const squaresType promotedSliders{ ownSlidersHV ^ toBB };
					for (const auto from : movers)
					{
						const squaresType fromBB{ squaresType(from) };
						const squaresType newUnoccupied{ unoccupied ^ fromBB ^ toBB };
						const squaresType criticalSquares2{ movegenSlidersHV.inverseAttacks(otherKing, newUnoccupied) };
						if (criticalSquares2[to])
						{
							moves.add(motorType::move().createPromotionQueen(from, to));
							moves.add(motorType::move().createPromotionRook(from, to));
						}
					}
				}
			}
			else
			{
				const squaresType criticalPromotionSquares{ rank1 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionBlack.inverseTargets(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					const squaresType toBB{ squaresType(to) };
					const squaresType promotedSliders{ ownSlidersHV ^ toBB };
					for (const auto from : movers)
					{
						const squaresType fromBB{ squaresType(from) };
						const squaresType newUnoccupied{ unoccupied ^ fromBB ^ toBB };
						const squaresType criticalSquares2{ movegenSlidersHV.inverseAttacks(otherKing, newUnoccupied) };
						if (criticalSquares2[to])
						{
							moves.add(motorType::move().createPromotionQueen(from, to));
							moves.add(motorType::move().createPromotionRook(from, to));
						}
					}
				}
			}
			if (stack.position().movingPlayer() == whitePlayer)
			{
				if (stack.position().checkCastleRightKingsideWhite())
				{
					if (!(occupied & kingsideCastleInterestWhite))
					{
						const movebitsType mv{ motorType::move().createKingsideCastle() };
						const squaresType ownDelta{ motorType::move().ownOccupancyDelta(stack.position(),mv) };
						const squaresType otherDelta{ motorType::move().otherOccupancyDelta(stack.position(),mv) };
						const squaresType ownOcc{ ownDelta ^ stack.position().playerOccupancy(whitePlayer) };
						const squaresType otherOcc{ otherDelta ^ stack.position().playerOccupancy(blackPlayer) };
						const squaresType unoccupied2{ ~(ownOcc | otherOcc) };
						const squaresType criticalSquares3{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied2) };
						if (criticalSquares3[squareF1])
							moves.add(mv);
					}
				}
				if (stack.position().checkCastleRightQueensideWhite())
				{
					if (!(occupied & queensideCastleInterestWhite))
					{
						const movebitsType mv{ motorType::move().createQueensideCastle() };
						const squaresType ownDelta{ motorType::move().ownOccupancyDelta(stack.position(),mv) };
						const squaresType otherDelta{ motorType::move().otherOccupancyDelta(stack.position(),mv) };
						const squaresType ownOcc{ ownDelta ^ stack.position().playerOccupancy(whitePlayer) };
						const squaresType otherOcc{ otherDelta ^ stack.position().playerOccupancy(blackPlayer) };
						const squaresType unoccupied2{ ~(ownOcc | otherOcc) };
						const squaresType criticalSquares3{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied2) };
						if (criticalSquares3[squareD1])
							moves.add(mv);
					}
				}
			}
			else
			{
				if (stack.position().checkCastleRightKingsideBlack())
				{
					if (!(occupied & kingsideCastleInterestBlack))
					{
						const movebitsType mv{ motorType::move().createKingsideCastle() };
						const squaresType ownDelta{ motorType::move().ownOccupancyDelta(stack.position(),mv) };
						const squaresType otherDelta{ motorType::move().otherOccupancyDelta(stack.position(),mv) };
						const squaresType ownOcc{ ownDelta ^ stack.position().playerOccupancy(blackPlayer) };
						const squaresType otherOcc{ otherDelta ^ stack.position().playerOccupancy(whitePlayer) };
						const squaresType unoccupied2{ ~(ownOcc | otherOcc) };
						const squaresType criticalSquares3{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied2) };
						if (criticalSquares3[squareF8])
							moves.add(mv);
					}
				}
				if (stack.position().checkCastleRightQueensideBlack())
				{
					if (!(occupied & queensideCastleInterestBlack))
					{
						const movebitsType mv{ motorType::move().createQueensideCastle() };
						const squaresType ownDelta{ motorType::move().ownOccupancyDelta(stack.position(),mv) };
						const squaresType otherDelta{ motorType::move().otherOccupancyDelta(stack.position(),mv) };
						const squaresType ownOcc{ ownDelta ^ stack.position().playerOccupancy(blackPlayer) };
						const squaresType otherOcc{ otherDelta ^ stack.position().playerOccupancy(whitePlayer) };
						const squaresType unoccupied2{ ~(ownOcc | otherOcc) };
						const squaresType criticalSquares3{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied2) };
						if (criticalSquares3[squareD8])
							moves.add(mv);
					}
				}
			}
		}
		static void generateQuietCriticalSliderMovesDiag(const stackType& stack, movelistType& moves) noexcept
		{
			const squaresType ownQueens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.movingPlayer()) };
			const squaresType ownBishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.movingPlayer()) };
			const squaresType ownSlidersDiag{ ownQueens | ownBishops };
			const squareType otherKing{ stack.kingSquare(stack.nextPlayer()) };
			const squaresType unoccupied{ ~stack.position().totalOccupancy() };
			const squaresType criticalSquares{ movegenSlidersDiag.inverseAttacks(otherKing, unoccupied) };
			const squaresType criticalTargets{ criticalSquares & unoccupied };
			const squaresType discoveryCandidates{ criticalSquares & stack.position().playerOccupancy(stack.movingPlayer()) };
			for (const auto to : criticalTargets)
			{
				const squaresType origins{ movegenSlidersDiag.inverseAttacks(to,unoccupied) };
				const squaresType movers{ origins & ownSlidersDiag };
				for (const auto from : movers)
					moves.add(motorType::move().createQuiet(from, to));
				const squaresType origins2{ movegenSlidersHV.inverseAttacks(to,unoccupied) };
				const squaresType movers2{ origins2 & ownQueens };
				for (const auto from : movers2)
					moves.add(motorType::move().createQuiet(from, to));
			}
			for (const auto from : discoveryCandidates)
			{
				const squaresType discovered{ unoccupied | from };
				const squaresType discoveredRays{ movegenSlidersDiag.inverseAttacks(otherKing,discovered) };
				const squaresType discoveredAttacks{ discoveredRays & ownSlidersDiag };
				if (discoveredAttacks != squaresType::none())
				{
					const pieceType discoveringPiece{ stack.position().getPiece(from) };
					const squareType discoveredSquare{ *discoveredAttacks.begin() };
					const squaresType allowedDestinations{ ~(movegenSlidersDiag.attacks(from,discovered) & discoveredRays) };
					switch (discoveringPiece)
					{
					case king:
					{
						const squaresType discoveryTargets{ movegenKing.targets(from,squaresType::all()) & allowedDestinations };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						break;
					}
					case knight:
					{
						const squaresType criticalSquares2{ movegenKnight.inverseAttacks(otherKing, squaresType::all()) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ movegenKnight.targets(from,squaresType::all()) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						break;
					}
					case rook:
					{
						const squaresType criticalSquares2{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ movegenSlidersHV.attacks(from,discovered) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						break;
					}
					case bishop:
					{
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares };
						const squaresType discoveryTargets{ movegenSlidersDiag.attacks(from,discovered) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						break;
					}
					case queen:
					{
						const squaresType criticalSquares2{ criticalSquares | movegenSlidersHV.inverseAttacks(otherKing, unoccupied) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ (movegenSlidersHV.attacks(from,discovered) | movegenSlidersDiag.attacks(from,discovered)) & allowedDestinations2 };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						break;
					}
					case pawn:
					{
						if (stack.movingPlayer() == whitePlayer)
						{
							constexpr const squaresType notRank1{ ~rank1 };
							const squaresType tempSquare{ squaresType(otherKing).down() & notRank1 };
							const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
							const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
							const squaresType discoveryMoves{ movegenPawnPushWhite.targets(from,squaresType::all()) & allowedDestinations2 & unoccupied };
							const squaresType discoveryDoublePushes{ movegenPawnDoublePushWhite.targets(from,discovered) & allowedDestinations2 };
							for (const auto to : discoveryMoves)
								moves.add(motorType::move().createQuiet(from, to));
							const fileType fromFile{ from.file() };
							for (const auto to : discoveryDoublePushes)
								moves.add(motorType::move().createDoublePush(fromFile));
						}
						else
						{
							constexpr const squaresType notRank8{ ~rank8 };
							const squaresType tempSquare{ squaresType(otherKing).up() & notRank8 };
							const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
							const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
							const squaresType discoveryMoves{ movegenPawnPushBlack.targets(from,squaresType::all()) & allowedDestinations2 & unoccupied };
							const squaresType discoveryDoublePushes{ movegenPawnDoublePushBlack.targets(from,discovered) & allowedDestinations2 };
							for (const auto to : discoveryMoves)
								moves.add(motorType::move().createQuiet(from, to));
							const fileType fromFile{ from.file() };
							for (const auto to : discoveryDoublePushes)
								moves.add(motorType::move().createDoublePush(fromFile));
						}
						break;
					}
					}
				}
			}
			if (stack.movingPlayer() == whitePlayer)
			{
				const squaresType criticalPromotionSquares{ rank8 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionWhite.inverseTargets(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					const squaresType toBB{ squaresType(to) };
					const squaresType promotedSliders{ ownSlidersDiag ^ toBB };
					for (const auto from : movers)
					{
						const squaresType fromBB{ squaresType(from) };
						const squaresType newUnoccupied{ unoccupied ^ fromBB ^ toBB };
						const squaresType criticalSquares2{ movegenSlidersDiag.inverseAttacks(otherKing, newUnoccupied) };
						if (criticalSquares2[to])
						{
							moves.add(motorType::move().createPromotionQueen(from, to));
							moves.add(motorType::move().createPromotionBishop(from, to));
						}
					}
				}
			}
			else
			{
				const squaresType criticalPromotionSquares{ rank1 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionBlack.inverseTargets(to,squaresType::all()) };
					const squaresType movers{ origins & ownPawns };
					const squaresType toBB{ squaresType(to) };
					const squaresType promotedSliders{ ownSlidersDiag ^ toBB };
					for (const auto from : movers)
					{
						const squaresType fromBB{ squaresType(from) };
						const squaresType newUnoccupied{ unoccupied ^ fromBB ^ toBB };
						const squaresType criticalSquares2{ movegenSlidersDiag.inverseAttacks(otherKing, newUnoccupied) };
						if (criticalSquares2[to])
						{
							moves.add(motorType::move().createPromotionQueen(from, to));
							moves.add(motorType::move().createPromotionBishop(from, to));
						}
					}
				}
			}
		}
		constexpr static inline moveGenFunction* m_QuietCriticalMoves[]
		{
			&generateQuietCriticalKnightMoves,
			&generateQuietCriticalPawnMoves,
			&generateQuietCriticalSliderMovesHV,
			&generateQuietCriticalSliderMovesDiag
		};
	public:
		static const rays& rays() noexcept
		{
			return m_Rays;
		}
		static squaresType attackers(const boardType& position, const squareType square) noexcept
		{
			assert(square.isValid());
			squaresType attackers{ squaresType::none() };
			const squaresType allowed{ ~position.totalOccupancy() };
			attackers |= movegenKnight.attacks(square, allowed) & position.pieceOccupancy(knight);
			attackers |= movegenKing.attacks(square, allowed) & position.pieceOccupancy(king);
			const squaresType whitepawns{ position.pieceOccupancy(pawn) & position.playerOccupancy(whitePlayer) };
			const squaresType blackpawns{ position.pieceOccupancy(pawn) & position.playerOccupancy(blackPlayer) };
			const squaresType piecemap{ squaresType(square) };
			const squaresType temppiecemap1{ piecemap.up() };
			const squaresType temppiecemap2{ piecemap.down() };
			attackers |= (temppiecemap1.left() | temppiecemap1.right()) & blackpawns;
			attackers |= (temppiecemap2.left() | temppiecemap2.right()) & whitepawns;
			const squaresType slidersHV{ position.pieceOccupancy(queen) | position.pieceOccupancy(rook) };
			const squaresType slidersDiag{ position.pieceOccupancy(queen) | position.pieceOccupancy(bishop) };
			attackers |= movegenSlidersHV.attacks(square, allowed) & slidersHV;
			attackers |= movegenSlidersDiag.attacks(square, allowed) & slidersDiag;
			return attackers;
		}
		static squaresType attackers(const boardType& position, const squareType square, const playerType attacker) noexcept
		{
			assert(square.isValid());
			squaresType attackers{ squaresType::none() };
			const squaresType allowed{ ~position.totalOccupancy() };
			attackers |= movegenKnight.attacks(square, allowed) & position.pieceOccupancy(knight);
			attackers |= movegenKing.attacks(square, allowed) & position.pieceOccupancy(king);
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
			attackers |= movegenSlidersHV.attacks(square, allowed) & slidersHV;
			attackers |= movegenSlidersDiag.attacks(square, allowed) & slidersDiag;
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
					if (!movegenKing.targets(from, ~position.playerOccupancy(movingPlayer))[to])
						return false;
					break;
				case knight:
					if (!movegenKnight.targets(from, ~position.playerOccupancy(movingPlayer))[to])
						return false;
					break;
				case rook:
					if (!(movegenSlidersHV.attacks(from, ~position.totalOccupancy()) & position.playerOccupancy(otherPlayer))[to])
						return false;
					break;
				case bishop:
					if (!(movegenSlidersDiag.attacks(from, ~position.totalOccupancy()) & position.playerOccupancy(otherPlayer))[to])
						return false;
					break;
				case queen:
					if (!((movegenSlidersHV.attacks(from, ~position.totalOccupancy()) | movegenSlidersDiag.attacks(from, ~position.totalOccupancy())) & position.playerOccupancy(otherPlayer))[to])
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
					if (!movegenKing.targets(from, ~position.playerOccupancy(movingPlayer))[to])
						return false;
					break;
				case knight:
					if (!movegenKnight.targets(from, ~position.playerOccupancy(movingPlayer))[to])
						return false;
					break;
				case rook:
					if (!(movegenSlidersHV.attacks(from, ~position.totalOccupancy()) & ~position.totalOccupancy())[to])
						return false;
					break;
				case bishop:
					if (!(movegenSlidersDiag.attacks(from, ~position.totalOccupancy()) & ~position.totalOccupancy())[to])
						return false;
					break;
				case queen:
					if (!((movegenSlidersHV.attacks(from, ~position.totalOccupancy()) | movegenSlidersDiag.attacks(from, ~position.totalOccupancy())) & ~position.totalOccupancy())[to])
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
				const squaresType knightsDelta{ motorType::move().pieceOccupancyDelta(position, knight, moveBits) };
				const squaresType otherKnights{ (position.pieceOccupancy(knight) ^ knightsDelta) & occOther };
				const squaresType attackedByOtherKnights{ movegenKnight.attacks(otherKnights,squaresType::all()) };
				if (attackedByOtherKnights[kingsquare])
					return false;

				// Does he live on a square that is guarded by an enemy pawn?
				const squaresType pawnsDelta{ motorType::move().pieceOccupancyDelta(position, pawn, moveBits) };
				const squaresType otherPawns{ (position.pieceOccupancy(pawn) ^ pawnsDelta) & occOther };
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
				if (isKingMove)
				{
					if (motorType::move().isKingsideCastle(moveBits))
					{
						// is the way for the king attacked?
						const squaresType castleWalk{ (movingPlayer == whitePlayer) ? kingsideCastleWalkWhite : kingsideCastleWalkBlack };
						if (stack.squaresAttackedByPlayer(otherPlayer) & castleWalk)
							return false;
					}
					else if (motorType::move().isQueensideCastle(moveBits))
					{
						// is the way for the king attacked?
						const squaresType castleWalk{ (movingPlayer == whitePlayer) ? queensideCastleWalkWhite : queensideCastleWalkBlack };
						if (stack.squaresAttackedByPlayer(otherPlayer) & castleWalk)
							return false;
					}
				}
			}

			// We need the total occupancy bitboard as it would be after the move...
			const squaresType movingOccupancy{ position.playerOccupancy(movingPlayer) };
			const squaresType movingDelta{ motorType::move().ownOccupancyDelta(position, moveBits) };
			const squaresType occMoving{ movingOccupancy ^ movingDelta };
			const squaresType occTotal{ occOther | occMoving };
			const squaresType unoccupied{ ~occTotal };

			// Is he attacked horizontally by sliding pieces?
			const squaresType queensDelta{ motorType::move().pieceOccupancyDelta(position, queen, moveBits) };
			const squaresType queens{ position.pieceOccupancy(queen) ^ queensDelta };
			const squaresType rooksDelta{ motorType::move().pieceOccupancyDelta(position, rook, moveBits) };
			const squaresType rooks{ position.pieceOccupancy(rook) ^ rooksDelta };
			const squaresType otherSlidersHV = occOther & (rooks | queens);
			const squaresType criticalSquaresHV{ movegenSlidersHV.inverseAttacks(kingsquare, unoccupied) };
			if ((criticalSquaresHV & otherSlidersHV) != squaresType::none())
				return false;

			// Is he attacked diagonally by sliding pieces?
			const squaresType bishopsDelta{ motorType::move().pieceOccupancyDelta(position, bishop, moveBits) };
			const squaresType bishops{ position.pieceOccupancy(bishop) ^ bishopsDelta };
			const squaresType otherSlidersDiag = occOther & (bishops | queens);
			const squaresType criticalSquaresDiag{ movegenSlidersDiag.inverseAttacks(kingsquare, unoccupied) };
			if ((criticalSquaresDiag & otherSlidersDiag) != squaresType::none())
				return false;

			// The move seems legal
			return true;
		}
		constexpr static void generateMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			(*(m_Moves[static_cast<size_t>(currentPass)]))(stack, moves);
		}
		constexpr static void generateCriticalMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			(*(m_CriticalMoves[static_cast<size_t>(currentPass)]))(stack, moves);
		}
		static void generateCriticalEvasionMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			const squaresType totalOCC{ stack.position().totalOccupancy() };
			const squaresType unoccupied{ ~totalOCC };
			movebitsType move;
			const playerType side{ stack.position().movingPlayer() };
			const playerType otherSide{ side.next() };
			const squareType king{ stack.kingSquare(side) };
			const squaresType otherPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(otherSide) };
			const squaresType otherKnights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(otherSide) };
			const squaresType otherBishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(otherSide) };
			const squaresType otherRooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(otherSide) };
			const squaresType otherQueens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(otherSide) };
			squaresType attackers = otherKnights & movegenKnight.attacks(king, squaresType::all());
			attackers |= (otherBishops | otherQueens) & movegenSlidersDiag.attacks(king, unoccupied);
			attackers |= (otherRooks | otherQueens) & movegenSlidersHV.attacks(king, unoccupied);
			const squaresType kingSquares{ squaresType(king) };
			if (side == blackPlayer)
			{
				const squaresType downSquares{ kingSquares.down() };
				attackers |= otherPawns & (downSquares.left() | downSquares.right());
			}
			else
			{
				const squaresType upSquares{ kingSquares.up() };
				attackers |= otherPawns & (upSquares.left() | upSquares.right());
			}
			// Is the king attacked by a single piece?
			if (attackers.count() == 1)
			{
				const squaresType ownPawns = stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(side);
				const squaresType ownKnights = stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(side);
				const squaresType ownDiagSliders = (stack.position().pieceOccupancy(bishop) | stack.position().pieceOccupancy(queen)) & stack.position().playerOccupancy(side);
				const squaresType ownHVSliders = (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen)) & stack.position().playerOccupancy(side);
				const squareType attackerSquare{ *attackers.begin() };
				// Can the attacker be captured with a knight?
				squaresType defenders = ownKnights & movegenKnight.attacks(attackerSquare, squaresType::all());
				for (const auto defenderSquare : defenders)
					moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
				// Can the attacker be captured with a diagonal slider?
				defenders = ownDiagSliders & movegenSlidersDiag.attacks(attackerSquare, unoccupied);
				for (const auto defenderSquare : defenders)
					moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
				// Can the attacker be captured with a HV slider?
				defenders = ownHVSliders & movegenSlidersHV.attacks(attackerSquare, unoccupied);
				for (const auto defenderSquare : defenders)
					moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
				// Can the attacker be captured by a pawn?
				const rankType attackerRank{ attackerSquare.rank() };
				if ((attackerRank == rank1) && (side == blackPlayer))
				{
					const fileType attackerFile{ attackerSquare.file() };
					if (attackerFile != fileA)
					{
						const squareType defenderSquare{ attackerFile.left() & rank2 };
						if (ownPawns[defenderSquare])
						{
							moves.add(motorType::move().createPromoCaptureQueen(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureKnight(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureRook(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureBishop(defenderSquare, attackerSquare));
						}
					}
					if (attackerFile != fileH)
					{
						const squareType defenderSquare{ attackerFile.right() & rank2 };
						if (ownPawns[defenderSquare])
						{
							moves.add(motorType::move().createPromoCaptureQueen(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureKnight(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureRook(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureBishop(defenderSquare, attackerSquare));
						}
					}
				}
				else if ((attackerRank == rank8) && (side == whitePlayer))
				{
					const fileType attackerFile{ attackerSquare.file() };
					if (attackerFile != fileA)
					{
						const squareType defenderSquare{ attackerFile.left() & rank7 };
						if (ownPawns[defenderSquare])
						{
							moves.add(motorType::move().createPromoCaptureQueen(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureKnight(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureRook(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureBishop(defenderSquare, attackerSquare));
						}
					}
					if (attackerFile != fileH)
					{
						const squareType defenderSquare{ attackerFile.right() & rank7 };
						if (ownPawns[defenderSquare])
						{
							moves.add(motorType::move().createPromoCaptureQueen(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureKnight(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureRook(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureBishop(defenderSquare, attackerSquare));
						}
					}
				}
				else
				{
					if (side == blackPlayer)
					{
						if (attackerRank != rank8)
						{
							const fileType attackerFile{ attackerSquare.file() };
							if (attackerFile != fileA)
							{
								const squareType defenderSquare{ attackerSquare.up().left() };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
							}
							if (attackerFile != fileH)
							{
								const squareType defenderSquare{ attackerSquare.up().right() };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
							}
						}
					}
					else
					{
						if (attackerRank != rank1)
						{
							const fileType attackerFile{ attackerSquare.file() };
							if (attackerFile != fileA)
							{
								const squareType defenderSquare{ attackerSquare.down().left() };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
							}
							if (attackerFile != fileH)
							{
								const squareType defenderSquare{ attackerSquare.down().right() };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
							}
						}
					}
				}
				// Is the attacker a pawn that can be captured en passant?
				if (attackers & otherPawns)
				{
					const fileType attackerFile{ attackerSquare.file() };
					if (stack.position().checkEnPassantFile(attackerFile))
					{
						if ((otherSide == blackPlayer) && (attackerRank == rank5))
						{
							if (attackerFile != fileA)
							{
								const fileType defenderFile{ attackerFile.left() };
								const squareType defenderSquare{ defenderFile & rank5 };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createEnPassant(defenderFile, attackerFile));
							}
							if (attackerFile != fileH)
							{
								const fileType defenderFile{ attackerFile.right() };
								const squareType defenderSquare{ defenderFile & rank5 };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createEnPassant(defenderFile, attackerFile));
							}
						}
						else if (attackerRank == rank4)
						{
							if (attackerFile != fileA)
							{
								const fileType defenderFile{ attackerFile.left() };
								const squareType defenderSquare{ defenderFile & rank4 };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createEnPassant(defenderFile, attackerFile));
							}
							if (attackerFile != fileH)
							{
								const fileType defenderFile{ attackerFile.right() };
								const squareType defenderSquare{ defenderFile & rank4 };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createEnPassant(defenderFile, attackerFile));
							}
						}
					}
				}
				// Is the attack a slide attack that can be blocked?
				squaresType blockSquares{ squaresType::none() };
				for (int rayDir = 0; rayDir < 8; rayDir++)
				{
					const squaresType rayFromKing{ m_Rays.getRay(rayDir,king) };
					if (rayFromKing & attackers)
					{
						switch (rayDir)
						{
						default:
							assert(false);
							break;
						case rays::rayUp:
						case rays::rayDown:
						case rays::rayLeft:
						case rays::rayRight:
							if (rayFromKing & (otherRooks | otherQueens))
							{
								const squaresType rayFromAttacker{ m_Rays.getRay(rays::invertRay(rayDir), attackerSquare) };
								blockSquares = rayFromAttacker & rayFromKing;
							}
							break;
						case rays::rayUpRight:
						case rays::rayDownRight:
						case rays::rayUpLeft:
						case rays::rayDownLeft:
							if (rayFromKing & (otherBishops | otherQueens))
							{
								const squaresType rayFromAttacker{ m_Rays.getRay(rays::invertRay(rayDir), attackerSquare) };
								blockSquares = rayFromAttacker & rayFromKing;
							}
							break;
						}
						break;
					}
				}
				for (const auto blockSquare : blockSquares)
				{
					// Is it possible to block on this square with knights?
					squaresType defenders{ ownKnights & movegenKnight.attacks(blockSquare, squaresType::all()) };
					for (const auto defenderSquare : defenders)
					{
						moves.add(motorType::move().createQuiet(defenderSquare, blockSquare));
					}
					// Is it possible to block on this square with diagonal sliders?
					defenders = ownDiagSliders & movegenSlidersDiag.attacks(blockSquare, unoccupied);
					for (const auto defenderSquare : defenders)
					{
						moves.add(motorType::move().createQuiet(defenderSquare, blockSquare));
					}
					// Is it possible to block on this square with HV sliders?
					defenders = ownHVSliders & movegenSlidersHV.attacks(blockSquare, unoccupied);
					for (const auto defenderSquare : defenders)
					{
						moves.add(motorType::move().createQuiet(defenderSquare, blockSquare));
					}
					// Is it possible to block on this square with a pawn doublepush?
					const rankType rank{ blockSquare.rank() };
					const fileType file{ blockSquare.file() };
					if ((rank == rank4) && (side == whitePlayer))
					{
						if (ownPawns[file & rank2] && !totalOCC[file & rank3])
						{
							moves.add(motorType::move().createDoublePush(file));
						}
					}
					else if ((rank == rank5) && (side == blackPlayer))
					{
						if (ownPawns[file & rank7] && !totalOCC[file & rank6])
						{
							moves.add(motorType::move().createDoublePush(file));
						}
					}
					// Is it possible to block on this square with a pawn push?
					if (side == whitePlayer)
					{
						if (rank != rank1)
						{
							const squareType defenderSquare{ file & rank.down() };
							if (ownPawns[defenderSquare])
							{
								if (rank == rank8)
								{
									// It's actually a pawn promotion...
									moves.add(motorType::move().createPromotionQueen(defenderSquare, blockSquare));
									moves.add(motorType::move().createPromotionKnight(defenderSquare, blockSquare));
									moves.add(motorType::move().createPromotionRook(defenderSquare, blockSquare));
									moves.add(motorType::move().createPromotionBishop(defenderSquare, blockSquare));
								}
								else
								{
									moves.add(motorType::move().createQuiet(defenderSquare, blockSquare));
								}
							}
						}
					}
					else
					{
						if (rank != rank8)
						{
							const squareType defenderSquare{ file & rank.up() };
							if (ownPawns[defenderSquare])
							{
								if (rank == rank1)
								{
									// It's actually a pawn promotion...
									moves.add(motorType::move().createPromotionQueen(defenderSquare, blockSquare));
									moves.add(motorType::move().createPromotionKnight(defenderSquare, blockSquare));
									moves.add(motorType::move().createPromotionRook(defenderSquare, blockSquare));
									moves.add(motorType::move().createPromotionBishop(defenderSquare, blockSquare));
								}
								else
								{
									moves.add(motorType::move().createQuiet(defenderSquare, blockSquare));
								}
							}
						}
					}
				}
			}
			// Finally generate the king moves out of check...
			const squaresType quiets{ movegenKing.attacks(king, squaresType::all()) & unoccupied };
			for (const auto square : quiets)
			{
				moves.add(motorType::move().createQuiet(king, square));
			}
			const squaresType caps{ movegenKing.attacks(king, squaresType::all()) & stack.position().playerOccupancy(otherSide) };
			for (const auto square : caps)
			{
				moves.add(motorType::move().createCapture(king, square));
			}
		}
		static void generateTacticalCriticalEvasionMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			const squaresType totalOCC{ stack.position().totalOccupancy() };
			const squaresType unoccupied{ ~totalOCC };
			movebitsType move;
			const playerType side{ stack.position().movingPlayer() };
			const playerType otherSide{ side.next() };
			const squareType king{ stack.kingSquare(side) };
			const squaresType otherPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(otherSide) };
			const squaresType otherKnights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(otherSide) };
			const squaresType otherBishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(otherSide) };
			const squaresType otherRooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(otherSide) };
			const squaresType otherQueens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(otherSide) };
			squaresType attackers = otherKnights & movegenKnight.attacks(king, squaresType::all());
			attackers |= (otherBishops | otherQueens) & movegenSlidersDiag.attacks(king, unoccupied);
			attackers |= (otherRooks | otherQueens) & movegenSlidersHV.attacks(king, unoccupied);
			const squaresType kingSquares{ squaresType(king) };
			if (side == blackPlayer)
			{
				const squaresType downSquares{ kingSquares.down() };
				attackers |= otherPawns & (downSquares.left() | downSquares.right());
			}
			else
			{
				const squaresType upSquares{ kingSquares.up() };
				attackers |= otherPawns & (upSquares.left() | upSquares.right());
			}
			// Is the king attacked by a single piece?
			if (attackers.count() == 1)
			{
				const squaresType ownPawns = stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(side);
				const squaresType ownKnights = stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(side);
				const squaresType ownDiagSliders = (stack.position().pieceOccupancy(bishop) | stack.position().pieceOccupancy(queen)) & stack.position().playerOccupancy(side);
				const squaresType ownHVSliders = (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen)) & stack.position().playerOccupancy(side);
				const squareType attackerSquare{ *attackers.begin() };
				// Can the attacker be captured with a knight?
				squaresType defenders = ownKnights & movegenKnight.attacks(attackerSquare, squaresType::all());
				for (const auto defenderSquare : defenders)
					moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
				// Can the attacker be captured with a diagonal slider?
				defenders = ownDiagSliders & movegenSlidersDiag.attacks(attackerSquare, unoccupied);
				for (const auto defenderSquare : defenders)
					moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
				// Can the attacker be captured with a HV slider?
				defenders = ownHVSliders & movegenSlidersHV.attacks(attackerSquare, unoccupied);
				for (const auto defenderSquare : defenders)
					moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
				// Can the attacker be captured by a pawn?
				const rankType attackerRank{ attackerSquare.rank() };
				if ((attackerRank == rank1) && (side == blackPlayer))
				{
					const fileType attackerFile{ attackerSquare.file() };
					if (attackerFile != fileA)
					{
						const squareType defenderSquare{ attackerFile.left() & rank2 };
						if (ownPawns[defenderSquare])
						{
							moves.add(motorType::move().createPromoCaptureQueen(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureKnight(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureRook(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureBishop(defenderSquare, attackerSquare));
						}
					}
					if (attackerFile != fileH)
					{
						const squareType defenderSquare{ attackerFile.right() & rank2 };
						if (ownPawns[defenderSquare])
						{
							moves.add(motorType::move().createPromoCaptureQueen(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureKnight(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureRook(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureBishop(defenderSquare, attackerSquare));
						}
					}
				}
				else if ((attackerRank == rank8) && (side == whitePlayer))
				{
					const fileType attackerFile{ attackerSquare.file() };
					if (attackerFile != fileA)
					{
						const squareType defenderSquare{ attackerFile.left() & rank7 };
						if (ownPawns[defenderSquare])
						{
							moves.add(motorType::move().createPromoCaptureQueen(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureKnight(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureRook(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureBishop(defenderSquare, attackerSquare));
						}
					}
					if (attackerFile != fileH)
					{
						const squareType defenderSquare{ attackerFile.right() & rank7 };
						if (ownPawns[defenderSquare])
						{
							moves.add(motorType::move().createPromoCaptureQueen(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureKnight(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureRook(defenderSquare, attackerSquare));
							moves.add(motorType::move().createPromoCaptureBishop(defenderSquare, attackerSquare));
						}
					}
				}
				else
				{
					if (side == blackPlayer)
					{
						if (attackerRank != rank8)
						{
							const fileType attackerFile{ attackerSquare.file() };
							if (attackerFile != fileA)
							{
								const squareType defenderSquare{ attackerSquare.up().left() };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
							}
							if (attackerFile != fileH)
							{
								const squareType defenderSquare{ attackerSquare.up().right() };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
							}
						}
					}
					else
					{
						if (attackerRank != rank1)
						{
							const fileType attackerFile{ attackerSquare.file() };
							if (attackerFile != fileA)
							{
								const squareType defenderSquare{ attackerSquare.down().left() };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
							}
							if (attackerFile != fileH)
							{
								const squareType defenderSquare{ attackerSquare.down().right() };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createCapture(defenderSquare, attackerSquare));
							}
						}
					}
				}
				// Is the attacker a pawn that can be captured en passant?
				if (attackers & otherPawns)
				{
					const fileType attackerFile{ attackerSquare.file() };
					if (stack.position().checkEnPassantFile(attackerFile))
					{
						if ((otherSide == blackPlayer) && (attackerRank == rank5))
						{
							if (attackerFile != fileA)
							{
								const fileType defenderFile{ attackerFile.left() };
								const squareType defenderSquare{ defenderFile & rank5 };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createEnPassant(defenderFile, attackerFile));
							}
							if (attackerFile != fileH)
							{
								const fileType defenderFile{ attackerFile.right() };
								const squareType defenderSquare{ defenderFile & rank5 };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createEnPassant(defenderFile, attackerFile));
							}
						}
						else if (attackerRank == rank4)
						{
							if (attackerFile != fileA)
							{
								const fileType defenderFile{ attackerFile.left() };
								const squareType defenderSquare{ defenderFile & rank4 };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createEnPassant(defenderFile, attackerFile));
							}
							if (attackerFile != fileH)
							{
								const fileType defenderFile{ attackerFile.right() };
								const squareType defenderSquare{ defenderFile & rank4 };
								if (ownPawns[defenderSquare])
									moves.add(motorType::move().createEnPassant(defenderFile, attackerFile));
							}
						}
					}
				}
			}
			// Finally generate the king moves out of check...
			const squaresType caps{ movegenKing.attacks(king, squaresType::all()) & stack.position().playerOccupancy(otherSide) };
			for (const auto square : caps)
			{
				moves.add(motorType::move().createCapture(king, square));
			}
		}
		constexpr static void generateQuietCriticalMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			(*(m_QuietCriticalMoves[static_cast<size_t>(currentPass)]))(stack, moves);
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
		static std::string tacticalCriticalEvasionPassToString_Implementation(const passType tacticalCriticalEvasionPass) noexcept;
		static std::string criticalPassToString_Implementation(const passType criticalPass) noexcept;
		static std::string criticalEvasionPassToString_Implementation(const passType criticalEvasionPass) noexcept;
		static std::string quietCriticalPassToString_Implementation(const passType quietCriticalPass) noexcept;
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
			const squaresType knightsDelta{ motorType::move().pieceOccupancyDelta(position, knight, moveBits) };
			const squaresType ownKnights{ (position.pieceOccupancy(knight) ^ knightsDelta) & occOwn };
			const squaresType attackedByOwnKnights{ movegenKnight.attacks(ownKnights,squaresType::all()) };
			if (attackedByOwnKnights[otherking])
				return true;

			// Does he live on a square that is attacked by one of our pawns?
			const squaresType pawnsDelta{ motorType::move().pieceOccupancyDelta(position, pawn, moveBits) };
			const squaresType ownPawns{ (position.pieceOccupancy(pawn) ^ pawnsDelta) & occOwn };
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
			const squaresType unoccupied{ ~occTotal };

			// Is he attacked horizontally by sliding pieces?
			const squaresType queensDelta{ motorType::move().pieceOccupancyDelta(position, queen, moveBits) };
			const squaresType queens{ position.pieceOccupancy(queen) ^ queensDelta };
			const squaresType rooksDelta{ motorType::move().pieceOccupancyDelta(position, rook, moveBits) };
			const squaresType rooks{ position.pieceOccupancy(rook) ^ rooksDelta };
			const squaresType ownSlidersHV = occOwn & (rooks | queens);
			const squaresType criticalSquaresHV{ movegenSlidersHV.inverseAttacks(otherking, unoccupied) };
			if ((criticalSquaresHV & ownSlidersHV) != squaresType::none())
				return true;

			// Is he attacked diagonally by sliding pieces?
			const squaresType bishopsDelta{ motorType::move().pieceOccupancyDelta(position, bishop, moveBits) };
			const squaresType bishops{ position.pieceOccupancy(bishop) ^ bishopsDelta };
			const squaresType ownSlidersDiag = occOwn & (bishops | queens);
			const squaresType criticalSquaresDiag{ movegenSlidersDiag.inverseAttacks(otherking, unoccupied) };
			if ((criticalSquaresDiag & ownSlidersDiag) != squaresType::none())
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