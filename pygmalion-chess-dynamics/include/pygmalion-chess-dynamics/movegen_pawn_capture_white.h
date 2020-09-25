namespace pygmalion::chess
{
	class propagator_pawn_capture_white :
		public pygmalion::dynamics::propagator<descriptor_dynamics, 1, propagator_pawn_capture_white, pygmalion::dynamics::ray<1, 1>, pygmalion::dynamics::ray<-1, 1>>
	{};

	class movegen_pawn_capture_white :
		public pygmalion::dynamics::movegen<motor, propagator_pawn_capture_white>
	{
	private:
		constexpr static const squaresType pawnToSquares() noexcept
		{
			squaresType squares{ squaresType::none() };
			for (rankType rank = 1; rank < (countRanks - 2); rank++)
				squares |= static_cast<squaresType>(rank);
			return squares;
		}
		constexpr static const squaresType pawnFromSquares() noexcept
		{
			squaresType squares{ squaresType::none() };
			for (rankType rank = 2; rank < (countRanks - 1); rank++)
				squares |= static_cast<squaresType>(rank);
			return squares;
		}
	public:
		constexpr movegen_pawn_capture_white() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_pawn_capture_white>(pawnToSquares(), pawnFromSquares())
		{}
	};
}