namespace pygmalion::chess
{
	using propagator_pawn_doublepush_black = pygmalion::dynamics::propagator<descriptor_dynamics, 2, pygmalion::dynamics::ray<0, -1>>;

	class movegen_pawn_doublepush_black :
		public pygmalion::dynamics::movegen<motor, propagator_pawn_doublepush_black>
	{
	private:
		constexpr static const squaresType pawnToSquares() noexcept
		{
			squaresType squares{ squaresType::none() };
			squares |= static_cast<squaresType>(static_cast<rankType>(countRanks - 4));
			return squares;
		}
		constexpr static const squaresType pawnFromSquares() noexcept
		{
			squaresType squares{ squaresType::none() };
			squares |= static_cast<squaresType>(static_cast<rankType>(countRanks - 2));
			return squares;
		}
	public:
		constexpr movegen_pawn_doublepush_black() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_pawn_doublepush_black>(pawnToSquares(), pawnFromSquares())
		{}
	};
}