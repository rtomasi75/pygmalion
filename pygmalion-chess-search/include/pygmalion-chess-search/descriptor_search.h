namespace pygmalion::chess
{
	class heuristics;

	using descriptor_search = pygmalion::descriptor_search<evaluator, 128, true, true, 2, false, true, 2, true, true, heuristics>;
}
