namespace pygmalion::chess
{
	class evaluationstage_pawnstructure :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_pawnstructure, typename descriptor_evaluation::objectiveType>
	{
	private:
		constexpr static inline size_t whitePlayerIndex{ static_cast<size_t>(descriptor_evaluation::whitePlayer) };
		constexpr static inline size_t blackPlayerIndex{ static_cast<size_t>(descriptor_evaluation::blackPlayer) };
	public:
		static inline scoreType PawnStructure{ static_cast<scoreType>(0.5) };
		constexpr static size_t getParameterCount_Implementation() noexcept
		{
			return 1;
		}
		static parameterType getParameter_Implementation(const size_t index) noexcept
		{
			return parameterType(PawnStructure, static_cast<scoreType>(0.0), static_cast<scoreType>(1.0), static_cast<scoreType>(0.001), "term_pawnstructure");
		}
		PYGMALION_INLINE static scoreType quietChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to) noexcept
		{
			constexpr const scoreType zero{ scoreType::zero() };
/*			constexpr const scoreType baseScore{ static_cast<scoreType>(1.0) };
			if (pc == pawn)
			{
				const auto distanceToPromotion{ spl == whitePlayer ? pawnstructure::maxQuiet1(pl) + pawnstructure::maxQuiet2(pl) + pawnstructure::maxQuiet3(pl) : pawnstructure::minQuiet1(pl) + pawnstructure::minQuiet2(pl) + pawnstructure::minQuiet3(pl) };
				scoreType pawnStructureScoreWhite{ zero };
				scoreType pawnStructureScoreBlack{ zero };
				if (distanceToPromotion > 0)
				{
					const int divisor{ 1 << distanceToPromotion };
					pawnStructureScoreWhite += baseScore / divisor;
				}
				else if (distanceToPromotion < 0)
				{
					const int divisor{ 1 << -distanceToPromotion };
					pawnStructureScoreBlack += baseScore / divisor;
				}
				const objectiveType scoreWhite{ objectiveType::template makeObjective<static_cast<size_t>(whitePlayer)>(pawnStructureScoreWhite) };
				const objectiveType scoreBlack{ objectiveType::template makeObjective<static_cast<size_t>(blackPlayer)>(pawnStructureScoreBlack) };
				return (scoreWhite + scoreBlack).makeSubjective(spl) * pParameters[0];
			}
			else*/
				return zero;
		}
		PYGMALION_INLINE static scoreType promotionChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const pieceType promoted) noexcept
		{
			constexpr const scoreType zero{ scoreType::zero() };
	/*		constexpr const scoreType baseScore{ static_cast<scoreType>(1.0) };
			if (pc == pawn)
			{
				const auto distanceToPromotion{ spl == whitePlayer ? pawnstructure::maxPromotion1(pl) + pawnstructure::maxPromotion2(pl) + pawnstructure::maxPromotion3(pl) : pawnstructure::minPromotion1(pl) + pawnstructure::minPromotion2(pl) + pawnstructure::minPromotion3(pl) };
				scoreType pawnStructureScoreWhite{ zero };
				scoreType pawnStructureScoreBlack{ zero };
				if (distanceToPromotion > 0)
				{
					const int divisor{ 1 << distanceToPromotion };
					pawnStructureScoreWhite += baseScore / divisor;
				}
				else if (distanceToPromotion < 0)
				{
					const int divisor{ 1 << -distanceToPromotion };
					pawnStructureScoreBlack += baseScore / divisor;
				}
				const objectiveType scoreWhite{ objectiveType::template makeObjective<static_cast<size_t>(whitePlayer)>(pawnStructureScoreWhite) };
				const objectiveType scoreBlack{ objectiveType::template makeObjective<static_cast<size_t>(blackPlayer)>(pawnStructureScoreBlack) };
				return (scoreWhite + scoreBlack).makeSubjective(spl) * pParameters[0];
			}
			else*/
				return zero;
		}
		PYGMALION_INLINE static scoreType captureChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const playerType vpl, const pieceType vpc) noexcept
		{
		constexpr const scoreType zero{ scoreType::zero() };
/*				constexpr const scoreType baseScore{ static_cast<scoreType>(1.0) };
			if (pc == pawn)
			{
				if (vpc == pawn)
				{
					const auto distanceToPromotion{ spl == whitePlayer ? pawnstructure::maxCapture1(pl) + pawnstructure::maxCapture2(pl) + pawnstructure::maxCapture3(pl) : pawnstructure::minCapture1(pl) + pawnstructure::minCapture2(pl) + pawnstructure::minCapture3(pl) };
					scoreType pawnStructureScoreWhite{ zero };
					scoreType pawnStructureScoreBlack{ zero };
					if (distanceToPromotion > 0)
					{
						const int divisor{ 1 << distanceToPromotion };
						pawnStructureScoreWhite += baseScore / divisor;
					}
					else if (distanceToPromotion < 0)
					{
						const int divisor{ 1 << -distanceToPromotion };
						pawnStructureScoreBlack += baseScore / divisor;
					}
					const objectiveType scoreWhite{ objectiveType::template makeObjective<static_cast<size_t>(whitePlayer)>(pawnStructureScoreWhite) };
					const objectiveType scoreBlack{ objectiveType::template makeObjective<static_cast<size_t>(blackPlayer)>(pawnStructureScoreBlack) };
					return (scoreWhite + scoreBlack).makeSubjective(spl) * pParameters[0];
				}
				else*/
					return zero;
/* }
			else
			{
				if (vpc == pawn)
				{
					const auto distanceToPromotion{ spl == whitePlayer ? pawnstructure::maxDeath1(vpl) + pawnstructure::maxDeath2(vpl) + pawnstructure::maxDeath3(vpl) : pawnstructure::minDeath1(vpl) + pawnstructure::minDeath2(vpl) + pawnstructure::minDeath3(vpl) };
					scoreType pawnStructureScoreWhite{ zero };
					scoreType pawnStructureScoreBlack{ zero };
					if (distanceToPromotion > 0)
					{
						const int divisor{ 1 << distanceToPromotion };
						pawnStructureScoreWhite += baseScore / divisor;
					}
					else if (distanceToPromotion < 0)
					{
						const int divisor{ 1 << -distanceToPromotion };
						pawnStructureScoreBlack += baseScore / divisor;
					}
					const objectiveType scoreWhite{ objectiveType::template makeObjective<static_cast<size_t>(whitePlayer)>(pawnStructureScoreWhite) };
					const objectiveType scoreBlack{ objectiveType::template makeObjective<static_cast<size_t>(blackPlayer)>(pawnStructureScoreBlack) };
					return (scoreWhite + scoreBlack).makeSubjective(spl) * pParameters[0];
				}
				else
				{
					const auto distanceToPromotion{ spl == whitePlayer ? pawnstructure::maxCaptureOther1(pl) + pawnstructure::maxCaptureOther2(pl) + pawnstructure::maxCaptureOther3(pl) : pawnstructure::minCaptureOther1(pl) + pawnstructure::minCaptureOther2(pl) + pawnstructure::minCaptureOther3(pl) };
					scoreType pawnStructureScoreWhite{ zero };
					scoreType pawnStructureScoreBlack{ zero };
					if (distanceToPromotion > 0)
					{
						const int divisor{ 1 << distanceToPromotion };
						pawnStructureScoreWhite += baseScore / divisor;
					}
					else if (distanceToPromotion < 0)
					{
						const int divisor{ 1 << -distanceToPromotion };
						pawnStructureScoreBlack += baseScore / divisor;
					}
					const objectiveType scoreWhite{ objectiveType::template makeObjective<static_cast<size_t>(whitePlayer)>(pawnStructureScoreWhite) };
					const objectiveType scoreBlack{ objectiveType::template makeObjective<static_cast<size_t>(blackPlayer)>(pawnStructureScoreBlack) };
					return (scoreWhite + scoreBlack).makeSubjective(spl) * pParameters[0];
				}
			}*/
		}
		PYGMALION_INLINE static scoreType promoCaptureChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const playerType vpl, const pieceType vpc, const pieceType promoted) noexcept
		{
			constexpr const scoreType zero{ scoreType::zero() };
			/*constexpr const scoreType baseScore{ static_cast<scoreType>(1.0) };
			if (pc == pawn)
			{
				const auto distanceToPromotion{ spl == whitePlayer ? pawnstructure::maxPromotion1(pl) + pawnstructure::maxPromotion2(pl) + pawnstructure::maxPromotion3(pl) : pawnstructure::minPromotion1(pl) + pawnstructure::minPromotion2(pl) + pawnstructure::minPromotion3(pl) };
				scoreType pawnStructureScoreWhite{ zero };
				scoreType pawnStructureScoreBlack{ zero };
				if (distanceToPromotion > 0)
				{
					const int divisor{ 1 << distanceToPromotion };
					pawnStructureScoreWhite += baseScore / divisor;
				}
				else if (distanceToPromotion < 0)
				{
					const int divisor{ 1 << -distanceToPromotion };
					pawnStructureScoreBlack += baseScore / divisor;
				}
				const objectiveType scoreWhite{ objectiveType::template makeObjective<static_cast<size_t>(whitePlayer)>(pawnStructureScoreWhite) };
				const objectiveType scoreBlack{ objectiveType::template makeObjective<static_cast<size_t>(blackPlayer)>(pawnStructureScoreBlack) };
				return (scoreWhite + scoreBlack).makeSubjective(spl) * pParameters[0];
			}
			else*/
				return zero;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static void computeData_Implementation(const generatorType::template stackType<PLAYER>& stack, dataType& data) noexcept
		{
			auto& entry{ generatorType::pawnTable().entry(stack) };
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const playerType otherPlayer{ movingPlayer.next() };
			if (!entry.hasPawnStructureScore(movingPlayer))
			{
				constexpr const scoreType zero{ scoreType::zero() };
				std::int8_t whiteRanks[countFiles];
				std::int8_t blackRanks[countFiles];
				for (const auto file : fileType::range)
				{
					if (entry.pawns(whitePlayer) & file)
					{
						const squareType sq{ (entry.pawns(whitePlayer) & file).last() };
						whiteRanks[file] = static_cast<std::int8_t>(sq.rank());
					}
					else
						whiteRanks[file] = 0;
					if (entry.pawns(blackPlayer) & file)
					{
						const squareType sq{ (entry.pawns(blackPlayer) & file).first() };
						blackRanks[file] = static_cast<std::int8_t>(sq.rank());
					}
					else
						blackRanks[file] = 0;
				}
				scoreType pawnStructureScoreWhite{ zero };
				scoreType pawnStructureScoreBlack{ zero };
				for (size_t i = 0; i < countFiles; i++)
				{
					std::int8_t whiteRank1;
					std::int8_t whiteRank2;
					std::int8_t whiteRank3;
					std::int8_t blackRank1;
					std::int8_t blackRank2;
					std::int8_t blackRank3;
					if (i > 0)
					{
						whiteRank1 = whiteRanks[i - 1];
						blackRank1 = blackRanks[i - 1];
					}
					else
					{
						whiteRank1 = 0;
						blackRank1 = 0;
					}
					whiteRank2 = whiteRanks[i];
					blackRank2 = blackRanks[i];
					if (i < (countFiles - 1))
					{
						whiteRank3 = whiteRanks[i + 1];
						blackRank3 = blackRanks[i + 1];
					}
					else
					{
						whiteRank3 = 0;
						blackRank3 = 0;
					}
					std::int8_t distanceToPromotion{ pawnstructure::distance(movingPlayer, whiteRank1, whiteRank2, whiteRank3, blackRank1, blackRank2, blackRank3) };
					constexpr const scoreType baseScore{ static_cast<scoreType>(1.0) };
					if (distanceToPromotion > 0)
					{
						const int divisor{ 1 << distanceToPromotion };
						pawnStructureScoreWhite += baseScore / divisor;
					}
					else if (distanceToPromotion < 0)
					{
						const int divisor{ 1 << -distanceToPromotion };
						pawnStructureScoreBlack += baseScore / divisor;
					}
				}
				const objectiveType scoreWhite{ objectiveType::template makeObjective<whitePlayerIndex>(pawnStructureScoreWhite) };
				const objectiveType scoreBlack{ objectiveType::template makeObjective<blackPlayerIndex>(pawnStructureScoreBlack) };
				entry.setPawnStructureScore(movingPlayer, scoreWhite + scoreBlack);
			}
			data = entry.getPawnStructureScore(movingPlayer);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType evaluate_Implementation(const dataType& data, const scoreType* pParameters) noexcept
		{
			return pParameters[0] * (data.template makeSubjective<PLAYER>());
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType differentiate_Implementation(const dataType& data, const size_t parameterIndex, const scoreType* pParameters) noexcept
		{
			PYGMALION_ASSERT(parameterIndex == 0);
			return data.template makeSubjective<PLAYER>();
		}
		PYGMALION_INLINE static std::string name_Implementation() noexcept
		{
			return "pawnstructure";
		}
	};
}