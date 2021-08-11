namespace pygmalion::tictactoe
{
	using descriptor_mechanics = pygmalion::descriptor_mechanics<move, 4, 16>;

	class motor :
		public pygmalion::motor<descriptor_mechanics, motor>
	{

	};
}