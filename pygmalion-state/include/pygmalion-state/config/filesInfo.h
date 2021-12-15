namespace pygmalion::config
{
	class filesInfoBase
	{
		template<typename... FILES>
		friend class filesInfo;
	private:
		filesInfoBase() noexcept = default;
	};

	template<typename... FILES>
	class filesInfo :
		public enumerationInfo<FILES...>,
		public filesInfoBase
	{
	private:
		template<bool...> struct bool_pack;
		template<bool... bs>
		using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;
		static_assert(all_true<std::is_base_of<fileInfo, FILES>::value...>::value, "FILES... must inherit fileInfo type.");
	public:
		constexpr filesInfo(const FILES&... files) noexcept :
			enumerationInfo<FILES...>(files...)
		{
		}
	public:
		template<size_t INDEX>
		constexpr const typename enumerationInfo<FILES...>::template valueType<INDEX>& file() const noexcept
		{
			return this->template value<INDEX>();
		}
	};
}