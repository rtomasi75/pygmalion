namespace pygmalion::chess
{
	class evaluationstage_attacks :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_attacks>
	{
	public:
		PYGMALION_TUNABLE static inline double Attack{ 0.125 };
	private:
		PYGMALION_TUNABLE static inline scoreType AttackFactor{ static_cast<scoreType>(Attack / 64.0) };
		PYGMALION_TUNABLE static inline scoreType AttackDelta{ static_cast<scoreType>(48.0 * Attack / 64.0) };
	public:
		constexpr static size_t getParameterCount_Implementation() noexcept
		{
			return 1;
		}
		static parameter getParameter_Implementation(const size_t index) noexcept
		{
			return parameter(Attack, 0.0, 1.0, 0.001, "term_attack");
		}
#if defined(PYGMALION_TUNE)
		static void setParameter_Implementation(const size_t index, double value) noexcept
		{
			Attack = value;
			AttackFactor = static_cast<scoreType>(Attack / 64.0);
			AttackDelta = static_cast<scoreType>(48.0 * Attack / 64.0);
		}
#endif
		PYGMALION_TUNABLE static scoreType computeDelta_Implementation() noexcept
		{
			return AttackDelta;
		}
		template<size_t PLAYER>
		static scoreType evaluate_Implementation(const generatorType::template stackType<PLAYER>& stack) noexcept
		{
			const squaresType attackedByBlack{ stack.template squaresAttackedByPlayer<static_cast<size_t>(blackPlayer)>() };
			const squaresType attackedByWhite{ stack.template squaresAttackedByPlayer<static_cast<size_t>(whitePlayer)>() };
			const int attacks{ static_cast<int>(attackedByWhite.count()) - static_cast<int>(attackedByBlack.count()) };
			const scoreType scoreAttacks{ attacks * AttackFactor };
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr const bool invert{ movingPlayer == blackPlayer };
			if constexpr (invert)
				return -scoreAttacks;
			else
				return scoreAttacks;
		}
		static std::string name_Implementation() noexcept
		{
			return "attacks";
		}
	};
}