namespace pygmalion::chess
{
	class evaluator : public pygmalion::evaluator<pygmalion::chess::movegen, pygmalion::chess::score, pygmalion::chess::score, pygmalion::chess::evaluator >
	{
	private:
		static const evaluationTables m_Tables;
	public:
		constexpr static auto material(const board::player p, const board::piece pc, const board::square sq) noexcept
		{
			assert(p.isValid());
			assert(pc.isValid());
			assert(sq.isValid());
			return m_Tables.material(p, pc, sq);
		}
		static objectiveType evaluate_Implementation(const stackType& stack) noexcept
		{
			return stack.position().getMaterial();
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