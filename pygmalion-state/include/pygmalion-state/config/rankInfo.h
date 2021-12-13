namespace pygmalion::config
{
	class rankInfo
	{
	public:
		const std::string_view shortName;
		const std::string_view longName;
		constexpr rankInfo(const std::string_view& shortName_, const std::string_view& longName_) :
			shortName{ shortName_ },
			longName{ longName_ }
		{

		}
		~rankInfo() noexcept = default;
	};
}