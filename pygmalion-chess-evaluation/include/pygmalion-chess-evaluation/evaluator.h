namespace pygmalion::chess
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
		constexpr static inline double Mobility{ 0.125 };
		constexpr static inline double Attack{ 0.125 };
		constexpr static inline double Control{ 0.25 };
	private:
		constexpr static inline scoreType MobilityFactor{ static_cast<scoreType>(Mobility / 64.0) };
		constexpr static inline scoreType AttackFactor{ static_cast<scoreType>(Attack / 64.0) };
		constexpr static inline scoreType ControlFactor{ static_cast<scoreType>(Control / 64.0) };
		constexpr static inline scoreType DeltaMobility{ static_cast<scoreType>(Mobility) };
		constexpr static inline scoreType DeltaAttack{ static_cast<scoreType>(Attack) };
		constexpr static inline scoreType DeltaControl{ static_cast<scoreType>(Control) };
		constexpr static inline size_t CountStages{ 3 };
		static inline scoreType Delta[]{ DeltaMobility + DeltaAttack + DeltaControl,DeltaAttack + DeltaControl,DeltaControl };
		static scoreType attack(const generatorType::stackType& stack) noexcept;
		static scoreType mobility(const generatorType::stackType& stack) noexcept;
		static scoreType control(const generatorType::stackType& stack) noexcept;
		constexpr static scoreType evaluationFunction(int i, const generatorType::stackType& stack) noexcept
		{
			switch (i)
			{
			default:
				assert(0);
				return scoreType::zero();
			case 0:
				return attack(stack);
			case 1:
				return mobility(stack);
			case 2:
				return control(stack);
			}
		}
	public:
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commandsImplementation() noexcept;
		static gamestateType earlyResult_Implementation(const generatorType::stackType& stack) noexcept;
		static gamestateType lateResult_Implementation(const typename generatorType::stackType& stack) noexcept;
		static scoreType evaluate_Implementation(const scoreType alpha, const scoreType beta, const generatorType::stackType& stack) noexcept;
	};
}