namespace pygmalion::chess
{
	class propagator_pawn_promocapture_white :
		public pygmalion::dynamics::propagator<descriptor_dynamics, 1, propagator_pawn_promocapture_white, pygmalion::dynamics::ray<1, 1>, pygmalion::dynamics::ray<-1, 1>>
	{};

	class movegen_pawn_promocapture_white :
		public pygmalion::dynamics::movegen<motor, propagator_pawn_promocapture_white>
	{
	private:
		constexpr static const squaresType pawnToSquares() noexcept
		{
			return static_cast<squaresType>(static_cast<squareType>(countRanks - 1));
		}
		constexpr static const squaresType pawnFromSquares() noexcept
		{
			return static_cast<squaresType>(static_cast<squareType>(countRanks - 2));
		}
	public:
		constexpr movegen_pawn_promocapture_white() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_pawn_promocapture_white>(pawnToSquares(), pawnFromSquares())
		{}
	};
}