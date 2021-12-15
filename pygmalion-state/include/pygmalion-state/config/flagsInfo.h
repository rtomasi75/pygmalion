namespace pygmalion::config
{
	class flagsInfoBase
	{
		template<typename... FLAGS>
		friend class flagsInfo;
	private:
		flagsInfoBase() noexcept = default;
	};

	template<typename... FLAGS>
	class flagsInfo :
		public enumerationInfo<FLAGS...>,
		public flagsInfoBase
	{
	private:
		template<bool...> struct bool_pack;
		template<bool... bs>
		using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;
		static_assert(all_true<std::is_base_of<flagInfo, FLAGS>::value...>::value, "FLAGS... must inherit flagInfo type.");
	public:
		constexpr flagsInfo(const FLAGS&... flags) noexcept :
			enumerationInfo<FLAGS...>(flags...)
		{
		}
	public:
		template<size_t INDEX>
		constexpr const typename enumerationInfo<FLAGS...>::template valueType<INDEX>& flag() const noexcept
		{
			return this->template value<INDEX>();
		}
	};
}