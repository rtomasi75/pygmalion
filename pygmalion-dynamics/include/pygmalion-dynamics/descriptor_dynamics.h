namespace pygmalion
{
	template<typename MOTOR, size_t COUNT_MAX_GENERATED_MOVES, size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
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
		using scoreType = pygmalion::score<MANTISSA, SHIFT, MAXDIST>;
		using scorelistType = list<scoreType, countMaxGeneratedMoves>;
		using heuristicScore = score<62, SHIFT, 0>;
		constexpr static const size_t evaluationMantissa{ MANTISSA };
		constexpr static const size_t evaluationShift{ SHIFT };
		constexpr static const size_t evaluationMaxDistance{ MAXDIST };
	};

}