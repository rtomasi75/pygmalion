namespace pygmalion::config
{
	class playerpieceInfo
	{
	private:
	public:
		const std::string_view shortName;
		const std::string_view longName;
		constexpr playerpieceInfo(const std::string_view& shortName_, const std::string_view& longName_) :
			shortName{ shortName_ },
			longName{ longName_ }
		{

		}
	};
}