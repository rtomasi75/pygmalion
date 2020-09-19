namespace pygmalion::chess
{
	using basemove = pygmalion::mechanics::disjunctivemove<board, pygmalion::mechanics::nullmove<board>, pygmalion::mechanics::dropmove<board>, pygmalion::mechanics::transportmove<board>, pygmalion::mechanics::capturemove<board>, pygmalion::mechanics::killmove<board>, pygmalion::mechanics::promotionmove<board>, pygmalion::mechanics::promocapturemove<board>, pygmalion::mechanics::setflagsmove<board, 4, 11>, pygmalion::mechanics::clearflagsmove<board, 4, 11> > ;
	using move = pygmalion::mechanics::conjunctivemove <board, pygmalion::mechanics::nextplayermove < board>, basemove>;

	using descriptor_mechanics = pygmalion::descriptor_mechanics<move>;

	class motor :
		public pygmalion::motor<descriptor_mechanics, motor>
	{

	};
}