namespace pygmalion::tictactoe
{
	class evaluator : public pygmalion::evaluator<pygmalion::tictactoe::movegen, pygmalion::score<8, 0, 9>, pygmalion::score<8, 0, 9>, pygmalion::tictactoe::evaluator >
	{
	public:
		static auto evaluate_Implementation(const stackType& stack) noexcept
		{
			const auto& position{ stack.position() };
			auto sc = objectiveType::zero();
			for (int line = 0; line < patterns::lineCount; line++)
			{
				const auto ctr1 = (position.playerOccupancy(0) & patterns::line(line)).populationCount();
				const auto ctr2 = (position.playerOccupancy(1) & patterns::line(line)).populationCount();

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