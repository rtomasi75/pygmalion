namespace pygmalion::config
{
	class fileInfo :
		public valueInfo
	{
	public:
		constexpr fileInfo(const std::string_view& shortName_, const std::string_view& longName_) noexcept :
			valueInfo(shortName_, longName_)
		{

		}
	};
}