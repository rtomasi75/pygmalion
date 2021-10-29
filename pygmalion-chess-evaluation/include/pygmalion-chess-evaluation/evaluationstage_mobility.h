namespace pygmalion::chess
{
	class evaluationstage_mobility :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_mobility>
	{
	public:
		PYGMALION_TUNABLE static inline double Mobility{ 0.125 };
	private:
		PYGMALION_TUNABLE static inline scoreType MobilityFactor{ static_cast<scoreType>(Mobility / 64.0) };
		PYGMALION_TUNABLE static inline scoreType MobilityDelta{ static_cast<scoreType>(48.0 * Mobility / 64.0) };
	public:
		constexpr static size_t getParameterCount_Implementation() noexcept
		{
			return 1;
		}
		static parameter getParameter_Implementation(const size_t index) noexcept
		{
			return parameter(Mobility, 0.0, 1.0, 0.001, "term_mobility");
		}
#if defined(PYGMALION_TUNE)
		static void setParameter_Implementation(const size_t index, double value) noexcept
		{
			Mobility = value;
			MobilityFactor = static_cast<scoreType>(Mobility / 64.0);
			MobilityDelta= static_cast<scoreType>(48.0 * Mobility / 64.0);
		}
#endif
		PYGMALION_TUNABLE static scoreType computeDelta_Implementation() noexcept
		{
			return MobilityDelta;
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