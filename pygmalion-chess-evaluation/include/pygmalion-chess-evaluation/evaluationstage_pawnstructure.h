namespace pygmalion::chess
{
	class evaluationstage_pawnstructure :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_pawnstructure>
	{
	public:
		PYGMALION_TUNABLE static inline double PawnStructure{ 0.25 };
		PYGMALION_TUNABLE static inline scoreType PawnStructureDelta{ static_cast<scoreType>(1.5 * PawnStructure) };
		constexpr static size_t getParameterCount_Implementation() noexcept
		{
			return 1;
		}
		static parameter getParameter_Implementation(const size_t index) noexcept
		{
			return parameter(PawnStructure, 0.0, 1.0, 0.001, "term_pawnstructure");
		}
#if defined(PYGMALION_TUNE)
		static void setParameter_Implementation(const size_t index, double value) noexcept
		{
			PawnStructure = value;
			PawnStructureDelta = static_cast<scoreType>(1.5 * PawnStructure);
		}
#endif
		PYGMALION_TUNABLE static scoreType computeDelta_Implementation() noexcept
		{
			return PawnStructureDelta;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType evaluate_Implementation(const generatorType::template stackType<PLAYER>& stack) noexcept
		{
			const playerType movingPlayer{ stack.movingPlayer() };
			auto& entry{ generatorType::pawnTable().entry(stack) };
			scoreType pawnStructureScore;
			if (entry.hasPawnStructureScore(movingPlayer))
			{
				pawnStructureScore = entry.getPawnStructureScore(movingPlayer);
			}
			else
			{
				constexpr const scoreType zero{ scoreType::zero() };
				pawnStructureScore = zero;
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
					PYGMALION_TUNABLE const scoreType baseScore{ static_cast<scoreType>(PawnStructure) };
					if (distanceToPromotion > 0)
					{
						const int divisor{ 1 << distanceToPromotion };
						pawnStructureScore += baseScore / divisor;
					}
					else if (distanceToPromotion < 0)
					{
						const int divisor{ 1 << -distanceToPromotion };
						pawnStructureScore -= baseScore / divisor;
					}
				}
				entry.setPawnStructureScore(movingPlayer, pawnStructureScore);
			}
			const bool invert{ movingPlayer == blackPlayer };
			return invert ? -pawnStructureScore : pawnStructureScore;
		}
		static std::string name_Implementation() noexcept
		{
			return "pawnstructure";
		}
	};
}