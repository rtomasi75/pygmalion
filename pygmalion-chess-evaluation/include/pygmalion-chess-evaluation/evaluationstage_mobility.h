namespace pygmalion::chess
{
	class evaluationstage_mobility :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_mobility>
	{
	public:
		constexpr static inline double Mobility{ 0.125 };
	private:
		constexpr static inline scoreType MobilityFactor{ static_cast<scoreType>(Mobility / 64.0) };
	public:
		constexpr static scoreType computeDelta_Implementation() noexcept
		{
			return static_cast<scoreType>(48.0 * Mobility / 64.0);
		}
		static scoreType evaluate_Implementation(const generatorType::stackType& stack) noexcept
		{
			const squaresType targetedByBlack{ stack.squaresTargetedByPlayer(blackPlayer) };
			const squaresType targetedByWhite{ stack.squaresTargetedByPlayer(whitePlayer) };
			const int targets{ static_cast<int>(targetedByWhite.count()) - static_cast<int>(targetedByBlack.count()) };
			const scoreType scoreTargets{ targets * MobilityFactor };
			const bool invert{ stack.movingPlayer() == blackPlayer };
			return invert ? -scoreTargets : scoreTargets;
		}
		static std::string name_Implementation() noexcept
		{
			return "mobility";
		}
	};
}