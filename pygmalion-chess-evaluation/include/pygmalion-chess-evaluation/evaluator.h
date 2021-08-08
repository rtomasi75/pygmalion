namespace pygmalion::chess
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
			const objectiveType sc{ static_cast<objectiveType>(stack.position().material()) };
			return sc;
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