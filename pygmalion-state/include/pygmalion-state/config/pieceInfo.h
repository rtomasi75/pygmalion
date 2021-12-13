namespace pygmalion::config
{
	class pieceInfo
	{
	public:
		const std::string_view shortName;
		const std::string_view longName;
		constexpr pieceInfo(const std::string_view& shortName_, const std::string_view& longName_) :
			shortName{ shortName_ },
			longName{ longName_ }
		{

		}
		~pieceInfo() noexcept = default;
	};
}