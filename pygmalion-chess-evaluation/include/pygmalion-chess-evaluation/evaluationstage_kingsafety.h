namespace pygmalion::chess
{
	class evaluationstage_kingsafety :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_kingsafety>
	{
	public:
		PYGMALION_TUNABLE static inline double KingSafetyPawn{ 0.0125 };
		PYGMALION_TUNABLE static inline double KingSafetyKnight{ 0.0125 };
		PYGMALION_TUNABLE static inline double KingSafetyBishop{ 0.0125 };
		PYGMALION_TUNABLE static inline double KingSafetyRook{ 0.0125 };
		PYGMALION_TUNABLE static inline double KingSafetyQueen{ 0.0125 };
		PYGMALION_TUNABLE static inline double KingSafetyKing{ 0.0125 };
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
		static inline scoreLookUp m_KingSafetyScoresPawn{ scoreLookUp(KingSafetyPawn) };
		static inline scoreLookUp m_KingSafetyScoresKnight{ scoreLookUp(KingSafetyKnight) };
		static inline scoreLookUp m_KingSafetyScoresBishop{ scoreLookUp(KingSafetyBishop) };
		static inline scoreLookUp m_KingSafetyScoresRook{ scoreLookUp(KingSafetyRook) };
		static inline scoreLookUp m_KingSafetyScoresQueen{ scoreLookUp(KingSafetyQueen) };
		static inline scoreLookUp m_KingSafetyScoresKing{ scoreLookUp(KingSafetyKing) };
		PYGMALION_TUNABLE static inline scoreType KingSafetyDelta{ static_cast<scoreType>(8.0 * std::max(std::max(std::max(KingSafetyPawn,KingSafetyKnight), std::max(KingSafetyBishop, KingSafetyRook)), std::max(KingSafetyQueen, KingSafetyKing))) };
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType scoreKingsafety(const generatorType::template stackType<PLAYER>& stack, const playerType player) noexcept
		{
			const playerType otherPlayer{ player.next() };
			const std::array<squaresType, countPieces> pieces{ arrayhelper::generate<countPieces,squaresType>([&stack,otherPlayer](const size_t index) {return stack.position().pieceOccupancy(static_cast<pieceType>(index)) & stack.position().playerOccupancy(otherPlayer); }) };
			const auto& entry{ generatorType::pawnTable().entry(stack) };
			const auto& kingTropism{ entry.kingTropism(player) };
			scoreType safetyScore{ scoreType::zero() };
			bool bFound;
			const squaresType unoccupied{ ~stack.position().totalOccupancy() };
			const squaresType playerOcc{ stack.position().playerOccupancy(player) };
			for (const auto sq : pieces[pawn])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingTropism.distanceSquares(pawn, d)[sq])
					{
						safetyScore -= m_KingSafetyScoresPawn[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					if (otherPlayer == whitePlayer)
					{
						const squaresType pawnTargets{ generatorType::movegenPawnPushWhite.targets(sq, unoccupied) | generatorType::movegenPawnDoublePushWhite.targets(sq, unoccupied) };
						safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_KingSafetyScoresPawn[generatorType::tropismType::maxDistance + 1];
					}
					else
					{
						const squaresType pawnTargets{ generatorType::movegenPawnPushBlack.targets(sq, unoccupied) | generatorType::movegenPawnDoublePushBlack.targets(sq, unoccupied) };
						safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_KingSafetyScoresPawn[generatorType::tropismType::maxDistance + 1];
					}
				}
			}
			const squareType otherKing{ stack.kingSquare(otherPlayer) };
			bFound = false;
			for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
			{
				if (kingTropism.distanceSquares(pawn, d)[otherKing])
				{
					safetyScore -= m_KingSafetyScoresPawn[d];
					bFound = true;
					break;
				}
			}
			if (!bFound)
			{
				const squaresType kingTargets{ generatorType::movegenKing.targets(otherKing, unoccupied) | (generatorType::movegenKing.attacks(otherKing, unoccupied) & playerOcc) };
				safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(king, generatorType::tropismType::maxDistance) & kingTargets)) * m_KingSafetyScoresKing[generatorType::tropismType::maxDistance + 1];
			}
			for (const auto sq : pieces[knight])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingTropism.distanceSquares(knight, d)[sq])
					{
						safetyScore -= m_KingSafetyScoresKnight[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType knightTargets{ generatorType::movegenKnight.targets(sq, unoccupied) | (generatorType::movegenKnight.attacks(sq, unoccupied) & playerOcc) };
					safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(knight, generatorType::tropismType::maxDistance) & knightTargets)) * m_KingSafetyScoresKnight[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : pieces[rook])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingTropism.distanceSquares(rook, d)[sq])
					{
						safetyScore -= m_KingSafetyScoresRook[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType rookTargets{ generatorType::movegenSlidersHV.targets(sq, unoccupied) | (generatorType::movegenSlidersHV.attacks(sq, unoccupied) & playerOcc) };
					safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(rook, generatorType::tropismType::maxDistance) & rookTargets)) * m_KingSafetyScoresRook[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : pieces[bishop])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingTropism.distanceSquares(bishop, d)[sq])
					{
						safetyScore -= m_KingSafetyScoresBishop[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType bishopTargets{ generatorType::movegenSlidersDiag.targets(sq, unoccupied) | (generatorType::movegenSlidersDiag.attacks(sq, unoccupied) & playerOcc) };
					safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(bishop, generatorType::tropismType::maxDistance) & bishopTargets)) * m_KingSafetyScoresBishop[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : pieces[queen])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingTropism.distanceSquares(queen, d)[sq])
					{
						safetyScore -= m_KingSafetyScoresQueen[d];
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					const squaresType queenTargets{ generatorType::movegenSlidersDiag.targets(sq, unoccupied) | generatorType::movegenSlidersHV.targets(sq, unoccupied) | (generatorType::movegenSlidersDiag.attacks(sq, unoccupied) & playerOcc) | (generatorType::movegenSlidersHV.attacks(sq, unoccupied) & playerOcc) };
					safetyScore -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(queen, generatorType::tropismType::maxDistance) & queenTargets)) * m_KingSafetyScoresQueen[generatorType::tropismType::maxDistance + 1];
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
				return parameter(0.0, 0.0, 1.0, 0.001, "term_kingsafety_error");
			case 0:
				return parameter(KingSafetyPawn, 0.0, 1.0, 0.001, "term_kingsafety_pawn");
			case 1:
				return parameter(KingSafetyKnight, 0.0, 1.0, 0.001, "term_kingsafety_knight");
			case 2:
				return parameter(KingSafetyBishop, 0.0, 1.0, 0.001, "term_kingsafety_bishop");
			case 3:
				return parameter(KingSafetyRook, 0.0, 1.0, 0.001, "term_kingsafety_rook");
			case 4:
				return parameter(KingSafetyQueen, 0.0, 1.0, 0.001, "term_kingsafety_queen");
			case 5:
				return parameter(KingSafetyKing, 0.0, 1.0, 0.001, "term_kingsafety_king");
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
				KingSafetyPawn = value;
				m_KingSafetyScoresPawn = scoreLookUp(KingSafetyPawn);
				break;
			case 1:
				KingSafetyKnight = value;
				m_KingSafetyScoresKnight = scoreLookUp(KingSafetyKnight);
				break;
			case 2:
				KingSafetyBishop = value;
				m_KingSafetyScoresBishop = scoreLookUp(KingSafetyBishop);
				break;
			case 3:
				KingSafetyRook = value;
				m_KingSafetyScoresRook = scoreLookUp(KingSafetyRook);
				break;
			case 4:
				KingSafetyQueen = value;
				m_KingSafetyScoresQueen = scoreLookUp(KingSafetyQueen);
				break;
			case 5:
				KingSafetyKing = value;
				m_KingSafetyScoresKing = scoreLookUp(KingSafetyKing);
				break;
			}
			KingSafetyDelta = static_cast<scoreType>(8.0 * std::max(std::max(std::max(KingSafetyPawn,KingSafetyKnight), std::max(KingSafetyBishop, KingSafetyRook)), std::max(KingSafetyQueen, KingSafetyKing)));
		}
#endif
		PYGMALION_TUNABLE static scoreType computeDelta_Implementation() noexcept
		{
			return KingSafetyDelta;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType evaluate_Implementation(const generatorType::template stackType<PLAYER>& stack) noexcept
		{
			const scoreType kingSafetyWhite{ scoreKingsafety<PLAYER>(stack,whitePlayer) };
			const scoreType kingSafetyBlack{ scoreKingsafety<PLAYER>(stack,blackPlayer) };
			const scoreType scoreKingSafety{ kingSafetyWhite - kingSafetyBlack };
			const bool invert{ stack.movingPlayer() == blackPlayer };
			return invert ? -scoreKingSafety : scoreKingSafety;
		}
		static std::string name_Implementation() noexcept
		{
			return "king safety";
		}
	};
}