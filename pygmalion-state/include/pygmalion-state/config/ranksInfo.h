namespace pygmalion::config
{
	class ranksInfoBase
	{
		template<typename... RANKS>
		friend class ranksInfo;
	private:
		ranksInfoBase() noexcept = default;
	};

	template<typename... RANKS>
	class ranksInfo :
		public enumerationInfo<RANKS...>,
		public ranksInfoBase
	{
	private:
		template<bool...> struct bool_pack;
		template<bool... bs>
		using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;
		static_assert(all_true < std::is_base_of<rankInfo, RANKS>::value...>::value, "RANKS... must inherit rankInfo type.");
	public:
		constexpr ranksInfo(const RANKS&... ranks) noexcept :
			enumerationInfo<RANKS...>(ranks...)
		{
		}
	public:
		template<size_t INDEX>
		constexpr const typename enumerationInfo<RANKS...>::template valueType<INDEX>& rank() const noexcept
		{
			return this->template value<INDEX>();
		}
	};
}