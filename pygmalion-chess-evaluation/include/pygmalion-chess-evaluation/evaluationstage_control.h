namespace pygmalion::chess
{
	class evaluationstage_control :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_control, int>
	{
	public:
		PYGMALION_TUNABLE static inline double Control{ 0.25 };
	public:
		constexpr static size_t getParameterCount_Implementation() noexcept
		{
			return 1;
		}
		static parameter getParameter_Implementation(const size_t index) noexcept
		{
			return parameter(Control, 0.0, 1.0, 0.001, "term_control");
		}
		PYGMALION_TUNABLE static scoreType computeDelta_Implementation(const scoreType* pParameters) noexcept
		{
			return 48 * pParameters[0];
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static void computeData_Implementation(const generatorType::template stackType<PLAYER>& stack, int& data) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			squaresType controlledByBlack;
			squaresType controlledByWhite;
			stack.control(controlledByWhite, controlledByBlack);
			const int control{ static_cast<int>(controlledByWhite.count()) - static_cast<int>(controlledByBlack.count()) };
			if constexpr (movingPlayer == blackPlayer)
				data = -control;
			else
				data = control;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType evaluate_Implementation(const int data, const scoreType* pParameters) noexcept
		{
			const scoreType scoreControl{ data * pParameters[0] };
			return scoreControl;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType differentiate_Implementation(const dataType, const size_t parameterIndex, const scoreType* pParameters) noexcept
		{
			PYGMALION_ASSERT(parameterIndex == 0);
			return static_cast<scoreType>(data);
		}
		static std::string name_Implementation() noexcept
		{
			return "control";
		}
	};
}