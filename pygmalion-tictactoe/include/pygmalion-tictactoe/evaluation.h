namespace pygmalion::tictactoe
{
	class evaluation :
		public pygmalion::evaluation<descriptor_evaluation, evaluation>
	{
	private:
		static const inline patterns<descriptorBoard> m_Patterns;
	public:
		constexpr static const auto& patterns() noexcept
		{
			return m_Patterns;
		}
		constexpr static gamestateType lateResult_Implementation(const stack& stack) noexcept
		{
			return gamestateType::draw();
		}
		static gamestateType earlyResult_Implementation(const stack& stack) noexcept
		{
			const boardType& position{ stack.position() };
			const playerType movingPlayer{ stack.position().movingPlayer() };
			bool canDecide = false;
			constexpr int winLength{ (countRanks + countFiles) / 2 };
			for (int line = 0; line < m_Patterns.countLines; line++)
			{
				const auto ctr1{ (position.playerOccupancy(static_cast<playerType>(0)) & m_Patterns.line(line)).populationCount() };
				if (ctr1 >= winLength)
				{
					return gamestateType::win(0);
				}
				const auto ctr2{ (position.playerOccupancy(static_cast<playerType>(1)) & m_Patterns.line(line)).populationCount() };
				if (ctr2 >= winLength)
				{
					return gamestateType::win(1);
				}
				canDecide |= (ctr1 == 0) | (ctr2 == 0);
			}
			return (canDecide && (position.totalOccupancy().populationCount() < 9)) ? gamestateType::open() : gamestateType::draw();
		}
		static objectiveType evaluate_Implementation(const stack& stack) noexcept
		{
			const auto& position{ stack.position() };
			auto sc = objectiveType::zero();
			for (int line = 0; line < m_Patterns.countLines; line++)
			{
				const auto ctr1 = (position.playerOccupancy(0) & m_Patterns.line(line)).populationCount();
				const auto ctr2 = (position.playerOccupancy(1) & m_Patterns.line(line)).populationCount();

				if ((ctr1 > 0) && (ctr2 == 0))
					sc += objectiveType::one() * (ctr1 * ctr1);
				if ((ctr2 > 0) && (ctr1 == 0))
					sc -= objectiveType::one() * (ctr2 * ctr2);
			}
			return sc;
		}
		constexpr static subjectiveType makeSubjective_Implementation(const objectiveType& sc, const playerType player) noexcept
		{
			return (player != 0) ? -sc : sc;
		}
		constexpr static objectiveType maxScore_Implementation(const playerType player) noexcept
		{
			return (player != 0) ? objectiveType::minimum() : objectiveType::maximum();
		}
		constexpr static objectiveType minScore_Implementation(const playerType player) noexcept
		{
			return (player != 0) ? objectiveType::maximum() : objectiveType::minimum();
		}
		constexpr static void plyDown_Implementation(objectiveType& sc) noexcept
		{
			sc = sc.plyDown();
		}
		constexpr static void plyUp_Implementation(objectiveType& sc) noexcept
		{
			sc = sc.plyUp();
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