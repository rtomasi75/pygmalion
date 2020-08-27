namespace pygmalion
{
	template<typename MOVEGEN, typename EVALUATOR, size_t MAXDEPTH>
	class search
	{
	public:
		using movegenType = MOVEGEN;
		using playerType = typename movegenType::playerType;
		using squareType = typename movegenType::squareType;
		using pieceType = typename movegenType::pieceType;
		using boardType = typename movegenType::boardType;
		using moveType = typename movegenType::moveType;
		using gamestateType = typename movegenType::gamestateType;
		using evaluatorType = EVALUATOR;
		using subjectiveType = typename evaluatorType::subjectiveType;
		using objectiveType = typename evaluatorType::objectiveType;
		using multiscoreType = multiscore<evaluatorType>;
		constexpr static int maxDepth{ MAXDEPTH };
		using variationType = list<moveType, maxDepth>;
		using depthType = typename variationType::counterType;
		using nodeType = node<search>;
		static auto pvs(const boardType& board, variationType& principalVariation, const depthType depth, uint64_t& nodeCount) noexcept
		{
			boardType b{ board };
			nodeType node(b);
			principalVariation.clear();
			multiscoreType alphabeta;
			return node.search(alphabeta, depth, 0, principalVariation, nodeCount);
		}
		static auto perft(const boardType& board, const depthType depth, uint64_t& nodeCount) noexcept
		{
			boardType b{ board };
			nodeType node(b);
			return node.perft(depth, 0, nodeCount);
		}
	};
}