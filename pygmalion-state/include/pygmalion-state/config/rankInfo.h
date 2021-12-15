namespace pygmalion::config
{
	class rankInfo :
		public valueInfo
	{
	public:
		constexpr rankInfo(const std::string_view& shortName_, const std::string_view& longName_) noexcept :
			valueInfo(shortName_, longName_)
		{

		}
	};
}