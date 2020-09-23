namespace pygmalion::chess
{
	using propagator_pawn_doublepush_white = pygmalion::dynamics::propagator<descriptor_dynamics, 2, pygmalion::dynamics::ray<0, 1>>;

	class movegen_pawn_doublepush_white :
		public pygmalion::dynamics::movegen<motor, propagator_pawn_doublepush_white>
	{
	private:
		constexpr static const squaresType pawnToSquares() noexcept
		{
			squaresType squares{ squaresType::none() };
			squares |= static_cast<squaresType>(static_cast<rankType>(3));
			return squares;
		}
		constexpr static const squaresType pawnFromSquares() noexcept
		{
			squaresType squares{ squaresType::none() };
			squares |= static_cast<squaresType>(static_cast<rankType>(1));
			return squares;
		}
	public:
		constexpr movegen_pawn_doublepush_white() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_pawn_doublepush_white>(pawnToSquares(), pawnFromSquares())
		{}
	};
}