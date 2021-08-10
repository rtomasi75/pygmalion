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
	public:
		constexpr static inline double Mobility{ 0.125 };
		constexpr static inline double Attack{ 0.125 };
		constexpr static inline double Control{ 0.25 };
	private:
		constexpr static inline objectiveType m_MobilityFactor{ static_cast<objectiveType>(Mobility / 64.0) };
		constexpr static inline objectiveType m_AttackFactor{ static_cast<objectiveType>(Attack / 64.0) };
		constexpr static inline objectiveType m_ControlFactor{ static_cast<objectiveType>(Control / 64.0) };
		constexpr static inline subjectiveType m_DeltaMobility{ static_cast<subjectiveType>(Mobility) };
		constexpr static inline subjectiveType m_DeltaAttack{ static_cast<subjectiveType>(Attack) };
		constexpr static inline subjectiveType m_DeltaControl{ static_cast<subjectiveType>(Control) };
		static objectiveType attack(const generatorType::stackType& stack) noexcept;
		static objectiveType mobility(const generatorType::stackType& stack) noexcept;
		static objectiveType control(const generatorType::stackType& stack) noexcept;
	public:
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commandsImplementation() noexcept;
		static gamestateType earlyResult_Implementation(const generatorType::stackType& stack) noexcept;
		static gamestateType lateResult_Implementation(const typename generatorType::stackType& stack) noexcept;
		static objectiveType evaluate_Implementation(const multiscoreType& score, const generatorType::stackType& stack) noexcept;
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