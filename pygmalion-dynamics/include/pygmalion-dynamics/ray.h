namespace pygmalion::dynamics
{
	template<int INC_FILE, int INC_RANK>
	class ray 
	{
	public:
		constexpr static int fileIncrement{ INC_FILE };
		constexpr static int rankIncrement{ INC_RANK };
	};
}