namespace pygmalion
{
	template<typename DESCRIPTION_EVALUATION,typename SUBJECTIVE>
	class objective;
	
	template<typename GENERATOR>
	class descriptor_evaluation :
		public GENERATOR::descriptorDynamics
	{
	public:
		using generatorType = GENERATOR;
		using descriptorDynamics = typename GENERATOR::descriptorDynamics;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;

	}; 

}