namespace pygmalion
{
	template<typename MOTOR, size_t COUNT_MAX_GENERATED_MOVES, size_t MANTISSA, size_t SHIFT, size_t MAXDIST, size_t COUNT_PASSES,size_t COUNT_TACTICALPASSES>
	class descriptor_dynamics :
		public MOTOR::descriptorMechanics
	{
	public:
		constexpr static const size_t countPasses{ COUNT_PASSES };
		constexpr static const size_t countTacticalPasses{ COUNT_TACTICALPASSES };
		constexpr static const size_t countMaxGeneratedMoves{ COUNT_MAX_GENERATED_MOVES };
		using motorType = MOTOR;
		using descriptorMechanics = typename MOTOR::descriptorMechanics;
		using movelistType = list<typename descriptorMechanics::movebitsType, countMaxGeneratedMoves>;
		using indexType = typename movelistType::counterType;
		using scoreType = pygmalion::score<MANTISSA, SHIFT, MAXDIST>;
		constexpr static const size_t evaluationMantissa{ MANTISSA };
		constexpr static const size_t evaluationShift{ SHIFT };
		constexpr static const size_t evaluationMaxDistance{ MAXDIST };
	};

}