namespace pygmalion::config
{
	class playerInfo
	{
	public:
		const std::string_view shortName;
		const std::string_view longName;
		constexpr playerInfo(const std::string_view& shortName_, const std::string_view& longName_) noexcept :
			shortName{ shortName_ },
			longName{ longName_ }
		{
		}
		~playerInfo() noexcept = default;
	};
}