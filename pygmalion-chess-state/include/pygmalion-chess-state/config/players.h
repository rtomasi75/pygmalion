namespace pygmalion::config::chess
{
	class whitePlayerInfo :
		public playerInfo
	{
	public:
		constexpr whitePlayerInfo() noexcept :
			playerInfo("w", "white")
		{}
	};

	class blackPlayerInfo :
		public playerInfo
	{
	public:
		constexpr blackPlayerInfo() noexcept :
			playerInfo("b", "black")
		{}
	};

	class standardplayersInfo :
		public playersInfo<whitePlayerInfo, blackPlayerInfo>
	{
	public:
		constexpr standardplayersInfo() noexcept :
			playersInfo<whitePlayerInfo, blackPlayerInfo>(whitePlayerInfo(), blackPlayerInfo())
		{

		}
	};
}