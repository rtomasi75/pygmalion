namespace pygmalion::chess
{
	using descriptor_mechanics = pygmalion::descriptor_mechanics<combinedmoves, 10, 256>;

	class motor :
		public pygmalion::motor<descriptor_mechanics, motor>
	{

	};
}