namespace pygmalion::chess
{
	class evaluationstage_mobility :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_mobility, int>
	{
	public:
		PYGMALION_TUNABLE static inline double Mobility{ 0.125 / 64.0 };
	private:
	public:
		constexpr static size_t getParameterCount_Implementation() noexcept
		{
			return 1;
		}
		static parameter getParameter_Implementation(const size_t index) noexcept
		{
			return parameter(Mobility, 0.0, 1.0, 0.001, "term_mobility");
		}
		PYGMALION_TUNABLE static scoreType computeDelta_Implementation(const scoreType* pParameters) noexcept
		{
			return 48 * pParameters[0];
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static void computeData_Implementation(const generatorType::template stackType<PLAYER>& stack, int& data) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			const squaresType targetedByBlack{ stack.template squaresTargetedByPlayer<static_cast<size_t>(blackPlayer)>() };
			const squaresType targetedByWhite{ stack.template squaresTargetedByPlayer<static_cast<size_t>(whitePlayer)>() };
			const int targets{ static_cast<int>(targetedByWhite.count()) - static_cast<int>(targetedByBlack.count()) };
			if constexpr (movingPlayer == blackPlayer)
				data = -targets;
			else
				data = targets;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType evaluate_Implementation(const int data, const scoreType* pParameters) noexcept
		{
			const scoreType scoreTargets{ data * pParameters[0] };
			return scoreTargets;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType differentiate_Implementation(const dataType, const size_t parameterIndex, const scoreType* pParameters) noexcept
		{
			PYGMALION_ASSERT(parameterIndex == 0);
			return static_cast<scoreType>(data);
		}
		static std::string name_Implementation() noexcept
		{
			return "mobility";
		}
	};
}