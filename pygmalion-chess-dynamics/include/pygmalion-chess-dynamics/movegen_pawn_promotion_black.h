namespace pygmalion::chess
{
	class propagator_pawn_promotion_black :
		public pygmalion::dynamics::propagator<descriptor_dynamics, 1, propagator_pawn_promotion_black, pygmalion::dynamics::ray<0, -1>>
	{};

	class movegen_pawn_promotion_black :
		public pygmalion::dynamics::movegen<motor, propagator_pawn_promotion_black>
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
		constexpr movegen_pawn_promotion_black() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_pawn_promotion_black>(pawnToSquares(), pawnFromSquares())
		{}
	};
}