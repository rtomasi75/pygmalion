namespace pygmalion::chess
{
	using descriptor_mechanics = pygmalion::descriptor_mechanics<combinedmoves>;

	class motor :
		public pygmalion::motor<descriptor_mechanics, motor>
	{

	};
}