namespace pygmalion::chess
{
	class evaluationstage_kingareasafety :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_kingareasafety>
	{
	public:
		PYGMALION_TUNABLE static inline double KingAreaSafetyPawn{ 0.00625 };
		PYGMALION_TUNABLE static inline double KingAreaSafetyKnight{ 0.00625 };
		PYGMALION_TUNABLE static inline double KingAreaSafetyBishop{ 0.00625 };
		PYGMALION_TUNABLE static inline double KingAreaSafetyRook{ 0.00625 };
		PYGMALION_TUNABLE static inline double KingAreaSafetyQueen{ 0.00625 };
		PYGMALION_TUNABLE static inline double KingAreaSafetyKing{ 0.00625 };
	private:
		class scoreLookUp
		{
		private:
			std::array<scoreType, generatorType::tropismType::maxDistance + 2> m_Score;
		public:
			constexpr scoreLookUp(const double maxValue) noexcept :
				m_Score{ arrayhelper::make< generatorType::tropismType::maxDistance + 2 ,scoreType>(scoreType::zero()) }
			{
				double value{ maxValue };
				m_Score[0] = static_cast<scoreType>(value);
				for (unsigned int i = 1; i <= generatorType::tropismType::maxDistance + 1; i++)
				{
					value *= 0.5;
					m_Score[i] = static_cast<scoreType>(value);
				}
			}
			PYGMALION_INLINE const scoreType& operator[](const size_t index) const noexcept
			{
				return m_Score[index];
			}
			~scoreLookUp() noexcept = default;
			constexpr scoreLookUp(const scoreLookUp&) noexcept = default;
			constexpr scoreLookUp(scoreLookUp&&) noexcept = default;
			constexpr scoreLookUp& operator=(const scoreLookUp&) noexcept = default;
			constexpr scoreLookUp& operator=(scoreLookUp&&) noexcept = default;
		};
		static inline scoreLookUp m_KingAreaSafetyScoresPawn{ scoreLookUp(KingAreaSafetyPawn) };
		static inline scoreLookUp m_KingAreaSafetyScoresKnight{ scoreLookUp(KingAreaSafetyKnight) };
		static inline scoreLookUp m_KingAreaSafetyScoresBishop{ scoreLookUp(KingAreaSafetyBishop) };
		static inline scoreLookUp m_KingAreaSafetyScoresRook{ scoreLookUp(KingAreaSafetyRook) };
		static inline scoreLookUp m_KingAreaSafetyScoresQueen{ scoreLookUp(KingAreaSafetyQueen) };
		static inline scoreLookUp m_KingAreaSafetyScoresKing{ scoreLookUp(KingAreaSafetyKing) };
		PYGMALION_TUNABLE static inline scoreType KingAreaSafetyDelta{ static_cast<scoreType>(8.0 * std::max(std::max(std::max(KingAreaSafetyPawn,KingAreaSafetyKnight), std::max(KingAreaSafetyBishop, KingAreaSafetyRook)), std::max(KingAreaSafetyQueen, KingAreaSafetyKing))) };
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType scoreKingAreasafety(const generatorType::template stackType<PLAYER>& stack, const playerType player) noexcept
		{
			const playerType otherPlayer{ player.next() };
			const std::array<squaresType, countPieces> pieces{ arrayhelper::generate<countPieces,squaresType>([&stack,otherPlayer](const size_t index) {return stack.position().pieceOccupancy(static_cast<pieceType>(index)) & stack.position().playerOccupancy(otherPlayer); }) };
			const auto& entry{ generatorType::pawnTable().entry(stack) };
			const auto& kingAreaTropism{ entry.kingAreaTropism(player) };
			scoreType safetyScore{ scoreType::zero() };
			bool bFound;
			const squaresType unoccupied{ ~stack.position().totalOccupancy() };
			const squaresType playerOcc{ stack.position().playerOccupancy(player) };
			for (const auto sq : pieces[pawn])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropism.distanceSquares(pawn, d)[sq])
					{
						safetyScore -= m_KingAreaSafetyScoresPawn[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					if (otherPlayer == whitePlayer)
					{
						const squaresType pawnTargets{ generatorType::movegenPawnPushWhite.targets(sq, unoccupied) | generatorType::movegenPawnDoublePushWhite.targets(sq, unoccupied) };
						safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropism.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_KingAreaSafetyScoresPawn[generatorType::tropismType::maxDistance + 1];
					}
					else
					{
						const squaresType pawnTargets{ generatorType::movegenPawnPushBlack.targets(sq, unoccupied) | generatorType::movegenPawnDoublePushBlack.targets(sq, unoccupied) };
						safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropism.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_KingAreaSafetyScoresPawn[generatorType::tropismType::maxDistance + 1];
					}
				}
			}
			const squareType otherKing{ stack.kingSquare(otherPlayer) };
			bFound = false;
			for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
			{
				if (kingAreaTropism.distanceSquares(pawn, d)[otherKing])
				{
					safetyScore -= m_KingAreaSafetyScoresPawn[d];
					bFound = true;
					break;
				}
			}
			if (!bFound)
			{
				const squaresType kingTargets{ generatorType::movegenKing.targets(otherKing, unoccupied) | (generatorType::movegenKing.attacks(otherKing, unoccupied) & playerOcc) };
				safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropism.distanceSquares(king, generatorType::tropismType::maxDistance) & kingTargets)) * m_KingAreaSafetyScoresKing[generatorType::tropismType::maxDistance + 1];
			}
			for (const auto sq : pieces[knight])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropism.distanceSquares(knight, d)[sq])
					{
						safetyScore -= m_KingAreaSafetyScoresKnight[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType knightTargets{ generatorType::movegenKnight.targets(sq, unoccupied) | (generatorType::movegenKnight.attacks(sq, unoccupied) & playerOcc) };
					safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropism.distanceSquares(knight, generatorType::tropismType::maxDistance) & knightTargets)) * m_KingAreaSafetyScoresKnight[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : pieces[rook])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropism.distanceSquares(rook, d)[sq])
					{
						safetyScore -= m_KingAreaSafetyScoresRook[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType rookTargets{ generatorType::movegenSlidersHV.targets(sq, unoccupied) | (generatorType::movegenSlidersHV.attacks(sq, unoccupied) & playerOcc) };
					safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropism.distanceSquares(rook, generatorType::tropismType::maxDistance) & rookTargets)) * m_KingAreaSafetyScoresRook[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : pieces[bishop])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropism.distanceSquares(bishop, d)[sq])
					{
						safetyScore -= m_KingAreaSafetyScoresBishop[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType bishopTargets{ generatorType::movegenSlidersDiag.targets(sq, unoccupied) | (generatorType::movegenSlidersDiag.attacks(sq, unoccupied) & playerOcc) };
					safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropism.distanceSquares(bishop, generatorType::tropismType::maxDistance) & bishopTargets)) * m_KingAreaSafetyScoresBishop[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : pieces[queen])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingAreaTropism.distanceSquares(queen, d)[sq])
					{
						safetyScore -= m_KingAreaSafetyScoresQueen[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType queenTargets{ generatorType::movegenSlidersDiag.targets(sq, unoccupied) | generatorType::movegenSlidersHV.targets(sq, unoccupied) | (generatorType::movegenSlidersDiag.attacks(sq, unoccupied) & playerOcc) | (generatorType::movegenSlidersHV.attacks(sq, unoccupied) & playerOcc) };
					safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingAreaTropism.distanceSquares(queen, generatorType::tropismType::maxDistance) & queenTargets)) * m_KingAreaSafetyScoresQueen[generatorType::tropismType::maxDistance + 1];
				}
			}
			return safetyScore;
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
		PYGMALION_INLINE static scoreType evaluate_Implementation(const generatorType::template stackType<PLAYER>& stack) noexcept
		{
			const scoreType kingSafetyWhite{ scoreKingAreasafety<PLAYER>(stack,whitePlayer) };
			const scoreType kingSafetyBlack{ scoreKingAreasafety<PLAYER>(stack,blackPlayer) };
			const scoreType scoreKingAreaSafety{ kingSafetyWhite - kingSafetyBlack };
			const bool invert{ stack.movingPlayer() == blackPlayer };
			return invert ? -scoreKingAreaSafety : scoreKingAreaSafety;
		}
		static std::string name_Implementation() noexcept
		{
			return "kingarea safety";
		}
	};
}