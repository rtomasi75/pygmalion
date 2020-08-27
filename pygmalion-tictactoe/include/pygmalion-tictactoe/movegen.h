namespace pygmalion::tictactoe
{
	class movemagic;
	class movegen : public pygmalion::movegen<pygmalion::tictactoe::board, 9, true, pygmalion::tictactoe::board::movedata, pygmalion::tictactoe::movegen>
	{
	private:
		static movemagic m_Magic;
	public:
		static movemagic& magic() noexcept
		{
			return m_Magic;
		}

		static std::string name_Implementation() noexcept
		{
			return "TicTacToe ver. 1.0";
		}
		constexpr static gamestateType lateResult_Implementation(const stackType& stack) noexcept
		{
			return boardType::draw();
		}
		static gamestateType earlyResult_Implementation(const stackType& stack) noexcept
		{
			const auto& position{ stack.position() };
			const playerType movingPlayer{ stack.position().movingPlayer() };
			bool canDecide = false;
			for (int line = 0; line < patterns::lineCount; line++)
			{
				const auto ctr1{ (position.playerOccupancy(static_cast<playerType>(0)) & patterns::line(line)).populationCount() };
				if (ctr1 >= 3)
				{
					return boardType::win(0);
				}
				const auto ctr2{ (position.playerOccupancy(static_cast<playerType>(1)) & patterns::line(line)).populationCount() };
				if (ctr2 >= 3)
				{
					return boardType::win(1);
				}
				canDecide |= (ctr1 == 0) | (ctr2 == 0);
			}
			return (canDecide && (position.totalOccupancy().populationCount() < 9)) ? boardType::open() : boardType::draw();
		}
		static bool isMoveLegal_Implementation(const stackType& stack, const moveType& move) noexcept
		{
			const auto& position{ stack.position() };
			return !position.isOccupied(move.to());
		}
		static bool generateMoves_Implementation(const stackType& stack, movelistType& moves, int& currentPass) noexcept;
		constexpr static bool generateTacticalMoves_Implementation(const stackType& stack, movelistType& moves, int& currentPass) noexcept
		{
			return false;
		}
	};
}