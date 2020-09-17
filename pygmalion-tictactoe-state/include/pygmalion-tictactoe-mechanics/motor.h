namespace pygmalion::tictactoe
{
	using descriptor_mechanics = pygmalion::descriptor_mechanics<pygmalion::mechanics::drop<board>>;

	class motor :
		public pygmalion::motor<descriptor_mechanics, motor>
	{

	};
}