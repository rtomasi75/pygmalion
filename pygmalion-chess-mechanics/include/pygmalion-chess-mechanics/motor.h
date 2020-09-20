namespace pygmalion::chess
{
	using basemove = pygmalion::mechanics::disjunctivemove<board, queenpromotionmove, bishoppromotionmove, rookpromotionmove, knightpromotionmove, queenpromocapturemove, rookpromocapturemove, bishoppromocapturemove, knightpromocapturemove, doublepushmove, enpassantmove, castlingmove, quietmove, capturemove>;
	using move = basemove;

	using descriptor_mechanics = pygmalion::descriptor_mechanics<move>;

	class motor :
		public pygmalion::motor<descriptor_mechanics, motor>
	{

	};
}