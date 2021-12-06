namespace pygmalion::chess
{
	class evaluationstage_pawnstructure :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_pawnstructure, typename descriptor_evaluation::scoreType>
	{
	public:
		PYGMALION_TUNABLE static inline double PawnStructure{ 0.5 };
		PYGMALION_TUNABLE static inline scoreType PawnStructureDelta{ static_cast<scoreType>(1.5 * PawnStructure) };
		constexpr static size_t getParameterCount_Implementation() noexcept
		{
			return 1;
		}
		static parameter getParameter_Implementation(const size_t index) noexcept
		{
			return parameter(PawnStructure, 0.0, 1.0, 0.001, "term_pawnstructure");
		}
		PYGMALION_TUNABLE static scoreType computeDelta_Implementation(const scoreType* pParameters) noexcept
		{
			return (3 * pParameters[0]) / 2;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static void computeData_Implementation(const generatorType::template stackType<PLAYER>& stack, scoreType& data) noexcept
		{
			auto& entry{ generatorType::pawnTable().entry(stack) };
			constexpr const playerType movingPlayer0{ static_cast<playerType>(PLAYER) };
			constexpr const playerType otherPlayer0{ movingPlayer0.next() };
			if (!entry.hasPawnStructureScore(movingPlayer0))
			{
				for (const auto movingPlayer : playerType::range)
				{
					constexpr const scoreType zero{ scoreType::zero() };
					scoreType pawnStructureScore{ zero };
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
						constexpr const scoreType baseScore{ static_cast<scoreType>(1.0) };
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
					constexpr bool invert{ movingPlayer0 == blackPlayer };
					if constexpr (invert)
						entry.setPawnStructureScore(movingPlayer, -pawnStructureScore);
					else
						entry.setPawnStructureScore(movingPlayer, pawnStructureScore);
				}
			}
			data = entry.getPawnStructureScore(movingPlayer0) + entry.getPawnStructureScore(otherPlayer0);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType evaluate_Implementation(const scoreType data, const scoreType* pParameters) noexcept
		{
			return pParameters[0] * data;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType differentiate_Implementation(const dataType, const size_t parameterIndex, const scoreType* pParameters) noexcept
		{
			PYGMALION_ASSERT(parameterIndex == 0);
			return static_cast<scoreType>(data);
		}
		PYGMALION_INLINE static std::string name_Implementation() noexcept
		{
			return "pawnstructure";
		}
	};
}