namespace pygmalion
{
	template<typename DESCRIPTOR_FRONT>
	class base_frontend :
		public DESCRIPTOR_FRONT
	{
	public:
		using descriptorFrontend = DESCRIPTOR_FRONT;
	};
}