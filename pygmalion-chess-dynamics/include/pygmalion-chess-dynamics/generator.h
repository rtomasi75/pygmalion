namespace pygmalion::chess
{
	class generator :
		public pygmalion::generator<descriptor_dynamics, generator>
	{
	private:
		constexpr static const inline pygmalion::dynamics::movegen<motorType, propagator_knight> m_KnightPropagator{ pygmalion::dynamics::movegen<motorType, propagator_knight>(squaresType::all(),squaresType::all()) };
	public:
		using stackType = typename pygmalion::generator<descriptor_dynamics, generator>::stack;
	private:
		constexpr static void generateKnightMoves(const stackType& stack, movelistType& moves) noexcept
		{
			for (const squareType from : stack.position().pieceOccupancy(knight)& stack.position().playerOccupancy(stack.position().movingPlayer()))
			{
				for (const squareType to : m_KnightPropagator.targets(from, ~stack.position().totalOccupancy()))
				{
					moves.add(motorType::move().createQuiet(from, to));
				}
			}
		}
	public:
		static bool isMoveLegal_Implementation(const stackType& stack, const movebitsType& mv) noexcept
		{
			return true;
		}

		static bool generateMoves_Implementation(const stackType& stack, movelistType& moves, size_t& currentPass) noexcept
		{
			switch (currentPass)
			{
			default:
				return false;
			case 0:
				currentPass = 1;
				generateKnightMoves(stack, moves);
				return true;
			}
		}
		static bool generateTacticalMoves_Implementation(const stackType& stack, movelistType& moves, size_t& currentPass) noexcept
		{
			return false;
		}

	};
}