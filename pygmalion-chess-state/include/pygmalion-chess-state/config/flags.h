namespace pygmalion::config::chess
{
	class flagWhiteKingsideCastleright_Info :
		public flagInfo
	{
	public:
		constexpr flagWhiteKingsideCastleright_Info() noexcept :
			flagInfo("K", "flag_castleright_kingside_white")
		{

		}
	};

	class flagBlackKingsideCastleright_Info :
		public flagInfo
	{
	public:
		constexpr flagBlackKingsideCastleright_Info() noexcept :
			flagInfo("k", "flag_castleright_kingside_black")
		{

		}
	};

	class flagWhiteQueensideCastleright_Info :
		public flagInfo
	{
	public:
		constexpr flagWhiteQueensideCastleright_Info() noexcept :
			flagInfo("Q", "flag_castleright_queenside_white")
		{

		}
	};

	class flagBlackQueensideCastleright_Info :
		public flagInfo
	{
	public:
		constexpr flagBlackQueensideCastleright_Info() noexcept :
			flagInfo("q", "flag_castleright_queenside_black")
		{

		}
	};

	class standardflagsInfo :
		public flagsInfo<flagWhiteKingsideCastleright_Info, flagWhiteQueensideCastleright_Info, flagBlackKingsideCastleright_Info, flagBlackQueensideCastleright_Info>
	{
	public:
		constexpr standardflagsInfo() noexcept :
			flagsInfo<flagWhiteKingsideCastleright_Info, flagWhiteQueensideCastleright_Info, flagBlackKingsideCastleright_Info, flagBlackQueensideCastleright_Info>(
				flagWhiteKingsideCastleright_Info(),
				flagWhiteQueensideCastleright_Info(),
				flagBlackKingsideCastleright_Info(),
				flagBlackQueensideCastleright_Info())
		{

		}
	};
}