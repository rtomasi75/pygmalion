namespace pygmalion
{
	template<typename DESCRIPTOR_MECHANICS>
	class base_mechanics :
		public DESCRIPTOR_MECHANICS
	{
	public:
		using descriptorMechanics = DESCRIPTOR_MECHANICS;
	};
}