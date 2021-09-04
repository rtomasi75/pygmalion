namespace pygmalion::chess
{
	class heuristics;

	using descriptor_search = pygmalion::descriptor_search<evaluator, 128, true, true, true, 2, false, true, 2, true, heuristics>;
	//using descriptor_search = pygmalion::descriptor_search<evaluator, 128, true, true, true, 2, false, true, 2, false, heuristics>;
	//using descriptor_search = pygmalion::descriptor_search<evaluator, 128, true, true, true, 2, false, true, 0, false, heuristics>;
}
