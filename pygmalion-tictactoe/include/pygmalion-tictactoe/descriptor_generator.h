namespace pygmalion::tictactoe
{
	class descriptor_generator :
		public pygmalion::descriptor_generator<mechanics, 9>
	{
	public:
#if !defined(PYGMALION_CPU_BMI2)
	static inline movemagic<descriptor_generator> magic{ movemagic<descriptor_generator>(movemagicinfo(), 0x000b) };
#else
	static inline movemagic<descriptor_generator> magic{ movemagic<descriptor_generator>(movemagicinfo()) };
#endif
	};
}

 