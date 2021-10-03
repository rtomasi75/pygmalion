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
		template<size_t PLAYER>
		static scoreType evaluate_Implementation(const generatorType::template stackType<PLAYER>& stack) noexcept
		{
			const squaresType targetedByBlack{ stack.template squaresTargetedByPlayer<static_cast<size_t>(blackPlayer)>() };
			const squaresType targetedByWhite{ stack.template squaresTargetedByPlayer<static_cast<size_t>(whitePlayer)>() };
			const int targets{ static_cast<int>(targetedByWhite.count()) - static_cast<int>(targetedByBlack.count()) };
			const scoreType scoreTargets{ targets * MobilityFactor };
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const bool invert{ movingPlayer == blackPlayer };
			if constexpr (invert)
				return -scoreTargets;
			else
				return scoreTargets;
		}
		static std::string name_Implementation() noexcept
		{
			return "mobility";
		}
	};
}