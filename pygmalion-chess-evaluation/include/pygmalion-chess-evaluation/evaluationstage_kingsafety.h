namespace pygmalion::chess
{
	class evaluationstage_kingsafety :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_kingsafety>
	{
	public:
		constexpr static inline double KingSafety{ 0.025 };
		constexpr static inline double KingAreaSafety{ 0.0125 };
	private:
		class scoreLookUp
		{
		private:
			std::array<scoreType, generatorType::tropismType::maxDistance + 1> m_Score;
		public:
			constexpr scoreLookUp(const double maxValue) noexcept :
				m_Score{ arrayhelper::make< generatorType::tropismType::maxDistance + 1 ,scoreType>(scoreType::zero()) }
			{
				double value{ maxValue };
				std::array<scoreType, generatorType::tropismType::maxDistance + 1> scores;
				m_Score[0] = static_cast<scoreType>(value);
				for (unsigned int i = 1; i <= generatorType::tropismType::maxDistance; i++)
				{
					value *= 0.5;
					m_Score[i] = static_cast<scoreType>(value);
				}
			}
			const scoreType& operator[](const size_t index) const noexcept
			{
				return m_Score[index];
			}
			~scoreLookUp() noexcept = default;
			constexpr scoreLookUp(const scoreLookUp&) noexcept = default;
			constexpr scoreLookUp(scoreLookUp&&) noexcept = default;
			constexpr scoreLookUp& operator=(const scoreLookUp&) noexcept = default;
			constexpr scoreLookUp& operator=(scoreLookUp&&) noexcept = default;
		};
		static inline scoreLookUp m_KingAreaSafetyScores{ scoreLookUp(KingAreaSafety) };
		static inline scoreLookUp m_KingSafetyScores{ scoreLookUp(KingSafety) };
		template<size_t PLAYER>
		static scoreType scoreKingsafety(const generatorType::template stackType<PLAYER>& stack, const playerType player) noexcept
		{
			const playerType otherPlayer{ player.next() };
			const squareType kingSquare{ stack.kingSquare(player) };
			const squareType opponentKing{ stack.kingSquare(otherPlayer) };
			const squaresType kingArea{ generatorType::kingArea(kingSquare) & ~stack.position().playerOccupancy(player) };
			const std::array<squaresType, countPieces> pieces{ arrayhelper::generate<countPieces,squaresType>([&stack,otherPlayer](const size_t index) {return stack.position().pieceOccupancy(static_cast<pieceType>(index)) & stack.position().playerOccupancy(otherPlayer); }) };
			const auto& entry{ pawntable::entry(stack) };
			size_t counterKingSafety{ 0 };
			size_t counterKingAreaSafety{ 0 };
			for (const auto pc : pieceType::range)
			{
				if (pieces[pc])
				{
					for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
					{
						counterKingSafety += (entry.kingTropism(otherPlayer).distanceSquares(pc, d) & pieces[pc]).count();
						counterKingAreaSafety += (entry.kingAreaTropism(otherPlayer).distanceSquares(pc, d) & pieces[pc]).count();
					}
				}
			}
			scoreType safetyScore{ scoreType::zero() };
			for (unsigned int d = 0; d <= generatorType::tropismType::maxDistance; d++)
			{
				safetyScore -= static_cast<typename scoreType::valueType>(counterKingSafety) * m_KingSafetyScores[d];
				safetyScore -= static_cast<typename scoreType::valueType>(counterKingAreaSafety) * m_KingAreaSafetyScores[d];
			}
			return safetyScore;
		}
	public:
		constexpr static scoreType computeDelta_Implementation() noexcept
		{
			return static_cast<scoreType>(0.5 * (KingSafety + KingAreaSafety));
		}
		template<size_t PLAYER>
		static scoreType evaluate_Implementation(const generatorType::template stackType<PLAYER>& stack) noexcept
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