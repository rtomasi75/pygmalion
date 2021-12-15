namespace pygmalion::config
{
	class valueInfo
	{
		template<typename... VALUE>
		friend class enumerationInfo;
	public:
		const std::string_view shortName;
		const std::string_view longName;
	private:
		size_t m_Index;
	protected:
		constexpr valueInfo(const std::string_view& shortName_, const std::string_view& longName_) noexcept :
			shortName{ shortName_ },
			longName{ longName_ },
			m_Index{ 0 }
		{

		}
		constexpr const size_t& index() const noexcept
		{
			return m_Index;
		}
	public:
		bool parse(const std::string& text, size_t& pos) const noexcept
		{
			if (text.length() >= (pos + shortName.length()))
			{
				if (text.substr(pos, shortName.length()) == shortName)
				{
					pos += shortName.length();
					return true;
				}
			}
			return false;
		}
	};
}