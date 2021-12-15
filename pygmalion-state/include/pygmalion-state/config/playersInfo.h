namespace pygmalion::config
{
	class playersInfoBase
	{
		template<typename... PLAYERS>
		friend class playersInfo;
	private:
		playersInfoBase() noexcept = default;
	};

	template<typename... PLAYERS>
	class playersInfo :
		public enumerationInfo<PLAYERS...>,
		public playersInfoBase
	{
	private:
		template<bool...> struct bool_pack;
		template<bool... bs>
		using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;
		static_assert(all_true<std::is_base_of<playerInfo, PLAYERS>::value...>::value, "PLAYERS... must inherit playerInfo type.");
	public:
		constexpr playersInfo(const PLAYERS&... players) noexcept :
			enumerationInfo<PLAYERS...>(players...)
		{
		}
	public:
		constexpr playersInfo(const playersInfo&) noexcept = default;
		constexpr playersInfo(playersInfo&&) noexcept = default;
		~playersInfo() noexcept = default;
		template<size_t INDEX>
		constexpr const typename enumerationInfo<PLAYERS...>::template valueType<INDEX>& player() const noexcept
		{
			return this->template value<INDEX>();
		}
	};
}