namespace pygmalion::tictactoe
{
	class descriptor_dynamics :
		public pygmalion::descriptor_dynamics<motor, 9>
	{
	public:
		static inline movetable<descriptor_dynamics> moveTable{ movetable<descriptor_dynamics>(0x0095,9) };
	};

	class generator :
		public pygmalion::generator<descriptor_dynamics, generator>
	{
	public:
		using stackType = typename pygmalion::generator<descriptor_dynamics, generator>::stack;
		static bool isMoveLegal_Implementation(const stackType& stack, const movebitsType& mv) noexcept
		{
			return !stack.position().isOccupied(moveType::extractSquare(mv));
		}

		static bool generateMoves_Implementation(const stackType& stack, movelistType& moves, size_t& currentPass) noexcept
		{
			if (currentPass == 0)
			{
				moves = moveTable[static_cast<typename squaresType::bitsType>(stack.position().totalOccupancy())];
				currentPass++;
				return true;
			}
			else
				return false;
		}
		static bool generateTacticalMoves_Implementation(const stackType& stack, movelistType& moves, size_t& currentPass) noexcept
		{
			return false;
		}

	};
}