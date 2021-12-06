namespace pygmalion::chess
{
	namespace detail
	{
		class evaluationstage_kingareasafety_data
		{
		public:
			std::array<typename descriptor_evaluation::scoreType, descriptor_evaluation::countPieces> Score;
		};
	}
	class evaluationstage_kingareasafety :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_kingareasafety, detail::evaluationstage_kingareasafety_data>
	{
	public:
		PYGMALION_TUNABLE static inline double KingAreaSafetyPawn{ 0.00625 };
		PYGMALION_TUNABLE static inline double KingAreaSafetyKnight{ 0.00625 };
		PYGMALION_TUNABLE static inline double KingAreaSafetyBishop{ 0.00625 };
		PYGMALION_TUNABLE static inline double KingAreaSafetyRook{ 0.00625 };
		PYGMALION_TUNABLE static inline double KingAreaSafetyQueen{ 0.00625 };
		PYGMALION_TUNABLE static inline double KingAreaSafetyKing{ 0.00625 };
		using dataType = detail::evaluationstage_kingareasafety_data;
	private:
		constexpr static const inline std::array<scoreType, generatorType::tropismType::maxDistance + 2> m_LookUp
		{
			arrayhelper::generate<generatorType::tropismType::maxDistance + 2,scoreType>(
				[](const size_t d)
				{
					double value{ 1.0 };
					for (unsigned int i = 0; i <= generatorType::tropismType::maxDistance + 1; i++)
					{

						value *= 0.5;
						if (i == d)
							return static_cast<scoreType>(value);
					}
					return scoreType::zero();
				}
			)
		};
		PYGMALION_TUNABLE static inline scoreType m_KingAreaSafetyScoresPawn{ static_cast<scoreType>(KingAreaSafetyPawn) };
		PYGMALION_TUNABLE static inline scoreType m_KingAreaSafetyScoresKnight{ static_cast<scoreType>(KingAreaSafetyKnight) };
		PYGMALION_TUNABLE static inline scoreType m_KingAreaSafetyScoresBishop{ static_cast<scoreType>(KingAreaSafetyBishop) };
		PYGMALION_TUNABLE static inline scoreType m_KingAreaSafetyScoresRook{ static_cast<scoreType>(KingAreaSafetyRook) };
		PYGMALION_TUNABLE static inline scoreType m_KingAreaSafetyScoresQueen{ static_cast<scoreType>(KingAreaSafetyQueen) };
		PYGMALION_TUNABLE static inline scoreType m_KingAreaSafetyScoresKing{ static_cast<scoreType>(KingAreaSafetyKing) };
		PYGMALION_TUNABLE static inline scoreType KingAreaSafetyDelta{ static_cast<scoreType>(16.0 * std::max(std::max(std::max(KingAreaSafetyPawn,KingAreaSafetyKnight), std::max(KingAreaSafetyBishop, KingAreaSafetyRook)), std::max(KingAreaSafetyQueen, KingAreaSafetyKing))) };
		template<size_t PLAYER, bool MOVINGPLAYER>
		PYGMALION_INLINE static void scoreKingAreaSafety(const generatorType::template stackType<PLAYER>& stack, dataType& data) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType player{ MOVINGPLAYER ? movingPlayer : movingPlayer.next() };
			constexpr const playerType otherPlayer{ player.next() };
			const std::array<squaresType, countPieces> piecesOther{ arrayhelper::generate<countPieces,squaresType>([&stack,otherPlayer](const size_t index) {return stack.position().pieceOccupancy(static_cast<pieceType>(index)) & stack.position().playerOccupancy(otherPlayer); }) };
			const std::array<squaresType, countPieces> piecesOwn{ arrayhelper::generate<countPieces,squaresType>([&stack,player](const size_t index) {return stack.position().pieceOccupancy(static_cast<pieceType>(index)) & stack.position().playerOccupancy(player); }) };
			const auto& entry{ generatorType::pawnTable().entry(stack) };
			const auto& kingAreaTropismOwn{ entry.template kingAreaTropism<static_cast<size_t>(player)>() };
			const auto& kingAreaTropismOther{ entry.template kingAreaTropism<static_cast<size_t>(otherPlayer)>() };
			bool bFound;
			const squaresType unoccupied{ ~stack.position().totalOccupancy() };
			const squaresType playerOcc{ stack.position().playerOccupancy(player) };
			const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
			for (const auto sq : piecesOther[pawn])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropismOwn.distanceSquares(pawn, d)[sq])
					{
						if constexpr (movingPlayer == player)
							data.Score[pawn] -= m_LookUp[d];
						else
							data.Score[pawn] += m_LookUp[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					if constexpr (otherPlayer == whitePlayer)
					{
						const squaresType pawnTargets{ generatorType::movegenPawnPushWhite.targets(sq, unoccupied) | generatorType::movegenPawnDoublePushWhite.targets(sq, unoccupied) };
						if constexpr (movingPlayer == player)
							data.Score[pawn] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
						else
							data.Score[pawn] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					}
					else
					{
						const squaresType pawnTargets{ generatorType::movegenPawnPushBlack.targets(sq, unoccupied) | generatorType::movegenPawnDoublePushBlack.targets(sq, unoccupied) };
						if constexpr (movingPlayer == player)
							data.Score[pawn] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
						else
							data.Score[pawn] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					}
				}
			}
			for (const auto sq : piecesOwn[pawn])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropismOther.distanceSquares(pawn, d)[sq])
					{
						if constexpr (movingPlayer != player)
							data.Score[pawn] -= m_LookUp[d];
						else
							data.Score[pawn] += m_LookUp[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					if constexpr (otherPlayer != whitePlayer)
					{
						const squaresType pawnTargets{ generatorType::movegenPawnPushWhite.targets(sq, unoccupied) | generatorType::movegenPawnDoublePushWhite.targets(sq, unoccupied) };
						if constexpr (movingPlayer != player)
							data.Score[pawn] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
						else
							data.Score[pawn] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					}
					else
					{
						const squaresType pawnTargets{ generatorType::movegenPawnPushBlack.targets(sq, unoccupied) | generatorType::movegenPawnDoublePushBlack.targets(sq, unoccupied) };
						if constexpr (movingPlayer != player)
							data.Score[pawn] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
						else
							data.Score[pawn] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					}
				}
			}
			const squareType otherKing{ stack.kingSquare(otherPlayer) };
			bFound = false;
			for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
			{
				if (kingAreaTropismOwn.distanceSquares(pawn, d)[otherKing])
				{
					if constexpr (otherPlayer == whitePlayer)
						data.Score[king] -= m_LookUp[d];
					else
						data.Score[king] += m_LookUp[d];
					bFound = true;
					break;
				}
			}
			if (!bFound)
			{
				const squaresType kingTargets{ generatorType::movegenKing.targets(otherKing, unoccupied) | (generatorType::movegenKing.attacks(otherKing, unoccupied) & playerOcc) };
				if constexpr (otherPlayer == whitePlayer)
					data.Score[king] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(king, generatorType::tropismType::maxDistance) & kingTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				else
					data.Score[king] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(king, generatorType::tropismType::maxDistance) & kingTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
			}
			const squareType ownKing{ stack.kingSquare(player) };
			bFound = false;
			for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
			{
				if (kingAreaTropismOther.distanceSquares(pawn, d)[ownKing])
				{
					if constexpr (otherPlayer != whitePlayer)
						data.Score[king] -= m_LookUp[d];
					else
						data.Score[king] += m_LookUp[d];
					bFound = true;
					break;
				}
			}
			if (!bFound)
			{
				const squaresType kingTargets{ generatorType::movegenKing.targets(ownKing, unoccupied) | (generatorType::movegenKing.attacks(ownKing, unoccupied) & otherOcc) };
				if constexpr (otherPlayer != whitePlayer)
					data.Score[king] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(king, generatorType::tropismType::maxDistance) & kingTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				else
					data.Score[king] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(king, generatorType::tropismType::maxDistance) & kingTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
			}
			for (const auto sq : piecesOther[knight])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropismOwn.distanceSquares(knight, d)[sq])
					{
						if constexpr (otherPlayer == whitePlayer)
							data.Score[knight] -= m_LookUp[d];
						else
							data.Score[knight] += m_LookUp[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType knightTargets{ generatorType::movegenKnight.targets(sq, unoccupied) | (generatorType::movegenKnight.attacks(sq, unoccupied) & playerOcc) };
					if constexpr (otherPlayer == whitePlayer)
						data.Score[knight] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(knight, generatorType::tropismType::maxDistance) & knightTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					else
						data.Score[knight] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(knight, generatorType::tropismType::maxDistance) & knightTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : piecesOwn[knight])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropismOther.distanceSquares(knight, d)[sq])
					{
						if constexpr (otherPlayer != whitePlayer)
							data.Score[knight] -= m_LookUp[d];
						else
							data.Score[knight] += m_LookUp[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType knightTargets{ generatorType::movegenKnight.targets(sq, unoccupied) | (generatorType::movegenKnight.attacks(sq, unoccupied) & otherOcc) };
					if constexpr (otherPlayer != whitePlayer)
						data.Score[knight] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(knight, generatorType::tropismType::maxDistance) & knightTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					else
						data.Score[knight] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(knight, generatorType::tropismType::maxDistance) & knightTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : piecesOther[rook])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropismOwn.distanceSquares(rook, d)[sq])
					{
						if constexpr (otherPlayer == whitePlayer)
							data.Score[rook] -= m_LookUp[d];
						else
							data.Score[rook] += m_LookUp[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType rookTargets{ generatorType::movegenSlidersHV.targets(sq, unoccupied) | (generatorType::movegenSlidersHV.attacks(sq, unoccupied) & playerOcc) };
					if constexpr (otherPlayer == whitePlayer)
						data.Score[rook] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(rook, generatorType::tropismType::maxDistance) & rookTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					else
						data.Score[rook] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(rook, generatorType::tropismType::maxDistance) & rookTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : piecesOwn[rook])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropismOther.distanceSquares(rook, d)[sq])
					{
						if constexpr (otherPlayer != whitePlayer)
							data.Score[rook] -= m_LookUp[d];
						else
							data.Score[rook] += m_LookUp[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType rookTargets{ generatorType::movegenSlidersHV.targets(sq, unoccupied) | (generatorType::movegenSlidersHV.attacks(sq, unoccupied) & otherOcc) };
					if constexpr (otherPlayer != whitePlayer)
						data.Score[rook] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(rook, generatorType::tropismType::maxDistance) & rookTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					else
						data.Score[rook] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(rook, generatorType::tropismType::maxDistance) & rookTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : piecesOther[bishop])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropismOwn.distanceSquares(bishop, d)[sq])
					{
						if constexpr (otherPlayer == whitePlayer)
							data.Score[bishop] -= m_LookUp[d];
						else
							data.Score[bishop] += m_LookUp[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType bishopTargets{ generatorType::movegenSlidersDiag.targets(sq, unoccupied) | (generatorType::movegenSlidersDiag.attacks(sq, unoccupied) & playerOcc) };
					if constexpr (otherPlayer == whitePlayer)
						data.Score[bishop] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(bishop, generatorType::tropismType::maxDistance) & bishopTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					else
						data.Score[bishop] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(bishop, generatorType::tropismType::maxDistance) & bishopTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : piecesOwn[bishop])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropismOther.distanceSquares(bishop, d)[sq])
					{
						if constexpr (otherPlayer != whitePlayer)
							data.Score[bishop] -= m_LookUp[d];
						else
							data.Score[bishop] += m_LookUp[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType bishopTargets{ generatorType::movegenSlidersDiag.targets(sq, unoccupied) | (generatorType::movegenSlidersDiag.attacks(sq, unoccupied) & otherOcc) };
					if constexpr (otherPlayer != whitePlayer)
						data.Score[bishop] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(bishop, generatorType::tropismType::maxDistance) & bishopTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					else
						data.Score[bishop] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(bishop, generatorType::tropismType::maxDistance) & bishopTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : piecesOther[queen])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropismOwn.distanceSquares(queen, d)[sq])
					{
						if constexpr (otherPlayer == whitePlayer)
							data.Score[queen] -= m_LookUp[d];
						else
							data.Score[queen] += m_LookUp[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType queenTargets{ generatorType::movegenSlidersDiag.targets(sq, unoccupied) | generatorType::movegenSlidersHV.targets(sq, unoccupied) | (generatorType::movegenSlidersDiag.attacks(sq, unoccupied) & playerOcc) | (generatorType::movegenSlidersHV.attacks(sq, unoccupied) & playerOcc) };
					if constexpr (otherPlayer == whitePlayer)
						data.Score[queen] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(queen, generatorType::tropismType::maxDistance) & queenTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					else
						data.Score[queen] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOwn.distanceSquares(queen, generatorType::tropismType::maxDistance) & queenTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : piecesOwn[queen])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropismOther.distanceSquares(queen, d)[sq])
					{
						if constexpr (otherPlayer != whitePlayer)
							data.Score[queen] -= m_LookUp[d];
						else
							data.Score[queen] += m_LookUp[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType queenTargets{ generatorType::movegenSlidersDiag.targets(sq, unoccupied) | generatorType::movegenSlidersHV.targets(sq, unoccupied) | (generatorType::movegenSlidersDiag.attacks(sq, unoccupied) & otherOcc) | (generatorType::movegenSlidersHV.attacks(sq, unoccupied) & otherOcc) };
					if constexpr (otherPlayer != whitePlayer)
						data.Score[queen] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(queen, generatorType::tropismType::maxDistance) & queenTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					else
						data.Score[queen] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropismOther.distanceSquares(queen, generatorType::tropismType::maxDistance) & queenTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				}
			}
		}
	public:
		constexpr static size_t getParameterCount_Implementation() noexcept
		{
			return 6;
		}
		static parameter getParameter_Implementation(const size_t index) noexcept
		{
			switch (index)
			{
			default:
				PYGMALION_ASSERT(false);
				return parameter(0.0, 0.0, 1.0, 0.001, "term_kingareasafety_error");
			case 0:
				return parameter(KingAreaSafetyPawn, 0.0, 1.0, 0.001, "term_kingareasafety_pawn");
			case 1:
				return parameter(KingAreaSafetyKnight, 0.0, 1.0, 0.001, "term_kingareasafety_knight");
			case 2:
				return parameter(KingAreaSafetyBishop, 0.0, 1.0, 0.001, "term_kingareasafety_bishop");
			case 3:
				return parameter(KingAreaSafetyRook, 0.0, 1.0, 0.001, "term_kingareasafety_rook");
			case 4:
				return parameter(KingAreaSafetyQueen, 0.0, 1.0, 0.001, "term_kingareasafety_queen");
			case 5:
				return parameter(KingAreaSafetyKing, 0.0, 1.0, 0.001, "term_kingareasafety_king");
			}
		}
