namespace pygmalion::config::chess
{
	class materialScoreInfo :
		public scoreInfo
	{
	public:
		constexpr materialScoreInfo() noexcept :
			scoreInfo(31, 15, 1024)
		{

		}
	};
}