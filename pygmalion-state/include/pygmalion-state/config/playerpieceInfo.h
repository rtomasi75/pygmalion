namespace pygmalion::config
{
	template<typename PLAYER, typename PIECE>
	class playerpieceInfo :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const PLAYER& pl, const PIECE& pc) :
			valueInfo(pl.shortName + pc.shortName, pl.longName + " " + pc.longName)
		{

		}
	};
}