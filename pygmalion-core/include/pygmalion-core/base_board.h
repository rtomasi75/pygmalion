namespace pygmalion
{
	template<typename DESCRIPTOR_BOARD>
	class base_board :
		public DESCRIPTOR_BOARD
	{
	public:
		using descriptorBoard = DESCRIPTOR_BOARD;
	};
}