namespace pygmalion::config
{
	class pieceInfo :
		public valueInfo
	{
	public:
		const bool isStructural;
		const bool isRoyal;
		constexpr pieceInfo(const std::string_view& shortName_, const std::string_view& longName_, const bool isStructural_, const bool isRoyal_) noexcept :
			valueInfo(shortName_, longName_),
			isStructural{isStructural_},
			isRoyal{isRoyal_}
		{

		}
	};
}