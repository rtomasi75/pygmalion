namespace pygmalion::tictactoe
{
	class descriptor_evaluation :
		public pygmalion::descriptor_evaluation<generator, 7, 0, 10>
	{
	public:
	};

	class evaluator :
		public pygmalion::evaluator<descriptor_evaluation, evaluator>
	{
	private:
		static const inline patterns<descriptorEvaluation> m_Patterns;
	public:
		constexpr static subjectiveType makeSubjective_Implementation(const objectiveType& sc, const playerType player) noexcept
		{
			return (player != 0) ? -sc : sc;
		}
		constexpr static gamestateType lateResult_Implementation(const generatorType::stackType& stack) noexcept
		{
			return gamestateType::draw();
		}
		static gamestateType earlyResult_Implementation(const generatorType::stackType& stack) noexcept
		{
			const boardType& position{ stack.position() };
			const playerType movingPlayer{ stack.position().movingPlayer() };
			bool canDecide = false;
			constexpr int winLength{ (countRanks + countFiles) / 2 };
			for (int line = 0; line < m_Patterns.countLines; line++)
			{
				const auto ctr1{ (position.playerOccupancy(static_cast<playerType>(0)) & m_Patterns.line(line)).count() };
				if (ctr1 >= winLength)
				{
					return gamestateType::win(0);
				}
				const auto ctr2{ (position.playerOccupancy(static_cast<playerType>(1)) & m_Patterns.line(line)).count() };
				if (ctr2 >= winLength)
				{
					return gamestateType::win(1);
				}
				canDecide |= (ctr1 == 0) | (ctr2 == 0);
			}
			return (canDecide && (position.totalOccupancy().count() < 9)) ? gamestateType::open() : gamestateType::draw();
		}
		static objectiveType evaluate_Implementation(const generatorType::stackType& stack) noexcept
		{
			const auto& position{ stack.position() };
			auto sc = objectiveType::zero();
			for (int line = 0; line < m_Patterns.countLines; line++)
			{
				const auto ctr1 = (position.playerOccupancy(0) & m_Patterns.line(line)).count();
				const auto ctr2 = (position.playerOccupancy(1) & m_Patterns.line(line)).count();

				if ((ctr1 > 0) && (ctr2 == 0))
					sc += objectiveType::one() * (ctr1 * ctr1);
				if ((ctr2 > 0) && (ctr1 == 0))
					sc -= objectiveType::one() * (ctr2 * ctr2);
			}
			return sc;
		}
		constexpr static objectiveType maxScore_Implementation(const playerType player) noexcept
		{
			return (player != 0) ? objectiveType::minimum() : objectiveType::maximum();
		}
		constexpr static objectiveType minScore_Implementation(const playerType player) noexcept
		{
			return (player != 0) ? objectiveType::maximum() : objectiveType::minimum();
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