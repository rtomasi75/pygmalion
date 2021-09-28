namespace pygmalion::chess
{
	class evaluationstage_control :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_control>
	{
	public:
		constexpr static inline double Control{ 0.25 };
	private:
		constexpr static inline scoreType ControlFactor{ static_cast<scoreType>(Control / 64.0) };
		constexpr static inline scoreType ControlDelta{ static_cast<scoreType>(48.0 * Control / 64.0) };
	public:
		constexpr static scoreType computeDelta_Implementation() noexcept
		{
			return ControlDelta;
		}
		static scoreType evaluate_Implementation(const generatorType::stackType& stack) noexcept
		{
			squaresType controlledByBlack;
			squaresType controlledByWhite;
			stack.control(controlledByWhite, controlledByBlack);
			const int control{ static_cast<int>(controlledByWhite.count()) - static_cast<int>(controlledByBlack.count()) };
			const scoreType scoreControl{ control * ControlFactor };
			const bool invert{ stack.movingPlayer() == blackPlayer };
			return invert ? -scoreControl : scoreControl;
		}
	};
}