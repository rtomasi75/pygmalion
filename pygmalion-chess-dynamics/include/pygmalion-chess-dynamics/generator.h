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
		using tropismType = tropism<maxTopismDistance, generator>;
		class context :
			public pygmalion::generator<descriptor_dynamics, generator>::context
		{
		private:
		public:
			context() noexcept :
				pygmalion::generator<descriptor_dynamics, generator>::context()
			{
			}
			~context() noexcept = default;
		};
		using contextType = context;
		template<size_t PLAYER>
		class stack :
			public pygmalion::generator<descriptor_dynamics, generator>::stack<PLAYER>
		{
		private:
			mutable std::array<squaresType, countPlayers> m_SquaresAttackedByPlayer;
			mutable std::array<squaresType, countPlayers> m_SquaresTargetedByPlayer;
			mutable std::array<squaresType, countPlayers> m_ControlledByPlayer;
			mutable std::array<squareType, countPlayers> m_KingSquare;
			mutable std::array<bool, countPlayers> m_IsKingSquareValid{ arrayhelper::make<countPlayers,bool>(false) };
			mutable std::array<bool, countPlayers> m_SquaresAttackedByPlayerValid{ arrayhelper::make<countPlayers,bool>(false) };
			mutable std::array<bool, countPlayers> m_SquaresTargetedByPlayerValid{ arrayhelper::make<countPlayers,bool>(false) };
			mutable bool m_IsControlValid{ false };
		public:
			using parentType = stack<static_cast<size_t>(static_cast<playerType>(PLAYER).previous())>;
			void control(squaresType& white, squaresType& black) const noexcept
			{
				if (!m_IsControlValid)
				{
					generatorType::template control<PLAYER>(*this, m_ControlledByPlayer[whitePlayer], m_ControlledByPlayer[blackPlayer]);
					m_IsControlValid = true;
				}
				white = m_ControlledByPlayer[whitePlayer];
				black = m_ControlledByPlayer[blackPlayer];
			}
			squareType kingSquare(const playerType player) const noexcept
			{
				if (!m_IsKingSquareValid[player])
				{
					m_KingSquare[player] = this->position().kingSquare(player);
					m_IsKingSquareValid[player] = true;
				}
				return m_KingSquare[player];
			}
			template<size_t ATTACKER>
			squaresType squaresTargetedByPlayer() const
			{
				constexpr const playerType attacker{ static_cast<playerType>(ATTACKER) };
				if (!m_SquaresTargetedByPlayerValid[attacker])
				{
					m_SquaresTargetedByPlayer[attacker] = generatorType::template squaresTargetedByPlayer<PLAYER, ATTACKER>(*this);
					m_SquaresTargetedByPlayerValid[attacker] = true;
				}
				return m_SquaresTargetedByPlayer[attacker];
			}
			template<size_t ATTACKER>
			squaresType squaresAttackedByPlayer() const
			{
				constexpr const playerType attacker{ static_cast<playerType>(ATTACKER) };
				if (!m_SquaresAttackedByPlayerValid[attacker])
				{
					m_SquaresAttackedByPlayer[attacker] = generatorType::template squaresAttackedByPlayer<PLAYER, ATTACKER>(*this);
					m_SquaresAttackedByPlayerValid[attacker] = true;
				}
				return m_SquaresAttackedByPlayer[attacker];
			}
			stack(const parentType& parent, const movebitsType movebits) noexcept :
				pygmalion::generator<descriptor_dynamics, generator>::stack<PLAYER>(parent, movebits)
			{
			}
			stack(boardType& position, historyType& history, contextType* pContext) noexcept :
				pygmalion::generator<descriptor_dynamics, generator>::stack<PLAYER>(position, history, pContext)
			{
			}
			~stack() noexcept = default;
		};
		template<size_t PLAYER>
		using stackType = stack<PLAYER>;
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
			constexpr const squaresType none{ squaresType::none() };
			squaresType squares{ none };
			for (rankType rank = 2; rank < (countRanks - 1); rank++)
				squares |= static_cast<squaresType>(rank);
			return squares;
		}
		constexpr static const squaresType pawnFromSquaresWhite() noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType squares{ none };
			for (rankType rank = 1; rank < (countRanks - 2); rank++)
				squares |= static_cast<squaresType>(rank);
			return squares;
		}
		constexpr static const squaresType pawnDoublePushFromSquaresBlack() noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType squares{ none };
			squares |= static_cast<squaresType>(static_cast<rankType>(countRanks - 2));
			return squares;
		}
		constexpr static const squaresType pawnDoublePushFromSquaresWhite() noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType squares{ none };
			squares |= static_cast<squaresType>(static_cast<rankType>(1));
			return squares;
		}
		constexpr static const movebitsType m_NullMove{ motorType::move().createNull() };
		constexpr static const std::array<squaresType, 64> m_KingArea
		{
			arrayhelper::generate<64,squaresType>([](const size_t index)
				{
					const squareType sq{static_cast<squareType>(index)};
					squaresType area{ squaresType(sq) };
					area |= area.left() | area.right();
					area |= area.down() | area.up();
					return area;
				})
		};
	public:
		constexpr static squaresType kingArea(const squareType sq) noexcept
		{
			return m_KingArea[sq];
		}
		template<size_t PLAYER>
		constexpr static squaresType pawnPushTargets(const squareType sq, const squaresType& allowed) noexcept
		{
			constexpr const playerType player{ static_cast<playerType>(PLAYER) };
			if constexpr (player == whitePlayer)
				return movegenPawnPushWhite.targets(sq, allowed);
			else
				return movegenPawnPushBlack.targets(sq, allowed);
		}
		template<size_t PLAYER>
		constexpr static squaresType pawnCaptureTargets(const squaresType& squares, const squaresType& allowed) noexcept
		{
			constexpr const playerType player{ static_cast<playerType>(PLAYER) };
			if constexpr (player == whitePlayer)
				return movegenPawnCaptureWhite.attacks(squares, allowed);
			else
				return movegenPawnCaptureBlack.attacks(squares, allowed);
		}
		template<size_t PLAYER>
		constexpr static squaresType pawnDoublePushTargets(const squareType sq, const squaresType& allowed) noexcept
		{
			constexpr const playerType player{ static_cast<playerType>(PLAYER) };
			if constexpr (player == whitePlayer)
				return movegenPawnDoublePushWhite.targets(sq, allowed);
			else
				return movegenPawnDoublePushBlack.targets(sq, allowed);
		}
	private:
		template<size_t PLAYER>
		static void control(const stackType<PLAYER>& stack, squaresType& whiteControl, squaresType& blackControl) noexcept
		{
			const squaresType unoccupied{ ~stack.position().totalOccupancy() };
			const squaresType whiteOcc{ stack.position().playerOccupancy(whitePlayer) };
			const squaresType blackOcc{ stack.position().playerOccupancy(blackPlayer) };
			const squaresType pawnOcc{ stack.position().pieceOccupancy(pawn) };
			const squaresType whitePawns{ whiteOcc & pawnOcc };
			const squaresType blackPawns{ blackOcc & pawnOcc };
			const squaresType whiteRightAttacks{ whitePawns.upRight() };
			const squaresType whiteLeftAttacks{ whitePawns.upLeft() };
			const squaresType blackRightAttacks{ blackPawns.downRight() };
			const squaresType blackLeftAttacks{ blackPawns.downLeft() };
			const squaresType whiteSingleAttacks{ whiteLeftAttacks ^ whiteRightAttacks };
			const squaresType whiteDoubleAttacks{ whiteLeftAttacks & whiteRightAttacks };
			const squaresType blackSingleAttacks{ blackLeftAttacks ^ blackRightAttacks };
			const squaresType blackDoubleAttacks{ blackLeftAttacks & blackRightAttacks };
			constexpr const squaresType all{ squaresType::all() };
			squaresType open{ all };
			constexpr const squaresType none{ squaresType::none() };
			whiteControl = none;
			blackControl = none;
			const squaresType balancedDoubleAttacks{ ~(whiteDoubleAttacks & blackDoubleAttacks) };
			whiteControl |= open & whiteDoubleAttacks & balancedDoubleAttacks;
			blackControl |= open & blackDoubleAttacks & balancedDoubleAttacks;
			open &= ~(whiteControl | blackControl);
			const squaresType balancedSingleAttacks{ ~(whiteSingleAttacks & blackSingleAttacks) };
			whiteControl |= open & whiteSingleAttacks & balancedSingleAttacks;
			blackControl |= open & blackSingleAttacks & balancedSingleAttacks;
			open &= ~(whiteControl | blackControl);

			const squaresType knightOcc{ stack.position().pieceOccupancy(knight) };
			const squaresType whiteKnights{ whiteOcc & knightOcc };
			const squaresType blackKnights{ blackOcc & knightOcc };
			const squaresType bishopOcc{ stack.position().pieceOccupancy(bishop) };
			const squaresType whiteBishops{ whiteOcc & bishopOcc };
			const squaresType blackBishops{ blackOcc & bishopOcc };
			squaresType attackedBy1WhiteKnightOrBishop{ none };
			squaresType attackedBy2WhiteKnightOrBishop{ none };
			squaresType attackedBy3WhiteKnightOrBishop{ none };
			squaresType attackedBy4WhiteKnightOrBishop{ none };
			squaresType attackedBy1BlackKnightOrBishop{ none };
			squaresType attackedBy2BlackKnightOrBishop{ none };
			squaresType attackedBy3BlackKnightOrBishop{ none };
			squaresType attackedBy4BlackKnightOrBishop{ none };
			for (squareType sq : whiteKnights)
			{
				const squaresType attacks{ generatorType::movegenKnight.attacks(sq,all) };
				attackedBy4WhiteKnightOrBishop |= attacks & attackedBy3WhiteKnightOrBishop;
				attackedBy3WhiteKnightOrBishop |= attacks & attackedBy2WhiteKnightOrBishop;
				attackedBy2WhiteKnightOrBishop |= attacks & attackedBy1WhiteKnightOrBishop;
				attackedBy1WhiteKnightOrBishop |= attacks;
			}
			for (squareType sq : whiteBishops)
			{
				const squaresType attacks{ generatorType::movegenSlidersDiag.attacks(sq,unoccupied) };
				attackedBy4WhiteKnightOrBishop |= attacks & attackedBy3WhiteKnightOrBishop;
				attackedBy3WhiteKnightOrBishop |= attacks & attackedBy2WhiteKnightOrBishop;
				attackedBy2WhiteKnightOrBishop |= attacks & attackedBy1WhiteKnightOrBishop;
				attackedBy1WhiteKnightOrBishop |= attacks;
			}
			attackedBy3WhiteKnightOrBishop &= ~attackedBy4WhiteKnightOrBishop;
			attackedBy2WhiteKnightOrBishop &= ~attackedBy3WhiteKnightOrBishop;
			attackedBy1WhiteKnightOrBishop &= ~attackedBy2WhiteKnightOrBishop;
			for (squareType sq : blackKnights)
			{
				const squaresType attacks{ generatorType::movegenKnight.attacks(sq,all) };
				attackedBy4BlackKnightOrBishop |= attacks & attackedBy3BlackKnightOrBishop;
				attackedBy3BlackKnightOrBishop |= attacks & attackedBy2BlackKnightOrBishop;
				attackedBy2BlackKnightOrBishop |= attacks & attackedBy1BlackKnightOrBishop;
				attackedBy1BlackKnightOrBishop |= attacks;
			}
			for (squareType sq : blackBishops)
			{
				const squaresType attacks{ generatorType::movegenSlidersDiag.attacks(sq,unoccupied) };
				attackedBy4BlackKnightOrBishop |= attacks & attackedBy3BlackKnightOrBishop;
				attackedBy3BlackKnightOrBishop |= attacks & attackedBy2BlackKnightOrBishop;
				attackedBy2BlackKnightOrBishop |= attacks & attackedBy1BlackKnightOrBishop;
				attackedBy1BlackKnightOrBishop |= attacks;
			}
			attackedBy3BlackKnightOrBishop &= ~attackedBy4BlackKnightOrBishop;
			attackedBy2BlackKnightOrBishop &= ~attackedBy3BlackKnightOrBishop;
			attackedBy1BlackKnightOrBishop &= ~attackedBy2BlackKnightOrBishop;
			const squaresType balanced4KnightOrBishopAttacks{ ~(attackedBy4WhiteKnightOrBishop & attackedBy4BlackKnightOrBishop) };
			whiteControl |= open & attackedBy4WhiteKnightOrBishop & balanced4KnightOrBishopAttacks;
			blackControl |= open & attackedBy4BlackKnightOrBishop & balanced4KnightOrBishopAttacks;
			open &= ~(whiteControl | blackControl);
			const squaresType balanced3KnightOrBishopAttacks{ ~(attackedBy3WhiteKnightOrBishop & attackedBy3BlackKnightOrBishop) };
			whiteControl |= open & attackedBy3WhiteKnightOrBishop & balanced3KnightOrBishopAttacks;
			blackControl |= open & attackedBy3BlackKnightOrBishop & balanced3KnightOrBishopAttacks;
			open &= ~(whiteControl | blackControl);
			const squaresType balanced2KnightOrBishopAttacks{ ~(attackedBy2WhiteKnightOrBishop & attackedBy2BlackKnightOrBishop) };
			whiteControl |= open & attackedBy2WhiteKnightOrBishop & balanced2KnightOrBishopAttacks;
			blackControl |= open & attackedBy2BlackKnightOrBishop & balanced2KnightOrBishopAttacks;
			open &= ~(whiteControl | blackControl);
			const squaresType balanced1KnightOrBishopAttacks{ ~(attackedBy1WhiteKnightOrBishop & attackedBy1BlackKnightOrBishop) };
			whiteControl |= open & attackedBy1WhiteKnightOrBishop & balanced1KnightOrBishopAttacks;
			blackControl |= open & attackedBy1BlackKnightOrBishop & balanced1KnightOrBishopAttacks;
			open &= ~(whiteControl | blackControl);

			const squaresType rookOcc{ stack.position().pieceOccupancy(rook) };
			const squaresType whiteRooks{ whiteOcc & rookOcc };
			const squaresType blackRooks{ blackOcc & rookOcc };
			squaresType attackedBy2WhiteRook{ none };
			squaresType attackedBy2BlackRook{ none };
			squaresType attackedBy1WhiteRook{ none };
			squaresType attackedBy1BlackRook{ none };
			for (squareType sq : whiteRooks)
			{
				const squaresType attacks{ generatorType::movegenSlidersHV.attacks(sq,unoccupied) };
				attackedBy2WhiteRook |= attacks & attackedBy1WhiteRook;
				attackedBy1WhiteRook |= attacks;
			}
			for (squareType sq : blackRooks)
			{
				const squaresType attacks{ generatorType::movegenSlidersHV.attacks(sq,unoccupied) };
				attackedBy2BlackRook |= attacks & attackedBy1BlackRook;
				attackedBy1BlackRook |= attacks;
			}
			const squaresType balanced2RookAttacks{ ~(attackedBy2WhiteRook & attackedBy2BlackRook) };
			whiteControl |= open & attackedBy2WhiteRook & balanced2RookAttacks;
			blackControl |= open & attackedBy2BlackRook & balanced2RookAttacks;
			open &= ~(whiteControl | blackControl);
			const squaresType balanced1RookAttacks{ ~(attackedBy1WhiteRook & attackedBy1BlackRook) };
			whiteControl |= open & attackedBy1WhiteRook & balanced1RookAttacks;
			blackControl |= open & attackedBy1BlackRook & balanced1RookAttacks;
			open &= ~(whiteControl | blackControl);

			const squaresType queenOcc{ stack.position().pieceOccupancy(queen) };
			const squaresType whiteQueens{ whiteOcc & queenOcc };
			const squaresType blackQueens{ blackOcc & queenOcc };
			squaresType attackedByWhiteQueen{ none };
			squaresType attackedByBlackQueen{ none };
			for (squareType sq : whiteQueens)
			{
				const squaresType attacks{ generatorType::movegenSlidersDiag.attacks(sq,unoccupied) | generatorType::movegenSlidersHV.attacks(sq,unoccupied) };
				attackedByWhiteQueen |= attacks;
			}
			for (squareType sq : blackQueens)
			{
				const squaresType attacks{ generatorType::movegenSlidersDiag.attacks(sq,unoccupied) | generatorType::movegenSlidersHV.attacks(sq,unoccupied) };
				attackedByBlackQueen |= attacks;
			}
			const squaresType balancedQueenAttacks{ ~(attackedByWhiteQueen & attackedByBlackQueen) };
			whiteControl |= open & attackedByWhiteQueen & balancedQueenAttacks;
			blackControl |= open & attackedByBlackQueen & balancedQueenAttacks;
			open &= ~(whiteControl | blackControl);

			const squaresType whiteKingAttacks{ generatorType::movegenKing.attacks(stack.kingSquare(whitePlayer),all) };
			const squaresType blackKingAttacks{ generatorType::movegenKing.attacks(stack.kingSquare(blackPlayer),all) };
			const squaresType balancedKingAttacks{ ~(whiteKingAttacks & blackKingAttacks) };
			whiteControl |= open & whiteKingAttacks & balancedKingAttacks;
			blackControl |= open & blackKingAttacks & balancedKingAttacks;
		}
		template<size_t ATTACKER>
		static bool isAttacked(const boardType& position, const squareType square) noexcept
		{
			PYGMALION_ASSERT(square.isValid());
			constexpr const playerType attacker{ static_cast<playerType>(ATTACKER) };
			const squaresType allowed{ ~position.totalOccupancy() };
			if (movegenKnight.attacks(square, allowed) & position.pieceOccupancy(knight) & position.playerOccupancy(attacker))
				return true;
			if (movegenKing.attacks(square, allowed) & position.pieceOccupancy(king) & position.playerOccupancy(attacker))
				return true;
			const squaresType piecemap{ squaresType(square) };
			const squaresType attackerOcc{ position.playerOccupancy(attacker) };
			if constexpr (attacker == whitePlayer)
			{
				const squaresType pawns{ position.pieceOccupancy(pawn) & attackerOcc };
				const squaresType pawnAttacks{ pawns.upLeft() | pawns.upRight() };
				if (pawnAttacks & piecemap)
					return true;
			}
			else
			{
				const squaresType pawns{ position.pieceOccupancy(pawn) & attackerOcc };
				const squaresType temppawns{ pawns.down() };
				const squaresType pawnAttacks{ temppawns.left() | temppawns.right() };
				if (pawnAttacks & piecemap)
					return true;
			}
			const squaresType slidersDiag{ (position.pieceOccupancy(queen) | position.pieceOccupancy(bishop)) & attackerOcc };
			if (movegenSlidersDiag.attacks(square, allowed) & slidersDiag)
				return true;
			const squaresType slidersHV{ (position.pieceOccupancy(queen) | position.pieceOccupancy(rook)) & attackerOcc };
			if (movegenSlidersHV.attacks(square, allowed) & slidersHV)
				return true;
			return false;
		}
		template<size_t PLAYER, size_t ATTACKER>
		static squaresType squaresAttackedByPlayer(const stackType<PLAYER>& stack) noexcept
		{
			constexpr const playerType attackingPlayer{ static_cast<playerType>(ATTACKER) };
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
			if constexpr (attackingPlayer == whitePlayer)
				attacked |= pawns.upLeft() | pawns.upRight();
			else
				attacked |= pawns.downLeft() | pawns.downRight();
			return attacked;
		}
		template<size_t PLAYER, size_t ATTACKER>
		static squaresType squaresTargetedByPlayer(const stackType<PLAYER>& stack) noexcept
		{
			constexpr const playerType attackingPlayer{ static_cast<playerType>(ATTACKER) };
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
			if constexpr (attackingPlayer == whitePlayer)
				attacked |= pawns.upLeft() | pawns.upRight();
			else
				attacked |= pawns.downLeft() | pawns.downRight();
			return attacked;
		}
		template<size_t PLAYER>
		static void generateKingMoves(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			const squareType from{ stack.kingSquare(movingPlayer) };
			const squaresType destinations{ movegenKing.targets(from, ~stack.position().totalOccupancy()) };
			for (const squareType to : destinations)
				moves.add(motorType::move().createQuiet(from, to));
		}
		template<size_t PLAYER>
		static void generateKingCaptures(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType nextPlayer{ movingPlayer.next() };
			const squareType from{ stack.kingSquare(movingPlayer) };
			const squaresType destinations{ movegenKing.attacks(from, ~stack.position().totalOccupancy()) & stack.position().playerOccupancy(nextPlayer) };
			for (const squareType to : destinations)
				moves.add(motorType::move().createCapture(from, to));
		}
		template<size_t PLAYER>
		static void generateCastles(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			if constexpr (movingPlayer == whitePlayer)
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
		template<size_t PLAYER>
		static void generatePawnEnPassant(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			const uint_t<8, false> epFlags{ stack.position().flags().template extractRange<4,11>() };
			if (epFlags)
			{
				constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
				size_t bit;
				if constexpr (movingPlayer == whitePlayer)
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
		template<size_t PLAYER>
		constexpr static void generateKnightMoves(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			for (const squareType from : stack.position().pieceOccupancy(knight)& stack.position().playerOccupancy(movingPlayer))
			{
				for (const squareType to : movegenKnight.targets(from, ~stack.position().totalOccupancy()))
					moves.add(motorType::move().createQuiet(from, to));
			}
		}
		template<size_t PLAYER>
		constexpr static void generateSliderMovesHV(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			for (const squareType from : (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen))& stack.position().playerOccupancy(movingPlayer))
			{
				for (const squareType to : movegenSlidersHV.targets(from, ~stack.position().totalOccupancy()))
					moves.add(motorType::move().createQuiet(from, to));
			}
		}
		template<size_t PLAYER>
		constexpr static void generateSliderMovesDiag(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			for (const squareType from : (stack.position().pieceOccupancy(bishop) | stack.position().pieceOccupancy(queen))& stack.position().playerOccupancy(movingPlayer))
			{
				for (const squareType to : movegenSlidersDiag.targets(from, ~stack.position().totalOccupancy()))
					moves.add(motorType::move().createQuiet(from, to));
			}
		}
		template<size_t PLAYER>
		constexpr static void generateSliderCapturesHV(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType nextPlayer{ movingPlayer.next() };
			for (const squareType from : (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen))& stack.position().playerOccupancy(movingPlayer))
			{
				for (const squareType to : movegenSlidersHV.attacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(nextPlayer))
					moves.add(motorType::move().createCapture(from, to));
			}
		}
		template<size_t PLAYER>
		constexpr static void generateSliderCapturesDiag(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType nextPlayer{ movingPlayer.next() };
			for (const squareType from : (stack.position().pieceOccupancy(bishop) | stack.position().pieceOccupancy(queen))& stack.position().playerOccupancy(movingPlayer))
			{
				for (const squareType to : movegenSlidersDiag.attacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(nextPlayer))
					moves.add(motorType::move().createCapture(from, to));
			}
		}
		template<size_t PLAYER>
		constexpr static void generateKnightCaptures(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType nextPlayer{ movingPlayer.next() };
			for (const squareType from : stack.position().pieceOccupancy(knight)& stack.position().playerOccupancy(movingPlayer))
			{
				for (const squareType to : movegenKnight.attacks(from, ~stack.position().totalOccupancy())& stack.position().playerOccupancy(nextPlayer))
					moves.add(motorType::move().createCapture(from, to));
			}
		}
		template<size_t PLAYER>
		constexpr static void generatePawnPushesWhite(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			const squaresType whitePawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
			for (const squareType to : movegenPawnPushWhite.targets(whitePawns, ~stack.position().totalOccupancy()))
				moves.add(motorType::move().createQuiet(to.down(), to));
		}
		template<size_t PLAYER>
		constexpr static void generatePawnPushesBlack(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			const squaresType blackPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
			for (const squareType to : movegenPawnPushBlack.targets(blackPawns, ~stack.position().totalOccupancy()))
				moves.add(motorType::move().createQuiet(to.up(), to));
		}
		template<size_t PLAYER>
		constexpr static void generatePawnPushes(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			if constexpr (movingPlayer == whitePlayer)
				generatePawnPushesWhite(stack, moves);
			else
				generatePawnPushesBlack(stack, moves);
		}
		template<size_t PLAYER>
		constexpr static void generatePawnPromotionsWhite(const stackType<PLAYER>& stack, movelistType& moves) noexcept
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
		template<size_t PLAYER>
		constexpr static void generatePawnPromotionsBlack(const stackType<PLAYER>& stack, movelistType& moves) noexcept
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
		template<size_t PLAYER>
		constexpr static void generatePawnPromotions(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			if constexpr (movingPlayer == whitePlayer)
				generatePawnPromotionsWhite(stack, moves);
			else
				generatePawnPromotionsBlack(stack, moves);
		}
		template<size_t PLAYER>
		constexpr static void generatePawnCapturesWhite(const stackType<PLAYER>& stack, movelistType& moves) noexcept
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
		template<size_t PLAYER>
		constexpr static void generatePawnCapturesBlack(const stackType<PLAYER>& stack, movelistType& moves) noexcept
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
		template<size_t PLAYER>
		constexpr static void generatePawnCaptures(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			if constexpr (movingPlayer == whitePlayer)
				generatePawnCapturesWhite(stack, moves);
			else
				generatePawnCapturesBlack(stack, moves);
		}
		template<size_t PLAYER>
		constexpr static void generatePawnPromoCapturesWhite(const stackType<PLAYER>& stack, movelistType& moves) noexcept
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
		template<size_t PLAYER>
		constexpr static void generatePawnPromoCapturesBlack(const stackType<PLAYER>& stack, movelistType& moves) noexcept
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
		template<size_t PLAYER>
		constexpr static void generatePawnPromoCaptures(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			if constexpr (movingPlayer == whitePlayer)
				generatePawnPromoCapturesWhite(stack, moves);
			else
				generatePawnPromoCapturesBlack(stack, moves);
		}
		template<size_t PLAYER>
		constexpr static void generatePawnDoublePushesWhite(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			const squaresType whitePawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
			for (const squareType to : movegenPawnDoublePushWhite.targets(whitePawns, ~stack.position().totalOccupancy()))
				moves.add(motorType::move().createDoublePush(to.file()));
		}
		template<size_t PLAYER>
		constexpr static void generatePawnDoublePushesBlack(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			const squaresType blackPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
			for (const squareType to : movegenPawnDoublePushBlack.targets(blackPawns, ~stack.position().totalOccupancy()))
				moves.add(motorType::move().createDoublePush(to.file()));
		}
		template<size_t PLAYER>
		constexpr static void generatePawnDoublePushes(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			if constexpr (movingPlayer == whitePlayer)
				generatePawnDoublePushesWhite(stack, moves);
			else
				generatePawnDoublePushesBlack(stack, moves);
		}
		template<size_t PLAYER>
		static void generateCriticalKnightMoves(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType nextPlayer{ movingPlayer.next() };
			const squaresType ownKnights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(movingPlayer) };
			const squareType otherKing{ stack.kingSquare(nextPlayer) };
			constexpr const squaresType all{ squaresType::all() };
			const squaresType criticalSquares{ movegenKnight.inverseAttacks(otherKing, all) };
			const squaresType criticalTargets{ criticalSquares & ~stack.position().totalOccupancy() };
			const squaresType criticalCaptures{ criticalSquares & stack.position().playerOccupancy(stack.nextPlayer()) };
			for (const auto to : criticalTargets)
			{
				const squaresType origins{ movegenKnight.inverseTargets(to,all) };
				const squaresType movers{ origins & ownKnights };
				for (const auto from : movers)
					moves.add(motorType::move().createQuiet(from, to));
			}
			for (const auto to : criticalCaptures)
			{
				const squaresType origins{ movegenKnight.inverseAttacks(to,all) };
				const squaresType movers{ origins & ownKnights };
				for (const auto from : movers)
					moves.add(motorType::move().createCapture(from, to));
			}
			if constexpr (movingPlayer == whitePlayer)
			{
				const squaresType criticalPromotionSquares{ criticalSquares & rank8 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType criticalPromoCaptures{ criticalPromotionSquares & stack.position().playerOccupancy(blackPlayer) };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionWhite.inverseTargets(to,all) };
					const squaresType movers{ origins & ownPawns };
					for (const auto from : movers)
						moves.add(motorType::move().createPromotionKnight(from, to));
				}
				for (const auto to : criticalPromoCaptures)
				{
					const squaresType origins{ movegenPawnPromoCaptureWhite.inverseAttacks(to,all) };
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
					const squaresType origins{ movegenPawnPromotionBlack.inverseTargets(to,all) };
					const squaresType movers{ origins & ownPawns };
					for (const auto from : movers)
						moves.add(motorType::move().createPromotionKnight(from, to));
				}
				for (const auto to : criticalPromoCaptures)
				{
					const squaresType origins{ movegenPawnPromoCaptureWhite.inverseAttacks(to,all) };
					const squaresType movers{ origins & ownPawns };
					for (const auto from : movers)
						moves.add(motorType::move().createPromoCaptureKnight(from, to));
				}
			}
		}
		template<size_t PLAYER>
		static void generateCriticalPawnMovesWhite(const stackType<PLAYER>& stack, movelistType& moves) noexcept
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
		template<size_t PLAYER>
		static void generateCriticalPawnMovesBlack(const stackType<PLAYER>& stack, movelistType& moves) noexcept
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
		template<size_t PLAYER>
		static void generateCriticalPawnMoves(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			if constexpr (movingPlayer == whitePlayer)
				generateCriticalPawnMovesWhite(stack, moves);
			else
				generateCriticalPawnMovesBlack(stack, moves);
		}
		template<size_t PLAYER>
		static void generateCriticalSliderMovesHV(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType nextPlayer{ movingPlayer.next() };
			const squaresType ownQueens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(movingPlayer) };
			const squaresType ownRooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(movingPlayer) };
			const squaresType ownSlidersHV{ ownQueens | ownRooks };
			const squareType otherKing{ stack.kingSquare(stack.nextPlayer()) };
			const squaresType occupied{ stack.position().totalOccupancy() };
			const squaresType unoccupied{ ~occupied };
			const squaresType criticalSquares{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied) };
			const squaresType criticalTargets{ criticalSquares & unoccupied };
			const squaresType criticalCaptures{ criticalSquares & stack.position().playerOccupancy(nextPlayer) };
			const squaresType discoveryCandidates{ criticalSquares & stack.position().playerOccupancy(movingPlayer) };
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
			constexpr const squaresType all{ squaresType::all() };
			for (const auto from : discoveryCandidates)
			{
				const squaresType discovered{ unoccupied | from };
				const squaresType discoveredRays{ movegenSlidersHV.inverseAttacks(otherKing,discovered) };
				const squaresType discoveredAttacks{ discoveredRays & ownSlidersHV };
				if (discoveredAttacks)
				{
					const pieceType discoveringPiece{ stack.position().getPiece(from) };
					const squareType discoveredSquare{ *discoveredAttacks.begin() };
					const squaresType allowedDestinations{ ~(movegenSlidersHV.attacks(from,discovered) & discoveredRays) };
					switch (discoveringPiece)
					{
					default:
						PYGMALION_UNREACHABLE;
						break;
					case king:
					{
						const squaresType discoveryTargets{ movegenKing.targets(from,all) & allowedDestinations };
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
						const squaresType criticalSquares2{ movegenKnight.inverseAttacks(otherKing, all) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ movegenKnight.targets(from,all) & allowedDestinations2 };
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
						if constexpr (movingPlayer == whitePlayer)
						{
							constexpr const squaresType notRank1{ ~rank1 };
							const squaresType tempSquare{ squaresType(otherKing).down() & notRank1 };
							const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
							const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
							const squaresType discoveryMoves{ movegenPawnPushWhite.targets(from,all) & allowedDestinations2 & unoccupied };
							const squaresType discoveryCaptures{ movegenPawnCaptureWhite.targets(from,all) & allowedDestinations2 & stack.position().playerOccupancy(stack.nextPlayer()) };
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
							const squaresType discoveryMoves{ movegenPawnPushBlack.targets(from,all) & allowedDestinations2 & unoccupied };
							const squaresType discoveryCaptures{ movegenPawnCaptureBlack.targets(from,all) & allowedDestinations2 & stack.position().playerOccupancy(stack.nextPlayer()) };
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
			const uint_t<8, false> epFlags{ stack.position().flags().template extractRange<4,11>() };
			if (epFlags)
			{
				size_t bit;
				if constexpr (movingPlayer == whitePlayer)
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
								if (criticalSquares3 & ownSlidersHV)
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
								if (criticalSquares3 & ownSlidersHV)
									moves.add(mv);
							}
						}
					}
				}
			}
			if constexpr (movingPlayer == whitePlayer)
			{
				const squaresType criticalPromotionSquares{ rank8 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType criticalPromoCaptures{ criticalPromotionSquares & stack.position().playerOccupancy(blackPlayer) };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionWhite.inverseTargets(to,all) };
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
					const squaresType origins{ movegenPawnPromoCaptureWhite.inverseAttacks(to,all) };
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
					const squaresType origins{ movegenPawnPromotionBlack.inverseTargets(to,all) };
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
					const squaresType origins{ movegenPawnPromoCaptureWhite.inverseAttacks(to,all) };
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
			if constexpr (movingPlayer == whitePlayer)
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
		template<size_t PLAYER>
		static void generateCriticalSliderMovesDiag(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType nextPlayer{ movingPlayer.next() };
			const squaresType ownQueens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(movingPlayer) };
			const squaresType ownBishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(movingPlayer) };
			const squaresType ownSlidersDiag{ ownQueens | ownBishops };
			const squareType otherKing{ stack.kingSquare(stack.nextPlayer()) };
			const squaresType unoccupied{ ~stack.position().totalOccupancy() };
			const squaresType criticalSquares{ movegenSlidersDiag.inverseAttacks(otherKing, unoccupied) };
			const squaresType criticalTargets{ criticalSquares & unoccupied };
			const squaresType criticalCaptures{ criticalSquares & stack.position().playerOccupancy(nextPlayer) };
			const squaresType discoveryCandidates{ criticalSquares & stack.position().playerOccupancy(movingPlayer) };
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
				if (discoveredAttacks)
				{
					const pieceType discoveringPiece{ stack.position().getPiece(from) };
					const squareType discoveredSquare{ *discoveredAttacks.begin() };
					const squaresType allowedDestinations{ ~(movegenSlidersDiag.attacks(from,discovered) & discoveredRays) };
					switch (discoveringPiece)
					{
					default:
						PYGMALION_UNREACHABLE;
						break;
					case king:
					{
						const squaresType discoveryTargets{ movegenKing.targets(from,all) & allowedDestinations };
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
						const squaresType criticalSquares2{ movegenKnight.inverseAttacks(otherKing, all) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ movegenKnight.targets(from,all) & allowedDestinations2 };
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
						if constexpr (movingPlayer == whitePlayer)
						{
							constexpr const squaresType notRank1{ ~rank1 };
							const squaresType tempSquare{ squaresType(otherKing).down() & notRank1 };
							const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
							const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
							const squaresType discoveryMoves{ movegenPawnPushWhite.targets(from,all) & allowedDestinations2 & unoccupied };
							const squaresType discoveryCaptures{ movegenPawnCaptureWhite.targets(from,all) & allowedDestinations2 & stack.position().playerOccupancy(stack.nextPlayer()) };
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
							const squaresType discoveryMoves{ movegenPawnPushBlack.targets(from,all) & allowedDestinations2 & unoccupied };
							const squaresType discoveryCaptures{ movegenPawnCaptureBlack.targets(from,all) & allowedDestinations2 & stack.position().playerOccupancy(stack.nextPlayer()) };
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
			const uint_t<8, false> epFlags{ stack.position().flags().template extractRange<4,11>() };
			if (epFlags)
			{
				size_t bit;
				if constexpr (movingPlayer == whitePlayer)
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
								if (criticalSquares3 & ownSlidersDiag)
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
								if (criticalSquares3 & ownSlidersDiag)
									moves.add(mv);
							}
						}
					}
				}
			}
			if constexpr (movingPlayer == whitePlayer)
			{
				const squaresType criticalPromotionSquares{ rank8 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType criticalPromoCaptures{ criticalPromotionSquares & stack.position().playerOccupancy(blackPlayer) };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionWhite.inverseTargets(to,all) };
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
					const squaresType origins{ movegenPawnPromoCaptureWhite.inverseAttacks(to,all) };
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
			else
			{
				const squaresType criticalPromotionSquares{ rank1 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType criticalPromoCaptures{ criticalPromotionSquares & stack.position().playerOccupancy(whitePlayer) };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionBlack.inverseTargets(to,all) };
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
					const squaresType origins{ movegenPawnPromoCaptureWhite.inverseAttacks(to,all) };
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
		template<size_t PLAYER>
		static void generateQuietCriticalKnightMoves(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType nextPlayer{ movingPlayer.next() };
			const squaresType ownKnights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(movingPlayer) };
			const squareType otherKing{ stack.kingSquare(nextPlayer) };
			const squaresType criticalSquares{ movegenKnight.inverseAttacks(otherKing, all) };
			const squaresType criticalTargets{ criticalSquares & ~stack.position().totalOccupancy() };
			for (const auto to : criticalTargets)
			{
				const squaresType origins{ movegenKnight.inverseTargets(to,all) };
				const squaresType movers{ origins & ownKnights };
				for (const auto from : movers)
					moves.add(motorType::move().createQuiet(from, to));
			}
			if constexpr (movingPlayer == whitePlayer)
			{
				const squaresType criticalPromotionSquares{ criticalSquares & rank8 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionWhite.inverseTargets(to,all) };
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
					const squaresType origins{ movegenPawnPromotionBlack.inverseTargets(to,all) };
					const squaresType movers{ origins & ownPawns };
					for (const auto from : movers)
						moves.add(motorType::move().createPromotionKnight(from, to));
				}
			}
		}
		template<size_t PLAYER>
		static void generateQuietCriticalPawnMovesWhite(const stackType<PLAYER>& stack, movelistType& moves) noexcept
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
		template<size_t PLAYER>
		static void generateQuietCriticalPawnMovesBlack(const stackType<PLAYER>& stack, movelistType& moves) noexcept
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
		template<size_t PLAYER>
		static void generateQuietCriticalPawnMoves(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			if constexpr (movingPlayer == whitePlayer)
				generateQuietCriticalPawnMovesWhite(stack, moves);
			else
				generateQuietCriticalPawnMovesBlack(stack, moves);
		}
		template<size_t PLAYER>
		static void generateQuietCriticalSliderMovesHV(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType nextPlayer{ movingPlayer.next() };
			const squaresType ownQueens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(movingPlayer) };
			const squaresType ownRooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(movingPlayer) };
			const squaresType ownSlidersHV{ ownQueens | ownRooks };
			const squareType otherKing{ stack.kingSquare(stack.nextPlayer()) };
			const squaresType occupied{ stack.position().totalOccupancy() };
			const squaresType unoccupied{ ~occupied };
			const squaresType criticalSquares{ movegenSlidersHV.inverseAttacks(otherKing, unoccupied) };
			const squaresType criticalTargets{ criticalSquares & unoccupied };
			const squaresType discoveryCandidates{ criticalSquares & stack.position().playerOccupancy(movingPlayer) };
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
				if (discoveredAttacks)
				{
					const pieceType discoveringPiece{ stack.position().getPiece(from) };
					const squareType discoveredSquare{ *discoveredAttacks.begin() };
					const squaresType allowedDestinations{ ~(movegenSlidersHV.attacks(from,discovered) & discoveredRays) };
					switch (discoveringPiece)
					{
					default:
						PYGMALION_UNREACHABLE;
						break;
					case king:
					{
						const squaresType discoveryTargets{ movegenKing.targets(from,all) & allowedDestinations };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						break;
					}
					case knight:
					{
						const squaresType criticalSquares2{ movegenKnight.inverseAttacks(otherKing, all) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ movegenKnight.targets(from,all) & allowedDestinations2 };
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
						if constexpr (movingPlayer == whitePlayer)
						{
							constexpr const squaresType notRank1{ ~rank1 };
							const squaresType tempSquare{ squaresType(otherKing).down() & notRank1 };
							const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
							const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
							const squaresType discoveryMoves{ movegenPawnPushWhite.targets(from,all) & allowedDestinations2 & unoccupied };
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
							const squaresType discoveryMoves{ movegenPawnPushBlack.targets(from,all) & allowedDestinations2 & unoccupied };
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
			if constexpr (movingPlayer == whitePlayer)
			{
				const squaresType criticalPromotionSquares{ rank8 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionWhite.inverseTargets(to,all) };
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
					const squaresType origins{ movegenPawnPromotionBlack.inverseTargets(to,all) };
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
			if constexpr (movingPlayer == whitePlayer)
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
		template<size_t PLAYER>
		static void generateQuietCriticalSliderMovesDiag(const stackType<PLAYER>& stack, movelistType& moves) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType nextPlayer{ movingPlayer.next() };
			const squaresType ownQueens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(movingPlayer) };
			const squaresType ownBishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(movingPlayer) };
			const squaresType ownSlidersDiag{ ownQueens | ownBishops };
			const squareType otherKing{ stack.kingSquare(stack.nextPlayer()) };
			const squaresType unoccupied{ ~stack.position().totalOccupancy() };
			const squaresType criticalSquares{ movegenSlidersDiag.inverseAttacks(otherKing, unoccupied) };
			const squaresType criticalTargets{ criticalSquares & unoccupied };
			const squaresType discoveryCandidates{ criticalSquares & stack.position().playerOccupancy(movingPlayer) };
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
				if (discoveredAttacks)
				{
					const pieceType discoveringPiece{ stack.position().getPiece(from) };
					const squareType discoveredSquare{ *discoveredAttacks.begin() };
					const squaresType allowedDestinations{ ~(movegenSlidersDiag.attacks(from,discovered) & discoveredRays) };
					switch (discoveringPiece)
					{
					default:
						PYGMALION_UNREACHABLE;
						break;
					case king:
					{
						const squaresType discoveryTargets{ movegenKing.targets(from,all) & allowedDestinations };
						const squaresType discoveryMoves{ discoveryTargets & unoccupied };
						for (const auto to : discoveryMoves)
							moves.add(motorType::move().createQuiet(from, to));
						break;
					}
					case knight:
					{
						const squaresType criticalSquares2{ movegenKnight.inverseAttacks(otherKing, all) };
						const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
						const squaresType discoveryTargets{ movegenKnight.targets(from,all) & allowedDestinations2 };
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
						if constexpr (movingPlayer == whitePlayer)
						{
							constexpr const squaresType notRank1{ ~rank1 };
							const squaresType tempSquare{ squaresType(otherKing).down() & notRank1 };
							const squaresType criticalSquares2{ tempSquare.left() | tempSquare.right() };
							const squaresType allowedDestinations2{ allowedDestinations & ~criticalSquares2 };
							const squaresType discoveryMoves{ movegenPawnPushWhite.targets(from,all) & allowedDestinations2 & unoccupied };
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
							const squaresType discoveryMoves{ movegenPawnPushBlack.targets(from,all) & allowedDestinations2 & unoccupied };
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
			if constexpr (movingPlayer == whitePlayer)
			{
				const squaresType criticalPromotionSquares{ rank8 };
				const squaresType criticalPromotions{ criticalPromotionSquares & ~stack.position().totalOccupancy() };
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
				for (const auto to : criticalPromotions)
				{
					const squaresType origins{ movegenPawnPromotionWhite.inverseTargets(to,all) };
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
					const squaresType origins{ movegenPawnPromotionBlack.inverseTargets(to,all) };
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
		static squaresType tropismKing(const squaresType& sq) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			return movegenKing.inverseAttacks(sq, all);
		}
		static squaresType tropismKing(const squareType sq) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			return movegenKing.inverseAttacks(sq, all);
		}
		static squaresType tropismKnight(const squareType sq) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			return movegenKnight.inverseAttacks(sq, all);
		}
		static squaresType tropismKnight(const squaresType& sq) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			return movegenKnight.inverseAttacks(sq, all);
		}
		static squaresType tropismBishop(const squareType sq, const squaresType& unoccupiedSquares) noexcept
		{
			return movegenSlidersDiag.inverseAttacks(sq, unoccupiedSquares);
		}
		static squaresType tropismBishop(const squaresType& sq, const squaresType& unoccupiedSquares) noexcept
		{
			return movegenSlidersDiag.inverseAttacks(sq, unoccupiedSquares);
		}
		static squaresType tropismRook(const squareType sq, const squaresType& unoccupiedSquares) noexcept
		{
			return movegenSlidersHV.inverseAttacks(sq, unoccupiedSquares);
		}
		static squaresType tropismRook(const squaresType& sq, const squaresType& unoccupiedSquares) noexcept
		{
			return movegenSlidersHV.inverseAttacks(sq, unoccupiedSquares);
		}
		static squaresType tropismQueen(const squareType sq, const squaresType& unoccupiedSquares) noexcept
		{
			return movegenSlidersHV.inverseAttacks(sq, unoccupiedSquares) | movegenSlidersDiag.inverseAttacks(sq, unoccupiedSquares);
		}
		static squaresType tropismQueen(const squaresType& sq, const squaresType& unoccupiedSquares) noexcept
		{
			return movegenSlidersHV.inverseAttacks(sq, unoccupiedSquares) | movegenSlidersDiag.inverseAttacks(sq, unoccupiedSquares);
		}
		static squaresType tropismPawn(const squareType sq, const playerType pl, const squaresType& unoccupiedSquares, const squaresType& victims) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			squaresType tropism;
			const rankType rank{ sq.rank() };
			if (pl == whitePlayer)
			{
				if (victims[sq])
					tropism = rank != rank8 ? movegenPawnCaptureWhite.inverseAttacks(sq, all) : movegenPawnPromoCaptureWhite.inverseAttacks(sq, all);
				else
				{
					tropism = rank != rank8 ? movegenPawnPushWhite.inverseTargets(sq, all) : movegenPawnPromotionWhite.inverseTargets(sq, all);
					if (rank == rank4)
						tropism |= movegenPawnDoublePushWhite.inverseAttacks(sq, unoccupiedSquares);
				}
			}
			else
			{
				if (victims[sq])
					tropism = rank != rank1 ? movegenPawnCaptureBlack.inverseAttacks(sq, all) : movegenPawnPromoCaptureBlack.inverseAttacks(sq, all);
				else
				{
					tropism = rank != rank1 ? movegenPawnPushBlack.inverseTargets(sq, all) : movegenPawnPromotionBlack.inverseTargets(sq, all);
					if (rank == rank5)
						tropism |= movegenPawnDoublePushBlack.inverseAttacks(sq, unoccupiedSquares);
				}
			}
			return tropism;
		}
		static squaresType tropismPawn(const squaresType& sq, const playerType pl, const squaresType& unoccupiedSquares, const squaresType& victims) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			constexpr const squaresType none{ squaresType::none() };
			squaresType tropism{ none };
			const squaresType pushDestinations{ sq & ~victims };
			const squaresType captureDestinations{ sq & victims };
			if (pl == whitePlayer)
			{
				if (pushDestinations)
				{
					tropism |= movegenPawnPushWhite.inverseTargets(pushDestinations & ~rank8, all) | movegenPawnPromotionWhite.inverseTargets(pushDestinations & rank8, all);
					tropism |= movegenPawnDoublePushWhite.inverseAttacks(pushDestinations & rank4, unoccupiedSquares);
				}
				if (captureDestinations)
					tropism |= movegenPawnCaptureWhite.inverseAttacks(captureDestinations & ~rank8, all) | movegenPawnPromoCaptureWhite.inverseAttacks(captureDestinations & rank8, all);
				return tropism;
			}
			else
			{
				if (pushDestinations)
				{
					tropism |= movegenPawnPushBlack.inverseTargets(pushDestinations & ~rank1, all) | movegenPawnPromotionBlack.inverseTargets(pushDestinations & rank1, all);
					tropism |= movegenPawnDoublePushBlack.inverseAttacks(pushDestinations & rank5, unoccupiedSquares);
				}
				if (captureDestinations)
					tropism |= movegenPawnCaptureBlack.inverseAttacks(captureDestinations & ~rank1, all) | movegenPawnPromoCaptureBlack.inverseAttacks(captureDestinations & rank1, all);
				return tropism;
			}
		}
	public:
		template<unsigned MAXDIST>
		static void attackTropismKing(const squareType sq, const playerType pl, const squaresType& allowedSquares, std::array<squaresType, MAXDIST + 1>& tropism) noexcept
		{
			tropism[0] = tropismKing(sq);
			if constexpr (MAXDIST > 0)
			{
				std::array<squaresType, MAXDIST> visited;
				visited[0] = tropism[0];
				for (unsigned i = 1; i < MAXDIST; i++)
				{
					tropism[i] = tropismKing(tropism[i - 1] & allowedSquares) & ~visited[i - 1];
					visited[i] = visited[i - 1] | tropism[i];
				}
				tropism[MAXDIST] = tropismKing(tropism[MAXDIST - 1] & allowedSquares) & ~visited[MAXDIST - 1];
			}
		}
		template<unsigned MAXDIST>
		static void attackTropismKing(const squaresType& sq, const playerType pl, const squaresType& allowedSquares, std::array<squaresType, MAXDIST + 1>& tropism) noexcept
		{
			tropism[0] = tropismKing(sq);
			if constexpr (MAXDIST > 0)
			{
				std::array<squaresType, MAXDIST> visited;
				visited[0] = tropism[0];
				for (unsigned i = 1; i < MAXDIST; i++)
				{
					tropism[i] = tropismKing(tropism[i - 1] & allowedSquares) & ~visited[i - 1];
					visited[i] = visited[i - 1] | tropism[i];
				}
				tropism[MAXDIST] = tropismKing(tropism[MAXDIST - 1] & allowedSquares) & ~visited[MAXDIST - 1];
			}
		}
		template<unsigned MAXDIST>
		static void attackTropismKnight(const squareType sq, const playerType pl, const squaresType& allowedSquares, std::array<squaresType, MAXDIST + 1>& tropism) noexcept
		{
			tropism[0] = tropismKnight(sq);
			if constexpr (MAXDIST > 0)
			{
				std::array<squaresType, MAXDIST> visited;
				visited[0] = tropism[0];
				for (unsigned i = 1; i < MAXDIST; i++)
				{
					tropism[i] = tropismKnight(tropism[i - 1] & allowedSquares) & ~visited[i - 1];
					visited[i] = visited[i - 1] | tropism[i];
				}
				tropism[MAXDIST] = tropismKnight(tropism[MAXDIST - 1] & allowedSquares) & ~visited[MAXDIST - 1];
			}
		}
		template<unsigned MAXDIST>
		static void attackTropismKnight(const squaresType& sq, const playerType pl, const squaresType& allowedSquares, std::array<squaresType, MAXDIST + 1>& tropism) noexcept
		{
			tropism[0] = tropismKnight(sq);
			if constexpr (MAXDIST > 0)
			{
				std::array<squaresType, MAXDIST> visited;
				visited[0] = tropism[0];
				for (unsigned i = 1; i < MAXDIST; i++)
				{
					tropism[i] = tropismKnight(tropism[i - 1] & allowedSquares) & ~visited[i - 1];
					visited[i] = visited[i - 1] | tropism[i];
				}
				tropism[MAXDIST] = tropismKnight(tropism[MAXDIST - 1] & allowedSquares) & ~visited[MAXDIST - 1];
			}
		}
		template<unsigned MAXDIST>
		static void attackTropismRook(const squareType sq, const playerType pl, const squaresType& allowedSquares, const squaresType& unoccupiedSquares, std::array<squaresType, MAXDIST + 1>& tropism) noexcept
		{
			tropism[0] = tropismRook(sq, unoccupiedSquares);
			if constexpr (MAXDIST > 0)
			{
				std::array<squaresType, MAXDIST> visited;
				visited[0] = tropism[0];
				for (unsigned i = 1; i < MAXDIST; i++)
				{
					tropism[i] = tropismRook(tropism[i - 1] & allowedSquares, unoccupiedSquares) & ~visited[i - 1];
					visited[i] = visited[i - 1] | tropism[i];
				}
				tropism[MAXDIST] = tropismRook(tropism[MAXDIST - 1] & allowedSquares, unoccupiedSquares) & ~visited[MAXDIST - 1];
			}
		}
		template<unsigned MAXDIST>
		static void attackTropismRook(const squaresType& sq, const playerType pl, const squaresType& allowedSquares, const squaresType& unoccupiedSquares, std::array<squaresType, MAXDIST + 1>& tropism) noexcept
		{
			tropism[0] = tropismRook(sq, unoccupiedSquares);
			if constexpr (MAXDIST > 0)
			{
				std::array<squaresType, MAXDIST> visited;
				visited[0] = tropism[0];
				for (unsigned i = 1; i < MAXDIST; i++)
				{
					tropism[i] = tropismRook(tropism[i - 1] & allowedSquares, unoccupiedSquares) & ~visited[i - 1];
					visited[i] = visited[i - 1] | tropism[i];
				}
				tropism[MAXDIST] = tropismRook(tropism[MAXDIST - 1] & allowedSquares, unoccupiedSquares) & ~visited[MAXDIST - 1];
			}
		}
		template<unsigned MAXDIST>
		static void attackTropismBishop(const squareType sq, const playerType pl, const squaresType& allowedSquares, const squaresType& unoccupiedSquares, std::array<squaresType, MAXDIST + 1>& tropism) noexcept
		{
			tropism[0] = tropismBishop(sq, unoccupiedSquares);
			if constexpr (MAXDIST > 0)
			{
				std::array<squaresType, MAXDIST> visited;
				visited[0] = tropism[0];
				for (unsigned i = 1; i < MAXDIST; i++)
				{
					tropism[i] = tropismBishop(tropism[i - 1] & allowedSquares, unoccupiedSquares) & ~visited[i - 1];
					visited[i] = visited[i - 1] | tropism[i];
				}
				tropism[MAXDIST] = tropismBishop(tropism[MAXDIST - 1] & allowedSquares, unoccupiedSquares) & ~visited[MAXDIST - 1];
			}
		}
		template<unsigned MAXDIST>
		static void attackTropismBishop(const squaresType& sq, const playerType pl, const squaresType& allowedSquares, const squaresType& unoccupiedSquares, std::array<squaresType, MAXDIST + 1>& tropism) noexcept
		{
			tropism[0] = tropismBishop(sq, unoccupiedSquares);
			if constexpr (MAXDIST > 0)
			{
				std::array<squaresType, MAXDIST> visited;
				visited[0] = tropism[0];
				for (unsigned i = 1; i < MAXDIST; i++)
				{
					tropism[i] = tropismBishop(tropism[i - 1] & allowedSquares, unoccupiedSquares) & ~visited[i - 1];
					visited[i] = visited[i - 1] | tropism[i];
				}
				tropism[MAXDIST] = tropismBishop(tropism[MAXDIST - 1] & allowedSquares, unoccupiedSquares) & ~visited[MAXDIST - 1];
			}
		}
		template<unsigned MAXDIST>
		static void attackTropismQueen(const squareType sq, const playerType pl, const squaresType& allowedSquares, const squaresType& unoccupiedSquares, std::array<squaresType, MAXDIST + 1>& tropism) noexcept
		{
			tropism[0] = tropismQueen(sq, unoccupiedSquares);
			if constexpr (MAXDIST > 0)
			{
				std::array<squaresType, MAXDIST> visited;
				visited[0] = tropism[0];
				for (unsigned i = 1; i < MAXDIST; i++)
				{
					tropism[i] = tropismQueen(tropism[i - 1] & allowedSquares, unoccupiedSquares) & ~visited[i - 1];
					visited[i] = visited[i - 1] | tropism[i];
				}
				tropism[MAXDIST] = tropismQueen(tropism[MAXDIST - 1] & allowedSquares, unoccupiedSquares) & ~visited[MAXDIST - 1];
			}
		}
		template<unsigned MAXDIST>
		static void attackTropismQueen(const squaresType& sq, const playerType pl, const squaresType& allowedSquares, const squaresType& unoccupiedSquares, std::array<squaresType, MAXDIST + 1>& tropism) noexcept
		{
			tropism[0] = tropismQueen(sq, unoccupiedSquares);
			if constexpr (MAXDIST > 0)
			{
				std::array<squaresType, MAXDIST> visited;
				visited[0] = tropism[0];
				for (unsigned i = 1; i < MAXDIST; i++)
				{
					tropism[i] = tropismQueen(tropism[i - 1] & allowedSquares, unoccupiedSquares) & ~visited[i - 1];
					visited[i] = visited[i - 1] | tropism[i];
				}
				tropism[MAXDIST] = tropismQueen(tropism[MAXDIST - 1] & allowedSquares, unoccupiedSquares) & ~visited[MAXDIST - 1];
			}
		}
		template<unsigned MAXDIST>
		static void attackTropismPawn(const squareType sq, const playerType pl, const squaresType& allowedSquares, const squaresType& unoccupiedSquares, const squaresType& victims, const std::array<squaresType, MAXDIST + 1>& tropismKnight, const std::array<squaresType, MAXDIST + 1>& tropismBishop, const std::array<squaresType, MAXDIST + 1>& tropismRook, const std::array<squaresType, MAXDIST + 1>& tropismQueen, std::array<squaresType, MAXDIST + 1>& tropism) noexcept
		{
			if (pl == whitePlayer)
			{
				const rankType rank{ sq.rank() };
				constexpr const squaresType all{ squaresType::all() };
				tropism[0] = movegenPawnCaptureWhite.inverseTargets(sq, all) | movegenPawnPromoCaptureWhite.inverseTargets(sq, all);
				if constexpr (MAXDIST > 0)
				{
					std::array<squaresType, MAXDIST> visited;
					visited[0] = tropism[0];
					for (unsigned i = 1; i < MAXDIST; i++)
					{
						const squaresType tropismPromotion{ (tropismKnight[i - 1] | tropismBishop[i - 1] | tropismRook[i - 1] | tropismQueen[i - 1]) & rank8 };
						tropism[i] = tropismPawn((tropism[i - 1] | tropismPromotion) & allowedSquares, whitePlayer, unoccupiedSquares, victims) & ~visited[i - 1];
						visited[i] = visited[i - 1] | tropism[i];
					}
					const squaresType tropismPromotion2{ (tropismKnight[MAXDIST - 1] | tropismBishop[MAXDIST - 1] | tropismRook[MAXDIST - 1] | tropismQueen[MAXDIST - 1]) & rank8 };
					tropism[MAXDIST] = tropismPawn((tropism[MAXDIST - 1] | tropismPromotion2) & allowedSquares, whitePlayer, unoccupiedSquares, victims) & ~visited[MAXDIST - 1];
				}
			}
			else
			{
				const rankType rank{ sq.rank() };
				constexpr const squaresType all{ squaresType::all() };
				tropism[0] = movegenPawnCaptureBlack.inverseTargets(sq, all) | movegenPawnPromoCaptureBlack.inverseTargets(sq, all);
				if constexpr (MAXDIST > 0)
				{
					std::array<squaresType, MAXDIST> visited;
					visited[0] = tropism[0];
					for (unsigned i = 1; i < MAXDIST; i++)
					{
						const squaresType tropismPromotion{ (tropismKnight[i - 1] | tropismBishop[i - 1] | tropismRook[i - 1] | tropismQueen[i - 1]) & rank1 };
						tropism[i] = tropismPawn((tropism[i - 1] | tropismPromotion) & allowedSquares, blackPlayer, unoccupiedSquares, victims) & ~visited[i - 1];
						visited[i] = visited[i - 1] | tropism[i];
					}
					const squaresType tropismPromotion2{ (tropismKnight[MAXDIST - 1] | tropismBishop[MAXDIST - 1] | tropismRook[MAXDIST - 1] | tropismQueen[MAXDIST - 1]) & rank1 };
					tropism[MAXDIST] = tropismPawn((tropism[MAXDIST - 1] | tropismPromotion2) & allowedSquares, blackPlayer, unoccupiedSquares, victims) & ~visited[MAXDIST - 1];
				}
			}
		}
		template<unsigned MAXDIST>
		static void attackTropismPawn(const squaresType& sq, const playerType pl, const squaresType& allowedSquares, const squaresType& unoccupiedSquares, const squaresType& victims, const std::array<squaresType, MAXDIST + 1>& tropismKnight, const std::array<squaresType, MAXDIST + 1>& tropismBishop, const std::array<squaresType, MAXDIST + 1>& tropismRook, const std::array<squaresType, MAXDIST + 1>& tropismQueen, std::array<squaresType, MAXDIST + 1>& tropism) noexcept
		{
			if (pl == whitePlayer)
			{
				constexpr const squaresType all{ squaresType::all() };
				tropism[0] = movegenPawnCaptureWhite.inverseTargets(sq, all) | movegenPawnPromoCaptureWhite.inverseTargets(sq, all);
				if constexpr (MAXDIST > 0)
				{
					std::array<squaresType, MAXDIST> visited;
					visited[0] = tropism[0];
					for (unsigned i = 1; i < MAXDIST; i++)
					{
						const squaresType tropismPromotion{ (tropismKnight[i - 1] | tropismBishop[i - 1] | tropismRook[i - 1] | tropismQueen[i - 1]) & rank8 };
						tropism[i] = tropismPawn((tropism[i - 1] | tropismPromotion) & allowedSquares, whitePlayer, unoccupiedSquares, victims) & ~visited[i - 1];
						visited[i] = visited[i - 1] | tropism[i];
					}
					const squaresType tropismPromotion2{ (tropismKnight[MAXDIST - 1] | tropismBishop[MAXDIST - 1] | tropismRook[MAXDIST - 1] | tropismQueen[MAXDIST - 1]) & rank8 };
					tropism[MAXDIST] = tropismPawn((tropism[MAXDIST - 1] | tropismPromotion2) & allowedSquares, whitePlayer, unoccupiedSquares, victims) & ~visited[MAXDIST - 1];
				}
			}
			else
			{
				constexpr const squaresType all{ squaresType::all() };
				tropism[0] = movegenPawnCaptureBlack.inverseTargets(sq, all) | movegenPawnPromoCaptureBlack.inverseTargets(sq, all);
				if constexpr (MAXDIST > 0)
				{
					std::array<squaresType, MAXDIST> visited;
					visited[0] = tropism[0];
					for (unsigned i = 1; i < MAXDIST; i++)
					{
						const squaresType tropismPromotion{ (tropismKnight[i - 1] | tropismBishop[i - 1] | tropismRook[i - 1] | tropismQueen[i - 1]) & rank1 };
						tropism[i] = tropismPawn((tropism[i - 1] | tropismPromotion) & allowedSquares, blackPlayer, unoccupiedSquares, victims) & ~visited[i - 1];
						visited[i] = visited[i - 1] | tropism[i];
					}
					const squaresType tropismPromotion2{ (tropismKnight[MAXDIST - 1] | tropismBishop[MAXDIST - 1] | tropismRook[MAXDIST - 1] | tropismQueen[MAXDIST - 1]) & rank1 };
					tropism[MAXDIST] = tropismPawn((tropism[MAXDIST - 1] | tropismPromotion2) & allowedSquares, blackPlayer, unoccupiedSquares, victims) & ~visited[MAXDIST - 1];
				}
			}
		}
		static const rays& getRays() noexcept
		{
			return m_Rays;
		}
		static squaresType attackers(const boardType& position, const squareType square) noexcept
		{
			PYGMALION_ASSERT(square.isValid());
			constexpr const squaresType none{ squaresType::none() };
			squaresType attackers{ none };
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
			PYGMALION_ASSERT(square.isValid());
			constexpr const squaresType none{ squaresType::none() };
			squaresType attackers{ none };
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
		template<size_t PLAYER>
		static bool isMoveLegal_Implementation(const stackType<PLAYER>& stack, const movebitsType moveBits) noexcept
		{
			const boardType& position{ stack.position() };
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType otherPlayer{ movingPlayer.next() };
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

				if constexpr (movingPlayer == whitePlayer)
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
				if constexpr (movingPlayer == whitePlayer)
				{
					if (rank7 == rankFrom)
						return false;
				}
				else
				{
					if (rank2 == rankFrom)
						return false;
				}

				// is the destination rank correct?
				const fileType rankTo{ to.rank() };
				if constexpr (movingPlayer == whitePlayer)
				{
					if (rank8 == rankTo)
						return false;
				}
				else
				{
					if (rank1 == rankTo)
						return false;
				}

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
				if constexpr (movingPlayer == whitePlayer)
				{
					if (position.totalOccupancy() & kingsideCastleInterestWhite)
						return false;
				}
				else
				{
					if (position.totalOccupancy() & kingsideCastleInterestBlack)
						return false;
				}
			}
			else if (motorType::move().isQueensideCastle(moveBits))
			{
				// do we have kingside castling rights?
				if (!position.checkCastleRightQueenside(movingPlayer))
					return false;

				// are pieces obstructing the way?
				if constexpr (movingPlayer == whitePlayer)
				{
					if (position.totalOccupancy() & queensideCastleInterestWhite)
						return false;
				}
				else
				{
					if (position.totalOccupancy() & queensideCastleInterestBlack)
						return false;
				}
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

				// are we illegally capturing the other king?
				if (stack.kingSquare(otherPlayer) == captureSquare)
					return false;


				// is there a piece to capture?
				if (!position.playerOccupancy(otherPlayer)[captureSquare])
					return false;

				// what piece are we moving?
				const pieceType movingPiece{ position.getPiece(from) };

				// are we doing a legal capture?
				switch (movingPiece)
				{
				default:
					PYGMALION_UNREACHABLE;
					break;
				case pawn:
					if (!pawnCaptureTargets<PLAYER>(from, ~position.playerOccupancy(movingPlayer))[to])
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
				default:
					PYGMALION_UNREACHABLE;
					break;
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

			// No. Let's see where our king lives after the move as been made then...
			const squareType kingsquareOld{ stack.kingSquare(movingPlayer) };
			const bool isKingMove{ from == kingsquareOld };
			const squareType kingsquare{ isKingMove ? to : kingsquareOld };

			// We need the enemy occupancy bitboard as it would be after the move...
			const squaresType otherOccupancy{ position.playerOccupancy(otherPlayer) };
			const squaresType otherDelta{ motorType::move().otherOccupancyDelta(position, moveBits) };
			const squaresType occOther{ otherOccupancy ^ otherDelta };

			// if we're moving the king or are in check, we need to do some extra work
			constexpr const squaresType all{ squaresType::all() };
			if (isKingMove || stack.isPositionCritical())
			{
				// Does our king live on a square that is guarded by the other king?
				const squaresType attackedByOtherKing{ movegenKing.attacks(stack.kingSquare(otherPlayer),all) };
				if (attackedByOtherKing[kingsquare])
					return false;

				// Does he live on a square that is guarded by an enemy knight?
				const squaresType knightsDelta{ motorType::move().pieceOccupancyDelta(position, knight, moveBits) };
				const squaresType otherKnights{ (position.pieceOccupancy(knight) ^ knightsDelta) & occOther };
				const squaresType attackedByOtherKnights{ movegenKnight.attacks(otherKnights,all) };
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
					if (motorType::move().isQueensideCastle(moveBits))
					{
						// is the way for the king attacked?
						if constexpr (movingPlayer == whitePlayer)
						{
							if (stack.template squaresAttackedByPlayer<static_cast<size_t>(otherPlayer)>() & queensideCastleWalkWhite)
								return false;
						}
						else
						{
							if (stack.template squaresAttackedByPlayer<static_cast<size_t>(otherPlayer)>() & queensideCastleWalkBlack)
								return false;
						}
					}
					else if (motorType::move().isKingsideCastle(moveBits))
					{
						// is the way for the king attacked?
						if constexpr (movingPlayer == whitePlayer)
						{
							if (stack.template squaresAttackedByPlayer<static_cast<size_t>(otherPlayer)>() & kingsideCastleWalkWhite)
								return false;
						}
						else
						{
							if (stack.template squaresAttackedByPlayer<static_cast<size_t>(otherPlayer)>() & kingsideCastleWalkBlack)
								return false;
						}
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
			if (criticalSquaresHV & otherSlidersHV)
				return false;

			// Is he attacked diagonally by sliding pieces?
			const squaresType bishopsDelta{ motorType::move().pieceOccupancyDelta(position, bishop, moveBits) };
			const squaresType bishops{ position.pieceOccupancy(bishop) ^ bishopsDelta };
			const squaresType otherSlidersDiag = occOther & (bishops | queens);
			const squaresType criticalSquaresDiag{ movegenSlidersDiag.inverseAttacks(kingsquare, unoccupied) };
			if (criticalSquaresDiag & otherSlidersDiag)
				return false;

			// The move seems legal
			return true;
		}
		template<size_t PLAYER>
		static bool isMoveTactical_Implementation(const stackType<PLAYER>& stack, const movebitsType moveBits) noexcept
		{
			return motorType::move().isCapture(moveBits);
		}
		template<size_t PLAYER>
		static bool isGeneratedMoveLegal_Implementation(const stackType<PLAYER>& stack, const movebitsType moveBits) noexcept
		{
			const boardType& position{ stack.position() };
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType otherPlayer{ movingPlayer.next() };
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
			constexpr const squaresType all{ squaresType::all() };
			if (isKingMove)
			{
				// Does our king live on a square that is guarded by the other king?
				const squaresType attackedByOtherKing{ movegenKing.attacks(otherking,all) };
				if (attackedByOtherKing[kingsquare])
					return false;

				// Does he live on a square that is guarded by an enemy knight?
				const squaresType knightsDelta{ motorType::move().pieceOccupancyDelta(position, knight, moveBits) };
				const squaresType otherKnights{ (position.pieceOccupancy(knight) ^ knightsDelta) & occOther };
				const squaresType attackedByOtherKnights{ movegenKnight.attacks(otherKnights,all) };
				if (attackedByOtherKnights[kingsquare])
					return false;

				// Does he live on a square that is guarded by an enemy pawn?
				const squaresType pawnsDelta{ motorType::move().pieceOccupancyDelta(position, pawn, moveBits) };
				const squaresType otherPawns{ (position.pieceOccupancy(pawn) ^ pawnsDelta) & occOther };
				if constexpr (otherPlayer == whitePlayer)
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

				if (motorType::move().isQueensideCastle(moveBits))
				{
					// is the way for the king attacked?
					if constexpr (movingPlayer == whitePlayer)
					{
						if (stack.template squaresAttackedByPlayer<static_cast<size_t>(otherPlayer)>() & queensideCastleWalkWhite)
							return false;
					}
					else
					{
						if (stack.template squaresAttackedByPlayer<static_cast<size_t>(otherPlayer)>() & queensideCastleWalkBlack)
							return false;
					}
				}
				else if (motorType::move().isKingsideCastle(moveBits))
				{
					// is the way for the king attacked?
					if constexpr (movingPlayer == whitePlayer)
					{
						if (stack.template squaresAttackedByPlayer<static_cast<size_t>(otherPlayer)>() & kingsideCastleWalkWhite)
							return false;
					}
					else
					{
						if (stack.template squaresAttackedByPlayer<static_cast<size_t>(otherPlayer)>() & kingsideCastleWalkBlack)
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
			if (criticalSquaresHV & otherSlidersHV)
				return false;

			// Is he attacked diagonally by sliding pieces?
			const squaresType bishopsDelta{ motorType::move().pieceOccupancyDelta(position, bishop, moveBits) };
			const squaresType bishops{ position.pieceOccupancy(bishop) ^ bishopsDelta };
			const squaresType otherSlidersDiag = occOther & (bishops | queens);
			const squaresType criticalSquaresDiag{ movegenSlidersDiag.inverseAttacks(kingsquare, unoccupied) };
			if (criticalSquaresDiag & otherSlidersDiag)
				return false;

			// The move seems legal
			return true;
		}
		template<size_t PLAYER>
		static void generateMoves_Implementation(const stackType<PLAYER>& stack, movelistType& moves, const passType currentPass) noexcept
		{
			switch (static_cast<size_t>(currentPass))
			{
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
			default:
				PYGMALION_UNREACHABLE;
				break;
			}
		}
		template<size_t PLAYER>
		static void generateCriticalMoves_Implementation(const stackType<PLAYER>& stack, movelistType& moves, const passType currentPass) noexcept
		{
			switch (static_cast<size_t>(currentPass))
			{
			case 0:
				generateCriticalKnightMoves(stack, moves);
				break;
			case 1:
				generateCriticalPawnMoves(stack, moves);
				break;
			case 2:
				generateCriticalSliderMovesHV(stack, moves);
				break;
			case 3:
				generateCriticalSliderMovesDiag(stack, moves);
				break;
			default:
				PYGMALION_UNREACHABLE;
				break;
			};
		}
		template<size_t PLAYER>
		static void generateCriticalEvasionMoves_Implementation(const stackType<PLAYER>& stack, movelistType& moves, const passType currentPass) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			constexpr const playerType side{ static_cast<playerType>(PLAYER) };
			constexpr const playerType otherSide{ side.next() };
			const squaresType totalOCC{ stack.position().totalOccupancy() };
			const squaresType unoccupied{ ~totalOCC };
			movebitsType move;
			const squareType king{ stack.kingSquare(side) };
			const squaresType otherOcc{ stack.position().playerOccupancy(otherSide) };
			const squaresType otherPawns{ stack.position().pieceOccupancy(pawn) & otherOcc };
			const squaresType otherKnights{ stack.position().pieceOccupancy(knight) & otherOcc };
			const squaresType otherBishops{ stack.position().pieceOccupancy(bishop) & otherOcc };
			const squaresType otherRooks{ stack.position().pieceOccupancy(rook) & otherOcc };
			const squaresType otherQueens{ stack.position().pieceOccupancy(queen) & otherOcc };
			squaresType attackers = otherKnights & movegenKnight.attacks(king, all);
			attackers |= (otherBishops | otherQueens) & movegenSlidersDiag.attacks(king, unoccupied);
			attackers |= (otherRooks | otherQueens) & movegenSlidersHV.attacks(king, unoccupied);
			const squaresType kingSquares{ squaresType(king) };
			if constexpr (side == blackPlayer)
			{
				attackers |= otherPawns & (kingSquares.downLeft() | kingSquares.downRight());
			}
			else
			{
				attackers |= otherPawns & (kingSquares.upLeft() | kingSquares.upRight());
			}
			// Is the king attacked by a single piece?
			if (attackers.count() == 1)
			{
				const squaresType ownOcc{ stack.position().playerOccupancy(side) };
				const squaresType ownPawns = stack.position().pieceOccupancy(pawn) & ownOcc;
				const squaresType ownKnights = stack.position().pieceOccupancy(knight) & ownOcc;
				const squaresType ownDiagSliders = (stack.position().pieceOccupancy(bishop) | stack.position().pieceOccupancy(queen)) & ownOcc;
				const squaresType ownHVSliders = (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen)) & ownOcc;
				const squareType attackerSquare{ *attackers.begin() };
				// Can the attacker be captured with a knight?
				squaresType defenders = ownKnights & movegenKnight.attacks(attackerSquare, all);
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
				constexpr const bool sideIsBlack{ side == blackPlayer };
				constexpr const bool sideIsWhite{ side == whitePlayer };
				if ((attackerRank == rank1) && sideIsBlack)
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
				else if ((attackerRank == rank8) && sideIsWhite)
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
					if constexpr (side == blackPlayer)
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
						if (sideIsWhite && (attackerRank == rank5))
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
						else if (sideIsBlack && (attackerRank == rank4))
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
				constexpr const squaresType none{ squaresType::none() };
				squaresType blockSquares{ none };
				for (int rayDir = 0; rayDir < 8; rayDir++)
				{
					const squaresType rayFromKing{ m_Rays.getRay(rayDir,king) };
					if (rayFromKing & attackers)
					{
						switch (rayDir)
						{
						default:
							PYGMALION_UNREACHABLE;
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
					squaresType defenders{ ownKnights & movegenKnight.attacks(blockSquare, all) };
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
					if ((rank == rank4) && sideIsWhite)
					{
						if (ownPawns[file & rank2] && !totalOCC[file & rank3])
						{
							moves.add(motorType::move().createDoublePush(file));
						}
					}
					else if ((rank == rank5) && sideIsBlack)
					{
						if (ownPawns[file & rank7] && !totalOCC[file & rank6])
						{
							moves.add(motorType::move().createDoublePush(file));
						}
					}
					// Is it possible to block on this square with a pawn push?
					if constexpr (side == whitePlayer)
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
			const squaresType quiets{ movegenKing.attacks(king, all) & unoccupied };
			for (const auto square : quiets)
			{
				moves.add(motorType::move().createQuiet(king, square));
			}
			const squaresType caps{ movegenKing.attacks(king, all) & stack.position().playerOccupancy(otherSide) };
			for (const auto square : caps)
			{
				moves.add(motorType::move().createCapture(king, square));
			}
		}
		template<size_t PLAYER>
		static void generateTacticalCriticalEvasionMoves_Implementation(const stackType<PLAYER>& stack, movelistType& moves, const passType currentPass) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			const squaresType totalOCC{ stack.position().totalOccupancy() };
			const squaresType unoccupied{ ~totalOCC };
			movebitsType move;
			constexpr const playerType side{ static_cast<playerType>(PLAYER) };
			constexpr const playerType otherSide{ side.next() };
			const squareType king{ stack.kingSquare(side) };
			const squaresType otherPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(otherSide) };
			const squaresType otherKnights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(otherSide) };
			const squaresType otherBishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(otherSide) };
			const squaresType otherRooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(otherSide) };
			const squaresType otherQueens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(otherSide) };
			squaresType attackers = otherKnights & movegenKnight.attacks(king, all);
			attackers |= (otherBishops | otherQueens) & movegenSlidersDiag.attacks(king, unoccupied);
			attackers |= (otherRooks | otherQueens) & movegenSlidersHV.attacks(king, unoccupied);
			const squaresType kingSquares{ squaresType(king) };
			if constexpr (side == blackPlayer)
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
				squaresType defenders = ownKnights & movegenKnight.attacks(attackerSquare, all);
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
				constexpr const bool sideIsBlack{ side == blackPlayer };
				constexpr const bool sideIsWhite{ side == whitePlayer };
				if ((attackerRank == rank1) && sideIsBlack)
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
				else if ((attackerRank == rank8) && sideIsWhite)
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
					if constexpr (side == blackPlayer)
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
						if (sideIsWhite && (attackerRank == rank5))
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
						else if (sideIsBlack && (attackerRank == rank4))
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
			const squaresType caps{ movegenKing.attacks(king, all) & stack.position().playerOccupancy(otherSide) };
			for (const auto square : caps)
			{
				moves.add(motorType::move().createCapture(king, square));
			}
		}
		template<size_t PLAYER>
		static void generateQuietCriticalMoves_Implementation(const stackType<PLAYER>& stack, movelistType& moves, const passType currentPass) noexcept
		{
			switch (static_cast<size_t>(currentPass))
			{
			case 0:
				generateQuietCriticalKnightMoves(stack, moves);
				break;
			case 1:
				generateQuietCriticalPawnMoves(stack, moves);
				break;
			case 2:
				generateQuietCriticalSliderMovesHV(stack, moves);
				break;
			case 3:
				generateQuietCriticalSliderMovesDiag(stack, moves);
				break;
			default:
				PYGMALION_UNREACHABLE;
				break;
			}
		}
		template<size_t PLAYER>
		static void generateTacticalMoves_Implementation(const stackType<PLAYER>& stack, movelistType& moves, const passType currentPass) noexcept
		{
			switch (static_cast<size_t>(currentPass))
			{
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
			default:
				PYGMALION_UNREACHABLE;
				break;
			};
		}
		template<size_t PLAYER>
		static void movesFromSquare(const stackType<PLAYER>& stack, const squareType square, squaresType& moves, squaresType& captures, const size_t depth) noexcept
		{
			const boardType& position{ stack.position() };
			constexpr const squaresType none{ squaresType::none() };
			moves = none;
			captures = none;
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
		template<size_t PLAYER>
		static std::string moveToString_Implementation(const stackType<PLAYER>& stack, const movebitsType mv, const size_t depth) noexcept
		{
			const boardType& position{ stack.position() };
			const squareType from{ motorType::move().fromSquare(position,mv) };
			const squareType to{ motorType::move().toSquare(position,mv) };
			const pieceType piece{ position.getPiece(from) };
			constexpr const playerType side{ static_cast<playerType>(PLAYER) };
			if (motorType::move().isKingsideCastle(mv))
				return "O-O";
			if (motorType::move().isQueensideCastle(mv))
				return "O-O-O";
			std::string ret = "";
			switch (piece)
			{
			default:
				PYGMALION_UNREACHABLE;
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
			constexpr const squaresType none{ squaresType::none() };
			for (const auto sq : squareType::range)
			{
				if ((position.pieceOccupancy(piece) & position.playerOccupancy(side))[sq])
				{
					squaresType captures{ none };
					squaresType moves{ none };
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
						squaresType captures{ none };
						squaresType moves{ none };
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
							squaresType captures{ none };
							squaresType moves{ none };
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
						default:
							PYGMALION_UNREACHABLE;
							break;
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
					default:
						PYGMALION_UNREACHABLE;
						break;
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
			{
				ret += "x";
				if (motorType::move().isEnPassant(mv))
				{
					ret = ret + boardType::squareToString(motorType::move().captureSquare(position, mv));
					ret += "ep";
				}
				else
					ret = ret + boardType::squareToString(to);
			}
			else
				ret = ret + boardType::squareToString(to);
			if (motorType::move().isPromotion(mv))
			{
				switch (motorType::move().promotedPiece(mv))
				{
				default:
					PYGMALION_UNREACHABLE;
					break;
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
		static std::string passToString_Implementation(const passType pass) noexcept;
		static std::string tacticalPassToString_Implementation(const passType tacticalPass) noexcept;
		static std::string tacticalCriticalEvasionPassToString_Implementation(const passType tacticalCriticalEvasionPass) noexcept;
		static std::string criticalPassToString_Implementation(const passType criticalPass) noexcept;
		static std::string criticalEvasionPassToString_Implementation(const passType criticalEvasionPass) noexcept;
		static std::string quietCriticalPassToString_Implementation(const passType quietCriticalPass) noexcept;
		static squaresType attacksXrayDiag(const squareType square, const squaresType& occ, const squaresType& xrays) noexcept
		{
			PYGMALION_ASSERT(square.isValid());
			const squaresType attmask{ movegenSlidersDiag.attacks(square, ~occ) };
			return attmask & xrays;
		}
		static squaresType attacksXrayHV(const squareType square, const squaresType& occ, const squaresType& xrays) noexcept
		{
			PYGMALION_ASSERT(square.isValid());
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
		template<size_t PLAYER>
		static bool isMoveCritical_Implementation(const stackType<PLAYER>& stack, const movebitsType moveBits) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			const boardType& position{ stack.position() };
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType otherPlayer{ movingPlayer.next() };
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
			const squaresType attackedByOwnKnights{ movegenKnight.attacks(ownKnights,all) };
			if (attackedByOwnKnights[otherking])
				return true;

			// Does he live on a square that is attacked by one of our pawns?
			const squaresType pawnsDelta{ motorType::move().pieceOccupancyDelta(position, pawn, moveBits) };
			const squaresType ownPawns{ (position.pieceOccupancy(pawn) ^ pawnsDelta) & occOwn };
			if constexpr (movingPlayer == whitePlayer)
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
			if (criticalSquaresHV & ownSlidersHV)
				return true;

			// Is he attacked diagonally by sliding pieces?
			const squaresType bishopsDelta{ motorType::move().pieceOccupancyDelta(position, bishop, moveBits) };
			const squaresType bishops{ position.pieceOccupancy(bishop) ^ bishopsDelta };
			const squaresType ownSlidersDiag = occOwn & (bishops | queens);
			const squaresType criticalSquaresDiag{ movegenSlidersDiag.inverseAttacks(otherking, unoccupied) };
			if (criticalSquaresDiag & ownSlidersDiag)
				return true;

			// The move seems not to be giving check
			return false;
		}
		template<size_t PLAYER>
		static bool isPositionCritical_Implementation(const stackType<PLAYER>& stack) noexcept
		{
			constexpr const playerType player{ static_cast<playerType>(PLAYER) };
			constexpr const playerType attacker{ player.next() };
			return generatorType::template isAttacked<static_cast<size_t>(attacker)>(stack.position(), stack.kingSquare(player));
		}
	};
}