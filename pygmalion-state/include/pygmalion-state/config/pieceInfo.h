namespace pygmalion::config
{
	class pieceInfo :
		public valueInfo
	{
	public:
		constexpr pieceInfo(const std::string_view& shortName_, const std::string_view& longName_) noexcept :
			valueInfo(shortName_, longName_)
		{

		}
	};
}