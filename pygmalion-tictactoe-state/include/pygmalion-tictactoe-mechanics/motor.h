namespace pygmalion::tictactoe
{
	using move = pygmalion::mechanics::conjunctivemove<board, pygmalion::mechanics::nullmove<board>, pygmalion::mechanics::dropmove<board>>;

	using descriptor_mechanics = pygmalion::descriptor_mechanics<move>;

	class motor :
		public pygmalion::motor<descriptor_mechanics, motor>
	{

	};
}