namespace pygmalion::config
{
	class fileInfo
	{
	public:
		const std::string_view shortName;
		const std::string_view longName;
		constexpr fileInfo(const std::string_view& shortName_, const std::string_view& longName_) :
			shortName{ shortName_ },
			longName{ longName_ }
		{

		}
		~fileInfo() noexcept = default;
	};
}