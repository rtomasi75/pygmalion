namespace pygmalion::chess
{
	class evaluationstage_control :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_control>
	{
	public:
		PYGMALION_TUNABLE static inline double Control{ 0.25 };
	private:
		PYGMALION_TUNABLE static inline scoreType ControlFactor{ static_cast<scoreType>(Control / 64.0) };
		PYGMALION_TUNABLE static inline scoreType ControlDelta{ static_cast<scoreType>(48.0 * Control / 64.0) };
	public:
		constexpr static size_t getParameterCount_Implementation() noexcept
		{
			return 1;
		}
		static parameter getParameter_Implementation(const size_t index) noexcept
		{
			return parameter(Control, 0.0, 1.0, 0.001, "term_control");
		}
#if defined(PYGMALION_TUNE)
		static void setParameter_Implementation(const size_t index, double value) noexcept
		{
			Control = value;
			ControlFactor = static_cast<scoreType>(Control / 64.0);
			ControlDelta = static_cast<scoreType>(48.0 * Control / 64.0);
		}
#endif
		PYGMALION_TUNABLE static scoreType computeDelta_Implementation() noexcept
		{
			return ControlDelta;
		}
		template<size_t PLAYER>
		static scoreType evaluate_Implementation(const generatorType::template stackType<PLAYER>& stack) noexcept
		{
			squaresType controlledByBlack;
			squaresType controlledByWhite;
			stack.control(controlledByWhite, controlledByBlack);
			const int control{ static_cast<int>(controlledByWhite.count()) - static_cast<int>(controlledByBlack.count()) };
			const scoreType scoreControl{ control * ControlFactor };
			const bool invert{ stack.movingPlayer() == blackPlayer };
			return invert ? -scoreControl : scoreControl;
		}
		static std::string name_Implementation() noexcept
		{
			return "control";
		}
	};
}