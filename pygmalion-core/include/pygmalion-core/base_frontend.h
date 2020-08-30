namespace pygmalion
{
	template<typename DESCRIPTOR_FRONTEND>
	class base_frontend :
		public DESCRIPTOR_FRONTEND
	{
	public:
		using descriptorFrontend = DESCRIPTOR_FRONTEND;
	};
}