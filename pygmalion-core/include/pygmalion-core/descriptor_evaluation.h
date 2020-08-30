namespace pygmalion
{
	template<typename GENERATOR, int COUNT_SCORE_BITS_MANTISSA, int COUNT_SCORE_BITS_SHIFT, int COUNT_SCORE_PLIES>
	class descriptor_evaluation :
		public base_generator<typename GENERATOR::descriptorGenerator>
	{
	public:
		constexpr static int countScoreBitsMantissa{ COUNT_SCORE_BITS_MANTISSA };
		constexpr static int countScoreBitsShift{ COUNT_SCORE_BITS_SHIFT };
		constexpr static int countScorePlies{ COUNT_SCORE_PLIES };
		using generatorType = GENERATOR;
		using gamestateType = gamestate<GENERATOR::countPlayers>;
		using objectiveType = score<countScoreBitsMantissa, countScoreBitsShift, countScorePlies>;
		using subjectiveType = score<countScoreBitsMantissa, countScoreBitsShift, countScorePlies>;
	};

}