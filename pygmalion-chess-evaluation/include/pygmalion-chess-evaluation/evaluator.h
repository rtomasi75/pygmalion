namespace pygmalion::chess
{
	class descriptor_evaluation :
		public pygmalion::descriptor_evaluation<generator, 31, 15, 10>
	{
	public:
	};

	class evaluator :
		public pygmalion::evaluator<descriptor_evaluation, evaluator>
	{
	private:
		constexpr static inline objectiveType m_MobilityFactor{ static_cast<objectiveType>(0.125 / 64.0) };
		constexpr static inline objectiveType m_AttackFactor{ static_cast<objectiveType>(0.125 / 64.0) };
		static objectiveType mobility(const generatorType::stackType& stack) noexcept
		{
			const squaresType attackedByBlack{ stack.squaresAttackedByPlayer(blackPlayer) };
			const squaresType attackedByWhite{ stack.squaresAttackedByPlayer(whitePlayer) };
			const squaresType targetedByBlack{ stack.squaresTargetedByPlayer(blackPlayer) };
			const squaresType targetedByWhite{ stack.squaresTargetedByPlayer(whitePlayer) };
			const int attacks{ static_cast<int>(attackedByWhite.count()) - static_cast<int>(attackedByBlack.count()) };
			const int targets{ static_cast<int>(targetedByWhite.count()) - static_cast<int>(targetedByBlack.count()) };
			const objectiveType scoreTargets{ targets * m_MobilityFactor };
			const objectiveType scoreAttacks{ attacks * m_AttackFactor };
			return scoreTargets + scoreAttacks;
		}
	public:
		static gamestateType earlyResult_Implementation(const generatorType::stackType& stack) noexcept
		{
			return gamestateType::open();
		}
		static gamestateType lateResult_Implementation(const typename generatorType::stackType& stack) noexcept
		{
			if (stack.isCheck())
				return gamestateType::loss(stack.position().movingPlayer());
			else
				return gamestateType::draw();
		}
		static objectiveType evaluate_Implementation(const generatorType::stackType& stack) noexcept
		{
			const objectiveType mat{ static_cast<objectiveType>(stack.position().material()) };
			const objectiveType mob{ mobility(stack) };
			return mat + mob;
		}
		constexpr static subjectiveType makeSubjective_Implementation(const objectiveType& sc, const playerType player) noexcept
		{
			return (player > 0) ? -sc : sc;
		}
		constexpr static objectiveType maxScore_Implementation(const playerType player) noexcept
		{
			return (player > 0) ? objectiveType::minimum() : objectiveType::maximum();
		}
		constexpr static objectiveType minScore_Implementation(const playerType player) noexcept
		{
			return (player > 0) ? objectiveType::maximum() : objectiveType::minimum();
		}
		constexpr static objectiveType neutralScore_Implementation() noexcept
		{
			return objectiveType::zero();
		}
		constexpr static objectiveType winScore_Implementation(const playerType player) noexcept
		{
			return (player > 0) ? objectiveType::loss() : objectiveType::win();
		}
		constexpr static objectiveType lossScore_Implementation(const playerType player) noexcept
		{
			return (player > 0) ? objectiveType::win() : objectiveType::loss();
		}
	};
}