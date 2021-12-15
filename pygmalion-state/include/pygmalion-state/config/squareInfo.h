namespace pygmalion::config
{
	template<typename FILE, typename RANK>
	class squareInfo :
		public valueInfo
	{
	public:
		constexpr squareInfo(const FILE& f, const RANK& r) :
			valueInfo(f.shortName + r.shortName, f.longName + " " + r.longName)
		{

		}
	};
}