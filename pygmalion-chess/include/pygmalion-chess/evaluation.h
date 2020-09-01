namespace pygmalion::chess
{
	class evaluation : 
		public pygmalion::evaluation<descriptor_evaluation,evaluation>
	{
	private:
		static inline const evaluationTables<descriptor_evaluation> materialTable;
	public:
		constexpr static objectiveType material(const board::playerType p, const board::pieceType pc, const board::squareType sq) noexcept
		{
			assert(p.isValid());
			assert(pc.isValid());
			assert(sq.isValid());
			return materialTable.material(p, pc, sq);
		}
		static objectiveType evaluate_Implementation(const stackType& stack) noexcept
		{
			return neutralScore();
		}
		constexpr static auto makeSubjective_Implementation(const objectiveType& sc, const playerType player) noexcept
		{
			return (player > 0) ? -sc : sc;
		}
		constexpr static auto maxScore_Implementation(const playerType player) noexcept
		{
			return (player > 0) ? objectiveType::minimum() : objectiveType::maximum();
		}
		constexpr static auto minScore_Implementation(const playerType player) noexcept
		{
			return (player > 0) ? objectiveType::maximum() : objectiveType::minimum();
		}
		constexpr static void plyDown_Implementation(objectiveType& sc) noexcept
		{
			sc = sc.plyDown();
		}
		constexpr static void plyUp_Implementation(objectiveType& sc) noexcept
		{
			sc = sc.plyUp();
		}
		constexpr static auto neutralScore_Implementation() noexcept
		{
			return objectiveType::zero();
		}
		constexpr static auto winScore_Implementation(const playerType player) noexcept
		{
			return (player > 0) ? objectiveType::loss() : objectiveType::win();
		}
		constexpr static auto lossScore_Implementation(const playerType player) noexcept
		{
			return (player > 0) ? objectiveType::win() : objectiveType::loss();
		}
	};
}