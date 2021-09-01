namespace pygmalion::tictactoe
{
	class descriptor_evaluation :
		public pygmalion::descriptor_evaluation<generator>
	{
	public:
	};

	class evaluator :
		public pygmalion::evaluator<descriptor_evaluation, evaluator>
	{
	public:
		constexpr static scoreType aspirationWindowSize_Implementation(const size_t index) noexcept
		{
			return scoreType::zero();
		}
		constexpr static size_t countAspirationWindows_Implementation() noexcept
		{
			return 0;
		}
		static const inline patterns<descriptorEvaluation> m_Patterns;
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commandsImplementation() noexcept
		{
			std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ std::deque<std::shared_ptr<pygmalion::intrinsics::command>>() };
			return list;
		}
		constexpr static gamestateType lateResult_Implementation(const generatorType::stackType& stack) noexcept
		{
			return gamestateType::draw();
		}
		static gamestateType earlyResult_Implementation(const generatorType::stackType& stack, bool& allowStoreTT) noexcept
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
					allowStoreTT = true;
					return gamestateType::win(0);
				}
				const auto ctr2{ (position.playerOccupancy(static_cast<playerType>(1)) & m_Patterns.line(line)).count() };
				if (ctr2 >= winLength)
				{
					allowStoreTT = true;
					return gamestateType::win(1);
				}
				canDecide |= (ctr1 == 0) | (ctr2 == 0);
			}
			allowStoreTT = true;
			return (canDecide && (position.totalOccupancy().count() < 9)) ? gamestateType::open() : gamestateType::draw();
		}
		static scoreType evaluate_Implementation(const scoreType alpha, const scoreType beta, const generatorType::stackType& stack) noexcept
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
			return stack.movingPlayer() == playerType(0) ? sc : -sc;
		}
	};
}