namespace pygmalion
{
	template<typename DESCRIPTOR_EVALUATION>
	class base_evaluation :
		public DESCRIPTOR_EVALUATION
	{
	public:
		using descriptorEvaluation = DESCRIPTOR_EVALUATION;
	};
}