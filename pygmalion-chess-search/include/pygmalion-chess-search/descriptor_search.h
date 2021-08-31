namespace pygmalion::chess
{
	class heuristics;

	using descriptor_search = pygmalion::descriptor_search<evaluator, 64, true, true, true, true, false, true, 2, true, heuristics>;
}
