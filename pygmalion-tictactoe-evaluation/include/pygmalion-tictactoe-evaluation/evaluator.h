namespace pygmalion::tictactoe
{
	class descriptor_evaluation :
		public pygmalion::descriptor_evaluation<generator>
	{
	public:
	};

	class evaluator :
		public pygmalion::evaluator<descriptor_evaluation, evaluator>
	{
	public:
		constexpr static scoreType initialAspirationWindowSize() noexcept
		{
			constexpr const scoreType zero{ scoreType::zero() };
			return zero;
		}
		PYGMALION_INLINE constexpr static size_t countAspirationWindows() noexcept
		{
			return 0;
		}
		static const inline patterns<descriptorEvaluation> m_Patterns;
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commandsImplementation() noexcept
		{
			std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ std::deque<std::shared_ptr<pygmalion::intrinsics::command>>() };
			return list;
		}
		template<size_t PLAYER>
		constexpr static gamestateType lateResult_Implementation(const generatorType::template stackType<PLAYER>& stack) noexcept
		{
			return gamestateType::draw();
		}
		template<size_t PLAYER, bool LAZY>
		static gamestateType earlyResult_Implementation(const generatorType::template stackType<PLAYER>& stack, bool& allowStoreTT) noexcept
		{
			const boardType& position{ stack.position() };
			const playerType movingPlayer{ stack.position().movingPlayer() };
			bool canDecide = false;
			constexpr int winLength{ (countRanks + countFiles) / 2 };
			for (int line = 0; line < m_Patterns.countLines; line++)
			{
				const auto ctr1{ (position.playerOccupancy(static_cast<playerType>(0)) & m_Patterns.line(line)).count() };
				if (ctr1 >= winLength)
				{
					allowStoreTT = true;
					return gamestateType::win(0);
				}
				const auto ctr2{ (position.playerOccupancy(static_cast<playerType>(1)) & m_Patterns.line(line)).count() };
				if (ctr2 >= winLength)
				{
					allowStoreTT = true;
					return gamestateType::win(1);
				}
				canDecide |= (ctr1 == 0) | (ctr2 == 0);
			}
			allowStoreTT = true;
			return (canDecide && (position.totalOccupancy().count() < 9)) ? gamestateType::open() : gamestateType::draw();
		}
		template<size_t PLAYER>
		static scoreType computeMaterial_Implementation(const typename generatorType::template stackType<PLAYER>& stack) noexcept
		{
			const auto& position{ stack.position() };
			constexpr const scoreType zero{ scoreType::zero() };
			auto sc = zero;
			for (int line = 0; line < m_Patterns.countLines; line++)
			{
				const auto ctr1 = (position.playerOccupancy(0) & m_Patterns.line(line)).count();
				const auto ctr2 = (position.playerOccupancy(1) & m_Patterns.line(line)).count();
				constexpr const scoreType one{ scoreType::one() };
				if ((ctr1 > 0) && (ctr2 == 0))
					sc += one * (ctr1 * ctr1);
				if ((ctr2 > 0) && (ctr1 == 0))
					sc -= one * (ctr2 * ctr2);
			}
			return stack.movingPlayer() == playerType(0) ? sc : -sc;
		}
		static scoreType staticTacticalMoveScore_Implementation(const boardType& position, const movebitsType move) noexcept
		{
			PYGMALION_ASSERT(false);
			constexpr const scoreType zero{ scoreType::zero() };
			return zero;
		}
	};
}