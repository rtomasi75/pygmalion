namespace pygmalion::chess
{
	using basemove = pygmalion::mechanics::disjunctivemove<doublepushmove> ;
	using move = doublepushmove;

	using descriptor_mechanics = pygmalion::descriptor_mechanics<move>;

	class motor :
		public pygmalion::motor<descriptor_mechanics, motor>
	{

	};
}