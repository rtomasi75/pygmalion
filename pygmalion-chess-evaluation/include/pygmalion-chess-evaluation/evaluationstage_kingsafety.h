namespace pygmalion::chess
{
	namespace detail
	{
		class evaluationstage_kingsafety_data
		{
		public:
			std::array<typename descriptor_evaluation::scoreType, descriptor_evaluation::countPieces> Score;
		};
	}
	class evaluationstage_kingsafety :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_kingsafety, detail::evaluationstage_kingsafety_data>
	{
	public:
		PYGMALION_TUNABLE static inline double KingSafetyPawn{ 0.0125 };
		PYGMALION_TUNABLE static inline double KingSafetyKnight{ 0.0125 };
		PYGMALION_TUNABLE static inline double KingSafetyBishop{ 0.0125 };
		PYGMALION_TUNABLE static inline double KingSafetyRook{ 0.0125 };
		PYGMALION_TUNABLE static inline double KingSafetyQueen{ 0.0125 };
		PYGMALION_TUNABLE static inline double KingSafetyKing{ 0.0125 };
		using dataType = detail::evaluationstage_kingsafety_data;
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
		template<size_t PLAYER, bool MOVINGPLAYER>
		PYGMALION_INLINE static void scoreKingsafety(const generatorType::template stackType<PLAYER>& stack, dataType& data) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType player{ MOVINGPLAYER ? movingPlayer : movingPlayer.next() };
			constexpr const playerType otherPlayer{ player.next() };
			const std::array<squaresType, countPieces> pieces{ arrayhelper::generate<countPieces,squaresType>([&stack,otherPlayer](const size_t index) {return stack.position().pieceOccupancy(static_cast<pieceType>(index)) & stack.position().playerOccupancy(otherPlayer); }) };
			const auto& entry{ generatorType::pawnTable().entry(stack) };
			const auto& kingTropism{ entry.template kingTropism<static_cast<playerType>(player)>() };
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
							data.Score[pawn] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
						else
							data.Score[pawn] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					}
					else
					{
						const squaresType pawnTargets{ generatorType::movegenPawnPushBlack.targets(sq, unoccupied) | generatorType::movegenPawnDoublePushBlack.targets(sq, unoccupied) };
						if constexpr (movingPlayer == player)
							data.Score[pawn] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
						else
							data.Score[pawn] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(pawn, generatorType::tropismType::maxDistance) & pawnTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					}
				}
			}
			const squareType otherKing{ stack.kingSquare(otherPlayer) };
			bFound = false;
			for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
			{
				if (kingTropism.distanceSquares(pawn, d)[otherKing])
				{
					if constexpr (movingPlayer == player)
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
				if constexpr (movingPlayer == player)
					data.Score[king] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(king, generatorType::tropismType::maxDistance) & kingTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				else
					data.Score[king] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(king, generatorType::tropismType::maxDistance) & kingTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
			}
			for (const auto sq : pieces[knight])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingTropism.distanceSquares(knight, d)[sq])
					{
						if constexpr (movingPlayer == player)
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
					if constexpr (movingPlayer == player)
						data.Score[knight] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(knight, generatorType::tropismType::maxDistance) & knightTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					else
						data.Score[knight] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(knight, generatorType::tropismType::maxDistance) & knightTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : pieces[rook])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingTropism.distanceSquares(rook, d)[sq])
					{
						if constexpr (movingPlayer == player)
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
					if constexpr (movingPlayer == player)
						data.Score[rook] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(rook, generatorType::tropismType::maxDistance) & rookTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					else
						data.Score[rook] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(rook, generatorType::tropismType::maxDistance) & rookTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : pieces[bishop])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingTropism.distanceSquares(bishop, d)[sq])
					{
						if constexpr (movingPlayer == player)
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
					if constexpr (movingPlayer == player)
						data.Score[bishop] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(bishop, generatorType::tropismType::maxDistance) & bishopTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					else
						data.Score[bishop] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(bishop, generatorType::tropismType::maxDistance) & bishopTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
				}
			}
			for (const auto sq : pieces[queen])
			{
				bFound = false;
				for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
				{
					if (kingTropism.distanceSquares(queen, d)[sq])
					{
						if constexpr (movingPlayer == player)
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
					if constexpr (movingPlayer == player)
						data.Score[queen] -= static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(queen, generatorType::tropismType::maxDistance) & queenTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
					else
						data.Score[queen] += static_cast<typename scoreType::valueType>(static_cast<bool>(kingTropism.distanceSquares(queen, generatorType::tropismType::maxDistance) & queenTargets)) * m_LookUp[generatorType::tropismType::maxDistance + 1];
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
			KingSafetyDelta = static_cast<scoreType>(8.0 * std::max(std::max(std::max(KingSafetyPawn, KingSafetyKnight), std::max(KingSafetyBishop, KingSafetyRook)), std::max(KingSafetyQueen, KingSafetyKing)));
		}
#endif
		PYGMALION_INLINE static scoreType computeDelta_Implementation(const scoreType* pParameters) noexcept
		{
			const scoreType kingSafetyDelta{ 8 * scoreType::max(scoreType::max(scoreType::max(pParameters[0],pParameters[1]), scoreType::max(pParameters[2], pParameters[3])), scoreType::max(pParameters[4], pParameters[5])) };
			return kingSafetyDelta;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static void computeData_Implementation(const generatorType::template stackType<PLAYER>& stack, dataType& data) noexcept
		{
			constexpr const scoreType zero{ scoreType::zero() };
			for (const auto pc : pieceType::range)
			{
				data.Score[pc] = zero;
			}
			scoreKingsafety<PLAYER, true>(stack, data);
			scoreKingsafety<PLAYER, false>(stack, data);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType evaluate_Implementation(const dataType& data, const scoreType* pParameters) noexcept
		{
			constexpr const scoreType zero{ scoreType::zero() };
			scoreType score{ zero };
			score += data.Score[pawn] * pParameters[0];
			score += data.Score[knight] * pParameters[1];
			score += data.Score[bishop] * pParameters[2];
			score += data.Score[rook] * pParameters[3];
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
			return "king safety";
		}
	};
}