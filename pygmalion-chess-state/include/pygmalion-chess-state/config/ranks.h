namespace pygmalion::config::chess
{
	class rank1_Info :
		public rankInfo
	{
	public:
		constexpr rank1_Info() noexcept :
			rankInfo("1", "rank_1")
		{

		}
	};

	class rank2_Info :
		public rankInfo
	{
	public:
		constexpr rank2_Info() noexcept :
			rankInfo("2", "rank_2")
		{

		}
	};

	class rank3_Info :
		public rankInfo
	{
	public:
		constexpr rank3_Info() noexcept :
			rankInfo("3", "rank_3")
		{

		}
	};

	class rank4_Info :
		public rankInfo
	{
	public:
		constexpr rank4_Info() noexcept :
			rankInfo("4", "rank_4")
		{

		}
	};

	class rank5_Info :
		public rankInfo
	{
	public:
		constexpr rank5_Info() noexcept :
			rankInfo("5", "rank_5")
		{

		}
	};

	class rank6_Info :
		public rankInfo
	{
	public:
		constexpr rank6_Info() noexcept :
			rankInfo("6", "rank_6")
		{

		}
	};

	class rank7_Info :
		public rankInfo
	{
	public:
		constexpr rank7_Info() noexcept :
			rankInfo("7", "rank_7")
		{

		}
	};

	class rank8_Info :
		public rankInfo
	{
	public:
		constexpr rank8_Info() noexcept :
			rankInfo("8", "rank_8")
		{

		}
	};

	class standardranksInfo :
		public ranksInfo<rank1_Info, rank2_Info, rank3_Info, rank4_Info, rank5_Info, rank6_Info, rank7_Info, rank8_Info>
	{
	public:
		constexpr standardranksInfo() noexcept :
			ranksInfo<rank1_Info, rank2_Info, rank3_Info, rank4_Info, rank5_Info, rank6_Info, rank7_Info, rank8_Info>(
				rank1_Info(),
				rank2_Info(),
				rank3_Info(),
				rank4_Info(),
				rank5_Info(),
				rank6_Info(),
				rank7_Info(),
				rank8_Info())
		{

		}
	};
}