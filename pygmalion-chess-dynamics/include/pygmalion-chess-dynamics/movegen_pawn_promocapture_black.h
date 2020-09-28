namespace pygmalion::chess
{
	class propagator_pawn_promocapture_black:
		public pygmalion::dynamics::propagator<descriptor_dynamics, 1, propagator_pawn_promocapture_black, pygmalion::dynamics::ray<1, -1>, pygmalion::dynamics::ray<-1, -1>>
	{};

	class movegen_pawn_promocapture_black :
		public pygmalion::dynamics::movegen<motor, propagator_pawn_promocapture_black>
	{
	private:
		constexpr static const squaresType pawnToSquares() noexcept
		{
			return static_cast<squaresType>(static_cast<rankType>(0));
		}
		constexpr static const squaresType pawnFromSquares() noexcept
		{
			return static_cast<squaresType>(static_cast<rankType>(1));
		}
	public:
		constexpr movegen_pawn_promocapture_black() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_pawn_promocapture_black>(pawnToSquares(), pawnFromSquares())
		{}
	};
}