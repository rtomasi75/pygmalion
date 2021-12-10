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
		friend pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_kingsafety, detail::evaluationstage_kingsafety_data>;
	public:
		static inline scoreType KingSafetyPawn{ static_cast<scoreType>(0.0125) };
		static inline scoreType KingSafetyKnight{ static_cast<scoreType>(0.0125) };
		static inline scoreType KingSafetyBishop{ static_cast<scoreType>(0.0125) };
		static inline scoreType KingSafetyRook{ static_cast<scoreType>(0.0125) };
		static inline scoreType KingSafetyQueen{ static_cast<scoreType>(0.0125) };
		static inline scoreType KingSafetyKing{ static_cast<scoreType>(0.0125) };
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
		PYGMALION_INLINE static scoreType quietChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to) noexcept
		{
			constexpr const auto maxDistance{ generatorType::tropismType::maxDistance + 1 };
			const int maxFrom{ static_cast<int>(generatorType::quietTargets(pl,pc,from).count() + generatorType::promotionTargets(pl,pc,from).count()) };
			const int maxTo{ static_cast<int>(generatorType::quietTargets(pl,pc,to).count() + generatorType::promotionTargets(pl,pc,to).count()) };
			const auto d{ std::max(maxFrom,maxTo) * maxDistance + 1 };
			return d * (pParameters[0]);
		}
		PYGMALION_INLINE static scoreType promotionChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const pieceType promoted) noexcept
		{
			constexpr const auto maxDistance{ generatorType::tropismType::maxDistance + 1 };
			const int maxFrom{ static_cast<int>(generatorType::quietTargets(pl,pc,from).count() + generatorType::promotionTargets(pl,pc,from).count()) };
			const int maxTo{ static_cast<int>(generatorType::quietTargets(pl,promoted,to).count() + generatorType::promotionTargets(pl,promoted,to).count()) };
			const auto d{ std::max(maxFrom,maxTo) * maxDistance + 1 };
			return d * (pParameters[0]);
		}
		PYGMALION_INLINE static scoreType captureChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const playerType vpl, const pieceType vpc) noexcept
		{
			constexpr const auto maxDistance{ generatorType::tropismType::maxDistance + 1 };
			const int maxTo{ static_cast<int>(generatorType::quietTargets(pl,pc,to).count() + generatorType::promotionTargets(pl,pc,to).count()) };
			const int maxFrom{ static_cast<int>(generatorType::quietTargets(pl,pc,from).count() + generatorType::promotionTargets(pl,pc,from).count()) };
			const int maxVictim{ static_cast<int>(generatorType::quietTargets(vpl,vpc,to).count() + generatorType::promotionTargets(vpl,vpc,to).count()) };
			const auto d{ (std::max(maxFrom,maxTo) + maxVictim) * maxDistance + 1 };
			return d * (pParameters[0]);
		}
		PYGMALION_INLINE static scoreType promoCaptureChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const playerType vpl, const pieceType vpc, const pieceType promoted) noexcept
		{
			constexpr const auto maxDistance{ generatorType::tropismType::maxDistance + 1 };
			const int maxFrom{ static_cast<int>(generatorType::quietTargets(pl,pc,from).count() + generatorType::promotionTargets(pl,pc,from).count()) };
			const int maxTo{ static_cast<int>(generatorType::quietTargets(pl,promoted,to).count() + generatorType::promotionTargets(pl,promoted,to).count()) };
			const int maxVictim{ static_cast<int>(generatorType::quietTargets(vpl,vpc,to).count() + generatorType::promotionTargets(vpl,vpc,to).count()) };
			const auto d{ (std::max(maxFrom,maxTo) + maxVictim) * maxDistance + 1 };
			return d * (pParameters[0]);
		}
	public:
		constexpr static size_t getParameterCount_Implementation() noexcept
		{
			return 6;
		}
		static parameterType getParameter_Implementation(const size_t index) noexcept
		{
			switch (index)
			{
			default:
				PYGMALION_ASSERT(false);
				return parameterType(scoreType::zero(), static_cast<scoreType>(0.0), static_cast<scoreType>(1.0), static_cast<scoreType>(0.001), "term_kingsafety_error");
			case 0:
				return parameterType(KingSafetyPawn, static_cast<scoreType>(0.0), static_cast<scoreType>(1.0), static_cast<scoreType>(0.001), "term_kingsafety_pawn");
			case 1:
				return parameterType(KingSafetyKnight, static_cast<scoreType>(0.0), static_cast<scoreType>(1.0), static_cast<scoreType>(0.001), "term_kingsafety_knight");
			case 2:
				return parameterType(KingSafetyBishop, static_cast<scoreType>(0.0), static_cast<scoreType>(1.0), static_cast<scoreType>(0.001), "term_kingsafety_bishop");
			case 3:
				return parameterType(KingSafetyRook, static_cast<scoreType>(0.0), static_cast<scoreType>(1.0), static_cast<scoreType>(0.001), "term_kingsafety_rook");
			case 4:
				return parameterType(KingSafetyQueen, static_cast<scoreType>(0.0), static_cast<scoreType>(1.0), static_cast<scoreType>(0.001), "term_kingsafety_queen");
			case 5:
				return parameterType(KingSafetyKing, static_cast<scoreType>(0.0), static_cast<scoreType>(1.0), static_cast<scoreType>(0.001), "term_kingsafety_king");
			}
		}
		static void setParameter_Implementation(const size_t index, scoreType value) noexcept
		{
			switch (index)
			{
			default:
				PYGMALION_ASSERT(false);
				break;
			case 0:
				KingSafetyPawn = value;
				break;
			case 1:
				KingSafetyKnight = value;
				break;
			case 2:
				KingSafetyBishop = value;
				break;
			case 3:
				KingSafetyRook = value;
				break;
			case 4:
				KingSafetyQueen = value;
				break;
			case 5:
				KingSafetyKing = value;
				break;
			}
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