namespace pygmalion::config
{
	class playerInfo :
		public valueInfo
	{
	public:
		constexpr playerInfo(const std::string_view& shortName_, const std::string_view& longName_) noexcept :
			valueInfo(shortName_, longName_)
		{

		}
	};
}