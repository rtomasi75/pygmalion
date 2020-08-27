namespace pygmalion
{
	template<typename MOVEGEN, typename SUBJECTIVESCORE, typename OBJECTIVESCORE, typename INSTANCE>
	class evaluator
	{
	public:
		using movegenType = MOVEGEN;
		using subjectiveType = SUBJECTIVESCORE;
		using objectiveType = OBJECTIVESCORE;
		using instanceType = INSTANCE;
		using playerType = typename movegenType::playerType;
		using squareType = typename movegenType::squareType;
		using pieceType = typename movegenType::pieceType;
		using boardType = typename movegenType::boardType;
		using moveType = typename movegenType::moveType;
		using stackType = typename movegenType::stackType;
		using gamestateType = typename movegenType::gamestateType;
		static auto evaluate(const stackType& stack) noexcept
		{
			return instanceType::evaluate_Implementation(stack);
		}
		constexpr static auto makeSubjective(const objectiveType& sc, const playerType player) noexcept
		{
			return instanceType::makeSubjective_Implementation(sc, player);
		}
		constexpr static auto maxScore(const playerType player) noexcept
		{
			return instanceType::maxScore_Implementation(player);
		}
		constexpr static auto neutralScore() noexcept
		{
			return instanceType::neutralScore_Implementation();
		}
		constexpr static auto winScore(const playerType player) noexcept
		{
			return instanceType::winScore_Implementation(player);
		}
		constexpr static auto lossScore(const playerType player) noexcept
		{
			return instanceType::lossScore_Implementation(player);
		}
		constexpr static auto minScore(const playerType player) noexcept
		{
			return instanceType::minScore_Implementation(player);
		}
		constexpr static void plyDown(objectiveType& sc) noexcept
		{
			instanceType::plyDown_Implementation(sc);
		}
		constexpr static void plyUp(objectiveType& sc) noexcept
		{
			instanceType::plyDown_Implementation(sc);
		}
	};
}