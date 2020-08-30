namespace pygmalion
{
	template<typename DESCRIPTOR_GENERATOR>
	class base_generator :
		public DESCRIPTOR_GENERATOR
	{
	public:
		using descriptorGenerator = DESCRIPTOR_GENERATOR;
	};
}