#if defined(PYGMALION_TUNE)
		static void setParameter_Implementation(const size_t index, double value) noexcept
		{
			switch (index)
			{
			default:
				PYGMALION_ASSERT(false);
				break;
			case 0:
				KingAreaSafetyPawn = value;
				m_KingAreaSafetyScoresPawn = scoreLookUp(KingAreaSafetyPawn);
				break;
			case 1:
				KingAreaSafetyKnight = value;
				m_KingAreaSafetyScoresKnight = scoreLookUp(KingAreaSafetyKnight);
				break;
			case 2:
				KingAreaSafetyBishop = value;
				m_KingAreaSafetyScoresBishop = scoreLookUp(KingAreaSafetyBishop);
				break;
			case 3:
				KingAreaSafetyRook = value;
				m_KingAreaSafetyScoresRook = scoreLookUp(KingAreaSafetyRook);
				break;
			case 4:
				KingAreaSafetyQueen = value;
				m_KingAreaSafetyScoresQueen = scoreLookUp(KingAreaSafetyQueen);
				break;
			case 5:
				KingAreaSafetyKing = value;
				m_KingAreaSafetyScoresKing = scoreLookUp(KingAreaSafetyKing);
				break;
			}
			KingAreaSafetyDelta = static_cast<scoreType>(8.0 * std::max(std::max(std::max(KingAreaSafetyPawn,KingAreaSafetyKnight), std::max(KingAreaSafetyBishop, KingAreaSafetyRook)), std::max(KingAreaSafetyQueen, KingAreaSafetyKing)));
		}
