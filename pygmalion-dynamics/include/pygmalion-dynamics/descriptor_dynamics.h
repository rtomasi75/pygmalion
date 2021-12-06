namespace pygmalion
{
	template<typename MOTOR, size_t COUNT_MAX_GENERATED_MOVES>
	class descriptor_dynamics :
		public MOTOR::descriptorMechanics
	{
	public:
		constexpr static size_t countMaxGeneratedMoves{ COUNT_MAX_GENERATED_MOVES };
		using passType = size_t;
		using passlistType = list<passType, countMaxGeneratedMoves>;
		using stageType= size_t;
		using stagelistType = list<stageType, countMaxGeneratedMoves>;
		using motorType = MOTOR;
		using descriptorMechanics = typename MOTOR::descriptorMechanics;
		using movelistType = list<typename descriptorMechanics::movebitsType, countMaxGeneratedMoves>;
		using indexType = typename movelistType::counterType;
		using scorelistType = list<typename descriptorMechanics::scoreType, countMaxGeneratedMoves>;
		using heuristicScore = score<62, descriptorMechanics::scoreShift, 0>;
	};

}