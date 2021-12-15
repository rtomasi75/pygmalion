namespace pygmalion::config
{
	class flagInfo :
		public valueInfo
	{
	public:
		constexpr flagInfo(const std::string_view& shortName_, const std::string_view& longName_) noexcept :
			valueInfo(shortName_, longName_)
		{

		}
	};
}