namespace pygmalion::tictactoe
{
	class generator :
		public pygmalion::generator<descriptor_generator, generator>
	{
	public:
		static std::string name_Implementation() noexcept
		{
			return "TicTacToe ver. 1.0";
		}

		static bool isMoveLegal_Implementation(const stack& stack, const moveType& mv) noexcept
		{
			return !stack.position().isOccupied(mv.square(0));
		}

		static bool generateMoves_Implementation(const stack& stack, movelistType& moves, int& currentPass) noexcept
		{
			if (currentPass == 0)
			{
				moves = magic[static_cast<typename squaresType::bitsType>(stack.position().totalOccupancy())];
				currentPass++;
				return true;
			}
			else
				return false;
		}
		static bool generateTacticalMoves_Implementation(const stack& stack, movelistType& moves, int& currentPass) noexcept
		{
			return false;
		}

		using stackType = stack;
	};
}