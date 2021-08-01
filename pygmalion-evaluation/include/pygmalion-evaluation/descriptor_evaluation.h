namespace pygmalion
{
	template<typename GENERATOR, size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
	class descriptor_evaluation :
		public GENERATOR::descriptorDynamics
	{
	public:
		using generatorType = GENERATOR;
		using descriptorDynamics = typename GENERATOR::descriptorDynamics;
		using evaluationType = pygmalion::score<MANTISSA, SHIFT, MAXDIST>;
		constexpr static const size_t evaluationMantissa{ MANTISSA };
		constexpr static const size_t evaluationShift{ SHIFT };
		constexpr static const size_t evaluationMaxDistance{ MAXDIST };
	}; 

}