#endif
		PYGMALION_TUNABLE static scoreType computeDelta_Implementation() noexcept
		{
			return KingAreaSafetyDelta;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static void computeData_Implementation(const generatorType::template stackType<PLAYER>& stack, dataType& data) noexcept
		{
			constexpr const scoreType zero{ scoreType::zero() };
			for (const auto pc : pieceType::range)
			{
				data.Score[pc] = zero;
			}
			scoreKingAreaSafety<PLAYER, true>(stack, data);
			scoreKingAreaSafety<PLAYER, false>(stack, data);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType evaluate_Implementation(const dataType& data, const scoreType* pParameters) noexcept
		{
			constexpr const scoreType zero{ scoreType::zero() };
			scoreType score{ zero };
			score += data.Score[pawn] * pParameters[0];
			score += data.Score[knight] * pParameters[1];
			score += data.Score[rook] * pParameters[2];
			score += data.Score[bishop] * pParameters[3];
			score += data.Score[queen] * pParameters[4];
			score += data.Score[king] * pParameters[5];
			return score;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType differentiate_Implementation(const dataType, const size_t parameterIndex, const scoreType* pParameters) noexcept
		{
			switch (parameterIndex)
			{
			case 0:
				return data.Score[pawn];
			case 1:
				return data.Score[knight];
			case 2:
				return data.Score[bishop];
			case 3:
				return data.Score[rook];
			case 4:
				return data.Score[queen];
			case 5:
				return data.Score[king];
			default:
				PYGMALION_UNREACHABLE;
				return scoreType::zero();
			}
		}
		static std::string name_Implementation() noexcept
		{
			return "kingarea safety";
		}
	};
}