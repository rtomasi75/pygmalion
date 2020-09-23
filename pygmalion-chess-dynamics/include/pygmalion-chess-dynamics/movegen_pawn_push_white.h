namespace pygmalion::chess
{
	using propagator_pawn_push_white = pygmalion::dynamics::propagator<descriptor_dynamics, 1, pygmalion::dynamics::ray<0, 1>>;

	class movegen_pawn_push_white :
		public pygmalion::dynamics::movegen<motor, propagator_pawn_push_white>
	{
	private:
		constexpr static const squaresType pawnToSquares() noexcept
		{
			squaresType squares{ squaresType::none() };
			for (rankType rank = 2; rank < (countRanks - 2); rank++)
				squares |= static_cast<squaresType>(rank);
			return squares;
		}
		constexpr static const squaresType pawnFromSquares() noexcept
		{
			squaresType squares{ squaresType::none() };
			for (rankType rank = 1; rank < (countRanks - 3); rank++)
				squares |= static_cast<squaresType>(rank);
			return squares;
		}
	public:
		constexpr movegen_pawn_push_white() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_pawn_push_white>(pawnToSquares(), pawnFromSquares())
		{}
	};
}