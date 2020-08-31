namespace pygmalion::tictactoe
{
	class descriptor_generator :
		public pygmalion::descriptor_generator<mechanics, 9>
	{
	public:
		static inline movetable<descriptor_generator> moveTable{ movetable<descriptor_generator>(0x01ff, 0x0095, 9) };
	};
}

