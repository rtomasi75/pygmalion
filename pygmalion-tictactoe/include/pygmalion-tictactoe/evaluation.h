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
		static scoreType evaluate_Implementation(const stack& stack) noexcept
		{
			const auto& position{ stack.position() };
			auto sc = scoreType::zero();
			for (int line = 0; line < m_Patterns.countLines; line++)
			{
				const auto ctr1 = (position.playerOccupancy(0) & m_Patterns.line(line)).count();
				const auto ctr2 = (position.playerOccupancy(1) & m_Patterns.line(line)).count();

				if ((ctr1 > 0) && (ctr2 == 0))
					sc += scoreType::one() * (ctr1 * ctr1);
				if ((ctr2 > 0) && (ctr1 == 0))
					sc -= scoreType::one() * (ctr2 * ctr2);
			}
			return sc;
		}
		constexpr static subjectiveType makeSubjective_Implementation(const scoreType& sc, const playerType player) noexcept
		{
			return (player != 0) ? -sc : sc;
		}
		constexpr static scoreType maxScore_Implementation(const playerType player) noexcept
		{
			return (player != 0) ? scoreType::minimum() : scoreType::maximum();
		}
		constexpr static scoreType minScore_Implementation(const playerType player) noexcept
		{
			return (player != 0) ? scoreType::maximum() : scoreType::minimum();
		}
		constexpr static void plyDown_Implementation(scoreType& sc) noexcept
		{
			sc = sc.plyDown();
		}
		constexpr static void plyUp_Implementation(scoreType& sc) noexcept
		{
			sc = sc.plyUp();
		}
		constexpr static scoreType neutralScore_Implementation() noexcept
		{
			return scoreType::zero();
		}
		constexpr static scoreType winScore_Implementation(const playerType player) noexcept
		{
			return (player > 0) ? scoreType::loss() : scoreType::win();
		}
		constexpr static scoreType lossScore_Implementation(const playerType player) noexcept
		{
			return (player > 0) ? scoreType::win() : scoreType::loss();
		}
	};
}