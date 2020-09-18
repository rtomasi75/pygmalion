namespace pygmalion::tictactoe
{
	using move = pygmalion::mechanics::combinedmove<board, pygmalion::mechanics::nullmove<board>, pygmalion::mechanics::drop<board>>;

	using descriptor_mechanics = pygmalion::descriptor_mechanics<move>;

	class motor :
		public pygmalion::motor<descriptor_mechanics, motor>
	{

	};
}