namespace pygmalion
{
	template<typename MECHANICS, int COUNT_MAX_GENERATED_MOVES>
	class descriptor_generator :
		public base_mechanics<typename MECHANICS::descriptorMechanics>
	{
	public:
		constexpr static int countMaxGeneratedMoves{ COUNT_MAX_GENERATED_MOVES };
		using mechanicsType = MECHANICS;
		using boardType = typename mechanicsType::boardType;
		using movelistType = list<typename mechanicsType::descriptorMechanics::moveType, countMaxGeneratedMoves>;
		using indexType = typename movelistType::counterType;
		using movedataType = typename mechanicsType::movedataType;
	};

}