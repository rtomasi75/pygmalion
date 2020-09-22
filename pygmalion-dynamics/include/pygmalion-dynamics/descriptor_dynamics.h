namespace pygmalion
{
	template<typename MECHANICS, int COUNT_MAX_GENERATED_MOVES>
	class descriptor_dynamics :
		public MECHANICS::descriptorMechanics
	{
	public:
		constexpr static const int countMaxGeneratedMoves{ COUNT_MAX_GENERATED_MOVES };
		using mechanicsType = MECHANICS;
		using movelistType = list<typename mechanicsType::descriptorMechanics::movebitsType, countMaxGeneratedMoves>;
		using indexType = typename movelistType::counterType;
	};

}