namespace pygmalion
{

	template<typename GENERATOR, size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
	class descriptor_evaluation :
		public GENERATOR::descriptorDynamics
	{
	public:
		using generatorType = GENERATOR;
		using descriptorDynamics = typename GENERATOR::descriptorDynamics;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using parameterType = typename pygmalion::evaluation::parameter<descriptor_evaluation>;
		using evaluationType = pygmalion::score<MANTISSA, SHIFT, MAXDIST>;
		constexpr static const size_t evaluationMantissa{ MANTISSA };
		constexpr static const size_t evaluationShift{ SHIFT };
		constexpr static const size_t evaluationMaxDistance{ MAXDIST };
	};

}