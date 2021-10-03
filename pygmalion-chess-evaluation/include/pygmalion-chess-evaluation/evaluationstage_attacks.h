namespace pygmalion::chess
{
	class evaluationstage_attacks :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_attacks>
	{
	public:
		constexpr static inline double Attack{ 0.125 };
	private:
		constexpr static inline scoreType AttackFactor{ static_cast<scoreType>(Attack / 64.0) };
	public:
		constexpr static scoreType computeDelta_Implementation() noexcept
		{
			return static_cast<scoreType>(48.0 * Attack / 64.0);
		}
		template<size_t PLAYER>
		static scoreType evaluate_Implementation(const generatorType::template stackType<PLAYER>& stack) noexcept
		{
			const squaresType attackedByBlack{ stack.squaresAttackedByPlayer(blackPlayer) };
			const squaresType attackedByWhite{ stack.squaresAttackedByPlayer(whitePlayer) };
			const int attacks{ static_cast<int>(attackedByWhite.count()) - static_cast<int>(attackedByBlack.count()) };
			const scoreType scoreAttacks{ attacks * AttackFactor };
			const bool invert{ stack.movingPlayer() == blackPlayer };
			return invert ? -scoreAttacks : scoreAttacks;
		}
		static std::string name_Implementation() noexcept
		{
			return "attacks";
		}
	};
}